#pragma once

#include <iostream> 
#include <iomanip>
#include <sstream> 
#include <string>
#include <vector>
#include <time.h>
#include <math.h>

#include <opencv2/opencv.hpp>

#include "Holistic.hpp"
#include "SkelConverter/Skeleton.hpp"

using namespace std;
using namespace cv;

class SkeletonPlotter
{
    public:
        SkeletonPlotter();
        ~SkeletonPlotter();

        // Setting
        void SetImageSize(int Width, int Height);
        void SetAxesSize(int length);
        void SetEngineName(string engineName);

        void SetAxesLabelHor(string label);
        void SetAxesMaximumHor(float value);
        void SetAxesMinimumHor(float value);

        void SetAxesLabelVer(string label);
        void SetAxesMaximumVer(float value);
        void SetAxesMinimumVer(float value);

        Mat DrawAxes(void);
        Mat DrawHolistic(Mat image, Holistic &holistic);
        Mat DrawLine(Mat image, Point a, Point b, int thickness, Scalar RGB);
        
        // Mediapipe three-view
        Mat DrawHolisticFrontView(Mat image, Holistic &holistic);
        Mat DrawHolisticTopView(Mat image, Holistic &holistic);
        Mat DrawHolisticSideView(Mat image, Holistic &holistic);

        // Skeleton three-view
        Mat DrawFrontView(Mat image, Skeleton &skeleton);
        Mat DrawTopView(Mat image, Skeleton &skeleton);
        Mat DrawSideView(Mat image, Skeleton &skeleton);

        // Face and Skeleton three-view
        Mat DrawFacemeshFrontView(Mat image, Skeleton &skeleton, Holistic &holistic);
        Mat DrawFacemeshTopView(Mat image, Skeleton &skeleton, Holistic &holistic);
        Mat DrawFacemeshSideView(Mat image, Skeleton &skeleton, Holistic &holistic);

        Mat DrawSkeletonOnPhoto(Mat image, Skeleton &skeleton);

    private:
        Scalar BGR_RED = Scalar(0, 0, 255);
        Scalar BGR_GREEN = Scalar(0, 255, 0);
        Scalar BGR_BLUE = Scalar(255, 0, 0);
        Scalar BGR_BLACK = Scalar(0, 0, 0);
        Scalar BGR_WHITE = Scalar(255, 255, 255);
        Scalar BGR_GRAY = Scalar(128, 128, 128);
        Scalar BGR_SLIVER = Scalar(192, 192, 192);
        Scalar BGR_ORANGE = Scalar(40, 123, 255);
        Scalar BGR_YELLOW = Scalar(0, 255, 255);

        int mWidth, mHeight, mLength;
        string mEngineName, mLabelHor, mLabelVer;
        float mMaximumHor, mMinimumHor, mMaximumVer, mMinimumVer;
        float mRatioX, mRatioY;
        
        int BodyCircleMapR[7] = {15, 13, 11, 23, 25, 27, 29};
        int BodyCircleMapL[7] = {16, 14, 12, 24, 26, 28, 30};
        int BodyLineMapR[9] = {15, 13, 11, 23, 25, 27, 29, 31, 27};
        int BodyLineMapL[9] = {16, 14, 12, 24, 26, 28, 30, 32, 28};

        int SkeletonBoneR[12] = {0};
        int SkeletonBoneFinger1R[5] = {0};        
        int SkeletonBoneFinger2R[5] = {0};        
        int SkeletonBoneFinger3R[5] = {0};        
        int SkeletonBoneFinger4R[5] = {0};        
        int SkeletonBoneFinger5R[5] = {0};        

        int SkeletonBoneL[12] = {0};
        int SkeletonBoneFinger1L[5] = {0};        
        int SkeletonBoneFinger2L[5] = {0};        
        int SkeletonBoneFinger3L[5] = {0};        
        int SkeletonBoneFinger4L[5] = {0};        
        int SkeletonBoneFinger5L[5] = {0};        
};
