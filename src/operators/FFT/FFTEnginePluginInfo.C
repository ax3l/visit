// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

// ****************************************************************************
//  File: FFTEnginePluginInfo.C
// ****************************************************************************

#include <FFTPluginInfo.h>
#include <avtFFTFilter.h>

VISIT_OPERATOR_PLUGIN_ENTRY_EV(FFT,Engine)

// ****************************************************************************
//  Method: FFTEnginePluginInfo::AllocAvtPluginFilter
//
//  Purpose:
//    Return a pointer to a newly allocated avtPluginFilter.
//
//  Returns:    A pointer to the newly allocated avtPluginFilter.
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// ****************************************************************************

avtPluginFilter *
FFTEnginePluginInfo::AllocAvtPluginFilter()
{
    return new avtFFTFilter;
}
