
// MFCMeiTuanDlg.cpp : 实现文件
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


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMFCMeiTuanDlg 对话框



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


// CMFCMeiTuanDlg 消息处理程序

BOOL CMFCMeiTuanDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	picPath = NULL;
	videoPath = NULL;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCMeiTuanDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCMeiTuanDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCMeiTuanDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlg(TRUE, //TRUE为OPEN对话框，FALSE为SAVE AS对话框
		NULL, 
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		(LPCTSTR)_TEXT("Image Sorce (*.jpg;*.png)|*.jpg;*.png|All Files (*.*)|*.*||"),
		NULL);
	if(dlg.DoModal()==IDOK)
	{
		PicFilePath=dlg.GetPathName(); //文件名保存在了FilePathName里
		//SetDlgItemText(IDC_EDIT_FilePath,FilePathName);   //显示文件路径名
		//CString to char
		int len=PicFilePath.GetLength();
		char *buffer=new char[len+1];    //申请内存
		if(NULL==buffer)
		{
				//内存分配失败
				//异常处理
		}
		memset(buffer,0,len+1);
		WideCharToMultiByte(CP_OEMCP,NULL,(LPCWSTR)PicFilePath,-1,NULL,0,NULL,FALSE);
		WideCharToMultiByte(CP_OEMCP, NULL, (LPCWSTR)PicFilePath, -1,(LPSTR)buffer, len, NULL, FALSE);
		buffer[len]='\0';
		//**打开视频**//
		picPath = buffer;
		sampleImg = cvLoadImage(picPath);
		if(!sampleImg)
		{
			AfxMessageBox(_T("Please Choose The Sample Picture !"));
		} 
		else
		{
			p_pStc = (CStatic *)GetDlgItem(IDC_STATIC_P);	//IDC_VIEW为Picture控件ID
			p_pStc->GetClientRect(&p_rect);    //将CWind类客户区的坐标点传给矩形
			p_pDC = p_pStc->GetDC();    //得到Picture控件设备上下文
			p_hDC = p_pDC->GetSafeHdc();
			CvvImage cvvImage;  
			cvvImage.CopyOf(sampleImg,1); //复制该帧图像    
			cvvImage.DrawToHDC(p_hDC, &p_rect); //显示到设备的矩形框内
		}		
		delete buffer;  //释放内存 
		buffer = NULL;		
		//AfxMessageBox(PicFilePath);
	}
}


void CMFCMeiTuanDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlg2(TRUE, //TRUE为OPEN对话框，FALSE为SAVE AS对话框
		NULL, 
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		(LPCTSTR)_TEXT("Video Sorce (*.avi;*.mp4)|*.avi;*.mp4|All Files (*.*)|*.*||"),
		NULL);
	if(dlg2.DoModal()==IDOK)
	{
		VideoFilePath =dlg2.GetPathName(); //文件名保存在了FilePathName里
		//AfxMessageBox(VideoFilePath);
		int len=VideoFilePath.GetLength();
		char *buffer=new char[len+1];    //申请内存
		if(NULL==buffer)
		{
				//内存分配失败
				//异常处理
		}
		memset(buffer,0,len+1);
		WideCharToMultiByte(CP_OEMCP,NULL,(LPCWSTR)VideoFilePath,-1,NULL,0,NULL,FALSE);
		WideCharToMultiByte(CP_OEMCP, NULL, (LPCWSTR)VideoFilePath, -1,(LPSTR)buffer, len, NULL, FALSE);
		buffer[len]='\0';
		//**打开视频**//
		videoPath = buffer;
		v_capture=cvCreateFileCapture(videoPath);   //初始化一个视频文件捕捉器
		if(!v_capture)
		{
			AfxMessageBox(_T("Can not open video!"));
			//pBtnVideo->SetCheck(0);  //设置“视频信息”复选框状态为“未选中”
		} 
		else
		{
			v_pStc = (CStatic *)GetDlgItem(IDC_STATIC_V);	//IDC_VIEW为Picture控件ID
			v_pStc->GetClientRect(&v_rect);    //将CWind类客户区的坐标点传给矩形
			v_pDC = v_pStc->GetDC();    //得到Picture控件设备上下文
			v_hDC = v_pDC->GetSafeHdc();
			m_inputFrame=cvQueryFrame(v_capture); //从摄像头或者文件中抓取并返回一帧
			CvvImage cvvImage;  
			cvvImage.CopyOf(m_inputFrame,1); //复制该帧图像    
			cvvImage.DrawToHDC(v_hDC, &v_rect); //显示到设备的矩形框内
		}
		delete buffer;  //释放内存 
		buffer = NULL;		
	}
}


void CMFCMeiTuanDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
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
		vector<KeyPoint> trainKeyPoints;                    //给定人脸的特征点集
		detector.detect(trainImage,trainKeyPoints);
		SurfDescriptorExtractor  extractor;                  //求出描述子
		Mat trainDescriptors;
		extractor.compute(trainImage,trainKeyPoints,trainDescriptors);
		FlannBasedMatcher matcher;              //求匹配点对
		//CvCapture *capture=cvCreateFileCapture("1.avi");
		//CvCapture* capture = cvCreateCameraCapture(-1);
		int nframe=0;
		while(srcImage1=cvQueryFrame(v_capture))
		{
			nframe++;
			//cout <<"第"<< nframe<<"帧:\n" << endl;
			//第二步，对待检测图片，提取出人脸部分，保存在vector<Mat> faces;
			vector<Mat> faces;
			vector<Rect> faceRects; 		
			
			//flip((Mat)srcImage1,(Mat)srcImage1,0);
			//imshow("检测视频",Mat(srcImage1));
			faceRects=faceDete.faceRect(srcImage1,faces);
			int faceNum=faces.size();
			if(faceNum==0)
			{
				//cout<<"没有待匹配人脸！\n";				
				CvvImage cvvImage;  
				cvvImage.CopyOf(srcImage1,1); //复制该帧图像    
				cvvImage.DrawToHDC(v_hDC, &v_rect);
				continue;
			}

			vector<int> fakeFaceIndex;

			//第三步，将给定人脸与待检人脸做匹配，找出最相似的显示出来。
         
			vector<KeyPoint> *testKeyPoints=new vector<KeyPoint>[faceNum];    //待测人脸特征点集	
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
			//cout<<"有"<<faceNum<<"张待匹配人脸，正在计算相似度...\n";
	
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
				//cout<<"人脸"<<i+1<<"的特征点最大距离: "<<max_dist[i]<<",最小距离: "<<min_dist[i]<<",平均距离： "<<mean_dist[i]<<endl;

			vector<DMatch> *goodMatches=new vector<DMatch>[faceNum];
			for(int i=0;i<faceNum;i++)
			{
				for(int j=0;j<(int)matches[i].size();j++)
					if(matches[i][j].distance<=1.2*mean_dist[i])
						goodMatches[i].push_back(matches[i][j]);

			}
		
			//计算优秀匹配点的平均距离
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
				namedWindow("对比照"+num2str(i+1));
				imshow("对比照"+num2str(i+1),dst0[i]);
			}*/

  
			Rect mostFitRect;
			double minDist=100.0;    //选取平均距离最小的
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
				cvvImage.CopyOf(&IplImage(dst),1); //复制该帧图像    
				cvvImage.DrawToHDC(v_hDC, &v_rect);
				//imshow("检测视频",dst);		
			}
			else
			{
				CvvImage cvvImage;  
				cvvImage.CopyOf(&IplImage(dst),1); //复制该帧图像    
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
