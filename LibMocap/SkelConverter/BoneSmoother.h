#pragma once

#include <iostream>
#include <vector>

#include "Core/Math/OneEuroFilter.hpp"
#include "Utils/Timer.hpp"

using namespace std;

class BoneSmoother {

public:

    BoneSmoother();
    ~BoneSmoother();

    void Update(float* Bone);
    void GetUpdatedBone(float* Bone);

private:

    float mBone[3];
    one_euro::OneEuroFilter mBoneOneEuro[3];

    // One Euro filter
    double mFrequency = 18.0;
    double mMincutoff = 1.0;
    double mBeta = 10.0;
    double mDcutoff = 1.0 ;   // this one should be ok

    Timer mTimer;
    double mTimestamp;

};