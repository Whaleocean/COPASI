// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQTaskHeaderWidget.cpp,v $
//   $Revision: 1.8 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/12/18 19:57:10 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQTaskHeaderWidget.h"

#include <qvariant.h>
#include "CQTaskHeaderWidget.ui.h"
/*
 *  Constructs a CQTaskHeaderWidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CQTaskHeaderWidget::CQTaskHeaderWidget(QWidget* parent, const char* name, Qt::WindowFlags fl)
    : QWidget(parent, name, fl)
{
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQTaskHeaderWidget::~CQTaskHeaderWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQTaskHeaderWidget::languageChange()
{
  retranslateUi(this);
}
