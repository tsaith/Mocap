#include "pch.h"
 
#include "skeleton_plotter.h"


SkeletonPlotter::SkeletonPlotter()
{
    // Right Half
    SkeletonBoneR[0] = Skeleton::GetIHandR();
    SkeletonBoneR[1] = Skeleton::GetILowerarmR();
    SkeletonBoneR[2] = Skeleton::GetIUpperarmR();
    SkeletonBoneR[3] = Skeleton::GetIClavicleR();
    SkeletonBoneR[4] = Skeleton::GetISpine03();
    SkeletonBoneR[5] = Skeleton::GetISpine02();
    SkeletonBoneR[6] = Skeleton::GetISpine01();
    SkeletonBoneR[7] = Skeleton::GetIPelvis();
    SkeletonBoneR[8] = Skeleton::GetIThighR();
    SkeletonBoneR[9] = Skeleton::GetICalfR();
    SkeletonBoneR[10] = Skeleton::GetIFootR();
    SkeletonBoneR[11] = Skeleton::GetIBallR();

    // Right Hand
    SkeletonBoneFinger1R[0] = Skeleton::GetIHandR();    // Right Thumb
    SkeletonBoneFinger1R[1] = Skeleton::GetIThumb01R();
    SkeletonBoneFinger1R[2] = Skeleton::GetIThumb02R();
    SkeletonBoneFinger1R[3] = Skeleton::GetIThumb03R();
    SkeletonBoneFinger1R[4] = Skeleton::GetIThumb04R();

    SkeletonBoneFinger2R[0] = Skeleton::GetIHandR();    // Right Index
    SkeletonBoneFinger2R[1] = Skeleton::GetIIndex01R();
    SkeletonBoneFinger2R[2] = Skeleton::GetIIndex02R();
    SkeletonBoneFinger2R[3] = Skeleton::GetIIndex03R();
    SkeletonBoneFinger2R[4] = Skeleton::GetIIndex04R();

    SkeletonBoneFinger3R[0] = Skeleton::GetIHandR();    // Right Middle
    SkeletonBoneFinger3R[1] = Skeleton::GetIMiddle01R();
    SkeletonBoneFinger3R[2] = Skeleton::GetIMiddle02R();
    SkeletonBoneFinger3R[3] = Skeleton::GetIMiddle03R();
    SkeletonBoneFinger3R[4] = Skeleton::GetIMiddle04R();

    SkeletonBoneFinger4R[0] = Skeleton::GetIHandR();    // Right Ring
    SkeletonBoneFinger4R[1] = Skeleton::GetIRing01R();
    SkeletonBoneFinger4R[2] = Skeleton::GetIRing02R();
    SkeletonBoneFinger4R[3] = Skeleton::GetIRing03R();
    SkeletonBoneFinger4R[4] = Skeleton::GetIRing04R();

    SkeletonBoneFinger5R[0] = Skeleton::GetIHandR();    // Right Pinky
    SkeletonBoneFinger5R[1] = Skeleton::GetIPinky01R();
    SkeletonBoneFinger5R[2] = Skeleton::GetIPinky02R();
    SkeletonBoneFinger5R[3] = Skeleton::GetIPinky03R();
    SkeletonBoneFinger5R[4] = Skeleton::GetIPinky04R();

    // Left Half
    SkeletonBoneL[0] = Skeleton::GetIHandL();
    SkeletonBoneL[1] = Skeleton::GetILowerarmL();
    SkeletonBoneL[2] = Skeleton::GetIUpperarmL();
    SkeletonBoneL[3] = Skeleton::GetIClavicleL();
    SkeletonBoneL[4] = Skeleton::GetISpine03();
    SkeletonBoneL[5] = Skeleton::GetISpine02();
    SkeletonBoneL[6] = Skeleton::GetISpine01();
    SkeletonBoneL[7] = Skeleton::GetIPelvis();
    SkeletonBoneL[8] = Skeleton::GetIThighL();
    SkeletonBoneL[9] = Skeleton::GetICalfL();
    SkeletonBoneL[10] = Skeleton::GetIFootL();
    SkeletonBoneL[11] = Skeleton::GetIBallL();

    // Left Hand
    SkeletonBoneFinger1L[0] = Skeleton::GetIHandL();    // Left Thumb
    SkeletonBoneFinger1L[1] = Skeleton::GetIThumb01L();
    SkeletonBoneFinger1L[2] = Skeleton::GetIThumb02L();
    SkeletonBoneFinger1L[3] = Skeleton::GetIThumb03L();
    SkeletonBoneFinger1L[4] = Skeleton::GetIThumb04L();

    SkeletonBoneFinger2L[0] = Skeleton::GetIHandL();    // Left Index
    SkeletonBoneFinger2L[1] = Skeleton::GetIIndex01L();
    SkeletonBoneFinger2L[2] = Skeleton::GetIIndex02L();
    SkeletonBoneFinger2L[3] = Skeleton::GetIIndex03L();
    SkeletonBoneFinger2L[4] = Skeleton::GetIIndex04L();

    SkeletonBoneFinger3L[0] = Skeleton::GetIHandL();    // Left Middle
    SkeletonBoneFinger3L[1] = Skeleton::GetIMiddle01L();
    SkeletonBoneFinger3L[2] = Skeleton::GetIMiddle02L();
    SkeletonBoneFinger3L[3] = Skeleton::GetIMiddle03L();
    SkeletonBoneFinger3L[4] = Skeleton::GetIMiddle04L();

    SkeletonBoneFinger4L[0] = Skeleton::GetIHandL();    // Left Ring
    SkeletonBoneFinger4L[1] = Skeleton::GetIRing01L();
    SkeletonBoneFinger4L[2] = Skeleton::GetIRing02L();
    SkeletonBoneFinger4L[3] = Skeleton::GetIRing03L();
    SkeletonBoneFinger4L[4] = Skeleton::GetIRing04L();

    SkeletonBoneFinger5L[0] = Skeleton::GetIHandL();    // Left Pinky
    SkeletonBoneFinger5L[1] = Skeleton::GetIPinky01L();
    SkeletonBoneFinger5L[2] = Skeleton::GetIPinky02L();
    SkeletonBoneFinger5L[3] = Skeleton::GetIPinky03L();
    SkeletonBoneFinger5L[4] = Skeleton::GetIPinky04L();
}

SkeletonPlotter::~SkeletonPlotter()
{
}

void SkeletonPlotter::SetImageSize(int Width, int Height)
{
    mWidth = Width;
    mHeight = Height;
}

void SkeletonPlotter::SetAxesSize(int length)
{
    mLength = length;
}

void SkeletonPlotter::SetEngineName(string engineName)
{
    mEngineName = engineName;
}

void SkeletonPlotter::SetAxesLabelHor(string label)
{
    mLabelHor = label;
}

void SkeletonPlotter::SetAxesMaximumHor(float value)
{
    mMaximumHor = value;
}

void SkeletonPlotter::SetAxesMinimumHor(float value)
{
    mMinimumHor = value;
}

void SkeletonPlotter::SetAxesLabelVer(string label)
{
    mLabelVer = label;
}

void SkeletonPlotter::SetAxesMaximumVer(float value)
{
    mMaximumVer = value;
}

void SkeletonPlotter::SetAxesMinimumVer(float value)
{
    mMinimumVer = value;
}

Mat SkeletonPlotter::DrawAxes()
{
    Mat image = Mat(500, 500, CV_8UC3, Scalar(255, 255, 255));

    mRatioX = ((float)mLength / abs(mMaximumHor - mMinimumHor)) / (float)mLength;
    mRatioY = ((float)mLength / abs(mMaximumVer - mMinimumVer)) / (float)mLength;
    int i;

    // around
    int x0 = mLength * 0.1, x1 = mLength * 0.9;
    int y0 = mLength * 0.1, y1 = mLength * 0.9;
    DrawLine(image, Point(x0, y0), Point(x0, y1), 2, BGR_BLACK);
    DrawLine(image, Point(x0, y1), Point(x1, y1), 2, BGR_BLACK);
    DrawLine(image, Point(x1, y1), Point(x1, y0), 2, BGR_BLACK);
    DrawLine(image, Point(x1, y0), Point(x0, y0), 2, BGR_BLACK);

    // cross
    Point point_e = Point(mLength * 0.9, mLength * 0.5);
    Point point_s = Point(mLength * 0.5, mLength * 0.9);
    Point point_w = Point(mLength * 0.1, mLength * 0.5);
    Point point_n = Point(mLength * 0.5, mLength * 0.1);
    DrawLine(image, point_e, point_w, 1, BGR_BLACK);
    DrawLine(image, point_s, point_n, 1, BGR_BLACK);

    // mask
    for (i = 0 ; i < 34 ; i++)
    {
        Point temp;
        temp = Point(mLength * (0.1 + 0.025 * i), mLength * 0.5);
        circle(image, temp, 2, BGR_WHITE, -1);
        temp = Point(mLength * 0.5, mLength * (0.1 + 0.025 * i));
        circle(image, temp, 2, BGR_WHITE, -1);
    }

    // text
    Point HorMax = Point(mLength * 0.825, mLength * 0.075);
    Point HorMin = Point(mLength * 0.075, mLength * 0.075);
    Point VerMax = Point(mLength * 0.025, mLength * 0.1);
    Point VerMin = Point(mLength * 0.025, mLength * 0.9);
    int min = mLength * 0.1;
    int mid = mLength * 0.5;
    int max = mLength * 0.9;

    ostringstream MaxX, MinX, MaxY, MinY;
    MaxX << setprecision(2) << fixed << mMaximumHor;
    MinX << setprecision(2) << fixed << mMinimumHor;
    MaxY << setprecision(2) << fixed << mMaximumVer;
    MinY << setprecision(2) << fixed << mMinimumVer;

    // Vertical
    putText(image, mLabelVer, Point(mid, mLength * 0.95), FONT_HERSHEY_PLAIN, 1.0, BGR_BLACK, 2);
    Point2f center(mLength / 2., mLength / 2.);
    Mat rot_mat = getRotationMatrix2D(center, -90, 1.0);
    warpAffine(image, image, rot_mat, Size(mLength, mLength));
    putText(image, MinY.str(), VerMin, FONT_HERSHEY_PLAIN, 1.0, BGR_BLACK, 2);
    putText(image, MaxY.str(), VerMax, FONT_HERSHEY_PLAIN, 1.0, BGR_BLACK, 2);

    // Horizontal
    putText(image, mLabelHor, Point(mid, mLength * 0.95), FONT_HERSHEY_PLAIN, 1.0, BGR_BLACK, 2);
    putText(image, MinX.str(), HorMin, FONT_HERSHEY_PLAIN, 1.0, BGR_BLACK, 2);
    putText(image, MaxX.str(), HorMax, FONT_HERSHEY_PLAIN, 1.0, BGR_BLACK, 2);

    // scale
    for (i = 1 ; i < 10 ; i++)
    {
        Point temp_s, temp_e;
        temp_s = Point(mLength * (0.1 * i), mLength * 0.89);
        temp_e = Point(mLength * (0.1 * i), mLength * 0.91);
        DrawLine(image, temp_s, temp_e, 1, BGR_BLACK);
        temp_s = Point(mLength * 0.09, mLength * (0.1 * i));
        temp_e = Point(mLength * 0.11, mLength * (0.1 * i));
        DrawLine(image, temp_s, temp_e, 1, BGR_BLACK);
    }

    return image;
}

