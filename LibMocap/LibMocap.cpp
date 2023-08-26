#include "pch.h" // use stdafx.h in Visual Studio 2017 and earlier

#include "LibMocap.h"
#include "Mocap.h"

static Mocap *pInst = nullptr;
float mHeadTransformArray[10];
float mSkelTransformArray[10];

void MocapInit(int FrameWidth, int FrameHeight) {

    pInst = new Mocap;
    pInst->Init(FrameWidth, FrameHeight);

} 

void MocapFinalize() {

    if (!pInst) {
        delete pInst;
        pInst = nullptr;
    }

}

void MocapDetect(cv::Mat& Image) {

    pInst->Detect(Image);

} 

bool MocapIsFaceDetected() {
    return pInst->IsFaceDetected();
}

float* MocapGetBlendshapes() {
    return pInst->GetBlendshapes().data();
}

float* MocapGetHeadTransform() {

    FTransform transform = pInst->GetHeadTransform();
    FQuat rotation = transform.Rotation;
    FVector translation = transform.Translation;
    FVector scale3D = transform.Scale3D;

    mHeadTransformArray[0] = rotation.X;
    mHeadTransformArray[1] = rotation.Y;
    mHeadTransformArray[2] = rotation.Z;
    mHeadTransformArray[3] = rotation.W;

    mHeadTransformArray[4] = translation.X;
    mHeadTransformArray[5] = translation.Y;
    mHeadTransformArray[6] = translation.Z;

    mHeadTransformArray[7] = scale3D.X;
    mHeadTransformArray[8] = scale3D.Y;
    mHeadTransformArray[9] = scale3D.Z;

    return mHeadTransformArray; 
    //return &mHeadTransformArray[0];
}
 
float* MocapGetSkelTransform(int Index) {

    FTransform transform = pInst->GetSkelTransform(Index);
    FQuat rotation = transform.Rotation;
    FVector translation = transform.Translation;
    FVector scale3D = transform.Scale3D;

    mSkelTransformArray[0] = rotation.X;
    mSkelTransformArray[1] = rotation.Y;
    mSkelTransformArray[2] = rotation.Z;
    mSkelTransformArray[3] = rotation.W;

    mSkelTransformArray[4] = translation.X;
    mSkelTransformArray[5] = translation.Y;
    mSkelTransformArray[6] = translation.Z;

    mSkelTransformArray[7] = scale3D.X;
    mSkelTransformArray[8] = scale3D.Y;
    mSkelTransformArray[9] = scale3D.Z;

    return mSkelTransformArray; 
}


