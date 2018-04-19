
// Build2D_OpenCVDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Build2D_OpenCV.h"
#include "Build2D_OpenCVDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_UPDATE_MESSAGE (WM_USER+200) //�߳�֪ͨ�������
#define DELAY_REAL 500					//ʵʱ�ɼ�ͼ���ӳ�

//ʵʱ�ɼ�ͼ���߳�
DWORD WINAPI ThreadReal(LPVOID pthread)
{
	CBuild2D_OpenCVDlg * m_pDlg = (CBuild2D_OpenCVDlg*)pthread;
	CString butCStr;
	do{
		m_pDlg->GetDlgItemTextW(IDC_BTN_CONTINUOUS, butCStr);
		m_pDlg->PostMessage(WM_UPDATE_MESSAGE,0,0);
		Sleep(DELAY_REAL);
	}while(L"ʵʱ����" == butCStr);
	return 0;
}

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


// CBuild2D_OpenCVDlg �Ի���




CBuild2D_OpenCVDlg::CBuild2D_OpenCVDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBuild2D_OpenCVDlg::IDD, pParent)
	, m_comNum(1)
	, m_sendCStr(_T(""))
	, m_ABdis(0)
	, m_ratio(0.1)
	, m_xy(FALSE)
	, m_real(FALSE)
	, m_pix(_T("�������"))
	, m_isRectify(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBuild2D_OpenCVDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_COM, m_comNum);
	DDX_Text(pDX, IDC_EDIT_SEND, m_sendCStr);
	DDX_Text(pDX, IDC_EDIT_AB, m_ABdis);
	DDX_Text(pDX, IDC_EDIT_RATIO, m_ratio);
	DDX_Check(pDX, IDC_CHECK_XY, m_xy);
	DDX_Check(pDX, IDC_CHECK_REAL, m_real);
	DDX_Text(pDX, IDC_STATIC_CAM, m_pix);
	DDX_Check(pDX, IDC_CHECK_RECTIFY, m_isRectify);
}

BEGIN_MESSAGE_MAP(CBuild2D_OpenCVDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_COMM, &CBuild2D_OpenCVDlg::OnBnClickedBtnComm)
	ON_BN_CLICKED(IDC_BTN_SEND, &CBuild2D_OpenCVDlg::OnBnClickedBtnSend)
	ON_BN_CLICKED(IDC_BTN_SINGLE, &CBuild2D_OpenCVDlg::OnBnClickedBtnSingle)
	ON_BN_CLICKED(IDC_BTN_PIC, &CBuild2D_OpenCVDlg::OnBnClickedBtnPic)
	ON_BN_CLICKED(IDC_BTN_A, &CBuild2D_OpenCVDlg::OnBnClickedBtnA)
	ON_BN_CLICKED(IDC_BTN_B, &CBuild2D_OpenCVDlg::OnBnClickedBtnB)
	ON_BN_CLICKED(IDC_BTN_RATIO, &CBuild2D_OpenCVDlg::OnBnClickedBtnRatio)
	ON_BN_CLICKED(IDC_CHECK_XY, &CBuild2D_OpenCVDlg::OnBnClickedCheckXy)
	ON_BN_CLICKED(IDC_CHECK_REAL, &CBuild2D_OpenCVDlg::OnBnClickedCheckReal)
	ON_BN_CLICKED(IDC_BTN_CONTINUOUS, &CBuild2D_OpenCVDlg::OnBnClickedBtnContinuous)
	ON_BN_CLICKED(IDC_BTN_CAM, &CBuild2D_OpenCVDlg::OnBnClickedBtnCam)
	ON_MESSAGE(WM_UPDATE_MESSAGE, OnUpdateMessage)
	ON_BN_CLICKED(IDC_BTN_DIS, &CBuild2D_OpenCVDlg::OnBnClickedBtnDis)
	ON_BN_CLICKED(IDC_CHECK_RECTIFY, &CBuild2D_OpenCVDlg::OnBnClickedCheckRectify)
END_MESSAGE_MAP()


