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
	CByteArray byte_to_be_send ;
	byte_to_be_send.Add(single_byte);
	put_Output(COleVariant(byte_to_be_send));
}
void CMscomm::SendArray(byte* array_byte,UINT n)
{
	for (UINT i = 0;i < n; i++)
	{
		SendByte(array_byte[i]);
	}
}
/////////////////////////////////////////////////////////////////////////////
// CMscomm ����
