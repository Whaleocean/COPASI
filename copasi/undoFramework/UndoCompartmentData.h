// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * UndoCompartmentData.h
 *
 *  Created on: 15 Sep 2014
 *      Author: dada
 */

#ifndef UNDOCOMPARTMENTDATA_H_
#define UNDOCOMPARTMENTDATA_H_

#include "model/CCompartment.h"
#include "UndoData.h"

#include <QList>

class UndoReactionData;
class UndoSpeciesData;
class UndoGlobalQuantityData;
class UndoEventData;

class UndoCompartmentData : public UndoData
{
public:
  UndoCompartmentData();

  UndoCompartmentData(CCompartment* compartment);

  virtual ~UndoCompartmentData();

  QList<UndoData*> *getDependencyObjects() const;
  void setDependencyObjects(QList<UndoData*> *dependencyObjects);

  CModelEntity::Status getStatus() const;
  void setStatus(CModelEntity::Status status);

  double getInitialValue() const;
  void setInitialValue(double initialValue);

  QList<UndoReactionData*> *getReactionDependencyObjects() const;
  void setReactionDependencyObjects(
    QList<UndoReactionData*> *reactionDependencyObjects);

  QList<UndoSpeciesData*> *getSpecieDependencyObjects() const;
  void setSpecieDependencyObjects(
    QList<UndoSpeciesData*> *specieDependencyObjects);

  QList<UndoGlobalQuantityData*> *getGlobalQuantityDependencyObjects() const;
  void setGlobalQuantityDependencyObjects(QList<UndoGlobalQuantityData*> *globalQuantityDependencyObjects);

  QList<UndoEventData*> *getEventDependencyObjects() const;
  void setEventDependencyObjects(QList<UndoEventData*> *eventDependencyObjects);

  const std::string& getInitialExpression() const;
  void setInitialExpression(const std::string &initialExpression);

  const std::string& getExpression() const;
  void setExpression(const std::string &expression);

private:

  /**
   *  Initial volume of the compartment as double
   */
  double mInitialValue;

  /**
   * initial expression of the compartment
   */
  std::string mInitialExpression;

  /**
   * expression of the compartment
   */
  std::string mExpression;

  /**
   * The status of the metabolite
   */
  CModelEntity::Status mStatus;

  /**
   * Pointer to species dependency objects
   */
  QList<UndoData*> *mDependencyObjects;

  /**
   * Pointer to species dependency objects
   */
  QList<UndoSpeciesData*> *mSpecieDependencyObjects;

  /**
   * Pointer to reaction dependency objects
   */
  QList<UndoReactionData*> *mReactionDependencyObjects;

  /**
   * Pointer to global quantity dependency objects
   */
  QList<UndoGlobalQuantityData*> *mGlobalQuantityDependencyObjects;

  /**
   * Pointer to event dependency objects
   */
  QList<UndoEventData*> *mEventDependencyObjects;
};

#endif /* UNDOCOMPARTMENTDATA_H_ */