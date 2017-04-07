// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <math.h>
#include <string.h>
#include <algorithm>

#include "copasi/copasi.h"

#include "copasi/report/CCopasiRootContainer.h"
#include "copasi/utilities/CUnitDefinition.h"
#include "copasi/utilities/CUnit.h"
#include "copasi/utilities/CUnitParser.h"
#include "copasi/model/CModel.h"
#include "copasi/xml/CCopasiXMLInterface.h"
#include "copasi/utilities/CUnitParser.h"

#include "CCopasiException.h"

std::list< std::pair< std::string, CUnit > > sortSymbols(const std::set< std::string > symbols)
{
  std::list< std::pair< std::string, CUnit > > SortedList;
  std::list< std::pair< std::string, CUnit > >::iterator itList;
  std::list< std::pair< std::string, CUnit > >::iterator endList;

  std::set< std::string >::const_iterator it = symbols.begin();
  std::set< std::string >::const_iterator end = symbols.end();

  for (; it != end; ++it)
    {
      CUnit Unit(*it);

      if (Unit.isUndefined()) continue;

      itList = SortedList.begin();
      endList = SortedList.end();

      for (; itList != endList; ++itList)
        if (itList->second.getUsedSymbols().count(*it)) break;

      SortedList.insert(itList, std::make_pair(*it, Unit));
    }

  SortedList.reverse();
  return SortedList;
}

// static
C_FLOAT64 CUnit::Avogadro(6.022140857e23); // http://physics.nist.gov/cgi-bin/cuu/Value?na (Thu Feb 11 09:57:27 EST 2016)

const char * CUnit::VolumeUnitNames[] =
{"dimensionless", "m\xc2\xb3", "l", "ml", "\xc2\xb5l", "nl", "pl", "fl", NULL};

const char * CUnit::AreaUnitNames[] =
{"dimensionless", "m\xc2\xb2", "dm\xc2\xb2", "cm\xc2\xb2", "mm\xc2\xb2", "\xc2\xb5m\xc2\xb2", "nm\xc2\xb2", "pm\xc2\xb2", "fm\xc2\xb2", NULL};

const char * CUnit::LengthUnitNames[] =
{"dimensionless", "m", "dm", "cm", "mm", "\xc2\xb5m", "nm", "pm", "fm", NULL};

const char * CUnit::TimeUnitNames[] =
{"dimensionless", "d", "h", "min", "s", "ms", "\xc2\xb5s", "ns", "ps", "fs", NULL};

// "mol" is the correct name, however in the COPASI XML files "Mol" is used
// up to build 18

const char * CUnit::QuantityUnitOldXMLNames[] =
{"dimensionless", "Mol", "mMol", "\xc2\xb5Mol", "nMol", "pMol", "fMol", "#", NULL};

const char * CUnit::QuantityUnitNames[] =
{"dimensionless", "mol", "mmol", "\xc2\xb5mol", "nmol", "pmol", "fmol", "#", NULL};

// static
std::string CUnit::replaceSymbol(const std::string & expression,
                                 const std::string & oldSymbol,
                                 const std::string & newSymbol)
{
  if (oldSymbol == newSymbol || expression.empty())
    return expression;

  std::istringstream buffer(expression);

  CUnitParser Parser(&buffer);
  Parser.replaceSymbol(oldSymbol, newSymbol);

  bool success = true;

  try
    {
      success = Parser.yyparse() == 0;
    }
  catch (CCopasiException & /*exception*/)
    {
      success = false;
    }

  return success ? Parser.getReplacedExpression() : expression;
}

void CUnit::replaceSymbol(const std::string & oldSymbol,
                          const std::string & newSymbol)
{
  setExpression(replaceSymbol(mExpression, oldSymbol, newSymbol));
}

// static
std::string CUnit::prettyPrint(const std::string & expression)
{
  CUnit Unit(expression);
  Unit.buildExpression();

  return Unit.getExpression();
}

// constructors
// default
CUnit::CUnit():
  mExpression(""),
  mComponents(),
  mUsedSymbols(),
  mpDimensionless(NULL)
{}

// expression
CUnit::CUnit(const std::string & expression):
  mExpression(""),
  mComponents(),
  mUsedSymbols(),
  mpDimensionless(NULL)
{
  setExpression(expression);
}

// kind
CUnit::CUnit(const CBaseUnit::Kind & kind):
  mExpression(CBaseUnit::getSymbol(kind)),
  mComponents(),
  mUsedSymbols(),
  mpDimensionless(NULL)
{
  // Base units must be created without calling setExpression
  // as this would create an infinite loop.

  if (kind != CBaseUnit::undefined)
    {
      addComponent(CUnitComponent(kind));
      mUsedSymbols.insert(CBaseUnit::getSymbol(kind));
    }
}

// copy constructor
CUnit::CUnit(const CUnit & src):
  mExpression(src.mExpression),
  mComponents(src.mComponents),
  mUsedSymbols(src.mUsedSymbols),
  mpDimensionless(NULL)
{
  if (!mComponents.empty())
    {
      mpDimensionless = const_cast< CUnitComponent * >(&*mComponents.begin());
    }
}

CUnit&
CUnit::operator=(const CUnit & rightSide)
{
  if (&rightSide != this)
    {
      mExpression = rightSide.mExpression;
      mComponents = rightSide.mComponents;
      mUsedSymbols = rightSide.mUsedSymbols;

      if (!mComponents.empty())
        {
          mpDimensionless = const_cast<CUnitComponent *>(&*mComponents.begin());
        }
      else
        {
          mpDimensionless = NULL;
        }
    }

  return *this;
}

CUnit::~CUnit()
{}

//virtual
CIssue CUnit::setExpression(const std::string & expression)
{
  if (expression.empty())
    {
      *this = CBaseUnit::undefined;
      return CIssue(CIssue::eSeverity::Warning, CIssue::eKind::UnitUndefined);
    }

  mExpression = expression;

  return compile();
}

CIssue CUnit::compile()
{
  mComponents.clear();
  mUsedSymbols.clear();
  mpDimensionless = NULL;

  std::istringstream buffer(mExpression);
  CUnitParser Parser(&buffer);

  try
    {
      Parser.yyparse();
    }
  catch (CCopasiException & /*exception*/)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCUnit + 3, mExpression.c_str());
      return CIssue(CIssue::eSeverity::Error, CIssue::eKind::UnitInvalid);
    }

  mComponents = Parser.getComponents();
  mUsedSymbols.insert(Parser.getSymbols().begin(), Parser.getSymbols().end());

  if (!mComponents.empty())
    {
      mpDimensionless = const_cast< CUnitComponent * >(&*mComponents.begin());
    }

  return CIssue::Success;
}

std::string CUnit::getExpression() const
{
  return mExpression;
}

const std::set< std::string > & CUnit::getUsedSymbols() const
{
  return mUsedSymbols;
}

bool CUnit::isDimensionless() const
{
  // The first component is always dimensionless
  return mComponents.size() == 1;
}

bool CUnit::isUndefined() const
{
  return mComponents.empty();
}

void CUnit::addComponent(const CUnitComponent & component)
{
  if (mpDimensionless == NULL)
    {
      mpDimensionless = const_cast< CUnitComponent * >(&*mComponents.insert(CUnitComponent(CBaseUnit::dimensionless, 1.0, 0.0, 0.0)).first);
    }

  // Calculate the effective multiplier
  C_FLOAT64 Multiplier = mpDimensionless->getMultiplier() * component.getMultiplier() * pow(10.0, mpDimensionless->getScale() + component.getScale());

  if (component.getKind() != CBaseUnit::dimensionless)
    {
      std::pair< std::set< CUnitComponent >::iterator, bool > it = mComponents.insert(component);
      CUnitComponent * pComponent = const_cast< CUnitComponent * >(&*it.first);

      // Check whether the new component was inserted.
      if (it.second)
        {
          // Multiplier and scale have been combined with the dimensionless component
          pComponent->setMultiplier(1.0);
          pComponent->setScale(0.0);
        }
      else
        {
          // We need to updated the exponent of the existing component
          pComponent->setExponent(pComponent->getExponent() + component.getExponent());
        }

      // If the component has a zero exponent it can be removed
      if (pComponent->getExponent() == 0.0)
        {
          mComponents.erase(it.first);
        }
    }

  C_FLOAT64 log = log10(Multiplier) / 3.0;

  C_FLOAT64 fractpart;
  C_FLOAT64 Scale;
  fractpart = modf(log, &Scale);

  if (1.0 - fabs(fractpart) < 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon())
    {
      if (log < 0.0)
        {
          Scale -= 1.0;
        }
      else
        {
          Scale += 1.0;
        }
    }

  Scale *= 3.0;

  mpDimensionless->setMultiplier(Multiplier * pow(10, -Scale));
  mpDimensionless->setScale(Scale);
}

