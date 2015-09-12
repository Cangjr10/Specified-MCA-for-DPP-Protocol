
// MainFrm.h : CMainFrame 类的接口
//

#pragma once
#include "ControlView.h"
#include "DetailView.h"
#include "TotalView.h"
#include "mscomm.h"

class CMainFrame : public CFrameWnd
{
	
protected: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 特性
protected:
	CSplitterWnd m_wndSplitter;
	CSplitterWnd m_wndSplitter_VIEW;

public:
	CControlView*  pControlView;
	CTotalView*	   pTotalVIew;
	CDetailView*   pDetailView;
// 操作
public:

// 重写
public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CToolBar          m_wndToolBar;
	CImageList		  m_ImageList;
	CStatusBar        m_wndStatusBar;
private:
	BOOL m_ViewCreated;
	
// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

public:
	void Measure_Start(){ OnStart();};
	void Measure_Restart(){ OnRestart();};
	void Measure_SpectrumRequest(){ OnMcaDownload();};
	void Measure_Diagnostic(){ OnDiagnostic();};
	CMscomm	m_SCIModule;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnComm();
	DECLARE_EVENTSINK_MAP()
	
//	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	afx_msg void OnDefineroi();
	afx_msg void OnMcaDownload();
	afx_msg void OnDiagnostic();
	afx_msg void OnRestart();
	afx_msg void OnPause();
	afx_msg void OnStart();
};


