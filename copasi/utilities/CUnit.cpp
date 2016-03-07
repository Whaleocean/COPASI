// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <math.h>
#include <string.h>
#include <algorithm>

#include "copasi/report/CCopasiRootContainer.h"
#include "copasi/utilities/CUnitDefinition.h"
#include "copasi/utilities/CUnit.h"
#include "copasi/utilities/CUnitParser.h"
#include "copasi/model/CModel.h"
#include "copasi/xml/CCopasiXMLInterface.h"
#include "copasi/utilities/CUnitParser.h"

#include "CCopasiException.h"

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
  if (oldSymbol == newSymbol)
    return expression;

  std::istringstream buffer(expression);

  CUnitParser Parser(&buffer);
  Parser.setAvogadro(CUnit::Avogadro);
  Parser.replaceSymbol(oldSymbol, newSymbol);

  return (Parser.yyparse() == 0) ? Parser.getReplacedExpression() : expression;
}

// constructors
// default
CUnit::CUnit():
  mExpression(""),
  mComponents(),
  mUsedSymbols()
{
}

// expression
CUnit::CUnit(std::string expression):
  mExpression(""),
  mComponents(),
  mUsedSymbols()
{
  setExpression(expression, Avogadro);
}

// kind
CUnit::CUnit(const CBaseUnit::Kind & kind):
  mExpression(CBaseUnit::getSymbol(kind)),
  mComponents(),
  mUsedSymbols()
{
  mComponents.insert(CUnitComponent(kind));
}

// copy constructor
CUnit::CUnit(const CUnit & src):
  mExpression(src.mExpression),
  mComponents(src.mComponents),
  mUsedSymbols(src.mUsedSymbols)
{}

CUnit::~CUnit()
{}

void CUnit::fromEnum(VolumeUnit volEnum)
{
  mComponents.clear();

  mExpression = VolumeUnitNames[volEnum];

  if (volEnum == CUnit::dimensionlessVolume)
    return; // no need to add component

  CUnitComponent tmpComponent = CUnitComponent(CBaseUnit::meter);
  tmpComponent.setExponent(3);

  switch (volEnum)
    {
      case CUnit::m3:  //default scale = 0
        break;

      case CUnit::l:
        tmpComponent.setScale(-3);
        break;

      case CUnit::ml:
        tmpComponent.setScale(-6);
        break;

      case CUnit::microl:
        tmpComponent.setScale(-9);
        break;

      case CUnit::nl:
        tmpComponent.setScale(-12);
        break;

      case CUnit::pl:
        tmpComponent.setScale(-15);
        break;

      case CUnit::fl:
        tmpComponent.setScale(-18);
        break;

      default:
        return; // just to silence compiler warning
    }

  addComponent(tmpComponent);
}

void CUnit::fromEnum(AreaUnit areaEnum)
{
  mComponents.clear();

  mExpression = AreaUnitNames[areaEnum];

  if (areaEnum == CUnit::dimensionlessArea)
    return; // no need to add component

  CUnitComponent tmpComponent = CUnitComponent(CBaseUnit::meter);
  tmpComponent.setExponent(2);

  switch (areaEnum)
    {
      case CUnit::m2:  //default scale = 0
        break;

      case CUnit::dm2:
        tmpComponent.setScale(-2);
        break;

      case CUnit::cm2:
        tmpComponent.setScale(-4);
        break;

      case CUnit::mm2:
        tmpComponent.setScale(-6);
        break;

      case CUnit::microm2:
        tmpComponent.setScale(-12);
        break;

      case CUnit::nm2:
        tmpComponent.setScale(-18);
        break;

      case CUnit::pm2:
        tmpComponent.setScale(-24);
        break;

      case CUnit::fm2:
        tmpComponent.setScale(-30);
        break;

      default:
        return; // just to silence compiler warning
    }

  addComponent(tmpComponent);
}