// CBuild2D_OpenCVDlg ��Ϣ�������

BOOL CBuild2D_OpenCVDlg::OnInitDialog()
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
	namedWindow("��Сͼ",WINDOW_AUTOSIZE);  
	HWND hWnd = (HWND)cvGetWindowHandle("��Сͼ");  
	HWND hParent = ::GetParent(hWnd);  
	::SetParent(hWnd,GetDlgItem(IDC_PIC)->m_hWnd);  
	::ShowWindow(hParent,SW_HIDE);  

	UpdateDatas();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CBuild2D_OpenCVDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CBuild2D_OpenCVDlg::OnPaint()
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
HCURSOR CBuild2D_OpenCVDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CBuild2D_OpenCVDlg::OnBnClickedBtnComm()
{
	//���ڿ���
	CString butCStr;
	GetDlgItemTextW(IDC_BTN_COMM, butCStr);
	if(L"��" == butCStr)
	{
		UpdateData(true);
		CString comCStr;
		comCStr.Format(L"COM%d", m_comNum);
		if ( ! com.Open(comCStr, 19200, 0, 0, 0) )
		{
			USES_CONVERSION; 
			CString str;
			str.Format(L"Error: Can't open communication device!\n%s", A2W(com.GetErrorMessage()));
			MessageBox(str);
			return;
		}
		SetDlgItemText(IDCANCEL,L"��");
	}
	else
	{
		com.Close();
		SetDlgItemText(IDCANCEL,L"��");
	}
	UpdateDatas();
}


void CBuild2D_OpenCVDlg::OnBnClickedBtnSend()
{
	UpdateData(TRUE);
	//���͸�����
	CString butCStr;
	GetDlgItemTextW(IDC_BTN_COMM, butCStr);
	if(L"��" == butCStr)
	{
		USES_CONVERSION; 
		char* str = W2A(m_sendCStr);
		int write_result = com.WriteData(str, strlen(str));

		// -1 ? then we got an error and print it
		if ( write_result < 0 )
			MessageBox(A2W(com.GetErrorMessage()));

		//���մ��ڻ�����Ϣ
		int DATA_LEN = 10;
		char buf[255];
		int read_result = com.ReadData(buf, DATA_LEN);

		// -1 ? then we got an error and print it
		if ( (read_result < 0)  )
			MessageBox(A2W(com.GetErrorMessage()));

		// set end of received data
		buf[DATA_LEN] = '\0';

		CString dataRecv =  A2W(buf);
	}
	else
	{
		MessageBox(L"����δ�򿪣�");
	}
}


void CBuild2D_OpenCVDlg::UpdateDatas()
{
	CString butCStr;
	//�ж�ʵʱ״̬
	GetDlgItemTextW(IDC_BTN_CONTINUOUS, butCStr);
	if(L"ʵʱ����" == butCStr)
	{	
		GetDlgItem(IDC_BTN_SINGLE)->EnableWindow(TRUE);	
		GetDlgItem(IDC_BTN_CAM)->EnableWindow(TRUE);		
	}
	else
	{	
		GetDlgItem(IDC_BTN_SINGLE)->EnableWindow(FALSE);	
		GetDlgItem(IDC_BTN_CAM)->EnableWindow(FALSE);	
	}
	//�ж��������״̬
	GetDlgItemTextW(IDC_BTN_CAM, butCStr);
	if(L"��" == butCStr)
	{
		GetDlgItem(IDC_BTN_SINGLE)->EnableWindow(FALSE);	
		GetDlgItem(IDC_BTN_CONTINUOUS)->EnableWindow(FALSE);		
	}
	else
	{	
		GetDlgItem(IDC_BTN_SINGLE)->EnableWindow(TRUE);	
		GetDlgItem(IDC_BTN_CONTINUOUS)->EnableWindow(TRUE);	
	}

	//�жϴ��ڿ���״̬
	GetDlgItemTextW(IDC_BTN_COMM, butCStr);
	if(L"��" == butCStr)
	{
		GetDlgItem(IDC_BTN_SEND)->EnableWindow(FALSE);	
	}
	else
	{
		GetDlgItem(IDC_BTN_SEND)->EnableWindow(TRUE);		
	}
	//����ͼ��ֱ���
	m_pix.Format(L"������ƣ�%d * %d", scr.cols,  scr.rows);
	//�Ƿ���ʾԭͼ

	//��ȡ����ֵ
	CMarkup xml;				//��дxml����
	if (!xml.Load(CMarkup::GetFilePath(L"Setting.xml")))
		MessageBox(L"�Ҳ�����xml�ļ���");
	//��һ��
	xml.ResetPos();
	if(xml.FindChildElem())
	{
		CString para;	
		//�ڶ���
		bool b = xml.FindChildElem(L"Ratio");
		para = xml.GetChildData();
		m_ratio = _ttof(para.GetBuffer());
	}
	GetDlgItem(IDC_EDIT_RATIO)->EnableWindow(false);
	UpdateData(false);	
}

