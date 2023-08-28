#ifndef CALIBRATION_H
#define CALIBRATION_H

#include <iostream>
#include <cmath>
#include "holistic.hpp"

using namespace std;


class Calibration {

public:

    Calibration() {
    }

    ~Calibration() {

    }

    void ToPixelSpace(float* PointOut, float* PointIn) {

        PointOut[0] = PointIn[0] * mImageWidth;
        PointOut[1] = PointIn[1] * mImageHeight;
        PointOut[2] = PointIn[2] * mImageWidth;

    }

    void SetImageSize(int ImageWidth, int ImageHeight) {

        mImageWidth = ImageWidth;
        mImageHeight = ImageHeight;

    }

    float EstimateShoulderWidth() {

        float LeftShoulder[3];
        float RightShoulder[3];

        ToPixelSpace(LeftShoulder, mData.pose[11]);
        ToPixelSpace(RightShoulder, mData.pose[12]);

        LeftShoulder[2] = 0.0;
        RightShoulder[2] = 0.0;

        float ShoulderWidth = GetLength(LeftShoulder, RightShoulder);

        return ShoulderWidth;

    }

    float EstimateTrunkHeight() {

        float CenterShoulder[3];
        float CenterHips[3];

        EstimateCenterShoulder(CenterShoulder);
        EstimateCenterHips(CenterHips);
    
        CenterShoulder[2] = 0.0;
        CenterHips[2] = 0.0;

        float TrunkHeight = GetLength(CenterShoulder, CenterHips);

        return TrunkHeight;

    }

    void EstimateCenterShoulder(float* Center) {

        float LeftShoulder[3];
        float RightShoulder[3];

        ToPixelSpace(LeftShoulder, mData.pose[11]);
        ToPixelSpace(RightShoulder, mData.pose[12]);

        EstimateCenterTwoPoints(Center, LeftShoulder, RightShoulder);

    }

    float EstimateFaceHeight() {

        float p1[3];
        float p2[3];

        ToPixelSpace(p1, mData.facemesh[10]);
        ToPixelSpace(p2, mData.facemesh[152]);

        float Height = GetLength(p1, p2);

        return Height;

    }

    void EstimateCenterHips(float* Center) {

        float LeftHip[3];
        float RightHip[3];

        ToPixelSpace(LeftHip, mData.pose[23]);
        ToPixelSpace(RightHip, mData.pose[24]);

        EstimateCenterTwoPoints(Center, LeftHip, RightHip);

    }

    float EstimateUpperArmLength() {

        float out = EstimateLimbLength(mData.pose[11], mData.pose[13],
            mData.pose[12], mData.pose[14]);

        return out;

    }

    float EstimateLowerArmLength() {

        float out = EstimateLimbLength(mData.pose[13], mData.pose[15],
            mData.pose[14], mData.pose[16]);

        return out;

    }

    float EstimateUpperLegLength() {

        float out = EstimateLimbLength(mData.pose[23], mData.pose[25],
            mData.pose[24], mData.pose[26]);

        return out;

    }

    float EstimateLowerLegLength() {

        float out = EstimateLimbLength(mData.pose[25], mData.pose[27],
            mData.pose[26], mData.pose[28]);

        return out;

    }

    float EstimateLimbLength(float *LeftDataJoint1, float *LeftDataJoint2,
        float *RightDataJoint1, float *RightDataJoint2 ) {

        float LeftJoint1[3];
        float LeftJoint2[3];

        ToPixelSpace(LeftJoint1, LeftDataJoint1);
        ToPixelSpace(LeftJoint2, LeftDataJoint2);
        LeftJoint1[2] = 0.0;  
        LeftJoint2[2] = 0.0;  

        float LeftLength = GetLength(LeftJoint1, LeftJoint2);

        float RightJoint1[3];
        float RightJoint2[3];

        ToPixelSpace(RightJoint1, RightDataJoint1);
        ToPixelSpace(RightJoint2, RightDataJoint2);
        RightJoint1[2] = 0.0;  
        RightJoint2[2] = 0.0;  

        float RightLength = GetLength(LeftJoint1, LeftJoint2);

        float out = 0.5*(LeftLength + RightLength); 

        return out;

    }

