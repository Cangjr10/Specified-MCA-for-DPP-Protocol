// 计算机生成了由 Microsoft Visual C++ 创建的 IDispatch 包装类



// 注意: 不要修改此文件的内容。如果此类由
//  Microsoft Visual C++ 重新生成，您的修改将被覆盖。


#include "stdafx.h"
#include "mscomm.h"

/////////////////////////////////////////////////////////////////////////////
// CMscomm

IMPLEMENT_DYNCREATE(CMscomm, CWnd)

/////////////////////////////////////////////////////////////////////////////
// CMscomm 属性
void CMscomm::SendByte(byte single_byte)
{
try{
	CByteArray byte_to_be_send ;
	byte_to_be_send.Add(single_byte);
	put_Output(COleVariant(byte_to_be_send));
}
catch (...)
{
	AfxMessageBox(_T("CMscomm::SendByte！"));
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
	AfxMessageBox(_T("CMscomm::SendArray！"));
}
}
/////////////////////////////////////////////////////////////////////////////
// CMscomm 操作
