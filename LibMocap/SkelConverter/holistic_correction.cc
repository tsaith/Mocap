#include "pch.h"

#include "holistic_correction.h"

using namespace std;
using namespace math_utils;

HolisticCorrection::HolisticCorrection() {
}

HolisticCorrection::~HolisticCorrection() {
}

bool HolisticCorrection::Init(int ImageWidth, int ImageHeight) {
    try {
        mImageWidth = ImageWidth;
        mImageHeight = ImageHeight;

        mCalibration.SetImageSize(ImageWidth, ImageHeight);

        // Filter Timer starts
        mFilterTimer.tic();

        // One Euro filter
        double frequency = mOneEuroFrequency;
        double mincutoff = mOneEuroMincutoff;
        double beta = mOneEuroBeta;
        double dcutoff = mOneEuroDcutoff;   // this one should be ok

        for (int i=0; i < mData.POSE_LANDMARK_NUM; i++) {
            for (int j=0; j < 3; j++) {
                mPoseOneEuro[i][j].Init(frequency, mincutoff, beta, dcutoff);
            } 
        } 

        for (int i=0; i < mData.HAND_LANDMARK_NUM; i++) {
            for (int j=0; j < 3; j++) {
                mLeftHandOneEuro[i][j].Init(frequency, mincutoff, beta, dcutoff);
                mRightHandOneEuro[i][j].Init(frequency, mincutoff, beta, dcutoff);
            } 
        }

        for (int i=0; i < mData.FACEMESH_LANDMARK_NUM; i++) {
            for (int j=0; j < 3; j++) {
                mFacemeshOneEuro[i][j].Init(frequency, mincutoff, beta, dcutoff);
            } 
        } 

        // Kalman filter
        float Pvar = 0.1;
	    float Qvar = 0.1; // Process uncertainty
	    float Rvar = 0.5; // Measurement uncertainty
        float dt = 0.1;
        Eigen::VectorXd state = Eigen::VectorXd::Zero(2);

        for (int dim=0; dim < 3; dim++) {
            for (int i=0; i < mData.POSE_LANDMARK_NUM; i++) {
                mPoseKalman[i][dim].Init(state, dt, Pvar, Qvar, Rvar);
            }
        } 

        for (int dim=0; dim < 3; dim++) {
            for (int i=0; i < mData.GetHandLandmarkNum(); i++) {
                mLeftHandKalman[i][dim].Init(state, dt, Pvar, Qvar, Rvar);
                mRightHandKalman[i][dim].Init(state, dt, Pvar, Qvar, Rvar);
            }
        }

        for (int dim=0; dim < 3; dim++) {
            for (int i=0; i < mData.GetFacemeshLandmarkNum(); i++) {
                mFacemeshKalman[i][dim].Init(state, dt, Pvar, Qvar, Rvar);
            }
        }

        mDepthKalman.Init(state, dt, Pvar, Qvar, Rvar);

        return true;
    }
    catch(std::exception &e) {
        cout << e.what() << endl;
        
        return false;
    }
}

void HolisticCorrection::GuessOccludedPoints() {

    float visibility;
    float visibilityPrev;
    int dims = mData.DIMENSIONS;
    bool UseGuessed = false;


    int num = mData.POSE_LANDMARK_NUM;
    for (int i=0; i < num; i++) {

        visibility =  mData.pose[i][3]; 
        visibilityPrev =  mDataPrev.pose[i][3];

        UseGuessed = visibility < mVisibilityThreshold && visibilityPrev > mVisibilityThreshold;
        if (UseGuessed) {
            for (int j=0; j < dims; j++) {
                    mData.pose[i][j] = mDataPrev.pose[i][j];
            }
        }
    }

}

void HolisticCorrection::ToPixelSpace(float* PointOut, float* PointIn) {

    PointOut[0] = PointIn[0] * mImageWidth;
    PointOut[1] = PointIn[1] * mImageHeight;
    PointOut[2] = PointIn[2] * mImageWidth;

}

void HolisticCorrection::ToNormalizedSpace(float* PointOut, float* PointIn) {

    PointOut[0] = PointIn[0] / mImageWidth;
    PointOut[1] = PointIn[1] / mImageHeight;
    PointOut[2] = PointIn[2] / mImageWidth;

}

