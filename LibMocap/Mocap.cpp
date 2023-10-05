#include "pch.h"

#include "Mocap.h"
#include "Mediapipe/LibMpHand.h"
 

Mocap::Mocap() {   

    mBlendshapes.assign(mNumBlendshapes, 0); 

    FTransform boneTransform;
    mSkelTransforms.assign(mNumBones, boneTransform);



}

Mocap::~Mocap() {

    mFacialExpression.Finalize();

}

void Mocap::Init(int ImageWidth, int ImageHeight) {

    mImageWidth = ImageWidth; 
    mImageHeight = ImageHeight;

    string modelPath = "";

    // Facial expression
    mFacialExpression.Init(ImageWidth, ImageHeight);

    // Mediapipe  
    MpHandInit(); 

    // Pose detector
    mPoseDetector.Init(ImageWidth, ImageHeight);
    mPoseDetector.UseGpu(mUseGpu, mGpuDeviceId);
    mPoseDetector.LoadModel("TrainedModels");

    /*
    // HRNetPose
    mHRNetPose.Init(ImageWidth, ImageHeight);

    modelPath = "C:/Users/andrew/projects/Mocap/x64/Release/TrainedModels/hrnet_coco_w32_256x192.onnx";
    //modelPath = "TrainedModels/hrnet_coco_w32_256x192.onnx";
    mHRNetPose.UseGpu(true, mGpuDeviceId);
    mHRNetPose.LoadModel(modelPath);


    mMHFormer.Init(ImageWidth, ImageHeight);
    mMHFormer.UseGpu(true);

    //modelPath = "C:\\Users\\andrew\\projects\\Mocap\\x64\\Release\\TrainedModels\\mhformer.onnx";
    modelPath = "C:/Users/andrew/projects/Mocap/x64/Release/TrainedModels/mhformer.onnx";
    mMHFormer.LoadModel(modelPath);

    // Set angle used to rotate pose around x-axis
    mMHFormer.SetAngleAroundX(mMHFAngleAroundX);
    */

    // Skeleton converter
    mSkelConverter.Init(ImageWidth, ImageHeight);

    // Diagnostics
    mDiag.Init(ImageWidth, ImageHeight);

}

void Mocap::Detect(Mat& Image)
{
    // Update counter
    mCounter++;
    if (mCounter > mCounterMax) mCounter = 0;


    mImage = Image.clone();

    // Face Detection
    thread faceDetectWorker(&Mocap::FaceDetect, this, ref(Image));
    //FaceDetect(Image);

    // Hand detection (Use thread can speed up significantly)
    thread handDetectWorker(MpHandDetect, ref(Image));
    //MpHandDetect(Image);
    UpdateHolisticHands(mHolistic);

    // Pose detection
    mPoseDetector.Detect(Image);
    mPoseDetector.UpdateHolisticPose(mHolistic);

    // Refine depth with MHFormer  
    //RefinePoseDepthWithMHFormer(mHolistic, mCounter);

    // Sychronization
    faceDetectWorker.join();
    handDetectWorker.join(); 
    //poseDetectWorker.join(); 

    // Renormalize data
    mHolisticReNorm = ReNormalizeHolistic(mHolistic); 

    // Skeleton converter
    mSkelConverter.Process(mHolisticReNorm);
    
    FTransform transform;
    float* pQuat;
    float* pBone;
    for (int i = 0; i < mNumBones; i++) {

        pQuat = mSkelConverter.GetQuat(i);
        pBone = mSkelConverter.GetBone(i);

        transform.Rotation.X = pQuat[1];
        transform.Rotation.Y = pQuat[2];
        transform.Rotation.Z = pQuat[3];
        transform.Rotation.W = pQuat[0];

        transform.Translation.X = pBone[0];
        transform.Translation.Y = pBone[1];
        transform.Translation.Z = pBone[2];

        mSkelTransforms[i] = transform;
 
    }


}

