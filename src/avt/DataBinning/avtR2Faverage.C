// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

// ************************************************************************* //
//                               avtR2Faverage.C                             //
// ************************************************************************* //

#include <avtR2Faverage.h>

#include <avtParallel.h>


// ****************************************************************************
//  Method: avtR2Faverage constructor
//
//  Programmer: Hank Childs
//  Creation:   February 12, 2006
//
//  Modifications:
//
//    Hank Childs, Sat Feb 25 15:22:19 PST 2006
//    Add undefinedVal.
//
// ****************************************************************************

avtR2Faverage::avtR2Faverage(int nb, double uv) : avtR2Foperator(nb, uv)
{
    running_total = new double[nb];
    count         = new int[nb];
    for (int i = 0 ; i < nb ; i++)
    {
        running_total[i] = 0.;
        count[i]         = 0;
    }
}


// ****************************************************************************
//  Method: avtR2Faverage destructor
//
//  Purpose:
//      Defines the destructor.  Note: this should not be inlined in the header
//      because it causes problems for certain compilers.
//
//  Programmer: Hank Childs
//  Creation:   February 12, 2006
//
// ****************************************************************************

avtR2Faverage::~avtR2Faverage()
{
    delete [] running_total;
    delete [] count;
}


// ****************************************************************************
//  Method: avtR2Faverage::AddData
//
//  Purpose:
//      Adds a single data point to the operator.
//
//  Programmer: Hank Childs
//  Creation:   February 12, 2006
//
// ****************************************************************************

void
avtR2Faverage::AddData(int b, float v)
{
    running_total[b] += v;
    count[b]++;
}


// ****************************************************************************
//  Method: avtR2Faverage::FinalizePass
//
//  Purpose:
//      Finalizes the current pass.  In the case of "average", there is only
//      one pass.  So calculate the final averages and return them.  The caller
//      is responsible for freeing the memory.
//
//  Programmer: Hank Childs
//  Creation:   February 12, 2006
//
//  Modifications:
//
//    Hank Childs, Sat Feb 25 15:22:19 PST 2006
//    Use the "undefinedVal".
//
// ****************************************************************************

float *
avtR2Faverage::FinalizePass(int pass)
{
    float  *rv   = new float[nBins];
    double *rt2  = new double[nBins];
    int    *cnt2 = new int[nBins];
    SumIntArrayAcrossAllProcessors(count, cnt2, nBins);
    SumDoubleArrayAcrossAllProcessors(running_total, rt2, nBins);
    for (int i = 0 ; i < nBins ; i++)
    {
        if (cnt2[i] > 0)
            rv[i] = rt2[i] / cnt2[i];
        else
            rv[i] = undefinedVal;
    }
    delete [] rt2;
    delete [] cnt2;

    return rv;
}


