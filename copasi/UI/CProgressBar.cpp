/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CProgressBar.cpp,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/07/02 13:47:27 $
   End CVS Header */

#include "copasi.h"
#include "CProgressBar.h"
#include <qprogressdialog.h>
#include <qapplication.h>
#include "DataModelGUI.h"

CProgressBar::CProgressBar(DataModelGUI* dm)
{
  mDataModel = dm;
  mpWidget = NULL;
}

bool CProgressBar::init(C_INT32 maxSteps, const std::string & text)
{
  if (!mpWidget)
    mpWidget = new QProgressDialog(text.c_str(), 0, maxSteps,
                                   NULL, "progress_bar", TRUE);
  else
    {
      mpWidget->reset();
      mpWidget->setLabelText(text.c_str());
      mpWidget->setTotalSteps(maxSteps);
    }

  mpWidget->setMinimumDuration(0); //
  mpWidget->setProgress(0);
  mDataModel->getQApp()->processEvents();

  //std::cout << "ProgressBar: init" << std::endl;
  return true;
}

bool CProgressBar::reInit(C_INT32 maxSteps, const std::string & text)
{
  mpWidget->setLabelText(text.c_str());
  mpWidget->setTotalSteps(maxSteps);
  mDataModel->getQApp()->processEvents();

  //std::cout << "ProgressBar: reInit" << std::endl;
  return true;
}

bool CProgressBar::progress(C_INT32 steps)
{
  mpWidget->setProgress(steps);
  mDataModel->getQApp()->processEvents();
  //std::cout << "ProgressBar: progress... " << steps << std::endl;
  return true;
}

bool CProgressBar::finish()
{
  mpWidget->setProgress(mpWidget->totalSteps());
  mpWidget->reset();
  //std::cout << "ProgressBar: finish" << std::endl;
  return true;
}
