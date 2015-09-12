// ControlView.cpp : 实现文件
//

#include "stdafx.h"
#include "MCA.h"
#include "ControlView.h"
#include "MainFrm.h"
#include "MCADoc.h"
#include "DetailView.h"
#include "TotalView.h"
#include "GlobalVarDef.h"
// CControlView

IMPLEMENT_DYNCREATE(CControlView, CFormView)

CControlView::CControlView()
	: CFormView(CControlView::IDD)
	, m_nDeviceID(_T("Device001"))
	, m_nDeviceType(_T("国产LaBr3"))
	, m_nMonitorObject(_T("Cs-137"))
	, m_nLongitude(116.33)
	, m_nLatitude(40.00)
	, m_ntemperature(34)
	, m_nHumidity(56)
	, m_nHV(700)
	, m_nPickInterval(1)
	, m_nStartTime(_T("2015/01/26 9:54"))
	, m_nChannemNumber(0)
	, m_nAccTime(0)
	, m_nLiveTime(0)
	, m_nActivity_Cs137(0)
{

}

CControlView::~CControlView()
{
}

void CControlView::DoDataExchange(CDataExchange* pDX)
{
	try
	{
		CFormView::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_TREE_INFO, m_TreeCtr);
	DDX_Text(pDX, IDC_DEVICEID, m_nDeviceID);
	DDX_Text(pDX, IDC_DEVICETYPE, m_nDeviceType);
	DDX_Text(pDX, IDC_MONITOROBJECT, m_nMonitorObject);
	DDX_Text(pDX, IDC_LONGITUDE, m_nLongitude);
	DDX_Text(pDX, IDC_LATITUDE, m_nLatitude);
	DDX_Text(pDX, IDC_TEMPERATURE, m_ntemperature);
	DDX_Text(pDX, IDC_HUMIDITY, m_nHumidity);
	DDX_Text(pDX, IDC_HIGHVOLTAGE, m_nHV);
	DDX_Control(pDX, IDC_CHANNELNUMBER, m_SpectrumChannel);
	DDX_Text(pDX, IDC_PICKINTERVAL, m_nPickInterval);
	DDX_Text(pDX, IDC_BEGINTIME, m_nStartTime);
	DDX_CBIndex(pDX, IDC_CHANNELNUMBER, m_nChannemNumber);
	DDX_Text(pDX, IDC_ACCTIME, m_nAccTime);
	DDX_Text(pDX, IDC_LIVETIME, m_nLiveTime);
	DDX_Text(pDX, IDC_CsACTIVITY, m_nActivity_Cs137);
	}
	catch(...)
	{
		AfxMessageBox(_T("CControlView::DoDataExchange!"));
	}
}

BEGIN_MESSAGE_MAP(CControlView, CFormView)
	
	ON_CBN_SELENDOK(IDC_CHANNELNUMBER, &CControlView::OnCbnSelendokChannelnumber)
END_MESSAGE_MAP()


// CControlView 诊断

#ifdef _DEBUG
void CControlView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CControlView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CControlView 消息处理程序


