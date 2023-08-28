#include "pch.h"

#include "Mocap.h"
#include "LibFacialExpression.h" 
#include "libmediapipe.h"
#include "libmocap_mp.h"
 



Mocap::Mocap() {

    mBlendshapes.assign(mNumBlendshapes, 0);

    FTransform boneTransform;
    mSkelTransforms.assign(mNumBones, boneTransform);

}

Mocap::~Mocap() {

    FacialExpressionFinalize();
    MediapipeFinalize();
    MocapMpFinalize();

}

void Mocap::Init(int ImageWidth, int ImageHeight) {

    // Facial expression
    FacialExpressionInit(ImageWidth, ImageHeight);

    // Mediapipe 
    MediapipeInit(); 

    // Skeleton converter
    mSkelConverter.Init(ImageWidth, ImageHeight);

    // MocapMp
    MocapMpInit(ImageWidth, ImageHeight);

}


void Mocap::Detect(Mat& Image) {

    float* p;

    // Facial expression
    FacialExpressionDetect(Image);

    mIsFaceDetected = FacialExpressionIsFaceDetected();

    p = FacialExpressionGetBlendshapes();
    for (int i = 0; i < mNumBlendshapes; i++) {
        mBlendshapes[i] = p[i];
    }

    // Head transform
    FQuat headRotation;
    FVector headTranslation;

    p = FacialExpressionGetHeadQuat();
    headRotation.X = p[0];
    headRotation.Y = p[1];
    headRotation.Z = p[2];
    headRotation.W = p[3];

    p = FacialExpressionGetHeadTranslation();
    headTranslation.X = p[0];
    headTranslation.Y = p[1];
    headTranslation.Z = p[2];
    mHeadTransform = MakeTransform(headRotation, headTranslation);

    // Mediapipe
    MediapipeDetect(Image);
    UpdateHolistic(mHolistic);

    mSkelConverter.Process(mHolistic);

    // MocapMp
    MocapMpDetect(Image);


}

bool Mocap::IsFaceDetected() {
    return mIsFaceDetected;
}

vector<float> Mocap::GetBlendshapes() {
    return mBlendshapes;
}

FTransform Mocap::GetHeadTransform() {
    return mHeadTransform;
}


FTransform Mocap::GetSkelTransform(int Index) {

    FTransform transform;

    float* pQuat;
    float* pBone;
    pQuat = MocapMpGetQuat(Index);
    pBone = MocapMpGetBone(Index);

    transform.Rotation.X = pQuat[1];
    transform.Rotation.Y = pQuat[2];
    transform.Rotation.Z = pQuat[3];
    transform.Rotation.W = pQuat[0];

    transform.Translation.X = pBone[0];
    transform.Translation.Y = pBone[1];
    transform.Translation.Z = pBone[2];

    return transform;
}

// Private methods
FTransform Mocap::MakeTransform(FQuat Rotation, FVector Translation) {

    FTransform transform;

    transform.Translation = Translation;
    transform.Rotation = Rotation;

    return transform;
}

void Mocap::CopyArray2D(float* Src, float* Dest, int Rows, int Cols) {

    int num = Rows * Cols;
    memcpy(Dest, Src, num);

}

void Mocap::UpdateHolistic(Holistic& Data) {

    float* pFacemesh;
    MediapipeGetFacemesh(Data.HasFacemesh, pFacemesh);

    CopyArray2D(pFacemesh, &(Data.facemesh[0][0]),
        Data.FACEMESH_LANDMARK_NUM,
        Data.DIMENSIONS);

    float* pPose;
    MediapipeGetPose(Data.HasPose, pPose);

    CopyArray2D(pPose, &(Data.pose[0][0]),
        Data.POSE_LANDMARK_NUM,
        Data.DIMENSIONS);

    float* pLeftHand;
    MediapipeGetLeftHand(Data.HasLeftHand, pLeftHand);

    CopyArray2D(pLeftHand, &(Data.LeftHand[0][0]),
        Data.HAND_LANDMARK_NUM,
        Data.DIMENSIONS);

    //cout << "HasLeftHand: " << Data.HasLeftHand << endl;
    //cout << "LeftHand[0][0]: " << Data.LeftHand[0][0] << endl;

    float* pRightHand;
    MediapipeGetRightHand(Data.HasRightHand, pRightHand);

    CopyArray2D(pRightHand, &(Data.RightHand[0][0]),
        Data.HAND_LANDMARK_NUM,
        Data.DIMENSIONS);

    //cout << "HasRightHand: " << Data.HasRightHand << endl;
    //cout << "RightHand[0][0]: " << Data.RightHand[0][0] << endl;


}