void CBuild2D_OpenCVDlg::OnBnClickedBtnSingle()
{
	//OpenCV��ͼ
	try{
		scr = cam.GetImage();
		imwrite("��ͼ����.bmp", scr);
	}catch(cv::Exception)
	{
		AfxMessageBox(L"�����ͼ�쳣");
		scr = NULL;
	}

	//Halcon��ͼ
	//try{
	//	HObject Hobj = hCam.GetHImage();
	//	scr = HObject2Mat(Hobj);
	//	char a0[256] = "";
	//	CMarkup::GetFilePath(a0, "��ͼ����.bmp");
	//	imwrite(a0, scr);
	//}catch(cv::Exception)
	//{
	//	AfxMessageBox(L"�����ͼ�쳣");
	//	scr = NULL;
	//}

	OnBnClickedCheckRectify();
}

void on_mouse(int event,int x,int y,int flags,void *ustc)//event����¼����ţ�x,y������꣬flags��ק�ͼ��̲����Ĵ���  
{  
	CBuild2D_OpenCVDlg* pThis = (CBuild2D_OpenCVDlg*)ustc;
    static Point cur_pt = (-1,-1);//��Ӧͼʵʱ����
	char temp[16];
	pThis->UpdateData(true);
	
	//��Ӧͼʵʱ����
	cur_pt = Point(x,y);  
	if (event == CV_EVENT_LBUTTONDOWN)//�������
	{  
		if(pThis->m_real)
		{
			//��ʾԭͼ
			pThis->DrawX(pThis->xyScr, cur_pt);					
		}
		else
		{
			//��ʾ��Сͼ
			pThis->DrawX(pThis->xyZoom, cur_pt);
			pThis->ZoomToSrc(pThis->xyZoom, pThis->scr, cur_pt, x, y);		
		}
		pThis->m_sendCStr.Format(L"(%.2f,%.2f)", (x - pThis->scr.cols/2)*pThis->m_ratio, -(y - pThis->scr.rows/2)*pThis->m_ratio);	
		pThis->UpdateData(false);
	}  
	else if (event == CV_EVENT_MOUSEMOVE && !(flags & CV_EVENT_FLAG_LBUTTON))//���û�а��µ����������ƶ��Ĵ�����  
	{  
		if(pThis->m_real)
		{
			//��ʾԭͼ
			pThis->xyScr.copyTo(pThis->realScr); 			

			sprintf(temp,"(%.2f,%.2f)", (x - pThis->scr.cols/2)*pThis->m_ratio, -(y - pThis->scr.rows/2)*pThis->m_ratio);  
			putText(pThis->realScr,temp,cur_pt,FONT_HERSHEY_SIMPLEX,1,Scalar(0,0,255,255));//ֻ��ʵʱ��ʾ����ƶ�������  
			imshow("ԭͼ",pThis->realScr); 
		}
		else
		{
			//��ʾ��Сͼ
			pThis->xyZoom.copyTo(pThis->realZoom);//��xyZoom���Ƶ���ʱͼ��realZoom�ϣ�������ʾʵʱ����     
			pThis->ZoomToSrc(pThis->xyZoom, pThis->scr, cur_pt, x, y);
			sprintf(temp,"(%.2f,%.2f)", (x - pThis->scr.cols/2)*pThis->m_ratio, -(y - pThis->scr.rows/2)*pThis->m_ratio);
			putText(pThis->realZoom,temp,cur_pt,FONT_HERSHEY_SIMPLEX,1,Scalar(0,0,255,255));//ֻ��ʵʱ��ʾ����ƶ�������  
			imshow("��Сͼ",pThis->realZoom);  
		}

	}  
	else if (event == CV_EVENT_LBUTTONUP)//����ɿ�
	{   
		//ʹ��ԭͼ����
		if(!pThis->m_real)
		{
			pThis->ZoomToSrc(pThis->xyZoom, pThis->scr, cur_pt, x, y);
		}
		CString butCStr;	
		pThis->GetDlgItemTextW(IDC_BTN_A, butCStr);
		if(L"ѡ��A��" == butCStr)
		{
			pThis->m_A.x = x;
			pThis->m_A.y = y;
			butCStr.Format(L"A(%d, %d)", x, y);
			pThis->SetDlgItemText(IDC_BTN_A, butCStr);
		}

		pThis->GetDlgItemTextW(IDC_BTN_B, butCStr);
		if(L"ѡ��B��" == butCStr)
		{
			pThis->m_B.x = x;
			pThis->m_B.y = y;
			butCStr.Format(L"B(%d, %d)", x, y);
			pThis->SetDlgItemText(IDC_BTN_B, butCStr);
		}
	}  
}  

