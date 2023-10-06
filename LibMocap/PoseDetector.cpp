#include "pch.h"

#include "PoseDetector.h"
 

PoseDetector::PoseDetector() {   

    mImageWidth = 0;
    mImageHeight = 0;

    // Set angle used to rotate pose around x-axis
    mMHFormer.SetAngleAroundX(mMHFAngleAroundX);
}

PoseDetector::~PoseDetector() {

    mHRNetPose.Finalize();

}

void PoseDetector::Init(int ImageWidth, int ImageHeight) {

    mImageWidth = ImageWidth; 
    mImageHeight = ImageHeight;


}

void PoseDetector::UseGpu(bool bFlag, int GpuDeviceId)
{

    mUseGpu = bFlag;
    mGpuDeviceId = GpuDeviceId;

}

void PoseDetector::LoadModel(string ModelDir)
{

    mModelDir = ModelDir;

    string modelPath = "";

    // HRNetPose
    mHRNetPose.Init(mImageWidth, mImageHeight);

    modelPath = "C:/Users/andrew/projects/Mocap/x64/Release/TrainedModels/hrnet_coco_w32_256x192.onnx";
    //modelPath = "TrainedModels/hrnet_coco_w32_256x192.onnx";
    mHRNetPose.UseGpu(mUseGpu, mGpuDeviceId);
    mHRNetPose.LoadModel(modelPath);

    mMHFormer.Init(mImageWidth, mImageHeight);
    mMHFormer.UseGpu(mUseGpu);

    //modelPath = "C:\\Users\\andrew\\projects\\Mocap\\x64\\Release\\TrainedModels\\mhformer.onnx";
    modelPath = "C:/Users/andrew/projects/Mocap/x64/Release/TrainedModels/mhformer.onnx";
    mMHFormer.LoadModel(modelPath);

}

void PoseDetector::Detect(Mat& Image)
{
    mImage = Image.clone();

    // Estimate pose 2D 
    mHRNetPose.Detect(mImage);
    mPose2D = mHRNetPose.GetPoseNorm();
    MapPose2DToHolistic(mPose2D, mHolistic);

    // Correct pose
    CorrectPose2D(mHolistic);

    // Calculate pose depth 
    CalculatePoseDepthWithMHFormer(mHolistic);

    // Force hip's depth as zero
    //mHolistic.pose[23][2] = 0.f;
    //mHolistic.pose[24][2] = 0.f;
 
}

void PoseDetector::UpdateHolisticPose(Holistic& Data) 
{

    for (int idim = 0; idim < 3; idim++) {

        Data.pose[0][idim] = mHolistic.pose[0][idim];
        Data.pose[2][idim] = mHolistic.pose[2][idim];
        Data.pose[5][idim] = mHolistic.pose[5][idim];
        Data.pose[7][idim] = mHolistic.pose[7][idim];
        Data.pose[8][idim] = mHolistic.pose[8][idim];
        Data.pose[11][idim] = mHolistic.pose[11][idim];
        Data.pose[12][idim] = mHolistic.pose[12][idim];
        Data.pose[13][idim] = mHolistic.pose[13][idim];
        Data.pose[15][idim] = mHolistic.pose[15][idim];
        Data.pose[14][idim] = mHolistic.pose[14][idim];
        Data.pose[16][idim] = mHolistic.pose[16][idim];
        Data.pose[23][idim] = mHolistic.pose[23][idim];
        Data.pose[24][idim] = mHolistic.pose[24][idim];
        Data.pose[25][idim] = mHolistic.pose[25][idim];
        Data.pose[26][idim] = mHolistic.pose[26][idim];
        Data.pose[27][idim] = mHolistic.pose[27][idim];
        Data.pose[28][idim] = mHolistic.pose[28][idim];

    }

}

// Private methods

