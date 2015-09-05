
// MCA.cpp : ����Ӧ�ó��������Ϊ��
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
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// ��׼��ӡ��������


	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
	ON_COMMAND(ID_MCA_CONNECT, &CMCAApp::OnMcaConnect)
/*	ON_COMMAND(ID_START, &CMCAApp::OnStart)*/
	//ON_COMMAND(ID_DEFINEROI, &CMCAApp::OnDefineROI)
	ON_COMMAND(ID_DEFINEROI, &CMCAApp::OnDefineroi)
END_MESSAGE_MAP()


// CMCAApp ����

CMCAApp::CMCAApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// ���Ӧ�ó��������ù�����������ʱ֧��(/clr)�����ģ���:
	//     1) �����д˸������ã�������������������֧�ֲ�������������
	//     2) ��������Ŀ�У������밴������˳���� System.Windows.Forms ������á�
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("MCA.AppID.NoVersion"));

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
	m_pROIManageDlg = NULL;
}

// Ψһ��һ�� CMCAApp ����

CMCAApp theApp;


// CMCAApp ��ʼ��

BOOL CMCAApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// ʹ�� RichEdit �ؼ���Ҫ  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)


	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CMCADoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ��ܴ���
		RUNTIME_CLASS(CMCAView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// ������׼ shell ���DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	m_nCmdShow = SW_SHOWMAXIMIZED;


	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
	m_pMainWnd->ShowWindow(SW_SHOW);
	//m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

int CMCAApp::ExitInstance()
{
	//TODO: �����������ӵĸ�����Դ
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}

// CMCAApp ��Ϣ�������


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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

// �������жԻ����Ӧ�ó�������
void CMCAApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CMCAApp ��Ϣ�������





void CMCAApp::OnMcaConnect()
{
	// TODO: �ڴ���������������
	CCommunicationPortDlg	CommunicationPortDlg;
	CommunicationPortDlg.DoModal();
}


void CAboutDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


// void CMCAApp::OnStart()
// {
// 	// TODO: �ڴ���������������
// 	//�������ײɼ�
// 	byte Start_Command[] ={0xF5, 0xFA, 0xF0, 0x02, 0x00, 0x00, 0xFD, 0x1F};
// 	CMainFrame* pFrame = (CMainFrame*)m_pMainWnd;
// 	pFrame->m_SCIModule.SendArray(Start_Command,sizeof(Start_Command));
// 	//����CommandFlag��־
// 	CMCADoc* pMCADoc = (CMCADoc*)pFrame->GetActiveDocument();
// 	pMCADoc->SetCommandFlag(S_StartPick);
// 	UINT32 interval = 0;
// 	CControlView* pControlView_temp = (CControlView*) pFrame->pControlView;
// 	pControlView_temp->UpdateData(TRUE);
// 	interval = (pControlView_temp->m_nPickInterval)*3600*1000;
// 	pFrame->SetTimer(1,interval,NULL);//��ʱ�洢����
// 	pFrame->SetTimer(101,30000,NULL);//��ʼ���ײɼ�
// }


//void CMCAApp::OnDefineROI()
//{
//	// TODO: �ڴ���������������
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
	// TODO: �ڴ���������������
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

// 	try{
// 		throw 0;
// 	}
// 	catch(...)
// 	{
// 		AfxMessageBox(_T("HEHE����"));
// 	}
}
