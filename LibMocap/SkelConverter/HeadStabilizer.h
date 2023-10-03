#pragma once

#include "Utils/Skel/SignalAnalyzer.h"

#include <deque>
#include <iostream>

using namespace std;

class HeadStabilizer
{

public:

    HeadStabilizer();
    ~HeadStabilizer();

    static const int mNumLandmarks = 33;
    static const int mDims = 4;

    void Process(float (&Pose)[mNumLandmarks][mDims]);
    bool IsStable();

private:

    void CopyHead(float (&Target)[mNumLandmarks][mDims], float (&Source)[mNumLandmarks][mDims]);

    bool mIsStable = false;
    float mPoseSaved[mNumLandmarks][mDims];

    int mINose = 0;
    int mILeftEar = 7;
    int mIRightEar = 8;

    const int mNumHist = 5;
    
    SignalAnalyzer mNoseAnalyzer = SignalAnalyzer(mNumHist);
    SignalAnalyzer mLeftEarAnalyzer = SignalAnalyzer(mNumHist);
    SignalAnalyzer mRightEarAnalyzer = SignalAnalyzer(mNumHist);

};