float HolisticCorrection::GetDepth() {
    return mDepth;
}

float* HolisticCorrection::GetFaceDirection() {
    return mFaceDirection;
}    

float* HolisticCorrection::GetTrunkDirection() {
    return mTrunkDirection;
}    

float HolisticCorrection::EstimateLength(float* p1, float* p2) {

    float length;
    LengthFromTwoPoints(length, p1, p2);

    return length;

};

void HolisticCorrection::ToPoint(float point[3], float x, float y, float z) {

    point[0] = x;
    point[1] = y;
    point[2] = z;

};

void HolisticCorrection::EstimateCenterFromTwoPoints(float* center, float* p1, float* p2) {

    center[0] = 0.5*(p1[0]+p2[0]);
    center[1] = 0.5*(p1[1]+p2[1]);
    center[2] = 0.5*(p1[2]+p2[2]);

};

float HolisticCorrection::EstimateHeadWidth() {

    float LeftEar[3];
    float RightEar[3];

    ToPixelSpace(LeftEar, mData.pose[7]);
    ToPixelSpace(RightEar, mData.pose[8]);

    LeftEar[2] = 0;
    RightEar[2] = 0;

    float Width = EstimateLength(LeftEar, RightEar);

    return Width;

}

float HolisticCorrection::EstimateShoulderWidth() {

    float LeftShoulder[3];
    float RightShoulder[3];

    ToPixelSpace(LeftShoulder, mData.pose[11]);
    ToPixelSpace(RightShoulder, mData.pose[12]);

    LeftShoulder[2] = 0;
    RightShoulder[2] = 0;

    float ShoulderWidth = EstimateLength(LeftShoulder, RightShoulder);

    return ShoulderWidth;

}

float HolisticCorrection::EstimateTrunkHeight() {

    float CenterShoulder[3];
    float CenterHips[3];

    EstimateCenterShoulder(CenterShoulder);
    EstimateCenterHips(CenterHips);

    CenterShoulder[2] = 0;
    CenterHips[2] = 0;

    float TrunkHeight = EstimateLength(CenterShoulder, CenterHips);

    return TrunkHeight;

}

float HolisticCorrection::EstimateSpineLength() {

    if (IsFrontFace()) {
        mSpineLength = EstimateTrunkHeight();
    }

    return mSpineLength;
}

void HolisticCorrection::EstimateCenterShoulder(float* Center) {

    float LeftShoulder[3];
    float RightShoulder[3];

    ToPixelSpace(LeftShoulder, mData.pose[11]);
    ToPixelSpace(RightShoulder, mData.pose[12]);

    EstimateCenterFromTwoPoints(Center, LeftShoulder, RightShoulder);

}

void HolisticCorrection::EstimateCenterHips(float* Center) {

    float LeftHips[3];
    float RightHips[3];

    ToPixelSpace(LeftHips, mData.pose[23]);
    ToPixelSpace(RightHips, mData.pose[24]);

    EstimateCenterFromTwoPoints(Center, LeftHips, RightHips);

}

float HolisticCorrection::EstimateFaceHeight() {

    float p1[3];
    float p2[3];

    ToPixelSpace(p1, mData.facemesh[10]);
    ToPixelSpace(p2, mData.facemesh[152]);

    float Height = EstimateLength(p1, p2);


    return Height;

}


float HolisticCorrection::EstimateArmLength() {

    float ArmLength = mRatioArmFace*mFaceHeight;

    return ArmLength;

}

float HolisticCorrection::EstimateLegLength() {

    float LegLength = mRatioLegFace*mFaceHeight;

    return LegLength;

}

void HolisticCorrection::EstimateCenterHead(float* Center) {

    float LeftEar[3];
    float RightEar[3];

    ToPixelSpace(LeftEar, mData.pose[7]);
    ToPixelSpace(RightEar, mData.pose[8]);

    EstimateCenterFromTwoPoints(Center, LeftEar, RightEar);

}

