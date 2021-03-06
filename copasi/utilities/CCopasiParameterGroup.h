// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CCopasiParameterGroup
#define COPASI_CCopasiParameterGroup

#include <string>
#include <vector>

#include "copasi/utilities/CCopasiParameter.h"
#include "copasi/utilities/CCopasiMessage.h"

/**
 *  CCopasiParameterGroup class.
 *  This class is used to describe parameters. This class is intended
 *  to be used with integration or optimization methods or reactions.
 *
 *  Created for COPASI by Stefan Hoops 2002
 */
class CCopasiParameterGroup: public CCopasiParameter
{

public:
  typedef std::vector< CCopasiParameter * > elements;
  typedef elements::iterator index_iterator;

  class name_iterator
  {
  public:
    name_iterator();

    name_iterator(const CCopasiParameterGroup & group,
                  const bool & begin);

    name_iterator(const name_iterator & src);

    ~name_iterator();

    CDataObject * operator*() const;

    CDataObject * operator->() const;

    name_iterator & operator++();

    name_iterator operator++(int);

    bool operator != (const name_iterator & rhs) const;

  private:
    const CCopasiParameterGroup * mpGroup;
    bool mNameEnd;
    std::map< std::string, std::set< CDataObject * > >::iterator mName;
    bool mObjectEnd;
    std::set< CDataObject * >::iterator mObject;
    bool mParameterEnd;
    std::vector< CCopasiParameter * >::iterator mParameter;
  };

  // Operations
protected:
  /**
   * Default constructor
   */
  CCopasiParameterGroup();

  CCopasiParameterGroup(const CCopasiParameterGroup & src);

public:
  /**
   * Copy constructor
   * @param "const CCopasiParameterGroup &" src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CCopasiParameterGroup(const CCopasiParameterGroup & src,
                        const CDataContainer * pParent);

  /**
   * Specific constructor
   * @param const string & name
   * @param const CDataContainer * pParent (default: NULL)
   * @param const std::string & objectType (default: "ParameterGroup")
   */
  CCopasiParameterGroup(const std::string & name,
                        const CDataContainer * pParent = NO_PARENT,
                        const std::string & objectType = "ParameterGroup");

  /**
   * Destructor
   */
  virtual ~CCopasiParameterGroup();

  virtual CData toData() const;
  virtual bool applyData(const CData & data);

  virtual const CObjectInterface * getObject(const CCommonName & cn) const;

  /**
   * This methods must be called to elevate subgroups to
   * derived objects. The default implementation does nothing.
   * @return bool success
   */
  virtual bool elevateChildren();

  /**
   * Assignment operator
   * @param const CCopasiParameterGroup & rhs
   * @return CCopasiParameterGroup & lhs
   */
  CCopasiParameterGroup & operator = (const CCopasiParameterGroup & rhs);

  /**
   * Retrieve the begin of unsorted iterator
   * Note: the swap function may be used to change the order
   * @return name_iterator begin
   */
  index_iterator beginIndex() const;

  /**
   * Retrieve the end of unsorted iterator
   * Note: the swap function may be used to change the order
   * @return name_iterator end
   */
  index_iterator endIndex() const;

  /**
   * Add a parameter
   * @param const CCopasiParameter & parameter
   * @return bool success
   */
  bool addParameter(const CCopasiParameter & parameter);

  /**
   * Add a parameter to the group
   * @param const std::string & name
   * @param const CCopasiParameter::Type type
   * @return bool success
   */
  bool addParameter(const std::string & name,
                    const CCopasiParameter::Type type);

