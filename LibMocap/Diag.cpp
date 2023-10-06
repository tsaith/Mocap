#include "pch.h"

#include "Diag.h"


namespace diag {

    //using namespace plot_utils;
    using namespace plotlib;
    using namespace matplot;

    Diag::Diag()
    {

        mPoseLandmarks = InitVector2f(mNumPoseLandmarks, 4);

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

    void Diag::SetPoseLandmarks(FVector2f& PoseLandmarks) 
    {
        mPoseLandmarks = PoseLandmarks;
    }

    void Diag::SetHandLandmarks(FVector2f& LeftHandLandmarks, FVector2f& RightHandLandmarks)
    {
        mLeftHandLandmarks = LeftHandLandmarks;
        mRightHandLandmarks = RightHandLandmarks;
    }


    void Diag::SetSkeleton(
        FVector2f& Quats,
        FVector2f& Bones)
    {

        mSkelQuats = Quats;
        mSkelBones = Bones;

    }

    void Diag::Process()
    {

        mDiagImage = mInputImage.clone();


        // Plot pose on image
        FVector2f posePixel = ToPixelSpace(mPoseLandmarks,
            mImageWidth, mImageHeight);

        FVector2i poseConnect = GetPoseConnect();
        cv_plot::PlotPose2D(mDiagImage, posePixel, poseConnect);

        cv::imshow("Diag", mDiagImage);

        // Plot pose with diffent view
        FVector2f leftHandPixel = ToPixelSpace(mLeftHandLandmarks,
            mImageWidth, mImageHeight);

        FVector2f rightHandPixel = ToPixelSpace(mRightHandLandmarks,
            mImageWidth, mImageHeight);

        PlotLandmarks(mPoseImage, posePixel, leftHandPixel, rightHandPixel);
        cv::imshow("PoseImage", mPoseImage);

        // Plot skeleton
        FVector2f bonesPixel = ToPixelSpace(mSkelBones,
            mImageWidth, mImageHeight);
        PlotSkelBones(mSkelImage, bonesPixel);

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

    vector<int> Diag::GetPoseIndexes()
    {

        vector<int> indexes
        {
            0, 2, 5, 7, 8,
            11, 12, 13, 14, 15, 16,
            23, 24,
            //25, 26,
            //27, 28

        };

        return indexes;
    }

    FVector2i Diag::GetPoseConnect()
    {

        vector<vector<int>> connect
        {
            {0, 2}, {2,7},
            {0, 5}, {5, 8},
            {11, 12}, {12, 24}, {24, 23}, {23, 11},
            {11, 13}, {13, 15},
            {12, 14}, {14, 16},
            //{23, 25}, {25, 27},
            //{24, 26}, {26, 28},

        };

        return connect;
    }

    vector<int> Diag::GetHandIndexes()
    {

        vector<int> indexes;
        for (int i = 0; i < mNumHandLandmarks; i++) {
            indexes.push_back(i);
        }

        return indexes;
    }

    FVector2i Diag::GetHandConnect()
    {

        vector<vector<int>> connect
        {
            {1, 2}, {2, 3}, {3, 4},
            {5, 6}, {6, 7}, {7, 8},
            {9, 10}, {10, 11}, {11, 12},
            {13, 14}, {14, 15}, {15, 16},
            {17, 18}, {18, 19}, {19, 20}
        };

        return connect;
    }

    vector<int> Diag::GetMpPoseIndexes()
    {

        vector<int> indexes;
        for (int i = 0; i < mPoseLandmarks.size(); i++) {
            indexes.push_back(i);
        }

        return indexes;
    }

    FVector2i Diag::GetMpPoseConnect()
    {

        vector<vector<int>> connect
        {
            {0, 1}, {1, 2}, {2,3}, {3, 7},
            {0, 4}, {4, 5}, {5, 6}, {6, 8},
            {9, 10},
            {11, 12}, {12, 24}, {24, 23}, {23, 11},
            {11, 13}, {13, 15}, {15, 21}, {15, 19}, {15, 17}, {17, 19},
            {12, 14}, {14, 16}, {16, 22}, {16, 20}, {16, 18}, {18, 20},
            {23, 25}, {25, 27}, {27, 29}, {27, 31}, {29, 31},
            {24, 26}, {26, 28}, {28, 30}, {28, 32}, {30, 32}
        };

        return connect;
    }


    vector<int> Diag::GetSkelIndexes()
    {
        vector<int> indexes
        {
            0, 1, 2, 3, 4, 5,
            6, 7, 8, 10,
            11, 12, 13, 15,
            16, 21
        };

        return indexes;
    }

    FVector2i Diag::GetSkelConnect()
    {

        vector<vector<int>> connect
        {
            {0, 1}, {1, 2}, {2,3}, {3, 4}, {4, 5},
            {3, 6}, {6, 7}, {7, 8}, {8, 10},
            {3, 11}, {11, 12}, {12, 13}, {13, 15},
            {0, 16}, {0, 21}
        };

        return connect;
    }


    vector<int> Diag::GetSkelLeftHandIndexes()
    {
        vector<int> indexes;
        for (int i = 26; i < 46; i++) {
            indexes.push_back(i);
        }

        return indexes;
    }

    FVector2i Diag::GetSkelLeftHandConnect()
    {

        vector<vector<int>> connect
        {
            {26, 27},  {27, 28},  {28, 29},
            {30, 31},  {31, 32},  {32, 33},
            {34, 35},  {35, 36},  {36, 37},
            {38, 39},  {39, 40},  {40, 41},
        };

        return connect;
    }

    vector<int> Diag::GetSkelRightHandIndexes()
    {
        vector<int> indexes;
        for (int i = 46; i < 66; i++) {
            indexes.push_back(i);
        }

        return indexes;
    }

    FVector2i Diag::GetSkelRightHandConnect()
    {

        vector<vector<int>> connect
        {
            {46, 47},  {47, 48},  {48, 49},
            {50, 51},  {51, 52},  {52, 53},
            {54, 55},  {55, 56},  {56, 57},
            {58, 59},  {59, 60},  {60, 61},
        };

        return connect;
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

    void Diag::PlotLandmarks(Mat& Image, FVector2f& Pose,
        FVector2f& LeftHand, FVector2f& RightHand) 
    {

        auto figH = gcf(true);
        figH->size(mDiagImageWidth, mDiagImageHeight);

        // Cross-sectionPosse
        auto ax0 = subplot(figH, 2, 2, 0);
        hold(ax0, false);
        PlotLandmarksCore(ax0, Pose, LeftHand, RightHand, 0);

        auto ax1 = subplot(figH, 2, 2, 1);
        hold(ax1, false);
        PlotLandmarksCore(ax1, Pose, LeftHand, RightHand, 1);

        auto ax2 = subplot(figH, 2, 2, 2);
        hold(ax2, false);
        PlotLandmarksCore(ax2, Pose, LeftHand, RightHand, 2);

        ConvertFigureToMat(figH, Image);

        // Clear axes
        cla();
    }

    void Diag::PlotLandmarksCore(axes_handle& Ax,
        FVector2f& Pose, FVector2f& LeftHand, FVector2f& RightHand,int ViewFlag)
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

        vector<double> pX;
        vector<double> pY;
        float x = 0.0f;
        float y = 0.0f;

        // Plot Pose lines 
        for (auto& connect : GetPoseConnect()) {

            indexStart = connect[0];
            indexEnd = connect[1];
 
            GetBone2D(x1, y1, Pose[indexStart], ViewFlag);
            GetBone2D(x2, y2, Pose[indexEnd], ViewFlag);

            lineX[0] = x1;
            lineY[0] = y1;
            lineX[1] = x2;
            lineY[1] = y2;

            plot(Ax, lineX, lineY);
            hold(Ax, true);
        }

        // Plot Pose landmarks
        for (auto i : GetPoseIndexes()) {

            auto bone = Pose[i];
            GetBone2D(x, y, bone, ViewFlag);
            pX.push_back(x);
            pY.push_back(y);

        }
        hold(Ax, true);
        auto h = scatter(Ax, pX, pY, 1.0);
        h->marker_face(true);

        // Plot left hand lines 
        hold(Ax, true);
        for (auto& connect : GetHandConnect()) {

            indexStart = connect[0];
            indexEnd = connect[1];
 
            GetBone2D(x1, y1, LeftHand[indexStart], ViewFlag);
            GetBone2D(x2, y2, LeftHand[indexEnd], ViewFlag);

            lineX[0] = x1;
            lineY[0] = y1;
            lineX[1] = x2;
            lineY[1] = y2;

            plot(Ax, lineX, lineY);
            hold(Ax, true);
        }

        hold(Ax, true);

        // Plot left hand landmarks
        for (auto i : GetHandIndexes()) {

            auto bone = LeftHand[i];
            GetBone2D(x, y, bone, ViewFlag);
            pX.push_back(x);
            pY.push_back(y);

        }
        hold(Ax, true);
        h = scatter(Ax, pX, pY, 1.0);
        h->marker_face(true);

        // Plot right hand lines 
        hold(Ax, true);
        for (auto& connect : GetHandConnect()) {

            indexStart = connect[0];
            indexEnd = connect[1];
 
            GetBone2D(x1, y1, RightHand[indexStart], ViewFlag);
            GetBone2D(x2, y2, RightHand[indexEnd], ViewFlag);

            lineX[0] = x1;
            lineY[0] = y1;
            lineX[1] = x2;
            lineY[1] = y2;

            plot(Ax, lineX, lineY);
            hold(Ax, true);
        }

        hold(Ax, true);

        // Plot right hand landmarks
        for (auto i : GetHandIndexes()) {

            auto bone = LeftHand[i];
            GetBone2D(x, y, bone, ViewFlag);
            pX.push_back(x);
            pY.push_back(y);

        }
        hold(Ax, true);
        h = scatter(Ax, pX, pY, 1.0);
        h->marker_face(true);

        // Set plot axes 
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


    void Diag::PlotSkelBones(Mat& Image, FVector2f& Bones)
    {

        auto figH = gcf(true);
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

        // Clear axes
        cla();
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

        // Plot pose lines
        int indexStart, indexEnd;
        float x1, y1, x2, y2;

        vector<double> lineX {0.f, 0.f};
        vector<double> lineY {0.f, 0.f};
        int lineThickness = 5;
        for (auto& connect : GetSkelConnect()) {

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

        // Plot pose keypoints
        vector<double> pX;
        vector<double> pY;
        float x = 0.0f;
        float y = 0.0f;
        for (auto i : GetSkelIndexes()) {
            GetBone2D(x, y, Bones[i], ViewFlag);
            pX.push_back(x);
            pY.push_back(y);
        }

        hold(Ax, true);

        double sz = 3;
        auto h = scatter(Ax, pX, pY, sz);
        h->marker_face(true);

        /*
        // Plot left hand lines
        hold(Ax, true);
        for (auto& connect : GetSkelLeftHandConnect()) {

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

        // Plot right hand lines 
        hold(Ax, true);
        for (auto& connect : GetSkelRightHandConnect()) {

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

        */

        // Plot axes 
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
