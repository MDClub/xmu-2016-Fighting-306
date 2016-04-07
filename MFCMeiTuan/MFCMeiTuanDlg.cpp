
// MFCMeiTuanDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCMeiTuan.h"
#include "MFCMeiTuanDlg.h"
#include "afxdialogex.h"
#include "CvvImage.h"
#include "FaceDetection.h"
#include <opencv2\opencv.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/legacy/legacy.hpp>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCMeiTuanDlg �Ի���



CMFCMeiTuanDlg::CMFCMeiTuanDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCMeiTuanDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCMeiTuanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCMeiTuanDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCMeiTuanDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCMeiTuanDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCMeiTuanDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CMFCMeiTuanDlg ��Ϣ�������

BOOL CMFCMeiTuanDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	picPath = NULL;
	videoPath = NULL;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMFCMeiTuanDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCMeiTuanDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFCMeiTuanDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCMeiTuanDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(TRUE, //TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���
		NULL, 
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		(LPCTSTR)_TEXT("Image Sorce (*.jpg;*.png)|*.jpg;*.png|All Files (*.*)|*.*||"),
		NULL);
	if(dlg.DoModal()==IDOK)
	{
		PicFilePath=dlg.GetPathName(); //�ļ�����������FilePathName��
		//SetDlgItemText(IDC_EDIT_FilePath,FilePathName);   //��ʾ�ļ�·����
		//CString to char
		int len=PicFilePath.GetLength();
		char *buffer=new char[len+1];    //�����ڴ�
		if(NULL==buffer)
		{
				//�ڴ����ʧ��
				//�쳣����
		}
		memset(buffer,0,len+1);
		WideCharToMultiByte(CP_OEMCP,NULL,(LPCWSTR)PicFilePath,-1,NULL,0,NULL,FALSE);
		WideCharToMultiByte(CP_OEMCP, NULL, (LPCWSTR)PicFilePath, -1,(LPSTR)buffer, len, NULL, FALSE);
		buffer[len]='\0';
		//**����Ƶ**//
		picPath = buffer;
		sampleImg = cvLoadImage(picPath);
		if(!sampleImg)
		{
			AfxMessageBox(_T("Please Choose The Sample Picture !"));
		} 
		else
		{
			p_pStc = (CStatic *)GetDlgItem(IDC_STATIC_P);	//IDC_VIEWΪPicture�ؼ�ID
			p_pStc->GetClientRect(&p_rect);    //��CWind��ͻ���������㴫������
			p_pDC = p_pStc->GetDC();    //�õ�Picture�ؼ��豸������
			p_hDC = p_pDC->GetSafeHdc();
			CvvImage cvvImage;  
			cvvImage.CopyOf(sampleImg,1); //���Ƹ�֡ͼ��    
			cvvImage.DrawToHDC(p_hDC, &p_rect); //��ʾ���豸�ľ��ο���
		}		
		delete buffer;  //�ͷ��ڴ� 
		buffer = NULL;		
		//AfxMessageBox(PicFilePath);
	}
}


void CMFCMeiTuanDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg2(TRUE, //TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���
		NULL, 
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		(LPCTSTR)_TEXT("Video Sorce (*.avi;*.mp4)|*.avi;*.mp4|All Files (*.*)|*.*||"),
		NULL);
	if(dlg2.DoModal()==IDOK)
	{
		VideoFilePath =dlg2.GetPathName(); //�ļ�����������FilePathName��
		//AfxMessageBox(VideoFilePath);
		int len=VideoFilePath.GetLength();
		char *buffer=new char[len+1];    //�����ڴ�
		if(NULL==buffer)
		{
				//�ڴ����ʧ��
				//�쳣����
		}
		memset(buffer,0,len+1);
		WideCharToMultiByte(CP_OEMCP,NULL,(LPCWSTR)VideoFilePath,-1,NULL,0,NULL,FALSE);
		WideCharToMultiByte(CP_OEMCP, NULL, (LPCWSTR)VideoFilePath, -1,(LPSTR)buffer, len, NULL, FALSE);
		buffer[len]='\0';
		//**����Ƶ**//
		videoPath = buffer;
		v_capture=cvCreateFileCapture(videoPath);   //��ʼ��һ����Ƶ�ļ���׽��
		if(!v_capture)
		{
			AfxMessageBox(_T("Can not open video!"));
			//pBtnVideo->SetCheck(0);  //���á���Ƶ��Ϣ����ѡ��״̬Ϊ��δѡ�С�
		} 
		else
		{
			v_pStc = (CStatic *)GetDlgItem(IDC_STATIC_V);	//IDC_VIEWΪPicture�ؼ�ID
			v_pStc->GetClientRect(&v_rect);    //��CWind��ͻ���������㴫������
			v_pDC = v_pStc->GetDC();    //�õ�Picture�ؼ��豸������
			v_hDC = v_pDC->GetSafeHdc();
			m_inputFrame=cvQueryFrame(v_capture); //������ͷ�����ļ���ץȡ������һ֡
			CvvImage cvvImage;  
			cvvImage.CopyOf(m_inputFrame,1); //���Ƹ�֡ͼ��    
			cvvImage.DrawToHDC(v_hDC, &v_rect); //��ʾ���豸�ľ��ο���
		}
		delete buffer;  //�ͷ��ڴ� 
		buffer = NULL;		
	}
}


void CMFCMeiTuanDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(picPath&&videoPath)
	{
		IplImage *srcImage1;
		FaceDetection faceDete;		
		vector<Mat> faceImage;
		vector<Rect> faceRect=faceDete.faceRect(sampleImg, faceImage);
		Mat trainImage;
		if(faceImage.size()==0)
		{
			AfxMessageBox(_T("No face!"));
			
		}

		//Mat trainImage;
		trainImage = Mat(sampleImg);
		trainImage=faceImage[0];
		SurfFeatureDetector detector(300);                   
		vector<KeyPoint> trainKeyPoints;                    //���������������㼯
		detector.detect(trainImage,trainKeyPoints);
		SurfDescriptorExtractor  extractor;                  //���������
		Mat trainDescriptors;
		extractor.compute(trainImage,trainKeyPoints,trainDescriptors);
		FlannBasedMatcher matcher;              //��ƥ����
		//CvCapture *capture=cvCreateFileCapture("1.avi");
		//CvCapture* capture = cvCreateCameraCapture(-1);
		int nframe=0;
		while(srcImage1=cvQueryFrame(v_capture))
		{
			nframe++;
			//cout <<"��"<< nframe<<"֡:\n" << endl;
			//�ڶ������Դ����ͼƬ����ȡ���������֣�������vector<Mat> faces;
			vector<Mat> faces;
			vector<Rect> faceRects; 		
			
			//flip((Mat)srcImage1,(Mat)srcImage1,0);
			//imshow("�����Ƶ",Mat(srcImage1));
			faceRects=faceDete.faceRect(srcImage1,faces);
			int faceNum=faces.size();
			if(faceNum==0)
			{
				//cout<<"û�д�ƥ��������\n";				
				CvvImage cvvImage;  
				cvvImage.CopyOf(srcImage1,1); //���Ƹ�֡ͼ��    
				cvvImage.DrawToHDC(v_hDC, &v_rect);
				continue;
			}

			vector<int> fakeFaceIndex;

			//�����������������������������ƥ�䣬�ҳ������Ƶ���ʾ������
         
			vector<KeyPoint> *testKeyPoints=new vector<KeyPoint>[faceNum];    //�������������㼯	
			vector<KeyPoint> *testKeyPoints0=new vector<KeyPoint>[faceNum];
			Mat *testDescriptors=new Mat[faceNum];
			Mat *testDescriptors0=new Mat[faceNum];	
			for(int i=0;i<faceNum;i++)
			{
				  detector.detect(faces[i],testKeyPoints0[i]);
				  extractor.compute(faces[i],testKeyPoints0[i],testDescriptors0[i]);
				  if(testDescriptors0[i].cols==0)
					  fakeFaceIndex.push_back(i);
			}
			for(int i=0;i<(int)fakeFaceIndex.size();i++)
			{
				vector<Mat>::iterator faceIt=faces.begin();
				vector<Rect>::iterator faceRectIt=faceRects.begin();
				int ii=0;
				while(ii++<fakeFaceIndex[i])
				{
					faceIt++;
					faceRectIt++;
				}
				faces.erase(faceIt);
				faceRects.erase(faceRectIt);
			}
			int k=0;
			for(int i=0;i<faceNum;i++)
			{

				if(find(fakeFaceIndex.begin(),fakeFaceIndex.end(),i)==fakeFaceIndex.end())
				{
					testDescriptors[k]=testDescriptors0[i];
					testKeyPoints[k]=testKeyPoints0[i];
					k++;
				}
			}
			faceNum-=fakeFaceIndex.size();
			//cout<<"��"<<faceNum<<"�Ŵ�ƥ�����������ڼ������ƶ�...\n";
	
			vector<DMatch> *matches=new vector<DMatch>[faceNum];
			for(int i=0;i<faceNum;i++)
			{
				
				   matcher.match(trainDescriptors,testDescriptors[i],matches[i]);
		
			}

			double *min_dist=new double[faceNum];
			double *max_dist=new double[faceNum];
			double *mean_dist=new double[faceNum];
			for(int i=0;i<faceNum;i++)
			{
				max_dist[i]=0.0;
				min_dist[i]=1.0;
			}
			for(int i=0;i<faceNum;i++)
			{
				double sum=0.0;
				for(int j=0;j<(int)matches[i].size();j++)
				{
					double dist=matches[i][j].distance;
					sum+=dist;
					if(dist<=min_dist[i])
					{
						min_dist[i]=dist;
					}
					if(dist>=max_dist[i])
					{
						max_dist[i]=dist;
					}
				}
				mean_dist[i]=sum/(double)matches[i].size();

			}
			//for(int i=0;i<faceNum;i++)
				//cout<<"����"<<i+1<<"��������������: "<<max_dist[i]<<",��С����: "<<min_dist[i]<<",ƽ�����룺 "<<mean_dist[i]<<endl;

			vector<DMatch> *goodMatches=new vector<DMatch>[faceNum];
			for(int i=0;i<faceNum;i++)
			{
				for(int j=0;j<(int)matches[i].size();j++)
					if(matches[i][j].distance<=1.2*mean_dist[i])
						goodMatches[i].push_back(matches[i][j]);

			}
		
			//��������ƥ����ƽ������
			for(int i=0;i<faceNum;i++)
			{
				double sum=0.0;
				for(int j=0;j<(int)goodMatches[i].size();j++)
				{
					sum+=matches[i][j].distance;
				}
				mean_dist[i]=sum/(double)matches[i].size();
			}
			Mat *dst0=new Mat[faceNum];
			/*for(int i=0;i<faceNum;i++)
			{
				drawMatches(trainImage,trainKeyPoints,faces[i],testKeyPoints[i],goodMatches[i],dst0[i]);
				namedWindow("�Ա���"+num2str(i+1));
				imshow("�Ա���"+num2str(i+1),dst0[i]);
			}*/

  
			Rect mostFitRect;
			double minDist=100.0;    //ѡȡƽ��������С��
			for(int i=0;i<faceNum;i++)
			{
				if(mean_dist[i]<=minDist)
				{
					minDist=mean_dist[i];
					mostFitRect=faceRects[i];
				}
			}
			Mat dst=Mat(srcImage1);
			if(minDist<=0.3)
			{	
				CvFont font;
                cvInitFont( &font, CV_FONT_HERSHEY_COMPLEX_SMALL ,1, 1, 0, 1, 4);	
				rectangle(dst,mostFitRect,Scalar(0,0,255));
				char* lab = "Target person!";	
				cvPutText(&IplImage(dst), lab , Point(mostFitRect.x+0.25*mostFitRect.width,mostFitRect.y-30),&font, CV_RGB(255, 0, 0) );
				CvvImage cvvImage;  
				cvvImage.CopyOf(&IplImage(dst),1); //���Ƹ�֡ͼ��    
				cvvImage.DrawToHDC(v_hDC, &v_rect);
				//imshow("�����Ƶ",dst);		
			}
			else
			{
				CvvImage cvvImage;  
				cvvImage.CopyOf(&IplImage(dst),1); //���Ƹ�֡ͼ��    
				cvvImage.DrawToHDC(v_hDC, &v_rect);
			}
		}
	}
	else
	{
		if(!picPath)
		{
			AfxMessageBox(_T("Please Check Sorce pic!"));
		}
		if(!videoPath)
		{
			AfxMessageBox(_T("Please Check Sorce Video!"));
		}
	}
}
