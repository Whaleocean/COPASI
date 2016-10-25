// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CXMLParserData.h"

CXMLParserData::CXMLParserData():
  pVersion(NULL),
  pModel(NULL),
  CharacterData(),
  mAssignments(),
  pFunctionList(NULL),
  pFunction(NULL),
  pFunctionVariable(NULL),
  FunctionDescription(),
  mPredefinedFunction(),
  mFunctionParameterKeyMap(),
  mpExpression(NULL),
  mKey2ObjectiveFunction(),
  pReaction(NULL),
  pEvent(NULL),
  pEventAssignment(NULL),
  SourceParameterKeys(),
  mKeyMap(),
  StateVariableList(),
  pTaskList(NULL),
  pReportList(NULL),
  pPlotList(NULL),
  pReport(NULL),
  pCurrentTask(NULL),
  pCurrentParameter(NULL),
  ModelParameterGroupStack(),
  pCurrentModelParameter(NULL),
  pCurrentPlot(NULL),
  pCurrentPlotItem(NULL),
  pCurrentChannelSpec(NULL),
  UnmappedKeyParameters(),
  pLayoutList(NULL),
  pCurrentLayout(NULL),
  pCompartmentGlyph(NULL),
  pMetaboliteGlyph(NULL),
  pReactionGlyph(NULL),
  pTextGlyph(NULL),
  //pAdditionalGO(NULL),
  pGeneralGlyph(NULL),
  pCurve(NULL),
  pLineSegment(NULL),
  pMetaboliteReferenceGlyph(NULL),
  pRenderInformation(NULL),
  pGradient(NULL),
  pLineEnding(NULL),
  pStyle(NULL),
  pGroup(NULL),
  pText(NULL),
  pListOfCurveElements(NULL),
  mParameterGroupLevel(0),
  taskReferenceMap(),
  reportReferenceMap(),
  pGUI(NULL),
  pDataModel(NULL),
  pUnitDefinitionImportList(NULL),
  pCurrentUnitDefinition(NULL)
{}
