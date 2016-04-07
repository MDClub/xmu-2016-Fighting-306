#include <opencv2/opencv.hpp>  
#include "stdafx.h"
using namespace cv;

#ifndef FACEDETECTION_H 
#define FACEDETECTION_H 
class FaceDetection
{
    char *pstrCascadeFileName;   //OpenCV中自带人脸分类器的文件路径
	CvHaarClassifierCascade *pHaarCascade;

public:
	FaceDetection();
	~FaceDetection();
	vector<Rect> faceRect(IplImage *pSrcImage,vector<Mat> &faceImage);        //检测单张人脸，
	vector<Rect> faceRect(IplImage *pSrcImage,int &faceNum,vector<Mat> &faceImage);       //检测多张人脸，返回标记人脸的矩形框及个数,并将人脸区域保存
};

#endif FACEDETECTION_H