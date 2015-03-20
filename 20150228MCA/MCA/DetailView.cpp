// DetailView.cpp : 实现文件
//

#include "stdafx.h"
#include "MCA.h"
#include "DetailView.h"
#include "UserPlot.h"
#include "MCADoc.h"
// CDetailView

IMPLEMENT_DYNCREATE(CDetailView, CView)

CDetailView::CDetailView()
{

}

CDetailView::~CDetailView()
{
}

BEGIN_MESSAGE_MAP(CDetailView, CView)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CDetailView 绘图

void CDetailView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 在此添加绘制代码
	CMCADoc* pMCADoc = (CMCADoc*) m_pDocument;
	CSpectrum Spectra;
	pMCADoc->GetActiveSpectrumCopy(Spectra);
	UINT index_ROI = 0;
	if (Spectra.GetROINumber() >0 && Spectra.GetSelectedROIIndex(index_ROI))//正确获取ROI
	{
		UINT32 ROI_MAX = Spectra.GetROIMax(index_ROI);
		UINT32 ROI_MIN = Spectra.GetROIMin(index_ROI);
		UserPlot_Detail.SetAxis(Spectra.GetSpectrumROI(index_ROI).GetROIStart(),Spectra.GetSpectrumROI(index_ROI).GetROIEnd(),ROI_MIN,ROI_MAX);
		UserPlot_Detail.BarSpectrum(pDC,Spectra,RGB(251,249,236),RGB(0,0,255),RGB(0,0,255));
		UserPlot_Detail.DrawVerticleLine(pDC,UserPlot_Detail.GetCursorPosition());
	}
	else
	{
		CSpectrum _Spectra_temp;
		UserPlot_Detail.SetAxis(0,2047,0,256);
		UserPlot_Detail.BarSpectrum(pDC,_Spectra_temp,RGB(251,249,236),RGB(0,0,255),RGB(28,62,140));
		UserPlot_Detail.DrawVerticleLine(pDC,UserPlot_Detail.GetCursorPosition());
	}	
	UINT ShowData = UserPlot_Detail.GetCursorPosition();
	CString str = _T("");
	if (ShowData < pMCADoc->GetActiveSpectrum().GetSpectrumSize())
		str.Format(_T("能量%.1f,计数%d"),pMCADoc->GetActiveSpectrum().GetEnergy(ShowData),pMCADoc->GetActiveSpectrum().GetElement(ShowData));
	CRect rect;
	GetClientRect(&rect);
	CRect rect_text(rect.right-300,rect.top,rect.right-10,rect.top+20);
	pDC->FillSolidRect(rect_text,RGB(251,249,236));
	pDC->DrawText(str,rect_text,DT_RIGHT|DT_SINGLELINE|DT_VCENTER);
	
}


// CDetailView 诊断

#ifdef _DEBUG
void CDetailView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CDetailView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDetailView 消息处理程序


void CDetailView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	UserPlot_Detail.GetWnd(this); 
	m_nLButtonDown = FALSE;
	// TODO: 在此添加专用代码和/或调用基类
}


BOOL CDetailView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//return CView::OnEraseBkgnd(pDC);
	return TRUE;
}


void CDetailView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CMCADoc* pMCADoc = (CMCADoc*) m_pDocument;
	CClientDC dc(this);
	UserPlot_Detail.SetUserView(&dc);
	double x = UserPlot_Detail.WindowsXToAxis(point.x);
	double y = UserPlot_Detail.WindowsYToAxis(point.y);
	UserPlot_Detail.DrawVerticleLine(&dc,x);
	m_nLButtonDown = TRUE;
	UINT ShowData = UserPlot_Detail.GetCursorPosition();
	UserPlot_Detail.SetDefaultView(&dc);
	CString str = _T("");
	if (ShowData < pMCADoc->GetActiveSpectrum().GetSpectrumSize())
		str.Format(_T("能量%.1f,计数%d"),pMCADoc->GetActiveSpectrum().GetEnergy(ShowData),pMCADoc->GetActiveSpectrum().GetElement(ShowData));
	CRect rect;
	GetClientRect(&rect);
	CRect rect_text(rect.right-300,rect.top,rect.right-10,rect.top+20);
	dc.FillSolidRect(rect_text,RGB(251,249,236));
	dc.DrawText(str,rect_text,DT_RIGHT|DT_SINGLELINE|DT_VCENTER);
	CView::OnLButtonDown(nFlags, point);
}