void CControlView::OnInitialUpdate()
{
	try{
	CFormView::OnInitialUpdate();
	Str_ChannelNumber.resize(0);
	Str_ChannelNumber.push_back(_T("1024"));
	Str_ChannelNumber.push_back(_T("2048"));
	Str_ChannelNumber.push_back(_T("4096"));
	Str_ChannelNumber.push_back(_T("8192"));
	m_SpectrumChannel.ResetContent();
	for (int i=0;i < static_cast<int>(Str_ChannelNumber.size());i++)
	{
		m_SpectrumChannel.AddString(Str_ChannelNumber[i]);
	}
	m_nChannemNumber = 1;
	UpdateData(FALSE);
	}
	catch(...)
	{
		AfxMessageBox(_T("OnCbnSelendokChannelnumber！"));
	}
// 	m_TreeCtr.DeleteAllItems();
// 	m_TreeCtr.SetBkColor(RGB(240,240,240));
// 	CFont m_newFont;
// 	m_newFont.CreatePointFont(180, _T("楷体")); 
// 	m_TreeCtr.SetFont(&m_newFont,FALSE);
// 	MarkTreeItemNum[0]=m_TreeCtr.InsertItem(strTextInfo[0],0,0);
// 	MarkTreeItemNum[1]=m_TreeCtr.InsertItem(strTextInfo[1],MarkTreeItemNum[0],TVI_LAST);
// 	MarkTreeItemNum[2]=m_TreeCtr.InsertItem(strTextInfo[2]+nNumInfo[2],MarkTreeItemNum[0],TVI_LAST);
// 	MarkTreeItemNum[3]=m_TreeCtr.InsertItem(strTextInfo[3]+nNumInfo[3],MarkTreeItemNum[0],TVI_LAST);
// 	m_TreeCtr.Expand(MarkTreeItemNum[0],TVE_EXPAND);
// 	MarkTreeItemNum[4]=m_TreeCtr.InsertItem(strTextInfo[4],0,0);
// 	MarkTreeItemNum[5]=m_TreeCtr.InsertItem(strTextInfo[5],MarkTreeItemNum[4],TVI_LAST);
// 	MarkTreeItemNum[6]=m_TreeCtr.InsertItem(strTextInfo[6],MarkTreeItemNum[4],TVI_LAST);
// 	MarkTreeItemNum[7]=m_TreeCtr.InsertItem(strTextInfo[7]+nNumInfo[7],MarkTreeItemNum[4],TVI_LAST);
// 	MarkTreeItemNum[8]=m_TreeCtr.InsertItem(strTextInfo[8]+nNumInfo[8],MarkTreeItemNum[4],TVI_LAST);
// 	MarkTreeItemNum[9]=m_TreeCtr.InsertItem(strTextInfo[9]+nNumInfo[9],MarkTreeItemNum[4],TVI_LAST);
// 	m_TreeCtr.Expand(MarkTreeItemNum[4],TVE_EXPAND); //不展开屏蔽该语句
//  	MarkTreeItemNum[10]=m_TreeCtr.InsertItem(strTextInfo[10]+nNumInfo[10],0,0);
// 	MarkTreeItemNum[11]=m_TreeCtr.InsertItem(strTextInfo[11]+nNumInfo[11],MarkTreeItemNum[10],TVI_LAST);
// 	MarkTreeItemNum[12]=m_TreeCtr.InsertItem(strTextInfo[12]+nNumInfo[12],MarkTreeItemNum[10],TVI_LAST);
//  	m_TreeCtr.Expand(MarkTreeItemNum[10],TVE_EXPAND);
// 	MarkTreeItemNum[13]=m_TreeCtr.InsertItem(strTextInfo[13],0,0);
// 	MarkTreeItemNum[14]=m_TreeCtr.InsertItem(strTextInfo[14]+nNumInfo[14],MarkTreeItemNum[13],TVI_LAST);
// 	MarkTreeItemNum[15]=m_TreeCtr.InsertItem(strTextInfo[15]+nNumInfo[15],MarkTreeItemNum[13],TVI_LAST);
// 	MarkTreeItemNum[16]=m_TreeCtr.InsertItem(strTextInfo[16]+nNumInfo[16],MarkTreeItemNum[13],TVI_LAST);
// 	MarkTreeItemNum[17]=m_TreeCtr.InsertItem(strTextInfo[17]+nNumInfo[17],MarkTreeItemNum[13],TVI_LAST);
// 	m_TreeCtr.Expand(MarkTreeItemNum[13],TVE_EXPAND);
	// TODO: 在此添加专用代码和/或调用基类
}




void CControlView::OnCbnSelendokChannelnumber()
{
	// TODO: 在此添加控件通知处理程序代码
	try{
	CMCADoc* pMCADoc = (CMCADoc*)m_pDocument;
	UpdateData(TRUE);
	UINT32 temp = pMCADoc->GetSpectrumChannel();
	switch (m_nChannemNumber)
	{
	case 0:
		pMCADoc->SetSpectruumChannel(1024);	break;
	case 1:
		pMCADoc->SetSpectruumChannel(2048); break;
	case 2:
		pMCADoc->SetSpectruumChannel(4096); break;
	case 3:
		pMCADoc->SetSpectruumChannel(8192); break;
	default:
		break;
	}
	}
	catch(...)
	{
		AfxMessageBox(_T("OnCbnSelendokChannelnumber！"));
	}
}


