#pragma once

#include <opencv2/opencv.hpp>
#include <matplot/matplot.h>

namespace plotlib {

    using namespace std;
    using namespace cv;
    using namespace matplot;

    figure_handle Figure();
    void Figure(bool bQuietMode);
    axes_handle Subplot(int Rows, int Cols, int PlotId);

    figure_handle Gcf();
    axes_handle Gca();
    void Cla();

    line_handle Plot(axes_handle& Ax,
        vector<float>& DataX, vector<float>& DataY);

    line_handle Scatter(axes_handle& Ax,
        vector<float>& DataX, vector<float>& DataY);

    void Hold(bool bFlag);

    void ConvertFigureToMat(figure_handle& FigHandle, Mat& Image);
    vector<double> ConvertVectorFloatToDouble(const std::vector<float>& VecIn);

    cv::Mat CvCombineImages2x2(cv::Mat& Img1, cv::Mat& Img2,
        cv::Mat& Img3, cv::Mat& Img4, cv::Size SizeOut);

    //template<class T>
    //vector<T> MakeValidPoint2D(vector<T>& PointIn, int ImageWidth, int ImageHeight);
    vector<double> MakeValidPoint2D(vector<double>& PointIn, int ImageWidth, int ImageHeight);

} // Namespace
