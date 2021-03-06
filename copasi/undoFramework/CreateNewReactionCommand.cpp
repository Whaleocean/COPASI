// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CreateNewReactionCommand.cpp
 *
 *  Created on: 23 Jul 2014
 *      Author: dada
 */

#include "copasi.h"

#include "copasi/core/CRootContainer.h"
#include "model/CReaction.h"
#include "model/CReactionInterface.h"
#include "model/CModel.h"
#include "UI/ReactionsWidget1.h"

#include "CreateNewReactionCommand.h"
#include "UndoReactionData.h"

CreateNewReactionCommand::CreateNewReactionCommand(ReactionsWidget1 *pReactionWidget)
  : CCopasiUndoCommand("Reaction", REACTION_CREATE)
  , mpReactionWidget(pReactionWidget)
  , mpReactionData(NULL)
{
  this->setText(QObject::tr(": Created new reaction "));
}

void CreateNewReactionCommand::redo()
{
  if (mpReactionData == NULL)
    {
      // TODO: should only happen once
      mpReactionWidget->createNewReaction();
      CReaction *pReaction = dynamic_cast<CReaction *>(mpReactionWidget->mpObject);
      std::string sName = pReaction->getObjectName();
      mpReactionData = new UndoReactionData(pReaction);
      setName(sName);
    }
  else
    {
      mpReactionWidget->addReaction(mpReactionData);
    }

  setUndoState(true);
  setAction("Create");
}

void CreateNewReactionCommand::undo()
{
  mpReactionWidget->deleteReaction(mpReactionData);
  setUndoState(false);
  setAction("Delete");
}

CreateNewReactionCommand::~CreateNewReactionCommand()
{
  pdelete(mpReactionData);
}
