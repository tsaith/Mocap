#pragma once

#include <iostream>

#include "Core/Math/MathLib.h"

using namespace std;
using namespace zen_math;

class StableValue
{

public:

    void Update(float &Value) {

        if (mIsFirstValue) {

            mCurrentValue = Value;
            mIsUpdated = true;
            mNumSkips = 0;
            mIsFirstValue = false;

        } else {

            if (mNumSkips > mNumMaxSkips) mNumSkips = 0;

            if (mNumSkips < mNumSkipsC) {
                mRatio = mRatioMoving;
            } else {
                mRatio = mRatioStatic;
            }

            mDistance =  abs(Value - mCurrentValue);
            if (mDistance > mRatio*mDistanceC) {
                mCurrentValue = Value;
                mIsUpdated = true;
                mNumSkips = 0;
            } else {
                mIsUpdated = false;
                mNumSkips += 1;
            }

        }

        Value = mCurrentValue;

    }

    void SetDistanceC(float Distance) {
        mDistanceC = Distance;
    }

    float GetDistanceC() {
        return mDistanceC;
    }

    float GetDistance() {
        return mDistance;
    }
    
    float GetCurrentValue() {
        return mCurrentValue;
    }

    int GetNumSkips() {
        return mNumSkips;
    }

    bool IsUpdated() {
        return mIsUpdated;
    }

private:

    bool mIsFirstValue = true;

    float mCurrentValue;
    float mMeasuredValue;

    float mDistance;
    float mDistanceC = 0.05;

    float mRatio = 1.0;
    float mRatioMoving = 1.0;
    float mRatioStatic = 2.0;

    int mNumSkips = 0;
    int mNumSkipsC = 10;
    int mNumMaxSkips = 10000;

    bool mIsUpdated = false;

};