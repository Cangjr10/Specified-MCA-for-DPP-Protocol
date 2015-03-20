
// MainFrm.cpp : CMainFrame ���ʵ��
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
//��Ӵ��ڿؼ���Oncomm��Ϣ��Ӧ����
BEGIN_EVENTSINK_MAP(CMainFrame,CFrameWnd)
	ON_EVENT(CMainFrame,ID_COMMCTRL,1,OnComm,VTS_NONE)
END_EVENTSINK_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame():m_ViewCreated(FALSE)
{
	// TODO: �ڴ���ӳ�Ա��ʼ������

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
// 		TRACE0("δ�ܴ���������\n");
// 		return -1;      // δ�ܴ���
// 	}
	m_ImageList.Create(24,24,ILC_COLOR32|ILC_MASK,1,1);//����ͼ���б�
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
	//��ʾ������
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);


	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: �������Ҫ��ͣ������������ɾ��������
// 	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
// 	EnableDocking(CBRS_ALIGN_ANY);
// 	DockControlBar(&m_wndToolBar);
	m_SCIModule.Create(NULL, WS_VISIBLE | WS_CHILD, CRect(0,0,0,0),this, ID_COMMCTRL);
	return 0;
}



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	//�������Ҳ�ִ���
	VERIFY(m_wndSplitter.CreateStatic(this, 1, 2,WS_CHILD|WS_VISIBLE,AFX_IDW_PANE_FIRST));
	//�����󴰿���ͼ����ȡָ��
	m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CControlView), CSize(0,0 ), pContext);
	pControlView =(CControlView*)m_wndSplitter.GetPane(0,0);
	CSize size = pControlView->GetTotalSize();
	m_wndSplitter.SetColumnInfo(0,size.cx,1);
	//�����ұ����²�ִ���
	VERIFY(m_wndSplitter_VIEW.CreateStatic(&m_wndSplitter, 2,1,WS_CHILD | WS_VISIBLE,m_wndSplitter.IdFromRowCol(0,1)));
	//����ȫ�׺�ROI����Ĵ�С
	CRect rect;
	GetClientRect(&rect);
	//�������ϴ�����ͼ
	VERIFY(m_wndSplitter_VIEW.CreateView(0, 0,RUNTIME_CLASS(CDetailView), CSize( 0, (rect.bottom-rect.top)*2/3), pContext));
	pDetailView = (CDetailView*)m_wndSplitter_VIEW.GetPane(0,0);
	//�������´�����ͼ
	VERIFY(m_wndSplitter_VIEW.CreateView(1, 0,RUNTIME_CLASS(CTotalView), CSize( 0, 0), pContext));
	pTotalVIew = (CTotalView*)m_wndSplitter_VIEW.GetPane(1,0);
	m_ViewCreated = TRUE;
	SetTimer(100,300,NULL);//��һ��ʱ����ʾͨѶ���ý���
	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	//cs.style |= WS_MAXIMIZE;

	return TRUE;
}

// CMainFrame ���

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


// CMainFrame ��Ϣ�������



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
	// TODO: �ڴ˴������Ϣ����������
}
//������Ӧ����
void CMainFrame::OnComm()
{
	CMCADoc* pMCADoc;
	pMCADoc = (CMCADoc*)GetActiveDocument();
	VARIANT variant_input;
	COleSafeArray safearray_input;
	if(m_SCIModule.get_CommEvent()==2)//�¼�2��ʾ���ܻ��������ַ�
	{
		variant_input=m_SCIModule.get_Input();//��������
		safearray_input=variant_input;//variant����ת����colesafearray�ͱ���
		pMCADoc->MSComm_Decode(safearray_input);//������ת�����ĵ�����д���
	}

}




void CMainFrame::OnTimer(UINT_PTR nIDEvent)													
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(nIDEvent == 100)
	{
		KillTimer(100);
		CCommunicationPortDlg	CommunicationPortDlg;
		CommunicationPortDlg.DoModal();
	}
	if (nIDEvent == 1)//��ʱ��ȡ��������
	{
		OnMcaDownload();
	}
