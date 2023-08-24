#include "pch.h" // use stdafx.h in Visual Studio 2017 and earlier

#include "LibMocap.h"
#include "Mocap.h"

static Mocap *pInst = nullptr;
float mHeadTransformArray[10];

void MocapInit(int FrameWidth, int FrameHeight) {

    pInst = new Mocap;
    pInst->Init(FrameWidth, FrameHeight);

} 

void MocapFinalize() {

    if (!pInst) {
        delete pInst;
        pInst = NULL;
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
    FVector translation = transform.Translation;
    FQuat rotation = transform.Rotation;
    FVector scale3D = transform.Scale3D;

    mHeadTransformArray[0] = translation.X;
    mHeadTransformArray[1] = translation.Y;
    mHeadTransformArray[2] = translation.Z;

    mHeadTransformArray[3] = rotation.X;
    mHeadTransformArray[4] = rotation.Y;
    mHeadTransformArray[5] = rotation.Z;
    mHeadTransformArray[6] = rotation.W;

    mHeadTransformArray[7] = scale3D.X;
    mHeadTransformArray[8] = scale3D.Y;
    mHeadTransformArray[9] = scale3D.Z;

    return mHeadTransformArray;
    //return &mHeadTransformArray[0];
}

