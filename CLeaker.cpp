#include "pch.h"
#include "CLeaker.h"
#include "MainFrm.h"
#using <System.dll>
#using <System.Core.dll>
#using <..\\Syngistix\\bin\\Debug\\ROIFunctionsLibrary.dll>
using namespace System;
using namespace System::Collections::Generic;
using namespace ROIfunctionsLibrary;

CLeaker::CLeaker()
{
}
CLeaker::~CLeaker()
{
}

void CLeaker::startLeaking()
{
    static CString name[20] = { {L"A"},{L"B"},{L"C"},{L"D"},{L"E"},{L"F"},{L"G"},{L"H"},{L"I"},{L"J"},
                                {L"K"},{L"L"},{L"M"},{L"N"},{L"O"},{L"P"},{L"Q"},{L"R"},{L"S"},{L"T"} };
    List<CRoi^>^ ROIList = gcnew List<CRoi^>();
    // Dummy ROI at start, since array is 1-based at low level
    CRoi^ roiDummy = gcnew CRoi();
    ROIList->Add(roiDummy);
    // Make 20 ROIs
    for (int i = 0; i < 20; i++)
    {
        CRoi^ roi = gcnew CRoi();

        roi->m_Type = (CRoi::Type)3;
        roi->m_InitialRow = 1;
        roi->m_InitialCol = 2;
        roi->m_RowWidth = 10;
        roi->m_ColWidth = 31;
        roi->m_ExposureTime = 1000000;
        roi->m_AnalyteName = gcnew System::String(name[i]);
        roi->m_FramesRequired = 10;
        ROIList->Add(roi);
    }

    // Attempt to fix memory leaks ... null the pointers within the local list
  //  for each (CRoi ^ roi in ROIList)
  //  {
  //      roi->m_AnalyteName = nullptr;
  //      roi = nullptr;
  //  }
}



  


