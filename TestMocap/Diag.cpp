#include "pch.h"

#include "Diag.h"

namespace dg {

    Diag::Diag()
    {
    }

    Diag::~Diag()
    {
    }

    void Diag::Init(int ImageWidth, int ImageHeight)
    {
        mImageWidth = ImageWidth;
        mImageHeight = ImageHeight;
    }

    void Diag::Process()
    {
        //textPlotter.ResetPosition();
        //msg = "fps: " + to_string(int(fps));
        //textPlotter.putText(frame, msg);

    }

    void Diag::SetSkeleton(vector<vector<float>>& Quats,
            vector<vector<float>>& Bones)
    {

    }

    void Diag::SetInputImage(Mat& Image)
    {
        mInputImage = Image.clone();
    }

    Mat Diag::GetDiagImage()
    {
        return mDiagImage;
    }

    Mat Diag::GetSkelImage()
    {
        return mSkelImage;
    }


}