Mat SkeletonPlotter::DrawHolistic(Mat image, Holistic &holistic) 
{
    constexpr int FaceNum = holistic.FACEMESH_LANDMARK_NUM;
    constexpr int HandNum = holistic.HAND_LANDMARK_NUM;
    constexpr int PoseNum = holistic.POSE_LANDMARK_NUM;

    auto facemesh = holistic.facemesh;
    auto pose = holistic.pose;
    auto LeftHand = holistic.LeftHand;
    auto RightHand = holistic.RightHand;

    /*
    if (holistic.HasFacemesh) 
    {
        for (int i = 0; i < FaceNum; i++) 
        {
            float x = facemesh[i][0] * mWidth;
            float y = facemesh[i][1] * mHeight;
            circle(image, Point(x, y), 2, BGR_ORANGE, -1);
        }
    }
    */
    
    if (holistic.HasPose) 
    {
        float x[PoseNum], y[PoseNum];
        //for (int i = 11; i < PoseNum; i++)
        for (int i = 0; i < PoseNum; i++)
        {
            x[i] = pose[i][0] * mWidth;
            y[i] = pose[i][1] * mHeight;
            circle(image, Point(x[i], y[i]), 2, BGR_BLUE, -1);
    
            if (i + 1 >= PoseNum)
            {
                // Right Half
                line(image, Point(x[15], y[15]), Point(x[13], y[13]), BGR_SLIVER, 2);
                line(image, Point(x[13], y[13]), Point(x[11], y[11]), BGR_SLIVER, 2);
                line(image, Point(x[11], y[11]), Point(x[23], y[23]), BGR_SLIVER, 2);
                line(image, Point(x[23], y[23]), Point(x[25], y[25]), BGR_SLIVER, 2);
                line(image, Point(x[25], y[25]), Point(x[27], y[27]), BGR_SLIVER, 2);
                line(image, Point(x[27], y[27]), Point(x[31], y[31]), BGR_SLIVER, 2);
                line(image, Point(x[31], y[31]), Point(x[29], y[29]), BGR_SLIVER, 2);
                line(image, Point(x[29], y[29]), Point(x[27], y[27]), BGR_SLIVER, 2);
    
                // Left Half
                line(image, Point(x[16], y[16]), Point(x[14], y[14]), BGR_SLIVER, 2);
                line(image, Point(x[14], y[14]), Point(x[12], y[12]), BGR_SLIVER, 2);
                line(image, Point(x[12], y[12]), Point(x[24], y[24]), BGR_SLIVER, 2);
                line(image, Point(x[24], y[24]), Point(x[26], y[26]), BGR_SLIVER, 2);
                line(image, Point(x[26], y[26]), Point(x[28], y[28]), BGR_SLIVER, 2);
                line(image, Point(x[28], y[28]), Point(x[32], y[32]), BGR_SLIVER, 2);
                line(image, Point(x[32], y[32]), Point(x[30], y[30]), BGR_SLIVER, 2);
                line(image, Point(x[30], y[30]), Point(x[28], y[28]), BGR_SLIVER, 2);
    
                // Middle
                line(image, Point(x[11], y[11]), Point(x[12], y[12]), BGR_SLIVER, 2);
                line(image, Point(x[23], y[23]), Point(x[24], y[24]), BGR_SLIVER, 2);
            }
        }
    }

    if (holistic.HasLeftHand) 
    {
        for (int i = 0 ; i < HandNum; i++) 
        {
            float x = LeftHand[i][0] * mWidth;
            float y = LeftHand[i][1] * mHeight;
            circle(image, Point(x, y), 2, BGR_GREEN, -1);
        }
    }

    if (holistic.HasRightHand) 
    {
        for (int i = 0 ; i < HandNum; i++) 
        {
            float x = RightHand[i][0] * mWidth;
            float y = RightHand[i][1] * mHeight;
            circle(image, Point(x, y), 2, BGR_GREEN, -1);
        }
    }

    int position_x = (image.cols-1)/2;
    int position_y = (image.rows-1)/2;
    line(image, Point(position_x, 0), Point(position_x, (image.rows-1)), BGR_YELLOW, 2);
    line(image, Point(0, position_y), Point((image.cols-1), position_y), BGR_YELLOW, 2);

    return image;
}

Mat SkeletonPlotter::DrawLine(Mat image, Point a, Point b, int thickness, Scalar RGB)
{
    line(image, a, b, RGB, thickness);
    return image;
}

Mat SkeletonPlotter::DrawHolisticFrontView(Mat image, Holistic &holistic)
{
    int window = mLength * 0.8;
    int shift = mLength * 0.1;
    int i, length;

    constexpr int FaceNum = holistic.FACEMESH_LANDMARK_NUM;
    constexpr int PoseNum = holistic.POSE_LANDMARK_NUM;
    constexpr int LeftHandNum = holistic.HAND_LANDMARK_NUM;
    constexpr int RightHandNum = holistic.HAND_LANDMARK_NUM;

    if (holistic.HasFacemesh)
    {
        auto facemesh = holistic.facemesh;
        float facemeshX[FaceNum], facemeshY[FaceNum];

        for (i = 0; i < FaceNum; i++)
        {
            facemeshX[i] = (facemesh[i][0] * window) * mRatioX + shift;
            facemeshY[i] = (facemesh[i][1] * window) * mRatioY + shift;

            circle(image, Point(facemeshX[i], facemeshY[i]), 1, BGR_RED, -1);
        }
    }

    if (holistic.HasLeftHand) 
    {
        auto LeftHand = holistic.LeftHand;
        float LeftHandX[LeftHandNum], LeftHandY[LeftHandNum];

        for (i = 0; i < LeftHandNum; i++)
        {
            LeftHandX[i] = (LeftHand[i][0] * window) * mRatioX + shift;
            LeftHandY[i] = (LeftHand[i][1] * window) * mRatioY + shift;

            circle(image, Point(LeftHandX[i], LeftHandY[i]), 2, BGR_GREEN, -1);                        
        }
    }

    if (holistic.HasRightHand) 
    {
        auto RightHand = holistic.RightHand;
        float RightHandX[RightHandNum], RightHandY[RightHandNum];

        for (i = 0; i < RightHandNum; i++)
        {
            RightHandX[i] = (RightHand[i][0] * window) * mRatioX + shift;
            RightHandY[i] = (RightHand[i][1] * window) * mRatioY + shift;
            circle(image, Point(RightHandX[i], RightHandY[i]), 2, BGR_GREEN, -1);                        
        }
    }

    if (holistic.HasPose) 
    {
        auto pose = holistic.pose;
        float poseX[PoseNum], poseY[PoseNum];
        float PoseHeadX, PoseHeadY;

        for (i = 0; i < PoseNum; i++)
        {
            poseX[i] = (pose[i][0] * window) * mRatioX + shift;
            poseY[i] = (pose[i][1] * window) * mRatioY + shift;
        }

        PoseHeadX = (poseX[7] + poseX[8]) / 2;
        PoseHeadY = (poseY[7] + poseY[8]) / 2;
        circle(image, Point(PoseHeadX, PoseHeadY), 4, BGR_GREEN, -1);

        length = sizeof(BodyCircleMapR) / sizeof(BodyCircleMapR[0]);
        for (i = 0; i < length; i++)
        {
            circle(image, Point(poseX[BodyCircleMapR[i]], poseY[BodyCircleMapR[i]]), 2, BGR_BLACK, -1);
            circle(image, Point(poseX[BodyCircleMapL[i]], poseY[BodyCircleMapL[i]]), 2, BGR_BLACK, -1);
        }

        length = sizeof(BodyLineMapR) / sizeof(BodyLineMapR[0]);;
        for (i = 0; i < length - 1; i++)
        {
            Scalar Color;
            if (i < 2) { Color = BGR_GRAY; }
            else if (i < 3) { Color = BGR_BLUE; }
            else { Color = BGR_ORANGE; }

            DrawLine(image, Point(poseX[BodyLineMapR[i]], poseY[BodyLineMapR[i]]), Point(poseX[BodyLineMapR[i+1]], poseY[BodyLineMapR[i+1]]), 2, Color);
            DrawLine(image, Point(poseX[BodyLineMapL[i]], poseY[BodyLineMapL[i]]), Point(poseX[BodyLineMapL[i+1]], poseY[BodyLineMapL[i+1]]), 2, Color);
        }

        DrawLine(image, Point(poseX[12], poseY[12]), Point(poseX[11], poseY[11]), 2, BGR_BLUE);
        DrawLine(image, Point(poseX[24], poseY[24]), Point(poseX[23], poseY[23]), 2, BGR_BLUE);
    }

//    flip(image, image, 1);
    return image;
}

