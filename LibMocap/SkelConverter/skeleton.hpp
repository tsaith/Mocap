#ifndef SKELETON_H
#define SKELETON_H

#include "Core/Math/MathLib.h"
#include "Utils/DebugUtils.h"

using namespace std;
using namespace zen_math;
using namespace db_utils;

class Skeleton {

public:

    Skeleton() {

        // Skeleton height 
        mHeight = 0.8;
    
        // Length of bones
        SetBoneLen(GetISpine01(), 0.05*mHeight);
        SetBoneLen(GetISpine02(), 0.1*mHeight);
        SetBoneLen(GetISpine03(), 0.1*mHeight);
        SetBoneLen(GetINeck01(), 0.1*mHeight);
        SetBoneLen(GetIHead(), 0.05*mHeight);
        mLenNose = 0.025*mHeight; // Auxiliary
        mLenEar = 0.05*mHeight; // Auxiliary
        mLenSpine03ToClavicle = 0.08*mHeight;
        SetBoneLen(GetIClavicleL(), 0.1*mHeight);
        SetBoneLen(GetIClavicleR(), 0.1*mHeight);
        SetBoneLen(GetIUpperarmL(), 0.15*mHeight);
        SetBoneLen(GetIUpperarmR(), 0.15*mHeight);
        SetBoneLen(GetILowerarmL(), 0.2*mHeight);
        SetBoneLen(GetILowerarmR(), 0.2*mHeight);
    
        mLenPelvisToThigh = 0.05*mHeight;
        SetBoneLen(GetIThighL(), 0.25*mHeight);
        SetBoneLen(GetIThighR(), 0.25*mHeight);
        SetBoneLen(GetICalfL(), 0.25*mHeight);
        SetBoneLen(GetICalfR(), 0.25*mHeight);
        SetBoneLen(GetIFootL(), 0.1*mHeight);
        SetBoneLen(GetIFootR(), 0.1*mHeight);

        SetBoneLen(GetIThumb01L(), 0.02*mHeight);
        SetBoneLen(GetIThumb01R(), 0.02*mHeight);
        SetBoneLen(GetIThumb02L(), 0.02*mHeight);
        SetBoneLen(GetIThumb02R(), 0.02*mHeight);
        SetBoneLen(GetIThumb03L(), 0.02*mHeight);
        SetBoneLen(GetIThumb03R(), 0.02*mHeight);
        SetBoneLen(GetIThumb04L(), 0.015*mHeight);
        SetBoneLen(GetIThumb04R(), 0.015*mHeight);
        SetBoneLen(GetIIndex01L(), 0.05*mHeight);
        SetBoneLen(GetIIndex01R(), 0.05*mHeight);
        SetBoneLen(GetIIndex02L(), 0.02*mHeight);
        SetBoneLen(GetIIndex02R(), 0.02*mHeight);
        SetBoneLen(GetIIndex03L(), 0.02*mHeight);
        SetBoneLen(GetIIndex03R(), 0.02*mHeight);
        SetBoneLen(GetIIndex04L(), 0.01*mHeight);
        SetBoneLen(GetIIndex04R(), 0.01*mHeight);
        SetBoneLen(GetIMiddle01L(), 0.05*mHeight);
        SetBoneLen(GetIMiddle01R(), 0.05*mHeight);
        SetBoneLen(GetIMiddle02L(), 0.022*mHeight);
        SetBoneLen(GetIMiddle02R(), 0.022*mHeight);
        SetBoneLen(GetIMiddle03L(), 0.022*mHeight);
        SetBoneLen(GetIMiddle03R(), 0.022*mHeight);
        SetBoneLen(GetIMiddle04L(), 0.012*mHeight);
        SetBoneLen(GetIMiddle04R(), 0.012*mHeight);
        SetBoneLen(GetIRing01L(), 0.05*mHeight);
        SetBoneLen(GetIRing01R(), 0.05*mHeight);
        SetBoneLen(GetIRing02L(), 0.02*mHeight);
        SetBoneLen(GetIRing02R(), 0.02*mHeight);
        SetBoneLen(GetIRing03L(), 0.02*mHeight);
        SetBoneLen(GetIRing03R(), 0.02*mHeight);
        SetBoneLen(GetIRing04L(), 0.01*mHeight);
        SetBoneLen(GetIRing04R(), 0.01*mHeight);
        SetBoneLen(GetIPinky01L(), 0.04*mHeight);
        SetBoneLen(GetIPinky01R(), 0.04*mHeight);
        SetBoneLen(GetIPinky02L(), 0.015*mHeight);
        SetBoneLen(GetIPinky02R(), 0.015*mHeight);
        SetBoneLen(GetIPinky03L(), 0.015*mHeight);
        SetBoneLen(GetIPinky03R(), 0.015*mHeight);
        SetBoneLen(GetIPinky04L(), 0.01*mHeight);
        SetBoneLen(GetIPinky04R(), 0.01*mHeight);

        // Initialize quaternions
        for (int i=0; i < NumBones; i++) {
            mQuats[i][0] = 1.0;
            mQuats[i][1] = 0.0;
            mQuats[i][2] = 0.0;
            mQuats[i][3] = 0.0;
        }

    }

    ~Skeleton() {

    }

    bool HasFace() {return mHasFace; } 
    bool HasBody() {return mHasBody; } 
    bool HasLeftHand() {return mHasLeftHand; } 
    bool HasRightHand() {return mHasRightHand; } 

    void SetHasFace(bool bVal) { mHasFace = bVal; } 
    void SetHasBody(bool bVal) { mHasBody = bVal; } 
    void SetHasLeftHand(bool bVal) { mHasLeftHand = bVal; } 
    void SetHasRightHand(bool bVal) { mHasRightHand = bVal; } 

    const int GetNumBones() { return NumBones; }
    const int GetDims() { return Dims; }
    const int GetQuatDims() { return QuatDims; }
    float* GetBones() { return &mBones[0][0]; }
    float* GetBone(int i) { return mBones[i]; }
    float* GetQuats() { return &mQuats[0][0]; }
    float* GetQuat(int i) { return mQuats[i]; }

