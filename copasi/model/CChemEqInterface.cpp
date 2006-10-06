/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CChemEqInterface.cpp,v $
   $Revision: 1.34 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/10/06 16:03:44 $
   End CVS Header */

// Copyright � 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "mathematics.h"

#include "copasi.h"
#include "CChemEqInterface.h"
#include "CMetabNameInterface.h"
#include "CChemEq.h"
#include "CChemEqParser.h"
#include "CReaction.h"
#include "CModel.h"

#include "utilities/CCopasiVector.h"
#include "utilities/utility.h"

CChemEqInterface::CChemEqInterface():
    mpModel(NULL)
{}

CChemEqInterface::CChemEqInterface(CModel * pModel):
    mpModel(pModel)
{}

CChemEqInterface::~CChemEqInterface()
{}

std::string CChemEqInterface::getChemEqString(bool expanded) const
  {
    std::string ChemicalEquation;
    unsigned C_INT32 j;

    if ((mSubstrateNames.size() == 0) && (mProductNames.size() == 0) && (mModifierNames.size() == 0))
      return "";

    for (j = 0; j < mSubstrateNames.size(); j++)
      {
        if (j)
          ChemicalEquation += " + ";

        ChemicalEquation += writeElement(mSubstrateDisplayNames[j], mSubstrateMult[j], expanded);
      }

    if (mReversibility)
      ChemicalEquation += " = ";
    else
      ChemicalEquation += " -> ";

    for (j = 0; j < mProductNames.size(); j++)
      {
        if (j)
          ChemicalEquation += " + ";

        ChemicalEquation += writeElement(mProductDisplayNames[j], mProductMult[j], expanded);
      }

    if (mModifierNames.size())
      {
        ChemicalEquation += "; ";

        for (j = 0; j < mModifierNames.size(); j++)
          {
            ChemicalEquation += " ";

            ChemicalEquation += mModifierDisplayNames[j];
          }
      }

    return ChemicalEquation;
  }

bool CChemEqInterface::setChemEqString(const std::string & ces)
{
  // parse the description into a linked node tree
  std::istringstream buffer(ces);
  CChemEqParser Parser(&buffer);

  bool success = (Parser.yyparse() == 0);

  if (success)
    {
      mReversibility = Parser.isReversible();

      mSubstrateNames = Parser.getSubstrateNames();
      mSubstrateMult = Parser.getSubstrateMulitplicities();
      mSubstrateCompartments = Parser.getSubstrateCompartments();

      mProductNames = Parser.getProductNames();
      mProductMult = Parser.getProductMulitplicities();
      mProductCompartments = Parser.getProductCompartments();

      mModifierNames = Parser.getModifierNames();
      mModifierMult = Parser.getModifierMulitplicities();
      mModifierCompartments = Parser.getModifierCompartments();
    }

  completeCompartments();

  buildDisplayNames();

  return success;
}

void CChemEqInterface::completeCompartments()
{
  std::string DefaultCompartment;
  if (mpModel->getCompartments().size() == 0)
    DefaultCompartment = "compartment";
  else
    DefaultCompartment = mpModel->getCompartments()[0]->getObjectName();

  std::vector< std::string >::iterator it, end;

  for (it = mSubstrateCompartments.begin(), end = mSubstrateCompartments.end(); it != end; ++it)
    if (*it == "")
      *it = DefaultCompartment;

  for (it = mProductCompartments.begin(), end = mProductCompartments.end(); it != end; ++it)
    if (*it == "")
      *it = DefaultCompartment;

  for (it = mModifierCompartments.begin(), end = mModifierCompartments.end(); it != end; ++it)
    if (*it == "")
      *it = DefaultCompartment;
}