Mat SkeletonPlotter::DrawHolisticTopView(Mat image, Holistic &holistic)
{
    int window = mLength * 0.8;
    int shift = mLength * 0.1;
    int i, length;

    constexpr int FaceNum = holistic.FACEMESH_LANDMARK_NUM;
    constexpr int PoseNum = holistic.POSE_LANDMARK_NUM;
    constexpr int LeftHandNum = holistic.HAND_LANDMARK_NUM;
    constexpr int RightHandNum = holistic.HAND_LANDMARK_NUM;

    if (holistic.HasFacemesh)
    {
        auto facemesh = holistic.facemesh;
        float facemeshX[FaceNum], facemeshZ[FaceNum];

        for (i = 0; i < FaceNum; i++)
        {
//            facemeshX[i] = (facemesh[i][0] * window) * mRatioX + shift;
            facemeshX[i] = ((1 - facemesh[i][0]) * window) * mRatioX + shift;
            facemeshZ[i] = ((facemesh[i][2] * window) + 0.5 * window ) * mRatioY + shift ;
            //facemeshZ[i] = ((facemesh[i][2] * window / 2) + (window / 2)) * mRatioY + shift;
            circle(image, Point(facemeshX[i], facemeshZ[i]), 1, BGR_RED, -1);
        }
    }

    if (holistic.HasLeftHand) 
    {
        auto LeftHand = holistic.LeftHand;
        float LeftHandX[LeftHandNum], LeftHandZ[LeftHandNum];

        for (i = 0; i < LeftHandNum; i++)
        {
            LeftHandX[i] = (LeftHand[i][0] * window) * mRatioX + shift;
            LeftHandZ[i] = (LeftHand[i][2] * window + 0.5*window) * mRatioY + shift;
            //LeftHandZ[i] = ((LeftHand[i][2] * window / 2) + (window / 2)) * mRatioY + shift;
            circle(image, Point(LeftHandX[i], LeftHandZ[i]), 2, BGR_GREEN, -1);                        
        }
    }

    if (holistic.HasRightHand) 
    {
        auto RightHand = holistic.RightHand;
        float RightHandX[RightHandNum], RightHandZ[RightHandNum];

        for (i = 0; i < RightHandNum; i++)
        {
            RightHandX[i] = (RightHand[i][0] * window) * mRatioX + shift;
            RightHandZ[i] = (RightHand[i][2] * window + 0.5*window) * mRatioY + shift;
            //RightHandZ[i] = ((RightHand[i][2] * window / 2) + (window / 2)) * mRatioY + shift;
            circle(image, Point(RightHandX[i], RightHandZ[i]), 2, BGR_GREEN, -1);                        
        }
    }

    if (holistic.HasPose) 
    {
        auto pose = holistic.pose;
        float poseX[PoseNum], poseZ[PoseNum];
        float PoseHeadX, PoseHeadZ;

        for (i = 0; i < PoseNum; i++)
        {
            poseX[i] = (pose[i][0] * window) * mRatioX + shift;
            poseZ[i] = ((pose[i][2] * window) + 0.5*window ) * mRatioY + shift;
            //poseZ[i] = ((pose[i][2] * window / 2) + (window / 2)) * mRatioY + shift;
        }

        PoseHeadX = (poseX[7] + poseX[8]) / 2;
        PoseHeadZ = (poseZ[7] + poseZ[8]) / 2;
        circle(image, Point(PoseHeadX, PoseHeadZ), 4, BGR_GREEN, -1);

        length = sizeof(BodyCircleMapR) / sizeof(BodyCircleMapR[0]);
        for (i = 0; i < length; i++)
        {
            circle(image, Point(poseX[BodyCircleMapR[i]], poseZ[BodyCircleMapR[i]]), 2, BGR_BLACK, -1);
            circle(image, Point(poseX[BodyCircleMapL[i]], poseZ[BodyCircleMapL[i]]), 2, BGR_BLACK, -1);
        }

        length = sizeof(BodyLineMapR) / sizeof(BodyLineMapR[0]);;
        for (i = 0; i < length - 1; i++)
        {
            Scalar Color;
            if (i < 2) { Color = BGR_GRAY; }
            else if (i < 3) { Color = BGR_BLUE; }
            else { Color = BGR_ORANGE; }

            DrawLine(image, Point(poseX[BodyLineMapR[i]], poseZ[BodyLineMapR[i]]), Point(poseX[BodyLineMapR[i + 1]], poseZ[BodyLineMapR[i + 1]]), 2, Color);
            DrawLine(image, Point(poseX[BodyLineMapL[i]], poseZ[BodyLineMapL[i]]), Point(poseX[BodyLineMapL[i + 1]], poseZ[BodyLineMapL[i + 1]]), 2, Color);
        }

        DrawLine(image, Point(poseX[12], poseZ[12]), Point(poseX[11], poseZ[11]), 2, BGR_BLUE);
        DrawLine(image, Point(poseX[24], poseZ[24]), Point(poseX[23], poseZ[23]), 2, BGR_BLUE);
    }

    return image;
}

Mat SkeletonPlotter::DrawHolisticSideView(Mat image, Holistic &holistic)
{
    int window = mLength * 0.8;
    int shift = mLength * 0.1;
    int i, length;

    constexpr int FaceNum = holistic.FACEMESH_LANDMARK_NUM;
    constexpr int PoseNum = holistic.POSE_LANDMARK_NUM;
    constexpr int LeftHandNum = holistic.HAND_LANDMARK_NUM;
    constexpr int RightHandNum = holistic.HAND_LANDMARK_NUM;

    if (holistic.HasFacemesh)
    {
        auto facemesh = holistic.facemesh;
        float facemeshZ[FaceNum], facemeshY[FaceNum];

        for (i = 0; i < FaceNum; i++)
        {
            facemeshZ[i] = (facemesh[i][2]*window + 0.5*window) * mRatioX + shift;
            //facemeshZ[i] = ((facemesh[i][2] * window / 2) + (window / 2)) * mRatioX + shift;
            facemeshY[i] = (facemesh[i][1] * window) * mRatioY + shift;
            circle(image, Point(facemeshZ[i], facemeshY[i]), 1, BGR_RED, -1);
        }
    }

    if (holistic.HasLeftHand) 
    {
        auto LeftHand = holistic.LeftHand;
        float LeftHandZ[LeftHandNum], LeftHandY[LeftHandNum];

        for (i = 0; i < LeftHandNum; i++)
        {
            LeftHandZ[i] = (LeftHand[i][2]*window + 0.5*window) * mRatioX + shift;
            //LeftHandZ[i] = ((LeftHand[i][2] * window + (window / 2)) * mRatioX + shift;
            LeftHandY[i] = (LeftHand[i][1] * window) * mRatioY + shift;
            circle(image, Point(LeftHandZ[i], LeftHandY[i]), 2, BGR_GREEN, -1);                        
        }
    }

    if (holistic.HasRightHand) 
    {
        auto RightHand = holistic.RightHand;
        float RightHandZ[RightHandNum], RightHandY[RightHandNum];

        for (i = 0; i < RightHandNum; i++)
        {
            RightHandZ[i] = (RightHand[i][2]*window + 0.5*window) * mRatioX + shift;
            //RightHandZ[i] = ((RightHand[i][2] * window / 2) + (window / 2)) * mRatioX + shift;
            RightHandY[i] = (RightHand[i][1] * window) * mRatioY + shift;
            circle(image, Point(RightHandZ[i], RightHandY[i]), 2, BGR_GREEN, -1);                        
        }
    }

    if (holistic.HasPose) 
    {
        auto pose = holistic.pose;
        float poseZ[PoseNum], poseY[PoseNum];
        float PoseHeadZ, PoseHeadY;

        for (i = 0; i < PoseNum; i++)
        {
            poseZ[i] = (pose[i][2]*window + 0.5*window) * mRatioX + shift;
            //poseZ[i] = ((pose[i][2] * window / 2) + (window / 2)) * mRatioX + shift;
            poseY[i] = (pose[i][1] * window) * mRatioY + shift;
        }

        PoseHeadZ = (poseZ[7] + poseZ[8]) / 2;
        PoseHeadY = (poseY[7] + poseY[8]) / 2;
        circle(image, Point(PoseHeadZ, PoseHeadY), 4, BGR_GREEN, -1);

        length = sizeof(BodyCircleMapR) / sizeof(BodyCircleMapR[0]);
        for (i = 0; i < length; i++)
        {
            circle(image, Point(poseZ[BodyCircleMapR[i]], poseY[BodyCircleMapR[i]]), 2, BGR_BLACK, -1);
            circle(image, Point(poseZ[BodyCircleMapL[i]], poseY[BodyCircleMapL[i]]), 2, BGR_BLACK, -1);
        }

        length = sizeof(BodyLineMapR) / sizeof(BodyLineMapR[0]);;
        for (i = 0; i < length - 1; i++)
        {
            Scalar Color;
            if (i < 2) { Color = BGR_GRAY; }
            else if (i < 3) { Color = BGR_BLUE; }
            else { Color = BGR_ORANGE; }

            DrawLine(image, Point(poseZ[BodyLineMapR[i]], poseY[BodyLineMapR[i]]), Point(poseZ[BodyLineMapR[i + 1]], poseY[BodyLineMapR[i + 1]]), 2, Color);
            DrawLine(image, Point(poseZ[BodyLineMapL[i]], poseY[BodyLineMapL[i]]), Point(poseZ[BodyLineMapL[i + 1]], poseY[BodyLineMapL[i + 1]]), 2, Color);
        }

        DrawLine(image, Point(poseZ[12], poseY[12]), Point(poseZ[11], poseY[11]), 2, BGR_BLUE);
        DrawLine(image, Point(poseZ[24], poseY[24]), Point(poseZ[23], poseY[23]), 2, BGR_BLUE);
    }

    return image;
}

Mat SkeletonPlotter::DrawFrontView(Mat image, Skeleton &skeleton)
{
    int window = mLength * 0.8;
    int shift = mLength * 0.1;
    int i, length;

    float bonesX[66], bonesY[66], bonesZ[66];

    for (i = 0; i < 66; i++)
    {
        auto bones = skeleton.GetBone(i);
        if (mEngineName == "unreal")
        {
            bonesX[i] = (bones[0] * window) * mRatioX + shift;
            bonesY[i] = (-(bones[2] - 1) * window) * mRatioY + shift;
            bonesZ[i] = (-(0.5 - bones[1]) * window + 0.5 * window) * mRatioY + shift;
        }
        else if (mEngineName == "unity")
        {
            bonesX[i] = (bones[0] * window) * mRatioX + shift;
            bonesY[i] = (-bones[1] * window) * mRatioY + shift;
            bonesZ[i] = (bones[2] * window + 0.5 * window) * mRatioY + shift;
        }

        else if (mEngineName == "mediapipe")
        {
            bonesX[i] = (bones[0] * window) * mRatioX + shift;
            bonesY[i] = (bones[1] * window) * mRatioY + shift;
            bonesZ[i] = (bones[2] * window + 0.5 * window) * mRatioY + shift;
        }

//        printf("%d, x=%3.4f, y=%3.4f, z=%3.4f \n", i, bonesX[i], bonesY[i], bonesZ[i]);

//        circle(image, Point(bonesX[i], bonesY[i]), 1, BGR_RED, -1);
        if (((i >= 7) && (i <= 10)) || ((i >= 26) && (i <= 45)))
        {
            if (skeleton.HasLeftHand())
            {
                circle(image, Point(bonesX[i], bonesY[i]), 1, BGR_RED, -1);                
            }
        }
        else if (((i >= 12) && (i <=15)) || ((i >= 46) && (i <= 65)))
        {
            if (skeleton.HasRightHand())
            {
                circle(image, Point(bonesX[i], bonesY[i]), 1, BGR_RED, -1);                
            }
        }
        else
        {
            circle(image, Point(bonesX[i], bonesY[i]), 1, BGR_RED, -1);                            
        }
    }

    // Body
    length = sizeof(SkeletonBoneR) / sizeof(SkeletonBoneR[0]);
    for (i = 0; i < length - 1; i++)
    {
        Scalar Color;
        if (i < 2) { Color = BGR_GRAY; }
        else if (i < 3) { Color = BGR_BLUE; }
        else { Color = BGR_ORANGE; }

        if (i < 1)
        {
            if (skeleton.HasLeftHand()) 
            {
                DrawLine(image, Point(bonesX[SkeletonBoneL[i]], bonesY[SkeletonBoneL[i]]), Point(bonesX[SkeletonBoneL[i+1]], bonesY[SkeletonBoneL[i+1]]), 2, Color);
            }

            if (skeleton.HasRightHand()) 
            {
                DrawLine(image, Point(bonesX[SkeletonBoneR[i]], bonesY[SkeletonBoneR[i]]), Point(bonesX[SkeletonBoneR[i+1]], bonesY[SkeletonBoneR[i+1]]), 2, Color);
            }

        }
        else
        {
            DrawLine(image, Point(bonesX[SkeletonBoneL[i]], bonesY[SkeletonBoneL[i]]), Point(bonesX[SkeletonBoneL[i+1]], bonesY[SkeletonBoneL[i+1]]), 2, Color);
            DrawLine(image, Point(bonesX[SkeletonBoneR[i]], bonesY[SkeletonBoneR[i]]), Point(bonesX[SkeletonBoneR[i+1]], bonesY[SkeletonBoneR[i+1]]), 2, Color);            
        }
    }

    // Hands
    length = sizeof(SkeletonBoneFinger1R) / sizeof(SkeletonBoneFinger1R[0]);
    Scalar Color;

    for (i = 0; i < length - 1; i++) 
    {
        if (i < 2) { Color = BGR_GRAY; }
        else if (i < 3) { Color = BGR_BLUE; }
        else { Color = BGR_ORANGE; }

        if (skeleton.HasLeftHand())
        {
            DrawLine(image, Point(bonesX[SkeletonBoneFinger1L[i]], bonesY[SkeletonBoneFinger1L[i]]), Point(bonesX[SkeletonBoneFinger1L[i+1]], bonesY[SkeletonBoneFinger1L[i+1]]), 2, Color);
            DrawLine(image, Point(bonesX[SkeletonBoneFinger2L[i]], bonesY[SkeletonBoneFinger2L[i]]), Point(bonesX[SkeletonBoneFinger2L[i+1]], bonesY[SkeletonBoneFinger2L[i+1]]), 2, Color);
            DrawLine(image, Point(bonesX[SkeletonBoneFinger3L[i]], bonesY[SkeletonBoneFinger3L[i]]), Point(bonesX[SkeletonBoneFinger3L[i+1]], bonesY[SkeletonBoneFinger3L[i+1]]), 2, Color);
            DrawLine(image, Point(bonesX[SkeletonBoneFinger4L[i]], bonesY[SkeletonBoneFinger4L[i]]), Point(bonesX[SkeletonBoneFinger4L[i+1]], bonesY[SkeletonBoneFinger4L[i+1]]), 2, Color);
            DrawLine(image, Point(bonesX[SkeletonBoneFinger5L[i]], bonesY[SkeletonBoneFinger5L[i]]), Point(bonesX[SkeletonBoneFinger5L[i+1]], bonesY[SkeletonBoneFinger5L[i+1]]), 2, Color);            
        }

        if (skeleton.HasRightHand())
        {
            DrawLine(image, Point(bonesX[SkeletonBoneFinger1R[i]], bonesY[SkeletonBoneFinger1R[i]]), Point(bonesX[SkeletonBoneFinger1R[i+1]], bonesY[SkeletonBoneFinger1R[i+1]]), 2, Color);
            DrawLine(image, Point(bonesX[SkeletonBoneFinger2R[i]], bonesY[SkeletonBoneFinger2R[i]]), Point(bonesX[SkeletonBoneFinger2R[i+1]], bonesY[SkeletonBoneFinger2R[i+1]]), 2, Color);
            DrawLine(image, Point(bonesX[SkeletonBoneFinger3R[i]], bonesY[SkeletonBoneFinger3R[i]]), Point(bonesX[SkeletonBoneFinger3R[i+1]], bonesY[SkeletonBoneFinger3R[i+1]]), 2, Color);
            DrawLine(image, Point(bonesX[SkeletonBoneFinger4R[i]], bonesY[SkeletonBoneFinger4R[i]]), Point(bonesX[SkeletonBoneFinger4R[i+1]], bonesY[SkeletonBoneFinger4R[i+1]]), 2, Color);
            DrawLine(image, Point(bonesX[SkeletonBoneFinger5R[i]], bonesY[SkeletonBoneFinger5R[i]]), Point(bonesX[SkeletonBoneFinger5R[i+1]], bonesY[SkeletonBoneFinger5R[i+1]]), 2, Color);            
        }    
    }

    return image;
}

Mat SkeletonPlotter::DrawTopView(Mat image, Skeleton &skeleton)
{
    int window = mLength * 0.8;
    int shift = mLength * 0.1;
    int i, length;

    float bonesX[66], bonesY[66], bonesZ[66];

    for (i = 0; i < 66; i++)
    {
        auto bones = skeleton.GetBone(i);
        if (mEngineName == "unreal")
        {
            bonesX[i] = (bones[0] * window) * mRatioX + shift;
            bonesY[i] = (-(bones[2] - 1) * window) * mRatioY + shift;
            bonesZ[i] = (-(0.5 - bones[1]) * window + 0.5 * window) * mRatioY + shift;
        }
        else if (mEngineName == "unity")
        {
            bonesX[i] = ((1 - bones[0]) * window) * mRatioX + shift;
            bonesY[i] = (-bones[1] * window) * mRatioY + shift;
            bonesZ[i] = (bones[2] * window + 0.5 * window) * mRatioY + shift;            
        }
        else if (mEngineName == "mediapipe")
        {
            bonesX[i] = (bones[0] * window) * mRatioX + shift;
            bonesY[i] = (bones[1] * window) * mRatioY + shift;
            bonesZ[i] = (bones[2] * window + 0.5 * window) * mRatioY + shift;
        }
//        printf("%d, x=%3.4f, y=%3.4f, z=%3.4f \n", i, bonesX[i], bonesY[i], bonesZ[i]);
        if (((i >= 7) && (i <= 10)) || ((i >= 26) && (i <= 45)))
        {
            if (skeleton.HasLeftHand())
            {
                circle(image, Point(bonesX[i], bonesZ[i]), 1, BGR_RED, -1);
            }
        }
        else if (((i >= 12) && (i <=15)) || ((i >= 46) && (i <= 65)))
        {
            if (skeleton.HasRightHand())
            {
                circle(image, Point(bonesX[i], bonesZ[i]), 1, BGR_RED, -1);
            }
        }
        else
        {
            circle(image, Point(bonesX[i], bonesZ[i]), 1, BGR_RED, -1);
        }
    }

    // Body
    length = sizeof(SkeletonBoneR) / sizeof(SkeletonBoneR[0]);
    for (i = 0; i < length - 1; i++)
    {
        Scalar Color;
        if (i < 2) { Color = BGR_GRAY; }
        else if (i < 3) { Color = BGR_BLUE; }
        else { Color = BGR_ORANGE; }

        if (i < 1)
        {
            if (skeleton.HasLeftHand()) 
            {
                DrawLine(image, Point(bonesX[SkeletonBoneL[i]], bonesZ[SkeletonBoneL[i]]), Point(bonesX[SkeletonBoneL[i+1]], bonesZ[SkeletonBoneL[i+1]]), 2, Color);
            }

            if (skeleton.HasRightHand()) 
            {
                DrawLine(image, Point(bonesX[SkeletonBoneR[i]], bonesZ[SkeletonBoneR[i]]), Point(bonesX[SkeletonBoneR[i+1]], bonesZ[SkeletonBoneR[i+1]]), 2, Color);
            }
        }
        else
        {
            DrawLine(image, Point(bonesX[SkeletonBoneR[i]], bonesZ[SkeletonBoneR[i]]), Point(bonesX[SkeletonBoneR[i+1]], bonesZ[SkeletonBoneR[i+1]]), 2, Color);
            DrawLine(image, Point(bonesX[SkeletonBoneL[i]], bonesZ[SkeletonBoneL[i]]), Point(bonesX[SkeletonBoneL[i+1]], bonesZ[SkeletonBoneL[i+1]]), 2, Color);
        }
    }

    // Hand
    length = sizeof(SkeletonBoneFinger1R) / sizeof(SkeletonBoneFinger1R[0]);
    for (i = 0; i < length - 1; i++)
    {
        Scalar Color;
        if (i < 2) { Color = BGR_GRAY; }
        else if (i < 3) { Color = BGR_BLUE; }
        else { Color = BGR_ORANGE; }

        if (skeleton.HasLeftHand())
        {
            DrawLine(image, Point(bonesX[SkeletonBoneFinger1L[i]], bonesZ[SkeletonBoneFinger1L[i]]), Point(bonesX[SkeletonBoneFinger1L[i+1]], bonesZ[SkeletonBoneFinger1L[i+1]]), 2, Color);
            DrawLine(image, Point(bonesX[SkeletonBoneFinger2L[i]], bonesZ[SkeletonBoneFinger2L[i]]), Point(bonesX[SkeletonBoneFinger2L[i+1]], bonesZ[SkeletonBoneFinger2L[i+1]]), 2, Color);
            DrawLine(image, Point(bonesX[SkeletonBoneFinger3L[i]], bonesZ[SkeletonBoneFinger3L[i]]), Point(bonesX[SkeletonBoneFinger3L[i+1]], bonesZ[SkeletonBoneFinger3L[i+1]]), 2, Color);
            DrawLine(image, Point(bonesX[SkeletonBoneFinger4L[i]], bonesZ[SkeletonBoneFinger4L[i]]), Point(bonesX[SkeletonBoneFinger4L[i+1]], bonesZ[SkeletonBoneFinger4L[i+1]]), 2, Color);
            DrawLine(image, Point(bonesX[SkeletonBoneFinger5L[i]], bonesZ[SkeletonBoneFinger5L[i]]), Point(bonesX[SkeletonBoneFinger5L[i+1]], bonesZ[SkeletonBoneFinger5L[i+1]]), 2, Color);            
        }

        if (skeleton.HasRightHand())
        {
            DrawLine(image, Point(bonesX[SkeletonBoneFinger1R[i]], bonesZ[SkeletonBoneFinger1R[i]]), Point(bonesX[SkeletonBoneFinger1R[i+1]], bonesZ[SkeletonBoneFinger1R[i+1]]), 2, Color);
            DrawLine(image, Point(bonesX[SkeletonBoneFinger2R[i]], bonesZ[SkeletonBoneFinger2R[i]]), Point(bonesX[SkeletonBoneFinger2R[i+1]], bonesZ[SkeletonBoneFinger2R[i+1]]), 2, Color);
            DrawLine(image, Point(bonesX[SkeletonBoneFinger3R[i]], bonesZ[SkeletonBoneFinger3R[i]]), Point(bonesX[SkeletonBoneFinger3R[i+1]], bonesZ[SkeletonBoneFinger3R[i+1]]), 2, Color);
            DrawLine(image, Point(bonesX[SkeletonBoneFinger4R[i]], bonesZ[SkeletonBoneFinger4R[i]]), Point(bonesX[SkeletonBoneFinger4R[i+1]], bonesZ[SkeletonBoneFinger4R[i+1]]), 2, Color);
            DrawLine(image, Point(bonesX[SkeletonBoneFinger5R[i]], bonesZ[SkeletonBoneFinger5R[i]]), Point(bonesX[SkeletonBoneFinger5R[i+1]], bonesZ[SkeletonBoneFinger5R[i+1]]), 2, Color);            
        }
    }

    return image;
}

