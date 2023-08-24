#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "TypeDef.h"


#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

class Mocap {
public:

    Mocap();
    ~Mocap();
    void Init(int ImageWidth, int ImageHeight);
    void Detect(Mat& Image);
    bool IsFaceDetected();
    vector<float> GetBlendshapes();
    FTransform GetHeadTransform();


private:

    FTransform MakeTransform(FVector Translation, FQuat Rotation);

    bool mIsFaceDetected = false;
    const int mNumBlendshapes = 52;
    vector<float> mBlendshapes;
    FTransform mHeadTransform;

    const int mNumBones = 68;
    vector<FTransform> mBoneTransforms;


};