bool CChemEqInterface::loadFromChemEq(const CChemEq & ce)
{
  bool ret = true;
  const CCopasiVector<CChemEqElement> * elements;
  C_INT32 i, imax;

  elements = &ce.getSubstrates();
  imax = elements->size();
  mSubstrateNames.resize(imax);
  mSubstrateMult.resize(imax);
  mSubstrateCompartments.resize(imax);
  for (i = 0; i < imax; ++i)
    {
      mSubstrateNames[i] = (*elements)[i]->getMetabolite()->getObjectName();
      mSubstrateMult[i] = (*elements)[i]->getMultiplicity();
      mSubstrateCompartments[i] = (*elements)[i]->getMetabolite()->getCompartment()->getObjectName();
    }

  elements = &ce.getProducts();
  imax = elements->size();
  mProductNames.resize(imax);
  mProductMult.resize(imax);
  mProductCompartments.resize(imax);
  for (i = 0; i < imax; ++i)
    {
      mProductNames[i] = (*elements)[i]->getMetabolite()->getObjectName();
      mProductMult[i] = (*elements)[i]->getMultiplicity();
      mProductCompartments[i] = (*elements)[i]->getMetabolite()->getCompartment()->getObjectName();
    }

  elements = &ce.getModifiers();
  imax = elements->size();
  mModifierNames.resize(imax);
  mModifierMult.resize(imax);
  mModifierCompartments.resize(imax);
  for (i = 0; i < imax; ++i)
    {
      mModifierNames[i] = (*elements)[i]->getMetabolite()->getObjectName();
      mModifierMult[i] = (*elements)[i]->getMultiplicity();
      mModifierCompartments[i] = (*elements)[i]->getMetabolite()->getCompartment()->getObjectName();
    }

  mReversibility = ce.getReversibility();

  buildDisplayNames();

  return ret;
}

void CChemEqInterface::buildDisplayNames()
{
  std::vector< std::string >::const_iterator itName, itCompartment;
  std::vector< std::string >::iterator it, end;

  // We need to build the list of display names for the substrates;
  mSubstrateDisplayNames.resize(mSubstrateNames.size());
  for (itName = mSubstrateNames.begin(),
       itCompartment = mSubstrateCompartments.begin(),
       it = mSubstrateDisplayNames.begin(),
       end = mSubstrateDisplayNames.end();
       it != end;
       ++itName, ++itCompartment, ++it)
    *it = CMetabNameInterface::getDisplayName(mpModel, *itName, *itCompartment);

  // We need to build the list of display names for the products;
  mProductDisplayNames.resize(mProductNames.size());
  for (itName = mProductNames.begin(),
       itCompartment = mProductCompartments.begin(),
       it = mProductDisplayNames.begin(),
       end = mProductDisplayNames.end();
       it != end;
       ++itName, ++itCompartment, ++it)
    *it = CMetabNameInterface::getDisplayName(mpModel, *itName, *itCompartment);

  // We need to build the list of display names for the modifiers;
  mModifierDisplayNames.resize(mModifierNames.size());
  for (itName = mModifierNames.begin(),
       itCompartment = mModifierCompartments.begin(),
       it = mModifierDisplayNames.begin(),
       end = mModifierDisplayNames.end();
       it != end;
       ++itName, ++itCompartment, ++it)
    *it = CMetabNameInterface::getDisplayName(mpModel, *itName, *itCompartment);

  return;
}

bool CChemEqInterface::writeToChemEq(CChemEq & ce) const
  {
    bool ret = true;
    std::string metabkey;
    C_INT32 i, imax;

    ce.cleanup();

    imax = mSubstrateNames.size();
    for (i = 0; i < imax; ++i)
      {
        metabkey = CMetabNameInterface::getMetaboliteKey(mpModel, mSubstrateNames[i], mSubstrateCompartments[i]);
        if (metabkey.empty())
          ret = false;
        else
          ce.addMetabolite(metabkey, mSubstrateMult[i], CChemEq::SUBSTRATE);
      }

    imax = mProductNames.size();
    for (i = 0; i < imax; ++i)
      {
        metabkey = CMetabNameInterface::getMetaboliteKey(mpModel, mProductNames[i], mProductCompartments[i]);
        if (metabkey.empty())
          ret = false;
        else
          ce.addMetabolite(metabkey, mProductMult[i], CChemEq::PRODUCT);
      }

    imax = mModifierNames.size();
    for (i = 0; i < imax; ++i)
      {
        metabkey = CMetabNameInterface::getMetaboliteKey(mpModel, mModifierNames[i], mModifierCompartments[i]);
        if (metabkey.empty())
          ret = false;
        else
          ce.addMetabolite(metabkey, mModifierMult[i], CChemEq::MODIFIER);
      }

    ce.setReversibility(mReversibility);

    return ret; //TODO: really check
  }