Mat SkeletonPlotter::DrawSideView(Mat image, Skeleton &skeleton)
{
    int window = mLength * 0.8;
    int shift = mLength * 0.1;
    int i, length;

    float bonesX[66], bonesY[66], bonesZ[66];

    for (i = 0; i < 66; i++)
    {
        auto bones = skeleton.GetBone(i);
        if (mEngineName == "unreal")
        {
            bonesX[i] = (bones[0] * window) * mRatioX + shift;
            bonesY[i] = (-(bones[2] - 1) * window) * mRatioY + shift;
            bonesZ[i] = (-(0.5 - bones[1]) * window + 0.5 * window) * mRatioY + shift;
        }
        else if (mEngineName == "unity")
        {
            bonesX[i] = (bones[0] * window) * mRatioX + shift;
            bonesY[i] = (-bones[1] * window) * mRatioY + shift;
            bonesZ[i] = (bones[2] * window + 0.5 * window) * mRatioY + shift;            
        }
        else if (mEngineName == "mediapipe")
        {
            bonesX[i] = (bones[0] * window) * mRatioX + shift;
            bonesY[i] = (bones[1] * window) * mRatioY + shift;
            bonesZ[i] = (bones[2] * window + 0.5 * window) * mRatioY + shift;
        }
//        printf("%d, x=%3.4f, y=%3.4f, z=%3.4f \n", i, bonesX[i], bonesY[i], bonesZ[i]);
        if (((i >= 7) && (i <= 10)) || ((i >= 26) && (i <= 45)))
        {
            if (skeleton.HasLeftHand())
            {
                circle(image, Point(bonesZ[i], bonesY[i]), 1, BGR_RED, -1);
            }
        }
        else if (((i >= 12) && (i <=15)) || ((i >= 46) && (i <= 65)))
        {
            if (skeleton.HasRightHand())
            {
                circle(image, Point(bonesZ[i], bonesY[i]), 1, BGR_RED, -1);
            }
        }
        else
        {
            circle(image, Point(bonesZ[i], bonesY[i]), 1, BGR_RED, -1);
        }
        
    }

    // Body
    length = sizeof(SkeletonBoneR) / sizeof(SkeletonBoneR[0]);
    for (i = 0; i < length - 1; i++)
    {
        Scalar Color;
        if (i < 2) { Color = BGR_GRAY; }
        else if (i < 3) { Color = BGR_BLUE; }
        else { Color = BGR_ORANGE; }

        if (i < 1)
        {
            if (skeleton.HasLeftHand()) 
            {
                DrawLine(image, Point(bonesZ[SkeletonBoneL[i]], bonesY[SkeletonBoneL[i]]), Point(bonesZ[SkeletonBoneL[i+1]], bonesY[SkeletonBoneL[i+1]]), 2, Color);
            }

            if (skeleton.HasRightHand()) 
            {
                DrawLine(image, Point(bonesZ[SkeletonBoneR[i]], bonesY[SkeletonBoneR[i]]), Point(bonesZ[SkeletonBoneR[i+1]], bonesY[SkeletonBoneR[i+1]]), 2, Color);
            }
        }
        else
        {
            DrawLine(image, Point(bonesZ[SkeletonBoneR[i]], bonesY[SkeletonBoneR[i]]), Point(bonesZ[SkeletonBoneR[i+1]], bonesY[SkeletonBoneR[i+1]]), 2, Color);
            DrawLine(image, Point(bonesZ[SkeletonBoneL[i]], bonesY[SkeletonBoneL[i]]), Point(bonesZ[SkeletonBoneL[i+1]], bonesY[SkeletonBoneL[i+1]]), 2, Color);
        }
    }

    // Hand
    length = sizeof(SkeletonBoneFinger1R) / sizeof(SkeletonBoneFinger1R[0]);
    for (i = 0; i < length - 1; i++)
    {
        Scalar Color;
        if (i < 2) { Color = BGR_GRAY; }
        else if (i < 3) { Color = BGR_BLUE; }
        else { Color = BGR_ORANGE; }

        if (skeleton.HasLeftHand())
        {
            DrawLine(image, Point(bonesZ[SkeletonBoneFinger1L[i]], bonesY[SkeletonBoneFinger1L[i]]), Point(bonesZ[SkeletonBoneFinger1L[i+1]], bonesY[SkeletonBoneFinger1L[i+1]]), 2, Color);
            DrawLine(image, Point(bonesZ[SkeletonBoneFinger2L[i]], bonesY[SkeletonBoneFinger2L[i]]), Point(bonesZ[SkeletonBoneFinger2L[i+1]], bonesY[SkeletonBoneFinger2L[i+1]]), 2, Color);
            DrawLine(image, Point(bonesZ[SkeletonBoneFinger3L[i]], bonesY[SkeletonBoneFinger3L[i]]), Point(bonesZ[SkeletonBoneFinger3L[i+1]], bonesY[SkeletonBoneFinger3L[i+1]]), 2, Color);
            DrawLine(image, Point(bonesZ[SkeletonBoneFinger4L[i]], bonesY[SkeletonBoneFinger4L[i]]), Point(bonesZ[SkeletonBoneFinger4L[i+1]], bonesY[SkeletonBoneFinger4L[i+1]]), 2, Color);
            DrawLine(image, Point(bonesZ[SkeletonBoneFinger5L[i]], bonesY[SkeletonBoneFinger5L[i]]), Point(bonesZ[SkeletonBoneFinger5L[i+1]], bonesY[SkeletonBoneFinger5L[i+1]]), 2, Color);
        }

        if (skeleton.HasRightHand())
        {
            DrawLine(image, Point(bonesZ[SkeletonBoneFinger1R[i]], bonesY[SkeletonBoneFinger1R[i]]), Point(bonesZ[SkeletonBoneFinger1R[i+1]], bonesY[SkeletonBoneFinger1R[i+1]]), 2, Color);
            DrawLine(image, Point(bonesZ[SkeletonBoneFinger2R[i]], bonesY[SkeletonBoneFinger2R[i]]), Point(bonesZ[SkeletonBoneFinger2R[i+1]], bonesY[SkeletonBoneFinger2R[i+1]]), 2, Color);
            DrawLine(image, Point(bonesZ[SkeletonBoneFinger3R[i]], bonesY[SkeletonBoneFinger3R[i]]), Point(bonesZ[SkeletonBoneFinger3R[i+1]], bonesY[SkeletonBoneFinger3R[i+1]]), 2, Color);
            DrawLine(image, Point(bonesZ[SkeletonBoneFinger4R[i]], bonesY[SkeletonBoneFinger4R[i]]), Point(bonesZ[SkeletonBoneFinger4R[i+1]], bonesY[SkeletonBoneFinger4R[i+1]]), 2, Color);
            DrawLine(image, Point(bonesZ[SkeletonBoneFinger5R[i]], bonesY[SkeletonBoneFinger5R[i]]), Point(bonesZ[SkeletonBoneFinger5R[i+1]], bonesY[SkeletonBoneFinger5R[i+1]]), 2, Color);
        }
    }

    return image;
}

