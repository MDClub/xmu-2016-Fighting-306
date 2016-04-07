
// MFCMeiTuanDlg.h : 头文件
//

#pragma once
#include <highgui.h>

// CMFCMeiTuanDlg 对话框
class CMFCMeiTuanDlg : public CDialogEx
{
// 构造
public:
	CMFCMeiTuanDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MFCMEITUAN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();



public:
	CString PicFilePath;
	CString VideoFilePath;
	CRect p_rect;   //图像区域
	CRect v_rect;   //视频矩形区域
	CStatic* p_pStc; //标识图像显示的picture控件
	CDC* p_pDC;   //视频显示控件设备上下文
	HDC p_hDC;   //设备当前HDC
	CStatic* v_pStc; //标识图像显示的picture控件
	CDC* v_pDC;   //视频显示控件设备上下文
	HDC v_hDC;   //设备当前HDC
	IplImage* sampleImg; //sameple pic
	CvCapture* v_capture; //video imput
	afx_msg void OnBnClickedButton2();
	char *picPath;
	char *videoPath;
	IplImage* m_inputFrame;  //输入视频帧
	afx_msg void OnBnClickedButton3();
};