const std::vector<C_FLOAT64> & CChemEqInterface::getListOfMultiplicities(CFunctionParameter::Role role) const
  {
    if (role == CFunctionParameter::SUBSTRATE) return mSubstrateMult;
    else if (role == CFunctionParameter::PRODUCT) return mProductMult;
    else if (role == CFunctionParameter::MODIFIER) return mModifierMult;
    else fatalError();

    return mSubstrateMult; //never reached
  }

const std::vector<std::string> & CChemEqInterface::getListOfDisplayNames(CFunctionParameter::Role role) const
  {
    if (role == CFunctionParameter::SUBSTRATE) return mSubstrateDisplayNames;
    else if (role == CFunctionParameter::PRODUCT) return mProductDisplayNames;
    else if (role == CFunctionParameter::MODIFIER) return mModifierDisplayNames;
    else fatalError();

    return mSubstrateDisplayNames; //never reached
  }

void CChemEqInterface::addModifier(const std::string & name)
{
  std::pair< std::string, std::string > Modifier =
    CMetabNameInterface::splitDisplayName(name);

  //is the name already in the list
  std::vector< std::string >::const_iterator it, itEnd = mModifierNames.end();
  std::vector< std::string >::const_iterator itComp = mModifierCompartments.end();
  for (it = mModifierNames.begin(); it != itEnd; ++it, ++itComp)
    if (Modifier.first == *it &&
        Modifier.second == *itComp) break;

  if (it == itEnd)
    {
      mModifierNames.push_back(Modifier.first);
      mModifierMult.push_back(1.0);
      mModifierCompartments.push_back(Modifier.second);
      mModifierDisplayNames.push_back(name);
    }
}

void CChemEqInterface::clearModifiers()
{
  mModifierNames.clear();
  mModifierMult.clear();
  mModifierCompartments.clear();
  mModifierDisplayNames.clear();
}

std::string CChemEqInterface::writeElement(const std::string & name, C_FLOAT64 mult, bool expanded)
{
  std::string Metabolite = name;

  // The last character must not be a ';' in a reaction.
  if (Metabolite[Metabolite.length() - 1] == ';')
    Metabolite = "\"" + Metabolite + "\"";

  if (isNumber(Metabolite))
    Metabolite = "\"" + Metabolite + "\"";

  if (expanded)
    {
      std::string ces;
      C_INT32 i, imax = (C_INT32) mult;
      for (i = 0; i < imax; ++i)
        {
          if (i) ces += " + ";
          ces += Metabolite;
        }
      return ces;
    }
  else
    {
      if (mult == 1.0)
        return Metabolite;
      else
        return StringPrint("%g * %s", mult, Metabolite.c_str());
    }
}

unsigned C_INT32 CChemEqInterface::getMolecularity(CFunctionParameter::Role role) const
  {
    const std::vector<C_FLOAT64> * tmpVector = NULL;

    if (role == CFunctionParameter::SUBSTRATE)
      tmpVector = &mSubstrateMult;
    else if (role == CFunctionParameter::PRODUCT)
      tmpVector = &mProductMult;
    else if (role == CFunctionParameter::MODIFIER)
      tmpVector = &mModifierMult;
    else fatalError();

    C_INT32 ccc, i, imax = tmpVector->size();
    ccc = 0;
    for (i = 0; i < imax; ++i)
      {
        if ((*tmpVector)[i] != (C_FLOAT64) (C_INT32) (*tmpVector)[i])
          return C_INVALID_INDEX;

        ccc += (C_INT32)floor((*tmpVector)[i]);
      }

    return ccc;
  }

void CChemEqInterface::reverse()
{
  std::vector<std::string> dummyNames;
  std::vector<C_FLOAT64> dummyMults;

  dummyNames = mSubstrateNames; dummyMults = mSubstrateMult;
  mSubstrateNames = mProductNames; mSubstrateMult = mProductMult;
  mProductNames = dummyNames; mProductMult = dummyMults;
}

