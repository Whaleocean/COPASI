// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * UndoEventAssignmentData.h
 *
 *  Created on: 20 Nov 2014
 *      Author: dada
 */

#ifndef UNDOEVENTASSIGNMENTDATA_H_
#define UNDOEVENTASSIGNMENTDATA_H_

#include "UndoData.h"

class CModel;
class CEvent;
class CModelEntity;

class UndoEventAssignmentData: public UndoData
{
public:
  UndoEventAssignmentData(const std::string &key = "",
                          const std::string &name = "",
                          const std::string &type = "");

  UndoEventAssignmentData(const CModelEntity* pEntity,
                          const std::string& expression);

  virtual ~UndoEventAssignmentData();

  const std::string& getExpression() const;

  void setExpression(const std::string &expression);

  /**
   * Adds the event assignment to the given event
   * @param pEvent the event to add the assignment to
   */
  void addToEvent(CEvent* pEvent) const;

private:
  /**
  * Event assignment expression string.
  */
  std::string mExpression;
};

#endif /* UNDOEVENTASSIGNMENTDATA_H_ */
