
// MFCMeiTuanDlg.h : ͷ�ļ�
//

#pragma once
#include <highgui.h>

// CMFCMeiTuanDlg �Ի���
class CMFCMeiTuanDlg : public CDialogEx
{
// ����
public:
	CMFCMeiTuanDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFCMEITUAN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	CRect p_rect;   //ͼ������
	CRect v_rect;   //��Ƶ��������
	CStatic* p_pStc; //��ʶͼ����ʾ��picture�ؼ�
	CDC* p_pDC;   //��Ƶ��ʾ�ؼ��豸������
	HDC p_hDC;   //�豸��ǰHDC
	CStatic* v_pStc; //��ʶͼ����ʾ��picture�ؼ�
	CDC* v_pDC;   //��Ƶ��ʾ�ؼ��豸������
	HDC v_hDC;   //�豸��ǰHDC
	IplImage* sampleImg; //sameple pic
	CvCapture* v_capture; //video imput
	afx_msg void OnBnClickedButton2();
	char *picPath;
	char *videoPath;
	IplImage* m_inputFrame;  //������Ƶ֡
	afx_msg void OnBnClickedButton3();
};
