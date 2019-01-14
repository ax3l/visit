// ***************************************************************************
//
// Copyright (c) 2000 - 2019, Lawrence Livermore National Security, LLC
// Produced at the Lawrence Livermore National Laboratory
// LLNL-CODE-442911
// All rights reserved.
//
// This file is  part of VisIt. For  details, see https://visit.llnl.gov/.  The
// full copyright notice is contained in the file COPYRIGHT located at the root
// of the VisIt distribution or at http://www.llnl.gov/visit/copyright.html.
//
// Redistribution  and  use  in  source  and  binary  forms,  with  or  without
// modification, are permitted provided that the following conditions are met:
//
//  - Redistributions of  source code must  retain the above  copyright notice,
//    this list of conditions and the disclaimer below.
//  - Redistributions in binary form must reproduce the above copyright notice,
//    this  list of  conditions  and  the  disclaimer (as noted below)  in  the
//    documentation and/or other materials provided with the distribution.
//  - Neither the name of  the LLNS/LLNL nor the names of  its contributors may
//    be used to endorse or promote products derived from this software without
//    specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR  IMPLIED WARRANTIES, INCLUDING,  BUT NOT  LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS FOR A PARTICULAR  PURPOSE
// ARE  DISCLAIMED. IN  NO EVENT  SHALL LAWRENCE  LIVERMORE NATIONAL  SECURITY,
// LLC, THE  U.S.  DEPARTMENT OF  ENERGY  OR  CONTRIBUTORS BE  LIABLE  FOR  ANY
// DIRECT,  INDIRECT,   INCIDENTAL,   SPECIAL,   EXEMPLARY,  OR   CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT  LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR
// SERVICES; LOSS OF  USE, DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER
// CAUSED  AND  ON  ANY  THEORY  OF  LIABILITY,  WHETHER  IN  CONTRACT,  STRICT
// LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY  WAY
// OUT OF THE  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
// DAMAGE.
//
// ***************************************************************************

package llnl.visit.operators;

import llnl.visit.AttributeSubject;
import llnl.visit.CommunicationBuffer;
import llnl.visit.Plugin;

// ****************************************************************************
// Class: IndexSelectAttributes
//
// Purpose:
//    This class contains attributes for the index select operator.
//
// Notes:      Autogenerated by xml2java.
//
// Programmer: xml2java
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

public class IndexSelectAttributes extends AttributeSubject implements Plugin
{
    private static int IndexSelectAttributes_numAdditionalAtts = 20;

    // Enum values
    public final static int DIMENSION_ONED = 0;
    public final static int DIMENSION_TWOD = 1;
    public final static int DIMENSION_THREED = 2;


    public IndexSelectAttributes()
    {
        super(IndexSelectAttributes_numAdditionalAtts);

        maxDim = DIMENSION_THREED;
        dim = DIMENSION_TWOD;
        xAbsMax = -1;
        xMin = 0;
        xMax = -1;
        xIncr = 1;
        xWrap = false;
        yAbsMax = -1;
        yMin = 0;
        yMax = -1;
        yIncr = 1;
        yWrap = false;
        zAbsMax = -1;
        zMin = 0;
        zMax = -1;
        zIncr = 1;
        zWrap = false;
        useWholeCollection = true;
        categoryName = new String("Whole");
        subsetName = new String("Whole");
    }

    public IndexSelectAttributes(int nMoreFields)
    {
        super(IndexSelectAttributes_numAdditionalAtts + nMoreFields);

        maxDim = DIMENSION_THREED;
        dim = DIMENSION_TWOD;
        xAbsMax = -1;
        xMin = 0;
        xMax = -1;
        xIncr = 1;
        xWrap = false;
        yAbsMax = -1;
        yMin = 0;
        yMax = -1;
        yIncr = 1;
        yWrap = false;
        zAbsMax = -1;
        zMin = 0;
        zMax = -1;
        zIncr = 1;
        zWrap = false;
        useWholeCollection = true;
        categoryName = new String("Whole");
        subsetName = new String("Whole");
    }

    public IndexSelectAttributes(IndexSelectAttributes obj)
    {
        super(obj);

        maxDim = obj.maxDim;
        dim = obj.dim;
        xAbsMax = obj.xAbsMax;
        xMin = obj.xMin;
        xMax = obj.xMax;
        xIncr = obj.xIncr;
        xWrap = obj.xWrap;
        yAbsMax = obj.yAbsMax;
        yMin = obj.yMin;
        yMax = obj.yMax;
        yIncr = obj.yIncr;
        yWrap = obj.yWrap;
        zAbsMax = obj.zAbsMax;
        zMin = obj.zMin;
        zMax = obj.zMax;
        zIncr = obj.zIncr;
        zWrap = obj.zWrap;
        useWholeCollection = obj.useWholeCollection;
        categoryName = new String(obj.categoryName);
        subsetName = new String(obj.subsetName);

        SelectAll();
    }

    public int Offset()
    {
        return super.Offset() + super.GetNumAdditionalAttributes();
    }

    public int GetNumAdditionalAttributes()
    {
        return IndexSelectAttributes_numAdditionalAtts;
    }

