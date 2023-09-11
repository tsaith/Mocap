
#include <iostream>
 
#include "LibMocap.h"
#include "TestDiag.h"

#include "VideoPlayer.hpp" 
#include "TextPlotter.hpp" 
#include "Timer.hpp" 

using namespace test_diag;

typedef vector<vector<float>> FVector2D;

FVector2D InitVec2D(int Rows, int Cols) {
    FVector2D vec2D(Rows, vector<float>(Cols, 0.0f));
    return vec2D;
}

int main()
{
    int cameraId = 0;
    int imageWidth = 640;
    int imageHeight = 480;

    bool useVideo = true;
    //bool useVideo = false;
    //string videoPath = "C:/Users/andrew/Videos/MocapTestVideos/TurnHead.mp4";
    string videoPath = "C:/Users/andrew/Videos/MocapTestVideos/TurnHead_720p.mp4";

    // Diagnostics
    int numDiagInterval = 4;

    VideoPlayer videoPlayer;
    VideoCapture capture;
    int numFrames = -1;

    if (useVideo) {

        videoPlayer.Open(videoPath, true);
        numFrames = videoPlayer.GetVideoLength();

    }
    else {

        capture = VideoCapture(cameraId);
        capture.set(CAP_PROP_FRAME_WIDTH, imageWidth);
        capture.set(CAP_PROP_FRAME_HEIGHT, imageHeight);

        if (!capture.isOpened()) {
            printf("Failed to open webcam. \n");
            return 1;
        }

        numFrames = 100000000;

    }

    string libPath;
    string modelPath;

    MocapInit(imageWidth, imageHeight);

    Mat frame, imageInput, imageDiag;

    bool isFaceDetected = false;
    const int numBlendshapes = 52;
    vector<float> blendshapes(numBlendshapes);

    // Diagnostic
    float dt, fps;
    TestDiag diag;
    diag.Init(imageWidth, imageHeight);

    string msg;
    Timer timer;
    TextPlotter textPlotter;

    int i;
    const int numSkelJoints = 68;
    FVector2D skelBones;
    FVector2D skelQuats;

    skelBones = InitVec2D(numSkelJoints, 3);
    skelQuats = InitVec2D(numSkelJoints, 4);


    int keyCode = -1;
    int frameIndex = -1;
    while (true)
    {

        frameIndex += 1;
        if (frameIndex > numFrames - 1)
        {
            break;
        }

        if (useVideo)
        {

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
        cv::resize(frame, frame, cv::Size(imageWidth, imageHeight));

        // Detect
        timer.Tic();
        MocapDetect(frame);
        timer.Toc();

        if (frameIndex % numDiagInterval == 0) {
            MocapDiagnose();
        }

        dt = timer.GetElapsedTime();
        fps = timer.GetFPS();

        isFaceDetected = MocapIsFaceDetected();
        cout << "isFaceDetected: " << isFaceDetected << endl;

        float* p; 
        p = MocapGetBlendshapes();

        for (int i = 0; i < numBlendshapes; i++)
        {
            blendshapes[i] = p[i];
        }

        p = MocapGetHeadTransform();
        cout << "Head qx: " << p[0] << endl;
        cout << "Head qy: " << p[1] << endl;
        cout << "Head qz: " << p[2] << endl;
        cout << "Head w: " << p[3] << endl;
  
        for (i = 0; i < numSkelJoints; i++)
        {
            p = MocapGetSkelTransform(i);

            skelQuats[i][0] = p[0];
            skelQuats[i][1] = p[1];
            skelQuats[i][2] = p[2];
            skelQuats[i][3] = p[3];

            skelBones[i][0] = p[4];
            skelBones[i][1] = p[5];
            skelBones[i][2] = p[6];
        }

        i = 15;
        cout << "RightHand x: " << skelBones[i][0] << endl;
        cout << "RightHand y: " << skelBones[i][1]  << endl;
        cout << "RightHand z: " << skelBones[i][2]  << endl;

        // Diagostics
        diag.SetInputImage(frame);
        diag.SetFps(fps);
        diag.Process();

        Mat diagImage = diag.GetDiagImage();

        imshow("Win", diagImage);

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