void HolisticCorrection::CorrectPoseHead() {

    const int dims = mData.DIMENSIONS;
    float (*pose)[dims] = mData.pose;

    // Correct all points of head
    float zShoulderL = pose[11][2];
    float zShoulderR = pose[12][2];
    float zShoulderC = 0.5*(zShoulderL + zShoulderR);
    float zEarL = pose[7][2];
    float zEarR = pose[8][2];
    float zHead = 0.5*(zEarL + zEarR);
    float zHeadShift = zHead - zShoulderC;
    for (int i=0; i < 11; i++) {
        pose[i][2] -= zHeadShift;
    }

    /*
    float CenterHead[3];
    float CenterShoulder[3];
    EstimateCenterHead(CenterHead);
    EstimateCenterShoulder(CenterShoulder);
    */

}

void HolisticCorrection::EstimateTargetZ(float* PointTarget, float* PointRoot,
    float length, float sign) {
    /*
        PointTarget: Target point.
        PointRoot: Root point.
        length: Length between two points.
        sign: Sign which should be 1.0 or -1.0.
    */

    float x = PointTarget[0];
    float y = PointTarget[1];
    float z;

    float xRoot = PointRoot[0];
    float yRoot = PointRoot[1];
    float zRoot = PointRoot[2];

    float len2 = length*length;
    float dx2 = (x-xRoot)*(x-xRoot);
    float dy2 = (y-yRoot)*(y-yRoot);
    
    float tmp = len2 - dx2 - dy2;
    if (tmp < 0) tmp = 0.0;

    z = zRoot + sign*sqrt(tmp);

    PointTarget[2] = z;

}

void HolisticCorrection::EstimateUncertainPoints(float LenU, float LenL, 
    float* PointRoot, float* PointMiddle, float* PointTip) {
    /*
        LenU: Length of upper part.
        LenL: Length of lower part.
        PointRoot: Root point.
        MiddlePoint: Middle point.
        TipPoint: Tip point.
    */

}


void HolisticCorrection::EstimateFaceDirection(float* VecD) {

    const int dims = mData.DIMENSIONS;
    float (*facemesh)[dims] = mData.facemesh;

    float FaceTop[3], FaceBottom[3];
    float EyeLeft[3], EyeRight[3];
    float vecV[3], vecH[3];

    ToPixelSpace(FaceTop, mData.facemesh[10]);
    ToPixelSpace(FaceBottom, mData.facemesh[152]);
    ToPixelSpace(EyeLeft, mData.facemesh[362]);
    ToPixelSpace(EyeRight, mData.facemesh[133]);
    
    // Verical and horizontal vectors
    VecSubstract(vecV, FaceTop, FaceBottom);
    VecSubstract(vecH, EyeRight, EyeLeft);

    // Direction
    VecCrossNorm(VecD, vecV, vecH);

}


void HolisticCorrection::EstimateTrunkDirection(float* VecD) {

    const int dims = mData.DIMENSIONS;
    float (*pose)[dims] = mData.pose;

    float PointSL[3], PointSR[3], PointHL[3];

    ToPixelSpace(PointSL, mData.pose[11]);
    ToPixelSpace(PointSR, mData.pose[12]);
    ToPixelSpace(PointHL, mData.pose[23]);

    float VecA[3], VecB[3];
    //float norm;

    VecSubstract(VecA, PointSR, PointSL); 
    VecSubstract(VecB, PointHL, PointSL); 

    // Estimate the direction vector
    VecCrossNorm(VecD, VecA, VecB);

}

void HolisticCorrection::CorrectPoseShoulder(bool IsRight) {

    if (IsRight) {
        mData.pose[12][2] = mData.pose[24][2]; 
    } else {
        mData.pose[11][2] = mData.pose[23][2]; 
    }

}

