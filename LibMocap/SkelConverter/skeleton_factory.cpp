#include "pch.h"

#include "skeleton_factory.h"


SkeletonFactory::SkeletonFactory() {
} 

SkeletonFactory::~SkeletonFactory() {

}

void SkeletonFactory::Preprocess(Holistic &data, bool IsShortDistance) {

    /*
        Convert holistic data into a skeleton object.
    */

    mIsShortDistance = IsShortDistance;

    float weight;
    float length; 
    float dvec1[mDims];
    float vecTmp[mDims];

    mPose.SetHasFace(data.HasFacemesh);
    mPose.SetHasBody(data.HasPose);
    mPose.SetHasLeftHand(data.HasLeftHand);
    mPose.SetHasRightHand(data.HasRightHand);

    // Hips
    VecCopy(mPose.GetHipL(), data.pose[23], mDims);
    VecCopy(mPose.GetHipR(), data.pose[24], mDims);

    // Hip center
    VecMean(mPose.GetHipCenter(), mPose.GetHipL(), mPose.GetHipR());

    // Pelvis
    weight = 0.2;
    InterpPoint(mPose.GetPelvis(), mPose.GetHipCenter(), mPose.GetShoulderCenter(), weight);

    // Spine
    float weightSpine01 = 0.2;
    float weightSpine02 = 0.5;
    float weightSpine03 = 0.75;
    InterpPoint(mPose.GetSpine01(), mPose.GetPelvis(), mPose.GetShoulderCenter(), weightSpine01);
    InterpPoint(mPose.GetSpine02(), mPose.GetPelvis(), mPose.GetShoulderCenter(), weightSpine02);
    InterpPoint(mPose.GetSpine03(), mPose.GetPelvis(), mPose.GetShoulderCenter(), weightSpine03);
    
    // Clavicle
    float weightClavicleL = 0.35;
    float weightClavicleR = 0.65;
    InterpPoint(mPose.GetClavicleL(), mPose.GetShoulderL(), mPose.GetShoulderR(), weightClavicleL);
    InterpPoint(mPose.GetClavicleR(), mPose.GetShoulderL(), mPose.GetShoulderR(), weightClavicleR);

    // Shoulder
    VecCopy(mPose.GetShoulderL(), data.pose[11], mDims);
    VecCopy(mPose.GetShoulderR(), data.pose[12], mDims);

    // Shoulder center
    VecMean(mPose.GetShoulderCenter(), mPose.GetShoulderL(), mPose.GetShoulderR());

    // Neck
    float weightNeck01 = 0.333;
    InterpPoint(mPose.GetNeck01(), mPose.GetShoulderCenter(), mPose.GetHead(), weightNeck01);

    // Ears
    VecCopy(mPose.GetEarL(), data.pose[7], mDims);
    VecCopy(mPose.GetEarR(), data.pose[8], mDims);

    // Nose
    VecCopy(mPose.GetNose(), data.pose[0], mDims);

    // Head
    VecMean(mPose.GetHead(), mPose.GetEarL(), mPose.GetEarR());

    /*
    // Correct the depth of head
    LengthFromTwoPoints(length, mPose.GetHead(), mPose.GetNeck01());
    if (mPose.HasFace()) {
        VecSubstractNorm(dvec1, data.facemesh[10], data.facemesh[152]);
        VecMultiply(vecTmp, dvec1, length);
        VecAdd(mPose.GetHead(), mPose.GetNeck01(), vecTmp);
    }
    */

    // Upper arm
    VecCopy(mPose.GetUpperarmL(), mPose.GetShoulderL(), mDims);
    VecCopy(mPose.GetUpperarmR(), mPose.GetShoulderR(), mDims);

    // Lower arm
    VecCopy(mPose.GetLowerarmL(), data.pose[13], mDims);
    VecCopy(mPose.GetLowerarmR(), data.pose[14], mDims);

    // Hands
    VecCopy(mPose.GetHandL(), data.pose[15], mDims);
    VecCopy(mPose.GetHandR(), data.pose[16], mDims);

    // Thigh
    VecCopy(mPose.GetThighL(), mPose.GetHipL(), mDims);
    VecCopy(mPose.GetThighR(), mPose.GetHipR(), mDims);

    // Calf
    VecCopy(mPose.GetCalfL(), data.pose[25], mDims);
    VecCopy(mPose.GetCalfR(), data.pose[26], mDims);

    // Foot
    VecCopy(mPose.GetFootL(), data.pose[27], mDims);
    VecCopy(mPose.GetFootR(), data.pose[28], mDims);

    // Ball
    VecCopy(mPose.GetBallL(), data.pose[31], mDims);
    VecCopy(mPose.GetBallR(), data.pose[32], mDims);

    // Left fingers
    if (mPose.HasLeftHand()) {

        VecCopy(mPose.GetThumb01L(), data.GetThumb01L(), mDims);
        VecCopy(mPose.GetThumb02L(), data.GetThumb02L(), mDims);
        VecCopy(mPose.GetThumb03L(), data.GetThumb03L(), mDims);
        VecCopy(mPose.GetThumb04L(), data.GetThumb04L(), mDims);
        VecCopy(mPose.GetIndex01L(), data.GetIndex01L(), mDims);
        VecCopy(mPose.GetIndex02L(), data.GetIndex02L(), mDims);
        VecCopy(mPose.GetIndex03L(), data.GetIndex03L(), mDims);
        VecCopy(mPose.GetIndex04L(), data.GetIndex04L(), mDims);
        VecCopy(mPose.GetMiddle01L(), data.GetMiddle01L(), mDims);
        VecCopy(mPose.GetMiddle02L(), data.GetMiddle02L(), mDims);
        VecCopy(mPose.GetMiddle03L(), data.GetMiddle03L(), mDims);
        VecCopy(mPose.GetMiddle04L(), data.GetMiddle04L(), mDims);
        VecCopy(mPose.GetRing01L(), data.GetRing01L(), mDims);
        VecCopy(mPose.GetRing02L(), data.GetRing02L(), mDims);
        VecCopy(mPose.GetRing03L(), data.GetRing03L(), mDims);
        VecCopy(mPose.GetRing04L(), data.GetRing04L(), mDims);
        VecCopy(mPose.GetPinky01L(), data.GetPinky01L(), mDims);
        VecCopy(mPose.GetPinky02L(), data.GetPinky02L(), mDims);
        VecCopy(mPose.GetPinky03L(), data.GetPinky03L(), mDims);
        VecCopy(mPose.GetPinky04L(), data.GetPinky04L(), mDims);

    }
    
    // Right fingers
    if (mPose.HasRightHand()) {

        VecCopy(mPose.GetThumb01R(), data.GetThumb01R(), mDims);
        VecCopy(mPose.GetThumb02R(), data.GetThumb02R(), mDims);
        VecCopy(mPose.GetThumb03R(), data.GetThumb03R(), mDims);
        VecCopy(mPose.GetThumb04R(), data.GetThumb04R(), mDims);
        VecCopy(mPose.GetIndex01R(), data.GetIndex01R(), mDims);
        VecCopy(mPose.GetIndex02R(), data.GetIndex02R(), mDims);
        VecCopy(mPose.GetIndex03R(), data.GetIndex03R(), mDims);
        VecCopy(mPose.GetIndex04R(), data.GetIndex04R(), mDims);
        VecCopy(mPose.GetMiddle01R(), data.GetMiddle01R(), mDims);
        VecCopy(mPose.GetMiddle02R(), data.GetMiddle02R(), mDims);
        VecCopy(mPose.GetMiddle03R(), data.GetMiddle03R(), mDims);
        VecCopy(mPose.GetMiddle04R(), data.GetMiddle04R(), mDims);
        VecCopy(mPose.GetRing01R(), data.GetRing01R(), mDims);
        VecCopy(mPose.GetRing02R(), data.GetRing02R(), mDims);
        VecCopy(mPose.GetRing03R(), data.GetRing03R(), mDims);
        VecCopy(mPose.GetRing04R(), data.GetRing04R(), mDims);
        VecCopy(mPose.GetPinky01R(), data.GetPinky01R(), mDims);
        VecCopy(mPose.GetPinky02R(), data.GetPinky02R(), mDims);
        VecCopy(mPose.GetPinky03R(), data.GetPinky03R(), mDims);
        VecCopy(mPose.GetPinky04R(), data.GetPinky04R(), mDims);

    }

}


