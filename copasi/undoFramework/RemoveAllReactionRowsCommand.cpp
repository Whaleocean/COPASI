// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * RemoveAllReactionRowsCommand.cpp
 *
 *  Created on: 12 Aug 2014
 *      Author: dada
 */

#include <QtCore/QList>

#include "copasi.h"

#include "report/CCopasiRootContainer.h"
#include "model/CReaction.h"
#include "model/CReactionInterface.h"
#include "model/CModel.h"
#include "CQReactionDM.h"

#include "RemoveAllReactionRowsCommand.h"
#include "UndoReactionData.h"

RemoveAllReactionRowsCommand::RemoveAllReactionRowsCommand(
  CQReactionDM * pReaDM, const QModelIndex&)
  : CCopasiUndoCommand("Reaction", REACTION_REMOVE_ALL)
  , mpReactionDM(pReaDM)
  , mpReaData()
{

  CCopasiDataModel * pDataModel = pReaDM->getDataModel();
  assert(pDataModel != NULL);
  CModel * pModel = pDataModel->getModel();
  assert(pModel != NULL);

  for (int i = 0; i != pReaDM->rowCount() - 1; ++i)
    {
      if (&pModel->getReactions()[i] == NULL)
        continue;

      UndoReactionData *data = new UndoReactionData(&pModel->getReactions()[i]);
      mpReaData.append(data);
    }

  setText(QObject::tr(": Removed All Reaction Rows"));
}

void RemoveAllReactionRowsCommand::redo()
{
  mpReactionDM->removeAllReactionRows();
  setUndoState(true);
  setAction("Delete all");
}

void RemoveAllReactionRowsCommand::undo()
{
  mpReactionDM->insertReactionRows(mpReaData);
  setUndoState(false);
  setAction("Undelete all");
}

RemoveAllReactionRowsCommand::~RemoveAllReactionRowsCommand()
{
  // freeing the memory allocated above
  foreach(UndoReactionData * data, mpReaData)
  {
    pdelete(data);
  }

  mpReaData.clear();
}
