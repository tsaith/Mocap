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

        double sz = 3;
        line_handle h = Ax->scatter(x, y, sz);

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

    cv::Mat CvCombineImages2x2(cv::Mat& Img1, cv::Mat& Img2,
        cv::Mat& Img3, cv::Mat& Img4, cv::Size SizeOut)
    {

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

    //template<class T>
	//vector<T> MakeValidPoint2D(vector<T>& PointIn, int ImageWidth, int ImageHeight)
	vector<double> MakeValidPoint2D(vector<double>& PointIn, int ImageWidth, int ImageHeight)
    {

        //T x, y;
        double x, y;
        x = PointIn[0];
        y = PointIn[1];

        int leftBound = 0;
        int rightBound = ImageWidth - 1;
        int topBound = 0;
        int bottomBound = ImageHeight - 1;

        if (x < leftBound) x = 0;
        if (x > rightBound) x = rightBound;
        if (y < topBound) y = 0;
        if (y > bottomBound) y = bottomBound;

        //vector<T> p;
        vector<double> p;
        p.push_back(x);
        p.push_back(y);

        return p;

    }

}
