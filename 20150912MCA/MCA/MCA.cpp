
// MCA.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "MCA.h"
#include "MainFrm.h"

#include "MCADoc.h"
#include "MCAView.h"
#include "mscomm.h"
#include "CommunicationPortDlg.h"
#include "ControlView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMCAApp

BEGIN_MESSAGE_MAP(CMCAApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CMCAApp::OnAppAbout)
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// 标准打印设置命令


	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
	ON_COMMAND(ID_MCA_CONNECT, &CMCAApp::OnMcaConnect)
/*	ON_COMMAND(ID_START, &CMCAApp::OnStart)*/
	//ON_COMMAND(ID_DEFINEROI, &CMCAApp::OnDefineROI)
	ON_COMMAND(ID_DEFINEROI, &CMCAApp::OnDefineroi)
END_MESSAGE_MAP()


// CMCAApp 构造

CMCAApp::CMCAApp()
{
try{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// 如果应用程序是利用公共语言运行时支持(/clr)构建的，则:
	//     1) 必须有此附加设置，“重新启动管理器”支持才能正常工作。
	//     2) 在您的项目中，您必须按照生成顺序向 System.Windows.Forms 添加引用。
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
	//为 CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("MCA.AppID.NoVersion"));

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
	m_pROIManageDlg = NULL;
}
catch(...)
{
	AfxMessageBox(_T("CMCAApp::CMCAApp！"));
}
}

// 唯一的一个 CMCAApp 对象

CMCAApp theApp;


// CMCAApp 初始化

BOOL CMCAApp::InitInstance()
{
try{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// 使用 RichEdit 控件需要  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)


	// 注册应用程序的文档模板。文档模板
	// 将用作文档、框架窗口和视图之间的连接
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CMCADoc),
		RUNTIME_CLASS(CMainFrame),       // 主 SDI 框架窗口
		RUNTIME_CLASS(CMCAView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// 分析标准 shell 命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	m_nCmdShow = SW_SHOWMAXIMIZED;


	// 调度在命令行中指定的命令。如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// 唯一的一个窗口已初始化，因此显示它并对其进行更新
	m_pMainWnd->ShowWindow(SW_SHOW);
	//m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMainWnd->UpdateWindow();
}
catch(...)
{
	AfxMessageBox(_T("CMCAApp::InitInstance！"));
}
return TRUE;
}

int CMCAApp::ExitInstance()
{
	//TODO: 处理可能已添加的附加资源
	try{
	AfxOleTerm(FALSE);
	}
	catch(...)
	{
		AfxMessageBox(_T("CMCAApp::ExitInstance！"));
	}
	return CWinApp::ExitInstance();
}

// CMCAApp 消息处理程序


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
//	CMscomm m_SCIModule;
	afx_msg void OnBnClickedOk();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
//	DDX_Control(pDX, IDC_MSCOMM, m_SCIModule);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CMCAApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CMCAApp 消息处理程序





void CMCAApp::OnMcaConnect()
{
try{
	// TODO: 在此添加命令处理程序代码
	CCommunicationPortDlg	CommunicationPortDlg;
	CommunicationPortDlg.DoModal();
}
catch(...)
{
	AfxMessageBox(_T("CMCAApp::OnMcaConnect！"));
}
}


void CAboutDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


// void CMCAApp::OnStart()
// {
// 	// TODO: 在此添加命令处理程序代码
// 	//开启能谱采集
// 	byte Start_Command[] ={0xF5, 0xFA, 0xF0, 0x02, 0x00, 0x00, 0xFD, 0x1F};
// 	CMainFrame* pFrame = (CMainFrame*)m_pMainWnd;
// 	pFrame->m_SCIModule.SendArray(Start_Command,sizeof(Start_Command));
// 	//设置CommandFlag标志
// 	CMCADoc* pMCADoc = (CMCADoc*)pFrame->GetActiveDocument();
// 	pMCADoc->SetCommandFlag(S_StartPick);
// 	UINT32 interval = 0;
// 	CControlView* pControlView_temp = (CControlView*) pFrame->pControlView;
// 	pControlView_temp->UpdateData(TRUE);
// 	interval = (pControlView_temp->m_nPickInterval)*3600*1000;
// 	pFrame->SetTimer(1,interval,NULL);//定时存储能谱
// 	pFrame->SetTimer(101,30000,NULL);//初始能谱采集
// }


//void CMCAApp::OnDefineROI()
//{
//	// TODO: 在此添加命令处理程序代码
//	if (m_pROIManageDlg == NULL)
//	{
//		m_pROIManageDlg = new CROIManaging();
//		m_pROIManageDlg->Create(ID_DEFINEROI,this);
//	}
//	m_pROIManageDlg->ShowWindow(SW_SHOW);
//	
//}




void CMCAApp::OnDefineroi()
{
try{
	// TODO: 在此添加命令处理程序代码
	CMainFrame* pFrame = (CMainFrame*)m_pMainWnd;
	CMCADoc* pMCADoc = (CMCADoc*)pFrame->GetActiveDocument();
	if (NULL != m_pROIManageDlg)
	{
		delete m_pROIManageDlg;
		m_pROIManageDlg=NULL;
	}
	if (m_pROIManageDlg == NULL)
	{
		m_pROIManageDlg = new CROIManaging();
		m_pROIManageDlg->Create(IDD_ROI,NULL);
		pMCADoc->pDoc_ROIManageing = m_pROIManageDlg;
	}
	m_pROIManageDlg->ShowWindow(SW_SHOW);
}
catch(...)
{
	AfxMessageBox(_T("CMCAApp::OnDefineroi！"));
}
// 	try{
// 		throw 0;
// 	}
// 	catch(...)
// 	{
// 		AfxMessageBox(_T("HEHE！！"));
// 	}
}
