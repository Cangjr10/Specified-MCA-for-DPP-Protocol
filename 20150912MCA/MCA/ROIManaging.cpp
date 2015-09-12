// ROIManaging.cpp : 实现文件
//

#include "stdafx.h"
#include "MCA.h"
#include "ROIManaging.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "MCADoc.h"

// CROIManaging 对话框

IMPLEMENT_DYNAMIC(CROIManaging, CDialogEx)

CROIManaging::CROIManaging(CWnd* pParent /*=NULL*/)
	: CDialogEx(CROIManaging::IDD, pParent)
	, m_nROIStart(0)
	, m_nROIEnd(0)
{

}

CROIManaging::~CROIManaging()
{
}

void CROIManaging::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ROI_START, m_nROIStart);
	DDX_Text(pDX, IDC_ROI_END, m_nROIEnd);
	DDX_Control(pDX, IDC_ROI_LIST, m_ROIList);
}


BEGIN_MESSAGE_MAP(CROIManaging, CDialogEx)
	ON_BN_CLICKED(IDC_ROI_ADD, &CROIManaging::OnBnClickedRoiAdd)
	ON_BN_CLICKED(IDC_ROI_REMOVE, &CROIManaging::OnBnClickedRoiRemove)
	ON_LBN_SELCHANGE(IDC_ROI_LIST, &CROIManaging::OnSelchangeROIList)
	ON_BN_CLICKED(IDC_ROI_REPLACE, &CROIManaging::OnBnClickedRoiReplace)
	ON_BN_CLICKED(IDC_ROI_REMOVEALL, &CROIManaging::OnBnClickedRoiRemoveall)
END_MESSAGE_MAP()


// CROIManaging 消息处理程序


void CROIManaging::OnBnClickedRoiAdd()
{
try{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMCADoc* pDoc = (CMCADoc*)pFrame->GetActiveDocument();
	CDetailView* pDetailViewTemp = (CDetailView*) pFrame->pDetailView;
	UpdateData(TRUE);
	if (m_nROIEnd > m_nROIStart && m_nROIStart >= 0 && m_nROIEnd < pDoc->GetActiveSpectrum().GetSpectrumSize())
	{
		CString str;
		str.Format(_T("%10.lf %10.lf"),m_nROIStart,m_nROIEnd);
		if (m_ROIList.FindStringExact(-1,str)!=LB_ERR)
		{
			MessageBox(_T("ROI已存在！"));
		}
		else
		{
			CROI ROI_temp((UINT)m_nROIStart,(UINT)m_nROIEnd);
			pDoc->GetActiveSpectrum().AddROI(ROI_temp);
			int nIndex = m_ROIList.AddString(str);
			pDoc->GetActiveSpectrum().SetSelectedROIIndex(nIndex);
			pDoc->UpdateAllViews(NULL);
		}
		UpdateData(FALSE);
	}
	else
		AfxMessageBox(_T("Inavalid ROI!"));
}
catch (...)
{
	AfxMessageBox(_T("CROIManaging::OnBnClickedRoiAdd！"));
}
}


void CROIManaging::OnBnClickedRoiRemove()
{
try{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMCADoc* pDoc = (CMCADoc*)pFrame->GetActiveDocument();
	CDetailView* pDetailViewTemp = (CDetailView*) pFrame->pDetailView;
	int nIndex = m_ROIList.GetCurSel();
	if (nIndex != LB_ERR)
	{
		pDoc->GetActiveSpectrum().DeleteROI(nIndex);
		m_ROIList.DeleteString(nIndex);
		pDoc->UpdateAllViews(NULL);
	}
	else
		MessageBox(_T("没有选择列表框活列表框操作失败！"));
}
catch (...)
{
	AfxMessageBox(_T("CROIManaging::OnBnClickedRoiRemove！"));
}
}


void CROIManaging::OnSelchangeROIList()
{
try{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMCADoc* pDoc = (CMCADoc*)pFrame->GetActiveDocument();
	CDetailView* pDetailViewTemp = (CDetailView*) pFrame->pDetailView;
	int nIndex = m_ROIList.GetCurSel();
	if (nIndex != LB_ERR)
	{
		CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
		CMCADoc* pDoc = (CMCADoc*)pFrame->GetActiveDocument();
		m_nROIStart = pDoc->GetActiveSpectrum().GetSpectrumROI(nIndex).GetROIStart();
		m_nROIEnd = pDoc->GetActiveSpectrum().GetSpectrumROI(nIndex).GetROIEnd();
		pDoc->GetActiveSpectrum().SetSelectedROIIndex(nIndex);
		UpdateData(FALSE);
		pDetailViewTemp->Invalidate(FALSE);
	}
}
catch (...)
{
	AfxMessageBox(_T("CROIManaging::OnSelchangeROIList！"));

}
}


void CROIManaging::OnBnClickedRoiReplace()
{
try{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedRoiRemove();
	UpdateData(TRUE);
	OnBnClickedRoiAdd();
}
catch (...)
{
	AfxMessageBox(_T("CROIManaging::OnBnClickedRoiReplace！"));
}
}


void CROIManaging::OnBnClickedRoiRemoveall()
{
try{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMCADoc* pDoc = (CMCADoc*)pFrame->GetActiveDocument();
	CDetailView* pDetailViewTemp = (CDetailView*) pFrame->pDetailView;
	pDoc->GetActiveSpectrum().ClearAllROI();
	for (int nIndex = m_ROIList.GetCount()-1;nIndex>=0;nIndex--)
		m_ROIList.DeleteString(nIndex);
	UpdateData(FALSE);
	pDoc->UpdateAllViews(NULL);
}
catch (...)
{
	AfxMessageBox(_T("CROIManaging::OnBnClickedRoiRemoveall！"));
}
}


BOOL CROIManaging::OnInitDialog()
{
try{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMCADoc* pDoc = (CMCADoc*)pFrame->GetActiveDocument();
	UINT ROI_Number = pDoc->GetActiveSpectrum().GetROINumber();
	CString str;
	for (UINT index = 0; index < ROI_Number;index++)
	{
		CROI ROI0(pDoc->GetActiveSpectrum().GetSpectrumROI(index).GetROIStart(),pDoc->GetActiveSpectrum().GetSpectrumROI(index).GetROIEnd());
		str.Format(_T("%10.lf %10.lf"),(double)ROI0.GetROIStart(),(double)ROI0.GetROIEnd());
		if (m_ROIList.FindStringExact(-1,str)!=LB_ERR)
		{
			//MessageBox(_T("ROI已存在！"));
		}
		else
		{
			int nIndex = m_ROIList.AddString(str);
			pDoc->GetActiveSpectrum().SetSelectedROIIndex(nIndex);
		}
		UpdateData(FALSE);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
}
catch (...)
{
	AfxMessageBox(_T("CROIManaging::OnInitDialog！"));
}
return TRUE;
	// 异常: OCX 属性页应返回 FALSE
}
