#include "pch.h"

#include "BoneSmoother.h"


BoneSmoother::BoneSmoother() {

    mTimer.Tic();

    for (int i=0; i < 3; i++) {
        mBoneOneEuro[i].Init(mFrequency, mMincutoff, mBeta, mDcutoff);
    }

}

BoneSmoother::~BoneSmoother() {
}

void BoneSmoother::Update(float* Bone) {

    mTimer.Toc();
    mTimestamp = mTimer.GetElapsedTime();

    for (int i=0; i < 3; i++) {

        // Check if the value is NaN or not
        if (!isnan(Bone[i])) {
            mBone[i] = mBoneOneEuro[i].Filter(Bone[i], mTimestamp);
        }

    }


}

void BoneSmoother::GetUpdatedBone(float* Bone) {

    for (int i=0; i < 3; i++) {
        Bone[i] = mBone[i];
    }

}
