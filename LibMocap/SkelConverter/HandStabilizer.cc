#include "pch.h"

#include "HandStabilizer.h"


HandStabilizer::HandStabilizer() {


    float wristStdDevC = 5.0e-4;
    float HandwristStdDevC = 7.0e-3;
    float fingerStdDevC = 5.0e-6;

    mWristAnalyzer.SetStdDevC(wristStdDevC);
    mHandWristAnalyzer.SetStdDevC(HandwristStdDevC);
    mThumbAnalyzer.SetStdDevC(fingerStdDevC);
    mIndexAnalyzer.SetStdDevC(fingerStdDevC);
    mMiddleAnalyzer.SetStdDevC(fingerStdDevC);
    mRingAnalyzer.SetStdDevC(fingerStdDevC);
    mPinkyAnalyzer.SetStdDevC(fingerStdDevC);

}

HandStabilizer::~HandStabilizer() {
}

void HandStabilizer::Process(float (&Hand)[21][4], float (&Wrist)[3]) {

    float wristSignal;
    float hand_wristSignal;
    float thumbSignal;
    float indexSignal;
    float middleSignal;
    float ringSignal;
    float pinkySignal;
    
    wristSignal = Wrist[0];
    hand_wristSignal = Hand[mIWrist][0];
    thumbSignal = Hand[mIThumb][0];
    indexSignal = Hand[mIIndex][0];
    middleSignal = Hand[mIMiddle][0];
    ringSignal = Hand[mIRing][0];
    pinkySignal = Hand[mIPinky][0];

    mWristAnalyzer.Process(wristSignal);
    mHandWristAnalyzer.Process(hand_wristSignal);
    mThumbAnalyzer.Process(thumbSignal);
    mIndexAnalyzer.Process(indexSignal);
    mMiddleAnalyzer.Process(middleSignal);
    mRingAnalyzer.Process(ringSignal);
    mPinkyAnalyzer.Process(pinkySignal);

    bool bIsWristStable = mWristAnalyzer.IsSignalStable(); 
    bool bIsHandWristStable = mHandWristAnalyzer.IsSignalStable(); 
    bool bIsThumbStable = mThumbAnalyzer.IsSignalStable(); 
    bool bIsIndexStable = mIndexAnalyzer.IsSignalStable(); 
    bool bIsMiddleStable = mMiddleAnalyzer.IsSignalStable();  
    bool bIsRingStable = mRingAnalyzer.IsSignalStable(); 
    bool bIsPinkyStable = mPinkyAnalyzer.IsSignalStable(); 
    
    bool isMoving = !bIsWristStable;
    if (isMoving) {
        mIsStable = true;
    } else {
        //mIsStable = bIsThumbStable && bIsIndexStable && bIsMiddleStable &&
        //    bIsRingStable && bIsPinkyStable;
        mIsStable = bIsHandWristStable;
    }

    /*
    cout << "wristSignal: " << wristSignal << endl;
    cout << "mWristAnalyzer.GetStdDev(): " << mWristAnalyzer.GetStdDev() << endl;
    cout << "mWristAnalyzer.GetStdDevC(): " << mWristAnalyzer.GetStdDevC() << endl;
    cout << "mThumbAnalyzer.GetStdDev(): " << mThumbAnalyzer.GetStdDev() << endl;
    cout << "mIndexAnalyzer.GetStdDev(): " << mIndexAnalyzer.GetStdDev() << endl;
    cout << "mMiddleAnalyzer.GetStdDev(): " << mMiddleAnalyzer.GetStdDev() << endl;
    cout << "mRingAnalyzer.GetStdDev(): " << mRingAnalyzer.GetStdDev() << endl;
    cout << "mPinkyAnalyzer.GetStdDev(): " << mPinkyAnalyzer.GetStdDev() << endl;

    cout << "mIsStable: " << mIsStable << endl;
    cout << "isMoving: " << isMoving << endl;
    cout << "bIsThumbStable: " << bIsThumbStable << endl;
    cout << "bIsIndexStable: " << bIsIndexStable << endl;
    cout << "bIsMiddleStable: " << bIsMiddleStable << endl;
    cout << "bIsRingStable: " << bIsRingStable << endl;
    cout << "bIsPinkyStable: " << bIsPinkyStable << endl;
    */

    if (mIsStable) {
        CopyHand(mHandSaved, Hand);
    } else {
        CopyHand(Hand, mHandSaved);
    }

}

void HandStabilizer::CopyHand(float (&Target)[21][4], float (&Source)[21][4]) {

    for (int j=0; j < 4; j++) {
        for (int i=0; i < 21; i++) {
            Target[i][j] = Source[i][j];
        }
    }

}

bool HandStabilizer::IsStable() {
    return mIsStable;
}