// Skeleton With Facemesh
Mat SkeletonPlotter::DrawFacemeshFrontView(Mat image, Skeleton &skeleton, Holistic &holistic)
{
    int window = mLength * 0.8;
    int shift = mLength * 0.1;
    int i, length;

    float bonesX[66], bonesY[66], bonesZ[66];
    auto ShoulderR = skeleton.GetBone(0);
    auto ShoulderL = skeleton.GetBone(0);
    float DistanceShoulder;

    for (i = 0; i < 66; i++)
    {
        auto bones = skeleton.GetBone(i);
        if (mEngineName == "unreal")
        {
            bonesX[i] = (bones[0] * window) * mRatioX;
            bonesY[i] = (-bones[2] * window) * mRatioY;
            bonesZ[i] = (-bones[1] * window + 0.5 * window) * mRatioY;
        }
        else if(mEngineName == "unity")
        {
            bonesX[i] = (bones[0] * window) * mRatioX;
            bonesY[i] = (-bones[1] * window) * mRatioY;
            bonesZ[i] = (bones[2] * window + 0.5 * window) * mRatioY;            
        }
                
        if (i == 65)
        {
            DistanceShoulder = sqrt(pow((bonesX[7] - bonesX[12]), 2) + pow((bonesY[7] - bonesY[12]), 2) + + pow((bonesZ[7] - bonesZ[12]), 2));
        }       
    }

    for (i = 0; i < 66; i++)
    {
        bonesX[i] += shift;
        bonesY[i] += shift;
        bonesZ[i] += shift;
        if (((i >= 7) && (i <= 10)) || ((i >= 26) && (i <= 45)))
        {
            if (skeleton.HasLeftHand())
            {
                circle(image, Point(bonesX[i], bonesY[i]), 1, BGR_RED, -1);                
            }
        }
        else if (((i >= 12) && (i <=15)) || ((i >= 46) && (i <= 65)))
        {
            if (skeleton.HasRightHand())
            {
                circle(image, Point(bonesX[i], bonesY[i]), 1, BGR_RED, -1);                
            }
        }
        else
        {
            circle(image, Point(bonesX[i], bonesY[i]), 1, BGR_RED, -1);                            
        }
    }

    float HeadZeroX = bonesX[5];
    float HeadZeroY = bonesY[5];

    constexpr int FaceNum = holistic.FACEMESH_LANDMARK_NUM;
    if (holistic.HasFacemesh)
    {
        auto facemesh = holistic.facemesh;
        float facemeshX[FaceNum], facemeshY[FaceNum], facemeshZ[FaceNum];
        float DistanceEar;
        float EarMid[3] = {0};
        for (i = 0; i < FaceNum; i++)
        {
            facemeshX[i] = (facemesh[i][0] * window) * mRatioX;
            facemeshY[i] = (facemesh[i][1] * window) * mRatioY;
            facemeshZ[i] = (facemesh[i][2] * window + 0.5 * window) * mRatioX;

            if (i == (FaceNum - 1))
            {
                DistanceEar = sqrt(pow((facemeshX[234] - facemeshX[454]), 2) + pow((facemeshY[234] - facemeshY[454]), 2) + + pow((facemeshZ[234] - facemeshZ[454]), 2));
                EarMid[0] = (facemeshX[234] + facemeshX[454]) / 2;
                EarMid[1] = (facemeshY[234] + facemeshY[454]) / 2;
                EarMid[2] = (facemeshZ[234] + facemeshZ[454]) / 2;
            }
        }
        float TempX = (EarMid[0] - facemeshX[10]) * 2;
        float TempY = (EarMid[1] - facemeshY[10]) * 2;
        float TempZ = (EarMid[2] - facemeshZ[10]) * 2;
        float NewZero[3] = {0};
        NewZero[0] = facemeshX[10] + TempX;
        NewZero[1] = facemeshY[10] + TempY;
        NewZero[2] = facemeshZ[10] + TempZ;
        
        float ShiftTempX = HeadZeroX - ((NewZero[0] * (DistanceShoulder / DistanceEar * 0.55)) + shift);
        float ShiftTempY = HeadZeroY - ((NewZero[1] * (DistanceShoulder / DistanceEar * 0.55)) + shift);

        for (i = 0; i < FaceNum; i++)
        {
            facemeshX[i] *= (DistanceShoulder / DistanceEar * 0.55);
            facemeshX[i] += (shift + ShiftTempX);
            facemeshY[i] *= (DistanceShoulder / DistanceEar * 0.55);
            facemeshY[i] += (shift + ShiftTempY);

            circle(image, Point(facemeshX[i], facemeshY[i]), 1, BGR_RED, -1);
            if (i == (FaceNum - 1))
            {
                DistanceEar = sqrt(pow((facemeshX[234] - facemeshX[454]), 2) + pow((facemeshY[234] - facemeshY[454]), 2) + + pow((facemeshZ[234] - facemeshZ[454]), 2));
            }
        }
    }

    // Body
    length = sizeof(SkeletonBoneR) / sizeof(SkeletonBoneR[0]);
    for (i = 0; i < length - 1; i++)
    {
        Scalar Color;
        if (i < 2) { Color = BGR_GRAY; }
        else if (i < 3) { Color = BGR_BLUE; }
        else { Color = BGR_ORANGE; }

        if (i < 1)
        {
            if (skeleton.HasLeftHand()) 
            {
                DrawLine(image, Point(bonesX[SkeletonBoneL[i]], bonesY[SkeletonBoneL[i]]), Point(bonesX[SkeletonBoneL[i+1]], bonesY[SkeletonBoneL[i+1]]), 2, Color);
            }

            if (skeleton.HasRightHand()) 
            {
                DrawLine(image, Point(bonesX[SkeletonBoneR[i]], bonesY[SkeletonBoneR[i]]), Point(bonesX[SkeletonBoneR[i+1]], bonesY[SkeletonBoneR[i+1]]), 2, Color);
            }
        }
        else
        {
            DrawLine(image, Point(bonesX[SkeletonBoneR[i]], bonesY[SkeletonBoneR[i]]), Point(bonesX[SkeletonBoneR[i+1]], bonesY[SkeletonBoneR[i+1]]), 2, Color);
            DrawLine(image, Point(bonesX[SkeletonBoneL[i]], bonesY[SkeletonBoneL[i]]), Point(bonesX[SkeletonBoneL[i+1]], bonesY[SkeletonBoneL[i+1]]), 2, Color);
        }
    }

    // Hand
    length = sizeof(SkeletonBoneFinger1R) / sizeof(SkeletonBoneFinger1R[0]);
    for (i = 0; i < length - 1; i++)
    {
        Scalar Color;
        if (i < 2) { Color = BGR_GRAY; }
        else if (i < 3) { Color = BGR_BLUE; }
        else { Color = BGR_ORANGE; }

        if (skeleton.HasLeftHand())
        {
            DrawLine(image, Point(bonesX[SkeletonBoneFinger1L[i]], bonesY[SkeletonBoneFinger1L[i]]), Point(bonesX[SkeletonBoneFinger1L[i+1]], bonesY[SkeletonBoneFinger1L[i+1]]), 2, Color);
            DrawLine(image, Point(bonesX[SkeletonBoneFinger2L[i]], bonesY[SkeletonBoneFinger2L[i]]), Point(bonesX[SkeletonBoneFinger2L[i+1]], bonesY[SkeletonBoneFinger2L[i+1]]), 2, Color);
            DrawLine(image, Point(bonesX[SkeletonBoneFinger3L[i]], bonesY[SkeletonBoneFinger3L[i]]), Point(bonesX[SkeletonBoneFinger3L[i+1]], bonesY[SkeletonBoneFinger3L[i+1]]), 2, Color);
            DrawLine(image, Point(bonesX[SkeletonBoneFinger4L[i]], bonesY[SkeletonBoneFinger4L[i]]), Point(bonesX[SkeletonBoneFinger4L[i+1]], bonesY[SkeletonBoneFinger4L[i+1]]), 2, Color);
            DrawLine(image, Point(bonesX[SkeletonBoneFinger5L[i]], bonesY[SkeletonBoneFinger5L[i]]), Point(bonesX[SkeletonBoneFinger5L[i+1]], bonesY[SkeletonBoneFinger5L[i+1]]), 2, Color);            
        }

        if (skeleton.HasRightHand())
        {
            DrawLine(image, Point(bonesX[SkeletonBoneFinger1R[i]], bonesY[SkeletonBoneFinger1R[i]]), Point(bonesX[SkeletonBoneFinger1R[i+1]], bonesY[SkeletonBoneFinger1R[i+1]]), 2, Color);
            DrawLine(image, Point(bonesX[SkeletonBoneFinger2R[i]], bonesY[SkeletonBoneFinger2R[i]]), Point(bonesX[SkeletonBoneFinger2R[i+1]], bonesY[SkeletonBoneFinger2R[i+1]]), 2, Color);
            DrawLine(image, Point(bonesX[SkeletonBoneFinger3R[i]], bonesY[SkeletonBoneFinger3R[i]]), Point(bonesX[SkeletonBoneFinger3R[i+1]], bonesY[SkeletonBoneFinger3R[i+1]]), 2, Color);
            DrawLine(image, Point(bonesX[SkeletonBoneFinger4R[i]], bonesY[SkeletonBoneFinger4R[i]]), Point(bonesX[SkeletonBoneFinger4R[i+1]], bonesY[SkeletonBoneFinger4R[i+1]]), 2, Color);
            DrawLine(image, Point(bonesX[SkeletonBoneFinger5R[i]], bonesY[SkeletonBoneFinger5R[i]]), Point(bonesX[SkeletonBoneFinger5R[i+1]], bonesY[SkeletonBoneFinger5R[i+1]]), 2, Color);            
        }

    }

    return image;
}

