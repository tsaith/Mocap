#pragma once

#include "Utils/Skel/SignalAnalyzer.h"

#include <deque>
#include <iostream>

using namespace std;

class HandStabilizer 
{

public:

    HandStabilizer();
    ~HandStabilizer();

    void Process(float (&Hand)[21][4], float (&Wrist)[3]);
    bool IsStable();

private:

    void CopyHand(float (&Target)[21][4], float (&Source)[21][4]);

    bool mIsStable = false;
    float mHandSaved[21][4];

    const int mNumLandmarks = 21;
    const int mDims = 3;

    int mIWrist = 0;
    int mIThumb = 4;
    int mIIndex = 8;
    int mIMiddle = 12;
    int mIRing = 16;
    int mIPinky = 20;

    const int mNumHist = 5;
    
    SignalAnalyzer mWristAnalyzer = SignalAnalyzer(mNumHist);

    SignalAnalyzer mHandWristAnalyzer = SignalAnalyzer(mNumHist);
    SignalAnalyzer mThumbAnalyzer = SignalAnalyzer(mNumHist);
    SignalAnalyzer mIndexAnalyzer = SignalAnalyzer(mNumHist);
    SignalAnalyzer mMiddleAnalyzer = SignalAnalyzer(mNumHist);
    SignalAnalyzer mRingAnalyzer = SignalAnalyzer(mNumHist);
    SignalAnalyzer mPinkyAnalyzer = SignalAnalyzer(mNumHist);

};