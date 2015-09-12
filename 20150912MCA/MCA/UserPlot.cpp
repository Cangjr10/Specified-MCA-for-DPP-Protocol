#include "stdafx.h"
#include "UserPlot.h"

void CUserPlot::SetUserView(CDC* MemDC)
{
try{
	MemDC->SaveDC();
	pWnd->GetClientRect(&rect_view);//��ȡ���¾�������
	Origin.SetPoint(rect_view.left+50,rect_view.bottom-20);//����OnSize��֤���㹻�Ĵ�С
	Extent.SetPoint(rect_view.right-20,rect_view.top+20);
	MemDC->SetMapMode(MM_ANISOTROPIC); 
	MemDC->SetViewportOrg(Origin); 
	MemDC->SetViewportExt(abs(Extent.x-Origin.x),abs(Origin.y-Extent.y));
	View_Xrange = 20000;
	View_Yrange = 10000;
	MemDC->SetWindowOrg(0,0); 
	MemDC->SetWindowExt(View_Xrange,-View_Yrange);
	UserViewFlag = TRUE;
}
catch (...)
{
	AfxMessageBox(_T("CUserPlot::SetUserView��"));
}
}
void CUserPlot::SetDefaultView(CDC* MemDC)
{
try{
	if(UserViewFlag)
		MemDC->RestoreDC(-1);
}
catch (...)
{
	AfxMessageBox(_T("CUserPlot::SetDefaultView��"));
}
}
void CUserPlot::SetAxis(double _AxisX1 /* = 0 */,double _AxisX2/* =8192 */,double _AxisY1/* =0 */,double _AxisY2/* =256 */)
{
try{
	AxisX1 = _AxisX1;
	AxisX2 = _AxisX2; 
	AxisY1 = _AxisY1; 
	AxisY2 = _AxisY2;
}
catch (...)
{
	AfxMessageBox(_T("CUserPlot::SetAxis��"));
}
}
void CUserPlot::DrawAxis(CDC* MemDC,CSpectrum& spectrum)
{
try{
	pWnd->GetClientRect(&rect_view);//��ȡ���¾�������
	if ((rect_view.right-rect_view.left)>100 && (rect_view.bottom-rect_view.top) > 100)
	{
		CPen *PenOld,PenNew;
		PenNew.CreatePen(PS_SOLID,1,RGB(0,0,0));//��ɫ����
		int arrow_sizeX = (int)(10*View_Xrange/(rect_view.right-rect_view.left));//10������
		int arrow_sizeY = (int)(10*View_Yrange/(rect_view.bottom-rect_view.top));
		PenOld = MemDC->SelectObject(&PenNew);
		MemDC->MoveTo(0,0);
		MemDC->LineTo(0,View_Yrange+2*arrow_sizeY);
		MemDC->MoveTo(-arrow_sizeX,View_Yrange+arrow_sizeY);
		MemDC->LineTo(0,View_Yrange+2*arrow_sizeY);
		MemDC->LineTo(arrow_sizeX,View_Yrange+arrow_sizeY);
		MemDC->MoveTo(0,0);
		MemDC->LineTo(View_Xrange+arrow_sizeX+arrow_sizeX,0);
		MemDC->MoveTo(View_Xrange+arrow_sizeX,arrow_sizeY);
		MemDC->LineTo(View_Xrange+arrow_sizeX+arrow_sizeX,0);
		MemDC->LineTo(View_Xrange+arrow_sizeX,-arrow_sizeY);
		//���
		int Text_sizeX = (int)(40*View_Xrange/(rect_view.right-rect_view.left));
		int Text_sizeY = (int)(20*View_Yrange/(rect_view.bottom-rect_view.top));
		int Offset_Text_sizeY = (int)(2*View_Yrange/(rect_view.bottom-rect_view.top));
		int Offset_Text_sizeX = (int)(2*View_Xrange/(rect_view.right-rect_view.left));
		int ScaleSizeX = (int)(10*View_Yrange/(rect_view.bottom-rect_view.top));
		int ScaleSizeY = (int)(10*View_Xrange/(rect_view.right-rect_view.left));
		CString str;
		//������
		CRect rect_text0(0,-Offset_Text_sizeY,Text_sizeX,-Offset_Text_sizeY-Text_sizeY);
		str.Format(_T("%.lf"),AxisX1 );
		MemDC->DrawText(str,rect_text0,DT_LEFT|DT_SINGLELINE|DT_VCENTER);
		for (int i = 1;i<9;i++)
		{
			MemDC->MoveTo(i*View_Xrange/8,0);
			MemDC->LineTo(i*View_Xrange/8,ScaleSizeX);
			CRect rect_text(i*View_Xrange/8-Text_sizeX/2,-Offset_Text_sizeY,i*View_Xrange/8+Text_sizeX/2,-Offset_Text_sizeY-Text_sizeY);
			str.Format(_T("%.lf"),spectrum.GetEnergy(int(AxisX1 + i*(AxisX2-AxisX1)/8)));//ת��Ϊ������ʾ
			MemDC->DrawText(str,rect_text,DT_CENTER|DT_SINGLELINE|DT_VCENTER);
		}
		//������
		CRect rect_text1(-Text_sizeX-Offset_Text_sizeX,Text_sizeY,-Offset_Text_sizeX,0);
		if (AxisY1 < 1000)
			str.Format(_T("%d"),int(AxisY1));
		else if (AxisY1 < 1000000)
			str.Format(_T("%d k"),(int)(AxisY1/1000));
		else
			str.Format(_T("%d M"),(int)(AxisY1/1000000));
		MemDC->DrawText(str,rect_text1,DT_RIGHT|DT_SINGLELINE|DT_VCENTER);
		for (int i = 1;i<5;i++)
		{
			MemDC->MoveTo(0,i*View_Yrange/4);
			MemDC->LineTo(ScaleSizeY,i*View_Yrange/4);
			CRect rect_text(-Text_sizeX-Offset_Text_sizeX,i*View_Yrange/4+Text_sizeY/2,-Offset_Text_sizeX,i*View_Yrange/4-Text_sizeY/2);
			double Ylabel = AxisY1 + i*(AxisY2-AxisY1)/4;
			if (Ylabel < 1000)
				str.Format(_T("%d"),int(Ylabel));
			else if (Ylabel < 100000)
				str.Format(_T("%.1fk"),(Ylabel/1000));
			else if (Ylabel < 1000000)
				str.Format(_T("%dk"),int(Ylabel/1000));
			else
				str.Format(_T("%.1fM"),(Ylabel/1000000));
			MemDC->DrawText(str,rect_text,DT_RIGHT|DT_SINGLELINE|DT_VCENTER);
		}
		MemDC->SelectObject(PenOld);
		PenNew.DeleteObject();
	}
}
catch (...)
{
	AfxMessageBox(_T("CUserPlot::DrawAxis��"));
}
}