const std::set< CUnitComponent > & CUnit::getComponents() const
{
  return mComponents;
}

CUnit CUnit::exponentiate(double exp) const
{
  CUnit Unit(*this);

  std::set< CUnitComponent >::const_iterator it = Unit.getComponents().begin();
  std::set< CUnitComponent >::const_iterator end = Unit.getComponents().end();

  for (; it != end; it++)
    {
      CUnitComponent * pComponent = const_cast< CUnitComponent * >(&*it);

      pComponent->setMultiplier(pow(pComponent->getMultiplier(), exp));
      pComponent->setScale(pComponent->getScale() * exp);
      pComponent->setExponent(pComponent->getExponent() * exp);
    }

  return Unit;
}

// Putting units next to each other implies multiplying them.
CUnit CUnit::operator*(const CUnit & rightSide) const
{
  if (*this == CBaseUnit::undefined ||
      rightSide == CBaseUnit::undefined)
    {
      return CUnit();
    }

  CUnit Unit(*this);
  std::set< CUnitComponent >::const_iterator it = rightSide.mComponents.begin();
  std::set< CUnitComponent >::const_iterator end = rightSide.mComponents.end();

  for (; it != end; ++it)
    {
      Unit.addComponent(*it);
    }

  Unit.mUsedSymbols.insert(rightSide.mUsedSymbols.begin(), rightSide.mUsedSymbols.end());

  return Unit;
}

bool CUnit::operator==(const CUnit & rightSide) const
{
  if (mComponents.size() != rightSide.mComponents.size())
    {
      return false;
    }

  std::set< CUnitComponent >::const_iterator it = mComponents.begin(),
                                             end = mComponents.end(),
                                             itRhs = rightSide.mComponents.begin();

  for (; it != end; ++it, ++itRhs)
    {
      if (*it == *itRhs ||
          (it->getKind() == CBaseUnit::dimensionless &&
           itRhs->getKind() == CBaseUnit::dimensionless &&
           fabs(it->getMultiplier() * pow(10.0, it->getScale()) / itRhs->getMultiplier() * pow(10.0, itRhs->getScale()) - 1) < 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon()))
        {
          continue;
        }

      return false;
    }

  return true;
}

bool CUnit::operator<(const CUnit & rightSide) const
{
  if (mComponents.size() != rightSide.mComponents.size()) // RS has more components
    return mComponents.size() < rightSide.mComponents.size();

  if (mUsedSymbols.size() != rightSide.mUsedSymbols.size()) // RS has more symbols
    return mUsedSymbols.size() < rightSide.mUsedSymbols.size();

  // same (non-zero) number of components
  std::set< CUnitComponent >::const_iterator itLS = mComponents.begin(),
                                             itRS = rightSide.mComponents.begin();

  for (; itLS != mComponents.end(); ++itLS, ++itRS)
    {
      if (itLS->getKind() != itRS->getKind())
        {
          return itLS->getKind() < itRS->getKind();
        }

      if (itLS->getMultiplier() != itRS->getMultiplier() ||
          itLS->getScale() != itRS->getScale())
        {
          return itLS->getMultiplier() * pow(10.0, itLS->getScale()) < itRS->getMultiplier() * pow(10.0, itRS->getScale());
        }
    }

  return mExpression < rightSide.mExpression;
}

bool CUnit::isEquivalent(const CUnit & rightSide) const
{
  std::set< CUnitComponent >::const_iterator it = mComponents.begin(),
                                             end = mComponents.end(),
                                             itRhs = rightSide.mComponents.begin(),
                                             endRhs = rightSide.mComponents.end();

  while (it != end && itRhs != endRhs)
    {
      if ((it->getKind() == CBaseUnit::dimensionless &&
           itRhs->getKind() == CBaseUnit::dimensionless) ||
          *it == *itRhs)
        {
          ++it;
          ++itRhs;
        }
      else if (it->getKind() == CBaseUnit::avogadro)
        {
          ++it;
        }
      else if (itRhs->getKind() == CBaseUnit::avogadro)
        {
          ++itRhs;
        }
      else
        {
          return false;
        }
    }

  if ((it != end && it->getKind() != CBaseUnit::avogadro) ||
      (itRhs != endRhs && itRhs->getKind() != CBaseUnit::avogadro)) return false;

  return true;
}

