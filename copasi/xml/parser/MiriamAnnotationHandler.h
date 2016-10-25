// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_MiriamAnnotationHandler
#define COPASI_MiriamAnnotationHandler

#include <sstream>
#include "copasi/xml/parser/CXMLHandler.h"

class MiriamAnnotationHandler : public CXMLHandler
{
private:
  MiriamAnnotationHandler();

public:
  /**
   * Constructor
   * @param CXMLParser & parser
   * @param CXMLParserData & data
   */
  MiriamAnnotationHandler(CXMLParser & parser, CXMLParserData & data);

  /**
   * Destructor
   */
  virtual ~MiriamAnnotationHandler();

protected:

  /**
   * Process the start of an element
   * @param const XML_Char *pszName
   * @param const XML_Char **papszAttrs
   * @return CXMLHandler * pHandlerToCall
   */
  virtual CXMLHandler * processStart(const XML_Char * pszName,
                                     const XML_Char ** papszAttrs);

  /**
   * Process the end of an element
   * @param const XML_Char *pszName
   * @return bool finished
   */
  virtual bool processEnd(const XML_Char * pszName);

  /**
   * Retrieve the structure containing the process logic for the handler.
   * @return sElementInfo *
   */
  virtual sProcessLogic * getProcessLogic() const;

private:
  /**
   * String stream to handle RDF contents
   */
  std::ostringstream mRDF;

  /**
   * Information whether an element is empty
   */
  std::stack< bool > mElementEmpty;
};

#endif //COPASI_MiriamAnnotationHandler
