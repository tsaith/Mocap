#pragma once

#include "stable_value.hpp"

#include <iostream>

using namespace std;
using namespace math_utils;

class StablePoint
{

public:

    void Update(float* Point) {

        if (mIsFirstPoint) {

            VecCopy(mCurrentPoint, Point);
            mIsUpdated = true;
            mNumSkips = 0;
            mIsFirstPoint = false;

        } else {

            if (mNumSkips > mNumMaxSkips) mNumSkips = 0;

            VecSubstract(mVec, Point, mCurrentPoint);
            VecNorm(mDistance, mVec); 

            if (mNumSkips < mNumSkipsC) {
                mRatio = mRatioMoving;
            } else {
                mRatio = mRatioStatic;
            }

            if (mDistance > mRatio*mDistanceC) {
                VecCopy(mCurrentPoint, Point);
                mIsUpdated = true;
                mNumSkips = 0;
            } else {
                mIsUpdated = false;
                mNumSkips += 1;
            }

        }

        GetCurrentPoint(Point);

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
    
    void GetCurrentPoint(float* Point) {
        VecCopy(Point, mCurrentPoint);
    }

    int GetNumSkips() {
        return mNumSkips;
    }

    bool IsUpdated() {
        return mIsUpdated;
    }

    float GetRatio() {
        return mRatio;
    }

    void SetRatioStatic(float Ratio) {
        mRatioStatic = Ratio;
    }

    float GetRatioStatic() {
        return mRatioStatic;
    }

private:

    static constexpr int mDims = 3;

    bool mIsFirstPoint = true;

    float mCurrentPoint[mDims];
    float mMeasuredPoint[mDims];
    float mVec[mDims];

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