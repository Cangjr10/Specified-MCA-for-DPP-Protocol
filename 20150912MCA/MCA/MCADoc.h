
// MCADoc.h : CMCADoc ��Ľӿ�
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
protected: // �������л�����
	CMCADoc();
	DECLARE_DYNCREATE(CMCADoc)
// ����
public:
	
// ����
public:
	void MSComm_Decode(COleSafeArray safearray_input);
	BOOL Decode_IsMatch(byte newelement,byte* RightKey,UINT KeyNumber);//������Կ�ף���ȷԿ�ף���ȷԿ�׵ĸ���
	void GetActiveCommunicationDlg(CCommunicationPortDlg* _p_CommunicatDlg)	{p_CommunicatDlg = _p_CommunicatDlg;}//��ȡ��Ի���ָ�룬�Ӷ����浱ǰ������Ϣ
	void SetCommandFlag(_tagCommand_Flag _command)	{CommandFlag = _command;}
	void UpdateCommunicationDlgInfo(int &m_nCommDlg ,int &m_nBaudrateDlg , UINT &m_nTimeRequestDlg , BOOL flag) 
	{
		if (flag == FALSE) // ���ļ����ݸ��´�������
		{
			m_nCommDlg = m_nComm;
			m_nBaudrateDlg = m_nBaudrate;
			m_nTimeRequestDlg = m_nTimeRequest;
		}
		else // ���浱ǰ����
		{
			m_nComm = m_nCommDlg;
			m_nBaudrate = m_nBaudrateDlg;
			m_nTimeRequest = m_nTimeRequestDlg;
		}
	}
	CSpectrum& GetActiveSpectrum(void) { return Spectrum_Active;}//�������ļ���������ʾ��const
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
//	CSpectrum GetActiveSpectrum(void) const { return Spectrum_Active;}//�������ļ���������ʾ��const
// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CMCADoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
	
#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
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
	vector<byte> ByteStream_Spectrum;//�������ݻ��洦��
	vector<byte> Diagnostic_cache;
	vector<byte> Status_data;
	vector<UINT32> Stream_Spectrum;//������ʱ�����ݴ洢
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
