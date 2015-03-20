
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "MCA.h"
#include "MCADoc.h"
#include "MainFrm.h"
#include "CommunicationPortDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_COMMAND(ID_MCA_DOWNLOAD, &CMainFrame::OnMcaDownload)
	ON_COMMAND(ID_Diagnostic, &CMainFrame::OnDiagnostic)
	ON_COMMAND(ID_RESTART, &CMainFrame::OnRestart)
	ON_COMMAND(ID_PAUSE, &CMainFrame::OnPause)
	ON_COMMAND(ID_START, &CMainFrame::OnStart)
END_MESSAGE_MAP()
//添加串口控件的Oncomm消息响应函数
BEGIN_EVENTSINK_MAP(CMainFrame,CFrameWnd)
	ON_EVENT(CMainFrame,ID_COMMCTRL,1,OnComm,VTS_NONE)
END_EVENTSINK_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame():m_ViewCreated(FALSE)
{
	// TODO: 在此添加成员初始化代码

}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

// 	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
// 		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
// 	{
// 		TRACE0("未能创建工具栏\n");
// 		return -1;      // 未能创建
// 	}
	m_ImageList.Create(24,24,ILC_COLOR32|ILC_MASK,1,1);//创建图像列表
	m_ImageList.Add(AfxGetApp()->LoadIconW(IDI_ICON1));
	m_ImageList.Add(AfxGetApp()->LoadIconW(IDI_ICON2));
	m_ImageList.Add(AfxGetApp()->LoadIconW(IDI_ICON3));
	m_ImageList.Add(AfxGetApp()->LoadIconW(IDI_ICON4));
	UINT array[4];
	array[0] = ID_FILE_OPEN;
	array[1] = ID_FILE_SAVE_AS;
	array[2] = ID_MCA_CONNECT;
	array[3] = ID_MCA_DOWNLOAD;
	m_wndToolBar.Create(this);
	m_wndToolBar.SetButtons(array,4);
	m_wndToolBar.GetToolBarCtrl().SetImageList(&m_ImageList);
	m_wndToolBar.SetSizes(CSize(40,40),CSize(24,24));
	m_wndToolBar.EnableToolTips(TRUE);
	//显示工具栏
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);


	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: 如果不需要可停靠工具栏，则删除这三行
// 	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
// 	EnableDocking(CBRS_ALIGN_ANY);
// 	DockControlBar(&m_wndToolBar);
	m_SCIModule.Create(NULL, WS_VISIBLE | WS_CHILD, CRect(0,0,0,0),this, ID_COMMCTRL);
	return 0;
}



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	//创建左右拆分窗口
	VERIFY(m_wndSplitter.CreateStatic(this, 1, 2,WS_CHILD|WS_VISIBLE,AFX_IDW_PANE_FIRST));
	//创建左窗口视图并获取指针
	m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CControlView), CSize(0,0 ), pContext);
	pControlView =(CControlView*)m_wndSplitter.GetPane(0,0);
	CSize size = pControlView->GetTotalSize();
	m_wndSplitter.SetColumnInfo(0,size.cx,1);
	//创建右边上下拆分窗口
	VERIFY(m_wndSplitter_VIEW.CreateStatic(&m_wndSplitter, 2,1,WS_CHILD | WS_VISIBLE,m_wndSplitter.IdFromRowCol(0,1)));
	//划分全谱和ROI区域的大小
	CRect rect;
	GetClientRect(&rect);
	//创建右上窗口视图
	VERIFY(m_wndSplitter_VIEW.CreateView(0, 0,RUNTIME_CLASS(CDetailView), CSize( 0, (rect.bottom-rect.top)*2/3), pContext));
	pDetailView = (CDetailView*)m_wndSplitter_VIEW.GetPane(0,0);
	//创建右下窗口视图
	VERIFY(m_wndSplitter_VIEW.CreateView(1, 0,RUNTIME_CLASS(CTotalView), CSize( 0, 0), pContext));
	pTotalVIew = (CTotalView*)m_wndSplitter_VIEW.GetPane(1,0);
	m_ViewCreated = TRUE;
	SetTimer(100,300,NULL);//过一段时间显示通讯配置界面
	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	//cs.style |= WS_MAXIMIZE;

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序



