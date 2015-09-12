
// MCADoc.cpp : CMCADoc ���ʵ��
//
#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MCA.h"
#include "MainFrm.h"
#endif

#include "MCADoc.h"
//#include "MyTinyXML.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMCADoc

IMPLEMENT_DYNCREATE(CMCADoc, CDocument)

BEGIN_MESSAGE_MAP(CMCADoc, CDocument)
	
	ON_COMMAND(ID_FILE_SAVE_AS, &CMCADoc::OnFileSaveAs)
END_MESSAGE_MAP()


// CMCADoc ����/����

CMCADoc::CMCADoc()
	:IsMatchedFlag(FALSE)
	,m_nComm(2)
	,m_nBaudrate(5)
	,m_nTimeRequest(5000)
	,Channelnumber(2048)
	,FileCounter(1)
{
try{
	// TODO: �ڴ����һ���Թ������
	pDoc_ROIManageing = NULL;
	XML_format Dectetor_XML_exam[]=
	{   //����								//��λ			//��ֵ
		_T("DeviceID"),						_T(""),		_T("Device001"),				//�豸���:001
		_T("MonitorObject"),				_T(""),		_T("Cs137,Co60"),					//�������
		_T("GammaEnergy"),					_T(""),		_T("661.66,1173.24,1332.51,657.75"),
		_T("Efficiency"),					_T(""),		_T("0.264,0.282,0.278,0.295"),
		_T("Devicename"),					_T(""),		_T("Underwater Gamma Spectrometer"),
		_T("DeviceStatus"),					_T(""),		_T("0"),//0��ʾ��������
		_T("DeviceType"),					_T(""),		_T("����LaBr3,3inch"),		//�豸�ͺţ�LaBr3
		_T("BeginTime"),					_T(""),		_T("0"),			//��ʼʱ��
		_T("EndTime"),						_T(""),		_T("0"),			//����ʱ��
		_T("Longitude"),					_T(""),		_T("116.33"),					//���� 116.33��
		_T("Latitude"),						_T(""),		_T("40.00"),					//γ�� 40.00��
		_T("Temperature"),					_T("C"),	_T("34"),						//�¶�
		_T("Humidity"),						_T("%"),	_T("56"),						//ʪ��
		_T("HighVoltage"),					_T("V"),	_T("697"),						//��ѹֵ
		_T("IntrinsicTime"),				_T("s"),	_T("241974"),					//���ײ���ʱ��
		_T("IntrinsicSpectrumData"),		_T(""),		_T(""),							//������������
		_T("LiveSpectrumData"),				_T(""),		_T(""),							//ʵ����������
		_T("CalibrationCoefficient"),		_T(""),		_T("0.000021898,1.4341,0.5072 "),//��׼�������̶�����
		_T("FinalIntrinsicSpectrum"),		_T(""),		_T(""),//����֮���1000��������
		_T("FinalLiveSpectrum"),			_T(""),		_T(""),//����֮���1000��ʵ����
		_T("BackgroundSpectrum"),			_T(""),		_T(""),//SNIP�۳��ı�����
		_T("CalculatedActivity"),			_T("Bq/L"),	_T("0"),		
	};
	int NUMLINES = sizeof(Dectetor_XML_exam)/sizeof(Dectetor_XML_exam[0]);//������Ŀ
	for (int i=0;i<NUMLINES;i++)
	{
		Dectetor_XML.push_back(Dectetor_XML_exam[i]);
	}
}
catch(...)
{
	AfxMessageBox(_T("CMCADoc::CMCADoc��"));
}
}

CMCADoc::~CMCADoc()
{
}

BOOL CMCADoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CMCADoc ���л�

void CMCADoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CMCADoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void CMCADoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CMCADoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMCADoc ���

#ifdef _DEBUG
void CMCADoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMCADoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMCADoc ����


void CMCADoc::SetTitle(LPCTSTR lpszTitle)
{
	// TODO: �ڴ����ר�ô����/����û���


	CDocument::SetTitle(_T("MCA"));
}
BEGIN_EVENTSINK_MAP(CMCADoc, CDocument)

END_EVENTSINK_MAP()
//����һЩͨѶ��־
byte Connection_Start[] = {0xFF ,0xFF ,0xFF ,0x00 ,0xFF ,0xFF ,0xFF ,0xFF};//Ѱ���豸��Ϣ����ʼ��־
//byte Data_Acquisition[] = {0xF5 ,0xFA ,0x81 ,0x0C ,0x60 ,0x40};//8192����������+״̬���ر�־
byte Data_Acquisition[] = {0xF5 ,0xFA ,0x81 ,0x08 ,0x18 ,0x40};//8192����������+״̬���ر�־
byte Diagnostic_strat[] = {0xF5 ,0xFA ,0x82 ,0x05 ,0x01 ,0x00};//�������ݷ��ر�־
byte ACK_OK[] = {0xF5 ,0xFA ,0xFF ,0x00 ,0x00 ,0x00,0xFD ,0x12};//Acknowledge package���ر�־
void CMCADoc::MSComm_Decode(COleSafeArray safearray_input)
{
try{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	long len = safearray_input.GetOneDimSize();		//���ݵ���Ч����
	for (long k = 0; k < len; k++)
	{
		BYTE new_element;//��ʱ�洢�µ��ֽ�
		safearray_input.GetElement(&k, &new_element);
		switch(CommandFlag)
		{
		case S_Connection://�����ڼ�
			{
				//Is to show?
				if (IsMatchedFlag == FALSE && Decode_IsMatch(new_element,Connection_Start,sizeof(Connection_Start)))
				{
					IsMatchedFlag = TRUE; 
					break;
				}
				if (IsMatchedFlag == TRUE)
				{
					if (new_element == 0)//���з���־��Ϣ��β
					{
						IsMatchedFlag = FALSE;
						str_DeviceInfo +="\r\n";
						str_DeviceInfo +="Connection:RS232-COM";
						CString str;
						str.Format(_T("%s%d"),str_DeviceInfo,m_nComm+1);
						p_CommunicatDlg->m_DeviceInfo.SetWindowTextW(str);
						CommandFlag = S_NULL;
						str_DeviceInfo = "";
					}
					else
						str_DeviceInfo += new_element;				
				}
			}
			break;
		case S_StartPick://������Ӧ
			if (IsMatchedFlag == FALSE && Decode_IsMatch(new_element,ACK_OK,sizeof(ACK_OK)))
			{
				CommandFlag = S_NULL; //
				pFrame->Measure_SpectrumRequest();//��ʼ���ײɼ�
			}
			break;
		case S_Restart:
			if (IsMatchedFlag == FALSE && Decode_IsMatch(new_element,ACK_OK,sizeof(ACK_OK)))
			{
				CommandFlag = S_NULL; 
				//pFrame->Measure_SpectrumRequest();//��ʼ���ײɼ�
			}		
			break;
		case S_Pause:
			if (IsMatchedFlag == FALSE && Decode_IsMatch(new_element,ACK_OK,sizeof(ACK_OK)))
			{
				CommandFlag = S_NULL; 
			}		
			break;
		case S_Download:
			if (IsMatchedFlag == FALSE && Decode_IsMatch(new_element,Data_Acquisition,sizeof(Data_Acquisition)))
			{
				IsMatchedFlag = TRUE; 
				break;
			}
			if (IsMatchedFlag == TRUE)
			{
				ByteStream_Spectrum.push_back(new_element);
				if (ByteStream_Spectrum.size() == Channelnumber*3+64+2)//��������+״̬����+У��λ
				{
					//�����ݴ洢ת��
					Stream_Spectrum.resize(0);
					Status_data.resize(0);
					for (int i=0;i<Channelnumber;i++)
					{
						UINT32 a = 0;
						char* hehe = (char*)&a;
						*hehe = ByteStream_Spectrum[3*i+0];//���ֽ�
						*(hehe+1)=ByteStream_Spectrum[3*i+1];
						*(hehe+2)=ByteStream_Spectrum[3*i+2];
						Stream_Spectrum.push_back(a);
					}
					//����״̬��Ϣ���ڲ�����live time����Ҫ��Ϣ
					for (int i=Channelnumber*3;i<Channelnumber*3+64;i++)
					{
						Status_data.push_back(ByteStream_Spectrum[i]);
					}
					UINT32 time = 0;//ms
					char* hehe = (char*)&time;
					*hehe = Status_data[20];//����ʱ��
					*(hehe+1)=Status_data[21];
					*(hehe+2)=Status_data[22];
					*(hehe+3)=Status_data[23];
					//�ɵ�ǰʱ��Ͳ���ʱ����㿪ʼʱ��
					time = time/1000;
 					unsigned short day,hour,minute,second;
					day = (unsigned short)time/24/3600;
					hour = (unsigned short)((time-day*24*3600)/3600);
					minute = (unsigned short)((time - day*24*3600-hour*3600)/60);
					second = (unsigned short)(time - day*24*3600-hour*3600-minute*60);
					CTime CurrentTime,StartTime;
					CurrentTime=CTime::GetCurrentTime(); 
					CString endtime_str;
					endtime_str=CurrentTime.Format(_T("%Y/%m/%d %X"));
					CTimeSpan Time_Diff(day,hour,minute,second);
					StartTime = CurrentTime-Time_Diff; 
					CString starttime_str;
					starttime_str=StartTime.Format(_T("%Y/%m/%d %X"));
					Spectrum_Active.SetStartTime_Str(starttime_str);
					Spectrum_Active.SetEndTime_Str(endtime_str);
					Spectrum_Active.SetMeasureTime(UINT32(time));
					*hehe = Status_data[16];//��Ч����ʱ��
					*(hehe+1)=Status_data[17];
					*(hehe+2)=Status_data[18];
					*(hehe+3)=Status_data[19];
					Spectrum_Active.SetLiveTime(UINT32(time/1000));
					Spectrum_Active.SetSpectrumData(Stream_Spectrum);
					//Spectrum_Active.ClearAllROI();	
					//CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
					CTotalView* pTotalVIew_temp = (CTotalView*) pFrame->pTotalVIew;
					CDetailView* pDetialVIew_temp = (CDetailView*) pFrame->pDetailView;
					pTotalVIew_temp->Invalidate(FALSE);
					pDetialVIew_temp->Invalidate(FALSE);
					CommandFlag = S_NULL;
					ByteStream_Spectrum.resize(0);//���������ݽ����ջ���������
					IsMatchedFlag = FALSE;
					pFrame->Measure_Diagnostic();//�������ݻ�ȡ��ϣ���ȡ�¶���Ϣ
					CControlView* pControlVIew_temp = (CControlView*) pFrame->pControlView;
 					pControlVIew_temp->m_nAccTime = Spectrum_Active.GetMeasureTime();
 					pControlVIew_temp->m_nLiveTime = Spectrum_Active.GetLiveTime();
					pControlVIew_temp->m_nStartTime = Spectrum_Active.GetStartTime_Str();
					pControlVIew_temp->m_nActivity_Cs137 = Spectrum_Active.GetCsActivity();
					pControlVIew_temp->UpdateData(FALSE);
				}
			}
			break;
		case S_Diagnostic:
			if (IsMatchedFlag == FALSE && Decode_IsMatch(new_element,Diagnostic_strat,sizeof(Diagnostic_strat)))
			{
				IsMatchedFlag = TRUE; 
				break;
			}
			if (IsMatchedFlag == TRUE)
			{
				ByteStream_Spectrum.push_back(new_element);
				if (ByteStream_Spectrum.size() == 258)//�¶ȼ�����ݻ�ȡ���
				{
					Diagnostic_cache.resize(0);
					for (int i=0;i<258;i++)
					{
						Diagnostic_cache.push_back(ByteStream_Spectrum[i]);
					}
					CommandFlag = S_NULL;
					ByteStream_Spectrum.resize(0);//���������ݽ����ջ���������
					IsMatchedFlag = FALSE;
					//��ȡ�¶�֮��������ݴ洢
					CString filepath=_T("D:/MonitorData/LiveData/");
					CTime CurrentTime;
					CurrentTime=CTime::GetCurrentTime(); 
					CString CurrentTime_str;
					CurrentTime_str=CurrentTime.Format(_T("%Y%m%d %H_%M_%S"));
/*					FileCounter++;*/ 
					SaveSpectrumWithTemperature(filepath,CurrentTime_str);
					SaveXMLFile();
					//ÿ�ζ�ʱ��Ͼ���һ���ף�
					pFrame->Measure_Restart();
					if (Spectrum_Active.GetMeasureTime() > 7*24*3600)//����ʱ�䳬��7�죬����
					{
						pFrame->Measure_Restart();
					}
				}
			}
			break;
		default:
			break;
		}
		//pFrame->m_SCIModule.SendByte(new_element);
	}
	}
		catch (...)
		{
			AfxMessageBox(_T("DATA TRANSFER ERROR��"));
		}

}
BOOL CMCADoc::Decode_IsMatch(byte newelement,byte* RightKey,UINT KeyNumber)
{
try{
	static vector<byte> Key; 
	//ת��RightKey��ʽ�Է���Ƚ�
	vector<byte>_RightKey;
	_RightKey.resize(KeyNumber);
	for (UINT i = 0; i<KeyNumber; i++)
	{
		_RightKey[i]=RightKey[i];
	}
//	assert(Key.size()<KeyNumber+1);
	if (Key.size()==KeyNumber)//�Ѿ����㹻��Կ�ף����򲻿�����Ҫ����һ��Կ��
	{
		Key.erase(Key.begin());
		Key.push_back(newelement);
		if (Key == _RightKey)//Կ��ƥ��
		{
			Key.resize(0);
			return TRUE;
		}
		else
			return FALSE;
	}
	else if (Key.size()<KeyNumber)//Կ����Ŀ������������ȡԿ��
	{
		Key.push_back(newelement);
		if (Key.size()==KeyNumber)//����һ��Կ��֮��Կ����Ŀ�㹻�������Ƿ�ƥ��
		{
			if (Key == _RightKey)//Կ��ƥ��
			{
				Key.resize(0);
				return TRUE;//Կ����ȷ������
			}
			else
				return FALSE;//Կ�ײ���ȷ
		}
		else
			return FALSE;//����һ��Կ��Կ�ף���Ŀ���ɲ���������
	}
	else
		return FALSE;
}
catch(...)
{
	AfxMessageBox(_T("CMCADoc::CMCADoc��"));
}
}




