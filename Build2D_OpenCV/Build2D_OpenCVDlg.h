
// Build2D_OpenCVDlg.h : ͷ�ļ�
//

#pragma once
#include "comaccess.h"
#include <iostream>  
#include<opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp>  
#include<opencv2/imgproc/imgproc.hpp>  
#include "OpenCVCam.h"
#include "Markup.h"
  
#include<string>  
  
using namespace std;  
using namespace cv;  

// CBuild2D_OpenCVDlg �Ի���
class CBuild2D_OpenCVDlg : public CDialogEx
{
// ����
public:
	CBuild2D_OpenCVDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_BUILD2D_OPENCV_DIALOG };

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
	virtual void OnCancel();							//�رճ���
	void UpdateDatas();									//���½�������
	
	//���ڿ���
	int m_comNum;										// COM
	ComAccess com;										// ���ڶ���
	CString m_sendCStr;									// ���ڷ��͵���Ϣ
	afx_msg void OnBnClickedBtnComm();
	afx_msg void OnBnClickedBtnSend();

	//�������
	COpenCVCam cam;										//OpenCV�������
	afx_msg void OnBnClickedBtnContinuous();			//ʵʱ
	afx_msg void OnBnClickedBtnCam();					//�������
	afx_msg void OnBnClickedBtnSingle();				//����
	afx_msg void OnBnClickedBtnPic();					//��ͼ

	//��ʼ��
	afx_msg void OnBnClickedBtnA();						//ѡ��A��
	afx_msg void OnBnClickedBtnB();						//ѡ��B��
	Point m_A,m_B;										//AB��	
	double m_ABdis;										//AB����mm
	double m_ratio;										//����mm/pix
	afx_msg void OnBnClickedBtnRatio();					//�������

	
	afx_msg void OnBnClickedCheckXy();
	afx_msg void OnBnClickedCheckReal();	
	BOOL m_xy;											// �Ƿ���ʾ����ϵ
	BOOL m_real;										// �Ƿ���ʾԭͼ

	//zoom�����ڴ�Сԭͼ�����ͼ
	//xyZoom�����ڴ�Сԭͼ�����ͼ+����ϵ
	//realZoom�����ڴ�Сԭͼ�����ͼʵʱ��ʾ����������Ϣ
	Mat zoom,xyZoom,realZoom;  

	//xyScr��ԭͼ�����ͼ+����ϵ
	//realScr��ԭͼ�����ͼʵʱ��ʾ����������Ϣ
	//rectifyScr;ԭͼ�����ͼ
	Mat xyScr,realScr,rectifyScr; 

	//scr��ԭͼ
	Mat scr;

	afx_msg LRESULT OnUpdateMessage(WPARAM wParam, LPARAM lParam); //�߳�֪ͨ�������
	afx_msg void OnBnClickedBtnDis();
	// ͼ��ֱ���
	CString m_pix;

	//�滭ĳ���־
	void DrawX(Mat &image, Point point);

	//ͼ��������
	void Rectify(Mat &scr, Mat &dst, CString xmlPath);
	// �Ƿ�������
	BOOL m_isRectify;
	afx_msg void OnBnClickedCheckRectify();

	//��Сͼ������תԭͼ������
	void ZoomToSrc(Mat &zoom, Mat &scr, Point zoomP, int &x, int &y);

	//HObject2Mat
	//Mat HObject2Mat(HObject Hobj);
};
