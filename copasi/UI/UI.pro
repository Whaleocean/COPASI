# Begin CVS Header
#   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/UI.pro,v $
#   $Revision: 1.229.2.6 $
#   $Name:  $
#   $Author: shoops $
#   $Date: 2010/03/04 16:27:48 $
# End CVS Header

# Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc., EML Research, gGmbH, University of Heidelberg,
# and The University of Manchester.
# All rights reserved.

# Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
# Properties, Inc. and EML Research, gGmbH.
# All rights reserved.

######################################################################
# $Revision: 1.229.2.6 $ $Author: shoops $ $Date: 2010/03/04 16:27:48 $
######################################################################

LIB = UI

# Input

### Headers that belong to widgets generated from uic4 forms
HEADERS	+= \
  CQCompartment.h \
  CQCompartmentsWidget.h \
  CQDifferentialEquations.h \
  CQEFMListWidget.h \
  CQEFMResultWidget.h \
  CQEFMWidget.h \
  CQEventsWidget.h \
  CQEventWidget1.h \
  CQExpressionMmlStackedWidget.h \
  CQExpressionMmlWidget.h \
  CQFittingItemWidget.h \
  CQFittingWidget.h \
  CQFunctionsWidget.h \
  CQGlobalQuantitiesWidget.h \
  CQLyapWidget.h \
  CQMCAWidget.h \
  CQMergingData.h \
  CQModelValue.h \
  CQMoietiesTaskResult.h \
  CQOptimizationWidget.h \
  CQOptimizationResult.h \
  CQPlotsWidget.h \
  CQPreferenceDialog.h \
  CQProgressDialog.h \
  CQProgressItem.h \
  CQReactionsWidget.h \
  CQReportDefinition.h \
  CQReportsWidget.h \
  CQSpeciesDetail.h \
  CQSpeciesWidget.h \
  CQTrajectoryWidget.h \
  CQTSSAWidget.h \
  CScanWidgetRandom.h \
  CScanWidgetRepeat.h \
  CScanWidgetScan.h \
  CScanWidgetTask.h \
  SensitivitiesWidget.h \
  SliderSettingsDialog.h \
  StateSubwidget.h \
  SteadyStateWidget.h \
  CQExpandModelData.h \
#
### other headers (not belonging to generated widgets)
  AboutDialog.h \
  CColorScale.h \
  CCopasiPlotSelectionDialog.h \
  CCopasiSelectionDialog.h \
  CCopasiSelectionWidget.h \
  CCopasiSimpleSelectionTree.h \
  ChemEqValidator.h \
  CMCAResultWidget.h \
  CopasiFileDialog.h \
  CopasiSlider.h \
  CopasiTableWidget.h \
  copasiWidget.h \
  copasiui3window.h \
  CProgressBar.h \
  CReportDefinitionSelect.h \
  CQArrayAnnotationsWidget.h \
  CQBarChart.h \
  CQBaseDataModel.h \
  CQComboDelegate.h \
  CQCompartmentDM.h \
  CQDateTimeEditDelegate.h \
  CQDateTimeEditTableItem.h \
  CQEFMNetReactionDM.h  \
  CQEFMReactionDM.h \
  CQEFMSpeciesDM.h  \
  CQEventDM.h \
  CQExpressionWidget.h \
  CQFluxModeDM.h \
  CQFunctionDM.h \
  CQGlobalQuantityDM.h \
  CQIcons.h \
  CQLayoutsWidget.h \
  CQLyapResultWidget.h \
  CQMathMatrixWidget.h \
  CQMessageBox.h \
  CQMmlScrollView.h \
  CQPlotDM.h \
  CQReactionDM.h \
  CQReportDM.h \
  CQReportListItem.h \
  CQSBMLFileDialog.h \
  CQSensResultWidget.h \
  CQSortFilterProxyModel.h \
  CQSpecieDM.h \
  CQSpinBoxDelegate.h \
  CQTSSAResultWidget.h \
  CQTSSATimeScaleWidget.h \
  CQUpdatesWidget.h \
  CQValidator.h \
  CScanContainerWidget.h \
  CTabWidget.h \
  CTimeSeriesTable.h \
  DataModelGUI.h \
  DataModel.txt.h \
  FunctionItemWidget.h \
  FunctionWidget1.h \
  listviews.h \
  ModelWidget.h \
  MyLineEdit.h \
  ObjectBrowserDialog.h \
  ObjectBrowserItem.h \
  ObjectBrowserWidget.h \
  ParametersWidget.h \
  parametertable.h \
  qtUtilities.h \
  ReactionsWidget1.h \
  ScanWidget.h \
  SensWidgetComboBox.h \
  SliderDialog.h \
  StateWidget.h \
  TaskWidget.h \
  TimeSeriesWidget.h \
  Tree.h \
  TSSWidget.h