void SkeletonFactory::EstimateSkeletonTarget(float* target, 
    float* base, float length, float* TargetPose, float* BasePose) {

    float dvec[mDims];
    float shift[mDims];

    EstimateUnitVector(dvec, TargetPose, BasePose);
    // Avoid NAN situation comes from invalid finger data at beginning
    if (isnan(dvec[0])) VecSet(dvec, 1.0, 0.0, 0.0);

    VecMultiply(shift, dvec, length);
    VecAdd(target, base, shift);

}

void SkeletonFactory::EstimateMpBones() {

    mSkelP->SetHasFace(mPose.HasFace());
    mSkelP->SetHasBody(mPose.HasBody());
    mSkelP->SetHasLeftHand(mPose.HasLeftHand());
    mSkelP->SetHasRightHand(mPose.HasRightHand());

    // Pelvis
    VecCopy(mSkelP->GetPelvis(), mPose.GetPelvis(), mDims);

    // Spine
    EstimateSkeletonTarget(mSkelP->GetSpine01(), mSkelP->GetPelvis(),
        mSkelP->GetLenSpine01(), mPose.GetSpine01(), mPose.GetPelvis());

    EstimateSkeletonTarget(mSkelP->GetSpine02(), mSkelP->GetSpine01(),
        mSkelP->GetLenSpine02(), mPose.GetSpine02(), mPose.GetSpine01());

    EstimateSkeletonTarget(mSkelP->GetSpine03(), mSkelP->GetSpine02(),
        mSkelP->GetLenSpine03(), mPose.GetSpine03(), mPose.GetSpine02());

    // Neck
    EstimateSkeletonTarget(mSkelP->GetNeck01(), mSkelP->GetSpine03(),
        mSkelP->GetLenNeck01(), mPose.GetNeck01(), mPose.GetSpine03());

    // Head
    EstimateSkeletonTarget(mSkelP->GetHead(), mSkelP->GetNeck01(),
        mSkelP->GetLenHead(), mPose.GetHead(), mPose.GetNeck01());

    // Nose (auxiliary component)
    EstimateSkeletonTarget(mSkelP->GetNose(), mSkelP->GetHead(),
        mSkelP->GetLenNose(), mPose.GetNose(), mPose.GetHead());

    // Ear (auxiliary component)
    EstimateSkeletonTarget(mSkelP->GetEarL(), mSkelP->GetHead(),
        mSkelP->GetLenEar(), mPose.GetEarL(), mPose.GetHead());
    EstimateSkeletonTarget(mSkelP->GetEarR(), mSkelP->GetHead(),
        mSkelP->GetLenEar(), mPose.GetEarR(), mPose.GetHead());


    // Clavicle
    EstimateSkeletonTarget(mSkelP->GetClavicleL(), mSkelP->GetSpine03(),
        mSkelP->GetLenSpine03ToClavicle(), mPose.GetClavicleL(), mPose.GetSpine03());

    EstimateSkeletonTarget(mSkelP->GetClavicleR(), mSkelP->GetSpine03(),
        mSkelP->GetLenSpine03ToClavicle(), mPose.GetClavicleR(), mPose.GetSpine03());

    // Upper arm
    EstimateSkeletonTarget(mSkelP->GetUpperarmL(), mSkelP->GetClavicleL(),
        mSkelP->GetLenClavicle(), mPose.GetUpperarmL(), mPose.GetClavicleL());

    EstimateSkeletonTarget(mSkelP->GetUpperarmR(), mSkelP->GetClavicleR(),
        mSkelP->GetLenClavicle(), mPose.GetUpperarmR(), mPose.GetClavicleR());

    // Lower arm
    EstimateSkeletonTarget(mSkelP->GetLowerarmL(), mSkelP->GetUpperarmL(),
        mSkelP->GetLenUpperarm(), mPose.GetLowerarmL(), mPose.GetUpperarmL());

    EstimateSkeletonTarget(mSkelP->GetLowerarmR(), mSkelP->GetUpperarmR(),
        mSkelP->GetLenUpperarm(), mPose.GetLowerarmR(), mPose.GetUpperarmR());

    // Hands
    EstimateSkeletonTarget(mSkelP->GetHandL(), mSkelP->GetLowerarmL(),
        mSkelP->GetLenLowerarm(), mPose.GetHandL(), mPose.GetLowerarmL());

    EstimateSkeletonTarget(mSkelP->GetHandR(), mSkelP->GetLowerarmR(),
        mSkelP->GetLenLowerarm(), mPose.GetHandR(), mPose.GetLowerarmR());

    // Thigh
    EstimateSkeletonTarget(mSkelP->GetThighL(), mSkelP->GetPelvis(),
        mSkelP->GetLenPelvisToThigh(), mPose.GetThighL(), mPose.GetPelvis());

    EstimateSkeletonTarget(mSkelP->GetThighR(), mSkelP->GetPelvis(),
        mSkelP->GetLenPelvisToThigh(), mPose.GetThighR(), mPose.GetPelvis());

    // Calf
    EstimateSkeletonTarget(mSkelP->GetCalfL(), mSkelP->GetThighL(),
        mSkelP->GetLenThigh(), mPose.GetCalfL(), mPose.GetThighL());

    EstimateSkeletonTarget(mSkelP->GetCalfR(), mSkelP->GetThighR(),
        mSkelP->GetLenThigh(), mPose.GetCalfR(), mPose.GetThighR());

    // Foot
    EstimateSkeletonTarget(mSkelP->GetFootL(), mSkelP->GetCalfL(),
        mSkelP->GetLenCalf(), mPose.GetFootL(), mPose.GetCalfL());

    EstimateSkeletonTarget(mSkelP->GetFootR(), mSkelP->GetCalfR(),
        mSkelP->GetLenCalf(), mPose.GetFootR(), mPose.GetCalfR());

    // Ball
    EstimateSkeletonTarget(mSkelP->GetBallL(), mSkelP->GetFootL(),
        mSkelP->GetLenFoot(), mPose.GetBallL(), mPose.GetFootL());

    EstimateSkeletonTarget(mSkelP->GetBallR(), mSkelP->GetFootR(),
        mSkelP->GetLenFoot(), mPose.GetBallR(), mPose.GetFootR());


    // Left fingers
    if (mSkelP->HasLeftHand()) {
        EstimateSkeletonTarget(mSkelP->GetThumb01L(), mSkelP->GetHandL(),
            mSkelP->GetLenThumb01(), mPose.GetThumb01L(), mPose.GetHandL());
        EstimateSkeletonTarget(mSkelP->GetThumb02L(), mSkelP->GetThumb01L(),
            mSkelP->GetLenThumb02(), mPose.GetThumb02L(), mPose.GetThumb01L());
        EstimateSkeletonTarget(mSkelP->GetThumb03L(), mSkelP->GetThumb02L(),
            mSkelP->GetLenThumb03(), mPose.GetThumb03L(), mPose.GetThumb02L());
        EstimateSkeletonTarget(mSkelP->GetThumb04L(), mSkelP->GetThumb03L(),
            mSkelP->GetLenThumb04(), mPose.GetThumb04L(), mPose.GetThumb03L());
    
        EstimateSkeletonTarget(mSkelP->GetIndex01L(), mSkelP->GetHandL(),
            mSkelP->GetLenIndex01(), mPose.GetIndex01L(), mPose.GetHandL());
        EstimateSkeletonTarget(mSkelP->GetIndex02L(), mSkelP->GetIndex01L(),
            mSkelP->GetLenIndex02(), mPose.GetIndex02L(), mPose.GetIndex01L());
        EstimateSkeletonTarget(mSkelP->GetIndex03L(), mSkelP->GetIndex02L(),
            mSkelP->GetLenIndex03(), mPose.GetIndex03L(), mPose.GetIndex02L());
        EstimateSkeletonTarget(mSkelP->GetIndex04L(), mSkelP->GetIndex03L(),
            mSkelP->GetLenIndex04(), mPose.GetIndex04L(), mPose.GetIndex03L());
    
        EstimateSkeletonTarget(mSkelP->GetMiddle01L(), mSkelP->GetHandL(),
            mSkelP->GetLenMiddle01(), mPose.GetMiddle01L(), mPose.GetHandL());
        EstimateSkeletonTarget(mSkelP->GetMiddle02L(), mSkelP->GetMiddle01L(),
            mSkelP->GetLenMiddle02(), mPose.GetMiddle02L(), mPose.GetMiddle01L());
        EstimateSkeletonTarget(mSkelP->GetMiddle03L(), mSkelP->GetMiddle02L(),
            mSkelP->GetLenMiddle03(), mPose.GetMiddle03L(), mPose.GetMiddle02L());
        EstimateSkeletonTarget(mSkelP->GetMiddle04L(), mSkelP->GetMiddle03L(),
            mSkelP->GetLenMiddle04(), mPose.GetMiddle04L(), mPose.GetMiddle03L());
    
        EstimateSkeletonTarget(mSkelP->GetRing01L(), mSkelP->GetHandL(),
            mSkelP->GetLenRing01(), mPose.GetRing01L(), mPose.GetHandL());
        EstimateSkeletonTarget(mSkelP->GetRing02L(), mSkelP->GetRing01L(),
            mSkelP->GetLenRing02(), mPose.GetRing02L(), mPose.GetRing01L());
        EstimateSkeletonTarget(mSkelP->GetRing03L(), mSkelP->GetRing02L(),
            mSkelP->GetLenRing03(), mPose.GetRing03L(), mPose.GetRing02L());
        EstimateSkeletonTarget(mSkelP->GetRing04L(), mSkelP->GetRing03L(),
            mSkelP->GetLenRing04(), mPose.GetRing04L(), mPose.GetRing03L());
    
        EstimateSkeletonTarget(mSkelP->GetPinky01L(), mSkelP->GetHandL(),
            mSkelP->GetLenPinky01(), mPose.GetPinky01L(), mPose.GetHandL());
        EstimateSkeletonTarget(mSkelP->GetPinky02L(), mSkelP->GetPinky01L(),
            mSkelP->GetLenPinky02(), mPose.GetPinky02L(), mPose.GetPinky01L());
        EstimateSkeletonTarget(mSkelP->GetPinky03L(), mSkelP->GetPinky02L(),
            mSkelP->GetLenPinky03(), mPose.GetPinky03L(), mPose.GetPinky02L());
        EstimateSkeletonTarget(mSkelP->GetPinky04L(), mSkelP->GetPinky03L(),
            mSkelP->GetLenPinky04(), mPose.GetPinky04L(), mPose.GetPinky03L());
    }
    
    // Right fingers
    if (mSkelP->HasRightHand()) {

        EstimateSkeletonTarget(mSkelP->GetThumb01R(), mSkelP->GetHandR(),
            mSkelP->GetLenThumb01(), mPose.GetThumb01R(), mPose.GetHandR());
        EstimateSkeletonTarget(mSkelP->GetThumb02R(), mSkelP->GetThumb01R(),
            mSkelP->GetLenThumb02(), mPose.GetThumb02R(), mPose.GetThumb01R());
        EstimateSkeletonTarget(mSkelP->GetThumb03R(), mSkelP->GetThumb02R(),
            mSkelP->GetLenThumb03(), mPose.GetThumb03R(), mPose.GetThumb02R());
        EstimateSkeletonTarget(mSkelP->GetThumb04R(), mSkelP->GetThumb03R(),
            mSkelP->GetLenThumb04(), mPose.GetThumb04R(), mPose.GetThumb03R());
    
        EstimateSkeletonTarget(mSkelP->GetIndex01R(), mSkelP->GetHandR(),
            mSkelP->GetLenIndex01(), mPose.GetIndex01R(), mPose.GetHandR());
        EstimateSkeletonTarget(mSkelP->GetIndex02R(), mSkelP->GetIndex01R(),
            mSkelP->GetLenIndex02(), mPose.GetIndex02R(), mPose.GetIndex01R());
        EstimateSkeletonTarget(mSkelP->GetIndex03R(), mSkelP->GetIndex02R(),
            mSkelP->GetLenIndex03(), mPose.GetIndex03R(), mPose.GetIndex02R());
        EstimateSkeletonTarget(mSkelP->GetIndex04R(), mSkelP->GetIndex03R(),
            mSkelP->GetLenIndex04(), mPose.GetIndex04R(), mPose.GetIndex03R());
    
        EstimateSkeletonTarget(mSkelP->GetMiddle01R(), mSkelP->GetHandR(),
            mSkelP->GetLenMiddle01(), mPose.GetMiddle01R(), mPose.GetHandR());
        EstimateSkeletonTarget(mSkelP->GetMiddle02R(), mSkelP->GetMiddle01R(),
            mSkelP->GetLenMiddle02(), mPose.GetMiddle02R(), mPose.GetMiddle01R());
        EstimateSkeletonTarget(mSkelP->GetMiddle03R(), mSkelP->GetMiddle02R(),
            mSkelP->GetLenMiddle03(), mPose.GetMiddle03R(), mPose.GetMiddle02R());
        EstimateSkeletonTarget(mSkelP->GetMiddle04R(), mSkelP->GetMiddle03R(),
            mSkelP->GetLenMiddle04(), mPose.GetMiddle04R(), mPose.GetMiddle03R());
    
        EstimateSkeletonTarget(mSkelP->GetRing01R(), mSkelP->GetHandR(),
            mSkelP->GetLenRing01(), mPose.GetRing01R(), mPose.GetHandR());
        EstimateSkeletonTarget(mSkelP->GetRing02R(), mSkelP->GetRing01R(),
            mSkelP->GetLenRing02(), mPose.GetRing02R(), mPose.GetRing01R());
        EstimateSkeletonTarget(mSkelP->GetRing03R(), mSkelP->GetRing02R(),
            mSkelP->GetLenRing03(), mPose.GetRing03R(), mPose.GetRing02R());
        EstimateSkeletonTarget(mSkelP->GetRing04R(), mSkelP->GetRing03R(),
            mSkelP->GetLenRing04(), mPose.GetRing04R(), mPose.GetRing03R());
    
        EstimateSkeletonTarget(mSkelP->GetPinky01R(), mSkelP->GetHandR(),
            mSkelP->GetLenPinky01(), mPose.GetPinky01R(), mPose.GetHandR());
        EstimateSkeletonTarget(mSkelP->GetPinky02R(), mSkelP->GetPinky01R(),
            mSkelP->GetLenPinky02(), mPose.GetPinky02R(), mPose.GetPinky01R());
        EstimateSkeletonTarget(mSkelP->GetPinky03R(), mSkelP->GetPinky02R(),
            mSkelP->GetLenPinky03(), mPose.GetPinky03R(), mPose.GetPinky02R());
        EstimateSkeletonTarget(mSkelP->GetPinky04R(), mSkelP->GetPinky03R(),
            mSkelP->GetLenPinky04(), mPose.GetPinky04R(), mPose.GetPinky03R());

    }
    
}

