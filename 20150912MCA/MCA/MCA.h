
// MCA.h : MCA 应用程序的主头文件
//
#pragma once
#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号
 #include "ROIManaging.h"

// CMCAApp:
// 有关此类的实现，请参阅 MCA.cpp
//

class CMCAApp : public CWinApp
{
public:
	CMCAApp();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	
// 实现
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
