/****************************************************************************
 **  $ CopasiUI/MetabolitesWidget.h               
 **  $ Author  : Mudita Singhal
 **  
 ** This is the header file for the Metabolites Widget, i.e the First level 
 ** of Metabolites.
 *****************************************************************************/

#ifndef CONSTANT_SYMBOLS_H
#define CONSTANT_SYMBOLS_H

#include "MyTable.h"
#include "copasi.h"
#include "model/model.h"
#include <qtable.h>
#include <qpushbutton.h>

class ConstantSymbols : public QWidget
  {
    Q_OBJECT

  protected:
    CModel * mModel;
    MyTable * table;
    QPushButton *btnOK;
    QPushButton *btnCancel;

  signals:
    void name(QString &);

  public:
    ConstantSymbols(QWidget *parent, const char * name = 0, WFlags f = 0);
    void loadConstantSymbols(CModel *model);
    void resizeEvent(QResizeEvent * re);

  protected slots:
    virtual void slotBtnOKClicked();
    virtual void slotBtnCancelClicked();
    virtual void slotTableSelectionChanged();

  private:
    void showMessage(QString caption, QString text);
  };

#endif