void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);
	CRect rect;
	GetClientRect(&rect);
	if (m_ViewCreated == TRUE)
	{
		m_wndSplitter_VIEW.SetRowInfo(0,(rect.bottom-rect.top)*2/3,1);
		m_wndSplitter_VIEW.RecalcLayout();
	}
	// TODO: 在此处添加消息处理程序代码
}
//串口响应函数
void CMainFrame::OnComm()
{
	CMCADoc* pMCADoc;
	pMCADoc = (CMCADoc*)GetActiveDocument();
	VARIANT variant_input;
	COleSafeArray safearray_input;
	if(m_SCIModule.get_CommEvent()==2)//事件2表示接受缓冲区有字符
	{
		variant_input=m_SCIModule.get_Input();//读缓冲区
		safearray_input=variant_input;//variant数据转换成colesafearray型变量
		pMCADoc->MSComm_Decode(safearray_input);//将数据转移至文档类进行处理
	}

}




void CMainFrame::OnTimer(UINT_PTR nIDEvent)													
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(nIDEvent == 100)
	{
		KillTimer(100);
		CCommunicationPortDlg	CommunicationPortDlg;
		CommunicationPortDlg.DoModal();
	}
	if (nIDEvent == 1)//定时获取数据命令
	{
		OnMcaDownload();
	}
// 	if (nIDEvent == 2)
// 	{
// 		KillTimer(nIDEvent);//能谱数据获取完毕，进行温度获取
// 		OnDiagnostic();
// 	}
	
	CFrameWnd::OnTimer(nIDEvent);
}


//void CMainFrame::OnDefineroi()
//{
//	// TODO: 在此添加命令处理程序代码
//}

byte DataDownload[] = {0xF5, 0xFA, 0x02, 0x03, 0x00, 0x00, 0xFE, 0x0C};//能谱数据获取请求
void CMainFrame::OnMcaDownload()
{

	// TODO: 在此添加命令处理程序代码
	pControlView->UpdateData(TRUE);//获取更新信息
	if (m_SCIModule.get_PortOpen())
	{
		m_SCIModule.SendArray(DataDownload,sizeof(DataDownload));
	}
	//设置CommandFlag标志
	CMCADoc* pMCADoc;
	pMCADoc = (CMCADoc*)GetActiveDocument();
	pMCADoc->SetCommandFlag(S_Download);
	//pMCADoc->SaveSpectrumWithTemperature(_T("E:\\"),_T("1"));
	pMCADoc->SaveXMLFile();
// 	CWaringDlg WarningDLG;
// 	WarningDLG.DoModal();
}

byte RequestDiagnostic[] = {0xF5, 0xFA, 0x03, 0x05, 0x00, 0x00, 0xFE, 0x09};//寻找设备信息的起始标志
void CMainFrame::OnDiagnostic()
{
	// TODO: 在此添加命令处理程序代码
	if (m_SCIModule.get_PortOpen())
	{
		m_SCIModule.SendArray(RequestDiagnostic,sizeof(RequestDiagnostic));
	}
	//设置CommandFlag标志
	CMCADoc* pMCADoc;
	pMCADoc = (CMCADoc*)GetActiveDocument();
	pMCADoc->SetCommandFlag(S_Diagnostic);
}

byte ClearSpectrum[] = {0xF5, 0xFA, 0xF0, 0x01, 0x00, 0x00, 0xFD, 0x20};//Clear Spectrum
void CMainFrame::OnRestart()//更新开始时间
{
	// TODO: 在此添加命令处理程序代码
	if (m_SCIModule.get_PortOpen())
	{
		m_SCIModule.SendArray(ClearSpectrum,sizeof(ClearSpectrum));
	}
	//设置CommandFlag标志
	CMCADoc* pMCADoc;
	pMCADoc = (CMCADoc*)GetActiveDocument();
	pMCADoc->SetCommandFlag(S_Restart);
}

byte Pause_Command[] ={0xF5, 0xFA, 0xF0, 0x03, 0x00, 0x00, 0xFD, 0x1E};
void CMainFrame::OnPause()
{
	// TODO: 在此添加命令处理程序代码
	m_SCIModule.SendArray(Pause_Command,sizeof(Pause_Command));
	//设置CommandFlag标志
	CMCADoc* pMCADoc = (CMCADoc*)GetActiveDocument();
	pMCADoc->SetCommandFlag(S_Pause);
}

byte Start_Command[] ={0xF5, 0xFA, 0xF0, 0x02, 0x00, 0x00, 0xFD, 0x1F};
void CMainFrame::OnStart()
{
	// TODO: 在此添加命令处理程序代码
	m_SCIModule.SendArray(Start_Command,sizeof(Start_Command));
	//设置CommandFlag标志
	CMCADoc* pMCADoc = (CMCADoc*)GetActiveDocument();
	pMCADoc->SetCommandFlag(S_StartPick);
	UINT32 interval = 0;
	CControlView* pControlView_temp = pControlView;
	pControlView_temp->UpdateData(TRUE);
	interval = (pControlView_temp->m_nPickInterval)*3600*1000;
	SetTimer(1,interval,NULL);//定时存储能谱
	
}
