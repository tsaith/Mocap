#include "pch.h"

#include "PlotLib.h"

namespace plotlib {


    void ConvertFigureToMat(figure_handle& FigHandle, Mat& Image)
    {
        string figPath = "Outputs/matplot_temporary_plot.jpg";
        save(FigHandle, figPath);
        Image = cv::imread(figPath);
    }

    axes_handle Subplot(int Rows, int Cols, int Index)
    {
        axes_handle ax = subplot(Rows, Cols, Index);
        return ax;
    }

    line_handle Scatter(axes_handle& Ax, 
        vector<float>& DataX, vector<float>& DataY)
    {
        vector<double> x = ConvertVectorFloatToDouble(DataX);
        vector<double> y = ConvertVectorFloatToDouble(DataY);

        line_handle h = Ax->scatter(x, y);

        return h;
    }

    vector<double> ConvertVectorFloatToDouble(const std::vector<float>& VecIn)
    {
        vector<double> vecOut(VecIn.size());
        std::copy(VecIn.begin(), VecIn.end(), vecOut.begin());

        return vecOut;
    }

}
