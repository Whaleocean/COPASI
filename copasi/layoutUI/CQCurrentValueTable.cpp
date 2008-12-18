// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CQCurrentValueTable.cpp,v $
//   $Revision: 1.9 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/12/18 17:41:15 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.
#include "CQCurrentValueTable.h"

#include <q3header.h>
#include <q3table.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <q3hbox.h>
//Added by qt3to4:
#include <Q3VBoxLayout>

#include <iostream>

#include "copasi/UI/qtUtilities.h"
#include "copasi/layoutUI/CQLayoutMainWindow.h"

CQCurrentValueTable::CQCurrentValueTable(QWidget *parent, const char *name)
    : QWidget(parent, name)
{
  init();
  this->show();
}

void CQCurrentValueTable::init()
{
  Q3VBoxLayout* pLayout = new Q3VBoxLayout(this);
  this->mpTable = new Q3Table(this);
  pLayout->addWidget(this->mpTable);
  this->mpTable->setNumRows(1);
  this->mpTable->setNumCols(2);
  // set default entry
  Q3Header *header = this->mpTable->horizontalHeader();
  header->setLabel(0, "Metabolite");
  header->setLabel(1, "Concentration");
  header = this->verticalHeader();
  header->hide();
  this->mpTable->setLeftMargin(0);
  this->mpTable->setText(0, 0, "*** no time series load ***");
  this->mpTable->setText(0, 1, "NaN");
  this->mpTable->setColumnReadOnly(1, TRUE);
  Q3HBox* pHBox = new Q3HBox(this);
  pLayout->addWidget(pHBox);
  this->mpCheckAllButton = new QPushButton("Check all", pHBox);
  this->mpUncheckAllButton = new QPushButton("Uncheck all", pHBox);
  connect(this->mpTable, SIGNAL(valueChanged(int, int)), this, SLOT(tableValueChanged(int, int)));
  connect(this->mpCheckAllButton, SIGNAL(clicked()), this, SLOT(slotCheckAllClicked()));
  connect(this->mpUncheckAllButton, SIGNAL(clicked()), this, SLOT(slotUncheckAllClicked()));
  resize(QSize(202, 153).expandedTo(minimumSizeHint()));
}

CQCurrentValueTable::~CQCurrentValueTable()
{}

// sets complete row: 1. name of reactant 2. concentration (or number of particles) value
void CQCurrentValueTable::setRowInTable(int row, std::string key, std::string s, C_FLOAT64 val)
{
  Q3CheckTableItem * pCheckItem = new Q3CheckTableItem(this->mpTable, FROM_UTF8(s));
  pCheckItem->setChecked(true); // initially checked
  this->mpTable->setItem(row, 0, pCheckItem);
  this->mpTable->setText(row, 1, QString::number(val));
  this->setKeyIndex(key, row); // remember which node key is in which row
}

// changes the value in a given row (value in second column is replaced)
void CQCurrentValueTable::updateRowInTable(int row, C_FLOAT64 val)
{
  this->mpTable->setText(row, 1, QString::number(val));
}

// sets (numerical) value as text into the second column of the corresponding reactant (given by row index)
void CQCurrentValueTable::setValue(int row, C_FLOAT64 val)
{
  this->mpTable->setText(row, 1, QString::number(val));
}

void CQCurrentValueTable::setAllBoxesChecked(bool checked)
{
  int i;
  for (i = 0;i < this->mpTable->numRows();i++)
    {
      Q3TableItem *pCell = this->mpTable->item(i, 0);
      if (pCell->rtti() == 2)
        {// is cell a QCheckTableItem?
          Q3CheckTableItem *pCheckItem = dynamic_cast<Q3CheckTableItem *> (pCell);
          // set checkbox item checked
          pCheckItem->setChecked(checked);
          CQLayoutMainWindow * pTmp = dynamic_cast<CQLayoutMainWindow *>(parentWidget()->parentWidget()->parentWidget()->parentWidget());
          assert(pTmp);
          if (pTmp)
            {
              pTmp->addItemInAnimation(this->getKeyForRow(i));
            }
        }
    }
}

void CQCurrentValueTable::setAllBoxesUnchecked()
{
  this->setAllBoxesChecked(false);
}

//store row index for every node key
void CQCurrentValueTable::setKeyIndex(std::string key, int row)
{
  this->mIndexMap.insert(std::pair<int, std::string>
                         (row,
                          key));
}

std::string CQCurrentValueTable::getKeyForRow(int row) const
  {
    std::string s = "";

    std::map<int, std::string>::const_iterator itIndexObj = this->mIndexMap.find(row);
    if (itIndexObj != this->mIndexMap.end())
      {
        s = (*itIndexObj).second;
      }
    return s;
  }

bool CQCurrentValueTable::getValueForRow(int row) const
  {
    Q3TableItem *pCell = this->mpTable->item(row, 0);
    assert(pCell != NULL);
    Q3CheckTableItem *pCheckItem = dynamic_cast<Q3CheckTableItem *> (pCell);
    assert(pCheckItem != NULL);
    return pCheckItem->isChecked();
  }

void CQCurrentValueTable::slotCheckAllClicked()
{
  this->setAllBoxesChecked();
}

void CQCurrentValueTable::slotUncheckAllClicked()
{
  this->setAllBoxesUnchecked();
}

void CQCurrentValueTable::setNumRows(int rows)
{
  this->mpTable->setNumRows(rows);
}

void CQCurrentValueTable::setNumCols(int columns)
{
  this->mpTable->setNumCols(columns);
}

int CQCurrentValueTable::numRows() const
  {
    return this->mpTable->numRows();
  }

Q3Header* CQCurrentValueTable::verticalHeader()
{
  return this->mpTable->verticalHeader();
}

/**
 * This slot is caled whenever a value in the table changes, i.e. whenever
 * a species is activated or deactived by it's checkbox.
 * This information is broadcasted by emitting another signal which contains the row number.
 */
void CQCurrentValueTable::tableValueChanged(int row, int /*column*/)
{
  emit valueChanged(row);
}