    public boolean equals(IndexSelectAttributes obj)
    {
        // Create the return value
        return ((maxDim == obj.maxDim) &&
                (dim == obj.dim) &&
                (xAbsMax == obj.xAbsMax) &&
                (xMin == obj.xMin) &&
                (xMax == obj.xMax) &&
                (xIncr == obj.xIncr) &&
                (xWrap == obj.xWrap) &&
                (yAbsMax == obj.yAbsMax) &&
                (yMin == obj.yMin) &&
                (yMax == obj.yMax) &&
                (yIncr == obj.yIncr) &&
                (yWrap == obj.yWrap) &&
                (zAbsMax == obj.zAbsMax) &&
                (zMin == obj.zMin) &&
                (zMax == obj.zMax) &&
                (zIncr == obj.zIncr) &&
                (zWrap == obj.zWrap) &&
                (useWholeCollection == obj.useWholeCollection) &&
                (categoryName.equals(obj.categoryName)) &&
                (subsetName.equals(obj.subsetName)));
    }

    public String GetName() { return "IndexSelect"; }
    public String GetVersion() { return "1.0"; }

    // Property setting methods
    public void SetMaxDim(int maxDim_)
    {
        maxDim = maxDim_;
        Select(0);
    }

    public void SetDim(int dim_)
    {
        dim = dim_;
        Select(1);
    }

    public void SetXAbsMax(int xAbsMax_)
    {
        xAbsMax = xAbsMax_;
        Select(2);
    }

    public void SetXMin(int xMin_)
    {
        xMin = xMin_;
        Select(3);
    }

    public void SetXMax(int xMax_)
    {
        xMax = xMax_;
        Select(4);
    }

    public void SetXIncr(int xIncr_)
    {
        xIncr = xIncr_;
        Select(5);
    }

    public void SetXWrap(boolean xWrap_)
    {
        xWrap = xWrap_;
        Select(6);
    }

    public void SetYAbsMax(int yAbsMax_)
    {
        yAbsMax = yAbsMax_;
        Select(7);
    }

    public void SetYMin(int yMin_)
    {
        yMin = yMin_;
        Select(8);
    }

    public void SetYMax(int yMax_)
    {
        yMax = yMax_;
        Select(9);
    }

    public void SetYIncr(int yIncr_)
    {
        yIncr = yIncr_;
        Select(10);
    }

    public void SetYWrap(boolean yWrap_)
    {
        yWrap = yWrap_;
        Select(11);
    }

    public void SetZAbsMax(int zAbsMax_)
    {
        zAbsMax = zAbsMax_;
        Select(12);
    }

    public void SetZMin(int zMin_)
    {
        zMin = zMin_;
        Select(13);
    }

    public void SetZMax(int zMax_)
    {
        zMax = zMax_;
        Select(14);
    }

    public void SetZIncr(int zIncr_)
    {
        zIncr = zIncr_;
        Select(15);
    }

    public void SetZWrap(boolean zWrap_)
    {
        zWrap = zWrap_;
        Select(16);
    }

    public void SetUseWholeCollection(boolean useWholeCollection_)
    {
        useWholeCollection = useWholeCollection_;
        Select(17);
    }

    public void SetCategoryName(String categoryName_)
    {
        categoryName = categoryName_;
        Select(18);
    }

    public void SetSubsetName(String subsetName_)
    {
        subsetName = subsetName_;
        Select(19);
    }

    // Property getting methods
    public int     GetMaxDim() { return maxDim; }
    public int     GetDim() { return dim; }
    public int     GetXAbsMax() { return xAbsMax; }
    public int     GetXMin() { return xMin; }
    public int     GetXMax() { return xMax; }
    public int     GetXIncr() { return xIncr; }
    public boolean GetXWrap() { return xWrap; }
    public int     GetYAbsMax() { return yAbsMax; }
    public int     GetYMin() { return yMin; }
    public int     GetYMax() { return yMax; }
    public int     GetYIncr() { return yIncr; }
    public boolean GetYWrap() { return yWrap; }
    public int     GetZAbsMax() { return zAbsMax; }
    public int     GetZMin() { return zMin; }
    public int     GetZMax() { return zMax; }
    public int     GetZIncr() { return zIncr; }
    public boolean GetZWrap() { return zWrap; }
    public boolean GetUseWholeCollection() { return useWholeCollection; }
    public String  GetCategoryName() { return categoryName; }
    public String  GetSubsetName() { return subsetName; }