void HolisticCorrection::CorrectPoseArm(bool IsRight) {

    const int dims = mData.DIMENSIONS;
    float (*pose)[dims] = mData.pose;

    float Shoulder[3];
    float Elbow[3];
    float Wrist[3];

    int iShoulder, iElbow, iWrist;
    int iThumb, iIndex, iPinky;
    if (IsRight) { // Right foot

        iShoulder = 12;
        iElbow = 14;
        iWrist = 16;

        iThumb = 22;
        iIndex = 20;
        iPinky = 18;

    } else { // Left foot

        iShoulder = 11;
        iElbow = 13;
        iWrist = 15;

        iThumb = 21;
        iIndex = 19;
        iPinky = 17;

    }

    ToPixelSpace(Shoulder, pose[iShoulder]);
    ToPixelSpace(Elbow, pose[iElbow]);
    ToPixelSpace(Wrist, pose[iWrist]);

    EstimateUncertainPoints(mUpperArmLength, mLowerArmLength,
        Shoulder, Elbow, Wrist); 

    float zElbow = Elbow[2]; 
    float zWrist = Wrist[2]; 

    // Normalize
    zElbow /= mImageWidth;
    zWrist /= mImageWidth;

    // Correct values
    float zWristOri = pose[iWrist][2];
    float dzWrist = zWristOri - zWrist;

    float zPinky = pose[iPinky][2] - dzWrist;
    float zIndex = pose[iIndex][2] - dzWrist;
    float zThumb = pose[iThumb][2] - dzWrist;

    // Set values
    pose[iElbow][2] = zElbow;
    pose[iWrist][2] = zWrist;

    pose[iPinky][2] = zPinky;
    pose[iIndex][2] = zIndex;
    pose[iThumb][2] = zThumb;

}

void HolisticCorrection::CorrectPoseLeg(bool IsRight) {

    const int dim = mData.DIMENSIONS;
    float (*pose)[dim] = mData.pose;

    float Hip[3];
    float Knee[3];
    float Ankle[3];
    
    int iHip, iKnee, iAnkle;
    int iHeel, iIndex;
    if (IsRight) { // Right foot

        iHip = 24;
        iKnee = 26;
        iAnkle = 28;

        iHeel = 30;
        iIndex = 32;

    } else { // Left foot

        iHip = 23;
        iKnee = 25;
        iAnkle = 27;

        iHeel = 29;
        iIndex = 31;

    }

    ToPixelSpace(Hip, pose[iHip]);
    ToPixelSpace(Knee, pose[iKnee]);
    ToPixelSpace(Ankle, pose[iAnkle]);

    EstimateUncertainPoints(mUpperLegLength, mLowerLegLength,
        Hip, Knee, Ankle); 

    float zKnee = Knee[2]; 
    float zAnkle = Ankle[2]; 

    // Normalize
    zKnee /= mImageWidth;
    zAnkle /= mImageWidth;

    // Set the z of knee and ankle forcely
    float zHip = pose[iHip][2];
    if (zKnee > zHip) zKnee = zHip;
    if (zAnkle > zHip) zAnkle = zHip;

    // Correct values
    float zAngleOri = pose[iAnkle][2];
    float dzAnkle = zAngleOri - zAnkle;

    float zHeel = pose[iHeel][2] - dzAnkle;
    float zFootIndex = pose[iIndex][2] - dzAnkle;

    // Set values
    pose[iKnee][2] = zKnee;
    pose[iAnkle][2] = zAnkle;

    pose[iHeel][2] = zHeel;
    pose[iIndex][2] = zFootIndex;
        
}

void HolisticCorrection::CorrectPoseFoot(bool IsRight) {

    const int dim = mData.DIMENSIONS;
    float (*pose)[dim] = mData.pose;

    float Ankle[3];
    float Heel[3];
    float Index[3];
    
    int iAnkle, iHeel, iIndex;
    if (IsRight) { // Right foot

        iAnkle = 28;
        iHeel = 30;
        iIndex = 32;

    } else { // Left foot

        iAnkle = 27;
        iHeel = 29;
        iIndex = 31;

    }

    ToPixelSpace(Ankle, pose[iAnkle]);
    ToPixelSpace(Heel, pose[iHeel]);
    ToPixelSpace(Index, pose[iIndex]);

    // Assume the angle is 30 degree
    float SinTheta = 0.5;
    float CosTheta = 0.5*sqrt(3.0);

    float LenHI = 0.5*mLowerLegLength;
    float LenAI = CosTheta*LenHI;
    float LenAH = SinTheta*LenHI;

    float signIndex, signHeel;
    if (mTrunkDirection[2] < 0) {
        signIndex = -1.0;
        signHeel = 1.0;
    } else {
        signIndex = 1.0;
        signHeel = -1.0;
    }    

    // Heel
    EstimateTargetZ(Heel, Ankle, LenAH, signHeel);
    pose[iHeel][2] = Heel[2] / mImageWidth;

    // Foot index
    EstimateTargetZ(Index, Ankle, LenAI, signIndex);
    pose[iIndex][2] = Index[2] / mImageWidth;

}

