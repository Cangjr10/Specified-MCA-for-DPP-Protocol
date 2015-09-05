// TotalView.cpp : 实现文件
//

#include "stdafx.h"
#include "MCA.h"
#include "TotalView.h"
#include "MCADoc.h"
// CTotalView

IMPLEMENT_DYNCREATE(CTotalView, CView)

CTotalView::CTotalView()
{

}

CTotalView::~CTotalView()
{
}

BEGIN_MESSAGE_MAP(CTotalView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CTotalView 绘图

void CTotalView::OnDraw(CDC* pDC)
{
try{
	CDocument* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: 在此添加绘制代码
	//读取谱数据文件,用于谱的显示和处理
	CMCADoc* pMCADoc = (CMCADoc*) m_pDocument;
	//UserPlot_Total.plotlinetest();
	CSpectrum Spectra;
	pMCADoc->GetActiveSpectrumCopy(Spectra);
	if (Spectra.GetSpectrumSize()==0)
	{
		UserPlot_Total.SetAxis(0,2047,0,256);
		UserPlot_Total.BarSpectrum(pDC,Spectra,RGB(251,249,236),RGB(28,62,140),RGB(28,62,140));
		UserPlot_Total.DrawVerticleLine(pDC,UserPlot_Total.GetCursorPosition());
	}
	if (Spectra.GetSpectrumSize()>0)
	{
		UserPlot_Total.SetAxis(0,Spectra.GetSpectrumSize()-1,0,Spectra.GetSpectrumMax());
		UserPlot_Total.BarSpectrum(pDC,Spectra,RGB(251,249,236),RGB(236,18,13),RGB(0,0,255));//RGB(28,62,140)
		UserPlot_Total.DrawVerticleLine(pDC,UserPlot_Total.GetCursorPosition());
	}
	UINT ShowData = UserPlot_Total.GetCursorPosition();
	CString str = _T("");
	if (ShowData < pMCADoc->GetActiveSpectrum().GetSpectrumSize())
		str.Format(_T("能量%.1f,计数%d"),pMCADoc->GetActiveSpectrum().GetEnergy(ShowData),pMCADoc->GetActiveSpectrum().GetElement(ShowData));
	CRect rect;
	GetClientRect(&rect);
	CRect rect_text(rect.right-300,rect.top,rect.right-10,rect.top+20);
	pDC->FillSolidRect(rect_text,RGB(251,249,236));
	pDC->DrawText(str,rect_text,DT_RIGHT|DT_SINGLELINE|DT_VCENTER);
}
catch(...)
{
	AfxMessageBox(_T("TOTAL VIEW ERROR！"));
}
}


// CTotalView 诊断

#ifdef _DEBUG
void CTotalView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CTotalView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTotalView 消息处理程序

void CTotalView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CMCADoc* pMCADoc = (CMCADoc*) m_pDocument;
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CDetailView* pDetailViewtemp = (CDetailView*)pFrame->pDetailView;
	CClientDC dc(this);
	UserPlot_Total.SetUserView(&dc);
	double x = UserPlot_Total.WindowsXToAxis(point.x);
	double y = UserPlot_Total.WindowsYToAxis(point.y);
	UserPlot_Total.DrawVerticleLine(&dc,x);
	m_nLButtonDown = TRUE;
	UINT ShowData = UserPlot_Total.GetCursorPosition();
	UserPlot_Total.SetDefaultView(&dc);
	CString str = _T("");
	if (ShowData < pMCADoc->GetActiveSpectrum().GetSpectrumSize())
		str.Format(_T("能量%.1f,计数%d"),pMCADoc->GetActiveSpectrum().GetEnergy(ShowData),pMCADoc->GetActiveSpectrum().GetElement(ShowData));
	CRect rect;
	GetClientRect(&rect);
	CRect rect_text(rect.right-300,rect.top,rect.right-10,rect.top+20);
	dc.FillSolidRect(rect_text,RGB(251,249,236));
	dc.DrawText(str,rect_text,DT_RIGHT|DT_SINGLELINE|DT_VCENTER);
	CSpectrum& spectrum = pMCADoc->GetActiveSpectrum();
	UINT ROINumber = spectrum.GetROINumber();
	for (UINT i = 0;i<ROINumber;i++)
	{
		if (ShowData>spectrum.GetSpectrumROI(i).GetROIStart() && ShowData < spectrum.GetSpectrumROI(i).GetROIEnd())
		{
			spectrum.SetSelectedROIIndex(i);
			pDetailViewtemp->Invalidate(FALSE);
		}
	}
	CView::OnLButtonDown(nFlags, point);
}