// 	if (nIDEvent == 2)
// 	{
// 		KillTimer(nIDEvent);//�������ݻ�ȡ��ϣ������¶Ȼ�ȡ
// 		OnDiagnostic();
// 	}
	
	CFrameWnd::OnTimer(nIDEvent);
}


//void CMainFrame::OnDefineroi()
//{
//	// TODO: �ڴ���������������
//}

byte DataDownload[] = {0xF5, 0xFA, 0x02, 0x03, 0x00, 0x00, 0xFE, 0x0C};//�������ݻ�ȡ����
void CMainFrame::OnMcaDownload()
{

	// TODO: �ڴ���������������
	pControlView->UpdateData(TRUE);//��ȡ������Ϣ
	if (m_SCIModule.get_PortOpen())
	{
		m_SCIModule.SendArray(DataDownload,sizeof(DataDownload));
	}
	//����CommandFlag��־
	CMCADoc* pMCADoc;
	pMCADoc = (CMCADoc*)GetActiveDocument();
	pMCADoc->SetCommandFlag(S_Download);
	//pMCADoc->SaveSpectrumWithTemperature(_T("E:\\"),_T("1"));
	pMCADoc->SaveXMLFile();
// 	CWaringDlg WarningDLG;
// 	WarningDLG.DoModal();
}

byte RequestDiagnostic[] = {0xF5, 0xFA, 0x03, 0x05, 0x00, 0x00, 0xFE, 0x09};//Ѱ���豸��Ϣ����ʼ��־
void CMainFrame::OnDiagnostic()
{
	// TODO: �ڴ���������������
	if (m_SCIModule.get_PortOpen())
	{
		m_SCIModule.SendArray(RequestDiagnostic,sizeof(RequestDiagnostic));
	}
	//����CommandFlag��־
	CMCADoc* pMCADoc;
	pMCADoc = (CMCADoc*)GetActiveDocument();
	pMCADoc->SetCommandFlag(S_Diagnostic);
}

byte ClearSpectrum[] = {0xF5, 0xFA, 0xF0, 0x01, 0x00, 0x00, 0xFD, 0x20};//Clear Spectrum
void CMainFrame::OnRestart()//���¿�ʼʱ��
{
	// TODO: �ڴ���������������
	if (m_SCIModule.get_PortOpen())
	{
		m_SCIModule.SendArray(ClearSpectrum,sizeof(ClearSpectrum));
	}
	//����CommandFlag��־
	CMCADoc* pMCADoc;
	pMCADoc = (CMCADoc*)GetActiveDocument();
	pMCADoc->SetCommandFlag(S_Restart);
}

byte Pause_Command[] ={0xF5, 0xFA, 0xF0, 0x03, 0x00, 0x00, 0xFD, 0x1E};
void CMainFrame::OnPause()
{
	// TODO: �ڴ���������������
	m_SCIModule.SendArray(Pause_Command,sizeof(Pause_Command));
	//����CommandFlag��־
	CMCADoc* pMCADoc = (CMCADoc*)GetActiveDocument();
	pMCADoc->SetCommandFlag(S_Pause);
}

byte Start_Command[] ={0xF5, 0xFA, 0xF0, 0x02, 0x00, 0x00, 0xFD, 0x1F};
void CMainFrame::OnStart()
{
	// TODO: �ڴ���������������
	m_SCIModule.SendArray(Start_Command,sizeof(Start_Command));
	//����CommandFlag��־
	CMCADoc* pMCADoc = (CMCADoc*)GetActiveDocument();
	pMCADoc->SetCommandFlag(S_StartPick);
	UINT32 interval = 0;
	CControlView* pControlView_temp = pControlView;
	pControlView_temp->UpdateData(TRUE);
	interval = (pControlView_temp->m_nPickInterval)*3600*1000;
	SetTimer(1,interval,NULL);//��ʱ�洢����
	
}