void CBuild2D_OpenCVDlg::OnBnClickedBtnPic()
{
	CString picPath;   //����ͼƬ·������    
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY |   
		OFN_OVERWRITEPROMPT|OFN_ALLOWMULTISELECT,   NULL, this);   //ѡ���ļ��Ի���    

	if(dlg.DoModal() == IDOK)    
	{    
		picPath= dlg.GetPathName();  //��ȡͼƬ·��    
	}    
	//CString to string  
	USES_CONVERSION; 
	string picpath = W2A(picPath);      

	scr = imread(picpath);        

	OnBnClickedCheckRectify();
}


void CBuild2D_OpenCVDlg::OnCancel()
{
	CString butCStr;
	//�رմ���
	GetDlgItemTextW(IDCANCEL, butCStr);
	if(L"��" == butCStr)
	{
		OnBnClickedBtnComm();
	}
	//�ر����
	GetDlgItemTextW(IDC_BTN_CAM, butCStr);
	if(L"��" == butCStr)
	{
		OnBnClickedBtnCam();
	}
	Sleep(DELAY_REAL);
	//�˳�����
	exit(0);
	CDialogEx::OnCancel();
}


void CBuild2D_OpenCVDlg::OnBnClickedBtnA()
{
	//A��
	CString butCStr;
	GetDlgItemTextW(IDC_BTN_A, butCStr);
	if(L"ѡ��A��" != butCStr)
	{
		SetDlgItemText(IDC_BTN_A,L"ѡ��A��");
	}
	else
	{
		MessageBox(L"��ѡ��A�㣡");
	}
}


void CBuild2D_OpenCVDlg::OnBnClickedBtnB()
{
	//B��
	CString butCStr;
	GetDlgItemTextW(IDC_BTN_B, butCStr);
	if(L"ѡ��A��" != butCStr)
	{
		SetDlgItemText(IDC_BTN_B,L"ѡ��B��");
	}
	else
	{
		MessageBox(L"��ѡ��B�㣡");
	}
}


