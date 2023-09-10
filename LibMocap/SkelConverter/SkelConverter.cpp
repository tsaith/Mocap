#include "pch.h"

#include "SkelConverter.h"

SkelConverter::SkelConverter() { 

    mCorrection = new HolisticCorrection(); 
} 

SkelConverter::~SkelConverter() {
    delete mCorrection;
}

void SkelConverter::Init(int ImageWidth, int ImageHeight) {

    mImageWidth = ImageWidth;
    mImageWidth = ImageWidth;

    mCorrection->Init(ImageWidth, ImageHeight);

}

void SkelConverter::PostProcess() {

        mHolistic = mCorrection->Process(mHolisticMP);
        mDepth = mCorrection->GetDepth();
        mIsShortDistance = mCorrection->IsShortDistance();

        // Skeleton
        mSkeletonFactory.Preprocess(mHolistic, mIsShortDistance);
        mSkeletonFactory.Produce(mHolisticMP , &mSkeleton);

        // Data for calibration 
        CreateDataForCalibration();

        // Facemesh
        float HeadAngle = mSkeleton.GetHeadDeviationAngle() * Radian2Angle;

        /*
        // Left gestures
        mLeftGestureDetector.Detect(mHolistic.LeftHand, mHolistic.HasLeftHand);

        mGesture.LeftStaticGesture = mLeftGestureDetector.GetStaticGesture();
        mGesture.LeftStaticGestureIdx = mLeftGestureDetector.GetStaticGestureIndex();
        mGesture.LeftDynamicGesture = mLeftGestureDetector.GetDynamicGesture();
        mGesture.LeftDynamicGestureIdx = mLeftGestureDetector.GetDynamicGestureIndex();

        mRightGestureDetector.Detect(mHolistic.RightHand, mHolistic.HasRightHand);
        mRightGestureDetector.Detect(mHolistic.RightHand);

        mGesture.RightStaticGesture =  mRightGestureDetector.GetStaticGesture();
        mGesture.RightStaticGestureIdx =  mRightGestureDetector.GetStaticGestureIndex();
        mGesture.RightDynamicGesture = mRightGestureDetector.GetDynamicGesture();
        mGesture.RightDynamicGestureIdx = mRightGestureDetector.GetDynamicGestureIndex();
        */
}

void SkelConverter::Process(Holistic& Data ) {

    // Holistic
    mHolisticMP = Data;

    mHolistic = mCorrection->Process(mHolisticMP);
    mDepth = mCorrection->GetDepth();
    mIsShortDistance = mCorrection->IsShortDistance();

    // Skeleton
    mSkeletonFactory.Preprocess(mHolistic, mIsShortDistance);
    mSkeletonFactory.LoadImageSize(mImageWidth , mImageHeight);
    mSkeletonFactory.SetWeightingFactor(mRotationValue);
    mSkeletonFactory.Produce(mHolisticMP , &mSkeleton);

    // Data for calibration 
    CreateDataForCalibration();

    // Facemesh
    float HeadAngle = mSkeleton.GetHeadDeviationAngle() * Radian2Angle;

    /*
    // Left gestures
    mLeftGestureDetector.Detect(mHolistic.LeftHand, mHolistic.HasLeftHand);

    mGesture.LeftStaticGesture = mLeftGestureDetector.GetStaticGesture();
    mGesture.LeftStaticGestureIdx = mLeftGestureDetector.GetStaticGestureIndex();
    mGesture.LeftDynamicGesture = mLeftGestureDetector.GetDynamicGesture();
    mGesture.LeftDynamicGestureIdx = mLeftGestureDetector.GetDynamicGestureIndex();

    // Right gestures
    mRightGestureDetector.Detect(mHolistic.RightHand, mHolistic.HasRightHand);

    mGesture.RightStaticGesture =  mRightGestureDetector.GetStaticGesture();
    mGesture.RightStaticGestureIdx =  mRightGestureDetector.GetStaticGestureIndex();
    mGesture.RightDynamicGesture = mRightGestureDetector.GetDynamicGesture();
    mGesture.RightDynamicGestureIdx = mRightGestureDetector.GetDynamicGestureIndex();
    */

}

bool SkelConverter::IsShortDistance() {
    return mIsShortDistance;
}

void SkelConverter::SetEngineName(string name) {
    mEngineName = name;
}

void SkelConverter::Calibrate() {
    mCorrection->Calibrate(mHolisticMP);
}

void SkelConverter::Calibrate(float ShoulderWidthPhys) {

    SetShoulderWidthPhys(ShoulderWidthPhys);

    mCorrection->Calibrate(mHolisticMP);

    mDoCreateDataForCalibration = true;

}

