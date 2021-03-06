// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

// ************************************************************************* //
//  File: avtCylinderFilter.h
// ************************************************************************* //

#ifndef AVT_Cylinder_FILTER_H
#define AVT_Cylinder_FILTER_H

#include <avtPluginDataTreeIterator.h>

#include <CylinderAttributes.h>

class vtkImplicitFunction;


// ****************************************************************************
//  Class: avtCylinderFilter
//
//  Purpose:
//      A plugin operator for Cylinder.
//
//  Programmer: childs -- generated by xml2info
//  Creation:   Tue Oct 21 13:17:14 PST 2003
//
//  Modifications:
//    Eric Brugger, Wed Jul 23 11:51:05 PDT 2014
//    Modified the class to work with avtDataRepresentation.
//
// ****************************************************************************

class avtCylinderFilter : public avtPluginDataTreeIterator
{
  public:
                         avtCylinderFilter();
    virtual             ~avtCylinderFilter();

    static avtFilter    *Create();

    virtual const char  *GetType(void)  { return "avtCylinderFilter"; };
    virtual const char  *GetDescription(void)
                             { return "Cylinder"; };

    virtual void         SetAtts(const AttributeGroup*);
    virtual bool         Equivalent(const AttributeGroup*);

  protected:
    CylinderAttributes   atts;
    vtkImplicitFunction *cylinderSlice;

    virtual avtDataRepresentation *ExecuteData(avtDataRepresentation *);
    virtual void          UpdateDataObjectInfo(void);
};


#endif
