#include "pch.h"

#include "head_stabilizer.h"


HeadStabilizer::HeadStabilizer() {

    float noseStdDevC = 0.03;
    float leftEarStdDevC = 0.001;
    float rightEarStdDevC = 0.001;
    
    mNoseAnalyzer.SetStdDevC(noseStdDevC);
    mLeftEarAnalyzer.SetStdDevC(leftEarStdDevC);
    mRightEarAnalyzer.SetStdDevC(rightEarStdDevC);

}

HeadStabilizer::~HeadStabilizer() {
}

void HeadStabilizer::Process(float (&Pose)[mNumLandmarks][mDims]) {

    float noseSignal;
    float leftEarSignal;
    float rightEarSignal;
    
    math_utils::VecNorm(noseSignal, Pose[mINose]);
    math_utils::VecNorm(leftEarSignal, Pose[mILeftEar]);
    math_utils::VecNorm(rightEarSignal, Pose[mIRightEar]);

    mNoseAnalyzer.Process(noseSignal);
    mLeftEarAnalyzer.Process(leftEarSignal);
    mRightEarAnalyzer.Process(rightEarSignal);

    bool bIsNoseStable = mNoseAnalyzer.IsSignalStable(); 
    bool bIsLeftEarStable = mLeftEarAnalyzer.IsSignalStable(); 
    bool bIsRightEarStable = mRightEarAnalyzer.IsSignalStable(); 

    bool isMoving = !bIsNoseStable;
    if (isMoving) {
        mIsStable = true;
    } else {
        mIsStable = bIsLeftEarStable && bIsRightEarStable;
    }

    /*
    cout << "------- " << endl;
    cout << "Nose.z: " << Pose[mINose][2] << endl;
    cout << "mNoseAnalyzer.GetStdDevC(): " << mNoseAnalyzer.GetStdDevC() << endl;
    cout << "mNoseAnalyzer.GetStdDev(): " << mNoseAnalyzer.GetStdDev() << endl;
    cout << "LeftEar.z: " << Pose[mILeftEar][2] << endl;
    cout << "mLeftEarAnalyzer.GetStdDevC(): " << mLeftEarAnalyzer.GetStdDevC() << endl;
    cout << "mLeftEarAnalyzer.GetStdDev(): " << mLeftEarAnalyzer.GetStdDev() << endl;
    cout << "RightEar.z: " << Pose[mIRightEar][2] << endl;
    cout << "mRightEarAnalyzer.GetStdDev(): " << mRightEarAnalyzer.GetStdDev() << endl;
    cout << "------- " << endl;

    cout << "IsMoving: " << isMoving << endl;
    cout << "mIsNoseStable: " << bIsNoseStable << endl;
    cout << "mIsStable: " << mIsStable << endl;
    cout << "mIsLeftEarStable: " << bIsLeftEarStable << endl;
    cout << "mIsRightEarStable: " << bIsRightEarStable << endl;
    */

    if (mIsStable) {
        CopyHead(mPoseSaved, Pose);
    } else {
        CopyHead(Pose, mPoseSaved);
    }

}

void HeadStabilizer::CopyHead(float (&Target)[33][4], float (&Source)[33][4]) {

    for (int j=0; j < 4; j++) {
        for (int i=0; i < 11; i++) {
            Target[i][j] = Source[i][j];
        }
    }

}
bool HeadStabilizer::IsStable() {
    return mIsStable;
}