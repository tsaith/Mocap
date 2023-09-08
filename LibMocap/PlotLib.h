#pragma once

//#include <stdio.h>
//#include <iostream>
//#include <string>

//#include <memory>
#include <opencv2/opencv.hpp>
#include <matplot/matplot.h>

namespace plotlib {

    using namespace std;
    using namespace cv;
    using namespace matplot;

    void ConvertFigureToMat(figure_handle& FigHandle, Mat& Image);
    axes_handle Subplot(int Rows, int Cols, int Index);

    line_handle Scatter(axes_handle& Ax,
        vector<float>& DataX, vector<float>& DataY);

    vector<double> ConvertVectorFloatToDouble(const std::vector<float>& VecIn);

} // Namespace
