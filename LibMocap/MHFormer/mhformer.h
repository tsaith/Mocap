#pragma once

#include <onnxruntime_cxx_api.h>
#include <dml_provider_factory.h>

#include "mhformer_utils.h" 

//using namespace cv;
using namespace std;
using namespace mhf;

class MHFormer
{
public:
    
    MHFormer();
    ~MHFormer();

    void Init(int FrameWidth, int FrameHeight); 
    void UseGpu(bool bFlag);
    bool LoadModel(string ModelPath);

    vector<vector<float>> Predict(vector<vector<float>>& Pose2d);
    void Infer(Ort::Value& InputTensor, Ort::Value& OutputTensor);

    void SetAngleAroundX(float AngleDeg);
    mhf::Vector2d GetPose3dPixelUnnorm();


private:

    int mFrameWidth = 640;
    int mFrameHeight = 480;

    // Use GPU device 
    bool mUseGpu = true;
    int mDeviceId = 0;

    //Ort::Env mEnv;
    Ort::Env mEnv = Ort::Env(ORT_LOGGING_LEVEL_ERROR, "MHFormerOrt");
    Ort::AllocatorWithDefaultOptions mOrtAllocator;
    Ort::MemoryInfo mMemoryInfo = Ort::MemoryInfo::CreateCpu(OrtDeviceAllocator, OrtMemTypeCPU);
    Ort::Session* mSessionPtr = nullptr;

    Ort::SessionOptions mSessionOptions;
    //Ort::SessionOptions mSessionOptions = Ort::SessionOptions();
    Ort::RunOptions mRunOptions;
    //Ort::RunOptions mRunOptions { nullptr };

    const int mBatchSize= 1;
    const int mNumFramesUsed = 5;
    const int mNumFramesModel = 81;
    const int mNumJoints = 17;
    const int mDim2d = 2;
    const int mDim3d = 3;


    mhf::Vector3d mTemporalData;
    mhf::Vector4d mInputVec;

    int mInputBufferSize = mBatchSize * mNumFramesModel * mNumJoints * mDim2d;
    vector<float> mInputBuffer;

    int mOutputBufferSize = mBatchSize * mNumFramesModel * mNumJoints * mDim3d;
    vector<float> mOutputBuffer;

    mhf::Vector2d mPose3dPixelUnnorm;
    
    // Rotational angle around x-axis
    float mAngleAroundX = 0.0;

};

