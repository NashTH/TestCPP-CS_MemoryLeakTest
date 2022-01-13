using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection.Emit;
using System.Security.Authentication.ExtendedProtection;
using System.Security.Cryptography;
using System.Xml;
using System.IO;
using System.Text;
using System.Globalization;
using System.Net;
using System.Threading;
using System.Diagnostics;

namespace ROIfunctionsLibrary
{   
    //-----------------------------------------------------------------------------------------------------------------------------------------------
    //   OUTPUT ROI 
    //-----------------------------------------------------------------------------------------------------------------------------------------------
    // Initial_row,Row_width,Initial_column,Col_width,Type,Exp,
    // Frames required,Frames obtained,Max.number of frames in 
    //  ROIs=[rowi  roww  coli  colw  type  exp  nframes_req  nframes_run  max_frames];  
    //-----------------------------------------------------------------------------------------------------------------------------------------------
    //   INPUT ROI 
    //-----------------------------------------------------------------------------------------------------------------------------------------------
    // Initial_row,Row_width,Initial_column,Col_width,Type,Exp,Nframe
    //  ROIs=[rowi  roww  coli  colw  type  exp  nframes];  
    public class CRoi : Object
    {
        public enum Type { T8 = 0, T10 = 1, T12 = 2, T14 = 3 }
        public Type m_Type;               // 5
        public uint m_InitialRow;         // 1
        public uint m_RowWidth;           // 2
        public uint m_InitialCol;         // 3
        public uint m_ColWidth;           // 4
        public uint m_ExposureTime;       // 6
        public uint m_FramesRequired;     // 7   // Frames input
        public uint m_FramesRun;          // 8
        public uint m_MaxFrames;          // 9
        public uint m_FramesRequiredSave; // Saved during auto integration   
        public uint m_MaxValueRead;       // Maximum pixel value read minus SB for this Roi of all rows and cols
        public uint m_MaxValueReadPreSB;  // Maximum pixel value read before SB subtraction
        public uint m_MVR_SB;             // SB subtracted from m_MaxValueRead
        public uint m_MVR_Row;            // Row of m_MaxValueRead  
        public uint m_MVR_Col;            // Col of m_MaxValueRead  
        public int m_Error;               // indicates error reading, 0=OK
        public uint m_Saturated;          // indicates saturation,    0=OK
        public List<ushort[]> m_pixelDataRowFrameList; // Frames, Rows of pixel data  "new List<ushort[]>()
        public List<uint[]> m_pixelDataRowList;        // Rows of pixel data  "new List<uint[]>()
        public double[] m_pixelReplicate; // Normalized spectra for a replicate
        public string m_AnalyteName;
        // Copy Constructor
        public CRoi(CRoi Roi)
        {
            m_AnalyteName = Roi.m_AnalyteName;
            m_InitialRow = Roi.m_InitialRow;
            m_RowWidth = Roi.m_RowWidth;
            m_InitialCol = Roi.m_InitialCol;
            m_ColWidth = Roi.m_ColWidth;
            m_ExposureTime = Roi.m_ExposureTime;
            m_FramesRequired = Roi.m_FramesRequired;
            m_FramesRequiredSave = Roi.m_FramesRequiredSave;
            m_Type = Roi.m_Type;
            m_FramesRun = Roi.m_FramesRun;
            m_MaxFrames = Roi.m_MaxFrames;
            m_MaxValueRead = Roi.m_MaxValueRead;
            m_MaxValueReadPreSB = Roi.m_MaxValueReadPreSB;
            m_MVR_SB = Roi.m_MVR_SB;
            m_MVR_Row = Roi.m_MVR_Row;
            m_MVR_Col = Roi.m_MVR_Col;
            m_Error = Roi.m_Error;
            m_Saturated = Roi.m_Saturated;
            m_pixelDataRowFrameList = new List<ushort[]>();
            if (Roi.m_pixelDataRowFrameList == null)
                m_pixelDataRowFrameList = null;
            else
            {
                for (int framerow = 0; framerow < Roi.m_pixelDataRowFrameList.Count; framerow++)
                {
                    ushort[] rowFrameData = null;
                    moveFrameRowDataToSimpleObject(Roi, framerow, ref rowFrameData);
                    m_pixelDataRowFrameList.Add(rowFrameData);
                }
            }

            m_pixelDataRowList = new List<uint[]>(Roi.m_pixelDataRowList);

            if (Roi.m_pixelDataRowList == null)
                m_pixelDataRowList = null;
            else
            {
                for (int row = 0; row < Roi.m_pixelDataRowList.Count; row++)
                {
                    uint[] rowData = null;
                    moveRowDataToSimpleObject(Roi, row, ref rowData);
                    m_pixelDataRowList.Add(rowData);
                }
            }

            if (Roi.m_pixelReplicate == null)
            {
                m_pixelReplicate = null;
            }
            else
            {
                int nSize = (int)Roi.m_pixelReplicate.Count();
                m_pixelReplicate = new double[nSize];
                for (int pix = 0; pix < nSize; pix++)
                    m_pixelReplicate[pix] = Roi.m_pixelReplicate[pix];
            }
        }
        public void moveFrameRowDataToSimpleObject(CRoi roi, int idxRow, ref ushort[] rowFrameData)
        {
            int nLen = roi.m_pixelDataRowFrameList[idxRow].Length;
            rowFrameData = new ushort[nLen];
            Buffer.BlockCopy(roi.m_pixelDataRowFrameList[idxRow], 0, rowFrameData, 0, nLen * sizeof(ushort));
        }
        public void moveRowDataToSimpleObject(CRoi roi, int idxRow, ref uint[] rowData)
        {
            int nLen = roi.m_pixelDataRowList[idxRow].Length;
            rowData = new uint[nLen];
            Buffer.BlockCopy(roi.m_pixelDataRowList[idxRow], 0, rowData, 0, nLen * sizeof(uint));
        }
        // Construct from list of parameters
        public CRoi(uint InitialRow, uint RowWidth, uint InitialCol, uint ColWidth, uint ExposureTime,
                    uint FramesRequired, Type nType, uint FramesRun, uint MaxFrames)
        {
            m_AnalyteName = string.Empty;
            m_InitialRow = InitialRow;
            m_RowWidth = RowWidth;
            m_InitialCol = InitialCol;
            m_ColWidth = ColWidth;
            m_ExposureTime = ExposureTime;
            m_FramesRequired = FramesRequired;
            m_FramesRequiredSave = FramesRequired;
            m_Type = nType;
            m_FramesRun = FramesRun;
            m_MaxFrames = MaxFrames;
            m_MaxValueRead = 0;
            m_MaxValueReadPreSB = 0;
            m_MVR_SB = 0;
            m_MVR_Row = 0;
            m_MVR_Col = 0;
            m_Error = 0;
            m_Saturated = 0;
            m_pixelDataRowFrameList = new List<ushort[]>();
            m_pixelDataRowList = new List<uint[]>();
            m_pixelReplicate = null;
        }
        // Construct - basic
        public CRoi()
        {
            m_AnalyteName = string.Empty;
            m_InitialRow = 0;
            m_RowWidth = 0;
            m_InitialCol = 0;
            m_ColWidth = 0;
            m_ExposureTime = UInt32.MaxValue; // Set to max
            m_FramesRequired = 100000000; //10 ^ 8  Set to max 
            m_FramesRequiredSave = m_FramesRequired;
            m_Type = 0;
            m_FramesRun = 0;
            m_MaxFrames = 0;
            m_MaxValueRead = 0;
            m_MaxValueReadPreSB = 0;
            m_MVR_SB = 0;
            m_MVR_Row = 0;
            m_MVR_Col = 0;
            m_Error = 0;
            m_Saturated = 0;
            m_pixelDataRowFrameList = new List<ushort[]>();
            m_pixelDataRowList = new List<uint[]>();
            m_pixelReplicate = null;
        }
    }
    public class CRoiID : Object
    {
        public string m_AnalyteName;

        // Copy Constructor
        public CRoiID(CRoiID Roi)
        {
            m_AnalyteName = Roi.m_AnalyteName;
        }
        // Copy from CRoi
        public CRoiID(CRoi Roi)
        {
            m_AnalyteName = Roi.m_AnalyteName;
        }
    }
    //--------------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------------
     //--------------------------------------------------------------------------------------------
} // namespace ROIfunctions  end
