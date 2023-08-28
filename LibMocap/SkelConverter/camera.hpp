#ifndef CAMERA_H
#define CAMERA_H 

#include <iostream>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    #include <opencv2/opencv.hpp>
#else
    #include "mediapipe/framework/port/opencv_highgui_inc.h"
    #include "mediapipe/framework/port/opencv_imgproc_inc.h"
    #include "mediapipe/framework/port/opencv_video_inc.h"
#endif
#include "logger.h"

using namespace std;
using namespace cv;


class Camera {

public:

    Camera() {
    }

    ~Camera() {
        Close();
    }

    void Open(int index, int width, int height) {
        try {
            mIndex = index;
            mWidth = width; 
            mHeight = height;
        
            mCapture.open(index);

            if(mCapture.isOpened()) {
                mCapture.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));
                mCapture.set(cv::CAP_PROP_FRAME_WIDTH, mWidth);
                mCapture.set(cv::CAP_PROP_FRAME_HEIGHT, mHeight);
                mCapture.set(cv::CAP_PROP_FPS, mFPS);
            }
            else {
                LOG(ERROR) << " Failed to open the camera.";
            }
        }
        catch(cv::Exception e) {
            LOG(ERROR) << e.what();
        }
    }

    int Read(Mat& image) {
        try {
            int state = mCapture.read(image);
            
            return state;
        }
        catch(cv::Exception e) {
            LOG(ERROR) << e.what();
            
            return -1;
        }
    }

    void Close() {
        if(mCapture.isOpened()) mCapture.release();
    }

    
    int Video(string file) {
        mCapture.open(file);
        if(!mCapture.isOpened()) {
            cout << "Error: failed to open the video." << endl;

            return -1;
        }
        
        mVideoCnt = (int)mCapture.get(cv::CAP_PROP_FRAME_COUNT);

        return mVideoCnt;
    }

    int VideoRead(Mat image) {
        int state = mCapture.read(image);
        cout << state << endl;
        mFrameCnt += 1;
        if(mFrameCnt == mVideoCnt) {
            mFrameCnt = 0;
            mCapture.set(cv::CAP_PROP_POS_FRAMES, 0);
        }

        return state;
    }

    int Error=0;

private:
    int mIndex = 0;
    int mWidth = 640;
    int mHeight = 480;
    int mFPS = 30;
    int mVideoCnt = 0;
    int mFrameCnt = 0;

    VideoCapture mCapture;

};

#endif // CAMERA_H