void SkeletonFactory::EstimateQuat(int boneIndex, float* dvec1Init, float* dvec2Init) {

    float* quat = mSkelP->GetQuat(boneIndex); 

    mSkelP->SetDvec1Init(boneIndex, dvec1Init);
    mSkelP->SetDvec2Init(boneIndex, dvec2Init);

    mSkelP->EstimateJointQuat(quat, boneIndex, dvec1Init, dvec2Init);

}

void SkeletonFactory::EstimateQuatWithRowOnly(int boneIndex, float* dvec2Init) {

    float* quat = mSkelP->GetQuat(boneIndex); 

    mSkelP->SetDvec2Init(boneIndex, dvec2Init);

    mSkelP->EstimateJointQuatWithRowOnly(quat, boneIndex, dvec2Init);

}

void SkeletonFactory::EstimateQuatWithoutRow(int boneIndex, float* dvec1Init) {

    float* quat = mSkelP->GetQuat(boneIndex); 

    mSkelP->SetDvec1Init(boneIndex, dvec1Init);

    mSkelP->EstimateJointQuatWithoutRow(quat, boneIndex, dvec1Init);

}

void SkeletonFactory::EstimateMpQuats(Holistic &data) {
    // Estimate Mediapipe bone quaternions.

    float* quat;
    float bodyYaw;

    // Bone directions
    mSkelP->EstimatePelvisDirection();
    mSkelP->EstimateSpine01Direction();
    mSkelP->EstimateSpine02Direction();
    mSkelP->EstimateSpine03Direction();
    mSkelP->EstimateNeck01Direction();
    mSkelP->EstimateHeadDirection();

    mSkelP->EstimateClavicleLDirection();
    mSkelP->EstimateClavicleRDirection();

    mSkelP->EstimateUpperarmLDirection();
    mSkelP->EstimateUpperarmRDirection();

    mSkelP->EstimateLowerarmLDirection();
    mSkelP->EstimateLowerarmRDirection();

    mSkelP->EstimateHandLDirection();
    mSkelP->EstimateHandRDirection();

    mSkelP->EstimateThighLDirection();
    mSkelP->EstimateThighRDirection();

    mSkelP->EstimateCalfLDirection();
    mSkelP->EstimateCalfRDirection();

    mSkelP->EstimateFootLDirection();
    mSkelP->EstimateFootRDirection();

    mSkelP->EstimateFingersLDirection();
    mSkelP->EstimateFingersRDirection();

    // Bone quaternion
    float dvec1Init[mDims]; 
    float dvec2Init[mDims]; 

    // Pelvis, spine01, spine02, spine03, neck01
    VecSet(dvec1Init, 0.0, -1.0, 0.0);
    VecSet(dvec2Init, 0.0, 0.0, -1.0);

    EstimateQuatWithRowOnly(mSkelP->GetIPelvis(), dvec2Init);
    // Apply Kalman filter on Pelvis
    quat = mSkelP->GetQuat(mSkelP->GetIPelvis());

    // 修正轉動角度 [lc add start]
    float angleAxis[4];
    ConvertQuatToAngleAxis(quat, angleAxis);
    float angleDeg = RadianToDegree(angleAxis[0]);
    // actual = 0~45
    if (angleDeg <= 75.0) { //frame no = #114 for TurnBody.mp4
        //angleDeg = (angleDeg - 15.0)*0.75 + 0.0;
        angleDeg = (angleDeg - 15.0)*0.35 + 0.0;
    } // actual = 45~90
    else if (angleDeg <= 93.0) { //#125
        angleDeg = (angleDeg - 75.0)*3.0 + 45.0;
    } // actual = 90~135
    else if (angleDeg <= 105.0) { //#136
        angleDeg = (angleDeg - 93.0)*4.5 + 90.0;
    } // actual = 135~180
    //else if (angleDeg <= 150.0) { //#146
    else {
        angleDeg = (angleDeg - 105.0)*1.0 + 135.0;
    }

    angleAxis[0] = DegreeToRadian (angleDeg);
    ConvertAngleAxisToQuat(angleAxis, quat);

    // dbg
    /*ConvertQuatToAngleAxis(quat, angleAxis);
    angleDeg = RadianToDegree(angleAxis[0]);
    cout << "Pelvis AngleAxis: " << angleDeg << ", " << angleAxis[1] << ", " << angleAxis[2] << ", " << angleAxis[3] << endl;  
    */
    // [lc add end]

   
    /*
    mPelvisQuatSmoother.Update(quat);
    mPelvisQuatSmoother.GetUpdatedQuat(quat);
    */ 

    EstimateQuat(mSkelP->GetISpine01(), dvec1Init, dvec2Init);

    /*
    // Apply smoother on Spine01
    quat = mSkelP->GetQuat(mSkelP->GetISpine01());
    mSpine01QuatSmoother.Update(quat);
    mSpine01QuatSmoother.GetUpdatedQuat(quat);
    */

    EstimateQuat(mSkelP->GetISpine02(), dvec1Init, dvec2Init);

    /*
    // Apply smoother on Spine02
    quat = mSkelP->GetQuat(mSkelP->GetISpine02());
    mSpine02QuatSmoother.Update(quat);
    mSpine02QuatSmoother.GetUpdatedQuat(quat);
    */

    EstimateQuat(mSkelP->GetISpine03(), dvec1Init, dvec2Init);

    /*
    // Apply smoother on Spine03
    quat = mSkelP->GetQuat(mSkelP->GetISpine03());
    mSpine03QuatSmoother.Update(quat);
    mSpine03QuatSmoother.GetUpdatedQuat(quat);
    */

    // Neck
    quat = mSkelP->GetQuat(mSkelP->GetINeck01());
    VecCopy(quat, mSkelP->GetQuatPelvis(), 4);
    //EstimateQuat(mSkelP->GetINeck01(), dvec1Init, dvec2Init);
   
    /*
    // Apply smoother on Neck01
    quat = mSkelP->GetQuat(mSkelP->GetINeck01());
    mNeck01QuatSmoother.Update(quat);
    mNeck01QuatSmoother.GetUpdatedQuat(quat);
    */ 

    // Head
    bodyYaw = mSkelP->GetBodyYaw();
    float bodyYawC = 80.0; 
    if (abs(bodyYaw) < bodyYawC) {
        EstimateQuat(mSkelP->GetIHead(), dvec1Init, dvec2Init);
    } else {
        quat = mSkelP->GetQuat(mSkelP->GetIHead());
        VecCopy(quat, mSkelP->GetQuatPelvis(), 4);
    }
    
    // Apply smoother on Head
    quat = mSkelP->GetQuat(mSkelP->GetIHead());
    
    WeightedHeadQuat(quat , data );

    mHeadQuatSmoother.Update(quat);
    mHeadQuatSmoother.GetUpdatedQuat(quat);

    // Left clavicle
    VecSet(dvec1Init, 1.0, 0.0, 0.0);
    VecSet(dvec2Init, 0.0, 0.0, -1.0);
    EstimateQuat(mSkelP->GetIClavicleL(), dvec1Init, dvec2Init);

    // Right clavicle
    VecSet(dvec1Init, -1.0, 0.0, 0.0);
    VecSet(dvec2Init, 0.0, 0.0, -1.0);
    EstimateQuat(mSkelP->GetIClavicleR(), dvec1Init, dvec2Init);

    // Left upperarm
    VecSet(dvec1Init, 1.0, 0.0, 0.0);
    VecSet(dvec2Init, 0.0, 0.0, -1.0);

    EstimateQuatWithoutRow(mSkelP->GetIUpperarmL(), dvec1Init);

    // Left lowerarm
    VecSet(dvec1Init, 1.0, 0.0, 0.0);
    VecSet(dvec2Init, 0.0, -1.0, 0.0);

    EstimateQuatWithoutRow(mSkelP->GetILowerarmL(), dvec1Init);

    if (mSkelP->HasLeftHand()) {

        // Left hand
        VecSet(dvec1Init, 1.0, 0.0, 0.0);
        VecSet(dvec2Init, 0.0, -1.0, 0.0);

        EstimateQuat(mSkelP->GetIHandL(), dvec1Init, dvec2Init);

    }

    // Right upperarm
    VecSet(dvec1Init, -1.0, 0.0, 0.0);
    VecSet(dvec2Init, 0.0, 0.0, -1.0);

    EstimateQuatWithoutRow(mSkelP->GetIUpperarmR(), dvec1Init);

    // Right lowerarm
    VecSet(dvec1Init, -1.0, 0.0, 0.0);
    VecSet(dvec2Init, 0.0, -1.0, 0.0);

    EstimateQuatWithoutRow(mSkelP->GetILowerarmR(), dvec1Init);

    if (mSkelP->HasRightHand()) {

        // Right hand
        VecSet(dvec1Init, -1.0, 0.0, 0.0);
        VecSet(dvec2Init, 0.0, -1.0, 0.0);

        EstimateQuat(mSkelP->GetIHandR(), dvec1Init, dvec2Init);

    }

    // Thighs
    VecSet(dvec1Init, 0.0, 1.0, 0.0);
    VecSet(dvec2Init, 0.0, 0.0, -1.0);
    EstimateQuat(mSkelP->GetIThighL(), dvec1Init, dvec2Init);
    EstimateQuat(mSkelP->GetIThighR(), dvec1Init, dvec2Init);

    // Left calf
    VecSet(dvec1Init, 0.0, 1.0, 0.0);
    VecSet(dvec2Init, 1.0, 0.0, 0.0);
    EstimateQuat(mSkelP->GetICalfL(), dvec1Init, dvec2Init);

    // Right calf
    VecSet(dvec1Init, 0.0, 1.0, 0.0);
    VecSet(dvec2Init, 1.0, 0.0, 0.0);
    EstimateQuat(mSkelP->GetICalfR(), dvec1Init, dvec2Init);

    // Left foot
    VecSet(dvec1Init, 0.0, 0.0, -1.0);
    VecSet(dvec2Init, 1.0, 0.0, 0.0);
    EstimateQuat(mSkelP->GetIFootL(), dvec1Init, dvec2Init);

    // Right foot
    VecSet(dvec1Init, 0.0, 0.0, -1.0);
    VecSet(dvec2Init, 1.0, 0.0, 0.0);
    EstimateQuat(mSkelP->GetIFootR(), dvec1Init, dvec2Init);

    const int numFingers = 5;
    const int numFingerJoints = 4;
    int i, j, k;
    int iStart;

    // Left fingers
    if (mSkelP->HasLeftHand()) {

        VecSet(dvec1Init, 1.0, 0.0, 0.0);
        VecSet(dvec2Init, 0.0, 0.0, -1.0);
    
        iStart = mSkelP->GetIThumb01L();
        for (i = 0; i < numFingers; i++) { // Finger
            for (j = 0; j < numFingerJoints-1; j++) { // Finget joint
    
                k = iStart + i*numFingerJoints + j;
                EstimateQuatWithoutRow(k, dvec1Init);
                //EstimateQuat(k, dvec1Init, dvec2Init);
    
            }
        }
    }    
    
    // Right fingers
    if (mSkelP->HasRightHand()) {

        VecSet(dvec1Init, -1.0, 0.0, 0.0);
        VecSet(dvec2Init, 0.0, 0.0, -1.0);
    
        iStart = mSkelP->GetIThumb01R();
        for (i = 0; i < numFingers; i++) { // Finger
            for (j = 0; j < numFingerJoints-1; j++) { // Finget joint
    
                k = iStart + i*numFingerJoints + j;
                EstimateQuatWithoutRow(k, dvec1Init);
                //EstimateQuat(k, dvec1Init, dvec2Init);
    
            }
        }
    }


    // Auxiliary directions
    mSkelP->EstimatePalmLDirection();
    mSkelP->EstimatePalmRDirection();

}