void PoseDetector::CorrectPose2D(Holistic& Data)
{

    vector<int> imageSize{ mImageWidth, mImageHeight };

    vector<float> leftShoulder{ 0.f, 0.f };
    vector<float> rightShoulder{ 0.f, 0.f };
    vector<float> leftHip{ 0.f, 0.f };
    vector<float> rightHip{ 0.f, 0.f };
    vector<float> leftElbow{ 0.f, 0.f };
    vector<float> rightElbow{ 0.f, 0.f };
    vector<float> leftWrist{ 0.f, 0.f };
    vector<float> rightWrist{ 0.f, 0.f };

    vector<float> leftKnee{ 0.f, 0.f };
    vector<float> rightKnee{ 0.f, 0.f };
    vector<float> leftAnkle{ 0.f, 0.f };
    vector<float> rightAnkle{ 0.f, 0.f };


    leftShoulder = { Data.pose[11][0], Data.pose[11][1] };
    rightShoulder = { Data.pose[12][0], Data.pose[12][1] };
    leftHip = { Data.pose[23][0], Data.pose[23][1] };
    rightHip = { Data.pose[24][0], Data.pose[24][1] };
    leftElbow = { Data.pose[13][0], Data.pose[13][1] };
    rightElbow = { Data.pose[14][0], Data.pose[14][1] };
    leftWrist = { Data.pose[15][0], Data.pose[15][1] };
    rightWrist = { Data.pose[16][0], Data.pose[16][1] };

    leftKnee = { Data.pose[25][0], Data.pose[25][1] };
    rightKnee = { Data.pose[26][0], Data.pose[26][1] };
    leftAnkle = { Data.pose[27][0], Data.pose[27][1] };
    rightAnkle = { Data.pose[28][0], Data.pose[28][1] };

    // Convert to pixel space
    for (int i = 0; i < 2; i++) {

        leftShoulder[i] *= imageSize[i];
        rightShoulder[i] *= imageSize[i];
        leftHip[i] *= imageSize[i];
        rightHip[i] *= imageSize[i];
        leftElbow[i] *= imageSize[i];
        rightElbow[i] *= imageSize[i];
        leftWrist[i] *= imageSize[i];
        rightWrist[i] *= imageSize[i];

        leftKnee[i] *= imageSize[i];
        rightKnee[i] *= imageSize[i];
        leftAnkle[i] *= imageSize[i];
        rightAnkle[i] *= imageSize[i];

    }
 
    float minRatioShoulderLength = 0.2;
    float shoulderLengthMin = minRatioShoulderLength * mImageWidth;

    float maxRatioShoulderLength = 0.8;
    float shoulderLengthMax = maxRatioShoulderLength * mImageWidth;

    float minRatioOfWidth = 0.2;
    float maxRatioOfWidth = 0.8;
    float minRatioOfHeight = 0.3;
    float maxRatioOfHeight = 0.7;

    float leftBound = minRatioOfWidth * mImageWidth;
    float rightBound = maxRatioOfWidth * mImageWidth;
    float topBound = minRatioOfHeight * mImageHeight;
    float bottomBound = maxRatioOfHeight * mImageHeight;

    float shoulderLength;
    CalculateLengthTwoPoints2D(shoulderLength, leftShoulder, rightShoulder);

    if (shoulderLength < shoulderLengthMin) {
        shoulderLength = shoulderLengthMin;
    }
    if (shoulderLength > shoulderLengthMax) {
        shoulderLength = shoulderLengthMax;
    }

    //cout << "shoulderLength: " << shoulderLength << endl;

    float lengthLeftShoulderHip = 1.0f * shoulderLength;
    if (leftHip[1] > bottomBound) {
        leftHip[1] = leftShoulder[1] + lengthLeftShoulderHip;
    }

    float lengthRightShoulderHip = 1.0f * shoulderLength;
    if (rightHip[1] > bottomBound) {
        rightHip[1] = rightShoulder[1] + lengthRightShoulderHip;
    }

    /*
    cout << "leftHip[0]: " << leftHip[0] << endl;
    cout << "leftHip[1]: " << leftHip[1] << endl;
    cout << "rightHip[0]: " << rightHip[0] << endl;
    cout << "rightHip[1]: " << rightHip[1] << endl;
    */

    // Predict lower body
    leftKnee[0] = leftHip[0];
    leftKnee[1] = leftHip[1] + shoulderLength;

    rightKnee[0] = rightHip[0];
    rightKnee[1] = rightHip[1] + shoulderLength;

    leftAnkle[0] = leftHip[0];
    leftAnkle[1] = leftHip[1] + 2.0f*shoulderLength;

    rightAnkle[0] = rightHip[0];
    rightAnkle[1] = rightHip[1] + 2.0f*shoulderLength;

    /*
    cout << "leftKnee[1]: " << leftKnee[1] << endl;
    cout << "rightKnee[1]: " << rightKnee[1] << endl;
    cout << "leftAnkle[1]: " << leftAnkle[1] << endl;
    cout << "rightAnkle[1]: " << rightAnkle[1] << endl;
    */


    // Convert to normalized space
    for (int i = 0; i < 2; i++) {

        leftShoulder[i] /= imageSize[i];
        rightShoulder[i] /= imageSize[i];
        leftHip[i] /= imageSize[i];
        rightHip[i] /= imageSize[i];
        leftElbow[i] /= imageSize[i];
        rightElbow[i] /= imageSize[i];
        leftWrist[i] /= imageSize[i];
        rightWrist[i] /= imageSize[i];

        leftKnee[i] /= imageSize[i];
        rightKnee[i] /= imageSize[i];
        leftAnkle[i] /= imageSize[i];
        rightAnkle[i] /= imageSize[i];

    }
 

    // ---- Update holistic data ----

    // Hips
    Data.pose[23][0] = leftHip[0];
    Data.pose[23][1] = leftHip[1];
    Data.pose[24][0] = rightHip[0];
    Data.pose[24][1] = rightHip[1];

    // Wrist
    Data.pose[15][0] = leftWrist[0];
    Data.pose[15][1] = leftWrist[1];
    Data.pose[16][0] = rightWrist[0];
    Data.pose[16][1] = rightWrist[1];

    // Knees
    Data.pose[25][0] = leftKnee[0];
    Data.pose[25][1] = leftKnee[1];
    Data.pose[26][0] = rightKnee[0];
    Data.pose[26][1] = rightKnee[1];

    // Ankles
    Data.pose[27][0] = leftAnkle[0];
    Data.pose[27][1] = leftAnkle[1];
    Data.pose[28][0] = rightAnkle[0];
    Data.pose[28][1] = rightAnkle[1];

}