std::set<std::string> CChemEqInterface::listOfNonUniqueMetabNames() const
  {
    std::set<std::string> ret;

    std::vector<std::string>::const_iterator it, itEnd;

    itEnd = mSubstrateNames.end();
    for (it = mSubstrateNames.begin(); it != itEnd; ++it)
      if (!CMetabNameInterface::isUnique(mpModel, *it))
        ret.insert(*it);

    itEnd = mProductNames.end();
    for (it = mProductNames.begin(); it != itEnd; ++it)
      if (!CMetabNameInterface::isUnique(mpModel, *it))
        ret.insert(*it);

    itEnd = mModifierNames.end();
    for (it = mModifierNames.begin(); it != itEnd; ++it)
      if (!CMetabNameInterface::isUnique(mpModel, *it))
        ret.insert(*it);

    return ret;
  }

std::set< std::pair< std::string, std::string > > CChemEqInterface::listOfNonExistingMetabNames() const
  {
    std::set< std::pair< std::string, std::string > > ret;
    std::pair< std::string, std::string > Insert;

    std::vector<std::string>::const_iterator it, itComp, itEnd;

    itEnd = mSubstrateNames.end();
    for (it = mSubstrateNames.begin(), itComp = mSubstrateCompartments.begin(); it != itEnd; ++it, ++itComp)
      if (!CMetabNameInterface::doesExist(mpModel, *it, *itComp))
        {
          Insert.first = *it;
          Insert.second = *itComp;
          ret.insert(Insert);
        }

    itEnd = mProductNames.end();
    for (it = mProductNames.begin(), itComp = mProductCompartments.begin(); it != itEnd; ++it, ++itComp)
      if (!CMetabNameInterface::doesExist(mpModel, *it, *itComp))
        {
          Insert.first = *it;
          Insert.second = *itComp;
          ret.insert(Insert);
        }

    itEnd = mModifierNames.end();
    for (it = mModifierNames.begin(), itComp = mModifierCompartments.begin(); it != itEnd; ++it, ++itComp)
      if (!CMetabNameInterface::doesExist(mpModel, *it, *itComp))
        {
          Insert.first = *it;
          Insert.second = *itComp;
          ret.insert(Insert);
        }

    return ret;
  }

bool CChemEqInterface::createNonExistingMetabs() const
  {
    std::set< std::pair< std::string, std::string > > metabs = listOfNonExistingMetabNames();
    bool ret;
    if (metabs.size() == 0) ret = false; else ret = true;

    std::set< std::pair< std::string, std::string > >::const_iterator it, itEnd;

    itEnd = metabs.end();

    for (it = metabs.begin(); it != itEnd; ++it)
      {
        if (mpModel->getCompartments().getIndex(it->second) == C_INVALID_INDEX)
          mpModel->createCompartment(it->second, 1);

        mpModel->createMetabolite(it->first,
                                  it->second,
                                  0.1, CModelEntity::REACTIONS);
      }

    return ret;
  }

bool CChemEqInterface::isMulticompartment() const
  {
    CChemEq ce;
    writeToChemEq(ce);
    return (ce.getCompartmentNumber() > 1);
  }

const CCompartment * CChemEqInterface::getCompartment() const
  {
    CChemEq ce;
    writeToChemEq(ce);
    if (ce.getCompartmentNumber() > 1)
      return NULL;
    else
      {
        const CMetab * metab = NULL;
        if (ce.getSubstrates().size())
          metab = ce.getSubstrates()[0]->getMetabolite();
        else if (ce.getProducts().size())
          metab = ce.getProducts()[0]->getMetabolite();

        if (metab)
          return metab->getCompartment();
        else
          return NULL;
      }
  }

/*static*/
std::string CChemEqInterface::getChemEqString(CModel * model, const CReaction & rea, bool expanded)
{
  CChemEqInterface cei(model);
  cei.loadFromChemEq(rea.getChemEq());
  return cei.getChemEqString(expanded);
}

/*static*/
void CChemEqInterface::setChemEqFromString(CModel * model, CReaction & rea, const std::string & ces)
{
  CChemEqInterface cei(model);
  cei.setChemEqString(ces);
  cei.writeToChemEq(rea.getChemEq());
}

/*static*/
bool CChemEqInterface::isValidEq(const std::string & eq)
{
  // parse the description into a linked node tree
  std::istringstream buffer(eq);
  CChemEqParser Parser(&buffer);

  return (Parser.yyparse() == 0);
}