void SkeletonFactory::ConfineMpQuats() {
    // Estimate Mediapipe bone quaternions.


}

void SkeletonFactory::ToUnrealAxes(float* p) {
    /*
        Map point from Mediapipe to Unreal axes. 
        xU = xMp, yU = -zMp, zU = -yMp
    */    
    
    float y = p[1];
    float z = p[2];

    p[1] = -z + 0.5;
    p[2] = -y + 1.0;

}

void SkeletonFactory::ToUnrealQuat(float* q) {
    // Convert MP quaternion to Unreal quaternion.

    // Do nothing

}

void SkeletonFactory::ToUnrealDirection(float* Dvec) {
    // Convet the direction from Mediapipe to Unreal coordinates

    Dvec[1] = -Dvec[2];
    Dvec[2] = -Dvec[1];

}

void SkeletonFactory::ToUnityAxes(float* p) {
    /*
        Map point from Mediapipe to Unity axes. 
        xU = xMp, yU = -yMp, zU = zMp
    */    
    
    p[1] = -p[1];

}

void SkeletonFactory::ToUnityQuat(float* q) {
    // Convert MP quaternion to Unity quaternion.

    // Do nothing

}

void SkeletonFactory::ToUnityDirection(float* Dvec) {
    // Convet the direction from Mediapipe to Unity coordinates

    Dvec[1] = -Dvec[1];

}

