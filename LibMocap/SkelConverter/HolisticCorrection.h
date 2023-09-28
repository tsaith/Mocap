#pragma once

#include <iostream>
#include <cmath>

#include "Core/Math/MathLib.h"
#include "Core/Math/Kalman1d.hpp"
#include "Utils/Timer.hpp"
#include "BoneStabilizer.hpp"
#include "OneEuroFilter.hpp"
#include "Holistic.hpp"
#include "Calibration.hpp"
#include "HeadStabilizer.h"
#include "HandStabilizer.h"
#include "Utils/DebugUtils.h"

using namespace zen_math;
using namespace db_utils;

class HolisticCorrection {

public:

    HolisticCorrection();
    ~HolisticCorrection();

    bool Init(int ImageWidth, int ImageHeight);
    void Preprocess();
    void ApplyFilterOnBones();
    void StabilizeBones();
    void SetImageWidth(int width);
    void SetImageHeight(int height);
    void ToPixelSpace(float* PointOut, float* PointIn);
    void ToNormalizedSpace(float* PointOut, float* PointIn);

    void GuessOccludedPoints();
    float EstimateHeadWidth();
    float EstimateShoulderWidth();
    float EstimateTrunkHeight();
    float EstimateFaceHeight();
    float EstimateSpineLength();
    void EstimateCenterShoulder(float* Center);
    void EstimateCenterHips(float* Center);
    float EstimateArmLength();
    float EstimateLegLength();
    void EstimateCenterHead(float* Center);
    void EstimateTargetZ(float* PointTarget, float* PointRoot,
        float length, float sign);
    void EstimateUncertainPoints(float LenU, float LenL, 
        float* PointRoot, float* PointMiddle, float* PointTip);
    void EstimateFaceDirection(float* VecD);
    void EstimateTrunkDirection(float* VecD);

    void CorrectPoseHead();
    void CorrectPoseShoulder(bool IsRight);
    void CorrectPoseArm(bool IsRight);
    //void CorrectPoseArm_Ellipse(bool IsRight);
    void CorrectPoseLeg(bool IsRight);
    void CorrectPoseFoot(bool IsRight);

    void CorrectFacemesh();
    void CorrectLeftHand();
    void CorrectRightHand();
    void ToCustomizedHolistic();
    void UpdatePosePrev();

    Holistic Process(Holistic &Data);

    void Calibrate(Holistic &Data);
    void SetIsCalibrated(bool Status);
    bool IsCalibrated();
    bool IsFrontFace();
    bool DoesBendOver();
    float EstimateLength(float* p1, float* p2);
    float EstimateDepth();

    float GetDepth();

    void ToPoint(float point[3], float x, float y, float z);
    void EstimateCenterFromTwoPoints(float* center, float* p1, float* p2);

    float* GetFaceDirection();
    float* GetTrunkDirection();

    bool HasPose();
    bool HasFacemesh();
    bool HasLeftHand();
    bool HasRightHand();

    bool IsShortDistance();

    void SetShoulderWidthPhys(float Value);
    float GetRatioPhysToPixel();

    // Methods to set parameters
    void SetImageWidth(float Width);
    void SetImageHeight(float Height);
    void SetOneEuroParams(bool IsOn, float Frequency, float Mincutoff, float Beta, float Dcutoff);
    void SetBoneStabilizerParams(bool IsOn, float PoseDistanceC, float HandDistanceC, float FacemeshDistanceC);


private:

    static constexpr int POSE_LANDMARK_NUM = 33;
    static constexpr int HAND_LANDMARK_NUM = 21;
    static constexpr int FACEMESH_LANDMARK_NUM = 468;

    int mImageWidth;
    int mImageHeight;
    Holistic mData; // Holistic data
    Holistic mDataMP; // Mediapipe holistic data
    Holistic mDataPrev; // Previous holistic data

    float mVisibilityThreshold = 0.6;
    bool mIsCalibrated = false;

    float mFaceHeight;
    float mHeadWidth;
    float mShoulderWidth;
    float mTrunkHeight;
    float mArmLength;
    float mLegLength;
    float mSpineLength;

    float mRatioArmFace = 2.2; // Ratio of arm to shoulder
    float mRatioLegFace = 3.2; // Ratio of leg to shoulder
    float mRatioArmTrunk = 0.85; // Ratio of arm to shoulder
    float mRatioLegTrunk = 1.0; // Ratio of leg to shoulder
    float mRatioArmShoulder = 1.3; // Ratio of arm to shoulder
    float mRatioLegShoulder = 1.3; // Ratio of leg to shoulder

    float mUpperArmRatio = 0.5;
    float mLowerArmRatio = 0.5;

    float mUpperArmLength;
    float mLowerArmLength;

    float mUpperLegRatio = 0.5;
    float mLowerLegRatio = 0.5;

    float mUpperLegLength;
    float mLowerLegLength;

    float mCenterShoulder;

    Calibration mCalibration;

    float mDepth = 0; // The depth from camera to trunk.
    float mDepthPrev = 0;

    // Kalman filter
    Kalman1d mPoseKalman[POSE_LANDMARK_NUM][3];
    Kalman1d mLeftHandKalman[HAND_LANDMARK_NUM][3];
    Kalman1d mRightHandKalman[HAND_LANDMARK_NUM][3];
    Kalman1d mFacemeshKalman[FACEMESH_LANDMARK_NUM][3];
    Kalman1d mDepthKalman;

    // Bone stabilizer
    BoneStabilizer mPoseStabilizer[POSE_LANDMARK_NUM];
    BoneStabilizer mLeftFingersStabilizer[HAND_LANDMARK_NUM];
    BoneStabilizer mRightFingersStabilizer[HAND_LANDMARK_NUM];
    BoneStabilizer mFacemeshStabilizer[FACEMESH_LANDMARK_NUM];

    // One Euro filter
    one_euro::OneEuroFilter mPoseOneEuro[POSE_LANDMARK_NUM][3];
    one_euro::OneEuroFilter mLeftHandOneEuro[HAND_LANDMARK_NUM][3];
    one_euro::OneEuroFilter mRightHandOneEuro[HAND_LANDMARK_NUM][3];
    one_euro::OneEuroFilter mFacemeshOneEuro[FACEMESH_LANDMARK_NUM][3];

    float mFaceDirection[3];
    float mTrunkDirection[3];

    // Hand status 
    bool mHasPose = true; 
    bool mHasFacemesh = true; 
    bool mHasLeftHand = true; 
    bool mHasRightHand = true; 

    HeadStabilizer mHeadStabilizer;

    HandStabilizer mLeftHandStabilizer;
    HandStabilizer mRightHandStabilizer;

    // Parameters of One Euro filter
    bool mOneEuroIsOn = true;
    float mOneEuroFrequency = 18.0;
    float mOneEuroMincutoff = 1.0;
    float mOneEuroBeta = 10.0;
    float mOneEuroDcutoff = 1.0;

    // Parameters of bone stabilizer
    bool mBoneStabilizerIsOn = true;
    float mBoneStabilizerPoseDistanceC = 2.0e-3;
    float mBoneStabilizerHandDistanceC = 2.0e-3;
    float mBoneStabilizerFacemeshDistanceC = 2.0e-3;


    Timer mFilterTimer;

};

