
#include <iostream>
 
#include "LibMocap.h"
//#include "Mocap.h"

#include "VideoPlayer.hpp" 

int main()
{
    int cameraId = 0;
    int frameWidth = 640;
    int frameHeight = 480;

    bool useVideo = true;
    //bool useVideo = false;
    //string videoPath = "Webcam.mp4";
    string videoPath = "C:\\Users\\andrew\\Videos\\AvatarCam\\Test Videos\\MouthOpenClose.mp4";
    //string videoPath = "/home/andrew/projects/MHFormer/demo/video/TurnUpperBody.mp4";
    //string videoPath = "/home/andrew/projects/MHFormer/demo/video/SquatDown.mp4";
    //string videoPath = "/home/andrew/projects/MHFormer/demo/video/Dance1.mp4";
    //string videoPath = "/home/andrew/projects/MHFormer/demo/video/Dance2.mp4";
    //string videoPath = "/home/andrew/projects/MHFormer/demo/video/PosesMediapipeCanntSupport.mp4";

    VideoPlayer videoPlayer;
    VideoCapture capture;
    int numFrames = -1;

    if (useVideo) {

        videoPlayer.Open(videoPath, true);
        numFrames = videoPlayer.GetVideoLength();

    }
    else {

        capture = VideoCapture(cameraId);
        capture.set(CAP_PROP_FRAME_WIDTH, frameWidth);
        capture.set(CAP_PROP_FRAME_HEIGHT, frameHeight);

        if (!capture.isOpened()) {
            printf("Failed to open webcam. \n");
            return 1;
        }

        numFrames = 100000000;

    }

    string msg;
    string libPath;
    string modelPath;

    MocapInit(frameWidth, frameHeight);

    Mat frame, imageInput, imageDiag;

    bool isFaceDetected = false;
    const int numBlendshapes = 52;
    vector<float> blendshapes(numBlendshapes);

    int keyCode = -1;
    int frameIndex = -1;
    while (true) {

        frameIndex += 1;
        if (frameIndex > numFrames - 1) {
            break;
        }

        if (useVideo) {

            videoPlayer.Read(frame);

        }
        else {

            // Read frame 
            if (!capture.read(frame))
            {
                printf("There is no frame available.");
                break;
            }
        }

        // Resize image
        cv::resize(frame, frame, cv::Size(frameWidth, frameHeight));

        // Detect
        MocapDetect(frame);

        isFaceDetected = MocapIsFaceDetected();

        float* p;
        p = MocapGetBlendshapes();

        for (int i = 0; i < numBlendshapes; i++) {
            blendshapes[i] = p[i];
        }

        cout << "isFaceDetected: " << isFaceDetected << endl;
        cout << "blendshapes[0]: " << blendshapes[0] << endl;
        cout << "blendshapes[10]: " << blendshapes[10] << endl;

        float headTransform[10];
        p = MocapGetHeadTransform();
        for (int i = 0; i < 10; i++) {
            headTransform[i] = p[i];
        }

        cout << "headTransform[4]: " << headTransform[4] << endl;
        cout << "headTransform[9]: " << headTransform[9] << endl;

        imshow("Input", frame);

        // Quit
        keyCode = waitKey(1);
        if (char(keyCode) == 'q') {
            break;
        }

    }

    // Finalization
    if (useVideo) {
        videoPlayer.Close();
    }
    else {
        capture.release();
    }


    MocapFinalize();

    cout << "End of run." << endl;


}

