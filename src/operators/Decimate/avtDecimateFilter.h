// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

// ************************************************************************* //
//  File: avtDecimateFilter.h
// ************************************************************************* //

#ifndef AVT_Decimate_FILTER_H
#define AVT_Decimate_FILTER_H

#include <avtPluginDataTreeIterator.h>

#include <DecimateAttributes.h>


// ****************************************************************************
//  Class: avtDecimateFilter
//
//  Purpose:
//      A plugin operator for Decimate.
//
//  Programmer: childs -- generated by xml2info
//  Creation:   Sun Aug 11 08:02:03 PDT 2002
//
//  Modifications:
//    Eric Brugger, Wed Jul 23 11:54:43 PDT 2014
//    Modified the class to work with avtDataRepresentation.
//
// ****************************************************************************

class avtDecimateFilter : public avtPluginDataTreeIterator
{
  public:
                         avtDecimateFilter();
    virtual             ~avtDecimateFilter();

    static avtFilter    *Create();

    virtual const char  *GetType(void)  { return "avtDecimateFilter"; };
    virtual const char  *GetDescription(void)
                             { return "Decimating"; };

    virtual void         SetAtts(const AttributeGroup*);
    virtual bool         Equivalent(const AttributeGroup*);

  protected:
    DecimateAttributes   atts;
    bool                 haveIssuedWarning;

    virtual avtDataRepresentation *ExecuteData(avtDataRepresentation *);
    virtual void          UpdateDataObjectInfo(void);
};


#endif
