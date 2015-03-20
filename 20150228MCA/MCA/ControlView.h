#pragma once
#include "afxcmn.h"
#include "afxwin.h"

// CControlView ������ͼ

class CControlView : public CFormView
{
	DECLARE_DYNCREATE(CControlView)

protected:
	CControlView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CControlView();

public:
	enum { IDD = IDD_DIALOG_CONTROL };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
private:
	//CTreeCtrl m_TreeCtr;
	HTREEITEM MarkTreeItemNum[18];
public:
	CString m_nDeviceID;
	CString m_nDeviceType;
	CString m_nMonitorObject;
	double m_nLongitude;
	double m_nLatitude;
	short m_ntemperature;
	short m_nHumidity;
	short m_nHV;
	CComboBox m_SpectrumChannel;
	vector<CString> Str_ChannelNumber ;//���沨����
	double m_nPickInterval;
	CString m_nStartTime;
	CString m_nCurrentTime;
	int m_nChannemNumber;

	afx_msg void OnCbnSelendokChannelnumber();
	UINT m_nAccTime;
	UINT m_nLiveTime;
	float m_nActivity_Cs137;
};


