
// TextFixMemoryLeakDoc.cpp : implementation of the CTextFixMemoryLeakDoc class
//
#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "TextFixMemoryLeak.h"
#endif
#include "TextFixMemoryLeakDoc.h"
#include <propkey.h>

#include "CLeaker.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CTextFixMemoryLeakDoc

IMPLEMENT_DYNCREATE(CTextFixMemoryLeakDoc, CDocument)

BEGIN_MESSAGE_MAP(CTextFixMemoryLeakDoc, CDocument)
END_MESSAGE_MAP()


// CTextFixMemoryLeakDoc construction/destruction

CTextFixMemoryLeakDoc::CTextFixMemoryLeakDoc() noexcept
{
	// TODO: add one-time construction code here

}

CTextFixMemoryLeakDoc::~CTextFixMemoryLeakDoc()
{
}

BOOL CTextFixMemoryLeakDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	CLeaker* leaker(new CLeaker());
	while (true)
	{
		leaker->startLeaking();
	}

	delete leaker;
	return TRUE;
}




// CTextFixMemoryLeakDoc serialization

void CTextFixMemoryLeakDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CTextFixMemoryLeakDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
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

// Support for Search Handlers
void CTextFixMemoryLeakDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CTextFixMemoryLeakDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CTextFixMemoryLeakDoc diagnostics

#ifdef _DEBUG
void CTextFixMemoryLeakDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTextFixMemoryLeakDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CTextFixMemoryLeakDoc commands