Mat SkeletonPlotter::DrawFacemeshTopView(Mat image, Skeleton &skeleton, Holistic &holistic)
{
    int window = mLength * 0.8;
    int shift = mLength * 0.1;
    int i, length;

    float bonesX[66], bonesY[66], bonesZ[66];
    auto ShoulderR = skeleton.GetBone(0);
    auto ShoulderL = skeleton.GetBone(0);
    float DistanceShoulder;

    for (i = 0; i < 66; i++)
    {
        auto bones = skeleton.GetBone(i);
        if (mEngineName == "unreal")
        {
            bonesX[i] = (bones[0] * window) * mRatioX;
            bonesY[i] = (-bones[2] * window) * mRatioY;
            bonesZ[i] = (-bones[1] * window + 0.5 * window) * mRatioY;
        }
        else if (mEngineName == "unity")
        {
            bonesX[i] = (bones[0] * window) * mRatioX;
            bonesY[i] = (-bones[1] * window) * mRatioY;
            bonesZ[i] = (bones[2] * window + 0.5 * window) * mRatioY;
        }
                
        if (i == 65)
        {
            DistanceShoulder = sqrt(pow((bonesX[7] - bonesX[12]), 2) + pow((bonesY[7] - bonesY[12]), 2) + + pow((bonesZ[7] - bonesZ[12]), 2));
        }       
    }

    for (i = 0; i < 66; i++)
    {
        bonesX[i] += shift;
        bonesY[i] += shift;
        bonesZ[i] += shift;
        if (((i >= 7) && (i <= 10)) || ((i >= 26) && (i <= 45)))
        {
            if (skeleton.HasLeftHand())
            {
                circle(image, Point(bonesX[i], bonesZ[i]), 1, BGR_RED, -1);
            }
        }
        else if (((i >= 12) && (i <=15)) || ((i >= 46) && (i <= 65)))
        {
            if (skeleton.HasRightHand())
            {
                circle(image, Point(bonesX[i], bonesZ[i]), 1, BGR_RED, -1);
            }
        }
        else
        {
            circle(image, Point(bonesX[i], bonesZ[i]), 1, BGR_RED, -1);
        }
    }

    float HeadZeroX = bonesX[5];
    float HeadZeroZ = bonesZ[5];

    constexpr int FaceNum = holistic.FACEMESH_LANDMARK_NUM;
    if (holistic.HasFacemesh)
    {
        auto facemesh = holistic.facemesh;
        float facemeshX[FaceNum], facemeshY[FaceNum], facemeshZ[FaceNum];
        float DistanceEar;
		float EarMid[3] = {0};
        for (i = 0; i < FaceNum; i++)
        {
            facemeshX[i] = (facemesh[i][0] * window) * mRatioX;
            facemeshY[i] = (facemesh[i][1] * window) * mRatioY;
            facemeshZ[i] = (facemesh[i][2] * window + 0.5 * window) * mRatioX;

            if (i == (FaceNum - 1))
            {
                DistanceEar = sqrt(pow((facemeshX[234] - facemeshX[454]), 2) + pow((facemeshY[234] - facemeshY[454]), 2) + + pow((facemeshZ[234] - facemeshZ[454]), 2));
                EarMid[0] = (facemeshX[234] + facemeshX[454]) / 2;
                EarMid[1] = (facemeshY[234] + facemeshY[454]) / 2;
                EarMid[2] = (facemeshZ[234] + facemeshZ[454]) / 2;
            }
        }
        float TempX = (EarMid[0] - facemeshX[10]) * 2;
        float TempY = (EarMid[1] - facemeshY[10]) * 2;
        float TempZ = (EarMid[2] - facemeshZ[10]);
        float NewZero[3] = {0};
        NewZero[0] = facemeshX[10] + TempX;
        NewZero[1] = facemeshY[10] + TempY;
        NewZero[2] = facemeshZ[10] + TempZ;

        float ShiftTempX = HeadZeroX - ((NewZero[0] * (DistanceShoulder / DistanceEar * 0.55)) + shift);
        float ShiftTempZ = HeadZeroZ - ((NewZero[2] * (DistanceShoulder / DistanceEar * 0.55)) + shift);

        for (i = 0; i < FaceNum; i++)
        {
            facemeshX[i] *= (DistanceShoulder / DistanceEar * 0.55);
            facemeshX[i] += (shift + ShiftTempX);
            facemeshZ[i] *= (DistanceShoulder / DistanceEar * 0.55);
            facemeshZ[i] += (shift + ShiftTempZ);

            circle(image, Point(facemeshX[i], facemeshZ[i]), 1, BGR_RED, -1);
            if (i == (FaceNum - 1))
            {
                DistanceEar = sqrt(pow((facemeshX[234] - facemeshX[454]), 2) + pow((facemeshY[234] - facemeshY[454]), 2) + + pow((facemeshZ[234] - facemeshZ[454]), 2));
            }
        }
    }

    // Body
    length = sizeof(SkeletonBoneR) / sizeof(SkeletonBoneR[0]);
    for (i = 0; i < length - 1; i++)
    {
        Scalar Color;
        if (i < 2) { Color = BGR_GRAY; }
        else if (i < 3) { Color = BGR_BLUE; }
        else { Color = BGR_ORANGE; }

        if (i < 1)
        {
            if (skeleton.HasLeftHand()) 
            {
                DrawLine(image, Point(bonesX[SkeletonBoneL[i]], bonesZ[SkeletonBoneL[i]]), Point(bonesX[SkeletonBoneL[i+1]], bonesZ[SkeletonBoneL[i+1]]), 2, Color);
            }

            if (skeleton.HasRightHand()) 
            {
                DrawLine(image, Point(bonesX[SkeletonBoneR[i]], bonesZ[SkeletonBoneR[i]]), Point(bonesX[SkeletonBoneR[i+1]], bonesZ[SkeletonBoneR[i+1]]), 2, Color);
            }
        }
        else
        {
            DrawLine(image, Point(bonesX[SkeletonBoneR[i]], bonesZ[SkeletonBoneR[i]]), Point(bonesX[SkeletonBoneR[i+1]], bonesZ[SkeletonBoneR[i+1]]), 2, Color);
            DrawLine(image, Point(bonesX[SkeletonBoneL[i]], bonesZ[SkeletonBoneL[i]]), Point(bonesX[SkeletonBoneL[i+1]], bonesZ[SkeletonBoneL[i+1]]), 2, Color);
        }
    }

    // Hand
    length = sizeof(SkeletonBoneFinger1R) / sizeof(SkeletonBoneFinger1R[0]);
    for (i = 0; i < length - 1; i++)
    {
        Scalar Color;
        if (i < 2) { Color = BGR_GRAY; }
        else if (i < 3) { Color = BGR_BLUE; }
        else { Color = BGR_ORANGE; }

        if (skeleton.HasLeftHand())
        {
            DrawLine(image, Point(bonesX[SkeletonBoneFinger1L[i]], bonesZ[SkeletonBoneFinger1L[i]]), Point(bonesX[SkeletonBoneFinger1L[i+1]], bonesZ[SkeletonBoneFinger1L[i+1]]), 2, Color);
            DrawLine(image, Point(bonesX[SkeletonBoneFinger2L[i]], bonesZ[SkeletonBoneFinger2L[i]]), Point(bonesX[SkeletonBoneFinger2L[i+1]], bonesZ[SkeletonBoneFinger2L[i+1]]), 2, Color);
            DrawLine(image, Point(bonesX[SkeletonBoneFinger3L[i]], bonesZ[SkeletonBoneFinger3L[i]]), Point(bonesX[SkeletonBoneFinger3L[i+1]], bonesZ[SkeletonBoneFinger3L[i+1]]), 2, Color);
            DrawLine(image, Point(bonesX[SkeletonBoneFinger4L[i]], bonesZ[SkeletonBoneFinger4L[i]]), Point(bonesX[SkeletonBoneFinger4L[i+1]], bonesZ[SkeletonBoneFinger4L[i+1]]), 2, Color);
            DrawLine(image, Point(bonesX[SkeletonBoneFinger5L[i]], bonesZ[SkeletonBoneFinger5L[i]]), Point(bonesX[SkeletonBoneFinger5L[i+1]], bonesZ[SkeletonBoneFinger5L[i+1]]), 2, Color);
        }

        if (skeleton.HasRightHand())
        {
            DrawLine(image, Point(bonesX[SkeletonBoneFinger1R[i]], bonesZ[SkeletonBoneFinger1R[i]]), Point(bonesX[SkeletonBoneFinger1R[i+1]], bonesZ[SkeletonBoneFinger1R[i+1]]), 2, Color);
            DrawLine(image, Point(bonesX[SkeletonBoneFinger2R[i]], bonesZ[SkeletonBoneFinger2R[i]]), Point(bonesX[SkeletonBoneFinger2R[i+1]], bonesZ[SkeletonBoneFinger2R[i+1]]), 2, Color);
            DrawLine(image, Point(bonesX[SkeletonBoneFinger3R[i]], bonesZ[SkeletonBoneFinger3R[i]]), Point(bonesX[SkeletonBoneFinger3R[i+1]], bonesZ[SkeletonBoneFinger3R[i+1]]), 2, Color);
            DrawLine(image, Point(bonesX[SkeletonBoneFinger4R[i]], bonesZ[SkeletonBoneFinger4R[i]]), Point(bonesX[SkeletonBoneFinger4R[i+1]], bonesZ[SkeletonBoneFinger4R[i+1]]), 2, Color);
            DrawLine(image, Point(bonesX[SkeletonBoneFinger5R[i]], bonesZ[SkeletonBoneFinger5R[i]]), Point(bonesX[SkeletonBoneFinger5R[i+1]], bonesZ[SkeletonBoneFinger5R[i+1]]), 2, Color);
        }
    }

    return image;
}

