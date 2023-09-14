#pragma once

#include "StableValue.hpp"
#include "StablePoint.hpp"
#include "SignalAnalyzer.h"

#include <deque>
#include <iostream>

using namespace std;

class QuatStabilizer
{

public:

    QuatStabilizer() {
    }

    ~QuatStabilizer() {

    }

    void Update(float* Quat) {


        float q0;
        float direct[3];

        q0 = Quat[0];
        direct[0] = Quat[1];
        direct[1] = Quat[2];
        direct[2] = Quat[3];

        mStableAngle.Update(q0);
        mStableDirect.Update(direct);

        Quat[0] = q0;
        Quat[1] = direct[0];
        Quat[2] = direct[1];
        Quat[3] = direct[2];

    }

    void SetAngleDistanceC(float Distance) {
        mStableAngle.SetDistanceC(Distance);
    }

    float GetAngleDistanceC() {
        return mStableAngle.GetDistanceC();
    }

    void SetDirectDistanceC(float Distance) {
        mStableDirect.SetDistanceC(Distance);
    }

    float GetDirectDistanceC() {
        return mStableDirect.GetDistanceC();
    }

    float GetAngleDistance() {
        return mStableAngle.GetDistance();
    }

    float GetDirectDistance() {
        return mStableDirect.GetDistance();
    }

    bool IsAngleUpdated() {
        return mStableAngle.IsUpdated();
    }

    bool IsDirectUpdated() {
        return mStableDirect.IsUpdated();
    }

private:

    StableValue mStableAngle;
    StablePoint mStableDirect;

};