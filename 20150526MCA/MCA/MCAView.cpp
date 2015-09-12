
// MCAView.cpp : CMCAView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MCA.h"
#endif

#include "MCADoc.h"
#include "MCAView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMCAView

IMPLEMENT_DYNCREATE(CMCAView, CView)

BEGIN_MESSAGE_MAP(CMCAView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMCAView ����/����

CMCAView::CMCAView()
{
	// TODO: �ڴ˴���ӹ������

}

CMCAView::~CMCAView()
{
}

BOOL CMCAView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMCAView ����

void CMCAView::OnDraw(CDC* /*pDC*/)
{
	CMCADoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CMCAView ��ӡ

BOOL CMCAView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMCAView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMCAView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CMCAView ���

#ifdef _DEBUG
void CMCAView::AssertValid() const
{
	CView::AssertValid();
}

void CMCAView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMCADoc* CMCAView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMCADoc)));
	return (CMCADoc*)m_pDocument;
}
#endif //_DEBUG


// CMCAView ��Ϣ�������
