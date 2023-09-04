#pragma once

#include "TextPlotter.hpp" 

typedef vector<vector<float>> FVector2f;
typedef vector<vector<int>> FVector2i;

using namespace std;

namespace dg {


    class Diag {

    public:

        Diag();
        ~Diag();

        void Init(int ImageWidth, int ImageHeight);

        void SetInputImage(cv::Mat& Image);
        void SetFps(float Fps);
	    void SetSkeleton(
            FVector2f& Quats,
            FVector2f& Bones);

	    void Process();

        cv::Mat GetDiagImage();
        cv::Mat GetSkelImage();


    private:

        vector<int> GetPoseIndexes(); 
        vector<vector<int>> GetPoseConnect();
        void GetBone2D(float& Out1, float& Out2,
             vector<float> Bone, int IntFlag);
        void PlotPose2D(cv::Mat& Image,
            FVector2f& SkelBones, int IntFlag);
        cv::Mat CombineImages2x2(cv::Mat& Img1, cv::Mat& Img2,
            cv::Mat& Img3, cv::Mat& Img4, cv::Size SizeOut);
        FVector2f ToPixelSpace(FVector2f& SkelBones, int Width, int Height);


        int mImageWidth = 1280;
        int mImageHeight = 720;

        int mNumSkelKeypoints = 68;
        FVector2f mSkelQuats;
        FVector2f mSkelBones;

        cv::Mat mInputImage;
        cv::Mat mSkelImage;
        cv::Mat mDiagImage;

        TextPlotter mTextPlotter;

        float mFps = 0.0f;

        vector<int> mPoseIndexes;
        vector<vector<int>> mPoseConnet;
        //FVector2i mPoseConnet;
        //vector<int> mPoseIndexes = GetPoseIndexes();
        //FVector2i mPoseConnet = GetPoseConnect();


    };

}
