// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQFittingWidget.cpp,v $
//   $Revision: 1.12 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/12/18 19:56:21 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQFittingWidget.h"

#include <qvariant.h>
#include "TaskWidget.h"
#include "CQFittingWidget.ui.h"
/*
 *  Constructs a CQFittingWidget which is a child of 'parent', with the
 *  name 'name'.'
 */
CQFittingWidget::CQFittingWidget(QWidget* parent, const char* name)
    : TaskWidget(parent, name)
{
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQFittingWidget::~CQFittingWidget()
{
  destroy();
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQFittingWidget::languageChange()
{
  retranslateUi(this);
}
