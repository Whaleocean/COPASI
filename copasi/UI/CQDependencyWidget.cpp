// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#include "CQDependencyWidget.h"

#include <copasi/model/CModel.h>
#include <copasi/model/CModelValue.h>
#include <copasi/model/CChemEqInterface.h>

#include <copasi/function/CExpression.h>

#include <copasi/UI/qtUtilities.h>

CQDependencyWidget::CQDependencyWidget(QWidget *parent, const char *name, Qt::WindowFlags f)
  : CopasiWidget(parent, name, f)
  , mType(UNKNOWN)
  , mpModel(NULL)
  , mResizeTableToRows(true)
{
  setupUi(this);

#if QT_VERSION >= 0x050000
  mpTable->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
#endif
}

CQDependencyWidget::~CQDependencyWidget()
{}

// virtual
QSize CQDependencyWidget::minimumSizeHint() const
{
  int LblHeight = mpLbl->minimumSizeHint().height();
  int TableHeight = mpTable->sizeHint().height();
  QSize SizeHint = CopasiWidget::minimumSizeHint();

  return QSize(SizeHint.width(), std::max(LblHeight, TableHeight));
}

QString
getNameForType(CDependencyType type)
{
  switch (type)
    {
      case COMPARTMENT: return "Compartment";

      case SPECIES: return "Species";

      case PARAMETERS: return "Parameter";

      case REACTION: return "Reaction";

      case EVENT: return "Event";
    }

  return "";
}

void CQDependencyWidget::updateFromDependencies(std::set< const CDataObject * > &elements, std::set<const CDataObject *> &dependencies, const CModel *pModel)
{
  mpModel = pModel;
  bool haveDependentElements = !dependencies.empty();
  setVisible(haveDependentElements);
  mpTable->clearContents();
  int numDependentElements = (int)dependencies.size();
  mpTable->setRowCount(numDependentElements);

  if (!haveDependentElements) return;

  mpTable->setSortingEnabled(false);
  std::set< const CDataObject * >::const_iterator it = dependencies.begin();
  std::set< const CDataObject * >::const_iterator end = dependencies.end();
  int i = 0;

  for (; it != end; ++it, ++i)
    {
      const CDataObject *pObject = *it;
      QTableWidgetItem *item = new QTableWidgetItem(FROM_UTF8(pObject->getObjectName()) + ":");
      item->setData(Qt::UserRole, FROM_UTF8(pObject->getKey()));
      mpTable->setItem(i, 0, item);
      mpTable->setItem(i, 1, new QTableWidgetItem(FROM_UTF8(getDetailsFor(pObject, elements))));
    }

  mpTable->setSortingEnabled(true);
  // resize table to contents
  resizeTable();
  // Provide count of reactions, in label.
  mpLbl->setText(QString("Involved in \n%1 %2%3").arg(numDependentElements).arg(getNameForType(mType)).arg(mType != SPECIES && numDependentElements > 0 ? "s" : ""));
}

std::string
CQDependencyWidget::getDetailsFor(const CDataObject *pObject, std::set< const CDataObject * > &elements)
{

  const CEvent *pEvent = dynamic_cast<const CEvent *>(pObject);

  if (pEvent != NULL) return pEvent->getOriginFor(elements);

  const CReaction *pReaction = dynamic_cast<const CReaction *>(pObject);

  if (pReaction != NULL) return CChemEqInterface::getChemEqString(mpModel, *pReaction, false);

  const CModelEntity *pEntity = dynamic_cast<const CModelEntity *>(pObject);

  std::string Origin;
  std::string Separator;

  if (pEntity != NULL)
    {
      if (pEntity->getExpressionPtr() != NULL &&
          pEntity->getExpressionPtr()->containsCN(elements))
        {
          if (pEntity->getStatus() == CModelEntity::Status::ASSIGNMENT)
            {
              Origin += Separator + "Assignment Expression";
              Separator = "\n";
            }

          if (pEntity->getStatus() == CModelEntity::Status::ODE)
            {
              Origin += Separator + "ODE";
              Separator = "\n";
            }
        }

      if (pEntity->getInitialExpressionPtr() != NULL &&
          pEntity->getInitialExpressionPtr()->containsCN(elements))
        {
          Origin += Separator + "Initial Expression";
          Separator = "\n";
        }
    }

  return Origin.empty() ? pObject->getObjectDisplayName() : Origin;
}

void
CQDependencyWidget::resizeEvent(QResizeEvent *pEvent)
{
  resizeTable();
}

void CQDependencyWidget::resizeTable()
{
  // resize table to contents
  if (mResizeTableToRows)
    {
      mpTable->resizeRowsToContents();
      mpTable->setFixedHeight(mpTable->sizeHint().height());
    }
}

void
CQDependencyWidget::setLabelWidth(int width)
{
  mpLbl->setMinimumWidth(width);
  mpLbl->setFixedWidth(width);
}

int
CQDependencyWidget::getLabelWidth() const
{
  return mpLbl->width();
}

void
CQDependencyWidget::setDependencyType(CDependencyType type)
{
  mType = type;
#if QT_VERSION >= 0x050000
  mpTable->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
#else
  mpTable->verticalHeader()->setResizeMode(mType == REACTION ?
      QHeaderView::ResizeToContents : QHeaderView::Fixed);
  mpTable->setSizePolicy(QSizePolicy::Expanding,
                         mType == REACTION ? QSizePolicy::Expanding : QSizePolicy::MinimumExpanding);
#endif
}

CDependencyType
CQDependencyWidget::getDependencyType() const
{
  return mType;
}

void
CQDependencyWidget::setResizeTableToRows(bool resizeTable)
{
  mResizeTableToRows = resizeTable;
}

bool
CQDependencyWidget::getResizeTableToRows() const
{
  return mResizeTableToRows;
}

int
CQDependencyWidget::getNumDependencies() const
{
  return mpTable->rowCount();
}

void
CQDependencyWidget::rowDoubleClicked(int row, int)
{
  std::string key = TO_UTF8(mpTable->item(row, 0)->data(Qt::UserRole).toString());

  if (key.empty()) return;

  if (mpListView == NULL) return;

  mpListView->switchToOtherWidget(C_INVALID_INDEX, key);
}