void CUnit::fromEnum(LengthUnit lengthEnum)
{
  mComponents.clear();

  mExpression = LengthUnitNames[lengthEnum];

  if (lengthEnum == CUnit::dimensionlessLength)
    return; // no need to add component

  CUnitComponent tmpComponent = CUnitComponent(CBaseUnit::meter);

  switch (lengthEnum)
    {
      case CUnit::m:  //default scale = 0
        break;

      case CUnit::dm:
        tmpComponent.setScale(-1);
        break;

      case CUnit::cm:
        tmpComponent.setScale(-2);
        break;

      case CUnit::mm:
        tmpComponent.setScale(-3);
        break;

      case CUnit::microm:
        tmpComponent.setScale(-6);
        break;

      case CUnit::nm:
        tmpComponent.setScale(-9);
        break;

      case CUnit::pm:
        tmpComponent.setScale(-12);
        break;

      case CUnit::fm:
        tmpComponent.setScale(-15);
        break;

      default:
        return; // just to silence compiler warning
    }

  addComponent(tmpComponent);
}

void CUnit::fromEnum(TimeUnit timeEnum)
{
  mComponents.clear();

  mExpression = TimeUnitNames[timeEnum];

  if (timeEnum == CUnit::dimensionlessTime)
    return; // no need to add component

  CUnitComponent tmpComponent = CUnitComponent(CBaseUnit::second);

  switch (timeEnum)
    {
      case CUnit::d:
        tmpComponent.setMultiplier(60 * 60 * 24);
        break;

      case CUnit::h:
        tmpComponent.setMultiplier(60 * 60);
        break;

      case CUnit::min:
      case CUnit::OldMinute:
        tmpComponent.setMultiplier(60);
        break;

      case CUnit::s:  // defaults are appropriate
        break;

      case CUnit::micros:
        tmpComponent.setScale(-6);
        break;

      case CUnit::ns:
        tmpComponent.setScale(-9);
        break;

      case CUnit::ps:
        tmpComponent.setScale(-12);
        break;

      case CUnit::fs:
        tmpComponent.setScale(-15);
        break;

      default:
        return; // just to silence compiler warning
    }

  addComponent(tmpComponent);
}

void CUnit::fromEnum(QuantityUnit quantityEnum, C_FLOAT64 avogadro)
{
  mComponents.clear();

  mExpression = QuantityUnitNames[quantityEnum];

  if (quantityEnum == CUnit::dimensionlessQuantity)
    return; // no need to add component

  CUnitComponent tmpComponent = CUnitComponent(CBaseUnit::item);

  tmpComponent.setMultiplier(avogadro);

  //   enum QuantityUnit {dimensionlessQuantity = 0, Mol, mMol, microMol, nMol, pMol, fMol, number, OldXML};

  switch (quantityEnum)
    {
      case CUnit::Mol:
        break;

      case CUnit::mMol:
        tmpComponent.setScale(-3);
        break;

      case CUnit::microMol:
        tmpComponent.setScale(-6);
        break;

      case CUnit::nMol:
        tmpComponent.setScale(-9);
        break;

      case CUnit::pMol:
        tmpComponent.setScale(-12);
        break;

      case CUnit::fMol:
        tmpComponent.setScale(-15);
        break;

      case CUnit::number:
      case CUnit::OldXML:
        tmpComponent.setMultiplier(1);
        break;

      default:
        return; // just to silence compiler warning
    }

  addComponent(tmpComponent);
}

bool CUnit::setExpression(const std::string & expression,
                          const C_FLOAT64 & avogadro)
{
  mExpression = expression;

  if (expression.empty())
    {
      mComponents.clear();
      return true;
    }

  return compile(avogadro);
}