void SkeletonFactory::ToUnrealSkeleton() {

    int numBones = mSkelP->GetNumBones();
    int dims = mSkelP->GetDims();
    float* pBone;
    float* pQuat;
    
    // Convert axes
    for (int i=0; i < numBones; i++) {
        pBone = mSkelP->GetBone(i);
        ToUnrealAxes(pBone);
    }

    // Convert quaternions
    for (int i=0; i < numBones; i++) {
        pQuat = mSkelP->GetQuat(i);
        ToUnrealQuat(pQuat);
    }

    // Correct palm direction due to left-hand coordinates
    ToUnrealDirection(mSkelP->GetLeftPalmDirection());
    ToUnrealDirection(mSkelP->GetRightPalmDirection());

}

void SkeletonFactory::ToUnitySkeleton() {

    int numBones = mSkelP->GetNumBones();
    int dims = mSkelP->GetDims();
    float* pBone;
    float* pQuat;

    // Convert axes
    for (int i=0; i < numBones; i++) {
        pBone = mSkelP->GetBone(i);
        ToUnityAxes(pBone);
    }

    // Convert quaternions
    for (int i=0; i < numBones; i++) {
        pQuat = mSkelP->GetQuat(i);
        ToUnityQuat(pQuat);
    }

    // Correct palm direction due to left-hand coordinates
    ToUnityDirection(mSkelP->GetLeftPalmDirection());
    ToUnityDirection(mSkelP->GetRightPalmDirection());

}


