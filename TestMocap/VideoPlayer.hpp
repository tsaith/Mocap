#pragma once

#pragma once

#include <iostream>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <opencv2/opencv.hpp>
#else
#include <opencv2/opencv.hpp>
#endif

using namespace std;
using namespace cv;


class VideoPlayer {

public:

    VideoPlayer() {
    }

    ~VideoPlayer() {
        Close();
    }

    void Open(string VideoPath, bool IsCyclic = true) {

        mVideoPath = VideoPath;

        mIsCyclic = IsCyclic;

        mCapture.open(mVideoPath);

        if (mCapture.isOpened()) {

            mVideoLength = int(mCapture.get(cv::CAP_PROP_FRAME_COUNT));
            mCapture.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));

        }
        else {
            cout << "Error: failed to open the video: " << mVideoPath << endl;
            exit(0);
        }

    }

    int Read(Mat& image) {

        int state;
        try {
            state = mCapture.read(image);
        }
        catch (std::exception& e) { // exception should be caught by reference
            cout << "VideoPlaer: exception error is" << e.what() << endl;
        }

        if (state < 0 && mIsCyclic) {
            cout << "VideoPlayer rewind" << endl;
            mCapture.set(CAP_PROP_POS_FRAMES, 0);
            state = mCapture.read(image);
        }

        return state;

    }

    int GetVideoLength() {
        return mVideoLength;
    }

    void Close() {

        if (mCapture.isOpened()) mCapture.release();

    }

private:

    string mVideoPath = "video.mp4";
    bool mIsCyclic = true;

    VideoCapture mCapture;
    int mVideoLength = -1;

};
