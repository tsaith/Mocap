#pragma once

#include <onnxruntime_cxx_api.h>
#include <dml_provider_factory.h>

#include <vector>
#include <cmath>
#include <stdio.h>
#include <iostream>

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

namespace mhformer_utils {

	typedef vector<vector<float>> Vector2d;
	typedef vector<Vector2d> Vector3d;
	typedef vector<Vector3d> Vector4d;


	Vector2d GetMockKeypoints();
	Vector2d InitVec2d(int Rows, int Cols);
	Vector3d InitVec3d(int Nt, int Rows, int Cols);
	Vector4d InitVec4d(int BatchSize, int Nt, int Rows, int Cols);

	Vector2d RescaleAndShiftPose2d(Vector2d& Keypoints, int FrameWidth, int FrameHeight);

	Vector2d NormalizeKeypoints2d(Vector2d& Keypoints, int FrameWidth, int FrameHeight);
	Vector2d UnnormalizeKeypoints2d(Vector2d& Keypoints, int FrameWidth, int FrameHeight);
	Vector2d NormalizeKeypoints3d(Vector2d& Keypoints, int FrameWidth, int FrameHeight);
	Vector2d UnnormalizeKeypoints3d(Vector2d& Keypoints, int FrameWidth, int FrameHeight);

	vector<float> InterpVec1d(vector<float>& InputVec, int OutputSize);

	Vector4d ConvertKeypointsToInputVec(Vector2d& Keypoints, int BatchSize, int NumFrames);
	Vector4d CreateInputVec(Vector3d& TemporalData, int BatchSize, int NumFrames);
	Ort::Value CreateTensor(Vector4d& Vec, vector<float>& Buffer, Ort::MemoryInfo& Info);
	Vector2d ConvertOutputTensorToPose3d(Ort::Value& Outputs);

	void GetPoseMinMax(float& Min, float& Max, Vector2d& PoseIn, int Direct);
	Vector2d RescaleAndShiftPose3d(Vector2d& Pose3d, Vector2d& Pose2d);
	Vector2d RotatePose3dAroundX(Vector2d& Pose3d, float AngleDeg);
	vector<float> RotateAroundX(vector<float>& Vec, float AngleDeg);

	Vector2d ToPixelSpace(Vector2d& PoseIn, int Width, int Height);

	void PrintPoint(string Msg, vector<float>& Point, int Dims);

} // Namespace