// static
C_INT32 CUnit::getExponentOfSymbol(const std::pair< std::string, CUnit > & SymbolDef, CUnit & unit)
{
  // We ignore base units
  if (CBaseUnit::fromSymbol(SymbolDef.first) != CBaseUnit::undefined) return 0;

  CUnit MultiplyUnit(unit);
  std::pair< C_INT32, C_INT32 > MultiplyResult = removeSymbolFromUnit(SymbolDef.second, MultiplyUnit);

  CUnit DivisionUnit(unit);
  std::pair< C_INT32, C_INT32 > DivisionResult = removeSymbolFromUnit(SymbolDef.second.exponentiate(-1.0), DivisionUnit);

  C_INT32 Exponent = 0;

  if (MultiplyResult.first > DivisionResult.first)
    {
      Exponent = - MultiplyResult.second;
      unit = MultiplyUnit;
    }
  else if (MultiplyResult.first < DivisionResult.first)
    {
      Exponent =  DivisionResult.second;
      unit = DivisionUnit;
    }

  return Exponent;
}

// static
std::pair< C_INT32, C_INT32 > CUnit::removeSymbolFromUnit(const CUnit & symbol, CUnit & unit)
{
  std::pair< C_INT32, C_INT32 > Result = std::make_pair(0, 0);

  while (true)
    {
      CUnit Tmp = unit * symbol;

      std::set< CUnitComponent >::const_iterator itOld = unit.getComponents().begin();
      std::set< CUnitComponent >::const_iterator endOld = unit.getComponents().end();
      std::set< CUnitComponent >::const_iterator itNew = Tmp.getComponents().begin();
      std::set< CUnitComponent >::const_iterator endNew = Tmp.getComponents().end();

      int improvement = 0;

      while (itOld != endOld && itNew != endNew)
        {
          if (itNew->getKind() > itOld->getKind())
            {
              improvement += (int)fabs(itOld->getExponent());
              ++itOld;
            }
          else if (itNew->getKind() < itOld->getKind())
            {
              improvement -= (int)fabs(itNew->getExponent());
              ++itNew;
            }
          else
            {
              // The kind is the same.
              if (fabs(1.0 - itOld->getMultiplier()) < 100 * std::numeric_limits< C_FLOAT64 >::epsilon() &&
                  fabs(1.0 - itNew->getMultiplier()) >= 100 * std::numeric_limits< C_FLOAT64 >::epsilon())
                {
                  improvement -= 1;
                }
              /*
              else if ((itOld->getMultiplier() < 1.0 && itNew->getMultiplier() < itOld->getMultiplier()) ||
                       (itOld->getMultiplier() > 1.0 && itNew->getMultiplier() > itOld->getMultiplier()))
                {
                  improvement -= 100;
                }
              */
              else if (fabs(1.0 - itNew->getMultiplier()) < 100 * std::numeric_limits< C_FLOAT64 >::epsilon() &&
                       fabs(1.0 - itOld->getMultiplier()) >= 100 * std::numeric_limits< C_FLOAT64 >::epsilon())
                {
                  improvement += 1;
                }

              /*
              else if ((itNew->getMultiplier() < 1.0 && itOld->getMultiplier() < itNew->getMultiplier()) ||
                       (itNew->getMultiplier() > 1.0 && itOld->getMultiplier() > itNew->getMultiplier()))
                {
                  improvement += 100;
                }
              */

              // The kind is the same.
              improvement += (int)(fabs(itOld->getExponent()) - fabs(itNew->getExponent()));
              ++itOld;
              ++itNew;
            }
        }

      for (; itNew != endNew; ++itNew)
        {
          improvement -= (int)fabs(itNew->getExponent());
        }

      for (; itOld != endOld; ++itOld)
        {
          improvement += (int)fabs(itOld->getExponent());
        }

      if (improvement >= 0)
        {
          unit = Tmp;

          Result.first += improvement;
          Result.second++;

          continue;
        }

      break;
    }

  return Result;
}
std::vector< CUnit::SymbolComponent > CUnit::getSymbolComponents() const
{
  std::vector< SymbolComponent > SymbolComponents;

  size_t FirstNumeratorIndex = C_INVALID_INDEX;
  size_t FirstDenominatorIndex = C_INVALID_INDEX;
  int FirstNumeratorExponent = 0;
  int FirstDenominatorExponent = 0;

  SymbolComponent Component;

  Component.symbol = "1"; // default dimensionless
  Component.multiplier = 1.0;
  Component.scale = 0;
  Component.exponent = 0;

  CUnit Tmp(*this);

  std::list< std::pair< std::string, CUnit > > UsedDefinitions = sortSymbols(mUsedSymbols);
  size_t Index = 0;

  while (true)
    {
      std::list< std::pair< std::string, CUnit > >::iterator itDef = UsedDefinitions.begin();
      std::list< std::pair< std::string, CUnit > >::iterator endDef = UsedDefinitions.end();

      for (; itDef != endDef; ++itDef)
        {
          C_INT32 Exponent = getExponentOfSymbol(*itDef, Tmp);

          if (Exponent == 0) continue;

          Component.symbol = itDef->first;
          Component.exponent = Exponent;

          SymbolComponents.push_back(Component);

          if (Exponent > 0 &&
              FirstNumeratorIndex == C_INVALID_INDEX)
            {
              FirstNumeratorIndex = Index;
              FirstNumeratorExponent = Exponent;
            }
          else if (Exponent < 0 &&
                   FirstDenominatorIndex == C_INVALID_INDEX)
            {
              FirstDenominatorIndex = Index;
              FirstDenominatorExponent = -Exponent;
            }

          Index++;
          break;
        }

      if (itDef == endDef) break;

      UsedDefinitions.erase(itDef);
    }

  std::set< CUnitComponent >::const_iterator it = Tmp.getComponents().begin();
  std::set< CUnitComponent >::const_iterator end = Tmp.getComponents().end();

  // Find the dimensionless component, and the/a first components
  // which can in the numerator and denominator
  std::set< CUnitComponent >::const_iterator itDimensionless = end;

  for (; it != end; ++it)
    {
      if (itDimensionless == end &&
          it->getKind() == CBaseUnit::dimensionless)
        {
          itDimensionless = it;
          continue;
        }

      C_INT32 Exponent = (C_INT32)it->getExponent();

      Component.symbol = CBaseUnit::getSymbol(it->getKind());
      Component.exponent = Exponent;

      SymbolComponents.push_back(Component);

      if (Exponent > 0 &&
          FirstNumeratorIndex == C_INVALID_INDEX)
        {
          FirstNumeratorIndex = Index;
          FirstNumeratorExponent = Exponent;
        }
      else if (Exponent < 0 &&
               FirstDenominatorIndex == C_INVALID_INDEX)
        {
          FirstDenominatorIndex = Index;
          FirstDenominatorExponent = -Exponent;
        }

      Index++;
    }

  double exponent = 1;

  if (FirstNumeratorExponent > 0)
    exponent = FirstNumeratorExponent;
  else if (FirstDenominatorExponent > 0)
    exponent = FirstDenominatorExponent;

  double multiplier = itDimensionless != end ? fabs(itDimensionless->getMultiplier()) * pow(10.0, itDimensionless->getScale()) : 1.0;
  int scale = 0;

  // Only one, if either, of the
  // following loops should run,
  // to ensure the multiplier is
  // from 1 up to 1000
  while (multiplier >= (1.0 - 100 * std::numeric_limits< double >::epsilon()) * pow(1000, exponent) && scale < 15)
    {
      multiplier /= pow(1000, exponent);
      scale += 3;
    }

  if (multiplier <= 1.0)
    {
      multiplier = 1.0 / multiplier;

      while (multiplier >= (1.0 - 100 * std::numeric_limits< double >::epsilon()) * pow(1000, exponent) && scale > -18)
        {
          multiplier /= pow(1000, exponent);
          scale -= 3;
        }

      multiplier = 1.0 / multiplier;
    }

  if (itDimensionless != end)
    {
      if (FirstNumeratorIndex != C_INVALID_INDEX &&
          SymbolComponents[FirstNumeratorIndex].symbol != "#")
        {
          SymbolComponents[FirstNumeratorIndex].multiplier = multiplier;
          SymbolComponents[FirstNumeratorIndex].scale = scale;
        }
      else if (FirstDenominatorIndex != C_INVALID_INDEX &&
               SymbolComponents[FirstDenominatorIndex].symbol != "#")
        {
          SymbolComponents[FirstDenominatorIndex].multiplier = 1.0 / multiplier;
          SymbolComponents[FirstDenominatorIndex].scale = -scale;
        }
      else if (FirstNumeratorIndex != C_INVALID_INDEX)
        {
          SymbolComponents[FirstNumeratorIndex].multiplier = multiplier;
          SymbolComponents[FirstNumeratorIndex].scale = scale;
        }
      else if (FirstDenominatorIndex != C_INVALID_INDEX)
        {
          SymbolComponents[FirstDenominatorIndex].multiplier = 1.0 / multiplier;
          SymbolComponents[FirstDenominatorIndex].scale = -scale;
        }
      else
        {
          Component.symbol = "1";
          Component.multiplier = multiplier;
          Component.scale = scale;
          SymbolComponents.push_back(Component);
        }
    }

  return SymbolComponents;
}