void CUserPlot::SetPoint(CDC* MemDC,double _x,double _y,COLORREF _color/* = RGB(0,0,0)*/,int _radius/* = 6 */)
{
try{
	pWnd->GetClientRect(&rect_view);//��ȡ���¾�������
	double X_radius = _radius*View_Xrange/(rect_view.right-rect_view.left);//_radius�����ص���
	double Y_radius = _radius*View_Yrange/(rect_view.bottom-rect_view.top);//_radius�����ص���
	CRect BoardRect;
	BoardRect.left = (int)((_x - AxisX1)/(AxisX2 - AxisX1)*View_Xrange - X_radius);
	BoardRect.right = (int)((_x - AxisX1)/(AxisX2 - AxisX1)*View_Xrange + X_radius);
	BoardRect.top = (int)((_y - AxisY1)/(AxisY2 - AxisY1)*View_Yrange + Y_radius);
	BoardRect.bottom = (int)((_y - AxisY1)/(AxisY2 - AxisY1)*View_Yrange - Y_radius);
	if ( (int)_x > AxisX1 && (int)_x < AxisX2 && (int)_y < AxisY2 && (int)_y > AxisY1)
		MemDC->Ellipse(&BoardRect);
}
catch (...)
{
	AfxMessageBox(_T("CUserPlot::SetPoint��"));
}
}
CPoint CUserPlot::UserPointToLogical(double x, double y)
{
try{
	CPoint point;
	point.x = (int)((x - AxisX1)/(AxisX2 - AxisX1)*View_Xrange);
	point.y = (int)((y - AxisY1)/(AxisY2 - AxisY1)*View_Yrange);
	return point;
}
catch (...)
{
	AfxMessageBox(_T("CUserPlot::UserPointToLogical��"));
}
}
int CUserPlot::UserXToLogical(double x)
{
try{
	return (int)((x - AxisX1)/(AxisX2 - AxisX1)*View_Xrange);
}
catch (...)
{
	AfxMessageBox(_T("CUserPlot::UserXToLogical��"));
}
}
int CUserPlot::UserYToLogical(double y)
{
try{
	return (int)((y - AxisY1)/(AxisY2 - AxisY1)*View_Yrange);
}
catch (...)
{
	AfxMessageBox(_T("CUserPlot::UserYToLogical��"));
}
}
double CUserPlot::WindowsXToAxis(int x)
{
try{
	return double(x-Origin.x)/(Extent.x-Origin.x)*(AxisX2-AxisX1)+AxisX1;
}
catch (...)
{
	AfxMessageBox(_T("CUserPlot::WindowsXToAxis��"));
}
}
double CUserPlot::WindowsYToAxis(int y)
{
try{
	return double(Origin.y-y)/(Origin.y-Extent.y)*(AxisY2-AxisY1)+AxisY1;
}
catch (...)
{
	AfxMessageBox(_T("CUserPlot::WindowsYToAxis��"));
}
}
void CUserPlot::PlotSpectrum(CDC* pDC,CSpectrum& spectrum, COLORREF _bkgcolor,COLORREF _lineColor)
{
try{
	//˫�����ͼ����ֹ��˸
	CDC MemDC; //���ȶ���һ����ʾ�豸����  
	CBitmap MemBitmap;//����һ��λͼ����
	//���������Ļ��ʾ���ݵ��ڴ���ʾ�豸
	MemDC.CreateCompatibleDC(NULL); 
	//���潨��һ������Ļ��ʾ���ݵ�λͼ������λͼ�Ĵ�С������ô��ڵĴ�С 
	pWnd->GetClientRect(&rect_view);//��ȡ���¾�������
	int nWidth = rect_view.right - rect_view.left;
	int nHeight = rect_view.bottom - rect_view.top;
	MemBitmap.CreateCompatibleBitmap(pDC,nWidth,nHeight);
	//��λͼѡ�뵽�ڴ���ʾ�豸�� 
	CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);
	//���ñ���ɫ��λͼ����ɾ�
// 	if(HoldOn == FALSE)
	MemDC.FillSolidRect(0,0,nWidth,nHeight,_bkgcolor);
	//m_nCursor = AxisX1;
 	//MemDC.FillSolidRect(0,0,nWidth,nHeight,RGB(255,255,255));
	//��ͼ
	SetUserView(&MemDC);
	DrawAxis(&MemDC,spectrum);
	//CPoint point[8192]={(0,0)};
	CPoint point(0,0);
	for (UINT i = 0;i<spectrum.GetSpectrumSize();i++)
	{
		if (i == (UINT)AxisX1)
		{
			point = UserPointToLogical(AxisX1,spectrum.GetElement((UINT)AxisX1));
			MemDC.MoveTo(point.x,point.y);
		}
		if (i>AxisX1 && i<=AxisX2 && spectrum.GetElement(i) >= AxisY1 && spectrum.GetElement(i)<= AxisY2)
		{
			point = UserPointToLogical(i,spectrum.GetElement(i));
			MemDC.LineTo(point.x,point.y);
		}
	}
	//MemDC.Polyline(point,spectrum.GetSpectrumSize());
	SetDefaultView(&MemDC);
	//���ڴ��е�ͼ��������Ļ�Ͻ�����ʾ
/*	if(HoldOn == FALSE)*/
	pDC->BitBlt(0,0,nWidth,nHeight,&MemDC,0,0,SRCCOPY);
// 	else
// 		pDC->BitBlt(0,0,nWidth,nHeight,&MemDC,0,0,SRCAND);

	//��ͼ��ɺ������  
	MemBitmap.DeleteObject();  
	MemDC.DeleteDC();
}
catch (...)
{
	AfxMessageBox(_T("CUserPlot::PlotSpectrum��"));
}
}
void CUserPlot::BarSpectrum(CDC* pDC,CSpectrum& spectrum, COLORREF _bkgcolor,COLORREF _SpectrumColor,COLORREF _ROIColor)
{
try{
	//˫�����ͼ����ֹ��˸
	CDC MemDC; //���ȶ���һ����ʾ�豸����  
	CBitmap MemBitmap;//����һ��λͼ����
	//���������Ļ��ʾ���ݵ��ڴ���ʾ�豸
	MemDC.CreateCompatibleDC(NULL); 
	//���潨��һ������Ļ��ʾ���ݵ�λͼ������λͼ�Ĵ�С������ô��ڵĴ�С 
	pWnd->GetClientRect(&rect_view);//��ȡ���¾�������
	int nWidth = rect_view.right - rect_view.left;
	int nHeight = rect_view.bottom - rect_view.top;
	MemBitmap.CreateCompatibleBitmap(pDC,nWidth,nHeight);
	//��λͼѡ�뵽�ڴ���ʾ�豸�� 
	CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);
	//���ñ���ɫ��λͼ����ɾ�
//	if(HoldOn == FALSE)
	MemDC.FillSolidRect(0,0,nWidth,nHeight,_bkgcolor);
//	m_nCursor = AxisX1;
	//��ͼ
	CPen *OldPen,NewPen,PenROI;
	NewPen.CreatePen(PS_SOLID,1,_SpectrumColor);
	PenROI.CreatePen(PS_SOLID,1,_ROIColor);
	OldPen = MemDC.SelectObject(&NewPen);
	CBrush *BrushOld,BrushNew;
	BrushNew.CreateSolidBrush(_SpectrumColor);
	BrushOld = MemDC.SelectObject(&BrushNew);
	SetUserView(&MemDC);
	DrawAxis(&MemDC,spectrum);
	CPoint point1(0,0);
	CPoint point2(0,0);
	for (UINT i = 0;i<spectrum.GetSpectrumSize();i++)
	{
		if (i == AxisX1 && spectrum.GetElement(i) >= AxisY1 && spectrum.GetElement(i)<= AxisY2)
		{
			point1 = UserPointToLogical(i,spectrum.GetElement(i));
			point2 = UserPointToLogical(i+0.5,AxisY1);
			MemDC.Rectangle(point1.x,point1.y,point2.x,point2.y);
		}
		if (i>AxisX1 && i<=AxisX2 && spectrum.GetElement(i) >= AxisY1 && spectrum.GetElement(i)<= AxisY2)
		{
			point1 = UserPointToLogical(i-0.5,spectrum.GetElement(i));
			point2 = UserPointToLogical(i+0.5,AxisY1);
			MemDC.Rectangle(point1.x,point1.y,point2.x,point2.y);
		}	
	}
	MemDC.SelectObject(&PenROI);
	UINT ROINumber = spectrum.GetROINumber();
	for (UINT i = 0;i<ROINumber;i++)
	{
		for (UINT j = spectrum.GetSpectrumROI(i).GetROIStart();j<spectrum.GetSpectrumROI(i).GetROIEnd();j++)
		{
			if (j == AxisX1 && spectrum.GetElement(j) >= AxisY1 && spectrum.GetElement(j)<= AxisY2)
			{
				point1 = UserPointToLogical(j,spectrum.GetElement(j));
				point2 = UserPointToLogical(j+0.5,AxisY1);
				MemDC.Rectangle(point1.x,point1.y,point2.x,point2.y);
			}
			if (j>AxisX1 && j<=AxisX2 && spectrum.GetElement(j) >= AxisY1 && spectrum.GetElement(j)<= AxisY2)
			{
				point1 = UserPointToLogical(j-0.5,spectrum.GetElement(j));
				point2 = UserPointToLogical(j+0.5,AxisY1);
				MemDC.Rectangle(point1.x,point1.y,point2.x,point2.y);
			}
		}
	}
	MemDC.SelectObject(OldPen);
	NewPen.DeleteObject();
	//��cursor
	if (GetCursorPosition()>(UINT)AxisX1 && GetCursorPosition()<=(UINT)AxisX2)
	{
		point1 = UserPointToLogical(GetCursorPosition(),AxisY1);
		point2 = UserPointToLogical(GetCursorPosition(),AxisY2);
		MemDC.SetROP2(R2_NOT);
		MemDC.MoveTo(point1);
		MemDC.LineTo(point2);
	}	
	MemDC.SelectObject(BrushOld);
	BrushNew.DeleteObject();
	SetDefaultView(&MemDC);
	//���ڴ��е�ͼ��������Ļ�Ͻ�����ʾ   
	pDC->BitBlt(0,0,nWidth,nHeight,&MemDC,0,0,SRCCOPY);
	//��ͼ��ɺ������  
	MemBitmap.DeleteObject();  
	MemDC.DeleteDC();
}
catch (...)
{
	AfxMessageBox(_T("CUserPlot::BarSpectrum��"));
}
}
void CUserPlot::DrawVerticleLine(CDC* MemDC,double newCursor)
{
try{

// 	CPen *Penold, PenNew;
// 	PenNew.CreatePen(PS_SOLID,2,RGB(255,0,0));
// 	Penold = MemDC->SelectObject(&PenNew);
	MemDC->SetROP2(R2_NOT);
// 	if (m_nCursor == newCursor)
// 	{
// 		CPoint point1 = UserPointToLogical(m_nCursor,AxisY1);
// 		CPoint point2 = UserPointToLogical(m_nCursor,AxisY2);
// 		MemDC->MoveTo(point1);
// 		MemDC->LineTo(point2);
// 	}
	//clear last line
	if (m_nCursor > AxisX1 && m_nCursor <= AxisX2 /*&& m_nCursor*/)
	{
		CPoint point1 = UserPointToLogical(m_nCursor,AxisY1);
		CPoint point2 = UserPointToLogical(m_nCursor,AxisY2);
		MemDC->MoveTo(point1);
		MemDC->LineTo(point2);
	}
	if (newCursor < AxisX1)
		newCursor = AxisX1;
	if (newCursor > AxisX2)
		newCursor = AxisX2;
	m_nCursor = newCursor;
	//draw new line
	if (newCursor > AxisX1 && newCursor <= AxisX2)
	{
		CPoint point1 = UserPointToLogical(newCursor,AxisY1);
		CPoint point2 = UserPointToLogical(newCursor,AxisY2);
		MemDC->MoveTo(point1);
		MemDC->LineTo(point2);
	}
// 	MemDC->SelectObject(Penold);
// 	PenNew.DeleteObject();
}
catch (...)
{
	AfxMessageBox(_T("CUserPlot::DrawVerticleLine��"));
}
}