#include "StdAfx.h"
#include "OpenCVCam.h"


COpenCVCam::COpenCVCam(void)
{
}


COpenCVCam::~COpenCVCam(void)
{
}

bool COpenCVCam::OpenCam(int index)
{
	bool result = capture.open(index);
	if(!result)
	{
		AfxMessageBox(L"�����ʧ��");
	}
	return result;
}
	
Mat COpenCVCam::GetImage()
{
	Mat frame; //����һ��Mat���������ڴ洢ÿһ֡��ͼ��  
	if(capture.isOpened())                
	{
		capture >> frame;  //��ȡ��ǰ֡   
	} 
	else
	{
		AfxMessageBox(L"δ�����");
	}
	return frame;
}
	
bool COpenCVCam::CloseCam()
{
	capture.release();
	return true;
}