#include "pch.h"

#include "PlotLib.h"

namespace plotlib {


    figure_handle Figure()
    {
        return figure();
    }

    void Figure(bool bQuietMode)
    {
        figure(bQuietMode);
    }


    axes_handle Subplot(int Rows, int Cols, int PlotId)
    {
        axes_handle ax = subplot(Rows, Cols, PlotId);
        return ax;
    }

    figure_handle Gcf()
    {
        return gcf();
    }

    axes_handle Gca()
    {
        return gca();
    }

    void Cla()
    {
        cla();
    }

    line_handle Plot(axes_handle& Ax, 
        vector<float>& DataX, vector<float>& DataY)
    {
        vector<double> x = ConvertVectorFloatToDouble(DataX);
        vector<double> y = ConvertVectorFloatToDouble(DataY);

        line_handle h = Ax->plot(x, y);

        return h;
    }

    line_handle Scatter(axes_handle& Ax, 
        vector<float>& DataX, vector<float>& DataY)
    {
        vector<double> x = ConvertVectorFloatToDouble(DataX);
        vector<double> y = ConvertVectorFloatToDouble(DataY);

        line_handle h = Ax->scatter(x, y);

        return h;
    }

    void Hold(bool bFlag)
    {
        hold(bFlag);
    }

    void ConvertFigureToMat(figure_handle& FigHandle, Mat& Image)
    {
        string figPath = "Outputs/matplot_temporary_plot.jpg";
        save(FigHandle, figPath);

        // Wait for file writing
        int ms = 50;
        Sleep(ms);

        do {
            Image = cv::imread(figPath);
        } while (!Image.data);
    }

    vector<double> ConvertVectorFloatToDouble(const std::vector<float>& VecIn)
    {
        vector<double> vecOut(VecIn.size());
        std::copy(VecIn.begin(), VecIn.end(), vecOut.begin());

        return vecOut;
    }

}