void HolisticCorrection::CorrectLeftHand() {

    int iWrist = 15;
    float zPoseWrist = mData.pose[iWrist][2];

    for (int i=0; i < mData.HAND_LANDMARK_NUM; i++) {
        mData.LeftHand[i][2] += zPoseWrist;
    }

}

void HolisticCorrection::CorrectRightHand() {

    int iWrist = 16;
    float zPoseWrist = mData.pose[iWrist][2];

    for (int i=0; i < mData.HAND_LANDMARK_NUM; i++) {
        mData.RightHand[i][2] += zPoseWrist;
    }

}

void HolisticCorrection::ToCustomizedHolistic() {
    /*
       y' = y * (ImageHeight/ImageWidth)
       where y' is the customeized normalized value and
       y is the Mediapipe normalized value
    */

    float NormRatio = 1.0*mImageHeight/mImageWidth;

    // Pose
    for (int i=0; i < mData.GetPoseLandmarkNum(); i++) {
        mData.pose[i][1] *= NormRatio;
    }

    // Hands
    for (int i=0; i < mData.GetHandLandmarkNum(); i++) {
        mData.LeftHand[i][1] *= NormRatio;
        mData.RightHand[i][1] *= NormRatio;
    }

    // Facemesh
    for (int i=0; i < mData.GetFacemeshLandmarkNum(); i++) {
        mData.facemesh[i][1] *= NormRatio;
    }

}

bool HolisticCorrection::DoesBendOver() {
    // Bend over or not

    float centerShoulder[3];
    float centerHips[3];
    float zShoulder;
    float zHips;
    EstimateCenterShoulder(centerShoulder);
    EstimateCenterHips(centerHips);
    zShoulder = centerShoulder[2];
    zHips = centerHips[2];

    float dist;
    float distC = 0.2;
    dist = abs(zShoulder-zHips);
    dist /= mImageWidth; // Normalization
    
    bool bBendOver = false;   
    if (dist > distC) bBendOver = true;

    return bBendOver;

}

bool HolisticCorrection::IsFrontFace() {

    float* faceDirection;
    faceDirection = GetFaceDirection();

    float cosTheta = faceDirection[2]; 
    bool isFront = false;
    if (cosTheta < -0.95) isFront = true;

    return isFront;

}

float HolisticCorrection::EstimateDepth() {

    float Height;
    float HeightCalibrated;
    float Depth;
 
    bool isFrontFace = IsFrontFace();

    if (mData.HasFacemesh && isFrontFace) {

        Height = EstimateFaceHeight();
        HeightCalibrated = mCalibration.GetFaceHeight();
        Depth = 0.25*(1.0 - Height / HeightCalibrated);

    } else {

        Depth = mDepthPrev;

    }

    // Save the depth
    mDepthPrev = Depth;

    return Depth;

}


void HolisticCorrection::Calibrate(Holistic &data) {

    // Calibration flag
    mIsCalibrated = true;

    // Use Mediapipe holistic data 
    mCalibration.Process(data);

    // Update component ratio
    mRatioArmFace = mCalibration.GetRatioArmFace();
    mRatioLegFace = mCalibration.GetRatioLegFace();

    mRatioArmTrunk = mCalibration.GetRatioArmTrunk();
    mRatioLegTrunk = mCalibration.GetRatioLegTrunk();

    mUpperArmRatio = mCalibration.GetUpperArmRatio();
    mLowerArmRatio = mCalibration.GetLowerArmRatio();

    mUpperLegRatio = mCalibration.GetUpperLegRatio();
    mLowerLegRatio = mCalibration.GetLowerLegRatio();

}

