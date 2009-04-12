// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/SteadyStateWidget.cpp,v $
//   $Revision: 1.119 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2009/04/12 20:02:36 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <q3filedialog.h>

#include <qvariant.h>
#include <qcheckbox.h>
//#include <q3frame.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qradiobutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <q3whatsthis.h>
#include <qmessagebox.h>
//Added by qt3to4:
/*
#include <Q3GridLayout>
#include <Q3VBoxLayout>
 */
#include <QHBoxLayout>

#include "DataModelGUI.h"

#include "SteadyStateWidget.h"
#include "listviews.h"
#include "CQTaskBtnWidget.h"
#include "CQTaskHeaderWidget.h"
#include "CProgressBar.h"
#include "StateWidget.h"

#include "copasi.h"
#include "qtUtilities.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "steadystate/CSteadyStateTask.h"
#include "steadystate/CSteadyStateProblem.h"
#include "model/CModel.h"
#include "utilities/CCopasiException.h"
#include "report/CKeyFactory.h"

/**
 *  Constructs a SteadyStateWidget which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
SteadyStateWidget::SteadyStateWidget(QWidget* parent, const char* name, Qt::WFlags fl)
    : TaskWidget(parent, name, fl)
{
  setupUi(this);

  init();
  retranslateUi(this);

  /*
    if (!name)
      setName("SteadyStateWidget");
    setCaption(trUtf8("SteadyStateWidget"));

  //  SteadyStateWidgetLayout = new Q3VBoxLayout(this, 11, 6, "SteadyStateWidgetLayout");
  //  SteadyStateWidgetLayout = new QVBoxLayout(this, 11, 6, "SteadyStateWidgetLayout");
    SteadyStateWidgetLayout = new QVBoxLayout(this);

    //if a mpMethodLayout is created here, it will be used by addMethodXXX() below.
  //  mpLayoutProblem = new Q3GridLayout(0, 1, 1, 11, 6, "mpLayoutProblem");

  //  mpLayoutProblem = new QGridLayout(0, 1, 1, 11, 6, "mpLayoutProblem");

    QHBoxLayout* hLayout = new QHBoxLayout();

    //*************************

    taskJacobian = new QCheckBox(this, "taskJacobian");
    taskJacobian->setText(trUtf8("calculate Jacobian"));
  //  mpLayoutProblem->addWidget(taskJacobian, 0, 1);
    hLayout->addWidget(taskJacobian);

    taskStability = new QCheckBox(this, "taskStability");
    taskStability->setText(trUtf8("perform Stability Analysis"));
    taskStability->setEnabled(false);
  //  mpLayoutProblem->addWidget(taskStability, 0, 2);
    hLayout->addWidget(taskStability);

  //  SteadyStateWidgetLayout->addLayout(mpLayoutProblem);
    SteadyStateWidgetLayout->addLayout(hLayout);
  //  mpLayoutProblem->addLayout(hLayout, 1, 0);

    line1 = new QFrame(this, "line1");
    line1->setFrameShape(QFrame::HLine);
    line1->setFrameShadow(QFrame::Sunken);
    line1->setFrameShape(QFrame::HLine);
    SteadyStateWidgetLayout->addWidget(line1);
  //  mpLayoutProblem->addWidget(line1);

    // addHLineToGrid(mpMethodLayout, 4, 2);

    //************* parameter table ****************
    // addMethodParameterTable(10, 5);
    //addMethodParameterTableToLayout(5, 2);
  */
  /*QSpacerItem* spacer_3 = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
  TaskWidgetLayout->addMultiCell(spacer_3, 7, 7, 0, 2);*/

  //*******************************************
//  SteadyStateWidgetLayout->addLayout(mpLayoutProblem);

// mpMethodLayout->addMultiCellWidget(mpBtnWidget, 11, 11, 0, 2);
  /*
    // signals and slots connections
    //connect(parameterTable, SIGNAL(valueChanged(int, int)), this, SLOT(parameterValueChanged()));
    connect(taskJacobian, SIGNAL(toggled(bool)), this, SLOT(taskJacobianToggled()));

    // tab order
    //setTabOrder(taskName, bExecutable);
    //setTabOrder(bExecutable, setInitialState);
    //setTabOrder(setInitialState, taskJacobian);
    setTabOrder(taskJacobian, taskStability);
    //setTabOrder(taskStability, parameterTable);
    //setTabOrder(parameterTable, bRunButton);

    mpHeaderWidget->setTaskName("Steady State");

    SteadyStateWidgetLayout->insertWidget(0, mpHeaderWidget);

    std::cout << "from SteadyStateWidget.cpp" << std::endl;
    addMethodParameterTable(0, 0);

    SteadyStateWidgetLayout->addWidget(mpBtnWidget);
  */
}

