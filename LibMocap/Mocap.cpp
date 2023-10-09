#include "pch.h"

#include "Mocap.h"
#include "Mediapipe/LibMediapipe.h"
//#include "Mediapipe/LibMpHand.h"  
 

Mocap::Mocap() {   

    mBlendshapes.assign(mNumBlendshapes, 0); 

    FTransform boneTransform;
    mSkelTransforms.assign(mNumBones, boneTransform);

}

Mocap::~Mocap() {

    mFacialExpression.Finalize();

    //MpPoseFinalize(); 
    MpHandFinalize(); 

}

void Mocap::Init(int ImageWidth, int ImageHeight) {

    mImageWidth = ImageWidth; 
    mImageHeight = ImageHeight;

    string modelPath = "";

    // Facial expression
    mFacialExpression.Init(ImageWidth, ImageHeight);

    // Mediapipe  
    //MpPoseInit(); 
    MpHandInit(); 

    // Pose detector
    mPoseDetector.Init(ImageWidth, ImageHeight);
    mPoseDetector.UseGpu(mUseGpu, mGpuDeviceId);
    mPoseDetector.LoadModel("TrainedModels");

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
    mPoseDetector.SetHandInfo(mHasLeftHand, mHasRightHand);
    mPoseDetector.Detect(Image);
    mPoseDetector.UpdateHolisticPose(mHolistic);

    // Sychronization
    faceDetectWorker.join();
    handDetectWorker.join(); 

    // Correct pose and hands
    CorrectHolistic(mHolistic); 

    // Renormalize data
    mHolisticReNorm = ReNormalizeHolistic(mHolistic); 

    // Skeleton converter
    mSkelConverter.Process(mHolisticReNorm);
 
    // Calculate skeleton transform
    CaculateSkelTransforms();

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
    MpHandGetLeftHand(mHasLeftHand, pLeftHand);
    
    Data.HasLeftHand = mHasLeftHand;
    CopyArray2D(pLeftHand, &(Data.LeftHand[0][0]),
        Data.HAND_LANDMARK_NUM, 
        Data.DIMENSIONS);

    // Right hand 
    float* pRightHand;
    MpHandGetRightHand(mHasRightHand, pRightHand);

    Data.HasRightHand = mHasRightHand;
    CopyArray2D(pRightHand, &(Data.RightHand[0][0]),
        Data.HAND_LANDMARK_NUM,
        Data.DIMENSIONS);

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

void Mocap::CorrectHolistic(Holistic& Data) {

    int iWrist;
    float zPoseWrist;
    float zHandWrist;
    float shift;

    // Left hand
    iWrist = 15;
    zPoseWrist = Data.pose[iWrist][2];
    zHandWrist = Data.LeftHand[0][2];
    shift = zPoseWrist - zHandWrist;

    for (int i = 0; i < Data.HAND_LANDMARK_NUM; i++) {
        Data.LeftHand[i][2] += shift;
    }

    // Right hand
    iWrist = 16;
    zPoseWrist = Data.pose[iWrist][2];
    zHandWrist = Data.RightHand[0][2];
    shift = zPoseWrist - zHandWrist;

    for (int i = 0; i < Data.HAND_LANDMARK_NUM; i++) {
        Data.RightHand[i][2] += shift;
    }

}

void Mocap::CaculateSkelTransforms() 
{

    // Calculate skeleton transform
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