void CBuild2D_OpenCVDlg::OnBnClickedBtnRatio()
{
	//�������
	UpdateData(true);
	double a = (m_A.x-m_B.x)*(m_A.x-m_B.x) + (m_A.y-m_B.y)*(m_A.y-m_B.y);
	m_ratio = m_ABdis/sqrt(a);

	//�������ֵ
	CMarkup xml;				//��дxml����
	if (!xml.Load(CMarkup::GetFilePath(L"Setting.xml")))
		MessageBox(L"�Ҳ�����xml�ļ���");
	//��һ��
	xml.ResetPos();
	if(xml.FindChildElem())
	{
		CString para;	
		//�ڶ���
		bool b = xml.FindChildElem(L"Ratio");
		para.Format(L"%f", m_ratio);
		xml.SetChildData(para);
		if(!xml.Save(CMarkup::GetFilePath(L"Setting.xml"))){
			MessageBox(L"�������ֵʧ�ܣ�");
		}
	}
	UpdateDatas();
}

void CBuild2D_OpenCVDlg::OnBnClickedBtnContinuous()
{
	//����
	CString butCStr;
	GetDlgItemTextW(IDC_BTN_CONTINUOUS, butCStr);
	if(L"ʵʱ����" == butCStr)
	{
		CreateThread(NULL,0,ThreadReal,this,0,NULL);
		SetDlgItemText(IDC_BTN_CONTINUOUS, L"ʵʱ����");
	}
	else
	{
		SetDlgItemText(IDC_BTN_CONTINUOUS, L"ʵʱ����");
	}
}


void CBuild2D_OpenCVDlg::OnBnClickedBtnCam()
{
	//�������
	CString butCStr;
	GetDlgItemTextW(IDC_BTN_CAM, butCStr);
	if(L"��" == butCStr)
	{
		//OpenCV���
		if(cam.OpenCam(0))
		{
			SetDlgItemText(IDC_BTN_CAM, L"��");				
		}
		//Halcon���
		//if(hCam.OpenCamera(""))
		//{
		//	SetDlgItemText(IDC_BTN_CAM, L"��");	
		//}
	}
	else
	{
		//OpenCV���
		cam.CloseCam();
		//Halcon���
		//hCam.CloseCamera();
		SetDlgItemText(IDC_BTN_CAM, L"��");			
	}
	UpdateDatas();
}


LRESULT CBuild2D_OpenCVDlg::OnUpdateMessage(WPARAM wParam, LPARAM lParam)
{
	//�߳�֪ͨ�������
	OnBnClickedBtnSingle();
	return 0;
}

void CBuild2D_OpenCVDlg::OnBnClickedBtnDis()
{
	//����AB����mm��
	UpdateData(true);
	CString butCStr;
	double a = (m_A.x-m_B.x)*(m_A.x-m_B.x) + (m_A.y-m_B.y)*(m_A.y-m_B.y);
	double dis = m_ratio*sqrt(a);
	butCStr.Format(L"����AB����mm��%.2f", dis);
	SetDlgItemText(IDC_BTN_DIS, butCStr);		
}

void CBuild2D_OpenCVDlg::DrawX(Mat &image, Point point)
{
	//�滭ĳ���־
	int size = 5;
	line(image,Point(point.x - size, point.y - size),cvPoint(point.x + size, point.y + size),CV_RGB(0,255,255),2,CV_AA,0);  
    line(image,Point(point.x + size, point.y - size),cvPoint(point.x - size, point.y + size),CV_RGB(0,255,255),2,CV_AA,0);  
}