### Source files that belong to widgets generated from uic4 forms
SOURCES	+= \
  CQCompartment.cpp \
  CQCompartmentsWidget.cpp \
  CQDifferentialEquations.cpp \
  CQEFMListWidget.cpp \
  CQEFMResultWidget.cpp \
  CQEFMWidget.cpp \
  CQEventsWidget.cpp \
  CQEventWidget1.cpp \
  CQExpressionMmlStackedWidget.cpp \
  CQExpressionMmlWidget.cpp \
  CQFittingItemWidget.cpp \
  CQFittingWidget.cpp \
  CQFunctionsWidget.cpp \
  CQGlobalQuantitiesWidget.cpp \
  CQLyapWidget.cpp \
  CQMCAWidget.cpp \
  CQMergingData.cpp \
  CQModelValue.cpp \
  CQMoietiesTaskResult.cpp \
  CQOptimizationWidget.cpp \
  CQOptimizationResult.cpp \
  CQPlotsWidget.cpp \
  CQPreferenceDialog.cpp \
  CQProgressDialog.cpp \
  CQProgressItem.cpp \
  CQReactionsWidget.cpp \
  CQReportDefinition.cpp \
  CQReportsWidget.cpp \
  CQSpeciesDetail.cpp \
  CQSpeciesWidget.cpp \
  CQTrajectoryWidget.cpp \
  CQTSSAWidget.cpp \
  CScanWidgetRandom.cpp \
  CScanWidgetRepeat.cpp \
  CScanWidgetScan.cpp \
  CScanWidgetTask.cpp \
  SensitivitiesWidget.cpp \
  SliderSettingsDialog.cpp \
  StateSubwidget.cpp \
  SteadyStateWidget.cpp \
  CQExpandModelData.cpp \
