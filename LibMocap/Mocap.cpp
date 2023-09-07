#include "pch.h"

#include "Mocap.h"
#include "LibFacialExpression.h" 
#include "libmediapipe.h"
 

Mocap::Mocap() { 

    mBlendshapes.assign(mNumBlendshapes, 0);

    FTransform boneTransform;
    mSkelTransforms.assign(mNumBones, boneTransform);



}

Mocap::~Mocap() {

    FacialExpressionFinalize();
    MediapipeFinalize();

}

void Mocap::Init(int ImageWidth, int ImageHeight) {

    mImageWidth = ImageWidth;
    mImageHeight = ImageHeight;

    // Facial expression
    FacialExpressionInit(ImageWidth, ImageHeight);

    // Mediapipe 
    MediapipeInit(); 

    String modelPath = "C:\\Users\\andrew\\projects\\Mocap\\x64\\Release\\TrainedModels\\mhformer.onnx";
    //String modelPath = "C:\\Users\\andrew\\projects\\Mocap\\x64\\Release\\TrainedModels\\mhformer.onnx";
    //String modelPath = "TrainedModels/mhformer.onnx";

    mMHFormer.Init(ImageWidth, ImageHeight);
    //mMHFormer.UseGpu(false);
    mMHFormer.UseGpu(true);
    mMHFormer.LoadModel(modelPath);

    // Set angle used to rotate pose around x-axis
    float angleX = -10.0;
    mMHFormer.SetAngleAroundX(angleX);

    // Skeleton converter
    mSkelConverter.Init(ImageWidth, ImageHeight);

    // Diagnostics
    mDiag.Init(ImageWidth, ImageHeight);

}


void Mocap::Detect(Mat& Image)
{

    mImage = Image.clone();

    float* p;

    // Facial expression
    FacialExpressionDetect(Image);

    mIsFaceDetected = FacialExpressionIsFaceDetected();

    p = FacialExpressionGetBlendshapes();
    for (int i = 0; i < mNumBlendshapes; i++) {
        mBlendshapes[i] = p[i];
    }

    // Head transform
    FQuat headRotation;
    FVector headTranslation;

    p = FacialExpressionGetHeadQuat();
    headRotation.X = p[0];
    headRotation.Y = p[1];
    headRotation.Z = p[2];
    headRotation.W = p[3];

    p = FacialExpressionGetHeadTranslation();
    headTranslation.X = p[0];
    headTranslation.Y = p[1];
    headTranslation.Z = p[2];
    mHeadTransform = MakeTransform(headRotation, headTranslation);

    // Mediapipe
    MediapipeDetect(Image);
    UpdateHolistic(mHolistic);

    // Refine depth with MHFormer  
    //RefinePoseDepthWithMHFormer(mHolistic);

    // Skeleton converter
    mSkelConverter.Process(mHolistic);
    
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

    FVector2f skelQuats = InitVector2f(mNumBones, 4);
    FVector2f skelBones = InitVector2f(mNumBones, 3);

    FTransform transform;

    int i;
    for (i = 0; i < mNumBones; i++) {

        transform = GetSkelTransform(i);

        skelQuats[i][0] = transform.Rotation.X;
        skelQuats[i][1] = transform.Rotation.Y;
        skelQuats[i][2] = transform.Rotation.Z;
        skelQuats[i][3] = transform.Rotation.W;

        skelBones[i][0] = transform.Translation.X;
        skelBones[i][1] = transform.Translation.Y;
        skelBones[i][2] = transform.Translation.Z;

    }

    mDiag.SetInputImage(mImage);
    mDiag.SetSkeleton(skelQuats, skelBones);
    mDiag.Process();

    Mat diagImage = mDiag.GetDiagImage();

    imshow("Diag", diagImage);
}

bool Mocap::IsFaceDetected() {
    return mIsFaceDetected;
}

vector<float> Mocap::GetBlendshapes() {
    return mBlendshapes;
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
FTransform Mocap::MakeTransform(FQuat Rotation, FVector Translation) {

    FTransform transform;

    transform.Translation = Translation;
    transform.Rotation = Rotation;

    return transform;
}

void Mocap::CopyArray2D(float* Src, float* Dest, int Rows, int Cols) {

    int num = Rows * Cols;
    memcpy(Dest, Src, sizeof(float)*num);

}

void Mocap::UpdateHolistic(Holistic& Data) {

    float* pFacemesh;
    MediapipeGetFacemesh(Data.HasFacemesh, pFacemesh);

    CopyArray2D(pFacemesh, &(Data.facemesh[0][0]),
        Data.FACEMESH_LANDMARK_NUM,
        Data.DIMENSIONS);

    float* pPose;
    MediapipeGetPose(Data.HasPose, pPose);

    CopyArray2D(pPose, &(Data.pose[0][0]),
        Data.POSE_LANDMARK_NUM,
        Data.DIMENSIONS);

    float* pLeftHand;
    MediapipeGetLeftHand(Data.HasLeftHand, pLeftHand);

    CopyArray2D(pLeftHand, &(Data.LeftHand[0][0]),
        Data.HAND_LANDMARK_NUM,
        Data.DIMENSIONS);

    float* pRightHand;
    MediapipeGetRightHand(Data.HasRightHand, pRightHand);

    CopyArray2D(pRightHand, &(Data.RightHand[0][0]),
        Data.HAND_LANDMARK_NUM,
        Data.DIMENSIONS);

}

void Mocap::RefinePoseDepthWithMHFormer(Holistic& Data) {

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
        pose3d[i][0] /= imageWidth;
        pose3d[i][1] /= imageHeight;
        pose3d[i][2] /= imageWidth;
    }

    /* Update depth of Holistic data */
 
    /*
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
    */

}