void HolisticCorrection::SetIsCalibrated(bool Status) {
    mIsCalibrated = Status;
}

bool HolisticCorrection::IsCalibrated() {
    return mIsCalibrated;
}

void HolisticCorrection::UpdatePosePrev() {

    // Pose
    int num = mData.POSE_LANDMARK_NUM;
    int dims = mData.DIMENSIONS;
    for (int i=0; i < num; i++) {
        for (int j=0; j < dims; j++) {
            mDataPrev.pose[i][j] = mData.pose[i][j]; 
        }
    }

}

void HolisticCorrection::Preprocess() {

    if (mOneEuroIsOn) {
        ApplyFilterOnBones();
    }

    // Stablize all bones
    if (mBoneStabilizerIsOn) {
        StabilizeBones();
    }


}

void HolisticCorrection::ApplyFilterOnBones() {

    // Time
    mFilterTimer.toc();

    double timestamp = mFilterTimer.GetElapsedTime();

    // Apply filter on the depth of pose 
    for (int dim=0; dim < 3 ; dim++) {
        for (int i=0; i < mData.GetPoseLandmarkNum(); i++) {

            mData.pose[i][dim] = mPoseOneEuro[i][dim].Filter(mData.pose[i][dim], timestamp);

        }
    }

    // Apply filter on hands
    for (int i=0; i < mData.GetHandLandmarkNum(); i++) {

        mData.LeftHand[i][2] = mLeftHandOneEuro[i][2].Filter(mData.LeftHand[i][2], timestamp);
        mData.RightHand[i][2] = mRightHandOneEuro[i][2].Filter(mData.RightHand[i][2], timestamp);

    }

    // Only apply filter on two points of facemesh 
    // which will be used to estimate the head point
    int indexes[2] = {10, 152};
    for (int dim=0; dim < 3 ; dim++) {
        for (int i=0; i < 2; i++) {

            mData.facemesh[i][dim] = mFacemeshOneEuro[i][dim].Filter(mData.facemesh[i][dim], timestamp);

        }
    }

}

void HolisticCorrection::StabilizeBones() {

    float poseDistanceC = mBoneStabilizerPoseDistanceC;
    float handDistanceC = mBoneStabilizerHandDistanceC;
    float facemeshDistanceC = mBoneStabilizerFacemeshDistanceC;

    // Pose
    for (int i=0; i < mData.GetPoseLandmarkNum(); i++) {
        mPoseStabilizer[i].SetDistanceC(poseDistanceC);
        mPoseStabilizer[i].Update(mData.pose[i]);
    }

    // Left fingers
    for (int i=0; i < mData.GetHandLandmarkNum(); i++) {
        mLeftFingersStabilizer[i].SetDistanceC(handDistanceC);
        mLeftFingersStabilizer[i].Update(mData.LeftHand[i]);
    }

    // Right fingers
    for (int i=0; i < mData.GetHandLandmarkNum(); i++) {
        mRightFingersStabilizer[i].SetDistanceC(handDistanceC);
        mRightFingersStabilizer[i].Update(mData.RightHand[i]);
    }

    float wristPose[3];
    // Left hand
    VecCopy(wristPose, mData.pose[15], 3);
    mLeftHandStabilizer.Process(mData.LeftHand, wristPose);
    mData.SetIsLeftHandStable(mLeftHandStabilizer.IsStable());

    // Right hand
    VecCopy(wristPose, mData.pose[16], 3);
    mRightHandStabilizer.Process(mData.RightHand, wristPose);
    mData.SetIsRightHandStable(mRightHandStabilizer.IsStable());

    // Only apply bone stabilizer on two points of facemesh 
    // which will be used to estimate the head point
    int indexes[2] = {10, 152};
    int iFacemesh;
    for (int i=0; i < 2; i++) {
        iFacemesh = indexes[i];
        mRightFingersStabilizer[iFacemesh].SetDistanceC(facemeshDistanceC);
        mRightFingersStabilizer[iFacemesh].Update(mData.facemesh[iFacemesh]);
    }

}