#
### other sources (not belonging to generated widgets)
  AboutDialog.cpp \
  CColorScale.cpp \
  CCopasiPlotSelectionDialog.cpp \
  CCopasiSelectionDialog.cpp \
  CCopasiSelectionWidget.cpp \
  CCopasiSimpleSelectionTree.cpp \
  CMCAResultWidget.cpp \
  CopasiFileDialog.cpp \
  CopasiSlider.cpp \
  CopasiTableWidget.cpp \
  copasiWidget.cpp \
  copasiui3window.cpp \
  CProgressBar.cpp \
  CReportDefinitionSelect.cpp \
  CQArrayAnnotationsWidget.cpp \
  CQBarChart.cpp \
  CQBaseDataModel.cpp \
  CQComboDelegate.cpp \
  CQCompartmentDM.cpp \
  CQDateTimeEditDelegate.cpp \
  CQDateTimeEditTableItem.cpp \
  CQEFMNetReactionDM.cpp  \
  CQEFMReactionDM.cpp \
  CQEFMSpeciesDM.cpp  \
  CQEventDM.cpp \
  CQExpressionWidget.cpp \
  CQFluxModeDM.cpp \
  CQFunctionDM.cpp \
  CQGlobalQuantityDM.cpp \
  CQIcons.cpp \
  CQLayoutsWidget.cpp \
  CQLyapResultWidget.cpp \
  CQMathMatrixWidget.cpp \
  CQMessageBox.cpp \
  CQMmlScrollView.cpp \
  CQPlotDM.cpp \
  CQReactionDM.cpp \
  CQReportDM.cpp \
  CQReportListItem.cpp \
  CQSBMLFileDialog.cpp \
  CQSensResultWidget.cpp \
  CQSortFilterProxyModel.cpp \
  CQSpecieDM.cpp \
  CQSpinBoxDelegate.cpp \
  CQTSSAResultWidget.cpp \
  CQTSSATimeScaleWidget.cpp \
  CQUpdatesWidget.cpp \
  CQValidator.cpp \
  CScanContainerWidget.cpp \
  CTabWidget.cpp \
  CTimeSeriesTable.cpp \
  DataModelGUI.cpp \
  FunctionItemWidget.cpp \
  FunctionWidget1.cpp \
  listviews.cpp \
  ModelWidget.cpp \
  MyLineEdit.cpp \
  ObjectBrowserDialog.cpp \
  ObjectBrowserItem.cpp \
  ObjectBrowserWidget.cpp \
  ParametersWidget.cpp \
  parametertable.cpp \
  qtUtilities.cpp \
  ReactionsWidget1.cpp \
  ScanWidget.cpp \
  SensWidgetComboBox.cpp \
  SliderDialog.cpp \
  StateWidget.cpp \
  TaskWidget.cpp \
  TimeSeriesWidget.cpp \
  Tree.cpp \
  TSSWidget.cpp



!contains(DEFINES, COPASI_TSS) {
  HEADERS -= TSSWidget.h
  SOURCES -= TSSWidget.cpp
}

### uic3 forms
FORMS3 += CMCAResultSubwidget.ui
HEADERS += CMCAResultSubwidget.ui.h
FORMS3 += CQExperimentSelection.ui
HEADERS += CQExperimentSelection.ui.h 
FORMS3 += CQFittingResult.ui
HEADERS += CQFittingResult.ui.h
FORMS3 += CQFittingResultTab1.ui
HEADERS += CQFittingResultTab1.ui.h
FORMS3 += CQMatrixDialog.ui
HEADERS += CQMatrixDialog.ui.h
FORMS3 += CQMoietiesTaskWidget.ui
HEADERS += CQMoietiesTaskWidget.ui.h
FORMS3 += CQSplashWidget.ui
HEADERS += CQSplashWidget.ui.h
FORMS3 += CQStartValueReset.ui
HEADERS += CQStartValueReset.ui.h
FORMS3 += CQTSSAResultSubWidget.ui
HEADERS += CQTSSAResultSubWidget.ui.h
FORMS3 += CQTaskBtnWidget.ui
HEADERS += CQTaskBtnWidget.ui.h
FORMS3 += CQTaskHeaderWidget.ui
HEADERS += CQTaskHeaderWidget.ui.h
FORMS3 += CUpDownSubwidget.ui
HEADERS += CUpDownSubwidget.ui.h
FORMS3 += DefaultplotDialog.ui
HEADERS += DefaultplotDialog.ui.h
FORMS3 += TimeSeriesSubwidget.ui
HEADERS += TimeSeriesSubwidget.ui.h
FORMS3 += objectdebug.ui
HEADERS += objectdebug.ui.h

### uic3 forms that do not work at the moment
#FORMS3 += CQExperimentData.ui
HEADERS += CQExperimentData.h
HEADERS += CQExperimentData.ui.h
SOURCES += CQExperimentData.cpp

#FORMS3 += CQProgressItemBar.ui
HEADERS += CQProgressItemBar.h
HEADERS += CQProgressItemBar.ui.h
SOURCES += CQProgressItemBar.cpp

#FORMS3 += CQProgressItemText.ui
HEADERS += CQProgressItemText.h
HEADERS += CQProgressItemText.ui.h
SOURCES += CQProgressItemText.cpp

