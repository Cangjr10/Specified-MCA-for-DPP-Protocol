#pragma once
#include "afxwin.h"
#include "MainFrm.h"
#include "stdafx.h"
// CCommunicationPortDlg 对话框

class CCommunicationPortDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCommunicationPortDlg)

public:
	CCommunicationPortDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCommunicationPortDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_PROTOCOL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedConnect();
	int m_nCommDlg;
	int m_nBaudrateDlg;
	UINT m_nTimeRequestDlg;
	bool m_RS232;
	CComboBox m_CommDlg;
	CComboBox m_BaudDlg;
	virtual BOOL OnInitDialog();
private:
	vector<CString> str_baudrate ;//保存波特率
	BOOL m_nPortFlag;
	CMainFrame* pFrame;
public:
	afx_msg void OnBnClickedButtonSetdefaulttime();
	afx_msg void OnBnClickedButtonOpenport();
	afx_msg void OnBnClickedButtonFinddevice();
	CEdit m_DeviceInfo;
	afx_msg void OnBnClickedCancel();
};
