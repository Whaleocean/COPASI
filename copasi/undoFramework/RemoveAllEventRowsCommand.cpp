// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * RemoveAllEventRowsCommand.cpp
 *
 *  Created on: 14 Oct 2014
 *      Author: dada
 */

#include "report/CCopasiRootContainer.h"
#include "model/CEvent.h"
#include "model/CModel.h"
#include "UI/CQEventDM.h"

#include "UndoEventData.h"
#include "UndoEventAssignmentData.h"
#include "RemoveAllEventRowsCommand.h"

RemoveAllEventRowsCommand::RemoveAllEventRowsCommand(
  CQEventDM * pEventDM, const QModelIndex&)
  : CCopasiUndoCommand("Event", EVENT_REMOVE_ALL, "Remove All")
  , mpEventDM(pEventDM)
  , mpEventData()
{
  GET_MODEL_OR_RETURN(pModel);

  for (int i = 0; i != pEventDM->rowCount() - 1; ++i)
    {
      UndoEventData *data = new UndoEventData();

      if (pModel->getEvents()[i])
        {
          data->setName(pModel->getEvents()[i]->getObjectName());
          data->setPriorityExpression(pModel->getEvents()[i]->getPriorityExpression());
          data->setDelayExpression(pModel->getEvents()[i]->getDelayExpression());
          data->setTriggerExpression(pModel->getEvents()[i]->getTriggerExpression());

          CCopasiVector< CEventAssignment >::const_iterator it = pModel->getEvents()[i]->getAssignments().begin();
          CCopasiVector< CEventAssignment >::const_iterator end = pModel->getEvents()[i]->getAssignments().end();

          for (; it != end; ++it)
            {
              const CModelEntity * pEntity = dynamic_cast< CModelEntity * >(CCopasiRootContainer::getKeyFactory()->get((*it)->getTargetKey()));
              data->getEventAssignmentData()->append(
                new UndoEventAssignmentData(pEntity, (*it)->getExpression()));
            }

          mpEventData.append(data);
        }
    }

  setText(removeAllEventRowsText());
}

void RemoveAllEventRowsCommand::redo()
{
  mpEventDM->removeAllEventRows();
  setUndoState(true);
  setAction("Delete all");
}

void RemoveAllEventRowsCommand::undo()
{
  mpEventDM->insertEventRows(mpEventData);
  setUndoState(false);
  setAction("Undelete all");
}

QString RemoveAllEventRowsCommand::removeAllEventRowsText() const
{
  return QObject::tr(": Removed All Events");
}

RemoveAllEventRowsCommand::~RemoveAllEventRowsCommand()
{
  // freeing the memory allocated above
  foreach(UndoEventData * data, mpEventData)
  {
    pdelete(data);
  }
  mpEventData.clear();
}