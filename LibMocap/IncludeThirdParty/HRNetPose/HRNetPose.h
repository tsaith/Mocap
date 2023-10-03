#pragma once


#include "opencv2/opencv.hpp"

#include <onnxruntime_cxx_api.h>
#include <dml_provider_factory.h>

#include "Core/Math/OneEuroFilter.hpp" 
#include "Utils/Skel/BoneStabilizer.hpp"
#include "Utils/Timer.hpp"


namespace hrnet_pose {

    using namespace std;
    using namespace cv;

    class HRNetPose {
    public:

        HRNetPose();
        ~HRNetPose();

        void Init(int ImageWidth, int ImageHeight);
        void Finalize();
        void UseGpu(bool bFlag, int DeviceId);
        bool LoadModel(string ModelPath);
        void Detect(Mat& Image);
        void Diagnose();

        vector<vector<float>> GetPoseNorm();

    private:

        Ort::Value CreateImageTensor(Mat& Image, vector<float>& Buffer, Ort::MemoryInfo& Info);
        vector<Ort::Value> Infer(Ort::Value& InputTensor);
        void ConvertTensorToMat(Ort::Value& Input, Mat& Output);
        void RescalePose(vector<vector<float>>& Pose, int WidthIn, int HeightIn, int WidthOut, int HeightOut);

        int mImageWidth = 640;
        int mImageHeight = 480;

        Mat mImage;

        // Use GPU device 
        bool mUseGpu = true;
        int mDeviceId = 0;

        Ort::Env mEnv = Ort::Env(ORT_LOGGING_LEVEL_ERROR, "HRNetPose");
        Ort::AllocatorWithDefaultOptions mOrtAllocator;
        Ort::MemoryInfo mMemoryInfo = Ort::MemoryInfo::CreateCpu(OrtDeviceAllocator, OrtMemTypeCPU);
        Ort::Session* mSessionPtr = nullptr;

        Ort::SessionOptions mSessionOptions;
        Ort::RunOptions mRunOptions;

        int mInferWidth = 192;
        int mInferHeight = 256;

        int mInputBufferSize = 3 * mInferWidth * mInferHeight;
        vector<float> mInputBuffer;

        static const int mNumKeypoints = 17;
        std::vector<int64_t> mOutputShape = { 1, mNumKeypoints, 64, 48 };
        //const std::array<int64_t, 4> mOutputShape = { 1, 17, 64, 48 };
        int mOutputBufferSize = mNumKeypoints * 64 * 48;
        vector<float> mOutputBuffer;

        vector<float> mPreds;
        // Pose (x, y, possibility)
        vector<vector<float>> mPose;
        vector<vector<float>> mPoseNorm;

        // Parameters of One Euro filter
        float mOneEuroFrequency = 18.0;
        float mOneEuroMincutoff = 1.0;
        float mOneEuroBeta = 10.0;
        float mOneEuroDcutoff = 1.0;

        // One Euro filter
        one_euro::OneEuroFilter mPoseOneEuro[mNumKeypoints][2];

        Timer mFilterTimer;

        // Bone stabilizer
        BoneStabilizer mPoseStabilizer[mNumKeypoints];

    };

} // Namespace
