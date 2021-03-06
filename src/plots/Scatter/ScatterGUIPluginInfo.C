// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

// ****************************************************************************
//  File: ScatterGUIPluginInfo.C
// ****************************************************************************

#include <ScatterPluginInfo.h>
#include <ScatterAttributes.h>
#include <QApplication>
#include <QvisScatterPlotWindow.h>

VISIT_PLOT_PLUGIN_ENTRY(Scatter,GUI)

// ****************************************************************************
//  Method: ScatterGUIPluginInfo::GetMenuName
//
//  Purpose:
//    Return a pointer to the name to use in the GUI menu.
//
//  Returns:    A pointer to the name to use in the GUI menu.
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// ****************************************************************************

QString *
ScatterGUIPluginInfo::GetMenuName() const
{
    return new QString(qApp->translate("PlotNames", "Scatter"));
}


// ****************************************************************************
//  Method: ScatterGUIPluginInfo::CreatePluginWindow
//
//  Purpose:
//    Return a pointer to an plot's attribute window.
//
//  Arguments:
//    type      The type of the plot.
//    attr      The attribute subject for the plot.
//    notepad   The notepad to use for posting the window.
//
//  Returns:    A pointer to the plot's attribute window.
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// ****************************************************************************

QvisPostableWindowObserver *
ScatterGUIPluginInfo::CreatePluginWindow(int type, AttributeSubject *attr,
    const QString &caption, const QString &shortName, QvisNotepadArea *notepad)
{
    return new QvisScatterPlotWindow(type, (ScatterAttributes *)attr,
        caption, shortName, notepad);
}
// ****************************************************************************
// Method: ScatterGUIPluginInfo::CreatePluginWizard
//
// Purpose:
//   Creates a Scatter plot wizard and returns a pointer to it.
//
// Arguments:
//   attr   : The attributes that should be used for the plot.
//   parent : The wizard's parent widget.
//   name   : The name of the wizard.
//
// Returns:    A pointer to the new wizard.
//
// Note:
//
// Programmer: Brad Whitlock
// Creation:   Tue Dec 14 09:48:06 PDT 2004
//
// Modifications:
//   Mark Blair, Mon Aug 21 18:29:00 PDT 2006
//   Made argument sequence compatible with upgraded base class.
//
//   Cyrus Harrison, Wed Aug 18 14:55:58 PDT 2010
//   Pass name of the first var selection to the gui.
//
// ****************************************************************************
#include <QvisScatterPlotWizard.h>
QvisWizard *
ScatterGUIPluginInfo::CreatePluginWizard(AttributeSubject *attr,
    QWidget *parent, const std::string &varName, const avtDatabaseMetaData *md,
    const ExpressionList *expList)
{
    return new QvisScatterPlotWizard(attr, parent,varName);
}


// ****************************************************************************
//  Method: ScatterGUIPluginInfo::XPMIconData
//
//  Purpose:
//    Return a pointer to the icon data.
//
//  Returns:    A pointer to the icon data.
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// ****************************************************************************

#include <Scatter.xpm>
const char **
ScatterGUIPluginInfo::XPMIconData() const
{
    return Scatter_xpm;
}