    float* GetDvec1(int i) { return mDvec1[i]; }
    float* GetDvec2(int i) { return mDvec2[i]; }
    float* GetDvec1Init(int i) { return mDvec1Init[i]; }
    float* GetDvec2Init(int i) { return mDvec2Init[i]; }
    void SetDvec1Init(int i, float* dvec1) { VecCopy(mDvec1Init[i], dvec1, 3); }
    void SetDvec2Init(int i, float* dvec2) { VecCopy(mDvec2Init[i], dvec2, 3); }
    

    void SetBoneLen(int i, float len) { mBoneLens[i] = len; }
    float GetBoneLen(int i) { return mBoneLens[i]; }

    // Bone index
    static int GetIPelvis() { return mIPelvis; }        // 0
    static int GetISpine01() { return mISpine01; }      // 1
    static int GetISpine02() { return mISpine02; }      // 2
    static int GetISpine03() { return mISpine03; }      // 3
    static int GetINeck01() { return mINeck01; }        // 4
    static int GetIHead() { return mIHead; }            // 5

    static int GetIClavicleL() { return mIClavicleL; }  // 6
    static int GetIUpperarmL() { return mIUpperarmL; }  // 7
    static int GetILowerarmL() { return mILowerarmL; }  // 8
    static int GetILowerarmTwist01L() { return mILowerarmTwist01L; }    // 9
    static int GetIHandL() { return mIHandL; }          // 10

    static int GetIClavicleR() { return mIClavicleR; }  // 11
    static int GetIUpperarmR() { return mIUpperarmR; }  // 12
    static int GetILowerarmR() { return mILowerarmR; }  // 13
    static int GetILowerarmTwist01R() { return mILowerarmTwist01R; }    // 14
    static int GetIHandR() { return mIHandR; }          // 15

    static int GetIThighL() { return mIThighL; }        // 16
    static int GetICalfL() { return mICalfL; }          // 17
    static int GetICalfTwist01L() { return mICalfTwist01L; }    // 18
    static int GetIFootL() { return mIFootL; }          // 19
    static int GetIBallL() { return mIBallL; }          // 20

    static int GetIThighR() { return mIThighR; }        // 21
    static int GetICalfR() { return mICalfR; }          // 22
    static int GetICalfTwist01R() { return mICalfTwist01R; }    // 23
    static int GetIFootR() { return mIFootR; }          // 24
    static int GetIBallR() { return mIBallR; }          // 25

    static int GetIThumb01L() { return mIThumb01L; }    // 26
    static int GetIThumb02L() { return mIThumb02L; }    // 27
    static int GetIThumb03L() { return mIThumb03L; }    // 28
    static int GetIThumb04L() { return mIThumb04L; }    // 29
    static int GetIIndex01L() { return mIIndex01L; }   // 30
    static int GetIIndex02L() { return mIIndex02L; }   // 31
    static int GetIIndex03L() { return mIIndex03L; }   // 32
    static int GetIIndex04L() { return mIIndex04L; }   // 33
    static int GetIMiddle01L() { return mIMiddle01L; }  // 34
    static int GetIMiddle02L() { return mIMiddle02L; }  // 35
    static int GetIMiddle03L() { return mIMiddle03L; }  // 36
    static int GetIMiddle04L() { return mIMiddle04L; }  // 37
    static int GetIRing01L() { return mIRing01L; }      // 38
    static int GetIRing02L() { return mIRing02L; }      // 39
    static int GetIRing03L() { return mIRing03L; }      // 40
    static int GetIRing04L() { return mIRing04L; }      // 41
    static int GetIPinky01L() { return mIPinky01L; }    // 42
    static int GetIPinky02L() { return mIPinky02L; }    // 43
    static int GetIPinky03L() { return mIPinky03L; }    // 44
    static int GetIPinky04L() { return mIPinky04L; }    // 45

    static int GetIThumb01R() { return mIThumb01R; }    // 46
    static int GetIThumb02R() { return mIThumb02R; }    // 47
    static int GetIThumb03R() { return mIThumb03R; }    // 48
    static int GetIThumb04R() { return mIThumb04R; }    // 49
    static int GetIIndex01R() { return mIIndex01R; }   // 50
    static int GetIIndex02R() { return mIIndex02R; }   // 51
    static int GetIIndex03R() { return mIIndex03R; }   // 52
    static int GetIIndex04R() { return mIIndex04R; }   // 53
    static int GetIMiddle01R() { return mIMiddle01R; }  // 54
    static int GetIMiddle02R() { return mIMiddle02R; }  // 55
    static int GetIMiddle03R() { return mIMiddle03R; }  // 56
    static int GetIMiddle04R() { return mIMiddle04R; }  // 57
    static int GetIRing01R() { return mIRing01R; }      // 58
    static int GetIRing02R() { return mIRing02R; }      // 59
    static int GetIRing03R() { return mIRing03R; }      // 60
    static int GetIRing04R() { return mIRing04R; }      // 61
    static int GetIPinky01R() { return mIPinky01R; }    // 62
    static int GetIPinky02R() { return mIPinky02R; }    // 63
    static int GetIPinky03R() { return mIPinky03R; }    // 64
    static int GetIPinky04R() { return mIPinky04R; }    // 65

    // Bone position
    float* GetPelvis() { return mBones[mIPelvis]; }
    float* GetSpine01() { return mBones[mISpine01]; }
    float* GetSpine02() { return mBones[mISpine02]; }
    float* GetSpine03() { return mBones[mISpine03]; }
    float* GetNeck01() { return mBones[mINeck01]; }
    float* GetHead() { return mBones[mIHead]; }

    float* GetClavicleL() { return mBones[mIClavicleL]; }
    float* GetUpperarmL() { return mBones[mIUpperarmL]; }
    float* GetLowerarmL() { return mBones[mILowerarmL]; }
    float* GetLowerarmTwist01L() { return mBones[mILowerarmTwist01L]; }
    float* GetHandL() { return mBones[mIHandL]; }

    float* GetClavicleR() { return mBones[mIClavicleR]; }
    float* GetUpperarmR() { return mBones[mIUpperarmR]; }
    float* GetLowerarmR() { return mBones[mILowerarmR]; }
    float* GetLowerarmTwist01R() { return mBones[mILowerarmTwist01R]; }
    float* GetHandR() { return mBones[mIHandR]; }

