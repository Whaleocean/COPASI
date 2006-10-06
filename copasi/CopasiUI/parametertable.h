/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/parametertable.h,v $
   $Revision: 1.13 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/10/06 16:03:42 $
   End CVS Header */

// Copyright � 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef PARAMETERTABLE_H
#define PARAMETERTABLE_H

#include <qtable.h>
#include <qcombobox.h>

#include "copasi.h"
#include "model/CReaction.h"

class CReactionInterface;

class ColorTableItem : public QTableItem
  {
  public:
    ColorTableItem(QTable *t, EditType et, QColor c, const QString txt);
    ~ColorTableItem();
    void setColor(QColor col) {color = col; table()->repaint();}

  private:
    void paint(QPainter *p, const QColorGroup &cg, const QRect &cr, bool selected);

    QColor color;
  };

class ColorCheckTableItem : public QCheckTableItem
  {
  public:
    ColorCheckTableItem(QTable *t, QColor c, const QString txt);
    ~ColorCheckTableItem();
    void setColor(QColor col) {color = col; table()->repaint();}

  private:
    void paint(QPainter *p, const QColorGroup &cg, const QRect &cr, bool selected);

    QColor color;
  };

class ComboItem : public ColorTableItem
  {
  public:
    ComboItem(QTable *t, EditType et, QColor c, const QStringList & sl);
    QWidget *createEditor() const;
    void setContentFromEditor(QWidget *w);
    void setText(const QString &s);

  private:
    QComboBox *cb;
    QStringList mSL;
  };

//table used in the reactions widget

class ParameterTable : public QTable
  {
    Q_OBJECT

  public:
    ParameterTable(QWidget * parent = 0, const char * name = 0);

    void initTable();

  public slots:
    void updateTable(const CReactionInterface & ri, const CModel & model);

  private slots:
    void handleCurrentCell(int row, int col);
    void slotCellChanged(int row, int col);

  signals:
    void signalChanged(int, int, QString);
    void parameterStatusChanged(int, bool);

  private:
    //void initTable();

    //convenience function. It gets a List of all metab names in the CMetabNameInterface format
    static const std::vector<std::string> getListOfAllMetabNames(const CModel & model,
        const CReactionInterface & ri);

    //convenience function.
    static QStringList getListOfAllGlobalParameterNames(const CModel & model);
    //convenience function.
    static QStringList getListOfAllCompartmentNames(const CModel & model);

    int mOldRow;

  public:
    std::vector<C_INT32> mLine2Index;
    std::vector<C_INT32> mIndex2Line;
  };

#endif
//********************************************************************************