bool CUnit::compile(const C_FLOAT64 & avogadro)
{
  mComponents.clear();
  mUsedSymbols.clear();

  // parse the expression into a linked node tree
  std::istringstream buffer(mExpression);
  CUnitParser Parser(&buffer);
  Parser.setAvogadro(avogadro);

  bool success = (Parser.yyparse() == 0);

  if (success)
    {
      mComponents = Parser.getComponents();
      mUsedSymbols = Parser.getSymbols();
    }

  return success;
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
  // Components are a set of unique Kinds.
  // consolodateDimensionless() should ensure any zero-exponent
  // components are integrated into a single, dimensionless, one.
  // So the following should work to retrieve if a unit is dimensionless,
  // but not undefined (no components).
  if (mComponents.size() == 1 &&
      (*mComponents.begin()).getKind() == CBaseUnit::dimensionless)
    return true;
  else
    return false;
}

bool CUnit::isUndefined() const
{
  return mComponents.empty();
}

void CUnit::addComponent(const CUnitComponent & component)
{
  std::set< CUnitComponent >::iterator it = mComponents.find(component);

  if (it != mComponents.end())
    {
      CUnitComponent * pComponent = const_cast< CUnitComponent * >(&*it);

      pComponent->setScale(pComponent->getScale() + component.getScale());
      pComponent->setMultiplier(pComponent->getMultiplier() * component.getMultiplier());

      if (pComponent->getKind() != CBaseUnit::dimensionless)
        {
          pComponent->setExponent(pComponent->getExponent() + component.getExponent());
        }
    }
  else
    {
      mComponents.insert(component);
    }

  consolidateDimensionless();
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

      if (pComponent->getKind() != CBaseUnit::dimensionless)
        {
          pComponent->setExponent(pComponent->getExponent() * exp);
        }
    }

  Unit.consolidateDimensionless();

  return Unit;
}

// Putting units next to each other implies multiplying them.
CUnit & CUnit::operator*(const CUnit & rhs) const
{
  static CUnit Unit; // Make a copy of the first CUnit
  Unit = *this; // Make a copy of the first CUnit

  std::set< CUnitComponent >::const_iterator it = rhs.mComponents.begin();
  std::set< CUnitComponent >::const_iterator end = rhs.mComponents.end();

  for (; it != end; ++it)
    {
      Unit.addComponent(*it);
    }

  Unit.mUsedSymbols.insert(rhs.mUsedSymbols.begin(), rhs.mUsedSymbols.end());

  return Unit; // The calling code might want to call simplifyComponents() on the returned unit.
}

bool CUnit::operator==(const CUnit & rhs) const
{
  return (mExpression == rhs.mExpression);
}

bool CUnit::isEquivalent(const CUnit & rhs) const
{
  if (mComponents.size() != rhs.mComponents.size())
    {
      return false;
    }

  std::set< CUnitComponent >::const_iterator it = mComponents.begin();
  std::set< CUnitComponent >::const_iterator end = mComponents.end();
  std::set< CUnitComponent >::const_iterator itRhs = rhs.mComponents.begin();

  for (; it != end; ++it, ++itRhs)
    {
      if (*it == *itRhs)
        {
          continue;
        }
      else
        return false;
    }

  return true;
}