  /**
   * Add a parameter to the group
   * @param const std::string & name
   * @param const CCopasiParameter::Type type
   * @param const CType & value
   * @return bool success
   */
  template < class CType >
  bool addParameter(const std::string & name,
                    const CCopasiParameter::Type type,
                    const CType & value)
  {
    CCopasiParameter * pParameter;

    if (type == GROUP)
      {
        // Create a temporary group with the correct name
        CCopasiParameterGroup *tmp = new CCopasiParameterGroup(name);

        if (!tmp->isValidValue(value))
          {
            delete tmp;
            return false;
          }

        void * pGroup = tmp->mpValue;
        tmp->mpValue = const_cast<CType *>(& value);

        // Create the final parameter
        pParameter = new CCopasiParameterGroup(*tmp, NO_PARENT);

        tmp->mpValue = pGroup;
        delete tmp;
      }
    else
      {
        pParameter = new CCopasiParameter(name, type);

        if (!pParameter->isValidValue(value))
          {
            delete pParameter;
            return false;
          }

        pParameter->setValue(value);
      }

    addParameter(pParameter);

    return true;
  }

  /**
   * Assert that a parameter with the given name and type is present.
   * If not the parameter is created with the default value.
   * @param const std::string & name
   * @param const CCopasiParameter::Type type
   * @param const CType & Value
   * @return CCopasiParameter * pParameter
   */
  template < class CType >
  CType * assertParameter(const std::string & name,
                          const CCopasiParameter::Type type,
                          const CType & defaultValue)
  {
    CCopasiParameter * pParm = getParameter(name);

    if (pParm && pParm->getType() == type) return &pParm->getValue< CType >();

    if (pParm) removeParameter(name);

    addParameter(name, type, defaultValue);

    return &getParameter(name)->getValue< CType >();
  }

  /**
   * Removes the pointer to the object, from the vector
   * @param CDataObject * pObject
   * @return bool success
   */
  virtual bool remove(CDataObject * pObject);

  /**
   * Add a subgroup to the group
   * @param const std::string & name
   * @return bool success
   */
  bool addGroup(const std::string & name);

  /**
   * Assert that a group with the given name is present.
   * If not the group is created as empty group.
   * @param const std::string & name
   * @return CCopasiParameterGroup * pGroup
   */
  CCopasiParameterGroup * assertGroup(const std::string & name);

  /**
   * Remove a parameter or subgroup from the group
   * @param const std::string & name
   * @return bool success
   */
  bool removeParameter(const std::string & name);

  /**
   * Remove a parameter or subgroup from the group
   * @param const size_t & index
   * @return bool success
   */
  bool removeParameter(const size_t & index);

  /**
   * Remove a parameter or subgroup from the group
   * @param const size_t & index
   * @return bool success
   */
  bool removeParameter(CCopasiParameter * pParameter);

  /**
   * Retrieve a parameter or subgroup from the group
   * @param const std::string & name
   * @return CCopasiParameter * parameter
   */
  CCopasiParameter * getParameter(std::string name);

  /**
   * Retrieve a parameter or subgroup from the group
   * @param const std::string & name
   * @return const CCopasiParameter * parameter
   */
  const CCopasiParameter * getParameter(std::string name) const;

  /**
   * Retrieve a parameter or subgroup from the group
   * @param const size_t & index
   * @return CCopasiParameter * parameter
   */
  CCopasiParameter * getParameter(const size_t & index);

  /**
   * Retrieve a parameter or subgroup from the group
   * @param const size_t & index
   * @return const CCopasiParameter * parameter
   */
  const CCopasiParameter * getParameter(const size_t & index) const;

  /**
   * Retrieve a subgroup from the group
   * @param const std::string & name
   * @return CCopasiParameterGroup * group
   */
  CCopasiParameterGroup * getGroup(const std::string & name);

  /**
   * Retrieve a subgroup from the group
   * @param const std::string & name
   * @return const CCopasiParameterGroup * group
   */
  const CCopasiParameterGroup * getGroup(const std::string & name) const;

  /**
   * Retrieve a subgroup from the group
   * @param const size_t & index
   * @return CCopasiParameterGroup * parameter
   */
  CCopasiParameterGroup * getGroup(const size_t & index);