void CBuild2D_OpenCVDlg::Rectify(Mat &scr, Mat &dst, CString xmlPath)
{
	//ͼ��������
	//�ڲξ���, ���㸴�ƴ��룬Ҳ��Ҫ���ҵĲ���������ͷ����һ��...
	Mat cameraMatrix = Mat::eye(3, 3, CV_64F);
	//�����������Ҫ���ҵĲ���~
    Mat distCoeffs = Mat::zeros(5, 1, CV_64F);

	CMarkup xml;				//��дxml����
	if (!xml.Load(CMarkup::GetFilePath(xmlPath)))
		MessageBox(L"�Ҳ�����xml�ļ���");
	
	//��һ��
	xml.ResetPos();
	if(xml.FindChildElem())
	{
		CString para;	
		//�ڶ���
		bool b = xml.FindChildElem(L"CameraMatrix");
		xml.IntoElem();

		{				
			xml.FindChildElem(L"Mat00");
			para = xml.GetChildData();
			cameraMatrix.at<double>(0, 0) = _ttof(para.GetBuffer());
			xml.FindChildElem(L"Mat01");
			para = xml.GetChildData();
			cameraMatrix.at<double>(0, 1) = _ttof(para.GetBuffer());
			xml.FindChildElem(L"Mat02");
			para = xml.GetChildData();
			cameraMatrix.at<double>(0, 2) = _ttof(para.GetBuffer());

			xml.FindChildElem(L"Mat10");
			para = xml.GetChildData();
			cameraMatrix.at<double>(1, 0) = _ttof(para.GetBuffer());
			xml.FindChildElem(L"Mat11");
			para = xml.GetChildData();
			cameraMatrix.at<double>(1, 1) = _ttof(para.GetBuffer());
			xml.FindChildElem(L"Mat12");
			para = xml.GetChildData();
			cameraMatrix.at<double>(1, 2) = _ttof(para.GetBuffer());

			xml.FindChildElem(L"Mat20");
			para = xml.GetChildData();
			cameraMatrix.at<double>(2, 0) = _ttof(para.GetBuffer());
			xml.FindChildElem(L"Mat21");
			para = xml.GetChildData();
			cameraMatrix.at<double>(2, 1) = _ttof(para.GetBuffer());
			xml.FindChildElem(L"Mat22");
			para = xml.GetChildData();
			cameraMatrix.at<double>(2, 2) = _ttof(para.GetBuffer());
		}

		//�ڶ���
		xml.OutOfElem();
		//������
		bool bb = xml.FindChildElem(L"DistCoeffs");
		xml.IntoElem();

		{
			xml.FindChildElem(L"Mat0");
			para = xml.GetChildData();
			distCoeffs.at<double>(0, 0) = _ttof(para.GetBuffer());

			xml.FindChildElem(L"Mat1");
			para = xml.GetChildData();
			distCoeffs.at<double>(1, 0) = _ttof(para.GetBuffer());


			xml.FindChildElem(L"Mat2");
			para = xml.GetChildData();
			distCoeffs.at<double>(2, 0) = _ttof(para.GetBuffer());

			xml.FindChildElem(L"Mat3");
			para = xml.GetChildData();
			distCoeffs.at<double>(3, 0) = _ttof(para.GetBuffer());

			xml.FindChildElem(L"Mat4");
			para = xml.GetChildData();
			distCoeffs.at<double>(4, 0) = _ttof(para.GetBuffer());
		}
	}

    Mat view, rview, map1, map2;
	Mat R = Mat::eye(3,3,CV_32F);  
    Size imageSize;
    imageSize = scr.size();
    initUndistortRectifyMap(cameraMatrix, distCoeffs, R, cameraMatrix, imageSize, CV_16SC2, map1, map2);
    remap(scr, dst, map1, map2, INTER_LINEAR);
}


void CBuild2D_OpenCVDlg::OnBnClickedCheckRectify()
{
	//1���Ƿ�������
	UpdateData(true);
	if(m_isRectify)
	{
		Rectify(scr, rectifyScr, L"Setting.xml");
		char a0[256] = "";
		CMarkup::GetFilePath(a0, "������.bmp");
		imwrite(a0, rectifyScr);
	}
	else
	{
		scr.copyTo(rectifyScr);
	}
	OnBnClickedCheckReal();
}

void CBuild2D_OpenCVDlg::OnBnClickedCheckReal()
{
	//2���Ƿ���ʾԭͼ
	UpdateData(true);
	if(m_real)
	{			
		namedWindow("ԭͼ");  		
		rectifyScr.copyTo(xyScr); 
		imshow("ԭͼ",xyScr); 
		setMouseCallback("ԭͼ",on_mouse,this);  
	}
	else
	{
		destroyWindow("ԭͼ");
		//���²�����ȡͼ�οؼ��ߴ粢�Դ˸ı�ͼƬ�ߴ�    
		CRect rect;    
		GetDlgItem(IDC_PIC)->GetClientRect(&rect);    
		Rect dst(rect.left,rect.top,rect.right,rect.bottom);    
		resize(rectifyScr,zoom,cv::Size(rect.Width(),rect.Height()));     
		setMouseCallback("��Сͼ",on_mouse,this);  
		zoom.copyTo(xyZoom);  
	}
	OnBnClickedCheckXy();
}