// static
C_INT32 CUnit::getExponentOfSymbol(const std::string & symbol, CUnit & unit)
{
  // We ignore base units
  if (CBaseUnit::fromSymbol(symbol) != CBaseUnit::undefined) return 0;

  const CUnitDefinition * pUnitDef = CCopasiRootContainer::getUnitDefFromSymbol(symbol);

  if (pUnitDef == NULL) return 0;

  C_INT32 Exponent = 0;

  // First try multiplication
  while (true)
    {
      CUnit Tmp = unit **pUnitDef;

      // Compare symbols to determine whether this simplified the unit
      if (Tmp.getComponents().size() < unit.getComponents().size())
        {
          unit = Tmp;
          Exponent++;

          continue;
        }

      std::set< CUnitComponent >::const_iterator itOld = unit.getComponents().begin();
      std::set< CUnitComponent >::const_iterator endOld = unit.getComponents().end();
      std::set< CUnitComponent >::const_iterator itNew = Tmp.getComponents().begin();
      std::set< CUnitComponent >::const_iterator endNew = Tmp.getComponents().end();

      int improvement = 0;

      while (itOld != endOld && itNew != endNew)
        {
          if (itNew->getKind() > itOld->getKind())
            {
              improvement += fabs(itOld->getExponent());
              ++itOld;
            }
          else if (itNew->getKind() < itOld->getKind())
            {
              improvement -= fabs(itNew->getExponent());
              ++itNew;
            }
          else
            {
              // The kind is the same.
              improvement += fabs(itOld->getExponent()) - fabs(itNew->getExponent());
              ++itOld;
              ++itNew;
            }
        }

      for (; itNew != endNew; ++itNew)
        {
          improvement -= fabs(itNew->getExponent());
        }

      for (; itOld != endOld; ++itOld)
        {
          improvement += fabs(itOld->getExponent());
        }

      if (improvement > 0)
        {
          unit = Tmp;
          Exponent++;

          continue;
        }

      break;
    }

  if (Exponent > 0) return -Exponent;

  // Now try division
  CUnit Inverse = pUnitDef->exponentiate(-1.0);

  while (true)
    {
      CUnit Tmp = unit * Inverse;

      // Compare symbols to determine whether this simplified the unit
      if (Tmp.getComponents().size() < unit.getComponents().size())
        {
          unit = Tmp;
          Exponent++;

          continue;
        }

      std::set< CUnitComponent >::const_iterator itOld = unit.getComponents().begin();
      std::set< CUnitComponent >::const_iterator endOld = unit.getComponents().end();
      std::set< CUnitComponent >::const_iterator itNew = Tmp.getComponents().begin();
      std::set< CUnitComponent >::const_iterator endNew = Tmp.getComponents().end();

      int improvement = 0;

      while (itOld != endOld && itNew != endNew)
        {
          if (itNew->getKind() > itOld->getKind())
            {
              improvement += fabs(itOld->getExponent());
              ++itOld;
            }
          else if (itNew->getKind() < itOld->getKind())
            {
              improvement -= fabs(itNew->getExponent());
              ++itNew;
            }
          else
            {
              // The kind is the same.
              improvement += fabs(itOld->getExponent()) - fabs(itNew->getExponent());
              ++itOld;
              ++itNew;
            }
        }

      for (; itNew != endNew; ++itNew)
        {
          improvement -= fabs(itNew->getExponent());
        }

      for (; itOld != endOld; ++itOld)
        {
          improvement += fabs(itOld->getExponent());
        }

      if (improvement > 0)
        {
          unit = Tmp;
          Exponent++;

          continue;
        }

      break;
    }

  return Exponent;
}