    float GetLength(float* p1, float* p2) {

        float dx1 = p1[0]-p2[0];
        float dx2 = p1[1]-p2[1];
        float dx3 = p1[2]-p2[2];
        float length = sqrt(dx1*dx1+dx2*dx2+dx3*dx3);

        return length;
    }

    void EstimateCenterTwoPoints(float* center, float* p1, float* p2) {

        center[0] = 0.5*(p1[0]+p2[0]);
        center[1] = 0.5*(p1[1]+p2[1]);
        center[2] = 0.5*(p1[2]+p2[2]);

    }

    float GetFaceHeight() {
        return mFaceHeight;
    }

    float GetTrunkHeight() {
        return mTrunkHeight;
    }

    float GetShoulderWidth() {
        return mShoulderWidth;
    }

    float GetRatioArmFace() {
        return mRatioArmFace;
    }

    float GetRatioArmTrunk() {
        return mRatioArmTrunk;
    }

    float GetRatioLegFace() {
        return mRatioLegFace;
    }

    float GetRatioLegTrunk() {
        return mRatioLegTrunk;
    }

    float GetUpperArmRatio() {
        return mUpperArmRatio;
    }

    float GetLowerArmRatio() {
        return mLowerArmRatio;
    }

    float GetUpperLegRatio() {
        return mUpperLegRatio;
    }

    float GetLowerLegRatio() {
        return mLowerLegRatio;
    }

    float GetUpperArmLength() {
        return mUpperArmLength;
    }

    float GetLowerArmLength() {
        return mLowerArmLength;
    }

    float GetArmLength() {
        return mArmLength;
    }

    float GetLegLength() {
        return mLegLength;
    }

    void SetShoulderWidthPhys(float Width) {
        mShoulderWidthPhys = Width;
    }

    float GetShoulderWidthPhys() {
        return mShoulderWidthPhys;
    }

    float GetRatioPhysToPixel() {
        return mRatioPhysToPixel;
    }

    void Process(Holistic &data) {

        mData = data;

        mFaceHeight = EstimateFaceHeight();
        mTrunkHeight = EstimateTrunkHeight();
        mShoulderWidth = EstimateShoulderWidth();

        mUpperArmLength = EstimateUpperArmLength();
        mLowerArmLength = EstimateLowerArmLength();

        mUpperLegLength = EstimateUpperLegLength();
        mLowerLegLength = EstimateLowerLegLength();

        mArmLength = mUpperArmLength + mLowerArmLength;
        mLegLength = mUpperLegLength + mLowerLegLength;

        mRatioArmFace = mArmLength / mFaceHeight;
        mRatioLegFace = mLegLength / mFaceHeight;

        mRatioArmTrunk = mArmLength / mTrunkHeight;
        mRatioLegTrunk = mLegLength / mTrunkHeight;

        mRatioArmShoulder = mArmLength / mShoulderWidth;
        mRatioLegShoulder = mLegLength / mShoulderWidth;

        mUpperArmRatio = mUpperArmLength / mArmLength;
        mLowerArmRatio = 1.0 - mUpperArmRatio;

        mUpperLegRatio = mUpperLegLength / mLegLength;
        mLowerLegRatio = 1.0 - mUpperLegRatio;

        // Ratio of Physical space to pixel space
        mRatioPhysToPixel = 1.0 * mShoulderWidthPhys / GetShoulderWidth();

    }
    

private:

    int mImageWidth;
    int mImageHeight;

    Holistic mData; // Holistic data

    float mFaceHeight;
    float mTrunkHeight;
    float mShoulderWidth;

    float mArmLength;
    float mUpperArmLength;
    float mLowerArmLength;

    float mLegLength;
    float mUpperLegLength;
    float mLowerLegLength;

    float mRatioArmFace; // Ratio of arm to face
    float mRatioArmTrunk; // Ratio of arm to trunk
    float mRatioArmShoulder; // Ratio of arm to shoulder

    float mRatioLegFace; // Ratio of leg to face
    float mRatioLegTrunk; // Ratio of leg to trunk
    float mRatioLegShoulder; // Ratio of leg to shoulder

    float mUpperArmRatio;
    float mLowerArmRatio;

    float mUpperLegRatio;
    float mLowerLegRatio;

    // Physical space
    float mShoulderWidthPhys = 1.0; // meter
    float mRatioPhysToPixel = 1.0;

};

#endif