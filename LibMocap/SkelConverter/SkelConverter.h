#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Core/Core.h"
#include "HolisticCorrection.h"
#include "SkeletonFactory.h"

static const double Radian2Angle = 57.29577951308232087684;

using namespace std;
using namespace cv;


class SkelConverter {
public:

    SkelConverter();
    ~SkelConverter();

    void Init(int ImageWidth, int ImageHeight);
    void Process(Holistic& Data);
    void PostProcess();
    bool IsShortDistance();
    void Calibrate();
    void Calibrate(float ShoulderWidthPhys);
    void CreateDataForCalibration(void);

    void ConvertPointNormToPhys(float* PointNorm, float* PointPhys);
    void SetEngineName(string name);
    
    float GetDepth(void);
    //Holistic GetHolisticMP(void);
    Holistic GetHolistic(void);
    Skeleton GetSkeleton(void);
    Skeleton GetSkeletonCali(void);
    Skeleton GetSkeletonPhys(void);
    //Gesture GetGesture(void);

    int GetLeftEye(void);
    int GetRightEye(void);

    bool HasPose();
    bool HasFacemesh();
    bool HasLeftHand();
    bool HasRightHand();

    bool IsLeftHandStable();
    bool IsRightHandStable();

    void GetLeftPalmDirection(float *Dvec);
    void GetRightPalmDirection(float *Dvec);

    // Physics space
    void SetShoulderWidthPhys(float value);
    void GetRootPhys(float *Point, float* PointCali);
    void GetPelvisPhys(float *Point, float* PointCali);
    void GetPhysDelta(float *RootPoint, float* PelvisPoint);
    

    // Methods to set parameters
    void SetOneEuroParams(bool IsOn, float Frequency, float Mincutoff, float Beta, float Dcutoff);
    void SetBoneStabilizerParams(bool IsOn, float PoseDistanceC, float HandDistanceC, float FacemeshDistanceC);
    void SetHeadRotationParams(double RotationValue);

    // APIs of bones and quaternions
    const int GetNumBones();
    const int GetBoneDims();
    const int GetQuatDims();
    float* GetBone(int i);
    float* GetQuat(int i);

    const int GetMpPoseNumBones();
    float* GetMpPoseBone(int i);

private:

    // Image
    int mImageWidth;
    int mImageHeight;

    // Correct raw data for Mediapipe
    HolisticCorrection *mCorrection = NULL;

    // Skeleton
    SkeletonFactory mSkeletonFactory;

    // Gestures
    //gd::GestureDetector mLeftGestureDetector;
    //gd::GestureDetector mRightGestureDetector;

    //string mEngineName = "mediapipe"; // Name of game engine;
    string mEngineName = "unreal"; // Name of game engine;
    int mError;
    float mDepth;
    //Holistic mHolisticMP;   // Mediapipe holistic raw data
    Holistic mHolistic;     // Corrected holistic raw data
    Skeleton mSkeleton;     // Skeleton
    //Gesture mGesture;       // Gesture data

    int mLeftBlinkEye = 0;
    int mRightBlinkEye = 0;

    // Calibration
    bool mDoCreateDataForCalibration = false;

    // Physics space
    Skeleton mSkeletonCali; // Skeleton of calibrationn
    Skeleton mSkeletonPhys; // Skeleton in physics space

    float mRootPhys[3];
    float mRootCaliPhys[3];
    float mPelvisPhys[3];
    float mPelvisCaliPhys[3];
    float mRootPhysDelta[3];
    float mPelvisPhysDelta[3];

    // User is close to camera or not
    bool mIsShortDistance = false;
    double mRotationValue = 0.8;
};    

