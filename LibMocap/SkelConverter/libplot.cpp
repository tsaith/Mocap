#include "pch.h"

#include "libplot.h"

vector<vector<int>> GetPoseConnect() {

    vector<vector<int>> connect {
        {0, 1}, {1, 2}, {2, 3}, {0, 4}, {4, 5},
        {5, 6}, {0, 7}, {7, 8}, {8, 9}, {9, 10},
        {8, 11}, {11, 12}, {12, 13}, {8, 14}, {14, 15}, {15, 16}
    };

    return connect;

}

vector<vector<int>> GetMpPoseConnect() {

    vector<vector<int>> connect {
        {0, 1}, {1, 2}, {2, 3}, {3, 7},
        {0, 4}, {4, 5}, {5, 6}, {6, 8},
        {9, 10},
        {11, 23}, {23, 24}, {24, 12}, {12, 11},
        {11, 13}, {13, 15}, {15, 21}, {15, 19}, {15, 17},
        {12, 14}, {14, 16}, {16, 22}, {16, 20}, {16, 18},
        {23, 25}, {25, 27}, {27, 29}, {27, 31},
        {24, 26}, {26, 28}, {28, 30}, {28, 32}
    };

    return connect;

}

vector<vector<float>> GetPoseCrossSection(vector<vector<float>> &Pose, string ViewType) {

    int numJoints = Pose.size();
    vector<vector<float>> PoseOut(numJoints, vector<float>(2, 0.0));

    int i;
    if (ViewType == "x-y") {

        for (i=0; i < numJoints; i++) {
            PoseOut[i][0] = Pose[i][0];
            PoseOut[i][1] = Pose[i][1];
        }

    } else {

        if (ViewType == "z-y") {
            for (i=0; i < numJoints; i++) {
                PoseOut[i][0] = Pose[i][2];
                PoseOut[i][1] = Pose[i][1];
            }
        } else { // "x-z"
            for (i=0; i < numJoints; i++) {
                PoseOut[i][0] = Pose[i][0];
                PoseOut[i][1] = Pose[i][2];
            }
        }
        
    }

    return PoseOut;

}

vector<vector<float>> ShiftPoseXY(vector<vector<float>>& PoseIn, int ShiftX, int ShiftY) {

    vector<vector<float>> pose = PoseIn;

    int numJoints = pose.size();

    for (int i=0; i < numJoints; i++) {
        pose[i][0] += ShiftX;
        pose[i][1] += ShiftY;
    }
    
    return pose;

}



void PlotPose2d(cv::Mat &Image, vector<vector<float>> &Pose) {

    // Plot connection lines
    int indexStart, indexEnd;
    float x1, y1, x2, y2;
    cv::Point p1, p2;
    cv::Scalar lineColor = cv::Scalar(255, 0, 0);
    int lineThickness = 3;
    for (auto & connect : GetPoseConnect()) {

        indexStart = connect[0]; 
        indexEnd = connect[1]; 

        x1 = Pose[indexStart][0];
        y1 = Pose[indexStart][1];

        x2 = Pose[indexEnd][0];
        y2 = Pose[indexEnd][1];

        p1 = cv::Point(x1, y1);
        p2 = cv::Point(x2, y2);

        line(Image, p1, p2, lineColor, lineThickness, cv::LINE_8);
    }

    // Plot keypoints
    cv::Point point; 
    for (auto & bone : Pose) {

        point.x = bone[0];
        point.y = bone[1];

        cv::circle(Image, point, 3, cv::Scalar(0, 255, 255), -1);

    }

}

void PlotPose2dWithShift(cv::Mat &Image, vector<vector<float>> &Pose, int ShiftX, int ShiftY) {

    vector<vector<float>> poseShifted = ShiftPoseXY(Pose, ShiftX, ShiftY);
    PlotPose2d(Image, poseShifted);

}

void PlotMpPose2d(cv::Mat &Image, vector<vector<float>> &Pose) {

    int num = Pose.size();

    cv::Point point; 
    for (auto & bone : Pose) {

        point.x = bone[0];
        point.y = bone[1];

        cv::circle(Image, point, 3, cv::Scalar(0, 255, 255), -1);

    }



}

cv::Mat CombineImages2x2(cv::Mat& Img1, cv::Mat& Img2, cv::Mat& Img3, cv::Mat& Img4, cv::Size SizeOut) {

    // Resize the images to the final size / 2
    cv::Mat resized1, resized2, resized3, resized4;
    cv::resize(Img1, resized1, cv::Size(SizeOut.width / 2, SizeOut.height / 2));
    cv::resize(Img2, resized2, cv::Size(SizeOut.width / 2, SizeOut.height / 2));
    cv::resize(Img3, resized3, cv::Size(SizeOut.width / 2, SizeOut.height / 2));
    cv::resize(Img4, resized4, cv::Size(SizeOut.width / 2, SizeOut.height / 2));

    // Create the final image
    cv::Mat imageOut(SizeOut, Img1.type());

    // Insert the images
    resized1.copyTo(imageOut(cv::Rect(0, 0, SizeOut.width / 2, SizeOut.height / 2)));
    resized2.copyTo(imageOut(cv::Rect(SizeOut.width / 2, 0, SizeOut.width / 2, SizeOut.height / 2)));
    resized3.copyTo(imageOut(cv::Rect(0, SizeOut.height / 2, SizeOut.width / 2, SizeOut.height / 2)));
    resized4.copyTo(imageOut(cv::Rect(SizeOut.width / 2, SizeOut.height / 2, SizeOut.width / 2, SizeOut.height / 2)));

    return imageOut;
}
