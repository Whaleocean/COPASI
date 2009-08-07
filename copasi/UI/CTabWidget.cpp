// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CTabWidget.cpp,v $
//   $Revision: 1.20 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/08/07 14:18:07 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qtabwidget.h>
#include <qlayout.h>
//Added by qt3to4:
#include <Q3HBoxLayout>

#include "CTabWidget.h"
#include "ModelWidget.h"
#include "MIRIAMUI/CQMiriamWidget.h"
#include "MIRIAMUI/CQRDFListViewWidget.h"

/*
 *  Constructs a CTabWidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'. label is the first
 *  tab name.
 */
CTabWidget::CTabWidget(const QString & label, CopasiWidget * pCopasiWidget,
                       QWidget* parent, const char* name, Qt::WFlags f)
    : CopasiWidget(parent, name, f)
{
  if (!name)
    CopasiWidget::setName("CTabWidget");

  Q3HBoxLayout* tabLayout = new Q3HBoxLayout(this, 0, 0, "tabLayout");
  mTabWidget = new QTabWidget(this, "mTabWidget");
  tabLayout->addWidget(mTabWidget);

  mPages.push_back(pCopasiWidget);
  mTabWidget->addTab(pCopasiWidget, label);

  CQMiriamWidget* pMIRIAMWidget = new CQMiriamWidget(mTabWidget);
  mPages.push_back(pMIRIAMWidget);
  mTabWidget->addTab(mPages[1], "Annotation");

  CQRDFListViewWidget* pRDFListViewWidget = new CQRDFListViewWidget(mTabWidget);
  mPages.push_back(pRDFListViewWidget);
  mTabWidget->addTab(mPages[2], "RDF Browser");
}

/*
 *  Destroys the object and frees any allocated resources
 */
CTabWidget::~CTabWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

bool CTabWidget::leave()
{
  std::vector< CopasiWidget * >::iterator it = mPages.begin();
  std::vector< CopasiWidget * >::iterator end = mPages.end();

  for (; it != end; ++it)
    (*it)->leave();

  return true;
}

bool CTabWidget::enterProtected()
{
  std::vector< CopasiWidget * >::iterator it = mPages.begin();
  std::vector< CopasiWidget * >::iterator end = mPages.end();

  for (; it != end; ++it)
    (*it)->enter(mKey);

  return true;
}

bool CTabWidget::update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key)
{
  std::vector< CopasiWidget * >::iterator it = mPages.begin();
  std::vector< CopasiWidget * >::iterator end = mPages.end();

  for (; it != end; ++it)
    (*it)->update(objectType, action, key);

  return true;
}