void CBuild2D_OpenCVDlg::OnBnClickedCheckXy()
{
	//3���Ƿ���ʾ����ϵ
	UpdateData(true);
	if(m_real)
	{
		if(m_xy)
		{
			line(xyScr,Point(0,xyScr.rows/2),Point(scr.cols,xyScr.rows/2),Scalar(0,255,0),1,CV_AA);  
			line(xyScr,Point(xyScr.cols/2,0),Point(scr.cols/2,xyScr.rows),Scalar(0,255,0),1,CV_AA);	
			xyScr.copyTo(realScr); 
		}
		else
		{
			rectifyScr.copyTo(xyScr);  
			xyScr.copyTo(realScr);		
		}
		imshow("ԭͼ",xyScr);  
	}
	else
	{
		if(m_xy)
		{
			line(xyZoom,Point(0,xyZoom.rows/2),Point(xyZoom.cols,xyZoom.rows/2),Scalar(0,255,0),1,CV_AA);  
			line(xyZoom,Point(xyZoom.cols/2,0),Point(xyZoom.cols/2,xyZoom.rows),Scalar(0,255,0),1,CV_AA);
			xyZoom.copyTo(realZoom); 
		}
		else
		{
			zoom.copyTo(xyZoom);  
			xyZoom.copyTo(realZoom);		
		}
		imshow("��Сͼ",xyZoom);  
	}
	UpdateDatas();
}

void CBuild2D_OpenCVDlg::ZoomToSrc(Mat &zoom, Mat &scr, Point zoomP, int &x, int &y)
{
	//��Сͼ������תԭͼ������
	double cols = (double)zoom.cols/scr.cols;
	double rows = (double)zoom.rows/scr.rows;

	x = zoomP.x/cols;
	y = zoomP.y/rows;
}

//Mat CBuild2D_OpenCVDlg::HObject2Mat(HObject Hobj)  
//{  
//    HTuple htCh=HTuple();  
//    HTuple cType;  
//    Mat Image;  
//    ConvertImageType(Hobj,&Hobj,"byte");  
//    CountChannels(Hobj,&htCh);  
//    HTuple wid;  
//    HTuple hgt;  
//    int W,H;  
//    if(htCh[0].I()==1)  
//    {  
//        HTuple ptr;  
//        GetImagePointer1(Hobj,&ptr,&cType,&wid,&hgt);  
//        W=(Hlong)wid;  
//        H=(Hlong)hgt;  
//        Image.create(H,W,CV_8UC1);  
//        uchar* pdata=(uchar*)ptr[0].I();  
//        memcpy(Image.data,pdata,W*H);  
//    }  
//    else if(htCh[0].I()==3)  
//    {  
//        HTuple ptrR, ptrG, ptrB;  
//        GetImagePointer3(Hobj,&ptrR,&ptrG,&ptrB,&cType,&wid,&hgt);  
//        W=(Hlong)wid;  
//        H=(Hlong)hgt;  
//        Image.create(H,W,CV_8UC3);  
//        vector<Mat> vecM(3);  
//        vecM[2].create(H,W,CV_8UC1);  
//        vecM[1].create(H,W,CV_8UC1);  
//        vecM[0].create(H,W,CV_8UC1);  
//        uchar* pr=(uchar*)ptrR[0].I();  
//        uchar* pg=(uchar*)ptrG[0].I();  
//        uchar* pb=(uchar*)ptrB[0].I();  
//        memcpy(vecM[2].data,pr,W*H);  
//        memcpy(vecM[1].data,pg,W*H);  
//        memcpy(vecM[0].data,pb,W*H);  
//        merge(vecM,Image);  
//    }  
//    return Image;  
//}  