void CUnit::buildExpression()
{
  std::vector< SymbolComponent > Components = getSymbolComponents();

  if (Components.empty())
    {
      mExpression = "?";
      return;
    }

  std::ostringstream numerator, denominator;
  numerator.str("");
  denominator.str("");

  std::vector< SymbolComponent >::const_iterator it = Components.begin();
  std::vector< SymbolComponent >::const_iterator end = Components.end();

  size_t NumeratorCount = 0;
  size_t DenominatorCount = 0;

  for (; it != end; ++it)
    {
      if (it->exponent > 0)
        {
          if (NumeratorCount > 0)
            {
              numerator << "*";
            }
          else if (fabs(1.0 - it->multiplier) > 100 * std::numeric_limits< double >::epsilon())
            {
              numerator << it->multiplier << "*";
            }

          numerator << CBaseUnit::prefixFromScale(it->scale) << CCopasiRootContainer::quoteUnitDefSymbol(it->symbol);

          if (it->exponent > 1.0)
            {
              numerator << "^" << it->exponent;
            }

          NumeratorCount++;
        }
      else if (it->exponent < 0)
        {
          if (DenominatorCount > 0)
            {
              denominator << "*";
            }
          else if (fabs(1.0 - it->multiplier) > 100 * std::numeric_limits< double >::epsilon())
            {
              denominator << it->multiplier << "*";
              DenominatorCount++;
            }

          denominator << CBaseUnit::prefixFromScale(it->scale) << CCopasiRootContainer::quoteUnitDefSymbol(it->symbol);

          if (it->exponent < -1.0)
            {
              denominator << "^" << -it->exponent;
            }

          DenominatorCount++;
        }
      else
        {
          if (fabs(1.0 - it->multiplier) > 100 * std::numeric_limits< double >::epsilon())
            {
              numerator << it->multiplier << "*";
            }

          numerator << CBaseUnit::prefixFromScale(it->scale) << CCopasiRootContainer::quoteUnitDefSymbol(it->symbol);
          NumeratorCount++;
        }
    }

  mExpression = "";

  if (NumeratorCount == 0 &&
      DenominatorCount > 0)
    {
      numerator << 1.0;
      NumeratorCount++;
    }

  if (NumeratorCount > 0)
    {
      mExpression += numerator.str();
    }

  if (DenominatorCount > 1)
    {
      mExpression += "/(" + denominator.str() + ")";
    }
  else if (DenominatorCount > 0)
    {
      mExpression += "/" + denominator.str();
    }

  stringReplace(mExpression, "^2", "\xc2\xb2");
  stringReplace(mExpression, "^3", "\xc2\xb3");
}

