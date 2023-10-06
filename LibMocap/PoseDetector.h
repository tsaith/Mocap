#pragma once

#include "Core/Core.h"
#include "Core/VectorUtils.h"
#include "Holistic.hpp"
#include "HRNetPose/HRNetPose.h" 
#include "MHFormer/mhformer.h"
#include "PoseUtils.h"

#include "opencv2/opencv.hpp"

using namespace std;
using namespace core;
using namespace cv;
using namespace hrnet_pose;
using namespace pose_utils;

class PoseDetector { 
public:

    PoseDetector();
    ~PoseDetector();
    void Init(int ImageWidth, int ImageHeight);
    void UseGpu(bool bFlag, int GpuDeviceId);
    void LoadModel(string ModelDir);
    void Detect(Mat& Image);
    void UpdateHolisticPose(Holistic& Data);


private:

    void CorrectPose2D(Holistic& Data);
    void MapPose2DToHolistic(FVector2f& Pose2D, Holistic& Data);
    void CalculatePoseDepthWithMHFormer(Holistic& Data);

    bool mUseGpu = true;
    int mGpuDeviceId = 0;
    string mModelDir = "TrainedModels";

    int mImageWidth;
    int mImageHeight;
    cv::Mat mImage;

    FVector2f mPose2D;
    FVector2f mPose3D;

    Holistic mHolistic;
    HRNetPose mHRNetPose;
    MHFormer mMHFormer;
    float mMHFAngleAroundX = -10.0;

};
