#include "pch.h"

#include "SignalAnalyzer.h"


SignalAnalyzer::SignalAnalyzer(int NumHist) {

    mNumHist = NumHist;

}

SignalAnalyzer::~SignalAnalyzer() {
}

void SignalAnalyzer::Process(float Data) {


    float value = Data;

    // Take care the outlier
    if (mExcludeOutlier) {

        if (mDataHist.size() > mNumHist) {
            if (IsOutlier(value)) {
                value = mMean;
            }
        }

    }

    mDataHist.push_back(value);

    if (mDataHist.size() > mNumHist) {
        mDataHist.pop_front();
    }

    size_t num = mDataHist.size();
    auto vecData = vector<float>(mDataHist.begin(), mDataHist.end());

    mMean = zen_math::EstimateMean(vecData);
    mStdDev = zen_math::EstimateStandardDeviation(vecData);

    // Signal is stable or not
    if (mStdDev < mStdDevC) {
        mIsSignalStable = true;
        mLastValidValue = Data;
    } else {
        mIsSignalStable = false;
    }

}

bool SignalAnalyzer::IsSignalStable() {
    return mIsSignalStable;
}

float SignalAnalyzer::GetMean() {
    return mMean;
}

float SignalAnalyzer::GetStdDev() {
    return mStdDev;
}

float SignalAnalyzer::GetLastValidValue() {
    return mLastValidValue;
}

void SignalAnalyzer::SetStdDevC(float Value) {
    mStdDevC = Value;
}

float SignalAnalyzer::GetStdDevC() {
    return mStdDevC;
}

void SignalAnalyzer::SetExludeOutlier(bool Value) {
    mExcludeOutlier = Value;
}

void SignalAnalyzer::SetOutlierThreshold(float Value) {
    mOutlierThreshold = abs(Value);
}

bool SignalAnalyzer::IsOutlier(float Value) {

    bool bResult = false;

    float diffAbs = abs(Value - mMean);

    if (diffAbs > mOutlierThreshold) {
        bResult = true;
    }

    return bResult;

}