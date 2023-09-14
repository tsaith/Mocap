#pragma once

#include "StablePoint.hpp"
#include "SignalAnalyzer.h"

#include <deque>
#include <iostream>

using namespace std;

class BoneStabilizer
{

public:

    BoneStabilizer() {
    }

    ~BoneStabilizer() {

    }

    void Update(float* Point) {
        mStablePoint.Update(Point);
    }

    void SetDistanceC(float Distance) {
        mStablePoint.SetDistanceC(Distance);
    }

    float GetDistanceC() {
        return mStablePoint.GetDistanceC();
    }

    float GetDistance() {
        return mStablePoint.GetDistance();
    }

    float GetRatio() {
        return mStablePoint.GetRatio();
    }

private:

    bool mIsStable = false;
    StablePoint mStablePoint;

};