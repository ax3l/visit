// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

// ************************************************************************* //
//                        avtMultipleInputQuery.C                            //
// ************************************************************************* //

#include <avtMultipleInputQuery.h>


// ****************************************************************************
//  Method: avtMultipleInputQuery constructor
//
//  Programmer: Hank Childs 
//  Creation:   October 3, 2003 
//
// ****************************************************************************

avtMultipleInputQuery::avtMultipleInputQuery() : avtMultipleInputSink() 
{
    resValue = 0.;
}


// ****************************************************************************
//  Method: avtMultipleInputQuery destructor
//
//  Purpose:
//      Defines the destructor.  Note: this should not be inlined in the header
//      because it causes problems for certain compilers.
//
//  Programmer: Hank Childs
//  Creation:   February 5, 2004
//
// ****************************************************************************

avtMultipleInputQuery::~avtMultipleInputQuery()
{
    ;
}


// ****************************************************************************
//  Method: avtMultipleInputQuery::PerformQuery
//
//  Purpose:
//    Perform  the requested query. 
//
//  Programmer: Hank Childs 
//  Creation:   October 3, 2003 
//
// ****************************************************************************

void
avtMultipleInputQuery::PerformQuery(QueryAttributes *qA)
{
    queryAtts = *qA;

    Execute();

    //
    // Retrieve the query results and set the message in the atts. 
    //
    queryAtts.SetResultsMessage(resMsg);
    queryAtts.SetResultsValue(resValue);
    UpdateProgress(1, 0);

    *qA = queryAtts;
}