void SkelConverter::CreateDataForCalibration(void) {

    if (mDoCreateDataForCalibration) {

        mSkeletonCali = mSkeleton;
        ConvertPointNormToPhys(mSkeletonCali.GetRoot(), mRootCaliPhys);
        ConvertPointNormToPhys(mSkeletonCali.GetPelvis(), mPelvisCaliPhys);

    }

    mDoCreateDataForCalibration = false;

}

void SkelConverter::ConvertPointNormToPhys(float* PointNorm, float* PointPhys) {
    // Convert point from nomalized space to physics space.

    float ratioPhysToPixel = mCorrection->GetRatioPhysToPixel();
    float fac = ratioPhysToPixel * mImageWidth;

    math_utils::VecMultiply(PointPhys, PointNorm, fac);

}

float SkelConverter::GetDepth(void) {
    return mDepth;
}

Holistic SkelConverter::GetHolisticMP(void) {
    return mHolisticMP;
}

Holistic SkelConverter::GetHolistic(void) {
    return mHolistic;
}

Skeleton SkelConverter::GetSkeleton(void) {
    return mSkeleton;
}

Skeleton SkelConverter::GetSkeletonCali(void) {
    return mSkeletonCali;
}

Skeleton SkelConverter::GetSkeletonPhys(void) {
    return mSkeletonPhys;
}

/*
Gesture SkelConverter::GetGesture(void) {
    return mGesture;
}
*/

int SkelConverter::GetLeftEye(void) {
    return mLeftBlinkEye;
}

int SkelConverter::GetRightEye(void) {
    return mRightBlinkEye;
}

bool SkelConverter::HasPose(void) {
    return mCorrection->HasPose();
}

bool SkelConverter::HasFacemesh(void) {
    return mCorrection->HasFacemesh();
}

bool SkelConverter::HasLeftHand(void) {
    return mCorrection->HasLeftHand();
}

bool SkelConverter::HasRightHand(void) {
    return mCorrection->HasRightHand();
}

bool SkelConverter::IsLeftHandStable(void) {
    return mHolistic.IsLeftHandStable();
}

bool SkelConverter::IsRightHandStable(void) {
    return mHolistic.IsRightHandStable();
}

void SkelConverter::GetLeftPalmDirection(float *Dvec) {
    VecCopy(Dvec, mSkeleton.GetLeftPalmDirection());
}

void SkelConverter::GetRightPalmDirection(float *Dvec) {
    VecCopy(Dvec, mSkeleton.GetRightPalmDirection());
}

void SkelConverter::SetShoulderWidthPhys(float Value) {
    mCorrection->SetShoulderWidthPhys(Value);
}

void SkelConverter::GetRootPhys(float *Point, float* PointCali) {
    VecCopy(Point, mRootPhys);
    VecCopy(PointCali, mRootCaliPhys);
}

void SkelConverter::GetPelvisPhys(float *Point, float* PointCali) {
    VecCopy(Point, mPelvisPhys);
    VecCopy(PointCali, mPelvisCaliPhys);
}

void SkelConverter::GetPhysDelta(float *RootPoint, float* PelvisPoint) {
    for(int i=0; i < 3; i++) {
        RootPoint[i] = mRootCaliPhys[i] - mRootPhys[i];
        PelvisPoint[i] = mPelvisCaliPhys[i] - mPelvisPhys[i];
    }
}

void SkelConverter::SetOneEuroParams(bool IsOn, float Frequency, float Mincutoff, float Beta, float Dcutoff) {

    mCorrection->SetOneEuroParams(IsOn, Frequency, Mincutoff, Beta, Dcutoff);

}

void SkelConverter::SetBoneStabilizerParams(bool IsOn, float PoseDistanceC, float HandDistanceC, float FacemeshDistanceC) {

    mCorrection->SetBoneStabilizerParams(IsOn, PoseDistanceC, HandDistanceC, FacemeshDistanceC);

}

void SkelConverter::SetHeadRotationParams(double RotationValue) {
    mRotationValue = RotationValue;
}

const int SkelConverter::GetNumBones() {
    return mSkeleton.GetNumBones();
}

const int SkelConverter::GetBoneDims() {
    return mSkeleton.GetDims();
}

const int SkelConverter::GetQuatDims() {
    return mSkeleton.GetQuatDims();
}

float* SkelConverter::GetBone(int i) {
    return mSkeleton.GetBone(i);
}

float* SkelConverter::GetQuat(int i) {
    return mSkeleton.GetQuat(i);
}

const int SkelConverter::GetMpPoseNumBones() {
    return mHolisticMP.POSE_LANDMARK_NUM;
}

float* SkelConverter::GetMpPoseBone(int i) {
    return mHolisticMP.pose[i];
}
