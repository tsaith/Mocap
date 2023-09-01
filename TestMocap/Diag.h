#pragma once

#include "PlotUtils.h"
#include "TextPlotter.hpp" 

using namespace std;
using namespace cv;

namespace dg {


    class Diag {

    public:

        Diag();
        ~Diag();

        void Init(int ImageWidth, int ImageHeight);
	    void Process();

	    void SetSkeleton(vector<vector<float>>& Quats,
            vector<vector<float>>& Bones);
        void SetInputImage(Mat& Image);
        Mat GetDiagImage();
        Mat GetSkelImage();

    private:

        int mImageWidth = 1280;
        int mImageHeight = 720;

        vector<vector<float>> mSkelQuats;
        vector<vector<float>> mSkelBones;

        Mat mInputImage;
        Mat mSkelImage;
        Mat mDiagImage;

    };

}
