
// Build2D_OpenCV.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CBuild2D_OpenCVApp:
// �йش����ʵ�֣������ Build2D_OpenCV.cpp
//

class CBuild2D_OpenCVApp : public CWinApp
{
public:
	CBuild2D_OpenCVApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CBuild2D_OpenCVApp theApp;