#FORMS3 += CQTextDialog.ui
HEADERS += CQTextDialog.h
HEADERS += CQTextDialog.ui.h
SOURCES += CQTextDialog.cpp

FORMS += CQCompartment.ui
FORMS += CQCompartmentsWidget.ui
FORMS += CQDifferentialEquations.ui
FORMS += CQEFMListWidget.ui
FORMS += CQEFMResultWidget.ui
FORMS += CQEFMWidget.ui
FORMS += CQEventsWidget.ui
FORMS += CQEventWidget1.ui
FORMS += CQExpressionMmlStackedWidget.ui
FORMS += CQExpressionMmlWidget.ui
FORMS += CQFittingItemWidget.ui
FORMS += CQFittingWidget.ui
FORMS += CQFunctionsWidget.ui
FORMS += CQGlobalQuantitiesWidget.ui
FORMS += CQLyapWidget.ui
FORMS += CQMCAWidget.ui
FORMS += CQMergingData.ui
FORMS += CQModelValue.ui
FORMS += CQMoietiesTaskResult.ui
FORMS += CQOptimizationWidget.ui
FORMS += CQOptimizationResult.ui
FORMS += CQPlotsWidget.ui
FORMS += CQPreferenceDialog.ui
FORMS += CQProgressDialog.ui
FORMS += CQProgressItem.ui
FORMS += CQReactionsWidget.ui
FORMS += CQReportDefinition.ui
FORMS += CQReportsWidget.ui
FORMS += CQSpeciesDetail.ui
FORMS += CQSpeciesWidget.ui
FORMS += CQTrajectoryWidget.ui
FORMS += CQTSSAWidget.ui
FORMS += CScanWidgetRandom.ui
FORMS += CScanWidgetRepeat.ui
FORMS += CScanWidgetScan.ui
FORMS += CScanWidgetTask.ui
FORMS += SensitivitiesWidget.ui
FORMS += SliderSettingsDialog.ui
FORMS += StateSubwidget.ui
FORMS += SteadyStateWidget.ui
FORMS += CQExpandModelData.ui

contains(COPASI_SRC_PACKAGE, true) {
  HEADERS -= CQDifferentialEquations.h
  SOURCES -= CQDifferentialEquations.cpp
  
  DISTFILES += CQDifferentialEquations.h
  DISTFILES += CQDifferentialEquations.cpp
}

DISTFILES += icons/Copasi.ico \
             icons/Copasi??-Alpha.xpm \
             icons/CopasiDoc.ico \
             icons/CopasiDoc??-Alpha.xpm \
             icons/closeSlider.xpm \
             icons/checkModel.xpm \
             icons/copasi_beta_background.xpm \
             icons/copasi_rc.xpm \
             icons/editSlider.xpm \
             icons/filenew.xpm \
             icons/fileopen.xpm \
             icons/fileprint.xpm \
             icons/filesave.xpm \
             icons/istos.xpm \
             icons/locked.xpm \
             icons/modifier.xpm \
             icons/objectAll.xpm \
             icons/objectNone.xpm \
             icons/objectParts.xpm \
             icons/product.xpm \
             icons/scanwidgetbuttonicon.xpm \
             icons/showSliders.xpm \
             icons/stois.xpm \
             icons/substrate.xpm \
             icons/unlocked.xpm \
             icons/MIRIAM.xpm \
             icons/saveIcon.xpm \
             icons/edit_Icon.xpm \
             icons/photo.xpm
             
include(../lib.pri)

CONFIG += qt 

include(../common.pri)

#ifdef COPASI_LICENSE_COM
contains(USE_LICENSE, COM) {
# FORMS3 += CQRegistrationDialog.ui

  HEADERS += CQRegistrationDialog.h \
             CQRegistrationDialog.ui.h

  SOURCES += CQRegistrationDialog.cpp
}
#endif // COPASI_LICENSE_COM

#The following line was inserted by qt3to4
QT += xml  opengl qt3support 
#The following line was inserted by qt3to4
CONFIG += uic3

