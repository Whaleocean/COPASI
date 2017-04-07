// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CObjectInterface
#define COPASI_CObjectInterface

#include <iostream>
#include <vector>
#include <set>

#include "copasi/math/CMathEnum.h"

class CMathUpdateSequence;
class CCopasiContainer;
class CCopasiObjectName;
class CValidity;

//********************************************************************************

class CObjectInterface
{
public:
  typedef std::set< const CObjectInterface * > ObjectSet;
  typedef CMathUpdateSequence UpdateSequence;
  typedef std::vector< const CCopasiContainer * > ContainerList;

  static const CCopasiObject * DataObject(const CObjectInterface * pInterface);

  static CObjectInterface * GetObjectFromCN(const ContainerList & listOfContainer,
      const CCopasiObjectName & objName);

  /**
   * Constructor
   */
  CObjectInterface();

  /**
   * Copy Constructor
   */
  CObjectInterface(const CObjectInterface & src);

  /**
   * Destructor
   */
  virtual ~CObjectInterface();

  /**
   * Calculate the objects value.
   */
  virtual void calculateValue() = 0;

  /**
   * Retrieve the CN of the object
   * @return CCopasiObjectName
   */
  virtual CCopasiObjectName getCN() const = 0;

  /**
   * Retrieve a descendant object by its CN.
   * @param const CCopasiObjectName & cn
   * @return const CObjectInterface * pObject
   */
  virtual const CObjectInterface * getObject(const CCopasiObjectName & cn) const = 0;

  /**
   * Retrieve the prerequisites, i.e., the objects which need to be evaluated
   * before this.
   * @return const CObjectInterface::ObjectSet & prerequisites
   */
  virtual const CObjectInterface::ObjectSet & getPrerequisites() const = 0;

  /**
   * Check whether a given object is a prerequisite for a context.
   * @param const CObjectInterface * pObject
   * @param const CMath::SimulationContextFlag & context
   * @param const CObjectInterface::ObjectSet & changedObjects
   * @return bool isPrerequisiteForContext
   */
  virtual bool isPrerequisiteForContext(const CObjectInterface * pObject,
                                        const CMath::SimulationContextFlag & context,
                                        const CObjectInterface::ObjectSet & changedObjects) const = 0;

  /**
   * This is the output method for any object. The default implementation
   * provided with CCopasiObject uses the ostream operator<< of the object
   * to print the object.To override this default behavior one needs to
   * reimplement the virtual print function.
   * @param std::ostream * ostream
   */
  virtual void print(std::ostream * ostream) const = 0;

  /**
   * Retrieve a pointer to the value of the object
   */
  virtual void * getValuePointer() const = 0;

  /**
   * Retrieve a pointer to the data object
   * @return const CCopasiObject * dataObject
   */
  virtual const CCopasiObject * getDataObject() const = 0;

  /**
   * Retrieve the display name of the object
   * @param bool regular (default: true)
   * @param bool richtext (default: false)
   * @return std::string objectDisplayName
   */
  virtual std::string getObjectDisplayName() const = 0;

  /**
   * Get the aggregation of any issues associated with this object
   * @return CValidity & validity
   */
  virtual CValidity & getValidity() = 0;

  /**
   * Get the aggregation of any issues associated with this object
   * @return const CValidity & validity
   */
  virtual const CValidity & getValidity() const = 0;
};

#endif // COPASI_CObjectInterface
