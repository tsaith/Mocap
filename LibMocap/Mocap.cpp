#include "pch.h"

#include "Mocap.h"
#include "LibFacialExpression.h"
#include "libmocap_mp.h"


Mocap::Mocap() {

    mBlendshapes.assign(mNumBlendshapes, 0);

    FTransform boneTransform;
    mBoneTransforms.assign(mNumBones, boneTransform);

}

Mocap::~Mocap() {

    FacialExpressionFinalize();

}

void Mocap::Init(int ImageWidth, int ImageHeight) {

    FacialExpressionInit(ImageWidth, ImageHeight);

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
    FVector headTranslation;
    FQuat headQuat;

    p = FacialExpressionGetHeadTranslation();
    headTranslation.X = p[0];
    headTranslation.Y = p[1];
    headTranslation.Z = p[2];

    p = FacialExpressionGetHeadQuat();
    headQuat.X = p[0];
    headQuat.Y = p[1];
    headQuat.Z = p[2];
    headQuat.W = p[3];

    mHeadTransform = MakeTransform(headTranslation, headQuat);



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

// Private methods
FTransform Mocap::MakeTransform(FVector Translation, FQuat Rotation) {

    FTransform transform;

    transform.Translation = Translation;
    transform.Rotation = Rotation;

    return transform;
}
