#include "pch.h"
#include "Diag.h"


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

        mDiagImage = mInputImage.clone();


        // Make skeleton plot
        FVector2f bonesPixel = ToPixelSpace(mSkelBones,
            mImageWidth, mImageHeight);
        PlotSkelBones(mSkelImage, bonesPixel);
        /*
        auto figH = figure(true);
        figH->size(mDiagImageWidth, mDiagImageHeight);

        FVector2f bonesPixel = ToPixelSpace(mSkelBones,
            mImageWidth, mImageHeight);

        // Cross-section
        auto ax0 = subplot(figH, 2, 2, 0);
        hold(ax0, false);
        PlotSkelBones(ax0, bonesPixel, 0);

        auto ax1 = subplot(figH, 2, 2, 1);
        hold(ax1, false);
        PlotSkelBones(ax1, bonesPixel, 1);

        auto ax2 = subplot(figH, 2, 2, 2);
        hold(ax2, false);
        PlotSkelBones(ax2, bonesPixel, 2);

        //figH->draw();

        ConvertFigureToMat(figH, mSkelImage);
        */
        cv::imshow("SkelImage", mSkelImage);

        // Write message 
        mTextPlotter.ResetPosition();

        string  msg;
        msg = "fps: " + to_string(int(mFps + 0.5));
        mTextPlotter.putText(mDiagImage, msg);

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

    void Diag::PlotSkelBones(Mat& Image, FVector2f& Bones)
    {

        auto figH = figure(true);
        figH->size(mDiagImageWidth, mDiagImageHeight);

        // Cross-section
        auto ax0 = subplot(figH, 2, 2, 0);
        hold(ax0, false);
        PlotSkelBonesCore(ax0, Bones, 0);

        auto ax1 = subplot(figH, 2, 2, 1);
        hold(ax1, false);
        PlotSkelBonesCore(ax1, Bones, 1);

        auto ax2 = subplot(figH, 2, 2, 2);
        hold(ax2, false);
        PlotSkelBonesCore(ax2, Bones, 2);

        ConvertFigureToMat(figH, Image);

    }

    void Diag::PlotSkelBonesCore(axes_handle& Ax,
        FVector2f& Bones, int ViewFlag)
    {
        /*
        ViewFlag: Flag of view angle
            0: x-y 
            1: z-y
            2: x-z
        */

        float imageWidth = 640;
        float imageHeight = 480;

        double xMarginRatio = 0.25;
        double yMarginRatio = 0.25;

        float xLength = 1.0f*imageWidth * (1.0 + 2.0 * xMarginRatio);
        float yLength = 1.0f*imageHeight * (1.0 + 2.0 * yMarginRatio);

        // Plot connection lines
        int indexStart, indexEnd;
        float x1, y1, x2, y2;

        vector<double> lineX {0.f, 0.f};
        vector<double> lineY {0.f, 0.f};
        int lineThickness = 3;
        for (auto& connect : GetSkelPoseConnect()) {

            indexStart = connect[0];
            indexEnd = connect[1];
 
            GetBone2D(x1, y1, Bones[indexStart], ViewFlag);
            GetBone2D(x2, y2, Bones[indexEnd], ViewFlag);

            lineX[0] = x1;
            lineY[0] = y1;
            lineX[1] = x2;
            lineY[1] = y2;

            plot(Ax, lineX, lineY);
            hold(Ax, true);
        }

        // Plot keypoints
        vector<double> pX;
        vector<double> pY;
        float x = 0.0f;
        float y = 0.0f;
        for (auto& bone : Bones) {

            GetBone2D(x, y, bone, ViewFlag);
            pX.push_back(x);
            pY.push_back(y);
        }

        hold(Ax, true);
        scatter(Ax, pX, pY);

        float xMin, xMax, yMin, yMax;
        if (ViewFlag == 0) {

            xMin = -xMarginRatio * imageWidth;
            xMax = xMin + xLength;
            yMin = -yMarginRatio * imageHeight;
            yMax = yMin + yLength;
            Ax->xlim({xMin, xMax});
            Ax->ylim({yMin, yMax});
            Ax->y_axis().reverse(true);

            Ax->xlabel("x");
            Ax->ylabel("y");
            Ax->title("x-y");

        }
        else if (ViewFlag == 1) {

            xMin = -0.5 * xLength;
            xMax = xMin + xLength;
            yMin = -yMarginRatio * imageHeight;
            yMax = yMin + yLength;

            Ax->xlim({xMin, xMax});
            Ax->ylim({yMin, yMax});
            Ax->y_axis().reverse(true);

            Ax->xlabel("z");
            Ax->ylabel("y");
            Ax->title("z-y");

        }
        else {

            xMin = -xMarginRatio * imageWidth;
            xMax = xMin + xLength;
            yMin = -0.5 * xLength;
            yMax = yMin + xLength;

            Ax->xlim({xMin, xMax});
            Ax->ylim({yMin, yMax});

            Ax->xlabel("x");
            Ax->ylabel("z");
            Ax->title("x-z");

        }

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
