// CommunicationPortDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MCA.h"
#include "CommunicationPortDlg.h"
#include "afxdialogex.h"
#include "MCADoc.h"


// CCommunicationPortDlg 对话框

IMPLEMENT_DYNAMIC(CCommunicationPortDlg, CDialogEx)

CCommunicationPortDlg::CCommunicationPortDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCommunicationPortDlg::IDD, pParent)
	, m_nCommDlg(2)
	, m_nBaudrateDlg(0)
	, m_nTimeRequestDlg(3000)
	, m_RS232(TRUE)
	,m_nPortFlag(FALSE)
{
	pFrame = (CMainFrame*)AfxGetMainWnd();
	CMCADoc* pDoc = (CMCADoc*)pFrame->GetActiveDocument();
	pDoc->GetActiveCommunicationDlg(this);
}

CCommunicationPortDlg::~CCommunicationPortDlg()
{
	CMCADoc* pDoc = (CMCADoc*)pFrame->GetActiveDocument();
	pDoc->SetCommandFlag(S_NULL);
}

void CCommunicationPortDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_COMBO_COM, m_nCommDlg);
	DDX_CBIndex(pDX, IDC_COMBO_BAUD, m_nBaudrateDlg);
	DDX_Text(pDX, IDC_EDIT_REQUESRTIME, m_nTimeRequestDlg);
	DDX_Control(pDX, IDC_COMBO_COM, m_CommDlg);
	DDX_Control(pDX, IDC_COMBO_BAUD, m_BaudDlg);
	DDX_Control(pDX, IDC_EDIT_DEVICEINFO, m_DeviceInfo);
}


BEGIN_MESSAGE_MAP(CCommunicationPortDlg, CDialogEx)
	ON_BN_CLICKED(IDCONNECT, &CCommunicationPortDlg::OnBnClickedConnect)
	ON_BN_CLICKED(IDC_BUTTON_SETDEFAULTTIME, &CCommunicationPortDlg::OnBnClickedButtonSetdefaulttime)
	ON_BN_CLICKED(IDC_BUTTON_OpenPort, &CCommunicationPortDlg::OnBnClickedButtonOpenport)
	ON_BN_CLICKED(IDC_BUTTON_FINDDEVICE, &CCommunicationPortDlg::OnBnClickedButtonFinddevice)
//	ON_WM_SETTINGCHANGE()

ON_BN_CLICKED(IDCANCEL, &CCommunicationPortDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CCommunicationPortDlg 消息处理程序




BOOL CCommunicationPortDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString str;
	for (int i=1;i<25;i++)
	{
		//查询可用串口
// 		try
// 		{
// 			pFrame->m_SCIModule.put__CommPort(i);//选择com口
// 			pFrame->m_SCIModule.put_PortOpen(1);
// 			if(pFrame->m_SCIModule.get_PortOpen())
// 			{
// 				CString strtemp;
// 				strtemp.Format(_T("串口%d打开成功"),i);
// 				AfxMessageBox(strtemp);
// 				CString strtemp1;
// 				strtemp1.Format(_T("com%d"),i);
// 				m_CommDlg.AddString(strtemp1);
// 				pFrame->m_SCIModule.put_PortOpen(0);
// 			}
// 		}
// 		catch(...)
// 		{
// 		}
		str.Format(_T("COM%d"),i);
		m_CommDlg.AddString(str);
	}
	str_baudrate.push_back(_T("4800"));
	str_baudrate.push_back(_T("9600"));
	str_baudrate.push_back(_T("19200"));
	str_baudrate.push_back(_T("38400"));
	str_baudrate.push_back(_T("57600"));
	str_baudrate.push_back(_T("115200"));//CString类型存储的是string变量的首地址，每个元素占四个字节
	for (int i=0;i < static_cast<int>(str_baudrate.size());i++)
	{
		m_BaudDlg.AddString(str_baudrate[i]);
	}
	//m_nBaudrateDlg = str_baudrate.size()-1;
	CheckDlgButton(IDC_RADIO_RS232, 1); 
	CMCADoc* pMCADoc = (CMCADoc*)pFrame->GetActiveDocument();
	pMCADoc->UpdateCommunicationDlgInfo(m_nCommDlg,m_nBaudrateDlg,m_nTimeRequestDlg,FALSE);
	UpdateData(FALSE);
	return TRUE;
	// 异常: OCX 属性页应返回 FALSE
}