void SkeletonFactory::Produce( Holistic &data  ,Skeleton *pSkel, string engineName) {
    /* 
    Produce skeleton.
    pSkel: pointer of skeleton.
    engineName: Engine name. 
        e.g. 'unreal', 'unity', 'mediapipe' 
    */

    mSkelP = pSkel;

    // Bones
    EstimateMpBones();

    // Quaternions
    EstimateMpQuats(data);

    // Apply constraints on quaternion
    ConfineMpQuats();

    /*
    if (engineName == "unreal") {
        ToUnrealSkeleton();
    } else {
        if (engineName == "unity") {
            ToUnitySkeleton();
        } else {
            cout << "Warning: Use Mediapipe as the core engine." << endl;
        }
    }
    */

}

void SkeletonFactory::SetIsShortDistance(bool Value) {
    mIsShortDistance = Value;
}

bool SkeletonFactory::IsShortDistance() {
    return mIsShortDistance;
}

void SkeletonFactory::DebugBoneRotation(int boneIndex, float* dvec1Init, float* dvec2Init) {

    float* quat = mSkelP->GetQuat(boneIndex);

    VecCopy(dvec1Init, mSkelP->GetDvec1Init(boneIndex), 3);
    VecCopy(dvec2Init, mSkelP->GetDvec2Init(boneIndex), 3);
    float* dvec1 = mSkelP->GetDvec1(boneIndex);
    float* dvec2 = mSkelP->GetDvec2(boneIndex);

    float dvec1Rotated[3], dvec2Rotated[3]; 
    EstimateRotatedVector(dvec1Rotated, dvec1Init, quat);
    EstimateRotatedVector(dvec2Rotated, dvec2Init, quat);

    float euler[3];
    ConvertQuatToEulerXYZ(quat, euler); // XYZ order
    for (int i=0; i < 3; i++) {
        euler[i] = RadianToDegree(euler[i]);
    }

    float angleAxis[4];
    ConvertQuatToAngleAxis(quat, angleAxis);
    angleAxis[0] = RadianToDegree(angleAxis[0]);

    DbPrintArray("dvec1: ", dvec1, 3);
    DbPrintArray("dvec2: ", dvec2, 3);
    DbPrintArray("quat: ", quat, 4);
    DbPrintArray("angleAxis: ", angleAxis, 4);
    DbPrintArray("euler: ", euler, 3);
    DbPrintArray("dvec1Rotated: ", dvec1Rotated, 3);
    DbPrintArray("dvec2Rotated: ", dvec2Rotated, 3);

}

