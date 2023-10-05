#include "pch.h"

#include "mhformer.h"


MHFormer::MHFormer() {
}

MHFormer::~MHFormer() {
}

void MHFormer::Init(int FrameWidth, int FrameHeight) {

	mFrameWidth = FrameWidth;
	mFrameHeight = FrameHeight;

    // Initialize the temporal data which is supposed to predict
    // reasonable pose depth for the first frame but can't work!
	Vector2d pose2dPixel = GetMockKeypoints();
    Vector2d pose2d = NormalizeKeypoints2d(pose2dPixel, FrameWidth, FrameHeight);
    for (int i = 0; i < mNumFramesUsed; i++) {
        mTemporalData.push_back(pose2d);
    }

    // Input and output buffer for model inference
    mInputBuffer.assign(mInputBufferSize, 0.0f);
    mOutputBuffer.assign(mOutputBufferSize, 0.0f);

    mSessionOptions.SetIntraOpNumThreads(1);
    mSessionOptions.SetGraphOptimizationLevel(ORT_ENABLE_BASIC);


}

void MHFormer::UseGpu(bool bFlag) {

    mUseGpu = bFlag;  

}

bool MHFormer::LoadModel(string ModelPath) {

    bool bStatus = true;

    std::wstring modelPathWide(ModelPath.begin(), ModelPath.end());

    // Use CUDA GPU
    if (mUseGpu) { 

        //OrtSessionOptionsAppendExecutionProvider_DML(mSessionOptions, mDeviceId);

        OrtApi const& ortApi = Ort::GetApi(); // Uses ORT_API_VERSION
        const OrtDmlApi* ortDmlApi;
        ortApi.GetExecutionProviderApi("DML", ORT_API_VERSION, reinterpret_cast<const void**>(&ortDmlApi));
        ortDmlApi->SessionOptionsAppendExecutionProvider_DML(mSessionOptions, mDeviceId);

    }

    // Create session
    try {
        mSessionPtr = new Ort::Session(mEnv, modelPathWide.c_str(), mSessionOptions);
    }
    catch (std::exception& e) {
        cout << "Error: failed to create Ort session." << endl;
        cout << "Error: " << e.what() << endl;
        cout << "Please check the model path: " << ModelPath << endl;
        
    }

    return bStatus;

}


vector<vector<float>> MHFormer::Predict(vector<vector<float>>& Pose2d) {

    Vector2d pose2dPixel = Pose2d; 
    pose2dPixel = RescaleAndShiftPose2d(pose2dPixel, mFrameWidth, mFrameHeight);

    // Normalize keypoints 2d
    Vector2d pose2d = NormalizeKeypoints2d(pose2dPixel, mFrameWidth, mFrameHeight);

    // Update temporal data
    mTemporalData.push_back(pose2d);

    while (mTemporalData.size() < mNumFramesUsed) {
        mTemporalData.push_back(pose2d);
    }

    if (mTemporalData.size() > mNumFramesUsed) {
        mTemporalData.erase(mTemporalData.begin());
    }

    Vector4d inputVec = CreateInputVec(mTemporalData, mBatchSize, mNumFramesModel);
	Vector4d outputVec = InitVec4d(1, 81, 17, 3);

    // Inference
    Ort::Value inputTensor = CreateTensor(inputVec, mInputBuffer, mMemoryInfo);
    Ort::Value outputTensor = CreateTensor(outputVec, mOutputBuffer, mMemoryInfo);

    Infer(inputTensor, outputTensor);

    Vector2d pose3d = ConvertOutputTensorToPose3d(outputTensor);

    // Rotate pose around x-axis
    pose3d = RotatePose3dAroundX(pose3d, mAngleAroundX);

    // Unnormalize keypoints 3d
    Vector2d pose3dPixel = UnnormalizeKeypoints3d(pose3d, mFrameWidth, mFrameHeight);

    // Save unnormalized pose 3d
    mPose3dPixelUnnorm = pose3dPixel;

    // Rescale and rotate pose
    pose3dPixel = RescaleAndShiftPose3d(pose3dPixel, Pose2d);

    return pose3dPixel;

}

void MHFormer::Infer(Ort::Value& InputTensor, Ort::Value& OutputTensor) {

    vector<const char*> inputNames;
    vector<const char*> outputNames;
    vector<vector<int64_t>> inputNodeDims;
    vector<vector<int64_t>> outputNodeDims;

    size_t numInputNodes = mSessionPtr->GetInputCount();
    size_t numOutputNodes = mSessionPtr->GetOutputCount();

    for (int i = 0; i < numInputNodes; i++)
    {
        Ort::AllocatedStringPtr inputName = mSessionPtr->GetInputNameAllocated(i, mOrtAllocator);
        inputNames.push_back(inputName.get());
        Ort::TypeInfo inputTypeInfo = mSessionPtr->GetInputTypeInfo(i);
        auto inputTensorInfo = inputTypeInfo.GetTensorTypeAndShapeInfo();
        auto inputDims = inputTensorInfo.GetShape();
        inputNodeDims.push_back(inputDims);

        inputName.release();
    } 

    for (int i = 0; i < numOutputNodes; i++)
    {
        Ort::AllocatedStringPtr outputName = mSessionPtr->GetOutputNameAllocated(i, mOrtAllocator);
        outputNames.push_back(outputName.get());
        Ort::TypeInfo outputTypeInfo = mSessionPtr->GetOutputTypeInfo(i);
        auto outputTensorInfo = outputTypeInfo.GetTensorTypeAndShapeInfo();
        auto outputDims = outputTensorInfo.GetShape();
        outputNodeDims.push_back(outputDims);

        outputName.release();
    }

    mSessionPtr->Run(mRunOptions, inputNames.data(), &InputTensor, 1,
        outputNames.data(), &OutputTensor, 1);

}

void MHFormer::SetAngleAroundX(float AngleDeg) {
    mAngleAroundX = AngleDeg;
}


Vector2d MHFormer::GetPose3dPixelUnnorm() {
    return mPose3dPixelUnnorm;
}