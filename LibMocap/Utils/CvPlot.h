#pragma once

#include <stdio.h>
#include <iostream>
#include <string>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;


vector<vector<int>> GetPoseConnect();
vector<vector<int>> GetMpPoseConnect();
vector<vector<float>> ShiftPoseXY(vector<vector<float>>& PoseIn, int ShiftX, int ShiftY);

vector<vector<float>> GetPoseCrossSection(vector<vector<float>> &Pose, string ViewType);

void PlotPose2d(cv::Mat &Image, vector<vector<float>> &Pose);
void PlotPose2dWithShift(cv::Mat &Image, vector<vector<float>> &Pose, int ShiftX, int ShiftY);
void PlotMpPose2d(cv::Mat &Image, vector<vector<float>> &Pose);

cv::Mat CombineImages2x2(cv::Mat& Img1, cv::Mat& Img2, cv::Mat& Img3, cv::Mat& Img4, cv::Size SizeOut);
