#pragma once
#include "Spectrum.h"

class CUserPlot
{
	//friend class CSpectrum;
public:
	CUserPlot(){}//Ĭ�Ϲ��캯��
	CUserPlot(CWnd* _pWnd) : pWnd(_pWnd){}//��ȡ��ͼĿ�����Ĵ�����
	~CUserPlot(){}
	void GetWnd(CWnd* _pWnd){pWnd = _pWnd;}//��ȡ����
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
	CPoint Origin,Extent;//ʵ��������ʾ����
	int View_Xrange,View_Yrange;//�߼��������
	double AxisX1,AxisX2,AxisY1,AxisY2;//����������ݷ�Χ
	double m_nCursor;
};
