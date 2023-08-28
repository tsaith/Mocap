#pragma once

#include "math_utils.h"

#include <memory>
#include <deque>
#include <iostream>

using namespace std;

class SignalAnalyzer
{

public:
    
    SignalAnalyzer(int NumHist);
    ~SignalAnalyzer();

    void Process(float Data); 

    bool IsSignalStable();
    float GetMean();
    float GetStdDev();
    float GetLastValidValue();

    void SetStdDevC(float Value);
    float GetStdDevC();

    void SetExludeOutlier(bool Value);
    void SetOutlierThreshold(float Value);

private:

    bool IsOutlier(float Value);

    int mNumHist;
    deque<float> mDataHist;

    float mMean = 0.0;
    float mStdDev = 0.0;
    float mStdDevC = 0.0005;

    bool mIsSignalStable = false;

    float mLastValidValue;
    float mOutlierThreshold = 1.0e20;

    bool mExcludeOutlier = false;

};