void SkeletonFactory::DebugBonePosition(Skeleton* pSkel) {

    cout << "Debug bone position ----" << endl;

    int numBones = pSkel->NumBones;
    int dims = pSkel->Dims;
    int quatDims = pSkel->QuatDims;

    float value;
    for (int i=0; i < numBones; i++) {
        for (int j=0; j < dims; j++) {

            value = pSkel->GetBone(i)[j];
            if (isnan(value)) {
                cout << "There is NAN at bone, i =" << i << ", j = " << j << endl;
            }
        }
    }

    for (int i=0; i < numBones; i++) {
        for (int j=0; j < quatDims; j++) {

            value = pSkel->GetQuat(i)[j];
            if (isnan(value)) {
                cout << "There is NAN at quat, i =" << i << ", j = " << j << endl;
            }
        }
    }

}

void SkeletonFactory::EstimateQuatFromPoseOnly(float* quat ,Holistic &data )
{

    //
    // float dvec1[3];
    // float dvec2[3];

    // float vecEarREarL[3] = {0.0 , 0.0 , 0.0 };
    // math_utils::VecSubstractNorm(vecEarREarL ,mSkelP->GetEarR() , mSkelP->GetEarL());
    // float EarR_coor[3];
    // float EarL_coor[3];
    // math_utils::VecCopy(EarR_coor, mSkelP->GetEarR());
    // math_utils::VecCopy(EarL_coor, mSkelP->GetEarL());
    // float Ear_middle[3] = { (EarR_coor[0] + EarL_coor[0])*0.5 , 
    //                         (EarR_coor[1] + EarL_coor[1])*0.5 , 
    //                         (EarR_coor[2] + EarL_coor[2])*0.5  };

    // float vecNoseHeadTemp[3] = {0.0 , 0.0 , 0.0 };
    // math_utils::VecSubstractNorm(vecNoseHeadTemp ,mSkelP->GetNose() , Ear_middle);
  
    // float vecHeadNeck[3] = {0.0 , 0.0 , 0.0 };
    // math_utils::VecCrossNorm(vecHeadNeck , vecEarREarL , vecNoseHeadTemp);
 
    // float vecNoseHead[3] = {0.0 , 0.0 , 0.0 };
    // math_utils::VecCrossNorm(vecNoseHead , vecHeadNeck , vecEarREarL);

    // math_utils::VecCopy(dvec1, vecHeadNeck);
    // math_utils::VecCopy(dvec2, vecNoseHead);
    //

    //RAW DATA VEC RESULT
    float Nose_Landmark[3] = {0,0,0} ;
    float EarR_Landmark[3] = {0,0,0} ;
    float EarL_Landmark[3] = {0,0,0} ;
    math_utils::VecCopy(Nose_Landmark , data.pose[0] , 3);
    math_utils::VecCopy(EarR_Landmark , data.pose[7] , 3);
    math_utils::VecCopy(EarL_Landmark , data.pose[8] , 3);
    Nose_Landmark[0] = Nose_Landmark[0] * Iwidth;
    EarR_Landmark[0] = EarR_Landmark[0] * Iwidth;
    EarL_Landmark[0] = EarL_Landmark[0] * Iwidth;
    Nose_Landmark[1] = Nose_Landmark[1] * Iheight;
    EarR_Landmark[1] = EarR_Landmark[1] * Iheight;
    EarL_Landmark[1] = EarL_Landmark[1] * Iheight;
    Nose_Landmark[2] = Nose_Landmark[2] * Iwidth;
    EarR_Landmark[2] = EarR_Landmark[2] * Iwidth;
    EarL_Landmark[2] = EarL_Landmark[2] * Iwidth;
    // cout<<"Iwidth:"<<Iwidth<<endl;
    // cout<<"Iheight:"<<Iheight<<endl;
    // db_utils::DbPrintArray("Nose_Landmark" , Nose_Landmark , 3);
    // db_utils::DbPrintArray("EarR_Landmark" , EarR_Landmark , 3);
    // db_utils::DbPrintArray("EarL_Landmark" , EarL_Landmark , 3);
    
    float vecEarREarL_[3] = {0.0 , 0.0 , 0.0 };
    math_utils::VecSubstractNorm(vecEarREarL_ ,EarL_Landmark , EarR_Landmark);
    // db_utils::DbPrintArray("vecEarREarL_" , vecEarREarL_ , 3);
    float EarLandmarkMiddle[3] = {  (EarL_Landmark[0] + EarR_Landmark[0]) * 0.5 , 
                                    (EarL_Landmark[1] + EarR_Landmark[1]) * 0.5 ,
                                    (EarL_Landmark[2] + EarL_Landmark[2]) *0.5 };
    float vecNoseHeadTemp_[3] = {0.0 , 0.0 , 0.0 };
    math_utils::VecSubstractNorm(vecNoseHeadTemp_ , EarLandmarkMiddle , Nose_Landmark );
    float vecHeadNeck_[3] = {0.0 , 0.0 , 0.0};
    math_utils::VecCrossNorm(vecHeadNeck_ , vecNoseHeadTemp_ , vecEarREarL_);
    // db_utils::DbPrintArray("vecHeadNeck_" , vecHeadNeck_ , 3);

    float vecNoseHead_[3] = {0.0 ,0.0 ,0.0};
    math_utils::VecCrossNorm(vecNoseHead_ , vecHeadNeck_ ,vecEarREarL_  );
    // db_utils::DbPrintArray("vecNoseHead_" , vecNoseHead_ , 3);

    float dvec1[3];
    float dvec2[3];
    math_utils::VecCopy(dvec1, vecHeadNeck_);
    math_utils::VecCopy(dvec2, vecNoseHead_);
    //RAW DATA VEC RESULT






    float Posedvec1Init[3];
    float Posedvec2Init[3];
    math_utils::VecSet(Posedvec1Init, 0.0, -1.0, 0.0);
    math_utils::VecSet(Posedvec2Init, 0.0, 0.0, -1.0);

    float dvec2InitRotated[3];
    math_utils::VecSet(dvec2InitRotated, 0.0, 0.0, 0.0);
    float q1[4] = {1.0 , 0.0 , 0.0 ,0.0 };
    float q2[4] = {1.0 , 0.0 , 0.0 ,0.0 };
    math_utils::EstimateQuatFromTwoVectors(q1, Posedvec1Init, dvec1);
    math_utils::EstimateRotatedVector(dvec2InitRotated, Posedvec2Init, q1);
    math_utils::EstimateQuatFromTwoVectors(q2, dvec2InitRotated, dvec2);
    math_utils::EstimateQuatMultiply(quat, q2, q1);

    // db_utils::DbPrintArray("Ref_Quat_in_func-" , quat , 4);
    // cout<<"kk"<<endl;
}
  
