// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

// ************************************************************************* //
//  MergeScriptingPluginInfo.C
// ************************************************************************* //
#include <PyMergeOperatorAttributes.h>
#include <MergePluginInfo.h>

VISIT_OPERATOR_PLUGIN_ENTRY(Merge,Scripting)

// ****************************************************************************
// Method: MergeScriptingPluginInfo::InitializePlugin
//
// Purpose:
//   Calls the initialization function for the plugin.
//
// Arguments:
//   subj    : A pointer to the plugin's state object.
//   data    : A pointer to data to be used by the observer function.
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// Modifications:
//
// ****************************************************************************

void
MergeScriptingPluginInfo::InitializePlugin(AttributeSubject *subj,
    void *data)
{
    PyMergeOperatorAttributes_StartUp((MergeOperatorAttributes *)subj, data);
}

// ****************************************************************************
// Method: MergeScriptingPluginInfo::GetMethodTable
//
// Purpose:
//   Returns a pointer to the plugin's Python method table. These methods are
//   added to the top-level visit module's methods.
//
// Arguments:
//   nMethods : Returns the number of methods in the method table.
//
// Returns:    A pointer to the method table.
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// Modifications:
//
// ****************************************************************************

void *
MergeScriptingPluginInfo::GetMethodTable(int *nMethods)
{
    return PyMergeOperatorAttributes_GetMethodTable(nMethods);
}

// ****************************************************************************
// Method: MergeScriptingPluginInfo::TypesMatch
//
// Purpose:
//   Returns whether or not the input PyObject is Merge plot attributes.
//
// Arguments:
//   pyobject : A PyObject cast to void*.
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// Modifications:
//
// ****************************************************************************

bool
MergeScriptingPluginInfo::TypesMatch(void *pyobject)
{
    return PyMergeOperatorAttributes_Check((PyObject *)pyobject);
}

// ****************************************************************************
// Method: MergeScriptingPluginInfo::GetLogString
//
// Purpose:
//   Gets a string representation of the current attributes.
//
// Arguments:
//   val : Whether or not to log state information.
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// Modifications:
//
// ****************************************************************************

char *
MergeScriptingPluginInfo::GetLogString()
{
    std::string s(PyMergeOperatorAttributes_GetLogString());
    char *v = new char[s.size() + 1];
    strcpy(v, s.c_str());
    return v;
}

// ****************************************************************************
// Method: MergeScriptingPluginInfo::SetDefaults
//
// Purpose:
//   Used to set the default values for a plugin's state object.
//
// Arguments:
//   atts : The new state.
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// Modifications:
//
// ****************************************************************************

void
MergeScriptingPluginInfo::SetDefaults(const AttributeSubject *atts)
{
    PyMergeOperatorAttributes_SetDefaults((const MergeOperatorAttributes *)atts);
}
