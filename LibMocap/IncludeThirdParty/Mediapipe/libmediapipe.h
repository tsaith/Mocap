#pragma once

#ifdef LIBMEDIAPIPE_EXPORTS

    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
        #define DLL_API __declspec(dllexport)
    #else
        #define DLL_API
    #endif

#else

    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
        #define DLL_API __declspec(dllimport)
    #else
        #define DLL_API
    #endif

#endif

#include <opencv2/opencv.hpp>

extern "C" {

    DLL_API void MediapipeInit();
    DLL_API void MediapipeFinalize();
    DLL_API void MediapipeDetect(cv::Mat Image);

    DLL_API void MediapipeGetDefaultParams(
        int& NumFacemeshLandmarks, int& NumPoseLandmarks,
        int& NumHandLandmarks, int& Dimensions);

    DLL_API void MediapipeGetFacemesh(bool& Has, float*& Pointer);
    DLL_API void MediapipeGetPose(bool& Has, float*& Pointer);
    DLL_API void MediapipeGetLeftHand(bool& Has, float*& Pointer);
    DLL_API void MediapipeGetRightHand(bool& Has, float*& Pointer);


}
