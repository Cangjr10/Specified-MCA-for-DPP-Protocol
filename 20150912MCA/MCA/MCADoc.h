
// MCADoc.h : CMCADoc 类的接口
//


#pragma once
#include "mscomm.h"
#include "stdafx.h"
#include "CommunicationPortDlg.h"
#include "Spectrum.h"
//#include "MainFrm.h"
enum _tagCommand_Flag
{
	S_NULL = 0,
	S_Connection = 1, 
	S_StartPick = 2, 
	S_Pause = 3, 
	S_Restart = 4, 
	S_Configuration = 5,
	S_Download = 6,
	S_Diagnostic = 7
} ;
class CMCADoc : public CDocument
{
protected: // 仅从序列化创建
	CMCADoc();
	DECLARE_DYNCREATE(CMCADoc)
// 特性
public:
	
// 操作
public:
	void MSComm_Decode(COleSafeArray safearray_input);
	BOOL Decode_IsMatch(byte newelement,byte* RightKey,UINT KeyNumber);//新来的钥匙，正确钥匙，正确钥匙的个数
	void GetActiveCommunicationDlg(CCommunicationPortDlg* _p_CommunicatDlg)	{p_CommunicatDlg = _p_CommunicatDlg;}//获取活动对话框指针，从而保存当前参数信息
	void SetCommandFlag(_tagCommand_Flag _command)	{CommandFlag = _command;}
	void UpdateCommunicationDlgInfo(int &m_nCommDlg ,int &m_nBaudrateDlg , UINT &m_nTimeRequestDlg , BOOL flag) 
	{
		if (flag == FALSE) // 用文件数据更新窗口数据
		{
			m_nCommDlg = m_nComm;
			m_nBaudrateDlg = m_nBaudrate;
			m_nTimeRequestDlg = m_nTimeRequest;
		}
		else // 保存当前配置
		{
			m_nComm = m_nCommDlg;
			m_nBaudrate = m_nBaudrateDlg;
			m_nTimeRequest = m_nTimeRequestDlg;
		}
	}
	CSpectrum& GetActiveSpectrum(void) { return Spectrum_Active;}//复制谱文件，用于显示，const
 	void  GetActiveSpectrumCopy(CSpectrum& _Spectrum)	
	{
// 		_Spectrum.SetSpectrumData(Spectrum_Active.GetSpectrumData());
// 		for (UINT i = 0;i<Spectrum_Active.GetROINumber();i++)
// 		{
// 			_Spectrum.AddROI(Spectrum_Active.GetSpectrumROI(i));
// 		}
// 		UINT index = 0;
// 		Spectrum_Active.GetSelectedROIIndex(index);
// 		_Spectrum.SetSelectedROIIndex(index);
		_Spectrum = Spectrum_Active;
	}	
	UINT32 GetSpectrumChannel(void){return Channelnumber;}
	void SetSpectruumChannel(UINT32 _channel) {Channelnumber = _channel; }
	void SaveXMLFile(void);
	void SaveSpectrumWithTemperature(CString filepath,CString filename);
//	CSpectrum GetActiveSpectrum(void) const { return Spectrum_Active;}//复制谱文件，用于显示，const
// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CMCADoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
	
#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual void SetTitle(LPCTSTR lpszTitle);
	DECLARE_EVENTSINK_MAP()

public:
	CROIManaging* pDoc_ROIManageing;
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
private:
	_tagCommand_Flag	CommandFlag;
	CString str_DeviceInfo;
	CCommunicationPortDlg* p_CommunicatDlg;
	int m_nComm;
	int m_nBaudrate;
	UINT32 Channelnumber;
	UINT m_nTimeRequest;
	BOOL IsMatchedFlag;
	CSpectrum Spectrum_Active;
	vector<byte> ByteStream_Spectrum;//用于数据缓存处理
	vector<byte> Diagnostic_cache;
	vector<byte> Status_data;
	vector<UINT32> Stream_Spectrum;//用于临时谱数据存储
	UINT32 FileCounter;
	//vector<UINT32> * SpectraList;
	//UINT SpectrumNumber;
	struct XML_format
	{
		CString Property;
		CString Unit;
		CString Value;
	};
	vector<XML_format> Dectetor_XML;
public:
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	afx_msg void OnFileSaveAs();
};
