#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "TypeDef.h"
#include "PoseUtils.h"
#include "MHFormer/mhformer.h"
#include "SkelConverter/holistic.hpp"
#include "SkelConverter/SkelConverter.h"


#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;
using namespace pose_utils;

class Mocap {
public:

    Mocap();
    ~Mocap();
    void Init(int ImageWidth, int ImageHeight);
    void Detect(Mat& Image);
    bool IsFaceDetected();
    vector<float> GetBlendshapes();
    FTransform GetHeadTransform();
    FTransform GetSkelTransform(int Index);

private:

    FTransform MakeTransform(FQuat Rotation, FVector Translation);
    void CopyArray2D(float* Src, float* Dest, int Rows, int Cols);
    void UpdateHolistic(Holistic& Data);
    void RefinePoseDepthWithMHFormer(Holistic& Data);

    int mImageWidth;
    int mImageHeight;

    bool mIsFaceDetected = false;
    const int mNumBlendshapes = 52;
    vector<float> mBlendshapes;
    FTransform mHeadTransform;

    const int mNumBones = 68;
    vector<FTransform> mSkelTransforms;

    Holistic mHolistic;

    MHFormer mMHFormer;

    SkelConverter mSkelConverter;

};