    float* GetThighL() { return mBones[mIThighL]; }
    float* GetCalfL() { return mBones[mICalfL]; }
    float* GetFootL() { return mBones[mIFootL]; }
    float* GetBallL() { return mBones[mIBallL]; }

    float* GetThighR() { return mBones[mIThighR]; }
    float* GetCalfR() { return mBones[mICalfR]; }
    float* GetFootR() { return mBones[mIFootR]; }
    float* GetBallR() { return mBones[mIBallR]; }

    float* GetThumb01L() { return mBones[mIThumb01L]; }
    float* GetThumb02L() { return mBones[mIThumb02L]; }
    float* GetThumb03L() { return mBones[mIThumb03L]; }
    float* GetThumb04L() { return mBones[mIThumb04L]; }
    float* GetIndex01L() { return mBones[mIIndex01L]; }
    float* GetIndex02L() { return mBones[mIIndex02L]; }
    float* GetIndex03L() { return mBones[mIIndex03L]; }
    float* GetIndex04L() { return mBones[mIIndex04L]; }
    float* GetMiddle01L() { return mBones[mIMiddle01L]; }
    float* GetMiddle02L() { return mBones[mIMiddle02L]; }
    float* GetMiddle03L() { return mBones[mIMiddle03L]; }
    float* GetMiddle04L() { return mBones[mIMiddle04L]; }
    float* GetPinky01L() { return mBones[mIPinky01L]; }
    float* GetPinky02L() { return mBones[mIPinky02L]; }
    float* GetPinky03L() { return mBones[mIPinky03L]; }
    float* GetPinky04L() { return mBones[mIPinky04L]; }
    float* GetRing01L() { return mBones[mIRing01L]; }
    float* GetRing02L() { return mBones[mIRing02L]; }
    float* GetRing03L() { return mBones[mIRing03L]; }
    float* GetRing04L() { return mBones[mIRing04L]; }

    float* GetThumb01R() { return mBones[mIThumb01R]; }
    float* GetThumb02R() { return mBones[mIThumb02R]; }
    float* GetThumb03R() { return mBones[mIThumb03R]; }
    float* GetThumb04R() { return mBones[mIThumb04R]; }
    float* GetIndex01R() { return mBones[mIIndex01R]; }
    float* GetIndex02R() { return mBones[mIIndex02R]; }
    float* GetIndex03R() { return mBones[mIIndex03R]; }
    float* GetIndex04R() { return mBones[mIIndex04R]; }
    float* GetMiddle01R() { return mBones[mIMiddle01R]; }
    float* GetMiddle02R() { return mBones[mIMiddle02R]; }
    float* GetMiddle03R() { return mBones[mIMiddle03R]; }
    float* GetMiddle04R() { return mBones[mIMiddle04R]; }
    float* GetPinky01R() { return mBones[mIPinky01R]; }
    float* GetPinky02R() { return mBones[mIPinky02R]; }
    float* GetPinky03R() { return mBones[mIPinky03R]; }
    float* GetPinky04R() { return mBones[mIPinky04R]; }
    float* GetRing01R() { return mBones[mIRing01R]; }
    float* GetRing02R() { return mBones[mIRing02R]; }
    float* GetRing03R() { return mBones[mIRing03R]; }
    float* GetRing04R() { return mBones[mIRing04R]; }

    // Root
    float* GetRoot() {
         VecMean(mRoot, GetFootL(), GetFootR());
         return mRoot;
    }

    // Bone quaternion
    float* GetQuatPelvis() { return mQuats[mIPelvis]; }
    float* GetQuatSpine01() { return mQuats[mISpine01]; }
    float* GetQuatSpine02() { return mQuats[mISpine02]; }
    float* GetQuatSpine03() { return mQuats[mISpine03]; }
    float* GetQuatNeck01() { return mQuats[mINeck01]; }
    float* GetQuatHead() { return mQuats[mIHead]; }

    float* GetQuatClavicleL() { return mQuats[mIClavicleL]; }
    float* GetQuatUpperarmL() { return mQuats[mIUpperarmL]; }
    float* GetQuatLowerarmL() { return mQuats[mILowerarmL]; }
    float* GetQuatLowerarmTwist01L() { return mQuats[mILowerarmTwist01L]; }
    float* GetQuatHandL() { return mQuats[mIHandL]; }

    float* GetQuatClavicleR() { return mQuats[mIClavicleR]; }
    float* GetQuatUpperarmR() { return mQuats[mIUpperarmR]; }
    float* GetQuatLowerarmR() { return mQuats[mILowerarmR]; }
    float* GetQuatLowerarmTwist01R() { return mQuats[mILowerarmTwist01R]; }
    float* GetQuatHandR() { return mQuats[mIHandR]; }

    float* GetQuatThighL() { return mQuats[mIThighL]; }
    float* GetQuatCalfL() { return mQuats[mICalfL]; }
    float* GetQuatFootL() { return mQuats[mIFootL]; }
    float* GetQuatBallL() { return mQuats[mIBallL]; }

    float* GetQuatThighR() { return mQuats[mIThighR]; }
    float* GetQuatCalfR() { return mQuats[mICalfR]; }
    float* GetQuatFootR() { return mQuats[mIFootR]; }
    float* GetQuatBallR() { return mQuats[mIBallR]; }

    float* GetQuatThumb01L() { return mQuats[mIThumb01L]; }
    float* GetQuatThumb02L() { return mQuats[mIThumb02L]; }
    float* GetQuatThumb03L() { return mQuats[mIThumb03L]; }
    float* GetQuatIndex01L() { return mQuats[mIIndex01L]; }
    float* GetQuatIndex02L() { return mQuats[mIIndex02L]; }
    float* GetQuatIndex03L() { return mQuats[mIIndex03L]; }
    float* GetQuatMiddle01L() { return mQuats[mIMiddle01L]; }
    float* GetQuatMiddle02L() { return mQuats[mIMiddle02L]; }
    float* GetQuatMiddle03L() { return mQuats[mIMiddle03L]; }
    float* GetQuatPinky01L() { return mQuats[mIPinky01L]; }
    float* GetQuatPinky02L() { return mQuats[mIPinky02L]; }
    float* GetQuatPinky03L() { return mQuats[mIPinky03L]; }
    float* GetQuatRing01L() { return mQuats[mIRing01L]; }
    float* GetQuatRing02L() { return mQuats[mIRing02L]; }
    float* GetQuatRing03L() { return mQuats[mIRing03L]; }

