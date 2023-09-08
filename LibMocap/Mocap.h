#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "Core.h"
#include "MHFormer/mhformer.h"
#include "PoseUtils.h"
#include "SkelConverter/holistic.hpp"
#include "SkelConverter/SkelConverter.h"

#include "Diag.h"

#include "opencv2/opencv.hpp"

using namespace std;
using namespace pose_utils;
using namespace diag;

class Mocap { 
public:

    Mocap();
    ~Mocap();
    void Init(int ImageWidth, int ImageHeight);
    void Detect(Mat& Image);
    void Diagnose();
    bool IsFaceDetected();
    vector<float> GetBlendshapes();
    FTransform GetHeadTransform();
    vector<FTransform> GetSkelTransforms();
    FTransform GetSkelTransform(int Index);

private:

    FTransform MakeTransform(FQuat Rotation, FVector Translation);
    void CopyArray2D(float* Src, float* Dest, int Rows, int Cols);
    void UpdateHolistic(Holistic& Data);
    void RefinePoseDepthWithMHFormer(Holistic& Data);

    int mImageWidth;
    int mImageHeight;
    Mat mImage;


    bool mIsFaceDetected = false;
    const int mNumBlendshapes = 52;
    vector<float> mBlendshapes;
    FTransform mHeadTransform;

    const int mNumBones = 68;
    vector<FTransform> mSkelTransforms;

    Holistic mHolistic;

    MHFormer mMHFormer;

    SkelConverter mSkelConverter;

    // Diagnostics
    bool mIsDiag = true;
    Diag mDiag;
};
