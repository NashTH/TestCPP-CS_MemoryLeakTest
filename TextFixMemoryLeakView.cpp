
// TextFixMemoryLeakView.cpp : implementation of the CTextFixMemoryLeakView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "TextFixMemoryLeak.h"
#endif

#include "TextFixMemoryLeakDoc.h"
#include "TextFixMemoryLeakView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTextFixMemoryLeakView

IMPLEMENT_DYNCREATE(CTextFixMemoryLeakView, CView)

BEGIN_MESSAGE_MAP(CTextFixMemoryLeakView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTextFixMemoryLeakView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CTextFixMemoryLeakView construction/destruction

CTextFixMemoryLeakView::CTextFixMemoryLeakView() noexcept
{
	// TODO: add construction code here

}

CTextFixMemoryLeakView::~CTextFixMemoryLeakView()
{
}

BOOL CTextFixMemoryLeakView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CTextFixMemoryLeakView drawing

void CTextFixMemoryLeakView::OnDraw(CDC* /*pDC*/)
{
	CTextFixMemoryLeakDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CTextFixMemoryLeakView printing


void CTextFixMemoryLeakView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CTextFixMemoryLeakView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTextFixMemoryLeakView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTextFixMemoryLeakView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CTextFixMemoryLeakView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CTextFixMemoryLeakView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CTextFixMemoryLeakView diagnostics

#ifdef _DEBUG
void CTextFixMemoryLeakView::AssertValid() const
{
	CView::AssertValid();
}

void CTextFixMemoryLeakView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTextFixMemoryLeakDoc* CTextFixMemoryLeakView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTextFixMemoryLeakDoc)));
	return (CTextFixMemoryLeakDoc*)m_pDocument;
}
#endif //_DEBUG


// CTextFixMemoryLeakView message handlers