    float* GetQuatThumb01R() { return mQuats[mIThumb01R]; }
    float* GetQuatThumb02R() { return mQuats[mIThumb02R]; }
    float* GetQuatThumb03R() { return mQuats[mIThumb03R]; }
    float* GetQuatIndex01R() { return mQuats[mIIndex01R]; }
    float* GetQuatIndex02R() { return mQuats[mIIndex02R]; }
    float* GetQuatIndex03R() { return mQuats[mIIndex03R]; }
    float* GetQuatMiddle01R() { return mQuats[mIMiddle01R]; }
    float* GetQuatMiddle02R() { return mQuats[mIMiddle02R]; }
    float* GetQuatMiddle03R() { return mQuats[mIMiddle03R]; }
    float* GetQuatPinky01R() { return mQuats[mIPinky01R]; }
    float* GetQuatPinky02R() { return mQuats[mIPinky02R]; }
    float* GetQuatPinky03R() { return mQuats[mIPinky03R]; }
    float* GetQuatRing01R() { return mQuats[mIRing01R]; }
    float* GetQuatRing02R() { return mQuats[mIRing02R]; }
    float* GetQuatRing03R() { return mQuats[mIRing03R]; }

    // Bone length
    float GetHeight() { return mHeight; }
    float GetLenSpine01() { return mBoneLens[GetISpine01()]; }
    float GetLenSpine02() { return mBoneLens[GetISpine02()]; }
    float GetLenSpine03() { return mBoneLens[GetISpine03()]; }
    float GetLenNeck01() { return mBoneLens[GetINeck01()]; }
    float GetLenHead() { return mBoneLens[GetIHead()]; }
    float GetLenNose() { return mLenNose; } // Auxiliary
    float GetLenEar() { return mLenEar; } // Auxiliary

    float GetLenSpine03ToClavicle() { return mLenSpine03ToClavicle; }
    float GetLenClavicle() { return mBoneLens[GetIClavicleL()]; }
    float GetLenUpperarm() { return mBoneLens[GetIUpperarmL()]; }
    float GetLenLowerarm() { return mBoneLens[GetILowerarmL()]; }

    float GetLenPelvisToThigh() { return mLenPelvisToThigh; }
    float GetLenThigh() { return mBoneLens[GetIThighL()]; }
    float GetLenCalf() { return mBoneLens[GetICalfL()]; }
    float GetLenFoot() { return mBoneLens[GetIFootL()]; }

    float GetLenThumb01() { return mBoneLens[GetIThumb01L()]; }
    float GetLenThumb02() { return mBoneLens[GetIThumb02L()]; }
    float GetLenThumb03() { return mBoneLens[GetIThumb03L()]; }
    float GetLenThumb04() { return mBoneLens[GetIThumb04L()]; }
    float GetLenIndex01() { return mBoneLens[GetIIndex01L()]; }
    float GetLenIndex02() { return mBoneLens[GetIIndex02L()]; }
    float GetLenIndex03() { return mBoneLens[GetIIndex03L()]; }
    float GetLenIndex04() { return mBoneLens[GetIIndex04L()]; }
    float GetLenMiddle01() { return mBoneLens[GetIMiddle01L()]; }
    float GetLenMiddle02() { return mBoneLens[GetIMiddle02L()]; }
    float GetLenMiddle03() { return mBoneLens[GetIMiddle03L()]; }
    float GetLenMiddle04() { return mBoneLens[GetIMiddle04L()]; }
    float GetLenRing01() { return mBoneLens[GetIRing01L()]; }
    float GetLenRing02() { return mBoneLens[GetIRing02L()]; }
    float GetLenRing03() { return mBoneLens[GetIRing03L()]; }
    float GetLenRing04() { return mBoneLens[GetIRing04L()]; }
    float GetLenPinky01() { return mBoneLens[GetIPinky01L()]; }
    float GetLenPinky02() { return mBoneLens[GetIPinky02L()]; }
    float GetLenPinky03() { return mBoneLens[GetIPinky03L()]; }
    float GetLenPinky04() { return mBoneLens[GetIPinky04L()]; }

    // Auxiliary points
    float* GetNose() { return mNose; }
    float* GetEarL() { return mEarL; }
    float* GetEarR() { return mEarR; }
    float* GetShoulderL() { return mShoulderL; }
    float* GetShoulderR() { return mShoulderR; }
    float* GetShoulderCenter() { return mShoulderCenter; }
    float* GetHipL() { return mHipL; }
    float* GetHipR() { return mHipR; }
    float* GetHipCenter() { return mHipCenter; }

    // Front direction of skeleton which is horizontal.
    float* GetFrontDvec() {

        VecCopy(mFrontDvec, GetDvec2(mIPelvis));

        int indexVerticalAxis = 1; // Y-axis
        mFrontDvec[indexVerticalAxis] = 0.0;
        NormalizeVec(mFrontDvec, mFrontDvec);

        return mFrontDvec;

    }

    float* GetLeftPalmDirection() {
        return mLeftPalmDirection;
    }

    float* GetRightPalmDirection() {
        return mRightPalmDirection;
    }

    float GetHeadDeviationAngle() {
    // Deviation angle (in radian) of head.

        float *quat = GetQuat(GetIHead());
        float angleAxis[4];
        ConvertQuatToAngleAxis(quat, angleAxis);
        
        return abs(angleAxis[0]);

    }
 
    float GetHeadYaw() {
    // Return the yaw angle of body.

        float *quat = GetQuat(GetIHead());
        float angleAxis[4];
        ConvertQuatToAngleAxis(quat, angleAxis);

        float sign;
        if (angleAxis[2] > 0) {
            sign = 1.0;
        } else {
            sign = -1.0;
        } 
        
        float yaw = RadianToDegree(sign*angleAxis[0]);

        return yaw;

    }