  /**
   * Retrieve a subgroup from the group
   * @param const size_t & index
   * @return const CCopasiParameterGroup * parameter
   */
  const CCopasiParameterGroup * getGroup(const size_t & index) const;

  /**
   * Retrieve a pointer to the value of a parameter or subgroup
   * @param const std::string & name
   * @return const CType & Value
   */
  template <class CType> const CType & getValue(const std::string & name) const
  {
    const CCopasiParameter * pParameter = getParameter(name);

    if (!pParameter)
      __FatalError();

    return pParameter->getValue<CType>();
  }

  /**
   * Retrieve a pointer to the value of a parameter or subgroup
   * @param const std::string & name
   * @return CType & Value
   */
  template <class CType> CType & getValue(const std::string & name)
  {
    CCopasiParameter * pParameter = getParameter(name);

    if (!pParameter)
      __FatalError();

    return pParameter->getValue<CType>();
  }

  /**
   * Retrieve a pointer to the value of a parameter or subgroup
   * @param const size_t & index
   * @return const CType & Value
   */
  template <class CType> const CType & getValue(const size_t & index) const
  {
    const CCopasiParameter * pParameter = getParameter(index);

    if (!pParameter)
      __FatalError();

    return pParameter->getValue<CType>();
  }

  /**
   * Retrieve a pointer to the value of a parameter or subgroup
   * @param const size_t & index
   * @return CType & Value
   */
  template <class CType> CType & getValue(const size_t & index)
  {
    CCopasiParameter * pParameter = getParameter(index);

    if (!pParameter)
      __FatalError();

    return pParameter->getValue<CType>();
  }

  /**
   * Retrieve the type of a parameter or subgroup
   * @param const std::string & name
   * @return CCopasiParameter::Type
   */
  CCopasiParameter::Type getType(const std::string & name) const;

  /**
   * Retrieve the type of a parameter or subgroup
   * @param const size_t & index
   * @return CCopasiParameter::Type
   */
  CCopasiParameter::Type getType(const size_t & index) const;

  /**
   * Retrieve the key of a parameter or subgroup
   * @param const std::string & name
   * @return std::string key
   */
  std::string getKey(const std::string & name) const;

  /**
   * Retrieve the key of a parameter or subgroup
   * @param const size_t & index
   * @return std::string key
   */
  std::string getKey(const size_t & index) const;

  /**
   * Retrieve the name of a parameter or subgroup
   * @param const size_t & index
   * @return std::string name
   *
   */
  virtual const std::string & getName(const size_t & index) const;

  /**
   * Set the value of a parameter or subgroup.
   * @param const std::string & name
   * @param const CType & value
   * @return bool success
   */
  template <class CType>
  bool setValue(const std::string & name,
                const CType & value)
  {
    CCopasiParameter * pParameter =
      const_cast< CCopasiParameterGroup * >(this)->getParameter(name);

    if (pParameter) return pParameter->setValue(value);

    return false;
  }

  /**
   * Set the value of a parameter or subgroup.
   * @param const size_t & index
   * @param const CType & value
   * @return bool success
   */
  template <class CType>
  bool setValue(const size_t & index,
                const CType & value)
  {
    CCopasiParameter * pParameter =
      const_cast< CCopasiParameterGroup * >(this)->getParameter(index);

    if (pParameter) return pParameter->setValue(value);

    return false;
  }

  /**
   * Swap two parameters
   * Note: This has effect on the index_iterator and index access methods.
   * @param const size_t & iFrom
   * @param const size_t & iTo
   * @return bool success
   */
  bool swap(const size_t & iFrom,
            const size_t & iTo);

  /**
   * Swap two parameters
   * Note: This has effect on the iterator and index access methods.
   * @param index_iterator & from
   * @param index_iterator & to
   * @return bool success
   */
  bool swap(index_iterator & from,
            index_iterator & to);

  /**
   * The size of the parameter group
   * @ return size_t size
   */
  size_t size(const UserInterfaceFlag & flag = UserInterfaceFlag::All) const;

