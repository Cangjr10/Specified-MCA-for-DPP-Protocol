#pragma once

typedef int Bool_t;
typedef int Int_t;
typedef float Float_t;
/////////////////////////////////////////////////////////////////////////////
//	THIS FILE CONTAINS HEADERS FOR ADVANCED				   //
//	SPECTRA PROCESSING FUNCTIONS.	   				   //
//									   //
//	ONE-DIMENSIONAL BACKGROUND ESTIMATION FUNCTION			   //
//	TWO-DIMENSIONAL BACKGROUND ESTIMATION FUNCTION			   //
//	ONE-DIMENSIONAL DECONVOLUTION FUNCTION				   //
//	TWO-DIMENSIONAL DECONVOLUTION FUNCTION				   //
//	ONE-DIMENSIONAL PEAK SEARCH FUNCTION				   //
//	TWO-DIMENSIONAL PEAK SEARCH FUNCTION				   //
//									   //
//	Miroslav Morhac							   //
//	Institute of Physics						   //
//	Slovak Academy of Sciences					   //
//	Dubravska cesta 9, 842 28 BRATISLAVA				   //
//	SLOVAKIA							   //
//									   //
//	email:fyzimiro@savba.sk,	 fax:+421 7 54772479		   //
//									   //
/////////////////////////////////////////////////////////////////////////////

const double    EfficiencyOfCs = 0.264;
const double    EfficiencyOfCo1 = 0.282;
const double    EfficiencyOfCo2 = 0.278;
const double    EfficiencyOfAg = 0.295;
const int    SmoothOrder3=3;
const int    SmoothOrder5=5;
const int    SmoothOrder7=7;
const int    SmoothOrder11=11;
const int    kBackOrder2 =0;
const int    kBackOrder4 =1;
const int    kBackOrder6 =2;
const int    kBackOrder8 =3;
const int    kBackIncreasingWindow =0;
const int    kBackDecreasingWindow =1;
const Bool_t kBackExcludeCompton = false;
const Bool_t kBackIncludeCompton = true;
const int	 Cs137 = 0;//核素类型
const int	 Co60_1 = 1;
const int	 Co60_2 = 2;
const int	 Ag108 = 3;

//note that this class does not follow the ROOT naming conventions
class TSpectrumOneDimFit{
public:

#define N 3
};
class CROI  
{
public:
	CROI(UINT _start = 0 , UINT _end = 0) : ROI_start(_start),ROI_end(_end){}
	~CROI(){}
	CROI(const CROI &p) { ROI_start = p.ROI_start; ROI_end = p.ROI_end;}
	void SetROI(UINT _start , UINT _end) {ROI_start = _start; ROI_end = _end;}
	UINT GetROIStart()	{return ROI_start;}
	UINT GetROIEnd()	{return ROI_end;}
private:
	UINT ROI_start;
	UINT ROI_end;
};

