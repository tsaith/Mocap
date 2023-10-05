#pragma once

#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

namespace pose_utils {

	// Math
	template<typename T>
	void Interp1d(T A, T B, T Weight, T& Target);

	template<typename T>
	void Interp2d(T* A, T* B, T Weight, T* Target);

	template<typename T>
	void Interp3d(T* A, T* B, T Weight, T* Target);

	template<typename T>
	void Mean2d(T* A, T* B, T* Target);

	template<typename T>
	void Mean3d(T* A, T* B, T* Target);

	template<typename T>
	void ArrToVec(T* A, vector<T>& V, int Dims);

	template<typename T>
	void VecToArr(vector<T>& V, T* A, int Dims);

	// Pose related functions
	vector<vector<float>> CreateVectorPoseMp(float* Ptr, int NumJoints, int Dims);

	vector<vector<float>> ToPixelSpace(vector<vector<float>>& PoseIn, int Width, int Height);
	vector<vector<float>> ToNormSpace(vector<vector<float>>& PoseIn, int Width, int Height);
	vector<vector<float>> InitPose2d();
	void ConvertPoseMpToPose2d(vector<vector<float>>& PoseMp, vector<vector<float>>& Pose2d);

	void PrintPoint(string Msg, vector<float>& Point, int Dims);

}