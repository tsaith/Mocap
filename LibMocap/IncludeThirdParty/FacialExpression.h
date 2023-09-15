#pragma once

#include <vector>

#include "nvAR.h"
#include "nvCVOpenCV.h"  

#define DEFAULT_CODEC         "avc1"
#define DEFAULT_FACE_MODEL    "face_model2.nvf"
#define DEFAULT_RENDER_MODEL  "face_model2.nvf"
#define NUM_CAMERA_INTRINSIC_PARAMS 3

using namespace std;

struct Pose {

    NvAR_Quaternion rotation;
    NvAR_Vector3f translation;
    float* data() { return &rotation.x; }
    const float* data() const { return &rotation.x; }
};


class FacialExpression {
public:

    FacialExpression();
    ~FacialExpression();

    void Init(int FrameWidth, int FrameHeight);
    void Finalize();
    void Detect(cv::Mat& Image);
    string GetEnvVar(const string& VarName);
    bool IsFaceDetected();
    unsigned GetExprCount();
    vector<float> GetExpressionCoeffs();
    const int GetNumBlendshapes();
    vector<float> GetBlendshapes();
    vector<float> GetHeadQuat();
    vector<float> GetHeadTranslation();

    void NormalizeExpressionsWeights();
    void ConvertNvToARKitBlendshapes(vector<float>& Expr, vector<float>& Blendshapes);

private:

    NvAR_FeatureHandle mFeatureHan{};
    CUstream mStream = 0;
    cv::Mat mOcvSrcImg, mOcvDstImg;
    NvCVImage mSrcImgCpu, mSrcImgGpu;
    unsigned mFiltering = 55;
    //unsigned mFiltering = NVAR_TEMPORAL_FILTER_FACIAL_EXPRESSIONS;
    unsigned mPoseMode = 0;
    bool mEnableCheekPuff = false;
    vector<NvAR_Rect> mOutputBboxData;
    NvAR_BBoxes mOutputBboxes;

    vector<float>
        mExpressions, mExpressionZeroPoint, mExpressionScale, mExpressionExponent,
        mEigenvalues,
        mLandmarkConfidence;

    vector<NvAR_Point2f> mLandmarks;
    unsigned mExprCount = 53;
    float mCameraIntrinsicParams[NUM_CAMERA_INTRINSIC_PARAMS];

    const int mNumBlendshapes = 52;
    vector<float> mBlendshapes;

    Pose mPose;
    bool mIsFaceDetected = false;

    vector<float> mHeadQuat = {0.0, 0.0, 0.0, 1.0}; // x, y, z, w
    vector<float> mHeadTranslation = {0.0, 0.0, 0.0}; // x, y, z

};