void CCommunicationPortDlg::OnBnClickedButtonSetdefaulttime()
{
	// TODO: 在此添加控件通知处理程序代码
	m_nTimeRequestDlg = 5000;
	UpdateData(FALSE);
}


void CCommunicationPortDlg::OnBnClickedButtonOpenport()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString Com_Config=_T("");
	Com_Config += str_baudrate[m_nBaudrateDlg];
	Com_Config += _T(",n,8,1");
	m_nPortFlag=pFrame->m_SCIModule.get_PortOpen();
	if (m_nPortFlag == FALSE)
	{
		pFrame->m_SCIModule.put__CommPort(m_nCommDlg+1);//选择com口
		pFrame->m_SCIModule.put_InputMode(1);//输入方式为二进制方式
		pFrame->m_SCIModule.put_InBufferSize(30000);//输入缓冲区大小为1024byte
		pFrame->m_SCIModule.put_OutBufferSize(512);//输出缓冲区大小为512byte
		pFrame->m_SCIModule.put_Settings(Com_Config);//设置串口参数：9600波特率，无奇偶校验，8个数据位，1个停止位
		if(!pFrame->m_SCIModule.get_PortOpen() )//获取串口的当前状态
		{
			pFrame->m_SCIModule.put_PortOpen(1);//打开串口
			m_nPortFlag = TRUE;
		}
		pFrame->m_SCIModule.put_RThreshold(6);//每当串口接收缓冲区有多余或等于1个字符时将引发一个接收数据的oncomm事件
		pFrame->m_SCIModule.put_InputLen(0);//设置当前接收区数据长度为0
		pFrame->m_SCIModule.get_Input();//预读缓冲区以清空残留数据
		SetDlgItemTextW(IDC_BUTTON_OpenPort,_T("Close Port"));
	}
	else
	{
		pFrame->m_SCIModule.put_PortOpen(0);//关闭串口
		m_nPortFlag = FALSE;
		SetDlgItemTextW(IDC_BUTTON_OpenPort,_T("Open Port"));
	}
}


void CCommunicationPortDlg::OnBnClickedButtonFinddevice()
{
	// TODO: 在此添加控件通知处理程序代码
		byte Connect_Command[] ={0xF5, 0xFA, 0x03, 0x07, 0x00, 0x00, 0xFE, 0x07};
		pFrame->m_SCIModule.SendArray(Connect_Command,sizeof(Connect_Command));
		//设置CommandFlag标志
		CMCADoc* pDoc = (CMCADoc*)pFrame->GetActiveDocument();
		pDoc->SetCommandFlag(S_Connection);
/*		pDoc->UpdateCommunicationDlgInfo(m_nCommDlg , m_nBaudrateDlg, m_nTimeRequestDlg,TRUE);*/
}

void CCommunicationPortDlg::OnBnClickedConnect()
{
	// TODO: 在此添加控件通知处理程序代码
	//保存串口配置信息
	UpdateData(TRUE);
	CMCADoc* pDoc = (CMCADoc*)pFrame->GetActiveDocument();
	pDoc->UpdateCommunicationDlgInfo(m_nCommDlg , m_nBaudrateDlg, m_nTimeRequestDlg,TRUE);
	CDialogEx::OnOK();
}



void CCommunicationPortDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	if (pFrame->m_SCIModule.get_PortOpen())
	{
		pFrame->m_SCIModule.put_PortOpen(0);//关闭串口
	}
	UpdateData(TRUE);
	CMCADoc* pDoc = (CMCADoc*)pFrame->GetActiveDocument();
	pDoc->UpdateCommunicationDlgInfo(m_nCommDlg , m_nBaudrateDlg, m_nTimeRequestDlg,TRUE);
	m_nPortFlag = FALSE;
	CDialogEx::OnCancel();
}
