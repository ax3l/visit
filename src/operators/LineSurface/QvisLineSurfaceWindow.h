// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

#ifndef QVISLINESURFACEWINDOW_H
#define QVISLINESURFACEWINDOW_H

#include <QvisOperatorWindow.h>
#include <AttributeSubject.h>

class LineSurfaceAttributes;
class QLabel;
class QLineEdit;

// ****************************************************************************
// Class: QvisLineSurfaceWindow
//
// Purpose:
//    Defines QvisLineSurfaceWindow class.
//
// Notes:      Autogenerated by xml2window.
//
// Programmer: xml2window
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

class QvisLineSurfaceWindow : public QvisOperatorWindow
{
    Q_OBJECT
  public:
    QvisLineSurfaceWindow(const int type,
                         LineSurfaceAttributes *subj,
                         const QString &caption = QString::null,
                         const QString &shortName = QString::null,
                         QvisNotepadArea *notepad = 0);
    virtual ~QvisLineSurfaceWindow();
    virtual void CreateWindowContents();
  protected:
    void UpdateWindow(bool doAll);
    virtual void GetCurrentValues(int which_widget);
  private slots:
    void startTimeProcessText();
    void endTimeProcessText();
    void strideProcessText();
    void point1ProcessText();
    void point2ProcessText();
  private:
    QLineEdit *startTime;
    QLineEdit *endTime;
    QLineEdit *stride;
    QLineEdit *point1;
    QLineEdit *point2;
    QLabel *startTimeLabel;
    QLabel *endTimeLabel;
    QLabel *strideLabel;
    QLabel *point1Label;
    QLabel *point2Label;

    LineSurfaceAttributes *atts;
};



#endif
