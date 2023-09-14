#include "pch.h"

#include "QuatSmoother.h"


QuatSmoother::QuatSmoother() {

    mTimer.Tic();

    // One Euro filter
    double frequency = 18.0;
    double mincutoff = 1.0;
    double beta = 1.0;
    double dcutoff = 1.0 ;   // this one should be ok
    for (int i=0; i < 4; i++) {
        mQuatOneEuro[i].Init(frequency, mincutoff, beta, dcutoff);
    }

}

QuatSmoother::~QuatSmoother() {
}

void QuatSmoother::Update(float* quat) {

    mTimer.Toc();
    mTimestamp = mTimer.GetElapsedTime();

    vector<float> dataHist;
    int iHist;
    for (int i=0; i < 4; i++) {

        // Check if the value is NaN or not
        if (!isnan(quat[i])) {
            mQuat[i][0] = quat[i];
        }

        if (i == 0) {
            CorrectAngle(mQuat[i], dataHist);
        } else {
            CorrectRotation(mQuat[i], dataHist);
        }

        mQuatOut[i] = mQuatOneEuro[i].Filter(mQuat[i][0], mTimestamp);

        if (i == 0) {
            if (mQuatOut[i] < 0.0) mQuatOut[i] = 1.0e-5;
            if (mQuatOut[i] > 1.0) mQuatOut[i] = 0.99;
        } else {
            if (mQuatOut[i] < -1.0) mQuatOut[i] = -0.99;
            if (mQuatOut[i] > 1.0) mQuatOut[i] = 0.99;
        }

        // Update history data
        for (iHist=mNumHist-1; iHist > 0; iHist--) {
            mQuat[i][iHist] = mQuat[i][iHist-1]; 
        }

    }


}

void QuatSmoother::CorrectAngle(float* DataIn, vector<float> &DataOut) {

    DataOut = vector<float>(DataIn, DataIn+mNumHist);

    bool isCloseToPi = false;
    float degToRad = 3.1415926/180.0;
    float angleC = 170.0 * degToRad;
    float angle;

    for (int i=0; i < DataOut.size(); i++) {
        angle = DataOut[i];
        if (angle > angleC) isCloseToPi = true;
    }

    if (isCloseToPi) {
        for (int i=0; i < DataOut.size(); i++) {
            if(DataOut[i] < angleC) DataOut[i] = angleC;
        }
    }

}

void QuatSmoother::CorrectRotation(float* DataIn, vector<float> &DataOut) {

    DataOut = vector<float>(DataIn, DataIn+mNumHist);

    int numPos = 0;
    int numNeg = 0;
    for (int i=0; i < DataOut.size(); i++) {
        if (DataOut[i] > 0) numPos += 1;
    }

    numNeg = mNumHist - numPos;

    for (int i=0; i < DataOut.size(); i++) {

        if (numPos >= numNeg) {
            DataOut[i] = abs(DataOut[i]);
        } else {
            DataOut[i] = -abs(DataOut[i]);
        }

    }

}

void QuatSmoother::GetUpdatedQuat(float* quat) {

    for (int i=0; i < 4; i++) {
        quat[i] = mQuatOut[i];
    }

}