    float GetBodyYaw() {
    // Return the yaw angle of body.

        float *quat = GetQuat(GetIPelvis());
        float angleAxis[4];
        ConvertQuatToAngleAxis(quat, angleAxis);

        float sign;
        if (angleAxis[2] > 0) {
            sign = 1.0;
        } else {
            sign = -1.0;
        } 
        
        float yaw = RadianToDegree(sign*angleAxis[0]);

        return yaw;

    }

    // Estimate the direction of component
    void EstimatePelvisDirection() {

        float* dvec1 = GetDvec1(mIPelvis);
        float* dvec2 = GetDvec2(mIPelvis);

        VecSubstractNorm(dvec1, GetSpine01(), GetPelvis());

        float vecThighLPelvis[Dims];
        float vecSpine01Pelvis[Dims];

        VecSubstract(vecThighLPelvis, GetThighL(), GetPelvis());
        VecSubstract(vecSpine01Pelvis, GetSpine01(), GetPelvis());
        VecCrossNorm(dvec2, vecThighLPelvis, vecSpine01Pelvis);

    }

    void EstimateSpine01Direction() {

        float* dvec1 = GetDvec1(mISpine01);
        float* dvec2 = GetDvec2(mISpine01);

        VecSubstractNorm(dvec1, GetSpine01(), GetPelvis());

        float vecThighLSpine01[Dims];
        float vecSpine02Spine01[Dims];

        VecSubstract(vecThighLSpine01, GetThighL(), GetSpine01());
        VecSubstract(vecSpine02Spine01, GetSpine02(), GetSpine01());
        VecCrossNorm(dvec2, vecThighLSpine01, vecSpine02Spine01);

    }

    void EstimateSpine02Direction() {

        float* dvec1 = GetDvec1(mISpine02);
        float* dvec2 = GetDvec2(mISpine02);

        VecSubstractNorm(dvec1, GetSpine02(), GetSpine01());

        float vecThighLSpine02[Dims];
        float vecSpine03Spine02[Dims];

        VecSubstract(vecThighLSpine02, GetThighL(), GetSpine02());
        VecSubstract(vecSpine03Spine02, GetSpine03(), GetSpine02());
        VecCrossNorm(dvec2, vecThighLSpine02, vecSpine03Spine02);

    }

    void EstimateSpine03Direction() {

        float* dvec1 = GetDvec1(mISpine03);
        float* dvec2 = GetDvec2(mISpine03);

        VecSubstractNorm(dvec1, GetSpine03(), GetSpine02());

        float vecClavicleLSpine03[Dims];
        float vecClavicleRSpine03[Dims];

        VecSubstract(vecClavicleLSpine03, GetClavicleL(), GetSpine03());
        VecSubstract(vecClavicleRSpine03, GetClavicleR(), GetSpine03());
        VecCrossNorm(dvec2, vecClavicleLSpine03, vecClavicleRSpine03);

    }

    void EstimateNeck01Direction() {

        float* dvec1 = GetDvec1(mINeck01);
        float* dvec2 = GetDvec2(mINeck01);

        VecSubstractNorm(dvec1, GetNeck01(), GetSpine03());

        float vecEarLNeck01[Dims];
        float vecHeadNeck01[Dims];

        VecSubstract(vecEarLNeck01, GetEarL(), GetNeck01());
        VecSubstract(vecHeadNeck01, GetHead(), GetNeck01());
        VecCrossNorm(dvec2, vecEarLNeck01, vecHeadNeck01);

    }

    void EstimateHeadDirection() {

        float* dvec1 = GetDvec1(mIHead);
        float* dvec2 = GetDvec2(mIHead);

        /*
        float vecEarREarL[Dims];
        VecSubstractNorm(vecEarREarL, GetEarR(), GetEarL());

        float vecNoseHead[Dims];
        VecSubstractNorm(vecNoseHead, GetNose(), GetHead());
        EstimateVerticalVector(vecNoseHead, vecNoseHead, vecEarREarL);
        EstimateUnitVector(vecNoseHead, vecNoseHead);

        float vecHeadNeck[Dims];
        VecCrossNorm(vecHeadNeck, vecEarREarL, vecNoseHead);

        VecCopy(dvec1, vecHeadNeck);
        VecCopy(dvec2, vecNoseHead);
        */

        /*
        float ShoulderC[Dims];
        VecMean(ShoulderC, GetShoulderL(), GetShoulderR());

        DbPrintArray("Nose: ", GetNose(), 3);
        DbPrintArray("Head: ", GetHead(), 3);
        DbPrintArray("EarR: ", GetEarR(), 3);
        DbPrintArray("EarL: ", GetEarL(), 3);
        //DbPrintArray("ShoulderR: ", GetShoulderR(), 3);
        //DbPrintArray("ShoulderL: ", GetShoulderL(), 3);
        //DbPrintArray("ShoulderC: ", ShoulderC, 3);
        DbPrintArray("vecEarREarL: ", vecEarREarL, 3);
        DbPrintArray("vecNoseHead: ", vecNoseHead, 3);
        DbPrintArray("vecHeadNeck: ", vecHeadNeck, 3);
        */

        float vecHeadNeck[Dims];
        VecSubstractNorm(vecHeadNeck, GetHead(), GetNeck01());

        float vecEarREarL[Dims];
        VecSubstractNorm(vecEarREarL, GetEarR(), GetEarL());
        EstimateVerticalVector(vecEarREarL, vecEarREarL, vecHeadNeck);
        EstimateUnitVector(vecEarREarL, vecEarREarL);

        float vecNoseHead[Dims];
        VecCrossNorm(vecNoseHead, vecHeadNeck, vecEarREarL);

        VecCopy(dvec1, vecHeadNeck);
        VecCopy(dvec2, vecNoseHead);

    }

    void EstimateClavicleLDirection() {

        float* dvec1 = GetDvec1(mIClavicleL);
        float* dvec2 = GetDvec2(mIClavicleL);

        VecSubstractNorm(dvec1, GetUpperarmL(), GetClavicleL());

        float vecSpine03Clavicle[Dims];
        float vecUpperarmClavicle[Dims];

        VecSubstract(vecSpine03Clavicle, GetSpine03(), GetClavicleL());
        VecSubstract(vecUpperarmClavicle, GetUpperarmL(), GetClavicleL());
        VecCrossNorm(dvec2, vecSpine03Clavicle, vecUpperarmClavicle);

    }