class CSpectrum
{
	friend class CUserPlot;
public:
	CSpectrum();
	~CSpectrum() {}
	//复制构造函数，深复制！！！
	CSpectrum(const CSpectrum& spectra){ /*SpectrumData = spectra.SpectrumData; SpectrumROI = spectra.SpectrumROI;*/};//Spectrum Data Process
	void SetSpectrumData(vector<UINT32> _SpectrumData); 
	//void SetSpectrumDataForShow(vector<UINT32> _SpectrumData){SpectrumData = _SpectrumData;}; 
	UINT32	GetSpectrumMax(void);//获取全谱的最大值
	UINT32	GetROIMax(UINT Number);//获取第Number个ROI的最大值
	UINT32	GetROIMin(UINT Number);//获取第Number个ROI的最小值
	UINT	GetSpectrumSize(void) { return SpectrumData.size();}//获取谱数据的数目
	UINT	GetOriginSpectrumSize(void) { return SpectrumOrigin.size();}//获取谱数据的数目
	UINT32	GetElement(UINT i);	//获取第i个谱数据
	UINT32	GetElement_IntrinsicSpectrumData(UINT i);	//获取本底谱数据
	UINT32	GetElement_LiveSpectrumData(UINT i);	//获取原始谱数据
	float	GetElement_RebinedIntrinsicSpectrum(UINT i);	//并道之后的本底数据
	float	GetElement_RebinedLiveSpectrum(UINT i);	//并道之后的谱数据
	float	GetElement_SNIP_Background(UINT i);	//SNIP算法的本底数据
	float	GetEnergy(UINT i);	//获取第i个谱数据对应的能量
	vector<UINT32> GetSpectrumData(void) {return SpectrumData;}//获取全谱数据
	CROI GetSpectrumROI(UINT Number) {return SpectrumROI[Number];}//获取第Number个ROI
	void AddROI(CROI _ROI);//添加ROI
	void DeleteROI(UINT nIndex);
	void ClearAllROI(void)	{SpectrumROI.resize(0);}//清除所有的ROI
	UINT GetROINumber(void) {return SpectrumROI.size();}//获取ROI的数目
	BOOL GetSelectedROIIndex(UINT &index);//	{return Index_SelectedROI;}
	void SetSelectedROIIndex(UINT index)	{Index_SelectedROI = index;}
	//Spectrum ROI manSelectedROIIndexage
	//20150129能谱数据处理
	void Preprocess(void);//对道址数据进行稳谱，刻度，并道等一系列预处理转换成能量数据并用于显示。
	const char *Background1(float *spectrum,int size,int niter);
	const char *Background1General(float *spectrum,int size,int fNumberIterations,int direction,int filter_order,bool compton);
	const char *Rebin(float *energy_in,float *spectrum_in,vector<float> &spectrum_out,int size,float width);
	const char *Smooth(float *spectrum,int size,int smooth_order,int num);
	const char *polyfit2_3(float *x,float *y,vector<float> &coefficient);
	//const char *polyval2(float *y,int size,vector<float> &coefficient);
	const char *polyfit2_4(float *x,float *y,vector<float> &coefficient);
	float SearchMaxPosition(float *x,float *y,int min,int max);
	void SetMeasureTime(UINT32 _time) {MeasureTime = _time;};
	void SetLiveTime(UINT32 _time) {LiveTime = _time;};
	CString GetStartTime_Str(void){return Str_StartTime;};
	CString GetEndTime_Str(void){return Str_EndTime;};
	void SetStartTime_Str(CString _strattime){Str_StartTime = _strattime;};
	void SetEndTime_Str(CString _endtime){Str_EndTime = _endtime;};
	UINT32 GetMeasureTime(void){return MeasureTime;};
	UINT32 GetLiveTime(void){return LiveTime;};
	float CalculateActivity(int nuclide);
	float GetCsActivity(void){return Activity_Cs;};
private:
	void f1(double *a,float *x,int n,int num);
	void f2(double *a,double *b,float y[],int n,int num);
	void swap(double &a,double &b);
	void DirectLU(double a[N][N+1],double x[]);
	vector<UINT32> SpectrumData;//用于显示的数据，3000道
	vector<float> RebinedLiveSpectrum;//用于能谱数据计算，1000道，3keV/道
	vector<float> RebinedIntrinsicSpectrum;//并道之后的本底数据
	vector<float> SNIP_Background;//SNIP 算法处理得到的本底曲线
	vector<CROI>	SpectrumROI;
	vector<UINT32> SpectrumOrigin;//实测数据，道址2048
	vector<UINT32> SpectrumIntrinsic;//本底数据，2048道，从文件读取
	UINT Index_SelectedROI;
	CString Str_StartTime;
	CString Str_EndTime;
	UINT32 MeasureTime;
	UINT32 LiveTime;
	float Activity_Cs;
	float a ,b,c;//能量刻度系数
	double a0 ,b0,c0;//本底能量刻度系数
};