#pragma once
#include "Spectrum.h"

class CUserPlot
{
	//friend class CSpectrum;
public:
	CUserPlot(){}//默认构造函数
	CUserPlot(CWnd* _pWnd) : pWnd(_pWnd){}//获取绘图目标对象的窗口类
	~CUserPlot(){}
	void GetWnd(CWnd* _pWnd){pWnd = _pWnd;}//获取窗口
	void SetUserView(CDC* MemDC);
	void SetDefaultView(CDC* MemDC);
	void SetAxis(double _AxisX1 = 0,double _AxisX2=2048,double _AxisY1=0,double _AxisY2=256);
	void DrawAxis(CDC* MemDC,CSpectrum& spectrum);
	void SetPoint(CDC* MemDC,double _x,double _y,COLORREF _color = RGB(0,0,0),int _radius = 6 );
	double WindowsXToAxis(int x); 
	double WindowsYToAxis(int y); 
	void DrawVerticleLine(CDC* MemDC,double newCursor);
	CPoint UserPointToLogical(double x, double y);
	int UserXToLogical(double x);
	int UserYToLogical(double y);
	void PlotSpectrum(CDC* pDC,CSpectrum& spectrum, COLORREF _bkgcolor,COLORREF _lineColor);
	void BarSpectrum(CDC* pDC,CSpectrum& spectrum, COLORREF _bkgcolor,COLORREF _SpectrumColor,COLORREF _ROIColor);
	UINT GetCursorPosition(void) {return (UINT)(m_nCursor);}
private:
	CWnd* pWnd;
	CRect rect_view;
	BOOL UserViewFlag;
	CPoint Origin,Extent;//实际数据显示区域
	int View_Xrange,View_Yrange;//逻辑坐标点数
	double AxisX1,AxisX2,AxisY1,AxisY2;//坐标轴的数据范围
	double m_nCursor;
};