BOOL CMCADoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  �ڴ������ר�õĴ�������
	try
	{
		CStdioFile myfile(lpszPathName,CFile::modeRead|CFile::typeText);//���ļ�;
		CString strTemp = _T("");
		BOOL data_flag = FALSE;
		BOOL info_flag = FALSE;
		//��ȡ�������ļ�
		vector<UINT32> Spectrum_temp;
		Spectrum_temp.resize(0);
		while(myfile.ReadString(strTemp))
		{
			if (strTemp == _T("<<DATA_SPECTRUM>>"))
			{
				data_flag = TRUE;
				continue;
			}
			if (strTemp == _T("<<END_SPECTRUM>>"))
			{
				data_flag = FALSE;
				continue;
			}
			if (data_flag)
			{
				Spectrum_temp.push_back((UINT32)StrToInt(strTemp));
			}
			if (strTemp == _T("<<DATA_INFO>>"))
			{
				info_flag = TRUE;
				continue;
			}
			if (strTemp == _T("<<END_INFO>>"))
			{
				info_flag = FALSE;
				continue;
			}
			if (info_flag)//��Ϣ��ȡ��ʱ���
			{
				if (strTemp.Find(_T("LIVE_TIME"),0) != -1)
				{
					int pos = strTemp.Find(_T("-"),0);
					int nlength = strTemp.GetLength();
					CString live_time_str = strTemp.Right(nlength - pos-2);
					Spectrum_Active.SetLiveTime((UINT32)StrToInt(live_time_str));
				}
				if (strTemp.Find(_T("START_TIME"),0) != -1)
				{
					int pos = strTemp.Find(_T("-"),0);
					int nlength = strTemp.GetLength();
					CString start_time = strTemp.Right(nlength - pos-2);
					Spectrum_Active.SetStartTime_Str((start_time));
				}
				if (strTemp.Find(_T("MEASURE_TIME"),0) != -1)
				{
					int pos = strTemp.Find(_T("-"),0);
					int nlength = strTemp.GetLength();
					CString measure_time_str = strTemp.Right(nlength - pos-2);
					Spectrum_Active.SetMeasureTime((UINT32)StrToInt(measure_time_str));
				}	
				if (strTemp.Find(_T("END_TIME"),0) != -1)
				{
					int pos = strTemp.Find(_T("-"),0);
					int nlength = strTemp.GetLength();
					CString end_time_str = strTemp.Right(nlength - pos-2);
					Spectrum_Active.SetEndTime_Str(end_time_str);
				}
				//����ʼʱ��CStringת��ΪCTime
// 				CString str_starttime = Spectrum_Active.GetStartTime_Str();
// 				COleDateTime   tm;   
// 				tm.ParseDateTime(str_starttime);   
// 				SYSTEMTIME   st;   
// 				tm.GetAsSystemTime(st);   
// 				CTime   _StartTime(st); 
// 				//���ݲ���ʱ�����ʼʱ�� �����ʱ��
// 				UINT32 time = Spectrum_Active.GetMeasureTime();
// 				unsigned short day,hour,minute,second;
// 				day = (unsigned short)time/24/3600;
// 				hour = (unsigned short)((time-day*24*3600)/3600);
// 				minute = (unsigned short)((time - day*24*3600-hour*3600)/60);
// 				second = (unsigned short)(time - day*24*3600-hour*3600-minute*60);
// 				CTimeSpan Time_Diff(day,hour,minute,second); 
// 				CTime _EndTime;
// 				_EndTime = _StartTime+Time_Diff;
// 				CString endtime_str;
// 				endtime_str=_EndTime.Format(_T("%Y/%m/%d %X"));
// 				Spectrum_Active.SetEndTime_Str(endtime_str);
			}
		}
		Spectrum_Active.SetSpectrumData(Spectrum_temp);
		//Spectrum_Active.ClearAllROI();
		myfile.Close();
		CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
		CControlView* pControlVIew_temp = (CControlView*) pFrame->pControlView;
		pControlVIew_temp->m_nAccTime = Spectrum_Active.GetMeasureTime();
		pControlVIew_temp->m_nLiveTime = Spectrum_Active.GetLiveTime();
		pControlVIew_temp->m_nStartTime = Spectrum_Active.GetStartTime_Str();
		pControlVIew_temp->m_nActivity_Cs137 = Spectrum_Active.GetCsActivity();
		pControlVIew_temp->UpdateData(FALSE);
		CTotalView* pTotalVIew_temp = (CTotalView*) pFrame->pTotalVIew;
		CDetailView* pDetialVIew_temp = (CDetailView*) pFrame->pDetailView;
		pTotalVIew_temp->Invalidate(FALSE);
		pDetialVIew_temp->Invalidate(FALSE);
	}
	catch (...)
	{
		AfxMessageBox(_T("CMCADoc::Decode_IsMatch��"));
	}
	return TRUE;
}


