#pragma once


#ifdef LIBMPHAND_EXPORTS

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

    DLL_API void MpPoseInit();
    DLL_API void MpPoseFinalize();
    DLL_API void MpPoseDetect(cv::Mat Image);
    DLL_API void MpPoseGetPose(bool& Has, float*& Pointer);

    DLL_API void MpHandInit(); 
    DLL_API void MpHandFinalize();
    DLL_API void MpHandDetect(cv::Mat Image);
    DLL_API void MpHandGetLeftHand(bool& Has, float*& Pointer);
    DLL_API void MpHandGetRightHand(bool& Has, float*& Pointer);

}
