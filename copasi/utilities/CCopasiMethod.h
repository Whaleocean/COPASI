/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CCopasiMethod.h,v $
   $Revision: 1.7 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/01/04 17:19:23 $
   End CVS Header */

/**
 *  CCopasiMethod class.
 *  This class is used to describe a method in COPASI. This class is 
 *  intended to be used as the parent class for all methods whithin COPASI.
 *  
 *  Created for Copasi by Stefan Hoops 2003
 */

#ifndef COPASI_CCopasiMethod
#define COPASI_CCopasiMethod

#include <string>

#include "CCopasiParameterGroup.h"
#include "CCopasiTask.h"
#include "CReadConfig.h"

class CCopasiMethod : public CCopasiParameterGroup
  {
  public:
    /**
     * Enumeration of the sub types of methods known to COPASI.
     */
    enum SubType
    {
      unset = 0,
      RandomSearch,
      RandomSearchMaster,
      SimulatedAnnealing,
      GeneticAlgorithm,
      EvolutionaryProgram2,
      HybridGASA,
      Newton,
      deterministic,
      stochastic,
      hybrid,
      mcaMethodReder,
      scanMethod
    };

    /**
     * String literals for the GUI to display sub type names of methods known
     * to COPASI.
     */
    static const std::string SubTypeName[];

    /**
     * XML sub type names of methods known to COPASI.
     */
    static const char* XMLSubType[];

    // Attributes
  private:
    /**
     * The type of the method
     */
    CCopasiTask::Type mType;

    /**
     * The type of the method
     */
    CCopasiMethod::SubType mSubType;

    // Operations

  private:
    /**
     * Default constructor
     */
    CCopasiMethod();

  protected:
    /**
     * Specific constructor
     * @param const CCopasiTask::Type & type
     * @param const CCopasiMethod::SubType & subType
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CCopasiMethod(const CCopasiTask::Type & taskType,
                  const SubType & subType,
                  const CCopasiContainer * pParent = NULL);

  public:
    /**
     * Convert a SubTypeName to the matching enum value.
     * Returns CCopasiMethod::unset if no match is found.
     * @param (const std::string & subTypeName)
     * @return CCopasiMethod::SubType type
     */
    static
    CCopasiMethod::SubType TypeNameToEnum(const std::string & subTypeName);

    /**
     * Convert a XMLSubType to the matching enum value
     * Returns CCopasiMethod::unset if no match is found.
     * @param (const char * xmlTypeName)
     * @return CCopasiMethod::SubType type
     */
    static
    CCopasiMethod::SubType XMLNameToEnum(const char * xmlTypeName);

    /**
     * Copy constructor
     * @param const CCopasiMethodr & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CCopasiMethod(const CCopasiMethod & src,
                  const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    virtual ~CCopasiMethod();

    /**
     * Retrieve the type of the method
     * @return  const string & type
     */
    const CCopasiTask::Type & getType() const;

    /**
     * Retrieve the sub type of the method
     * @return CCopasiMethod::SubType & subType
     */
    const CCopasiMethod::SubType & getSubType() const;

    /**
     * Load a list of parameters
     * @param "CReadConfig &" configBuffer
     * @param "CReadConfig::Mode" mode Default(CReadConfig::SEARCH)
     */
    virtual void load(CReadConfig & configBuffer,
                      CReadConfig::Mode mode = CReadConfig::SEARCH);
  };

#endif // COPASI_CCopasiMethod