BOOL CMCADoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: �ڴ����ר�ô����/����û���
	
	return TRUE;
	//return CDocument::OnSaveDocument(lpszPathName);
}

void CMCADoc::SaveXMLFile(void)
{
try{
	int NUMLINES = Dectetor_XML.size();//������Ŀ
	//�洢XML�ļ�
	//	CStdioFile myfile(lpszPathName,CFile::modeCreate|CFile::modeReadWrite| CFile::typeText);
	CString filepath=_T("D:/MonitorData/LiveData/");
	filepath += Dectetor_XML[0].Value;
	filepath += ".XML";
	CStdioFile myfile(filepath,CFile::modeCreate|CFile::modeReadWrite| CFile::typeText);
	CString stringtitle=_T("");
	stringtitle+="<?xml version=\"1.0\" encoding=\"GB2312\"?>\n";//��һ�б���
	myfile.WriteString(stringtitle);
	CString root = _T("<MonitorData>\n");
	myfile.WriteString(root);
	CString info=_T("");
	for (int i=0;i<NUMLINES;i++)
	{
		if (Dectetor_XML[i].Property=="IntrinsicSpectrumData")//��������
		{
			CString str;
			str.Format(_T("  <%s>"),Dectetor_XML[i].Property);
			myfile.WriteString(str);
			CString spectrum_data_temp;
			spectrum_data_temp.Format(_T("%d"),Spectrum_Active.GetElement_IntrinsicSpectrumData(0));
			myfile.WriteString(spectrum_data_temp);
			for (int j=1;j<Channelnumber;j++)
			{
				spectrum_data_temp.Format(_T(",%d"),Spectrum_Active.GetElement_IntrinsicSpectrumData(j));
				myfile.WriteString(spectrum_data_temp);
			}
			str.Format(_T("</%s>\n"),Dectetor_XML[i].Property);
			myfile.WriteString(str);
			continue;
		}
		if (Dectetor_XML[i].Property=="LiveSpectrumData")//ʵʱ��������
		{
			CString str;
			str.Format(_T("  <%s>"),Dectetor_XML[i].Property);
			myfile.WriteString(str);
			CString spectrum_data_temp;
			spectrum_data_temp.Format(_T("%d"),Spectrum_Active.GetElement_LiveSpectrumData(0));
			myfile.WriteString(spectrum_data_temp);
			for (int j=1;j<Channelnumber;j++)
			{
				spectrum_data_temp.Format(_T(",%d"),Spectrum_Active.GetElement_LiveSpectrumData(j));
				myfile.WriteString(spectrum_data_temp);
			}
			str.Format(_T("</%s>\n"),Dectetor_XML[i].Property);
			myfile.WriteString(str);
			continue;
		}
		if (Dectetor_XML[i].Property=="FinalIntrinsicSpectrum")//����֮��ı�������
		{
			CString str;
			str.Format(_T("  <%s>"),Dectetor_XML[i].Property);
			myfile.WriteString(str);
			CString spectrum_data_temp;
			spectrum_data_temp.Format(_T("%.1f"),Spectrum_Active.GetElement_RebinedIntrinsicSpectrum(0));
			myfile.WriteString(spectrum_data_temp);
			for (int j=1;j<1000;j++)
			{
				spectrum_data_temp.Format(_T(",%.1f"),Spectrum_Active.GetElement_RebinedIntrinsicSpectrum(j));
				myfile.WriteString(spectrum_data_temp);
			}
			str.Format(_T("</%s>\n"),Dectetor_XML[i].Property);
			myfile.WriteString(str);
			continue;
		}
		if (Dectetor_XML[i].Property=="FinalLiveSpectrum")//����֮��ı�������
		{
			CString str;
			str.Format(_T("  <%s>"),Dectetor_XML[i].Property);
			myfile.WriteString(str);
			CString spectrum_data_temp;
			spectrum_data_temp.Format(_T("%.1f"),Spectrum_Active.GetElement_RebinedLiveSpectrum(0));
			myfile.WriteString(spectrum_data_temp);
			for (int j=1;j<1000;j++)
			{
				spectrum_data_temp.Format(_T(",%.1f"),Spectrum_Active.GetElement_RebinedLiveSpectrum(j));
				myfile.WriteString(spectrum_data_temp);
			}
			str.Format(_T("</%s>\n"),Dectetor_XML[i].Property);
			myfile.WriteString(str);
			continue;
		}
		if (Dectetor_XML[i].Property=="BackgroundSpectrum")//����֮��ı�������
		{
			CString str;
			str.Format(_T("  <%s>"),Dectetor_XML[i].Property);
			myfile.WriteString(str);
			CString spectrum_data_temp;
			spectrum_data_temp.Format(_T("%.1f"),Spectrum_Active.GetElement_SNIP_Background(0));
			myfile.WriteString(spectrum_data_temp);
			for (int j=1;j<1000;j++)
			{
				spectrum_data_temp.Format(_T(",%.1f"),Spectrum_Active.GetElement_SNIP_Background(j));
				myfile.WriteString(spectrum_data_temp);
			}
			str.Format(_T("</%s>\n"),Dectetor_XML[i].Property);
			myfile.WriteString(str);
			continue;
		}
		if (Dectetor_XML[i].Property=="CalculatedActivity")//���
		{
			CString str_activity;
			str_activity.Format(_T("%.2f"),Spectrum_Active.GetCsActivity());
			Dectetor_XML[i].Value = str_activity;
		}
		if (Dectetor_XML[i].Property=="BeginTime")//
		{
			Dectetor_XML[i].Value = Spectrum_Active.GetStartTime_Str();
		}
		if (Dectetor_XML[i].Property=="EndTime")//
		{
			Dectetor_XML[i].Value = Spectrum_Active.GetEndTime_Str();
		}
		if (Dectetor_XML[i].Unit!="")
		{
			info.Format(_T("  <%s Unit=\"%s\"> %s </%s>\n"),Dectetor_XML[i].Property,Dectetor_XML[i].Unit,Dectetor_XML[i].Value,Dectetor_XML[i].Property);
			//			myfile.WriteString(info);//����������������
			char *P1=NULL;
			if(P1)
			{
				delete P1;
				P1=NULL;
			}
			int strLen=info.GetLength();
			int len = WideCharToMultiByte(CP_ACP,0,info,info.GetLength(),NULL,0,NULL,NULL);
			P1=new char[len+1];
			WideCharToMultiByte(CP_ACP,0,info,info.GetLength(),P1,len,NULL,NULL);
			P1[len]='\0';
			myfile.Write(P1,len);
		}
		else
		{
			info.Format(_T("  <%s> %s </%s>\n"),Dectetor_XML[i].Property,Dectetor_XML[i].Value,Dectetor_XML[i].Property);
			/*			info+="\r\n";*/
			//			myfile.WriteString(info);
			char *P1=NULL;
			if(P1)
			{
				delete P1;
				P1=NULL;
			}
			int strLen=info.GetLength();
			int len = WideCharToMultiByte(CP_ACP,0,info,info.GetLength(),NULL,0,NULL,NULL);
			P1=new char[len+1];
			WideCharToMultiByte(CP_ACP,0,info,info.GetLength(),P1,len,NULL,NULL);
			P1[len]='\0';
			myfile.Write(P1,len);
		}

	}
	root = _T("</MonitorData>\n");
	myfile.WriteString(root);
	myfile.Close();
	}
	catch(...)
	{
		AfxMessageBox(_T("XML SAVE ERROR!"));
	}
}

