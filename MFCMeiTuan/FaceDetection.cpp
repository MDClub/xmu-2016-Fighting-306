#pragma once
#include "stdafx.h"
#include "FaceDetection.h"

FaceDetection::FaceDetection()
{
	pstrCascadeFileName="haarcascade_frontalface_alt.xml";
	pHaarCascade = (CvHaarClassifierCascade*)cvLoad(pstrCascadeFileName);
	
}
FaceDetection::~FaceDetection()
{

}
vector<Rect> FaceDetection::faceRect(IplImage *pSrcImage,vector<Mat> &faceImage)
{
	vector<Rect> rect;
	// ����ͼ��
	IplImage *pGrayImage = cvCreateImage(cvGetSize(pSrcImage), IPL_DEPTH_8U, 1);
	cvCvtColor(pSrcImage, pGrayImage, CV_BGR2GRAY);

	// ����ʶ������
	if (pHaarCascade != NULL)
	{		
		CvMemStorage *pcvMStorage = cvCreateMemStorage(0);
		cvClearMemStorage(pcvMStorage); 
		CvSeq *pcvSeqFaces = cvHaarDetectObjects(pGrayImage, pHaarCascade, pcvMStorage);   //���Ĵ�����
		for(int i = 0; i <pcvSeqFaces->total; i++)
		{
			CvRect* r = (CvRect*)cvGetSeqElem(pcvSeqFaces, i); 
			Rect temp;
			temp.x=r->x;
			temp.y=r->y;
			temp.width=r->width;
			temp.height=r->height;
			rect.push_back(temp);
			Mat faceImageTemp=Mat(pSrcImage)(temp);
			faceImage.push_back(faceImageTemp);
		}
		cvReleaseMemStorage(&pcvMStorage);
	}
	return rect;
	
}

vector<Rect> FaceDetection::faceRect(IplImage *pSrcImage,int &faceNum,vector<Mat> &faceImage)
{
	vector<Rect> rect;
	// ����ͼ��
	IplImage *pGrayImage = cvCreateImage(cvGetSize(pSrcImage), IPL_DEPTH_8U, 1);
	cvCvtColor(pSrcImage, pGrayImage, CV_BGR2GRAY);

	// ����ʶ������
	if (pHaarCascade != NULL)
	{		
		CvMemStorage *pcvMStorage = cvCreateMemStorage(0);
		cvClearMemStorage(pcvMStorage); 
		CvSeq *pcvSeqFaces = cvHaarDetectObjects(pGrayImage, pHaarCascade, pcvMStorage);   //���Ĵ�����
		faceNum=pcvSeqFaces->total;
		for(int i = 0; i <faceNum; i++)
		{
			CvRect* r = (CvRect*)cvGetSeqElem(pcvSeqFaces, i);
			Rect temp;
			temp.x=r->x;
			temp.y=r->y;
			temp.width=r->width;
			temp.height=r->height;
			rect.push_back(temp);
			Mat faceImageTemp=Mat(pSrcImage)(temp);
			faceImage.push_back(faceImageTemp);
		}
		cvReleaseMemStorage(&pcvMStorage);
	}
	return rect;
	
}