    // Write and read methods.
    public void WriteAtts(CommunicationBuffer buf)
    {
        if(WriteSelect(0, buf))
            buf.WriteInt(maxDim);
        if(WriteSelect(1, buf))
            buf.WriteInt(dim);
        if(WriteSelect(2, buf))
            buf.WriteInt(xAbsMax);
        if(WriteSelect(3, buf))
            buf.WriteInt(xMin);
        if(WriteSelect(4, buf))
            buf.WriteInt(xMax);
        if(WriteSelect(5, buf))
            buf.WriteInt(xIncr);
        if(WriteSelect(6, buf))
            buf.WriteBool(xWrap);
        if(WriteSelect(7, buf))
            buf.WriteInt(yAbsMax);
        if(WriteSelect(8, buf))
            buf.WriteInt(yMin);
        if(WriteSelect(9, buf))
            buf.WriteInt(yMax);
        if(WriteSelect(10, buf))
            buf.WriteInt(yIncr);
        if(WriteSelect(11, buf))
            buf.WriteBool(yWrap);
        if(WriteSelect(12, buf))
            buf.WriteInt(zAbsMax);
        if(WriteSelect(13, buf))
            buf.WriteInt(zMin);
        if(WriteSelect(14, buf))
            buf.WriteInt(zMax);
        if(WriteSelect(15, buf))
            buf.WriteInt(zIncr);
        if(WriteSelect(16, buf))
            buf.WriteBool(zWrap);
        if(WriteSelect(17, buf))
            buf.WriteBool(useWholeCollection);
        if(WriteSelect(18, buf))
            buf.WriteString(categoryName);
        if(WriteSelect(19, buf))
            buf.WriteString(subsetName);
    }

    public void ReadAtts(int index, CommunicationBuffer buf)
    {
        switch(index)
        {
        case 0:
            SetMaxDim(buf.ReadInt());
            break;
        case 1:
            SetDim(buf.ReadInt());
            break;
        case 2:
            SetXAbsMax(buf.ReadInt());
            break;
        case 3:
            SetXMin(buf.ReadInt());
            break;
        case 4:
            SetXMax(buf.ReadInt());
            break;
        case 5:
            SetXIncr(buf.ReadInt());
            break;
        case 6:
            SetXWrap(buf.ReadBool());
            break;
        case 7:
            SetYAbsMax(buf.ReadInt());
            break;
        case 8:
            SetYMin(buf.ReadInt());
            break;
        case 9:
            SetYMax(buf.ReadInt());
            break;
        case 10:
            SetYIncr(buf.ReadInt());
            break;
        case 11:
            SetYWrap(buf.ReadBool());
            break;
        case 12:
            SetZAbsMax(buf.ReadInt());
            break;
        case 13:
            SetZMin(buf.ReadInt());
            break;
        case 14:
            SetZMax(buf.ReadInt());
            break;
        case 15:
            SetZIncr(buf.ReadInt());
            break;
        case 16:
            SetZWrap(buf.ReadBool());
            break;
        case 17:
            SetUseWholeCollection(buf.ReadBool());
            break;
        case 18:
            SetCategoryName(buf.ReadString());
            break;
        case 19:
            SetSubsetName(buf.ReadString());
            break;
        }
    }

    public String toString(String indent)
    {
        String str = new String();
        str = str + indent + "maxDim = ";
        if(maxDim == DIMENSION_ONED)
            str = str + "DIMENSION_ONED";
        if(maxDim == DIMENSION_TWOD)
            str = str + "DIMENSION_TWOD";
        if(maxDim == DIMENSION_THREED)
            str = str + "DIMENSION_THREED";
        str = str + "\n";
        str = str + indent + "dim = ";
        if(dim == DIMENSION_ONED)
            str = str + "DIMENSION_ONED";
        if(dim == DIMENSION_TWOD)
            str = str + "DIMENSION_TWOD";
        if(dim == DIMENSION_THREED)
            str = str + "DIMENSION_THREED";
        str = str + "\n";
        str = str + intToString("xAbsMax", xAbsMax, indent) + "\n";
        str = str + intToString("xMin", xMin, indent) + "\n";
        str = str + intToString("xMax", xMax, indent) + "\n";
        str = str + intToString("xIncr", xIncr, indent) + "\n";
        str = str + boolToString("xWrap", xWrap, indent) + "\n";
        str = str + intToString("yAbsMax", yAbsMax, indent) + "\n";
        str = str + intToString("yMin", yMin, indent) + "\n";
        str = str + intToString("yMax", yMax, indent) + "\n";
        str = str + intToString("yIncr", yIncr, indent) + "\n";
        str = str + boolToString("yWrap", yWrap, indent) + "\n";
        str = str + intToString("zAbsMax", zAbsMax, indent) + "\n";
        str = str + intToString("zMin", zMin, indent) + "\n";
        str = str + intToString("zMax", zMax, indent) + "\n";
        str = str + intToString("zIncr", zIncr, indent) + "\n";
        str = str + boolToString("zWrap", zWrap, indent) + "\n";
        str = str + boolToString("useWholeCollection", useWholeCollection, indent) + "\n";
        str = str + stringToString("categoryName", categoryName, indent) + "\n";
        str = str + stringToString("subsetName", subsetName, indent) + "\n";
        return str;
    }


    // Attributes
    private int     maxDim;
    private int     dim;
    private int     xAbsMax;
    private int     xMin;
    private int     xMax;
    private int     xIncr;
    private boolean xWrap;
    private int     yAbsMax;
    private int     yMin;
    private int     yMax;
    private int     yIncr;
    private boolean yWrap;
    private int     zAbsMax;
    private int     zMin;
    private int     zMax;
    private int     zIncr;
    private boolean zWrap;
    private boolean useWholeCollection;
    private String  categoryName;
    private String  subsetName;
}