Holistic HolisticCorrection::Process(Holistic &Data) {

    // Save Holistic data
    mData = Data;

    // Preprocess
    Preprocess();

    // Component exists or not
    mHasPose = mData.HasPose;
    mHasFacemesh = mData.HasFacemesh;
    mHasLeftHand = mData.HasLeftHand;
    mHasRightHand = mData.HasRightHand;

    // Parameters
    mFaceHeight = EstimateFaceHeight();
    mHeadWidth = EstimateHeadWidth();
    mShoulderWidth = EstimateShoulderWidth();
    mTrunkHeight = EstimateTrunkHeight();

    mArmLength = EstimateArmLength();
    mLegLength = EstimateLegLength();

    mUpperArmLength = mUpperArmRatio * mArmLength;
    mLowerArmLength = mLowerArmRatio * mArmLength;

    mUpperLegLength = mUpperLegRatio * mLegLength;
    mLowerLegLength = mLowerLegRatio * mLegLength;

    // Face direction vector
    EstimateFaceDirection(mFaceDirection);
    // Trunk direction vector
    EstimateTrunkDirection(mTrunkDirection);

    // Depth from camera to target
    if (mIsCalibrated) {
        mDepth = EstimateDepth();
    }

    // Pose
    CorrectPoseShoulder(false); // Left shoulder
    CorrectPoseShoulder(true);  // Right shoulder

    CorrectPoseHead(); // This should be put after shoulder correction

    //CorrectPoseArm(false);  // Left arm
    //CorrectPoseArm(true);   // Right arm
    CorrectPoseLeg(false);  // Left leg
    CorrectPoseLeg(true);   // Right leg
    CorrectPoseFoot(false); // Left foot
    CorrectPoseFoot(true);  // Right foot

    // Hands
    CorrectLeftHand();
    CorrectRightHand();

    // Update previous pose
    UpdatePosePrev();

    // Covert to customized Holistic data
    ToCustomizedHolistic();

    // User is close to camera or not
    bool mIsShortDistance = false;

    return mData;

}

bool HolisticCorrection::HasPose() {
    return mHasPose;
}

bool HolisticCorrection::HasFacemesh() {
    return mHasFacemesh;
}

bool HolisticCorrection::HasLeftHand() {
    return mHasLeftHand;
}

bool HolisticCorrection::HasRightHand() {
    return mHasRightHand;
}

bool HolisticCorrection::IsShortDistance() {

    bool bResult = false;
    bool bIsLandscape = false;
    float heightRatio;


    if (mImageWidth > mImageHeight) {
        bIsLandscape = true;
    } else {
        bIsLandscape = false;
    }

    if (bIsLandscape) {
        heightRatio = 0.4;
    } else {
        heightRatio = 0.4;
    }

    if (mTrunkHeight > heightRatio*mImageHeight) {
        bResult = true;
    } else {
        bResult = false;
    }

    return bResult;

}

void HolisticCorrection::SetShoulderWidthPhys(float Value) {
    mCalibration.SetShoulderWidthPhys(Value);
}

float HolisticCorrection::GetRatioPhysToPixel() {
    return mCalibration.GetRatioPhysToPixel();
}

// Methods to set parameters
void HolisticCorrection::SetImageWidth(float Width) {
    mImageWidth = Width;
}

void HolisticCorrection::SetImageHeight(float Height) {
    mImageHeight = Height;
}

void HolisticCorrection::SetOneEuroParams(bool IsOn, float Frequency, float Mincutoff,
    float Beta, float Dcutoff) {

    mOneEuroIsOn = IsOn; 
    mOneEuroFrequency = Frequency;
    mOneEuroMincutoff = Mincutoff;
    mOneEuroBeta = Beta;
    mOneEuroDcutoff = Dcutoff;

}

void HolisticCorrection::SetBoneStabilizerParams(bool IsOn, float PoseDistanceC,
    float HandDistanceC, float FacemeshDistanceC) {

    mBoneStabilizerIsOn = IsOn; 
    mBoneStabilizerPoseDistanceC = PoseDistanceC;
    mBoneStabilizerHandDistanceC = HandDistanceC;
    mBoneStabilizerFacemeshDistanceC = FacemeshDistanceC;

}