void Mocap::Diagnose()
{

    // Input image
    mDiag.SetInputImage(mImage);

    // Pose landmarks
    int NumPoseLandmarks = mHolistic.GetPoseLandmarkNum();
    //int NumPoseLandmarks = mHolistic.GetPoseLandmarkNum();
    FVector2f poseLandmarks = InitVector2f(NumPoseLandmarks, 4);

    float* pPose = &mHolistic.pose[0][0];
    ArrayToVector(pPose, poseLandmarks, NumPoseLandmarks, 4);
    mDiag.SetPoseLandmarks(poseLandmarks);

    // Hand landmarks
    int NumHandLandmarks = mHolistic.GetHandLandmarkNum();
    FVector2f leftHandLandmarks = InitVector2f(NumHandLandmarks, 4);
    FVector2f rightHandLandmarks = InitVector2f(NumHandLandmarks, 4);

    float* pLeftHand = &mHolistic.LeftHand[0][0];
    float* pRightHand = &mHolistic.RightHand[0][0];
    ArrayToVector(pLeftHand, leftHandLandmarks, NumHandLandmarks, 4);
    ArrayToVector(pRightHand, rightHandLandmarks, NumHandLandmarks, 4);
    mDiag.SetHandLandmarks(leftHandLandmarks, rightHandLandmarks);

    // Skeleton
    FVector2f skelQuats = InitVector2f(mNumBones, 4);
    FVector2f skelBones = InitVector2f(mNumBones, 3);

    FTransform transform;
    for (int i = 0; i < mNumBones; i++) {

        transform = GetSkelTransform(i);

        skelQuats[i][0] = transform.Rotation.X;
        skelQuats[i][1] = transform.Rotation.Y;
        skelQuats[i][2] = transform.Rotation.Z;
        skelQuats[i][3] = transform.Rotation.W;

        skelBones[i][0] = transform.Translation.X;
        skelBones[i][1] = transform.Translation.Y;
        skelBones[i][2] = transform.Translation.Z;

    }

    mDiag.SetSkeleton(skelQuats, skelBones);

    // Process
    mDiag.Process();

}

bool Mocap::IsFaceDetected() {
    return mFacialExpression.IsFaceDetected();
}

vector<float> Mocap::GetBlendshapes() {
    return mFacialExpression.GetBlendshapes();
}

FTransform Mocap::GetHeadTransform() {
    return mHeadTransform;
}

vector<FTransform> Mocap::GetSkelTransforms()
{
    return mSkelTransforms;
}

FTransform Mocap::GetSkelTransform(int Index)
{
    return mSkelTransforms[Index];
}

// Private methods
void Mocap::FaceDetect(Mat& Image)
{

    mFacialExpression.Detect(Image);
 
    // Head transform
    vector<float> headQuatVec = mFacialExpression.GetHeadQuat();
    vector<float> headTranslationVec = mFacialExpression.GetHeadTranslation();
    FQuat headRotation;
    FVector headTranslation;

    headRotation.X = headQuatVec[0];
    headRotation.Y = headQuatVec[1];
    headRotation.Z = headQuatVec[2];
    headRotation.W = headQuatVec[3];

    headTranslation.X = headTranslationVec[0];
    headTranslation.Y = headTranslationVec[1];
    headTranslation.Z = headTranslationVec[2];
    mHeadTransform = MakeTransform(headRotation, headTranslation);

}


FTransform Mocap::MakeTransform(FQuat Rotation, FVector Translation)
{

    FTransform transform;

    transform.Translation = Translation;
    transform.Rotation = Rotation;

    return transform;
}

void Mocap::CopyArray2D(float* Src, float* Dest, int Rows, int Cols) {

    int num = Rows * Cols;
    memcpy(Dest, Src, sizeof(float)*num);

}

void Mocap::UpdateHolisticHands(Holistic& Data) {

    // Left hand 
    float* pLeftHand;
    MpHandGetLeftHand(Data.HasLeftHand, pLeftHand);

    CopyArray2D(pLeftHand, &(Data.LeftHand[0][0]),
        Data.HAND_LANDMARK_NUM, 
        Data.DIMENSIONS);

    // Right hand 
    float* pRightHand;
    MpHandGetRightHand(Data.HasRightHand, pRightHand);


    CopyArray2D(pRightHand, &(Data.RightHand[0][0]),
        Data.HAND_LANDMARK_NUM,
        Data.DIMENSIONS);

}


void Mocap::UpdateHolisticPose(Holistic& Data, FVector2f Pose) {


    // Update x and y of pose 
    FVector2f pose = Pose;

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

Holistic Mocap::ReNormalizeHolistic(Holistic& Data) 
{
    /*
       y' = y * (ImageHeight/ImageWidth)
       where y' is the customeized normalized value and
       y is the Mediapipe normalized value
    */

    float NormRatio = 1.0f*mImageHeight/mImageWidth;
    Holistic dataOut = Data;

    // Pose
    for (int i=0; i < dataOut.GetPoseLandmarkNum(); i++) {
        dataOut.pose[i][1] *= NormRatio;
    }

    // Hands
    for (int i=0; i < dataOut.GetHandLandmarkNum(); i++) {
        dataOut.LeftHand[i][1] *= NormRatio;
        dataOut.RightHand[i][1] *= NormRatio;
    }

    return dataOut;

}

/*
void Mocap::RefinePoseDepthWithMHFormer(Holistic& Data, int Counter) 
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

    int warmUpSteps = 5; // This could avoid Unreal crashes.
    if (Counter > warmUpSteps) {

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

}
*/

