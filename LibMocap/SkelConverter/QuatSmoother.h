#pragma once

#include <iostream>
#include <vector>

#include "Core/Math/OneEuroFilter.hpp"
#include "Utils/Timer.hpp"

using namespace std;

class QuatSmoother {

public:

    QuatSmoother();
    ~QuatSmoother();

    void Update(float* quat);
    void CorrectAngle(float* DataIn, vector<float> &DataOut);
    void CorrectRotation(float* DataIn, vector<float> &DataOut);
    void GetUpdatedQuat(float* quat);

private:

    const int mNumHist = 4;
    float mQuat[4][10];
    float mQuatOut[4];
    one_euro::OneEuroFilter mQuatOneEuro[4];

    bool mUseOneEuro = true;
    
    Timer mTimer;
    double mTimestamp;


};