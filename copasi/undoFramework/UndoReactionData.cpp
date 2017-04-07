// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * UndoReactionData.cpp
 *
 *  Created on: 15 Aug 2014
 *      Author: dada
 */

#include <QtCore/QList>

#include "copasi.h"

#include <copasi/model/CModel.h>
#include <copasi/model/CMetab.h>
#include <copasi/model/CReaction.h>
#include <copasi/model/CReactionInterface.h>
#include <copasi/model/CChemEqInterface.h>

#include <copasi/undoFramework/CCopasiUndoCommand.h>
#include <copasi/undoFramework/UndoSpeciesData.h>
#include <copasi/undoFramework/UndoReactionData.h>
#include <copasi/undoFramework/UndoDependentData.h>

#include <copasi/report/CCopasiRootContainer.h>

UndoReactionData::UndoReactionData(const std::string &key  /*= ""*/,
                                   const std::string &name /*= ""*/,
                                   const std::string &type /*= ""*/)
  : UndoData(key, name, type)
  , mpRi(NULL)
{
}

UndoReactionData::UndoReactionData(const CReaction *pReaction
                                   , bool trackDependencies /*= true*/)
  : UndoData(pReaction->getKey(), pReaction->getObjectName())
  , mpRi(NULL)
{
  CCopasiDataModel * pDataModel = pReaction->getObjectDataModel();
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();
  assert(pModel != NULL);

  mpRi = new CReactionInterface(pModel);
  mpRi->initFromReaction(pReaction->getKey());

  if (trackDependencies)
    mpData->initializeFrom(pReaction);
}

UndoReactionData::~UndoReactionData()
{
}

CCopasiObject *
UndoReactionData::createObjectIn(CModel *pModel)
{
  if (pModel == NULL) return NULL;

  createDependentObjects(pModel);

  CReaction* pRea = pModel->createReaction(getName());

  if (pRea == NULL) return NULL;

  mKey = pRea->getKey();

  return pRea;
}

CCopasiObject *
UndoReactionData::restoreObjectIn(CModel *pModel)
{
  CCopasiObject* pRea = createObjectIn(pModel);

  if (pRea == NULL) return NULL;

  fillObject(pModel);
  fillDependentObjects(pModel);

  return pRea;
}

void
UndoReactionData::fillObject(CModel *pModel)
{
  CReaction * pRea =
    dynamic_cast<CReaction*>(CCopasiRootContainer::getKeyFactory()->get(mKey));

  if (pRea == NULL) return;

  CChemEqInterface *chem = new CChemEqInterface(pModel);
  chem->setChemEqString(mpRi->getChemEqString());
  chem->writeToChemEq(pRea->getChemEq());
  mAdditionalKeys.clear();
  mpRi->createMetabolites(mAdditionalKeys);
  mpRi->createOtherObjects(mAdditionalKeys);
  mpRi->writeBackToReaction(pRea);
}

CReactionInterface *UndoReactionData::getRi() const
{
  return mpRi;
}

void UndoReactionData::setRi(CReactionInterface *pRi)
{
  mpRi = pRi;
}

const std::vector<std::string>& UndoReactionData::getAdditionalKeys() const
{
  return mAdditionalKeys;
}

void
UndoReactionData::setAdditionalKeys(const std::vector<std::string> &additionalKeys)
{
  mAdditionalKeys = additionalKeys;
}
