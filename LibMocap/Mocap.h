#pragma once

#include <vector>
#include <string>
#include <iostream> 
#include <thread> 
#include <mutex>

#include "Core/Core.h"
#include "Core/VectorUtils.h"
#include "FacialExpression/FacialExpression.h" 
#include "PoseDetector.h"
#include "HRNetPose/HRNetPose.h" 
#include "MHFormer/mhformer.h"
#include "PoseUtils.h"
#include "Holistic.hpp"
#include "SkelConverter/SkelConverter.h"

#include "Diag.h"

#include "opencv2/opencv.hpp"

using namespace std;
using namespace core;
using namespace hrnet_pose;
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

    void FaceDetect(Mat& Image);
    FTransform MakeTransform(FQuat Rotation, FVector Translation);
    void CopyArray2D(float* Src, float* Dest, int Rows, int Cols);
    void UpdateHolisticHands(Holistic& Data);
    Holistic ReNormalizeHolistic(Holistic& Data); 
    void CorrectHolistic(Holistic& Data);

    bool mUseGpu = true;
    int mGpuDeviceId = 0;

    int mImageWidth;
    int mImageHeight;
    Mat mImage;


    FacialExpression mFacialExpression;
    const int mNumBlendshapes = 52;
    vector<float> mBlendshapes;
    FTransform mHeadTransform;
    
    bool mHasLeftHand;
    bool mHasRightHand;

    const int mNumBones = 68;
    vector<FTransform> mSkelTransforms;

    Holistic mHolistic;
    Holistic mHolisticReNorm;

    FVector2f mPose;

    PoseDetector mPoseDetector;
    SkelConverter mSkelConverter;

    // Diagnostics
    bool mIsDiag = true;
    Diag mDiag;

    // Counter
    int mCounter = 0;
    int mCounterMax = 1000000;

};