/*
 *  Destroys the object and frees any allocated resources
 */
SteadyStateWidget::~SteadyStateWidget()
{}

void SteadyStateWidget::languageChange()
{
  retranslateUi(this);
}

void SteadyStateWidget::init()
{
  mpHeaderWidget->setTaskName("Steady State");

  SteadyStateWidgetLayout->insertWidget(0, mpHeaderWidget); // header
  SteadyStateWidgetLayout->insertSpacing(1, 14);      // space between header and body
  SteadyStateWidgetLayout->addWidget(mpBtnWidget);      // 'footer'

  addMethodParameterTable(0, 0);
}

CCopasiMethod * SteadyStateWidget::createMethod(const CCopasiMethod::SubType & /*type*/)
{return NULL; /*CTSSMethod::createTSSMethod(type);*/}

bool SteadyStateWidget::runTask()
{
  if (!commonBeforeRunTask()) return false;

  bool success = true;

  if (!commonRunTask()) success = false;

  if (!commonAfterRunTask()) success = false;

  StateWidget *pResult = dynamic_cast< StateWidget * >(mpListView->findWidgetFromId(211));

  if (pResult) pResult->loadFromBackend();

  if (success && isShown()) mpListView->switchToOtherWidget(211, ""); //change to the results window

  return success;
}

bool SteadyStateWidget::loadTask()
{
  loadCommon();
  loadMethod();

  CSteadyStateTask* mSteadyStateTask =
    dynamic_cast<CSteadyStateTask *>(CCopasiRootContainer::getKeyFactory()->get(mObjectKey));

  if (mSteadyStateTask == NULL)
    return false;

  CSteadyStateProblem* steadystateproblem =
    dynamic_cast<CSteadyStateProblem *>(mSteadyStateTask->getProblem());

  if (steadystateproblem == NULL)
    return false;

  CSteadyStateMethod* steadystatemethod =
    dynamic_cast<CSteadyStateMethod *>(mSteadyStateTask->getMethod());

  if (steadystatemethod == NULL)
    return false;

  bool bJacobian = steadystateproblem->isJacobianRequested();
  bool bStatistics = steadystateproblem->isStabilityAnalysisRequested();
  taskJacobian->setChecked(bJacobian);

  if (bJacobian)
    {
      taskStability->setEnabled(true);
      taskStability->setChecked(bStatistics);
    }

  return true;
}

bool SteadyStateWidget::saveTask()
{
  saveCommon();
  saveMethod();

  CSteadyStateTask* mSteadyStateTask =
    dynamic_cast<CSteadyStateTask *>(CCopasiRootContainer::getKeyFactory()->get(mObjectKey));

  if (mSteadyStateTask == NULL)
    return false;

  CSteadyStateProblem* steadystateproblem =
    dynamic_cast<CSteadyStateProblem *>(mSteadyStateTask->getProblem());

  if (steadystateproblem == NULL)
    return false;

  CSteadyStateMethod* steadystatemethod =
    dynamic_cast<CSteadyStateMethod *>(mSteadyStateTask->getMethod());

  if (steadystatemethod == NULL)
    return false;

  bool bJacobian = taskJacobian->isChecked();
  bool bStatistics = taskStability->isChecked();

  steadystateproblem->setJacobianRequested(bJacobian);
  steadystateproblem->setStabilityAnalysisRequested(bStatistics);

  //loadSteadyStateTask();

  // :TODO Bug 322: This should only be called when actual changes have been saved.
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  (*CCopasiRootContainer::getDatamodelList())[0]->changed();
  return true;
}

void SteadyStateWidget::taskJacobianToggled()
{
  if (!taskJacobian->isChecked())
    {
      taskStability->setChecked(false);
      taskStability->setEnabled(false);
    }
  else taskStability->setEnabled(true);
}