  /**
   * Clear all parameters and subgroups
   */
  void clear();

  virtual size_t getIndex(const CDataObject * pObject) const;

  virtual CDataObject * insert(const CData & data);

  /**
   * Retrieve the index of a parameter or subgroup with a given name
   * @param const std::string & name
   * @return size_t index
   */
  size_t getIndex(const std::string & name) const;

  /**
   * Retrieve a unique name for the given parameter
   * @param const CCopasiParameter * pParameter
   * @return std::string uniqueParameterName
   */
  std::string getUniqueParameterName(const CCopasiParameter * pParameter) const;

  /**
   * This is the output method for any object. The default implementation
   * provided with CDataObject uses the ostream operator<< of the object
   * to print the object.To override this default behavior one needs to
   * reimplement the virtual print function.
   * @param std::ostream * ostream
   */
  virtual void print(std::ostream * ostream) const;

  /**
   * Output stream operator
   * @param ostream & os
   * @param const CCopasiParameterGroup & o
   * @return ostream & os
   */
  friend std::ostream &operator<<(std::ostream &os, const CCopasiParameterGroup & o);

  /**
   * Comparison operator
   * @param const CCopasiParameterGroup & lhs
   * @param const CCopasiParameterGroup & rhs
   * @return bool equal
   */
  friend bool operator==(const CCopasiParameterGroup & lhs,
                         const CCopasiParameterGroup & rhs);

  /**
   * Add a parameter
   * @param CCopasiParameter * pParameter
   */
  void addParameter(CCopasiParameter * pParameter);

  CCopasiParameterGroup & getElementTemplates();
  const CCopasiParameterGroup & getElementTemplates() const;
  bool haveTemplate() const;

  virtual void setUserInterfaceFlag(const UserInterfaceFlag & flag);

private:
  CCopasiParameterGroup *mpElementTemplates;
};

// :TODO: This should be a member function but Visual C++ 6.0
// can not deal with specifying template parameters correctly.
/**
 * Elevate a CCopasiParameter pointer to ElevateTo. If pParm is NULL,
 * not of type ElevateFrom, or the elevation fails a NULL pointer is
 * returned. If the elevation is success full the parameter *pParm is
 * replaced with the elevated object.
 * @param CCopasiParameter * pParm
 * @return ElevateTo * pTo
 */
template <typename ElevateTo, typename ElevateFrom>
ElevateTo * elevate(CCopasiParameter * pParm)
{
  if (!pParm)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCParameter + 2);
      return NULL;
    }

  ElevateFrom * pFrom = dynamic_cast<ElevateFrom *>(pParm);

  if (!pFrom)
    {
      CCopasiMessage(CCopasiMessage::ERROR, MCParameter + 3);
      return NULL;
    }

  // Even if the pParm is already of the desired type we still
  // recreate it to assure that we have proper construction.
  ElevateTo * pTo = NULL;

  CCopasiParameterGroup * pGrp =
    dynamic_cast<CCopasiParameterGroup *>(pParm->getObjectParent());

  if (pGrp)
    {
      std::vector< CCopasiParameter * >::iterator it = pGrp->beginIndex();
      std::vector< CCopasiParameter * >::iterator end = pGrp->endIndex();

      while (it != end && *it != pParm) ++it;

      if (it == end)
        {
          CCopasiMessage(CCopasiMessage::ERROR, MCParameter + 5);
          return NULL;
        }

      pTo = new ElevateTo(*pFrom, NO_PARENT);

      // We do not want the parameter to be removed from the group which would happen during deletion.
      // To prevent this we remove it manually from the parent class.
      pGrp->CCopasiParameter::remove(pParm);
      delete pParm;
      pGrp->CCopasiParameter::add(pTo, true);

      *it = pTo;
    }
  else
    pTo = new ElevateTo(*pFrom, NO_PARENT);

  return pTo;
}
#endif // COPASI_CCopasiParameterGroup
