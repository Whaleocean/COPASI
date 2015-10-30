// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * EventDataChangeCommand.h
 *
 *  Created on: 14 Oct 2014
 *      Author: dada
 */

#ifndef EVENTDATACHANGECOMMAND_H_
#define EVENTDATACHANGECOMMAND_H_

#include "CCopasiUndoCommand.h"

class EventDataChangeCommand: public CCopasiUndoCommand
{
public:
  EventDataChangeCommand(QModelIndex index, const QVariant value, int role, CQEventDM *pEventDM);
  virtual ~EventDataChangeCommand();

  void redo();
  void undo();

private:
  QVariant mNew, mOld;
  QModelIndex mIndex;
  CQEventDM *mpEventDM;
  int mRole;
  Path mPathIndex;
};

#endif /* EVENTDATACHANGECOMMAND_H_ */