void CUnit::buildExpression()
{
  if (mComponents.empty())
    {
      mExpression = "";
      return;
    }

  if (isEquivalent(CUnit(mExpression))) return;

  std::ostringstream numerator, denominator;
  numerator.str("");
  denominator.str("");

  CUnit Tmp(*this);

  std::set< std::string >::const_iterator itSymbol = mUsedSymbols.begin();
  std::set< std::string >::const_iterator endSymbol = mUsedSymbols.end();

  int FirstNumeratorExponent = 0;
  int FirstDenominatorExponent = 0;
  size_t NumeratorCount = 0;
  size_t DenominatorCount = 0;

  for (; itSymbol != endSymbol; ++itSymbol)
    {
      C_INT32 Exponent = getExponentOfSymbol(*itSymbol, Tmp);

      if (Exponent == 0) continue;

      if (Exponent > 0)
        {
          if (FirstNumeratorExponent > 0)
            numerator << "*";
          else
            FirstNumeratorExponent = Exponent;

          if (Exponent == 1)
            numerator << *itSymbol;
          else
            numerator << *itSymbol << "^" << Exponent;

          NumeratorCount++;
        }
      else
        {
          if (FirstDenominatorExponent > 0)
            denominator << "*";
          else
            FirstDenominatorExponent = -Exponent;

          if (Exponent == -1)
            denominator << *itSymbol;
          else
            denominator << *itSymbol << "^" << -Exponent;

          DenominatorCount++;
        }
    }

  // At this point we have only base kinds left in Tmp

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

      C_INT32 Exponent = it->getExponent();

      if (Exponent > 0)
        {
          if (FirstNumeratorExponent > 0)
            numerator << "*";
          else
            FirstNumeratorExponent = Exponent;

          if (Exponent == 1)
            numerator << CBaseUnit::getSymbol(it->getKind());
          else
            numerator << CBaseUnit::getSymbol(it->getKind()) << "^" << Exponent;

          NumeratorCount++;
        }
      else
        {
          if (FirstDenominatorExponent > 0)
            denominator << "*";
          else
            FirstDenominatorExponent = -Exponent;

          if (Exponent == -1)
            denominator << CBaseUnit::getSymbol(it->getKind());
          else
            denominator << CBaseUnit::getSymbol(it->getKind()) << "^" << -Exponent;

          DenominatorCount++;
        }
    }

  double exponent = 1;

  if (FirstNumeratorExponent > 0)
    exponent = FirstNumeratorExponent;
  else if (FirstDenominatorExponent > 0)
    exponent = FirstDenominatorExponent;

  double multiplier = fabs(itDimensionless->getMultiplier()) * pow(10.0, itDimensionless->getScale());
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

  std::ostringstream expression;

  if (multiplier != 1.0 ||
      (DenominatorCount > 0 && NumeratorCount == 0))
    {
      expression << multiplier;
    }

  if (NumeratorCount > 0)
    {
      if (multiplier != 1.0) expression << "*";

      expression << CBaseUnit::prefixFromScale(scale) << numerator.str();
      scale = 0;
    }

  if (DenominatorCount > 1)
    {
      expression << "/(" <<  CBaseUnit::prefixFromScale(scale) << denominator.str() << ")";
    }
  else if (DenominatorCount > 0)
    {
      expression << "/" << CBaseUnit::prefixFromScale(scale) << denominator.str();
    }

  if (NumeratorCount == 0 &&
      DenominatorCount == 0)
    {
      if (multiplier != 1.0) expression << "*";

      expression << CBaseUnit::prefixFromScale(scale) << "1";
    }

  mExpression = expression.str();
}

void CUnit::consolidateDimensionless()
{
  // nothing to consolidate
  if (mComponents.empty()) return;

  std::set< CUnitComponent >::iterator it = mComponents.begin(),
                                       itEnd; //initialized later

  // logical default
  CUnitComponent tmpDimensionlessComponent = CUnitComponent(CBaseUnit::dimensionless);

  // If a dimensionless component already exists, it will be the first element
  // (set is ordered by Kind) and we should copy that one to the temporary one.
  if ((*it).getKind() == CBaseUnit::dimensionless)
    {
      tmpDimensionlessComponent = *it;
      mComponents.erase(it); // can't modify in-place, so may as well erase now
    }

  it = mComponents.begin(); // in case the previous *it was erased
  itEnd = mComponents.end();

  while (it != itEnd)
    {
      if ((*it).getExponent() == 0)
        {
          tmpDimensionlessComponent.setScale(tmpDimensionlessComponent.getScale() + (*it).getScale());
          tmpDimensionlessComponent.setMultiplier(tmpDimensionlessComponent.getMultiplier() * (*it).getMultiplier());
          mComponents.erase(it++); // Increment after erasing current one. This should be safe (C++ Standard 23.1.2.8)
        }
      else
        ++it;
    }

  mComponents.insert(tmpDimensionlessComponent);
}

// friend
std::ostream &operator<<(std::ostream &os, const CUnit & o)
{
  os << "Expression: " << o.mExpression << ", ";
  os << "Components: " << std::endl;

  std::set< CUnitComponent >::const_iterator it = o.mComponents.begin();
  std::set< CUnitComponent >::const_iterator end = o.mComponents.end();

  for (; it != end; ++it)
    {
      os << *it;
    }

  return os;
}