void PoseDetector::MapPose2DToHolistic(FVector2f& Pose2D, Holistic& Data) {

    // Update x and y of pose 
    FVector2f pose = Pose2D;

    for (int idim = 0; idim < 2; idim++) {

        Data.pose[0][idim] = pose[0][idim];
        Data.pose[2][idim] = pose[1][idim];
        Data.pose[5][idim] = pose[2][idim];
        Data.pose[7][idim] = pose[3][idim];
        Data.pose[8][idim] = pose[4][idim];
        Data.pose[11][idim] = pose[5][idim];
        Data.pose[12][idim] = pose[6][idim];
        Data.pose[13][idim] = pose[7][idim];
        Data.pose[15][idim] = pose[9][idim];
        Data.pose[14][idim] = pose[8][idim];
        Data.pose[16][idim] = pose[10][idim];
        Data.pose[23][idim] = pose[11][idim];
        Data.pose[24][idim] = pose[12][idim];
        Data.pose[25][idim] = pose[13][idim];
        Data.pose[26][idim] = pose[14][idim];
        Data.pose[27][idim] = pose[15][idim];
        Data.pose[28][idim] = pose[16][idim];

    }

    // Set the depth of head as zero
    Data.pose[0][2] = 0.0f;
    Data.pose[2][2] = 0.0f;
    Data.pose[5][2] = 0.0f;
    Data.pose[7][2] = 0.0f;
    Data.pose[8][2] = 0.0f;

}

void PoseDetector::CalculatePoseDepthWithMHFormer(Holistic& Data) 
{

    int imageWidth = mImageWidth;
    int imageHeight = mImageHeight;

    vector<vector<float>> poseMp, pose2d, pose3d;

    pose2d = InitPose2d();

    // Create a vector pose from Mediapipe 
    poseMp = CreateVectorPoseMp(&Data.pose[0][0], Data.POSE_LANDMARK_NUM, Data.DIMENSIONS);

    // Convert to pixel space
    poseMp = pose_utils::ToPixelSpace(poseMp, imageWidth, imageHeight);

    // Prepare 2d pose
    ConvertPoseMpToPose2d(poseMp, pose2d);

    // Predict the depth
    pose3d = mMHFormer.Predict(pose2d);

    // Normalize pose
    pose3d = pose_utils::ToNormSpace(pose3d, imageWidth, imageHeight);

    // Left shoulder
    Data.pose[11][2] = pose3d[11][2];

    // Right shoulder
    Data.pose[12][2] = pose3d[14][2];

    // Left elbow
    Data.pose[13][2] = pose3d[12][2];

    // Right elbow
    Data.pose[14][2] = pose3d[15][2];

    // Left wrist
    Data.pose[15][2] = pose3d[13][2];

    // Right wrist
    Data.pose[16][2] = pose3d[16][2];

    // Left hip
    Data.pose[23][2] = pose3d[4][2];

    // Right hip
    Data.pose[24][2] = pose3d[1][2];

    // Left knee
    Data.pose[25][2] = pose3d[5][2];

    // Right knee
    Data.pose[26][2] = pose3d[2][2];

    // Left ankle
    Data.pose[27][2] = pose3d[6][2];

    // Right ankle
    Data.pose[28][2] = pose3d[3][2];

}

