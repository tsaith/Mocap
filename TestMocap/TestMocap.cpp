
#include <iostream>
 
#include "LibMocap.h"

#include "VideoPlayer.hpp" 
#include "TextPlotter.hpp" 
#include "Timer.hpp" 

int main()
{
    int cameraId = 0;
    int frameWidth = 640;
    int frameHeight = 480;

    //bool useVideo = true;
    bool useVideo = false;
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

    string libPath;
    string modelPath;

    MocapInit(frameWidth, frameHeight);

    Mat frame, imageInput, imageDiag;

    bool isFaceDetected = false;
    const int numBlendshapes = 52;
    vector<float> blendshapes(numBlendshapes);

    // Diagnostic
    float dt, fps;
    string msg;
    Timer timer;
    TextPlotter textPlotter;

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
        timer.Tic();
        MocapDetect(frame);
        timer.Toc();

        dt = timer.GetElapsedTime();
        fps = timer.GetFPS();


        isFaceDetected = MocapIsFaceDetected();

        float* p; 
        p = MocapGetBlendshapes();

        for (int i = 0; i < numBlendshapes; i++) {
            blendshapes[i] = p[i];
        }

        p = MocapGetSkelTransform(15);

        cout << "RightHand qx: " << p[0] << endl;
        cout << "RightHand x: " << p[4] << endl;
        cout << "RightHand y: " << p[5] << endl;
        cout << "RightHand z: " << p[6] << endl;
  
        // Draw messages
        textPlotter.ResetPosition();
        msg = "fps: " + to_string(int(fps));
        textPlotter.putText(frame, msg);

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

