#pragma once

#include "Core/Core.h"
#include "TextPlotter.hpp" 


//using namespace std;
using namespace core;

namespace test_diag {


    class TestDiag {

    public:

        TestDiag();
        ~TestDiag();

        void Init(int ImageWidth, int ImageHeight);

        void SetInputImage(cv::Mat& Image);
        void SetFps(float Fps);

	    void Process();

        cv::Mat GetDiagImage();


    private:

        int mImageWidth = 1280;
        int mImageHeight = 720;

        int mNumPoseLandmarks = 33;
        FVector2f mPoseLandmarks;

        int mNumSkelKeypoints = 68;
        FVector2f mSkelQuats;
        FVector2f mSkelBones;

        cv::Mat mInputImage;
        cv::Mat mSkelImage;
        cv::Mat mDiagImage;

        TextPlotter mTextPlotter;

        float mFps = 0.0f;

    };

}
