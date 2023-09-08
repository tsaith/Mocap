#include "pch.h"

#include "Diag.h"

#include "PlotLib.h"
#include <matplot/matplot.h>


namespace diag {

    //using namespace plot_utils;
    using namespace plotlib;
    using namespace matplot;

    Diag::Diag()
    {

        mPoseLandmarks = InitVector2f(mNumPoseLandmarks, 4);

        mSkelPoseIndexes = GetSkelPoseIndexes();
        mSkelPoseConnet = GetSkelPoseConnect();

    }

    Diag::~Diag()
    {
    }

    void Diag::Init(int ImageWidth, int ImageHeight)
    {
        mImageWidth = ImageWidth;
        mImageHeight = ImageHeight;
    }

    void Diag::SetInputImage(Mat& Image)
    {
        mInputImage = Image.clone();
    }

    void Diag::SetFps(float Fps)
    {
        mFps = Fps;
    }

    void Diag::SetSkeleton(
        vector<vector<float>>& Quats,
        vector<vector<float>>& Bones)
    {

        mSkelQuats = Quats;
        mSkelBones = Bones;

    }

    void Diag::Process()
    {


        //vector<float> iVec{ 1, 2, 3 };
        auto iVec = linspace(1, 3, 3);
        //vector<float> xVec{ 1, 2, 3 };
        //vector<float> yVec{ 1, 2, 3 };
        vector<double> xVec{ 1, 2, 3 };
        vector<double> yVec{ 1, 2, 3 };
        vector<float> dataX{ 1, 2, 3 };
        vector<float> dataY{ 1, 2, 3 };

        //auto figH = figure();
        //auto ax = figH->current_axes();
        //auto ax = subplot(1, 1, 0);
        auto ax = Subplot(1, 1, 0);

        //figH->ioff();
        Scatter(ax, dataX, dataY);
        //scatter(ax, xVec, yVec);
        //ax->scatter(xVec, yVec);
        auto figH = gcf();

        Mat mat;
        ConvertFigureToMat(figH, mat);

        cv::imshow("mywindow", mat);

        mDiagImage = mInputImage.clone();

        FVector2f bonesPixel = ToPixelSpace(mSkelBones,
            mImageWidth, mImageHeight);

        cv::Mat frontView = cv::Mat(mImageHeight, mImageWidth,
            CV_8UC3, cv::Scalar(255, 255, 255));
        cv::Mat sideView = Mat(mImageHeight, mImageWidth,
            CV_8UC3, cv::Scalar(255, 255, 255));
        cv::Mat topView = Mat(mImageHeight, mImageWidth,
            CV_8UC3, cv::Scalar(255, 255, 255));

        // Cross-section
        PlotSkelBones(frontView, bonesPixel, 0);
        PlotSkelBones(sideView, bonesPixel, 1);
        PlotSkelBones(topView, bonesPixel, 2);


        // Write message 
        mTextPlotter.ResetPosition();

        string  msg;
        msg = "fps: " + to_string(int(mFps + 0.5));
        mTextPlotter.putText(mDiagImage, msg);

        Size size(mImageWidth, mImageHeight);
        mDiagImage = CombineImages2x2(mDiagImage, frontView,
            sideView, topView, size);

    }
    cv::Mat Diag::GetDiagImage()
    {
        return mDiagImage;
    }

    cv::Mat Diag::GetSkelImage()
    {
        return mSkelImage;
    }

    vector<int> Diag::GetSkelPoseIndexes()
    {
        vector<int> indexes
        {
            0, 1, 2, 3, 4, 5,
            6, 7, 8, 10,
            11, 12, 13, 15,
            16, 17, 19,
            21, 22, 24
        };

        return indexes;
    }

    FVector2i Diag::GetSkelPoseConnect()
    {

        vector<vector<int>> connect
        {
            {0, 1}, {1, 2}, {2,3}, {3, 4}, {4, 5},
            {3, 6}, {6, 7}, {7, 8}, {8, 10},
            {3, 11}, {11, 12}, {12, 13}, {13, 15},
            {0, 16}, {16, 17}, {17, 19},
            {0, 21}, {21, 22}, {22, 24}
        };

        return connect;
    }

