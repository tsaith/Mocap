#pragma once

#include <opencv2/opencv.hpp>

#include "Core/Core.h"
#include "Plot/CvPlot.h"
#include "Plot/PlotLib.h"
#include "Utils/TextPlotter.hpp" 


namespace diag {

    using namespace core;
    using namespace cv;
    using namespace plotlib;

    class Diag {

    public:

        Diag();
        ~Diag();

        void Init(int ImageWidth, int ImageHeight);

        void SetInputImage(cv::Mat& Image);
        void SetFps(float Fps);
        void SetPoseLandmarks(FVector2f& PoseLandmarks);
        void SetHandLandmarks(FVector2f& LeftHnadLandmarks, FVector2f& RightHnadLandmarks);
	    void SetSkeleton(
            FVector2f& Quats,
            FVector2f& Bones);

	    void Process();

        cv::Mat GetDiagImage();
        cv::Mat GetSkelImage();


    private:

        vector<int> GetPoseIndexes(); 
        FVector2i GetPoseConnect(); 
        vector<int> GetHandIndexes(); 
        FVector2i GetHandConnect(); 
        vector<int> GetMpPoseIndexes(); 
        FVector2i GetMpPoseConnect(); 
        vector<int> GetSkelIndexes(); 
        FVector2i GetSkelConnect();
        vector<int> GetSkelLeftHandIndexes(); 
        FVector2i GetSkelLeftHandConnect();
        vector<int> GetSkelRightHandIndexes(); 
        FVector2i GetSkelRightHandConnect();
        vector<int> GetSkelPoseIndexes(); 
        FVector2i GetSkelPoseConnect();
        void GetBone2D(float& Out1, float& Out2,
             vector<float> Bone, int IntFlag);
        void PlotLandmarks(Mat& Image, FVector2f& Pose,
            FVector2f& LeftHand, FVector2f& RightHand);
        void PlotLandmarksCore(axes_handle& Ax, FVector2f& Pose,
            FVector2f& LeftHand, FVector2f& RightHand, int ViewFlag);
        void PlotSkelBones(Mat& Image, FVector2f& Bones);
        void PlotSkelBonesCore(axes_handle& Ax,
            FVector2f& Bones, int ViewFlag);
        FVector2f ToPixelSpace(FVector2f& SkelBones, int Width, int Height);

        int mImageWidth = 1280;
        int mImageHeight = 720;

        int mDiagImageWidth = 1280;
        int mDiagImageHeight = 720;

        int mNumPoseLandmarks = 33;
        FVector2f mPoseLandmarks;

        int mNumHandLandmarks = 21;
        FVector2f mLeftHandLandmarks;
        FVector2f mRightHandLandmarks;

        int mNumSkelKeypoints = 68;
        FVector2f mSkelQuats;
        FVector2f mSkelBones;

        cv::Mat mInputImage;
        cv::Mat mDiagImage;
        cv::Mat mPoseImage;
        cv::Mat mSkelImage;

        TextPlotter mTextPlotter;

        float mFps = 0.0f;

        vector<int> mSkelPoseIndexes;
        FVector2i mSkelPoseConnet;
        //FVector2i mPoseConnet;
        //vector<int> mPoseIndexes = GetPoseIndexes();
        //FVector2i mPoseConnet = GetPoseConnect();


    };

}