void CMCADoc::SaveSpectrumWithTemperature(CString filepath,CString filename)
{
try{
	CString filepath_total = _T("");
	filepath_total+=filepath;
	filepath_total+=filename;
	filepath_total+=".txt";
	CStdioFile myfile(filepath_total,CFile::modeCreate|CFile::modeReadWrite| CFile::typeText);
	//�洢��������
// 	CString test=_T("<<DATA_Spectrum>>\n");
// 	myfile.Write(test,sizeof(test));
	CString data_str = _T("");
	myfile.WriteString(_T("<<DATA_INFO>>\n"));
	myfile.WriteString(_T("BEGIN_TIME - "));  myfile.WriteString(Spectrum_Active.GetStartTime_Str());myfile.WriteString(_T("\n"));
	myfile.WriteString(_T("END_TIME - "));  myfile.WriteString(Spectrum_Active.GetEndTime_Str());myfile.WriteString(_T("\n"));
	myfile.WriteString(_T("MEASURE_TIME - ")); data_str.Format(_T("%d\n"),Spectrum_Active.GetMeasureTime()); myfile.WriteString(data_str);
	myfile.WriteString(_T("LIVE_TIME - ")); data_str.Format(_T("%d\n"),Spectrum_Active.GetLiveTime()); myfile.WriteString(data_str);
	myfile.WriteString(_T("<<END_INFO>>\n"));
	myfile.WriteString(_T("<<DATA_SPECTRUM>>\n"));
	
	for (int i=0;i<Spectrum_Active.GetOriginSpectrumSize();i++)
	{
		data_str.Format(_T("%d\n"),Spectrum_Active.GetElement_LiveSpectrumData(i));
		myfile.WriteString(data_str);
	}
	myfile.WriteString(_T("<<END_SPECTRUM>>\n"));

	//��������״̬��Ϣ
	myfile.WriteString(_T("<<Data_Status>>\n"));
	for (int i=0;i<Status_data.size();i++)
	{
		data_str.Format(_T("%d\n"),Status_data[i]);
		myfile.WriteString(data_str);
	}
	myfile.WriteString(_T("<<END_Status>>\n"));
	//�洢�¶���Ϣ
	myfile.WriteString(_T("<<Data_Diagonostic>>\n"));
	for (int i=0;i<Diagnostic_cache.size();i++)
	{
		data_str.Format(_T("%d\n"),Diagnostic_cache[i]);
		myfile.WriteString(data_str);
	}
	myfile.WriteString(_T("<<END_Diagnostic>>"));
	
	myfile.Close();
}
catch(...)
{
	AfxMessageBox(_T("TXT SAVE ERROR��"));
}
}

