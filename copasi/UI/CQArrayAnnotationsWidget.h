// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQArrayAnnotationsWidget.h,v $
//   $Revision: 1.14 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/12/18 19:56:21 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CQARRAYANN_H
#define CQARRAYANN_H

#include <q3vbox.h>
//Added by qt3to4:
#include <Q3GridLayout>
#include <QLabel>
#include "utilities/CAnnotatedMatrix.h"
#include "mathematics.h"

#include <q3hbox.h>
#include <qpushbutton.h>
#include <q3widgetstack.h>

#include "copasi/UI/CQBarChart.h"
#include "copasi/utilities/CAnnotatedMatrix.h"
#include "copasi/mathematics.h"

class Q3GridLayout;
class Q3Table;
class QLabel;

/**
 * Base class for color scales. The derived classes provide algorithms
 * to map a double number to a QColor.
 * The scaling parameters can either be set automatically (by using methods
 * provided by the derived classes) or be determined automatically.
 * For automatic scaling all numbers that are to be displayed (or at least
 * a typical sample) have to be passed to the passValue() method before the
 * getColor() method is used.
 * This class is used by ArrayAnnotationWidget.
 */
class CColorScale
  {
  public:
    CColorScale(): mIsUsed(false){};

    virtual ~CColorScale(){};

    /**
     * this method maps a number to a color.
     */
    virtual QColor getColor(const C_FLOAT64 & number) = 0;

    /**
     * this method starts the calculation of the scaling parameters.
     */
    virtual void startAutomaticParameterCalculation() {};

    /**
     * with this method numbers are passed to the automatic scaling algorithm.
     */
    virtual void passValue(const C_FLOAT64 & /*number*/) {};

    /**
     * this finishes the calculation of the scaling parameters.
     */
    virtual void finishAutomaticParameterCalculation() {};

    /**
     * this is called by the array annotation widget to indicate that the scaler is in use
     */
    void setIsUsed(bool f) {mIsUsed = f;};

    /**
     * if setIsUsed() was used isUsed() can be called to find out if the scaler is
     * already in use. One scaler must not be used in several widgets.
     */
    bool isUsed() const {return mIsUsed;};

  private:
    /**
     * This flag indicates whether the scaler is in use. The widget using the scaler must
     * call setIsUsed() to keep this up to date.
     */
    bool mIsUsed;
  };

/**
 * This returns white, if the absolute value of the number is smaller than the
 * threshold. Otherwise if it is positive, the color is green, if negative red.
 */
class CColorScale1 : public CColorScale
  {
  public:
    CColorScale1();

    void setThreshold(const C_FLOAT64 & n) {m1 = n;};

    virtual QColor getColor(const C_FLOAT64 & number);

  protected:
    C_FLOAT64 m1;
  };

/**
 * This maps a range of numbers to a range of colors.
 * Automatic scaling looks for minimum and maximum of
 * the provided numbers
 */
class CColorScaleSimple : public CColorScale
  {
  public:
    CColorScaleSimple();

    /**
    * Set minimum and maximum of number range
    */
    void setMinMax(const C_FLOAT64 & min, const C_FLOAT64 & max)
    {mMin = min; mMax = max;};

    /**
    * Log scaling is not yet implemented
    */
    void setLog(bool l) {mLog = l;}    ; //log not implemented yet!

    /**
    * If this is true, the number range (if automatically determined)
    * is centered around 0.0.
    */
    void setSymmetric(bool s) {mSym = s;};

    virtual QColor getColor(const C_FLOAT64 & number);

    virtual void startAutomaticParameterCalculation();
    virtual void passValue(const C_FLOAT64 & number);
    virtual void finishAutomaticParameterCalculation();

  protected:
    C_FLOAT64 mMin;
    C_FLOAT64 mMax;
    bool mLog;
    bool mSym;
  };

/**
 * The same mapping as in the base class.
 * Option to set user defined colors for the min and
 * max value.
 */
class CColorScaleAdvanced : public CColorScaleSimple
  {
  public:

    CColorScaleAdvanced();

    virtual QColor getColor(const C_FLOAT64 & number);

    void setColorMin(QColor col);
    void setColorMax(QColor col);

  protected:

    QColor mColorMin;
    QColor mColorMax;
  };

/**
 * the same mapping as in the base class. However the automatic scaling
 * is done using the average of the absolute values of the provided numbers.
 * The average of the absolute values is multiplied by the factor to give the
 * range.
 */
