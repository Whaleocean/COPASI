/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQSensResultWidget.h,v $
   $Revision: 1.8 $
   $Name:  $
   $Author: ssahle $
   $Date: 2007/01/10 17:08:16 $
   End CVS Header */

// Copyright � 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CQSENSRESULT_H
#define CQSENSRESULT_H

//#include <qvbox.h>
#include "UI/copasiWidget.h"
#include "CQArrayAnnotationsWidget.h"
#include "utilities/CAnnotatedMatrix.h"
#include "mathematics.h"

class QGridLayout;
//class QLineEdit;
class QLabel;
//class QTable;

class QTabWidget;

class CQSensResultWidget : public CopasiWidget
  {
    Q_OBJECT

  public:
    CQSensResultWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~CQSensResultWidget();

    void newResult();

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");

  protected slots:

  protected:
    //bool loadFromBackend();
    void clearArrays();

    QGridLayout* mWidgetLayout;

    QLabel* mLabelTitle;

    QTabWidget* mpTab;

    CQArrayAnnotationsWidget* mArrayWidget;
    CQArrayAnnotationsWidget* mArrayWidgetScaled;

    const CArrayAnnotation * mpResult;
    const CArrayAnnotation * mpScaledResult;
  };

#endif