    void Diag::GetBone2D(float& Out1, float& Out2,
        vector<float> Bone, int IntFlag)
    {

        if (IntFlag == 0) // x-y
        {
            Out1 = Bone[0];
            Out2 = Bone[1];
        }
        else 
        {
            if (IntFlag == 1) // z-y
            {
                Out1 = Bone[2];
                Out2 = Bone[1];
            }
            else // x-z
            {
                Out1 = Bone[0];
                Out2 = Bone[2];
            }

        }

    }


    void Diag::PlotSkelBones(cv::Mat& Image,
        FVector2f& SkelBones, int IntFlag)
    {
        /*
        IntFlag: Flag of view angle
            0: x-y 
            1: z-y
            2: x-z
        */

        // Plot connection lines
        int indexStart, indexEnd;
        float x1 = 0.0f;
        float y1 = 0.0f;
        float x2 = 0.0f;
        float y2 = 0.0f;
        cv::Point p1, p2;
        cv::Scalar lineColor = cv::Scalar(255, 0, 0);
        int lineThickness = 3;
        for (auto& connect : GetSkelPoseConnect()) {

            indexStart = connect[0];
            indexEnd = connect[1];
 
            GetBone2D(x1, y1, SkelBones[indexStart], IntFlag);
            GetBone2D(x2, y2, SkelBones[indexEnd], IntFlag);

            p1 = cv::Point(int(x1), int(y1));
            p2 = cv::Point(int(x2), int(y2));

            cv::line(Image, p1, p2, lineColor, lineThickness, cv::LINE_8);
        }

        // Plot keypoints
        cv::Point point;
        float x = 0.0f;
        float y = 0.0f;
        for (auto& bone : SkelBones) {

            GetBone2D(x, y, bone, IntFlag);
            point.x = int(x);
            point.y = int(y);

            cv::circle(Image, point, 3, cv::Scalar(255, 0, 255), -1);

        }

    }

    cv::Mat Diag::CombineImages2x2(cv::Mat& Img1, cv::Mat& Img2,
        cv::Mat& Img3, cv::Mat& Img4, cv::Size SizeOut)
    {

        // Resize the images to the final size / 2
        cv::Mat resized1, resized2, resized3, resized4;
        cv::resize(Img1, resized1, cv::Size(SizeOut.width / 2, SizeOut.height / 2));
        cv::resize(Img2, resized2, cv::Size(SizeOut.width / 2, SizeOut.height / 2));
        cv::resize(Img3, resized3, cv::Size(SizeOut.width / 2, SizeOut.height / 2));
        cv::resize(Img4, resized4, cv::Size(SizeOut.width / 2, SizeOut.height / 2));

        // Create the final image
        cv::Mat imageOut(SizeOut, Img1.type());

        // Insert the images
        resized1.copyTo(imageOut(cv::Rect(0, 0, SizeOut.width / 2, SizeOut.height / 2)));
        resized2.copyTo(imageOut(cv::Rect(SizeOut.width / 2, 0, SizeOut.width / 2, SizeOut.height / 2)));
        resized3.copyTo(imageOut(cv::Rect(0, SizeOut.height / 2, SizeOut.width / 2, SizeOut.height / 2)));
        resized4.copyTo(imageOut(cv::Rect(SizeOut.width / 2, SizeOut.height / 2, SizeOut.width / 2, SizeOut.height / 2)));

        return imageOut;
    }

    FVector2f Diag::ToPixelSpace(FVector2f& SkelBones, int Width, int Height)
    {

        FVector2f bones = SkelBones;

        size_t numJoints = bones.size();
        int dims = 3;

        for (int i = 0; i < numJoints; i++) {
            bones[i][0] *= Width;
            bones[i][1] *= Height;
            bones[i][2] *= Width;
        }

        return bones;

    }

} // Namespace
