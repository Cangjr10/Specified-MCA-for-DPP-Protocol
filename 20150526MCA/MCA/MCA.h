
// MCA.h : MCA Ӧ�ó������ͷ�ļ�
//
#pragma once
#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������
 #include "ROIManaging.h"

// CMCAApp:
// �йش����ʵ�֣������ MCA.cpp
//

class CMCAApp : public CWinApp
{
public:
	CMCAApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	
// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
//	CMscomm m_SCIModule;
	afx_msg void OnMcaConnect();
	afx_msg void OnStart();
//	afx_msg void OnDefineROI();
private:
	CROIManaging* m_pROIManageDlg;
public:
	/*afx_msg void OnDefineROI();*/
	afx_msg void OnDefineroi();
};

extern CMCAApp theApp;
