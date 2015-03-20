#pragma once
#include "afxwin.h"


// CROIManaging �Ի���

class CROIManaging : public CDialogEx
{
	DECLARE_DYNAMIC(CROIManaging)

public:
	CROIManaging(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CROIManaging();

// �Ի�������
	enum { IDD = IDD_ROI };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRoiAdd();
	double m_nROIStart;
	double m_nROIEnd;
	CListBox m_ROIList;
	afx_msg void OnBnClickedRoiRemove();
	afx_msg void OnSelchangeROIList();
	afx_msg void OnBnClickedRoiReplace();
	afx_msg void OnBnClickedRoiRemoveall();
	virtual BOOL OnInitDialog();
};