void CDetailView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_nLButtonDown = FALSE;
	CView::OnLButtonUp(nFlags, point);
}


void CDetailView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CMCADoc* pMCADoc = (CMCADoc*) m_pDocument;
	if (m_nLButtonDown)
	{
		CClientDC dc(this);
		UserPlot_Detail.SetUserView(&dc);
		double x = UserPlot_Detail.WindowsXToAxis(point.x);
		double y = UserPlot_Detail.WindowsYToAxis(point.y);
		UserPlot_Detail.DrawVerticleLine(&dc,x);
		m_nLButtonDown = TRUE;
		UINT ShowData = UserPlot_Detail.GetCursorPosition();
		UserPlot_Detail.SetDefaultView(&dc);
		CString str = _T("");
		if (ShowData < pMCADoc->GetActiveSpectrum().GetSpectrumSize())
			str.Format(_T("能量%.1f,计数%d"),pMCADoc->GetActiveSpectrum().GetEnergy(ShowData),pMCADoc->GetActiveSpectrum().GetElement(ShowData));
		CRect rect;
		GetClientRect(&rect);
		CRect rect_text(rect.right-300,rect.top,rect.right-10,rect.top+20);
		dc.FillSolidRect(rect_text,RGB(251,249,236));
		dc.DrawText(str,rect_text,DT_RIGHT|DT_SINGLELINE|DT_VCENTER);
	}
	CView::OnMouseMove(nFlags, point);
}


BOOL CDetailView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	CMCADoc* pMCADoc = (CMCADoc*) m_pDocument;
	CClientDC dc(this);
	UserPlot_Detail.SetUserView(&dc);
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_LEFT:
			{
				UserPlot_Detail.DrawVerticleLine(&dc,UserPlot_Detail.GetCursorPosition()-1);
				UINT ShowData = UserPlot_Detail.GetCursorPosition();
				UserPlot_Detail.SetDefaultView(&dc);
				CString str = _T("");
				if (ShowData < pMCADoc->GetActiveSpectrum().GetSpectrumSize())
					str.Format(_T("能量%.1f,计数%d"),pMCADoc->GetActiveSpectrum().GetEnergy(ShowData),pMCADoc->GetActiveSpectrum().GetElement(ShowData));
				CRect rect;
				GetClientRect(&rect);
				CRect rect_text(rect.right-300,rect.top,rect.right-10,rect.top+20);
				dc.FillSolidRect(rect_text,RGB(251,249,236));
				dc.DrawText(str,rect_text,DT_RIGHT|DT_SINGLELINE|DT_VCENTER);
			}
			break;
		case VK_RIGHT:
			{
				UserPlot_Detail.DrawVerticleLine(&dc,UserPlot_Detail.GetCursorPosition()+1);
				UINT ShowData = UserPlot_Detail.GetCursorPosition();
				UserPlot_Detail.SetDefaultView(&dc);
				CString str = _T("");
				if (ShowData < pMCADoc->GetActiveSpectrum().GetSpectrumSize())
					str.Format(_T("能量%.1f,计数%d"),pMCADoc->GetActiveSpectrum().GetEnergy(ShowData),pMCADoc->GetActiveSpectrum().GetElement(ShowData));
				CRect rect;
				GetClientRect(&rect);
				CRect rect_text(rect.right-300,rect.top,rect.right-10,rect.top+20);
				dc.FillSolidRect(rect_text,RGB(251,249,236));
				dc.DrawText(str,rect_text,DT_RIGHT|DT_SINGLELINE|DT_VCENTER);
			}
			break;
		default:
			break;
		}
	}
	return CView::PreTranslateMessage(pMsg);
}