class CColorScaleAverage : public CColorScaleSimple
  {
  public:
    CColorScaleAverage();

    /**
    *
    */
    void setFactor(C_FLOAT64 f) {mFactor = f;};

    virtual void startAutomaticParameterCalculation();
    virtual void passValue(const C_FLOAT64 & number);
    virtual void finishAutomaticParameterCalculation();

  protected:
    C_FLOAT64 mFactor;
    C_FLOAT64 mFloat;
    C_INT32 mInt;
  };

class CColorScaleBiLog : public CColorScale
  {
  public:
    CColorScaleBiLog();

    /**
    *
    */
    void setWhitepoint(const C_FLOAT64 & n) {m1 = log(n);};

    /**
    *
    */
    void setMaxIntensityPoint(const C_FLOAT64 & n) {m2 = log(n);};

    virtual QColor getColor(const C_FLOAT64 & number);

    virtual void startAutomaticParameterCalculation();
    virtual void passValue(const C_FLOAT64 & number);
    virtual void finishAutomaticParameterCalculation();

  protected:
    C_FLOAT64 m1;
    C_FLOAT64 m2;

    C_FLOAT64 mFloat;
    C_INT32 mInt;
  };

//*********************************************************************

/**
 * This Widget displays a CArrayAnnotation (no editing yet)
 */
class CQArrayAnnotationsWidget : public Q3VBox
  {
    Q_OBJECT

  public:

    CQArrayAnnotationsWidget(QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0, bool barChart = true, bool slider = true, bool barChartFirst = false);
    ~CQArrayAnnotationsWidget();

    void setArrayAnnotation(const CArrayAnnotation * pArray);

    /**
     * set an algorithm for color coding. If cs=NULL no color coding is performed. The widget assumes
     * ownership of the scaler and will delete it in its destructor. This means a CColorScale
     * can only be used in one widget.
     */
    void setColorCoding(CColorScale * cs);

    /**
     * returns the color coding algorithm
     */
    CColorScale * getColorCoding() const {return mpColorScale;};

    /**
     * if true the parameters for the color coding are determined automatically
     */
    void setColorScalingAutomatic(bool s) {mAutomaticColorScaling = s;};

    /**
     * enable or disable the display of the dimensions annotation (the upper table)
     */
    void setLegendEnabled(bool b);

    void disableBarChart();

    void disableSlider();

    void setFocusOnTable();

    void setFocusOnBars();

  protected slots:

    void selectionTableChanged(int row, int col);

    void changeContents();

    void tableDoubleClicked();

    void setColumnSize(int dummy1, int dummy2, int size);

  protected:

    void fillTable(unsigned C_INT32 rowIndex, unsigned C_INT32 colIndex,
                   CCopasiAbstractArray::index_type & index);
    void fillTable(unsigned C_INT32 rowIndex,
                   CCopasiAbstractArray::index_type & index);
    void fillTable();

    void fillBarChart();

    /**
     *  only for dimensionality > 2
     */
    void initSelectionTable();

    /**
     *  get the active item from the combo box in the specified
     *  row in the mpSelectionTable
     */
    C_INT32 currentItem(C_INT32 row);

    /**
     *  set the active item of the combo box in the specified
     *  row in the mpSelectionTable
     */
    void setCurrentItem(C_INT32 row, C_INT32 index);

    /**
     *  store the current state of all the combo boxes
     */
    void storeCurrentCombos();

    void clearWidget();

    CQBarChart* plot3d;

    Q3HBox* mpHBoxSelection;
    Q3HBox* mpHBoxContents;
    Q3WidgetStack* mpStack;

    bool showBarChart;
    QPushButton* mpButton;
    double** data;
    std::vector<QColor> mColors;
    void enableBarChart(bool enable);
    void switchToTable();
    void switchToBarChart();

    Q3Table* mpSelectionTable;
    Q3Table* mpContentTable;

    const CArrayAnnotation * mpArray;

    CColorScale* mpColorScale;
    bool mAutomaticColorScaling;

    unsigned C_INT32 mRowIndex;
    unsigned C_INT32 mColIndex;
    CCopasiAbstractArray::index_type mIndex;
    bool mBarChartFilled;
    bool mOneDimensional;
    /**
     * the current active item of all the combo boxes
     */
    std::vector<C_INT32> combos;
  };

#endif