bool CUnit::isUnitType(UnitType type) const
{
  CBaseUnit::Kind kind = CBaseUnit::undefined;
  int exponent;

  switch (type)
    {
      case time:
        kind = CBaseUnit::second;
        exponent = 1;
        break;

      case quantity:
        kind = CBaseUnit::item;
        exponent = 1;
        break;

      case volume:
        kind = CBaseUnit::meter;
        exponent = 3;
        break;

      case area:
        kind = CBaseUnit::meter;
        exponent = 2;
        break;

      case length:
        kind = CBaseUnit::meter;
        exponent = 1;
        break;

      default:
        return false;
    }

  std::set< CUnitComponent >::const_iterator lastComponent = mComponents.end();
  --lastComponent; // (because end points to one after the last one)

  if (mComponents.size() >= 1 && // has to be one or two components
      mComponents.size() <= 2 &&
      ((lastComponent->getKind() == CBaseUnit::dimensionless &&
        getExpression() == "1") || // Include dimensionless, but not rad, sr, etc.
       (lastComponent->getKind() == kind &&
        lastComponent->getExponent() == double(exponent))))
    return true;
  else // includes 0 exponents (undefined)
    return false;
}

// friend
std::ostream &operator<<(std::ostream &os, const CUnit & o)
{
  os << "Expression: " << o.mExpression << std::endl;
  os << "Components: " << std::endl;

  std::set< CUnitComponent >::const_iterator it = o.mComponents.begin();
  std::set< CUnitComponent >::const_iterator end = o.mComponents.end();

  for (; it != end; ++it)
    {
      os << *it;
    }

  return os;
}
