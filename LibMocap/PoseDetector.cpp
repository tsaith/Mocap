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

    // Correct pose
    CorrectPose2D()

    MapPose2DToHolistic(mPose2D, mHolistic);

    // Estimate pose depth 
    EstimatePoseDepthWithMHFormer(mHolistic);
 
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

void CorrectPose2D()
{


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

void PoseDetector::EstimatePoseDepthWithMHFormer(Holistic& Data) 
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
    int numJoints = static_cast<int>(pose3d.size());
    for (int i = 0; i < numJoints; i++) {
        for (int j = 0; j < 3; j++) {
            pose3d[i][j] /= imageWidth;
        }
    }

    //int warmUpSteps = 5; // This could avoid Unreal crashes.
    //if (Counter > warmUpSteps) {

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

    //}

}
