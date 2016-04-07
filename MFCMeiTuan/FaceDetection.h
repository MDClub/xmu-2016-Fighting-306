#include <opencv2/opencv.hpp>  
#include "stdafx.h"
using namespace cv;

#ifndef FACEDETECTION_H 
#define FACEDETECTION_H 
class FaceDetection
{
    char *pstrCascadeFileName;   //OpenCV���Դ��������������ļ�·��
	CvHaarClassifierCascade *pHaarCascade;

public:
	FaceDetection();
	~FaceDetection();
	vector<Rect> faceRect(IplImage *pSrcImage,vector<Mat> &faceImage);        //��ⵥ��������
	vector<Rect> faceRect(IplImage *pSrcImage,int &faceNum,vector<Mat> &faceImage);       //���������������ر�������ľ��ο򼰸���,�����������򱣴�
};

#endif FACEDETECTION_H