#include "pch.h"

#include "Mocap.h"
#include "LibFacialExpression.h"
#include "libmocap_mp.h"


Mocap::Mocap() {

    mBlendshapes.assign(mNumBlendshapes, 0);

    FTransform boneTransform;
    mSkelTransforms.assign(mNumBones, boneTransform);

}

Mocap::~Mocap() {

    FacialExpressionFinalize();
    MocapMpFinalize();

}

void Mocap::Init(int ImageWidth, int ImageHeight) {

    // Facial expression
    FacialExpressionInit(ImageWidth, ImageHeight);

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