void CTotalView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_nLButtonDown = FALSE;
	CView::OnLButtonUp(nFlags, point);
}


void CTotalView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	static BOOL ROI_LeftFlag = FALSE;
	static UINT ROI_LEFT = 0,ROI_Right = 0;
	CMCADoc* pMCADoc = (CMCADoc*) m_pDocument;
	CClientDC dc(this);
	UserPlot_Total.SetUserView(&dc);
	if(!ROI_LeftFlag)
	{
		ROI_LEFT = (UINT)UserPlot_Total.WindowsXToAxis(point.x);
		ROI_LeftFlag = TRUE;
		if (pMCADoc->pDoc_ROIManageing != NULL)
		{
			pMCADoc->pDoc_ROIManageing->m_nROIStart = ROI_LEFT;
			pMCADoc->pDoc_ROIManageing->UpdateData(FALSE);
		}	
	}
	else
	{
		ROI_LeftFlag = FALSE;
		ROI_Right = (UINT)UserPlot_Total.WindowsXToAxis(point.x);
		if (ROI_Right < ROI_LEFT)
		{
			UINT temp = ROI_LEFT;
			ROI_LEFT = ROI_Right;
			ROI_Right = temp;
		}
		if (ROI_Right < pMCADoc->GetActiveSpectrum().GetSpectrumSize())
		{
			CROI ROI_new(ROI_LEFT,ROI_Right);
			CString str;
			str.Format(_T("确认ROI:%d-%d？"),ROI_LEFT,ROI_Right);
			BOOL IsOK = MessageBox(str,_T("ROI Identify"),1);
			if(IsOK == 1 && pMCADoc->pDoc_ROIManageing == NULL)//Define ROI对话框未弹出时添加
			{
				if(ROI_LEFT == ROI_Right)
					MessageBox(_T("Invalid ROI!"));
				else
					pMCADoc->GetActiveSpectrum().AddROI(ROI_new);
			}
			if (IsOK == 1 && pMCADoc->pDoc_ROIManageing != NULL)
			{
				pMCADoc->pDoc_ROIManageing->m_nROIStart = ROI_LEFT;
				pMCADoc->pDoc_ROIManageing->m_nROIEnd = ROI_Right;
				pMCADoc->pDoc_ROIManageing->UpdateData(FALSE);
				pMCADoc->pDoc_ROIManageing->OnBnClickedRoiAdd();
			}
		}
	}
	pMCADoc->UpdateAllViews(NULL);
	
	CView::OnLButtonDblClk(nFlags, point);
}


void CTotalView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	UserPlot_Total.GetWnd(this);  
	m_nLButtonDown = FALSE;
}


BOOL CTotalView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//return CView::OnEraseBkgnd(pDC);
	return TRUE;
}


void CTotalView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CMCADoc* pMCADoc = (CMCADoc*) m_pDocument;
	if (m_nLButtonDown)
	{
		CClientDC dc(this);
		UserPlot_Total.SetUserView(&dc);
		double x = UserPlot_Total.WindowsXToAxis(point.x);
		double y = UserPlot_Total.WindowsYToAxis(point.y);
		UserPlot_Total.DrawVerticleLine(&dc,x);
		UINT ShowData = UserPlot_Total.GetCursorPosition();
		UserPlot_Total.SetDefaultView(&dc);
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


BOOL CTotalView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	CMCADoc* pMCADoc = (CMCADoc*) m_pDocument;
	CClientDC dc(this);
	UserPlot_Total.SetUserView(&dc);
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_LEFT:
			{
				UserPlot_Total.DrawVerticleLine(&dc,UserPlot_Total.GetCursorPosition()-1);
				UINT ShowData = UserPlot_Total.GetCursorPosition();
				UserPlot_Total.SetDefaultView(&dc);
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
				UserPlot_Total.DrawVerticleLine(&dc,UserPlot_Total.GetCursorPosition()+1);
				UINT ShowData = UserPlot_Total.GetCursorPosition();
				UserPlot_Total.SetDefaultView(&dc);
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