    void EstimateClavicleRDirection() {

        float* dvec1 = GetDvec1(mIClavicleR);
        float* dvec2 = GetDvec2(mIClavicleR);

        VecSubstractNorm(dvec1, GetUpperarmR(), GetClavicleR());

        float vecSpine03Clavicle[Dims];
        float vecUpperarmClavicle[Dims];

        VecSubstract(vecSpine03Clavicle, GetSpine03(), GetClavicleR());
        VecSubstract(vecUpperarmClavicle, GetUpperarmR(), GetClavicleR());
        VecCrossNorm(dvec2, vecUpperarmClavicle, vecSpine03Clavicle);

    }

    void EstimateUpperarmLDirection() {

        float* dvec1 = GetDvec1(mIUpperarmL);
        float* dvec2 = GetDvec2(mIUpperarmL);

        VecSubstractNorm(dvec1, GetLowerarmL(), GetUpperarmL());

        float* dvec2OfLowerarm = GetDvec2(mILowerarmL);
        VecCrossNorm(dvec2, dvec1, dvec2OfLowerarm);

        /*
        float vecClavicleUpperarm[Dims];
        float vecLowerarmUpperarm[Dims];

        VecSubstract(vecClavicleUpperarm, GetClavicleL(), GetUpperarmL());
        VecSubstract(vecLowerarmUpperarm, GetLowerarmL(), GetUpperarmL());
        VecCrossNorm(dvec2, vecClavicleUpperarm, vecLowerarmUpperarm);
          
        float* dvec2Spine03 = GetDvec2(mISpine03);
        float dotValue;
        VecDot(dotValue, vecLowerarmUpperarm, dvec2Spine03);

        if (dotValue < 0) {
            VecCopy(dvec2, GetDvec2(mIHandL), Dims);
        }
        */

    }

    void EstimateUpperarmRDirection() {

        float* dvec1 = GetDvec1(mIUpperarmR);
        float* dvec2 = GetDvec2(mIUpperarmR);

        VecSubstractNorm(dvec1, GetLowerarmR(), GetUpperarmR());

        float* dvec2OfLowerarm = GetDvec2(mILowerarmR);
        VecCrossNorm(dvec2, dvec2OfLowerarm, dvec1);

    }

    void EstimateLowerarmLDirection() {

        float* dvec1 = GetDvec1(mILowerarmL);
        float* dvec2 = GetDvec2(mILowerarmL);

        VecSubstractNorm(dvec1, GetHandL(), GetLowerarmL());

        // Use dvec2 of left lowerarm
        VecCopy(dvec2, GetDvec2(mIHandL));

    }    

    void EstimateLowerarmRDirection() {

        float* dvec1 = GetDvec1(mILowerarmR);
        float* dvec2 = GetDvec2(mILowerarmR);

        VecSubstractNorm(dvec1, GetHandR(), GetLowerarmR());

        // Use dvec2 of left lowerarm
        VecCopy(dvec2, GetDvec2(mIHandR));

    }

    void EstimatePalmLDirection() {

        float vecIndex01Hand[Dims];
        float vecPinky01Hand[Dims];

        VecSubstract(vecIndex01Hand, GetIndex01L(), GetHandL());
        VecSubstract(vecPinky01Hand, GetPinky01L(), GetHandL());
        VecCrossNorm(mLeftPalmDirection, vecPinky01Hand, vecIndex01Hand);

    }

    void EstimatePalmRDirection() {

        float vecIndex01Hand[Dims];
        float vecPinky01Hand[Dims];

        VecSubstract(vecIndex01Hand, GetIndex01R(), GetHandR());
        VecSubstract(vecPinky01Hand, GetPinky01R(), GetHandR());
        VecCrossNorm(mRightPalmDirection, vecIndex01Hand, vecPinky01Hand);

    }

    void EstimateHandLDirection() {

        float* dvec1 = GetDvec1(mIHandL);
        float* dvec2 = GetDvec2(mIHandL);

        // Direction 1
        VecSubstractNorm(dvec1, GetMiddle01L(), GetHandL());

        // Direction 2
        float vecIndex01Pinky01[Dims];
        VecSubstract(vecIndex01Pinky01, GetIndex01L(), GetPinky01L());
        VecCrossNorm(dvec2, vecIndex01Pinky01, dvec1);

    }

    void EstimateHandRDirection() {

        float* dvec1 = GetDvec1(mIHandR);
        float* dvec2 = GetDvec2(mIHandR);

        // Direction 1
        VecSubstractNorm(dvec1, GetMiddle01R(), GetHandR());

        // Direction 2
        float vecIndex01Pinky01[Dims];
        VecSubstract(vecIndex01Pinky01, GetIndex01R(), GetPinky01R());
        VecCrossNorm(dvec2, dvec1, vecIndex01Pinky01);

    }

    void EstimateThighLDirection() {

        float* dvec1 = GetDvec1(mIThighL);
        float* dvec2 = GetDvec2(mIThighL);

        VecSubstractNorm(dvec1, GetCalfL(), GetThighL());

        float vecPelvisThigh[Dims];
        float vecCalfThigh[Dims];

        VecSubstract(vecPelvisThigh, GetPelvis(), GetThighL());
        VecSubstract(vecCalfThigh, GetCalfL(), GetThighL());
        VecCrossNorm(dvec2, vecPelvisThigh, vecCalfThigh);

    }

    void EstimateThighRDirection() {

        float* dvec1 = GetDvec1(mIThighR);
        float* dvec2 = GetDvec2(mIThighR);

        VecSubstractNorm(dvec1, GetCalfR(), GetThighR());

        VecCopy(dvec2, GetDvec2(mIPelvis));

        float vecPelvisThigh[Dims];
        float vecCalfThigh[Dims];

        VecSubstract(vecPelvisThigh, GetPelvis(), GetThighR());
        VecSubstract(vecCalfThigh, GetCalfR(), GetThighR());
        VecCrossNorm(dvec2, vecCalfThigh, vecPelvisThigh);

    }

    void EstimateCalfLDirection() {

        float* dvec1 = GetDvec1(mICalfL);
        float* dvec2 = GetDvec2(mICalfL);

        float vecFootCalf[Dims];
        VecSubstract(vecFootCalf, GetFootL(), GetCalfL());

        VecCopy(dvec1, vecFootCalf);
        VecCrossNorm(dvec2, GetFrontDvec(), vecFootCalf);

    }

    void EstimateCalfRDirection() {

        float* dvec1 = GetDvec1(mICalfR);
        float* dvec2 = GetDvec2(mICalfR);

        float vecFootCalf[Dims];
        VecSubstract(vecFootCalf, GetFootR(), GetCalfR());

        VecCopy(dvec1, vecFootCalf);
        VecCrossNorm(dvec2, GetFrontDvec(), vecFootCalf);

    }

    void EstimateFootLDirection() {

        float* dvec1 = GetDvec1(mIFootL);
        float* dvec2 = GetDvec2(mIFootL);

        float vecBallFoot[Dims];
        VecSubstract(vecBallFoot, GetBallL(), GetFootL());

        VecCopy(dvec1, vecBallFoot);
        VecCrossNorm(dvec2, GetFrontDvec(), vecBallFoot);

    }

    void EstimateFootRDirection() {

        float* dvec1 = GetDvec1(mIFootR);
        float* dvec2 = GetDvec2(mIFootR);

        float vecBallFoot[Dims];
        VecSubstract(vecBallFoot, GetBallR(), GetFootR());

        VecCopy(dvec1, vecBallFoot);
        VecCrossNorm(dvec2, GetFrontDvec(), vecBallFoot);

    }

    void EstimateFingersLDirection() {

        float* dvec1;
        float* dvec2;
        const int numJoints = 4;
        int iStart = mIThumb01L;

        int index; // Bone index
        int i, j;
        float vecLower[3], vecUpper[3];
        bool isAntiParallel;
        float vecIndex01Pinky01[3];
        float dotValue;
        

        float* pHand = GetHandL();
        for (i = 0; i < 5; i++) { // Finger
            for (j = 0; j < numJoints-1; j++) { // Finger joint

                index = iStart + i*numJoints + j;
                dvec1 = GetDvec1(index);
                dvec2 = GetDvec2(index);

                // Dvec1
                VecSubstractNorm(vecUpper, GetBone(index+1), GetBone(index));
                VecCopy(dvec1, vecUpper);

                // Dvec2
                if (j == 0) {
                    VecSubstract(vecLower, pHand, GetBone(index));
                } else {
                    VecSubstract(vecLower, GetBone(index-1), GetBone(index));
                }

                isAntiParallel = IsAntiParallel(vecLower, vecUpper, mSmallAngle);
                if (isAntiParallel) {
                    VecSubstract(vecLower, pHand, GetBone(index));
                }

                VecCrossNorm(dvec2, vecLower, vecUpper);

                VecSubstract(vecIndex01Pinky01, GetIndex01L(), GetPinky01L());
                VecDot(dotValue, dvec2, vecIndex01Pinky01);

                if (dotValue < 0) {
                    VecInverse(dvec2, dvec2);
                }

            }
        }

    }

    void EstimateFingersRDirection() {

        float* dvec1;
        float* dvec2;
        const int numJoints = 4;
        int iStart = mIThumb01R;

        int index; // Bone index
        int i, j;
        float vecLower[3], vecUpper[3];
        bool isAntiParallel;
        float vecIndex01Pinky01[3];
        float dotValue;

        float* pHand = GetHandR();
        for (i = 0; i < 5; i++) { // Finger
            for (j = 0; j < numJoints-1; j++) { // Finget joint

                index = iStart + i*numJoints + j;
                dvec1 = GetDvec1(index);
                dvec2 = GetDvec2(index);

                // Dvec1
                VecSubstractNorm(vecUpper, GetBone(index+1), GetBone(index));
                VecCopy(dvec1, vecUpper);

                // Dvec2
                if (j == 0) {
                    VecSubstract(vecLower, pHand, GetBone(index));
                } else {
                    VecSubstract(vecLower, GetBone(index-1), GetBone(index));
                }

                isAntiParallel = IsAntiParallel(vecLower, vecUpper, mSmallAngle);
                if (isAntiParallel) {
                    VecSubstract(vecLower, pHand, GetBone(index));
                }

                VecCrossNorm(dvec2, vecLower, vecUpper);

                VecSubstract(vecIndex01Pinky01, GetIndex01R(), GetPinky01R());
                VecDot(dotValue, dvec2, vecIndex01Pinky01);

                if (dotValue < 0) {
                    VecInverse(dvec2, dvec2);
                }
            }
        }

    }

    void EstimateJointQuat(float* quat, int boneIndex, float* dvec1Init, float* dvec2Init) {

        float* dvec1Final;
        float* dvec2Final;
        float dvec2InitRotated[Dims];

        dvec1Final = GetDvec1(boneIndex);
        dvec2Final = GetDvec2(boneIndex);

        float q1[QuatDims], q2[QuatDims];
        EstimateQuatFromTwoVectors(q1, dvec1Init, dvec1Final);
        EstimateRotatedVector(dvec2InitRotated, dvec2Init, q1);
        EstimateQuatFromTwoVectors(q2, dvec2InitRotated, dvec2Final);
        EstimateQuatMultiply(quat, q2, q1);

    }

    void EstimateJointQuatWithRowOnly(float* quat, int boneIndex, float* dvec2Init) {

        float* dvec2Final;
        dvec2Final = GetDvec2(boneIndex);

        float q1[QuatDims];
        EstimateQuatFromTwoVectors(q1, dvec2Init, dvec2Final);
        VecCopy(quat, q1, 4);

    }

    void EstimateJointQuatWithoutRow(float* quat, int boneIndex, float* dvec1Init) {

        float* dvec1Final;
        dvec1Final = GetDvec1(boneIndex);

        float q1[QuatDims];
        EstimateQuatFromTwoVectors(q1, dvec1Init, dvec1Final);
        VecCopy(quat, q1, 4);

    }

