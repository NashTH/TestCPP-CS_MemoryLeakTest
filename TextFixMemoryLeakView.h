
// TextFixMemoryLeakView.h : interface of the CTextFixMemoryLeakView class
//

#pragma once


class CTextFixMemoryLeakView : public CView
{
protected: // create from serialization only
	CTextFixMemoryLeakView() noexcept;
	DECLARE_DYNCREATE(CTextFixMemoryLeakView)

// Attributes
public:
	CTextFixMemoryLeakDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CTextFixMemoryLeakView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TextFixMemoryLeakView.cpp
inline CTextFixMemoryLeakDoc* CTextFixMemoryLeakView::GetDocument() const
   { return reinterpret_cast<CTextFixMemoryLeakDoc*>(m_pDocument); }
#endif

