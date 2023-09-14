#pragma once

#include <string>
#include <iostream>
#include <filesystem> 
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class ImageExporter {

public:

    ImageExporter() {
    }

    ~ImageExporter() {
    }

    void SetConfig(string OutputDir, string FilePrefix, string FileExt) {

        SetOutputDir(OutputDir);
        SetFilePrefix(FilePrefix);
        SetFileExt(FileExt);
        
        CreateDir(OutputDir);

    }

    void ExportImage(cv::Mat Image) {

        string filepath;
        string filename;
        string stringIndex;

        // Update file index 
        mFileIndex += 1;

        if (mFileIndex % mSnapshotInterval == 0) {

            stringIndex = IntToStringWithZeros(mFileIndex, mFieldWidth);
            filename = mFilePrefix + stringIndex + "." + mFileExt;
            filepath = JoinPath(mOutputDir, filename);
            cv::imwrite(filepath, Image);

        }

    }

    void SetSnapshotInterval(int Num) {
        mSnapshotInterval = Num;
    }

    int GetSnapshotInterval() {
        return mSnapshotInterval;
    }

    void SetOutputDir(string DirPath) {
        mOutputDir = DirPath;
    }

    string GetOutputDir() {
        return mOutputDir;
    }

    void SetFilePrefix(string FilePrefix) {
        mFilePrefix = FilePrefix;
    }

    string GetFilePrefix() {
        return mFilePrefix;
    }

    void SetFileExt(string FileExt) {
        mFileExt = FileExt;
    }

    string GetFileExt() {
        return mFileExt;
    }

    void CreateDir(const string& DirPath) {

        std::filesystem::path dir(DirPath);
    
        if (!std::filesystem::exists(dir)){
            std::filesystem::create_directory(dir);
            std::cout << "Create directory: " << DirPath << std::endl;
        }
    }

    string IntToStringWithZeros(int i, int FieldWidth) {

        std::ostringstream ss;
        ss << std::setw(FieldWidth) << std::setfill('0') << i;
        return ss.str();
    }

    string JoinPath(const string& DirPath, const string& Filename) {

        std::filesystem::path dir(DirPath);
        dir /= Filename; // append filename to directory path

        return dir.string();
    }


private:

    string mOutputDir = "outputs";
    string mFilePrefix = "image_";
    string mFileExt = "jpg";
    cv::Mat mImage;

    int mFileIndex = 0;
    int mFieldWidth = 6;

    int mSnapshotInterval = 1;

};