// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// This class defines a unit, which might be considered
// an enhanced form of metadata, in COPASI. It can merely
// contain the name and symbol of the unit, but is intended
// to also contain a list of the SI units it is derived from.
// This is intended to facilitate unit analysis, user input parsing,
// and easy compatibility to the SBML units representation.

#ifndef CUNIT_DEFINITION_H
#define CUNIT_DEFINITION_H

#include "copasi/utilities/CUnit.h"
//#include "copasi/utilities/CUnitDefinitionDB.h"
#include "copasi/report/CCopasiContainer.h"
#include "model/CAnnotation.h"

class CUnitDefinitionDB;

class CUnitDefinition : public CCopasiContainer, public CUnit, public CAnnotation
{
//  friend std::ostream &operator<<(std::ostream &os, const CUnitDefinition::& o);

public:

// constructors
  /**
   * Default constructor
   * @param const std::string & name (default: "NoName")
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CUnitDefinition(const std::string & name = "NoName",
                  const CCopasiContainer * pParent = NULL);

  /**
   * Kind constructor
   * @param const CBaseUnit::Kind & kind
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CUnitDefinition(const CBaseUnit::Kind & kind,
                  const CCopasiContainer * pParent = NULL);

  /**
  * Copy constructor
  * @param const CUnitDefinition::& src
  * @param const C_FLOAT64 & avogadro
  * @param const CCopasiContainer * pParent
  */
  CUnitDefinition(const CUnitDefinition & src,
                  const C_FLOAT64 & avogadro,
                  const CCopasiContainer * pParent);
  ~CUnitDefinition();

  virtual const std::string & getKey() const;

  static CUnit getSIUnit(const std::string & symbol,
                         const C_FLOAT64 & avogadro);

  static void updateSIUnitDefinitions(CUnitDefinitionDB * Units,
                                      const C_FLOAT64 & avogadro);

  void setSymbol(const std::string &symbol);
  std::string getSymbol() const;

  CUnitDefinition & operator=(const CUnitDefinition & src);

private:
  std::string mSymbol;

  void setup();
};

#endif // CUNIT_DEFINITION_H