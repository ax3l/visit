/*****************************************************************************
*
* Copyright (c) 2000 - 2019, Lawrence Livermore National Security, LLC
* Produced at the Lawrence Livermore National Laboratory
* LLNL-CODE-442911
* All rights reserved.
*
* This file is  part of VisIt. For  details, see https://visit.llnl.gov/.  The
* full copyright notice is contained in the file COPYRIGHT located at the root
* of the VisIt distribution or at http://www.llnl.gov/visit/copyright.html.
*
* Redistribution  and  use  in  source  and  binary  forms,  with  or  without
* modification, are permitted provided that the following conditions are met:
*
*  - Redistributions of  source code must  retain the above  copyright notice,
*    this list of conditions and the disclaimer below.
*  - Redistributions in binary form must reproduce the above copyright notice,
*    this  list of  conditions  and  the  disclaimer (as noted below)  in  the
*    documentation and/or other materials provided with the distribution.
*  - Neither the name of  the LLNS/LLNL nor the names of  its contributors may
*    be used to endorse or promote products derived from this software without
*    specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR  IMPLIED WARRANTIES, INCLUDING,  BUT NOT  LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS FOR A PARTICULAR  PURPOSE
* ARE  DISCLAIMED. IN  NO EVENT  SHALL LAWRENCE  LIVERMORE NATIONAL  SECURITY,
* LLC, THE  U.S.  DEPARTMENT OF  ENERGY  OR  CONTRIBUTORS BE  LIABLE  FOR  ANY
* DIRECT,  INDIRECT,   INCIDENTAL,   SPECIAL,   EXEMPLARY,  OR   CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT  LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR
* SERVICES; LOSS OF  USE, DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER
* CAUSED  AND  ON  ANY  THEORY  OF  LIABILITY,  WHETHER  IN  CONTRACT,  STRICT
* LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY  WAY
* OUT OF THE  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
* DAMAGE.
*
*****************************************************************************/

// ************************************************************************* //
//  File: avtStatisticalTrendsFilter.h
// ************************************************************************* //

#ifndef AVT_STATISTICALTRENDS_FILTER_H
#define AVT_STATISTICALTRENDS_FILTER_H

//#include <avtPluginDataTreeIterator.h>
#include <avtPluginFilter.h>
#include <avtTimeLoopFilter.h>
#include <avtDatasetToDatasetFilter.h>

#include <avtExtents.h>

#include <StatisticalTrendsAttributes.h>

class vtkDataSet;

// ****************************************************************************
//  Class: avtStatisticalTrendsFilter
//
//  Purpose:
//      A plugin operator for StatisticalTrends. This operator traces 
//      a set of particles based on a given ID variable through time. The
//      operator iterates through the time series and connects the locations
//      of the given particles to compute theit trend. The operator creates
//      a new vtkUnstructuredGrid dataset with the pahts as output.
//
//  Programmer: childs -- generated by xml2avt
//  Creation:   Fri Jan 25 11:02:55 PDT 2008
//
// ****************************************************************************

class avtStatisticalTrendsFilter : virtual public avtPluginFilter,
                                   virtual public avtTimeLoopFilter,
                                   virtual public avtDatasetToDatasetFilter
{
  public:
                         avtStatisticalTrendsFilter();
    virtual             ~avtStatisticalTrendsFilter();

    static avtFilter    *Create();

    virtual const char  *GetType(void)  { return "avtStatisticalTrendsFilter"; };
    virtual const char  *GetDescription(void)
                             { return "StatisticalTrends"; };

    virtual void         SetAtts(const AttributeGroup*);
    virtual bool         Equivalent(const AttributeGroup*);

  protected:
    StatisticalTrendsAttributes atts;

    virtual void InitializeTimeLoop(void);

    virtual void ExamineContract(avtContract_p in_contract);
    virtual void UpdateDataObjectInfo();

    virtual avtContract_p ModifyContract(avtContract_p in_spec);
    virtual void Execute(void);
    virtual void CreateFinalOutput(void);
    virtual bool ExecutionSuccessful(void);

  protected:
    std::vector< vtkDataSet* > trend_ds;

    vtkDataSet *sumX_ds, *sumY_ds, *sumX2_ds, *sumY2_ds, *sumXY_ds,
       *slope_ds, *intercept_ds, *out_ds;

    std::string outVarName;

    bool validTimeAxis;
    double lastTimeAxisValue;

    std::string mainVariable;   
    bool haveData;

    int numTypes;
    char typeString[6][12];
};
#endif
