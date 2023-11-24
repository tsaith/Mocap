#pragma once

#include <iostream>
#include <string>

#include "Core/Math/MathLib.h"
#include "Utils/DebugUtils.h"
#include "Skel/BoneStabilizer.hpp"
#include "Skel/QuatStabilizer.hpp"
#include "holistic.hpp"
#include "skeleton.hpp"
#include "QuatSmoother.h"

using namespace std;
using namespace zen_math;
using namespace db_utils;

class SkeletonFactory {

public:

    SkeletonFactory();
    ~SkeletonFactory();

    void Preprocess(Holistic &data, bool IsShortDistance);
    void EstimateMpBones();
    void StabilizeMpBones();
    void EstimateQuat(int boneIndex, float* dvec1Init, float* dvec2Init);
    void EstimateQuatWithRowOnly(int boneIndex, float* dvec2Init);
    void EstimateQuatWithoutRow(int boneIndex, float* dvec1Init);
    void EstimateMpQuats(Holistic &data);
    void ConfineMpQuats();
    void ToUnrealSkeleton();
    void ToUnitySkeleton();
    void ToUnrealAxes(float* p);
    void ToUnrealQuat(float* q);
    void ToUnrealDirection(float* Dvec);
    void ToUnityAxes(float* p);
    void ToUnityQuat(float* q);
    void ToUnityDirection(float* Dvec);
    void Produce(Holistic &data , Skeleton* pSkel);
    void SetIsShortDistance(bool Value);
    bool IsShortDistance();

    void DebugBoneRotation(int boneIndex, float* dvec1Init, float* dvec2Init);
    void DebugBonePosition(Skeleton* pSkel);
    void LoadImageSize(float w , float h);
    void SetWeightingFactor(double s);
private:

    void EstimateSkeletonTarget(float* target, float* base, float length,
        float* TargetPose, float* BasePose);

    static const int mNumBones = 68;
    static const int mDims = 3;
    static const int mQuatDims = 4;

    Skeleton* mSkelP;
    Skeleton mPose;

    // Quat smoothers 
    static const int mNumFingers = 5;
    static const int mNumFingerJoints = 4;

    QuatSmoother mLeftHandQuatSmoother;
    QuatSmoother mRightHandQuatSmoother;
    QuatSmoother mLeftFingerSmoothers[mNumFingers][mNumFingerJoints-1];
    QuatSmoother mRightFingerSmoothers[mNumFingers][mNumFingerJoints-1];

    // Bone stabilizers
    /*
    BoneStabilizer mPelvisStabilizer;
    BoneStabilizer mSpine01Stabilizer;
    BoneStabilizer mSpine02Stabilizer;
    BoneStabilizer mSpine03Stabilizer;
    BoneStabilizer mNeckStabilizer;
    BoneStabilizer mHeadStabilizer;
    BoneStabilizer mEarLStabilizer;
    BoneStabilizer mEarRStabilizer;
    BoneStabilizer mNoseStabilizer;

    BoneStabilizer mClavicleLStabilizer;
    BoneStabilizer mClavicleRStabilizer;
    BoneStabilizer mUpperarmLStabilizer;
    BoneStabilizer mUpperarmRStabilizer;
    BoneStabilizer mLowerarmLStabilizer;
    BoneStabilizer mLowerarmRStabilizer;
    BoneStabilizer mHandLStabilizer;
    BoneStabilizer mHandRStabilizer;

    BoneStabilizer mThighLStabilizer;
    BoneStabilizer mThighRStabilizer;
    BoneStabilizer mCalfLStabilizer;
    BoneStabilizer mCalfRStabilizer;
    BoneStabilizer mFootLStabilizer;
    BoneStabilizer mFootRStabilizer;
    BoneStabilizer mBallLStabilizer;
    BoneStabilizer mBallRStabilizer;
    */

    // Quat Stabilizer
    //QuatStabilizer mHeadQuatStabilizer;


    // User is close to camera or not
    bool mIsShortDistance = false;

    //The para for weighted head pose
    float Iwidth ;
    float Iheight ;
    float S_Threshold ;
};

