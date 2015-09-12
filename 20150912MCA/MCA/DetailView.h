#pragma once

#include "UserPlot.h"
// CDetailView ��ͼ

class CDetailView : public CView
{
	DECLARE_DYNCREATE(CDetailView)

protected:
	CDetailView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CDetailView();

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
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


