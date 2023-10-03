#pragma once

#include <opencv2/opencv.hpp>

using namespace cv;


class Timer {
public:

    void Tic()
    {
        mCountBegin = getTickCount();
    };

    void Toc()
    {

        mCountEnd = getTickCount();
        mCountDelta = mCountEnd - mCountBegin;
        mFPS = static_cast<float>(getTickFrequency()/mCountDelta);
        mDt = 1.0f/mFPS;

        if (mDt > 1.0e8) mCountBegin = mCountEnd;

    };

    void Delay(int dt) // dt is in milliseconds
    {
        // to do.
    }

    float GetElapsedTime() { return mDt; };
    float GetFPS() { return mFPS;};


private:

    int64 mCountBegin = 0;
    int64 mCountEnd = 0;
    int64 mCountDelta = 0;

    float mFPS = 0.0;
    float mDt = 0.0;

};