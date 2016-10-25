// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ListOfUnsupportedAnnotationsHandler.h"
#include "CXMLParser.h"
#include "utilities/CCopasiMessage.h"

#include "UnsupportedAnnotationHandler.h"

/**
 * Replace ListOfUnsupportedAnnotations with the name type of the handler and implement the
 * three methods below.
 */
ListOfUnsupportedAnnotationsHandler::ListOfUnsupportedAnnotationsHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ListOfUnsupportedAnnotations),
  mUnsupportedAnnotations()
{
  init();
}

// virtual
ListOfUnsupportedAnnotationsHandler::~ListOfUnsupportedAnnotationsHandler()
{}

// virtual
CXMLHandler * ListOfUnsupportedAnnotationsHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  switch (mCurrentElement.first)
    {
      case ListOfUnsupportedAnnotations:
        mUnsupportedAnnotations.clear();
        break;

      case UnsupportedAnnotation:
        pHandlerToCall = getHandler(mCurrentElement.second);
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return pHandlerToCall;
}

// virtual
bool ListOfUnsupportedAnnotationsHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case ListOfUnsupportedAnnotations:
        finished = true;
        break;

      case UnsupportedAnnotation:
      {
        UnsupportedAnnotationHandler * pHandler = static_cast< UnsupportedAnnotationHandler * >(getHandler(UnsupportedAnnotation));
        mUnsupportedAnnotations[pHandler->getName()] = pHandler->getXML();
      }
      break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * ListOfUnsupportedAnnotationsHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {ListOfUnsupportedAnnotations, HANDLER_COUNT}},
    {"ListOfUnsupportedAnnotations", ListOfUnsupportedAnnotations, ListOfUnsupportedAnnotations, {UnsupportedAnnotation, AFTER, HANDLER_COUNT}},
    {"UnsupportedAnnotations", UnsupportedAnnotation, UnsupportedAnnotation, {UnsupportedAnnotation, AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}

const CAnnotation::UnsupportedAnnotation & ListOfUnsupportedAnnotationsHandler::getUnsupportedAnnotations() const
{
  return mUnsupportedAnnotations;
}
