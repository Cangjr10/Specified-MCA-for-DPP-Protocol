// ������������� Microsoft Visual C++ ������ IDispatch ��װ��



// ע��: ��Ҫ�޸Ĵ��ļ������ݡ����������
//  Microsoft Visual C++ �������ɣ������޸Ľ������ǡ�


#include "stdafx.h"
#include "mscomm.h"

/////////////////////////////////////////////////////////////////////////////
// CMscomm

IMPLEMENT_DYNCREATE(CMscomm, CWnd)

/////////////////////////////////////////////////////////////////////////////
// CMscomm ����
void CMscomm::SendByte(byte single_byte)
{
try{
	CByteArray byte_to_be_send ;
	byte_to_be_send.Add(single_byte);
	put_Output(COleVariant(byte_to_be_send));
}
catch (...)
{
	AfxMessageBox(_T("CMscomm::SendByte��"));
}
}
void CMscomm::SendArray(byte* array_byte,UINT n)
{
try{
	for (UINT i = 0;i < n; i++)
	{
		SendByte(array_byte[i]);
	}
}
catch (...)
{
	AfxMessageBox(_T("CMscomm::SendArray��"));
}
}
/////////////////////////////////////////////////////////////////////////////
// CMscomm ����
