/*******************************************************************
 **  $ CopasiUI/CompartmentsWidget.cpp                 
 **  $ Author  : Mudita Singhal
 **
 ** This file is used to create the GUI FrontPage for the 
 ** information obtained from the data model about the 
 ** Compartments----It is Basically the First level of Compartments
 ********************************************************************/
#include "CompartmentsWidget.h"

#include <qlayout.h>
#include <qwidget.h>
#include <qmessagebox.h>
#include <qfont.h>
#include <qpushbutton.h>

#include "MyTable.h"
#include "model/CModel.h"
#include "model/CCompartment.h"
#include "listviews.h"

/**
 *  Constructs a Widget for the Compartments subsection of the tree.
 *  This widget is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'. 
 *  @param model The CModel class which contains the metabolites 
 *  to be displayed.
 *  @param parent The widget which this widget is a child of.
 *  @param name The object name is a text that can be used to identify 
 *  this QObject. It's particularly useful in conjunction with the Qt Designer.
 *  You can find an object by name (and type) using child(), and more than one 
 *  using queryList(). 
 *  @param flags Flags for this widget. Redfer Qt::WidgetFlags of Qt documentation 
 *  for more information about these flags.
 */
CompartmentsWidget::CompartmentsWidget(QWidget *parent, const char * name, WFlags f)
    : QWidget(parent, name, f)

{
  mModel = NULL;
  binitialized = true;
  mModel = NULL;
  table = new MyTable(0, 2, this, "tblCompartments");
  table->setNumRows(-1);
  QVBoxLayout *vBoxLayout = new QVBoxLayout(this, 0);
  vBoxLayout->addWidget(table);

  //Setting table headers
  QHeader *tableHeader = table->horizontalHeader();
  tableHeader->setLabel(0, "Name");
  tableHeader->setLabel(1, "Volume");

  btnOK = new QPushButton("&OK", this);
  btnCancel = new QPushButton("&Cancel", this);

  QHBoxLayout *hBoxLayout = new QHBoxLayout(vBoxLayout, 0);

  //To match the Table left Vertical Header Column Width.
  hBoxLayout->addSpacing(32);

  hBoxLayout->addSpacing(50);
  hBoxLayout->addWidget(btnOK);
  hBoxLayout->addSpacing(5);
  hBoxLayout->addWidget(btnCancel);
  hBoxLayout->addSpacing(50);

  table->sortColumn (0, true, true);
  table->setSorting (true);
  table->setFocusPolicy(QWidget::WheelFocus);

  // signals and slots connections
  connect(table, SIGNAL(doubleClicked(int, int, int, const QPoint &)), this, SLOT(slotTableCurrentChanged(int, int, int, const QPoint &)));
  connect(this, SIGNAL(name(const QString &)), (ListViews*)parent, SLOT(slotCompartmentTableChanged(const QString &)));

  connect(table, SIGNAL(selectionChanged ()), this, SLOT(slotTableSelectionChanged ()));
  connect(btnOK, SIGNAL(clicked ()), this, SLOT(slotBtnOKClicked()));
  connect(table, SIGNAL(valueChanged(int , int)), this, SLOT(tableValueChanged(int, int)));
}

void CompartmentsWidget::loadCompartments(CModel *model)
{
  if (model != NULL)
    {
      mModel = model;
      //Emptying the table
      int numberOfRows = table->numRows();
      int i;
      for (i = 0; i < numberOfRows; i++)
        {
          table->removeRow(0);
        }

      const CCopasiVectorNS < CCompartment > & compartments =
        mModel->getCompartments();

      C_INT32 noOfCompartmentsRows = compartments.size();

      table->setNumRows(noOfCompartmentsRows);

      //Now filling the table.
      const CCompartment *compartn;
      C_INT32 j;
      for (j = 0; j < noOfCompartmentsRows; j++)
        {
          compartn = compartments[j];
          table->setText(j, 0, compartn->getName().c_str());
          table->setText(j, 1, QString::number(compartn->getVolume()));
        }
    }
}

void CompartmentsWidget::slotTableCurrentChanged(int row,
    int col,
    int C_UNUSED(m) ,
    const QPoint & C_UNUSED(n))
{
  QString x = table->text(row, 0);
  emit name(x);
  //QMessageBox::information(this, "Compartments Widget",x);
}

void CompartmentsWidget::slotTableSelectionChanged()
{
  if (!mModel)
    return;
  if (!table->hasFocus())
    {
      table->setFocus();
    }
}

void CompartmentsWidget::resizeEvent(QResizeEvent * re)
{
  if (isVisible())
    {
      if (binitialized)
        {
          int newWidth = re->size().width();
          newWidth -= 35; //Accounting for the left (vertical) header width.
          float weight0 = 3.5, weight1 = 6.5;
          float weightSum = weight0 + weight1;
          int w0, w1;
          w0 = newWidth * (weight0 / weightSum);
          w1 = newWidth - w0;
          table->setColumnWidth(0, w0);
          table->setColumnWidth(1, w1);
          binitialized = false;
        }
      else
        {
          table->DisableColWidthUpdate();
          int newWidth = re->size().width() - 35;
          int i;

          int totalWidth = 0;
          for (i = 0; i < table->numCols(); i++)
            totalWidth += table->columnWidth(i);

          int minTotalWidth = 0;
          for (i = 0; i < table->numCols(); i++)
            minTotalWidth += table->minColWidth[i];

          //Zoom in
          if (newWidth > (re->oldSize().width() - 35))
            {
              if (newWidth > totalWidth) // can do expansion
                {
                  if (totalWidth < (re->oldSize().width() - 35))
                    for (i = 0; i < table->numCols(); i++) // Do expansion
                      table->setColumnWidth(i, newWidth*table->columnWidth(i) / (re->oldSize().width() - 35));
                  else
                    for (i = 0; i < table->numCols(); i++) // Do expansion
                      table->setColumnWidth(i, float(newWidth)*float(table->columnWidth(i)) / float(totalWidth));
                }
              else
                for (i = 0; i < table->numCols(); i++) // Do not expand
                  table->setColumnWidth(i, table->columnWidth(i));

              table->EnableColWidthUpdate();
              return;
            }
          //Zoom out
          //calculate total Width
          if (newWidth >= totalWidth)    //will not decrease any column width
            {
              for (i = 0; i < table->numCols(); i++)
                table->setColumnWidth(i, table->columnWidth(i));
              table->EnableColWidthUpdate();
              return;
            }
          //will decrease only those larger than the minimum width
          //Less than the user specified total width
          if (newWidth <= minTotalWidth)
            {
              for (i = 0; i < table->numCols(); i++)
                table->setColumnWidth(i, table->minColWidth[i]);
              table->EnableColWidthUpdate();
              return;
            }
          //Bigger than the user specified total width
          for (i = 0; i < table->numCols(); i++) // Do Expansion
            table->setColumnWidth(i, (newWidth - minTotalWidth)*(table->columnWidth(i) - table->minColWidth[i]) / (totalWidth - minTotalWidth) + table->minColWidth[i]);
          table->EnableColWidthUpdate();
          return;
        }
    }
}

/***********ListViews::showMessage(QString caption,QString text)------------------------>
 ** ** Parameters:- 1. QString :- The Title that needs to be displayed in message box
 **              2. QString :_ The Text that needs to be displayed in the message box
 ** Returns  :-  void(Nothing)
 ** Description:- This method is used to show the message box on the screen
 
 ****************************************************************************************/

void CompartmentsWidget::slotBtnOKClicked()
{
  // QMessageBox::information(this, "Compartments Widget", "Do you really want to commit changes");
}

void CompartmentsWidget::slotBtnCancelClicked()
{
  // QMessageBox::information(this, "Compartments Widget", "Do you really want to cancel changes");
  emit signal_emitted(*Compartment_Name);
}

void CompartmentsWidget::tableValueChanged(int C_UNUSED(row),
    int C_UNUSED(col))
{
  /*CWriteConfig *Mod = new CWriteConfig("try.gps");

  CCopasiVectorNS < CCompartment > & compartments1 = mModel->getCompartments();
  CCompartment *compartn1;
  compartn1 = compartments1[row];

  string x = table->text(row, col).latin1();

  if (col == 0)
    {
      compartn1->setName(x);
    }
  else
    {
      compartn1->setVolume(int(x.c_str()));
    }

  compartn1->save(*Mod);
  //Copasi->Compartmentfile.save(*Mod);
  delete Mod; */
}