Mat SkeletonPlotter::DrawFacemeshSideView(Mat image, Skeleton &skeleton, Holistic &holistic)
{
    int window = mLength * 0.8;
    int shift = mLength * 0.1;
    int i, length;

    float bonesX[66], bonesY[66], bonesZ[66];
    auto ShoulderR = skeleton.GetBone(0);
    auto ShoulderL = skeleton.GetBone(0);
    float DistanceShoulder;

    for (i = 0; i < 66; i++)
    {
        auto bones = skeleton.GetBone(i);
        if (mEngineName == "unreal")
        {
            bonesX[i] = (bones[0] * window) * mRatioX;
            bonesY[i] = (-bones[2] * window) * mRatioY;
            bonesZ[i] = (-bones[1] * window + 0.5 * window) * mRatioY;
        }
        else if (mEngineName == "unity")
        {
            bonesX[i] = (bones[0] * window) * mRatioX;
            bonesY[i] = (-bones[1] * window) * mRatioY;
            bonesZ[i] = (bones[2] * window + 0.5 * window) * mRatioY;
        }
                
        if (i == 65)
        {
            DistanceShoulder = sqrt(pow((bonesX[7] - bonesX[12]), 2) + pow((bonesY[7] - bonesY[12]), 2) + + pow((bonesZ[7] - bonesZ[12]), 2));
        }       
    }

    for (i = 0; i < 66; i++)
    {
        bonesX[i] += shift;
        bonesY[i] += shift;
        bonesZ[i] += shift;
        if (((i >= 7) && (i <= 10)) || ((i >= 26) && (i <= 45)))
        {
            if (skeleton.HasLeftHand())
            {
                circle(image, Point(bonesZ[i], bonesY[i]), 1, BGR_RED, -1);
            }
        }
        else if (((i >= 12) && (i <=15)) || ((i >= 46) && (i <= 65)))
        {
            if (skeleton.HasRightHand())
            {
                circle(image, Point(bonesZ[i], bonesY[i]), 1, BGR_RED, -1);
            }
        }
        else
        {
            circle(image, Point(bonesZ[i], bonesY[i]), 1, BGR_RED, -1);
        }
    }

    float HeadZeroZ = bonesZ[5];
    float HeadZeroY = bonesY[5];

    constexpr int FaceNum = holistic.FACEMESH_LANDMARK_NUM;
    if (holistic.HasFacemesh)
    {
        auto facemesh = holistic.facemesh;
        float facemeshX[FaceNum], facemeshY[FaceNum], facemeshZ[FaceNum];
        float DistanceEar;
		float EarMid[3] = {0};
        for (i = 0; i < FaceNum; i++)
        {
            facemeshX[i] = (facemesh[i][0] * window) * mRatioX;
            facemeshY[i] = (facemesh[i][1] * window) * mRatioY;
            facemeshZ[i] = (facemesh[i][2] * window + 0.5 * window) * mRatioX;

            if (i == (FaceNum - 1))
            {
                DistanceEar = sqrt(pow((facemeshX[234] - facemeshX[454]), 2) + pow((facemeshY[234] - facemeshY[454]), 2) + + pow((facemeshZ[234] - facemeshZ[454]), 2));
                EarMid[0] = (facemeshX[234] + facemeshX[454]) / 2;
                EarMid[1] = (facemeshY[234] + facemeshY[454]) / 2;
                EarMid[2] = (facemeshZ[234] + facemeshZ[454]) / 2;
            }
        }
        float TempX = (EarMid[0] - facemeshX[10]) * 2;
        float TempY = (EarMid[1] - facemeshY[10]) * 2;
        float TempZ = (EarMid[2] - facemeshZ[10]);
        float NewZero[3] = {0};
        NewZero[0] = facemeshX[10] + TempX;
        NewZero[1] = facemeshY[10] + TempY;
        NewZero[2] = facemeshZ[10] + TempZ;

        float ShiftTempZ = HeadZeroZ - ((NewZero[2] * (DistanceShoulder / DistanceEar * 0.55)) + shift);
        float ShiftTempY = HeadZeroY - ((NewZero[1] * (DistanceShoulder / DistanceEar * 0.55)) + shift);

        for (i = 0; i < FaceNum; i++)
        {
            facemeshY[i] *= (DistanceShoulder / DistanceEar * 0.55);
            facemeshY[i] += (shift + ShiftTempY);
            facemeshZ[i] *= (DistanceShoulder / DistanceEar * 0.55);
            facemeshZ[i] += (shift + ShiftTempZ);

            circle(image, Point(facemeshZ[i], facemeshY[i]), 1, BGR_RED, -1);
            if (i == (FaceNum - 1))
            {
                DistanceEar = sqrt(pow((facemeshX[234] - facemeshX[454]), 2) + pow((facemeshY[234] - facemeshY[454]), 2) + + pow((facemeshZ[234] - facemeshZ[454]), 2));
            }
        }
    }

    // Body
    length = sizeof(SkeletonBoneR) / sizeof(SkeletonBoneR[0]);
    for (i = 0; i < length - 1; i++)
    {
        Scalar Color;
        if (i < 2) { Color = BGR_GRAY; }
        else if (i < 3) { Color = BGR_BLUE; }
        else { Color = BGR_ORANGE; }

        if (i < 1)
        {
            if (skeleton.HasLeftHand()) 
            {
                DrawLine(image, Point(bonesZ[SkeletonBoneL[i]], bonesY[SkeletonBoneL[i]]), Point(bonesZ[SkeletonBoneL[i+1]], bonesY[SkeletonBoneL[i+1]]), 2, Color);
            }

            if (skeleton.HasRightHand()) 
            {
                DrawLine(image, Point(bonesZ[SkeletonBoneR[i]], bonesY[SkeletonBoneR[i]]), Point(bonesZ[SkeletonBoneR[i+1]], bonesY[SkeletonBoneR[i+1]]), 2, Color);
            }
        }
        else
        {
            DrawLine(image, Point(bonesZ[SkeletonBoneR[i]], bonesY[SkeletonBoneR[i]]), Point(bonesZ[SkeletonBoneR[i+1]], bonesY[SkeletonBoneR[i+1]]), 2, Color);
            DrawLine(image, Point(bonesZ[SkeletonBoneL[i]], bonesY[SkeletonBoneL[i]]), Point(bonesZ[SkeletonBoneL[i+1]], bonesY[SkeletonBoneL[i+1]]), 2, Color);
        }
    }

    // Hand
    length = sizeof(SkeletonBoneFinger1R) / sizeof(SkeletonBoneFinger1R[0]);
    for (i = 0; i < length - 1; i++)
    {
        Scalar Color;
        if (i < 2) { Color = BGR_GRAY; }
        else if (i < 3) { Color = BGR_BLUE; }
        else { Color = BGR_ORANGE; }

        if (skeleton.HasLeftHand())
        {
            DrawLine(image, Point(bonesZ[SkeletonBoneFinger1L[i]], bonesY[SkeletonBoneFinger1L[i]]), Point(bonesZ[SkeletonBoneFinger1L[i+1]], bonesY[SkeletonBoneFinger1L[i+1]]), 2, Color);
            DrawLine(image, Point(bonesZ[SkeletonBoneFinger2L[i]], bonesY[SkeletonBoneFinger2L[i]]), Point(bonesZ[SkeletonBoneFinger2L[i+1]], bonesY[SkeletonBoneFinger2L[i+1]]), 2, Color);
            DrawLine(image, Point(bonesZ[SkeletonBoneFinger3L[i]], bonesY[SkeletonBoneFinger3L[i]]), Point(bonesZ[SkeletonBoneFinger3L[i+1]], bonesY[SkeletonBoneFinger3L[i+1]]), 2, Color);
            DrawLine(image, Point(bonesZ[SkeletonBoneFinger4L[i]], bonesY[SkeletonBoneFinger4L[i]]), Point(bonesZ[SkeletonBoneFinger4L[i+1]], bonesY[SkeletonBoneFinger4L[i+1]]), 2, Color);
            DrawLine(image, Point(bonesZ[SkeletonBoneFinger5L[i]], bonesY[SkeletonBoneFinger5L[i]]), Point(bonesZ[SkeletonBoneFinger5L[i+1]], bonesY[SkeletonBoneFinger5L[i+1]]), 2, Color);
        }

        if (skeleton.HasRightHand())
        {
            DrawLine(image, Point(bonesZ[SkeletonBoneFinger1R[i]], bonesY[SkeletonBoneFinger1R[i]]), Point(bonesZ[SkeletonBoneFinger1R[i+1]], bonesY[SkeletonBoneFinger1R[i+1]]), 2, Color);
            DrawLine(image, Point(bonesZ[SkeletonBoneFinger2R[i]], bonesY[SkeletonBoneFinger2R[i]]), Point(bonesZ[SkeletonBoneFinger2R[i+1]], bonesY[SkeletonBoneFinger2R[i+1]]), 2, Color);
            DrawLine(image, Point(bonesZ[SkeletonBoneFinger3R[i]], bonesY[SkeletonBoneFinger3R[i]]), Point(bonesZ[SkeletonBoneFinger3R[i+1]], bonesY[SkeletonBoneFinger3R[i+1]]), 2, Color);
            DrawLine(image, Point(bonesZ[SkeletonBoneFinger4R[i]], bonesY[SkeletonBoneFinger4R[i]]), Point(bonesZ[SkeletonBoneFinger4R[i+1]], bonesY[SkeletonBoneFinger4R[i+1]]), 2, Color);
            DrawLine(image, Point(bonesZ[SkeletonBoneFinger5R[i]], bonesY[SkeletonBoneFinger5R[i]]), Point(bonesZ[SkeletonBoneFinger5R[i+1]], bonesY[SkeletonBoneFinger5R[i+1]]), 2, Color);
        }
    }

    return image;
}

// Skeleton
Mat SkeletonPlotter::DrawSkeletonOnPhoto(Mat image, Skeleton &skeleton)
{
    int window = 640;// * (mWidth / mHeight);//mLength * 0.8;
    int i, length;

    float bonesX[66], bonesY[66]; //, bonesZ[66];

    for (i = 0; i < 66; i++)
    {
        auto bones = skeleton.GetBone(i);
        if (mEngineName == "unreal")
        {
            bonesX[i] = bones[0] * mWidth;// * (mWidth / mHeight);
            bonesY[i] = -(bones[2] - 1) * mWidth;// * (mWidth / mHeight);
        }
        else if (mEngineName == "unity")
        {
            bonesX[i] = bones[0] * mWidth;// * (mWidth / mHeight);
            bonesY[i] = -bones[1] * mWidth;// * (mWidth / mHeight);
        }
        else if (mEngineName == "mediapipe")
        {
            bonesX[i] = bones[0] * mWidth;// * (mWidth / mHeight);
            bonesY[i] = bones[1] * mWidth;// * (mWidth / mHeight);
        }

//        printf("%d, x=%3.4f, y=%3.4f, z=%3.4f \n", i, bonesX[i], bonesY[i], bonesZ[i]);
        circle(image, Point(bonesX[i], bonesY[i]), 1, BGR_RED, -1);
    }

    // Body
    length = sizeof(SkeletonBoneR) / sizeof(SkeletonBoneR[0]);
    for (i = 0; i < length - 1; i++)
    {
        Scalar Color;
        if (i < 2) { Color = BGR_GRAY; }
        else if (i < 3) { Color = BGR_BLUE; }
        else { Color = BGR_ORANGE; }

        DrawLine(image, Point(bonesX[SkeletonBoneR[i]], bonesY[SkeletonBoneR[i]]), Point(bonesX[SkeletonBoneR[i+1]], bonesY[SkeletonBoneR[i+1]]), 2, Color);
        DrawLine(image, Point(bonesX[SkeletonBoneL[i]], bonesY[SkeletonBoneL[i]]), Point(bonesX[SkeletonBoneL[i+1]], bonesY[SkeletonBoneL[i+1]]), 2, Color);
    }

    // Hand
    length = sizeof(SkeletonBoneFinger1R) / sizeof(SkeletonBoneFinger1R[0]);
    for (i = 0; i < length - 1; i++)
    {
        Scalar Color;
        if (i < 2) { Color = BGR_GRAY; }
        else if (i < 3) { Color = BGR_BLUE; }
        else { Color = BGR_ORANGE; }

        DrawLine(image, Point(bonesX[SkeletonBoneFinger1R[i]], bonesY[SkeletonBoneFinger1R[i]]), Point(bonesX[SkeletonBoneFinger1R[i+1]], bonesY[SkeletonBoneFinger1R[i+1]]), 2, Color);
        DrawLine(image, Point(bonesX[SkeletonBoneFinger1L[i]], bonesY[SkeletonBoneFinger1L[i]]), Point(bonesX[SkeletonBoneFinger1L[i+1]], bonesY[SkeletonBoneFinger1L[i+1]]), 2, Color);

        DrawLine(image, Point(bonesX[SkeletonBoneFinger2R[i]], bonesY[SkeletonBoneFinger2R[i]]), Point(bonesX[SkeletonBoneFinger2R[i+1]], bonesY[SkeletonBoneFinger2R[i+1]]), 2, Color);
        DrawLine(image, Point(bonesX[SkeletonBoneFinger2L[i]], bonesY[SkeletonBoneFinger2L[i]]), Point(bonesX[SkeletonBoneFinger2L[i+1]], bonesY[SkeletonBoneFinger2L[i+1]]), 2, Color);

        DrawLine(image, Point(bonesX[SkeletonBoneFinger3R[i]], bonesY[SkeletonBoneFinger3R[i]]), Point(bonesX[SkeletonBoneFinger3R[i+1]], bonesY[SkeletonBoneFinger3R[i+1]]), 2, Color);
        DrawLine(image, Point(bonesX[SkeletonBoneFinger3L[i]], bonesY[SkeletonBoneFinger3L[i]]), Point(bonesX[SkeletonBoneFinger3L[i+1]], bonesY[SkeletonBoneFinger3L[i+1]]), 2, Color);

        DrawLine(image, Point(bonesX[SkeletonBoneFinger4R[i]], bonesY[SkeletonBoneFinger4R[i]]), Point(bonesX[SkeletonBoneFinger4R[i+1]], bonesY[SkeletonBoneFinger4R[i+1]]), 2, Color);
        DrawLine(image, Point(bonesX[SkeletonBoneFinger4L[i]], bonesY[SkeletonBoneFinger4L[i]]), Point(bonesX[SkeletonBoneFinger4L[i+1]], bonesY[SkeletonBoneFinger4L[i+1]]), 2, Color);

        DrawLine(image, Point(bonesX[SkeletonBoneFinger5R[i]], bonesY[SkeletonBoneFinger5R[i]]), Point(bonesX[SkeletonBoneFinger5R[i+1]], bonesY[SkeletonBoneFinger5R[i+1]]), 2, Color);
        DrawLine(image, Point(bonesX[SkeletonBoneFinger5L[i]], bonesY[SkeletonBoneFinger5L[i]]), Point(bonesX[SkeletonBoneFinger5L[i+1]], bonesY[SkeletonBoneFinger5L[i+1]]), 2, Color);

    }

    return image;
}
