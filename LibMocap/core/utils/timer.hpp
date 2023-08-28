#pragma once

#include <opencv2/opencv.hpp>

using namespace cv;


class Timer {
public:

    void tic()
    {
        mCountBegin = getTickCount();
    };

    void toc()
    {

        mCountEnd = getTickCount();
        mCountDelta = mCountEnd - mCountBegin;
        mFPS = getTickFrequency()/mCountDelta;
        mDt = 1.0/mFPS;

        if (mDt > 1.0e8) mCountBegin = mCountEnd;

    };

    void Delay(int dt) // dt is in milliseconds
    {
        // to do.
    }

    double GetElapsedTime() { return mDt; };
    double GetDt() { return mDt; };
    double GetFPS() { return mFPS;};


private:

    int64 mCountBegin = 0;
    int64 mCountEnd = 0;
    int64 mCountDelta = 0;

    float mFPS = 0.0;
    float mDt = 0.0;

};