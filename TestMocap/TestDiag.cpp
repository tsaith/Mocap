#include "pch.h"

#include "TestDiag.h"

namespace test_diag {

    TestDiag::TestDiag()
    {

        mPoseLandmarks = InitVector2f(mNumPoseLandmarks, 4);

    }

    TestDiag::~TestDiag()
    {
    }

    void TestDiag::Init(int ImageWidth, int ImageHeight)
    {
        mImageWidth = ImageWidth;
        mImageHeight = ImageHeight;
    }

    void TestDiag::SetInputImage(cv::Mat& Image)
    {
        mInputImage = Image.clone();
    }

    void TestDiag::SetFps(float Fps)
    {
        mFps = Fps;
    }

    void TestDiag::Process()
    {

        mDiagImage = mInputImage.clone();


        // Write message 
        mTextPlotter.ResetPosition();

        string  msg;
        msg = "fps: " + to_string(int(mFps + 0.5));
        mTextPlotter.putText(mDiagImage, msg);

    }

    cv::Mat TestDiag::GetDiagImage()
    {
        return mDiagImage;
    }


} // Namespace
