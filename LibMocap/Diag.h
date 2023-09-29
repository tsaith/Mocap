#pragma once

#include <opencv2/opencv.hpp>

#include "Core/Core.h"
#include "Utils/PlotLib.h"
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
	    void SetSkeleton(
            FVector2f& Quats,
            FVector2f& Bones);

	    void Process();

        cv::Mat GetDiagImage();
        cv::Mat GetSkelImage();


    private:

        vector<int> GetPoseIndexes(); 
        FVector2i GetPoseConnect(); 
        vector<int> GetMpPoseIndexes(); 
        FVector2i GetMpPoseConnect(); 
        vector<int> GetSkelIndexes(); 
        FVector2i GetSkelConnect();
        vector<int> GetSkelPoseIndexes(); 
        FVector2i GetSkelPoseConnect();
        void GetBone2D(float& Out1, float& Out2,
             vector<float> Bone, int IntFlag);
        void PlotPoseLandmarks(Mat& Image, FVector2f& Landmarks);
        void PlotPoseLandmarksCore(axes_handle& Ax,
            FVector2f& Landmarks, int ViewFlag);
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
