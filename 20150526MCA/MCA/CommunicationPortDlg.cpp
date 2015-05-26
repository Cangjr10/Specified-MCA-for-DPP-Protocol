// CommunicationPortDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MCA.h"
#include "CommunicationPortDlg.h"
#include "afxdialogex.h"
#include "MCADoc.h"


// CCommunicationPortDlg �Ի���

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


// CCommunicationPortDlg ��Ϣ�������




BOOL CCommunicationPortDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString str;
	for (int i=1;i<25;i++)
	{
		//��ѯ���ô���
// 		try
// 		{
// 			pFrame->m_SCIModule.put__CommPort(i);//ѡ��com��
// 			pFrame->m_SCIModule.put_PortOpen(1);
// 			if(pFrame->m_SCIModule.get_PortOpen())
// 			{
// 				CString strtemp;
// 				strtemp.Format(_T("����%d�򿪳ɹ�"),i);
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
	str_baudrate.push_back(_T("115200"));//CString���ʹ洢����string�������׵�ַ��ÿ��Ԫ��ռ�ĸ��ֽ�
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
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CCommunicationPortDlg::OnBnClickedButtonSetdefaulttime()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_nTimeRequestDlg = 5000;
	UpdateData(FALSE);
}


void CCommunicationPortDlg::OnBnClickedButtonOpenport()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CString Com_Config=_T("");
	Com_Config += str_baudrate[m_nBaudrateDlg];
	Com_Config += _T(",n,8,1");
	m_nPortFlag=pFrame->m_SCIModule.get_PortOpen();
	if (m_nPortFlag == FALSE)
	{
		pFrame->m_SCIModule.put__CommPort(m_nCommDlg+1);//ѡ��com��
		pFrame->m_SCIModule.put_InputMode(1);//���뷽ʽΪ�����Ʒ�ʽ
		pFrame->m_SCIModule.put_InBufferSize(30000);//���뻺������СΪ1024byte
		pFrame->m_SCIModule.put_OutBufferSize(512);//�����������СΪ512byte
		pFrame->m_SCIModule.put_Settings(Com_Config);//���ô��ڲ�����9600�����ʣ�����żУ�飬8������λ��1��ֹͣλ
		if(!pFrame->m_SCIModule.get_PortOpen() )//��ȡ���ڵĵ�ǰ״̬
		{
			pFrame->m_SCIModule.put_PortOpen(1);//�򿪴���
			m_nPortFlag = TRUE;
		}
		pFrame->m_SCIModule.put_RThreshold(6);//ÿ�����ڽ��ջ������ж�������1���ַ�ʱ������һ���������ݵ�oncomm�¼�
		pFrame->m_SCIModule.put_InputLen(0);//���õ�ǰ���������ݳ���Ϊ0
		pFrame->m_SCIModule.get_Input();//Ԥ������������ղ�������
		SetDlgItemTextW(IDC_BUTTON_OpenPort,_T("Close Port"));
	}
	else
	{
		pFrame->m_SCIModule.put_PortOpen(0);//�رմ���
		m_nPortFlag = FALSE;
		SetDlgItemTextW(IDC_BUTTON_OpenPort,_T("Open Port"));
	}
}


void CCommunicationPortDlg::OnBnClickedButtonFinddevice()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		byte Connect_Command[] ={0xF5, 0xFA, 0x03, 0x07, 0x00, 0x00, 0xFE, 0x07};
		pFrame->m_SCIModule.SendArray(Connect_Command,sizeof(Connect_Command));
		//����CommandFlag��־
		CMCADoc* pDoc = (CMCADoc*)pFrame->GetActiveDocument();
		pDoc->SetCommandFlag(S_Connection);
/*		pDoc->UpdateCommunicationDlgInfo(m_nCommDlg , m_nBaudrateDlg, m_nTimeRequestDlg,TRUE);*/
}

void CCommunicationPortDlg::OnBnClickedConnect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//���洮��������Ϣ
	UpdateData(TRUE);
	CMCADoc* pDoc = (CMCADoc*)pFrame->GetActiveDocument();
	pDoc->UpdateCommunicationDlgInfo(m_nCommDlg , m_nBaudrateDlg, m_nTimeRequestDlg,TRUE);
	CDialogEx::OnOK();
}



void CCommunicationPortDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (pFrame->m_SCIModule.get_PortOpen())
	{
		pFrame->m_SCIModule.put_PortOpen(0);//�رմ���
	}
	UpdateData(TRUE);
	CMCADoc* pDoc = (CMCADoc*)pFrame->GetActiveDocument();
	pDoc->UpdateCommunicationDlgInfo(m_nCommDlg , m_nBaudrateDlg, m_nTimeRequestDlg,TRUE);
	m_nPortFlag = FALSE;
	CDialogEx::OnCancel();
}