void SkeletonFactory::SlerpQuat(float* quat_1 , float* quat_2 ,float t1 , float t2)
{
    float cos_phi = (quat_1[0]*quat_2[0]) + (quat_1[1]*quat_2[1]) + (quat_1[2]*quat_2[2]) + (quat_1[3]*quat_2[3]);
    // cout<<"cos_phi:"<<cos_phi<<endl;
   
    // cout<<"phi:"<<phi<<endl;
    if(cos_phi > 1)
    {
        cos_phi = 1;
        
    }
     float phi = acos(cos_phi);
    //  cout<<"acos(1):"<<acos(1)<<endl;
    // if (phi = 0)
    // {
    //     t1 = 0;
    // }
    // float s1 = sin((phi*(1-t1*t2)))/sin(phi);
    // float s2 = sin(phi*t1*t2);
    // for (int i=0 ; i <4 ; i ++)
    // {
    //     quat_1[i] = s1 * quat_1[i] + s2 * quat_2[i];
    // }
    if (phi > 0)
    {
        float s1 = sin((phi*(1-t1*t2)))/sin(phi);
        float s2 = sin(phi*t1*t2);
        for (int i=0 ; i <4 ; i ++)
        {
            quat_1[i] = s1 * quat_1[i] + s2 * quat_2[i];
        }
        // cout<<"slerp"<<endl;
    }


}

void SkeletonFactory::WeightedHeadQuat(float* quat ,Holistic &data)
{
    float SlperEuler[3];
    math_utils::QuatNorm(quat);
    
    math_utils::ConvertQuatToEulerXYZ(quat ,SlperEuler );

    // float SlerpT1 = M_PI - ((abs(SlperEuler[1]))/M_PI); 

    
    float  QuatFromPose[4];
    EstimateQuatFromPoseOnly(QuatFromPose , data);
    math_utils::QuatNorm(QuatFromPose);


    // float RollAxis[3] = {0, 0 , -1};
    // math_utils::EstimateRotatedVector(RollAxis , RollAxis ,quat);
    // float SlerpT1 = sqrt(RollAxis[0]*RollAxis[0] + RollAxis[1] *RollAxis[1]);
    // float SlerpT1 = abs(RollAxis[0]); 

    float PithchAxis[3] = { -1.0 , 0.0 , 0.0};
    math_utils::EstimateRotatedVector(PithchAxis , PithchAxis , quat);
    float SlerpT1 = sqrt(PithchAxis[0]*PithchAxis[0] + PithchAxis[1] *PithchAxis[1]);
    SlerpT1 = 1.0 - SlerpT1;
    if(SlerpT1 > S_Threshold)
    {
        SlerpT1 = 1.0;
    }
    // cout<<"S_Threshold:"<<S_Threshold<<endl;
    // cout<<"====="<<endl;
    // db_utils::DbPrintArray("Ori_Quat-" , quat , 4);
    // db_utils::DbPrintArray("Ref_Quat-" , QuatFromPose , 4);
    // cout<<"SlerpT1:"<<SlerpT1<<endl;

    SlerpQuat(quat , QuatFromPose ,SlerpT1 , 1);
    math_utils::QuatNorm(quat);
    // db_utils::DbPrintArray("fin_Quat-" , quat , 4);

}

void SkeletonFactory::LoadImageSize(float w , float h)
{
    Iwidth = w;
    Iheight = h ;

}

void SkeletonFactory::SetWeightingFactor(double s)
{
    S_Threshold = s ; 
}