    static const int NumBones = 68;
    static const int Dims = 3;
    static const int QuatDims = 4;

    // Copy constructor
    Skeleton(const Skeleton &skel) {

        mHasFace = skel.mHasFace;
        mHasBody = skel.mHasBody;
        mHasLeftHand = skel.mHasLeftHand;
        mHasRightHand = skel.mHasRightHand;

        int i, iDim, iQuat;

        for (i = 0; i < NumBones; i++) {

            mBoneLens[i] = skel.mBoneLens[i];

            for (iDim = 0; iDim < Dims; iDim++) {

                mBones[i][iDim] = skel.mBones[i][iDim];
                mDvec1[i][iDim] = skel.mDvec1[i][iDim];
                mDvec2[i][iDim] = skel.mDvec2[i][iDim];
                mDvec1Init[i][iDim] = skel.mDvec1Init[i][iDim];
                mDvec2Init[i][iDim] = skel.mDvec2Init[i][iDim];

            }

            for (iQuat = 0; iQuat < QuatDims; iQuat++) {
                mQuats[i][iQuat] = skel.mQuats[i][iQuat];
            }

        }

        // Front direction vector
        for (i = 0; i < Dims; i++) {
            mFrontDvec[i] = skel.mFrontDvec[i];
        }

        // Copy auxillary bones
        for (i = 0; i < Dims; i++) {

            mNose[i] = skel.mNose[i];
            mEarL[i] = skel.mEarL[i];
            mEarR[i] = skel.mEarR[i];

            mShoulderL[i] = skel.mShoulderL[i];
            mShoulderR[i] = skel.mShoulderR[i];

            mHipL[i] = skel.mHipL[i];
            mHipR[i] = skel.mHipR[i];

        }

    }

private:

    bool mHasFace = true;
    bool mHasBody = true;
    bool mHasLeftHand = true;
    bool mHasRightHand = true;

    float mBones[NumBones][Dims] = {0.0};
    float mDvec1[NumBones][Dims] = {0.0}; // Direction vector 1
    float mDvec2[NumBones][Dims] = {0.0}; // Direction vector 2
    float mDvec1Init[NumBones][Dims] = {0.0}; // Direction vector 1
    float mDvec2Init[NumBones][Dims] = {0.0}; // Direction vector 2
    float mBoneLens[NumBones] = {0.0};

    float mQuats[NumBones][QuatDims] = {0.0};

    float mFrontDvec[Dims] = {0.0}; // Front direction

    static const int mIPelvis = 0;
    static const int mISpine01 = 1;
    static const int mISpine02 = 2;
    static const int mISpine03 = 3;
    static const int mINeck01 = 4;
    static const int mIHead = 5;

    static const int mIClavicleL = 6;
    static const int mIUpperarmL = 7;
    static const int mILowerarmL = 8;
    static const int mILowerarmTwist01L = 9;
    static const int mIHandL = 10;

    static const int mIClavicleR = 11;
    static const int mIUpperarmR = 12;
    static const int mILowerarmR = 13;
    static const int mILowerarmTwist01R = 14;
    static const int mIHandR = 15;
    
    static const int mIThighL = 16;
    static const int mICalfL = 17;
    static const int mICalfTwist01L = 18;
    static const int mIFootL = 19;
    static const int mIBallL = 20;

    static const int mIThighR = 21;
    static const int mICalfR = 22;
    static const int mICalfTwist01R = 23;
    static const int mIFootR = 24;
    static const int mIBallR = 25;

    static const int mIThumb01L = 26;
    static const int mIThumb02L = 27;
    static const int mIThumb03L = 28;
    static const int mIThumb04L = 29;
    static const int mIIndex01L = 30;
    static const int mIIndex02L = 31;
    static const int mIIndex03L = 32;
    static const int mIIndex04L = 33;
    static const int mIMiddle01L = 34;
    static const int mIMiddle02L = 35;
    static const int mIMiddle03L = 36;
    static const int mIMiddle04L = 37;
    static const int mIRing01L = 38;
    static const int mIRing02L = 39;
    static const int mIRing03L = 40;
    static const int mIRing04L = 41;
    static const int mIPinky01L = 42;
    static const int mIPinky02L = 43;
    static const int mIPinky03L = 44;
    static const int mIPinky04L = 45;

    static const int mIThumb01R = 46;
    static const int mIThumb02R = 47;
    static const int mIThumb03R = 48;
    static const int mIThumb04R = 49;
    static const int mIIndex01R = 50;
    static const int mIIndex02R = 51;
    static const int mIIndex03R = 52;
    static const int mIIndex04R = 53;
    static const int mIMiddle01R = 54;
    static const int mIMiddle02R = 55;
    static const int mIMiddle03R = 56;
    static const int mIMiddle04R = 57;
    static const int mIRing01R = 58;
    static const int mIRing02R = 59;
    static const int mIRing03R = 60;
    static const int mIRing04R = 61;
    static const int mIPinky01R = 62;
    static const int mIPinky02R = 63;
    static const int mIPinky03R = 64;
    static const int mIPinky04R = 65;

    static const int mISpringL = 66;
    static const int mISpringR = 67;

    // Auxiliary points
    float mRoot[Dims] = {0.0};

    float mLenNose;
    float mNose[Dims] = {0.0}; 
    float mLenEar;
    float mEarL[Dims] = {0.0}; 
    float mEarR[Dims] = {0.0}; 

    float mShoulderL[Dims] = {0.0}; 
    float mShoulderR[Dims] = {0.0}; 
    float mShoulderCenter[Dims] = {0.0}; 

    float mHipL[Dims] = {0.0}; 
    float mHipR[Dims] = {0.0}; 
    float mHipCenter[Dims] = {0.0}; 

    // Auxiliry lengths
    float mHeight;
    float mLenSpine03ToClavicle;
    float mLenPelvisToThigh;

    // Critera of small angle 
    float mSmallAngle = 10.0/180.0*M_PI; 

    // Error tolerance of angle
    float mAngleErr = 1e-8;

    // Auxiliary directions
    float mLeftPalmDirection[Dims];
    float mRightPalmDirection[Dims];

};


#endif // SKELETON_H