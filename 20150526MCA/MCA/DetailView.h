#pragma once

#include "UserPlot.h"
// CDetailView 视图

class CDetailView : public CView
{
	DECLARE_DYNCREATE(CDetailView)

protected:
	CDetailView();           // 动态创建所使用的受保护的构造函数
	virtual ~CDetailView();

public:
	virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
private:
	CUserPlot UserPlot_Detail;
	BOOL m_nLButtonDown;
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};