void CMCADoc::OnFileSaveAs()
{
	// TODO: �ڴ���������������
try{
	SaveXMLFile();//����XML�ļ�
	CFileDialog dlg(
		FALSE,
		NULL,
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("���ļ� (*.xml;*.txt)|*.xml;*.txt||"),AfxGetMainWnd());
	CString strPath=_T(""); 
	if (dlg.DoModal() == IDOK)
	{
		strPath = dlg.GetPathName();
		int a = dlg.m_ofn.nFilterIndex;
		if (a==1 && strPath.Right(4) != ".txt")
			strPath += ".txt";	
// 		if (a==2 && strPath.Right(4) != ".xml")
// 			strPath += ".xml";	
	}
	else	
	{
		return;
	}

	if(dlg.m_ofn.nFilterIndex == 1)//�����TXT��ʽ
	{
		CStdioFile myfile;
		if(!myfile.Open(strPath,CFile::modeCreate|CFile::modeWrite|CFile::typeText))
		{
			AfxMessageBox(_T("Can not write TXT file."));
			return;
		}
		CString data_str = _T("");
		myfile.WriteString(_T("<<DATA_INFO>>\n"));
		myfile.WriteString(_T("START_TIME - "));  myfile.WriteString(Spectrum_Active.GetStartTime_Str());myfile.WriteString(_T("\n"));
		myfile.WriteString(_T("END_TIME - "));  myfile.WriteString(Spectrum_Active.GetEndTime_Str());myfile.WriteString(_T("\n"));
		myfile.WriteString(_T("MEASURE_TIME - ")); data_str.Format(_T("%d\n"),Spectrum_Active.GetMeasureTime()); myfile.WriteString(data_str);
		myfile.WriteString(_T("LIVE_TIME - ")); data_str.Format(_T("%d\n"),Spectrum_Active.GetLiveTime()); myfile.WriteString(data_str);
		myfile.WriteString(_T("<<END_INFO>>\n"));
		myfile.WriteString(_T("<<DATA_SPECTRUM>>\n"));
		for (int i=0;i<Spectrum_Active.GetOriginSpectrumSize();i++)
		{
			data_str.Format(_T("%d\n"),Spectrum_Active.GetElement_LiveSpectrumData(i));
			myfile.WriteString(data_str);
		}
		myfile.WriteString(_T("<<END_SPECTRUM>>\n"));

		//��������״̬��Ϣ
		myfile.WriteString(_T("<<Data_Status>>\n"));
		for (int i=0;i<Status_data.size();i++)
		{
			data_str.Format(_T("%d\n"),Status_data[i]);
			myfile.WriteString(data_str);
		}
		myfile.WriteString(_T("<<END_Status>>\n"));
		//�洢�¶���Ϣ
		myfile.WriteString(_T("<<Data_Diagonostic>>\n"));
		for (int i=0;i<Diagnostic_cache.size();i++)
		{
			data_str.Format(_T("%d\n"),Diagnostic_cache[i]);
			myfile.WriteString(data_str);
		}
		myfile.WriteString(_T("<<END_Diagnostic>>"));

		myfile.Close();
	}
	else//�����xml��ʽ
	{

	}
}
catch (...)
{
	AfxMessageBox(_T("CMCADoc::OnFileSaveAs��"));
}
}
