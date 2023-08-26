#pragma once

#include "opencv2/opencv.hpp"

#ifdef LIBMOCAP_EXPORTS
    #define LIBMOCAP_API __declspec(dllexport)
#else
    #define LIBMOCAP_API __declspec(dllimport)
#endif


extern "C" LIBMOCAP_API void MocapInit(int FrameWidth, int FrameHeight);
extern "C" LIBMOCAP_API void MocapFinalize();
extern "C" LIBMOCAP_API void MocapDetect(cv::Mat& Image);
extern "C" LIBMOCAP_API bool MocapIsFaceDetected();
extern "C" LIBMOCAP_API float* MocapGetBlendshapes();
extern "C" LIBMOCAP_API float* MocapGetHeadTransform();
extern "C" LIBMOCAP_API float* MocapGetSkelTransform(int Index);

