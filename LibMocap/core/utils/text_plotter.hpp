#ifndef TEXT_PLOTTER_H
#define TEXT_PLOTTER_H

//#include <opencv2/opencv.hpp>
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    #include <opencv2/opencv.hpp>
#else
    #include "mediapipe/framework/port/opencv_highgui_inc.h"
    #include "mediapipe/framework/port/opencv_imgproc_inc.h"
    #include "mediapipe/framework/port/opencv_video_inc.h"
#endif

using namespace std;

class TextPlotter {
public:

    TextPlotter(int FontScale=0.8, cv::Scalar color=cv::Scalar(255, 255, 0),
        int Thickness=1) {

        mFontScale = FontScale;
        mColor = color;
        mThickness = Thickness;

        mDefaultPosX = 10;
        mDefaultPosY = 30;
        mPosX = mDefaultPosX;
        mPosY = mDefaultPosY;
    }

    void putText(cv::Mat &image, string msg) {

        cv::putText(image, msg.c_str(),
            cv::Point(mPosX, mPosY), //top-left position
            cv::FONT_HERSHEY_DUPLEX,
            mThickness, mColor);

        mPosY += mOffsetY;
    }

    void ResetPosition() {

        mPosX = mDefaultPosX;
        mPosY = mDefaultPosY;

    };

private:

    int mDefaultPosX;
    int mDefaultPosY;
    int mPosX;
    int mPosY;

    int mOffsetY = 30;

    int mFontFace = cv::FONT_HERSHEY_DUPLEX;
    float mFontScale;
    cv::Scalar mColor;
    int mThickness;

};

#endif