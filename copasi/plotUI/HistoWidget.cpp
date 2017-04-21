// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <QtCore/QVariant>

#include "HistoWidget.h"
#include "CQPlotEditWidget.h"
#include "CQPlotSubwidget.h"

#include "copasi/UI/CCopasiSelectionDialog.h"
#include "copasi/resourcesUI/CQIconResource.h"

#include "copasi/copasi.h"

#include "copasi/UI/qtUtilities.h"

#include "copasi/plot/CPlotItem.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/model/CModel.h"
#include "copasi/CopasiDataModel/CDataModel.h"

HistoWidget::HistoWidget(QWidget* parent, Qt::WindowFlags fl):
  CQPlotEditWidget(parent, fl),
  mpObjectX(NULL)
{
  setupUi(this);

  mpBtnVariable->setIcon(CQIconResource::icon(CQIconResource::copasi));
}

HistoWidget::~HistoWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

void HistoWidget::buttonPressedX()
{
  if (!mpModel) return;

  //  mpObjectX = CCopasiSelectionDialog::getObjectSingle(this, CQSimpleSelectionTree::NUMERIC, mpObjectX);
  //mpObjectX = CCopasiSelectionDialog::getObjectSingle(this, CQSimpleSelectionTree::PLOT_OBJECT, mpObjectX);

  std::vector< const CDataObject * > oldSelection;

  if (mpObjectX)
    oldSelection.push_back(mpObjectX);

  std::vector< const CDataObject * > objects =
    CCopasiSelectionDialog::getObjectVector(this,
        CQSimpleSelectionTree::NumericValues,
        &oldSelection);

  if (objects.size() && objects[0])
    {
      mpObjectX = objects[0];
      mpEditVariable->setText(FROM_UTF8(mpObjectX->getObjectDisplayName()));
      mpEditTitle->setText("Histogram: " + FROM_UTF8(mpObjectX->getObjectDisplayName()));
    }
  else
    {
      mpObjectX = NULL;
      mpEditVariable->setText("");
      mpEditTitle->setText("Histogram");
    }

  //check if more than one object was selected...
  if (objects.size() > 1)
    {
      CQPlotSubwidget * pParent;
      QObject* tmp = this;

      while (!(pParent = dynamic_cast< CQPlotSubwidget * >(tmp)) && this)
        tmp = tmp->parent();

      if (pParent) //tell the parent to create the remaining histogram descriptions.
        pParent->createHistograms(objects, mpEditIncrement->text().toDouble());
    }
}

bool HistoWidget::LoadFromCurveSpec(const CPlotItem * curve)
{
  if (!curve)
    {
      // We need to reset the widget to defaults
      mpEditTitle->setText("");

      mpObjectX = NULL;
      mpEditVariable->setText("");

      mpEditIncrement->setText("");

      mpCheckBefore->setChecked(false);
      mpCheckDuring->setChecked(true);
      mpCheckAfter->setChecked(false);

      return true;
    }

  if (curve->getType() != CPlotItem::histoItem1d) return false;

  if (curve->getChannels().size() != 1) return false;

  //title
  mpEditTitle->setText(FROM_UTF8(curve->getTitle()));

  //variable
  mpObjectX = NULL;
  CDataModel* pDataModel = mpModel->getObjectDataModel();
  assert(pDataModel != NULL);

  if (curve->getChannels().size() >= 1)
    mpObjectX = CObjectInterface::DataObject(pDataModel->getObjectFromCN(curve->getChannels()[0]));

  if (mpObjectX == pDataModel)
    {
      mpObjectX = NULL;
    }

  if (mpObjectX != NULL)
    mpEditVariable->setText(FROM_UTF8(mpObjectX->getObjectDisplayName()));
  else
    mpEditVariable->setText("");

  //other parameters:
  mpEditIncrement->setText(QString::number(curve->getValue< C_FLOAT64 >("increment")));

  mpCheckBefore->setChecked(curve->getActivity() & COutputInterface::BEFORE);
  mpCheckDuring->setChecked(curve->getActivity() & COutputInterface::DURING);
  mpCheckAfter->setChecked(curve->getActivity() & COutputInterface::AFTER);

  return true; //TODO
}

bool HistoWidget::SaveToCurveSpec(CPlotItem * curve, const CPlotItem *original /*= NULL*/) const
{

  C_INT32 Activity = 0;

  if (mpCheckBefore->isChecked()) Activity += COutputInterface::BEFORE;

  if (mpCheckDuring->isChecked()) Activity += COutputInterface::DURING;

  if (mpCheckAfter->isChecked()) Activity += COutputInterface::AFTER;

  std::string title = TO_UTF8(mpEditTitle->text());
  CCommonName name = mpObjectX ? mpObjectX->getCN() : CCommonName("");
  C_FLOAT64 increment = mpEditIncrement->text().toDouble();

  bool thingsChanged = false;

  if (original != NULL)
    {
      if (original->getType() != CPlotItem::histoItem1d)
        thingsChanged = true;

      if (thingsChanged || original->getTitle() != title)
        thingsChanged = true;

      if (thingsChanged || original->getValue< C_FLOAT64 >("increment") != increment)
        thingsChanged = true;

      if (thingsChanged || original->getActivity() != Activity)
        thingsChanged = true;

      if (thingsChanged || original->getChannels().size() != 1)
        thingsChanged = true;

      if (thingsChanged || original->getChannels()[0] != name)
        thingsChanged = true;
    }
  else thingsChanged = true;

  if (!thingsChanged)
    return false;

  //title
  curve->setTitle(title);

  //channels
  curve->getChannels().clear();
  curve->getChannels().push_back(CPlotDataChannelSpec(name));

  //other parameters: TODO
  curve->setValue("increment", increment);

  curve->setActivity((COutputInterface::Activity) Activity);

  return true;
}

/**
 * In multiple edit mode, we don't want to edit name & channels
 */
void HistoWidget::setMultipleEditMode(bool mode)
{
  mpEditTitle->setEnabled(!mode);
  mpEditVariable->setEnabled(!mode);
  mpBtnVariable->setEnabled(!mode);
}
