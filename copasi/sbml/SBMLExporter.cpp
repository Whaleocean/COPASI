/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/Attic/SBMLExporter.cpp,v $
   $Revision: 1.17 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2004/06/24 21:05:07 $
   End CVS Header */

#include "copasi.h"
#include "SBMLExporter.h"

#include "sbml/Unit.hpp"
#include "sbml/UnitKind.h"
#include "sbml/SBMLDocument.h"
#include "sbml/SBMLWriter.h"

#include "sbml/ModifierSpeciesReference.h"

const char* SBMLExporter::HTML_HEADER = "<body>";

const char* SBMLExporter::HTML_FOOTER = "</body>";

/**
 ** Constructor for the exporter.
 */
SBMLExporter::SBMLExporter(): sbmlDocument(NULL)
{
  /* nothing to do */
}

/**
 ** Destructor for the exporter.
 */
SBMLExporter::~SBMLExporter()
{
  /* delete the SBMLDocument created if it is not NULL */
  if (this->sbmlDocument != NULL)
    {
      delete this->sbmlDocument;
    }
}

/**
 ** This method takes a copasi CModel object, crerates an SBMLDocument from
 ** it and writes it to a file. The filename is given as the second
 ** argument to the function. The function return "true" on success and
 ** "false" on failure.
 */
bool SBMLExporter::exportSBML(const CModel* copasiModel, std::string sbmlFilename, int sbmlLevel, int sbmlVersion) throw (StdException)
{
  /* create the SBMLDocument from the copasi model */
  this->sbmlDocument = this->createSBMLDocumentFromCModel(copasiModel, sbmlLevel, sbmlVersion);
  if (this->sbmlDocument->getModel() != NULL)
    {
      SBMLWriter_t* writer = SBMLWriter_create();
      /* write the document to a file */
      int returnValue = SBMLWriter_writeSBML(writer, (SBMLDocument_t*)sbmlDocument, sbmlFilename.c_str());
      SBMLWriter_free(writer);
      if (returnValue == 1)
        {
          return true;
        }
      else
        {
          return false;
        }
    }
  else
    {
      /* if no SBMLDocument could be created return false */
      return false;
    }
}

/**
 **  This method takes a copasi CModel object and generates a SBMLDocument
 ** object from it.
 ** Optionally the method takes two integers that specify the level and the
 ** version number of the SBMLDocument that will be generated.
 */
SBMLDocument* SBMLExporter::createSBMLDocumentFromCModel(const CModel* copasiModel, int sbmlLevel, int sbmlVersion)
{
  /* create a new document object */
  SBMLDocument* sbmlDocument = new SBMLDocument();
  sbmlDocument->setLevel(sbmlLevel);
  sbmlDocument->setVersion(sbmlVersion);
  /* create the model object from the copasi model */
  Model* sbmlModel = this->createSBMLModelFromCModel(copasiModel);
  sbmlDocument->setModel(sbmlModel);
  return sbmlDocument;
}

/**
 ** This method taked a copasi CModel and generates a SBML Model object
 **  which is returned. On failure NULL is returned.
 */
Model* SBMLExporter::createSBMLModelFromCModel(const CModel* copasiModel)
{
  /* create a new model object */
  Model* sbmlModel = new Model();

  sbmlModel->setId(copasiModel->getKey().c_str());
  if (copasiModel->getObjectName().size() != 0)
    {
      sbmlModel->setName(copasiModel->getObjectName().c_str());
    }
  if ((copasiModel->getComments().size() != 0) && !(this->isEmptyString(copasiModel->getComments())))
    {
      sbmlModel->setNotes((SBMLExporter::HTML_HEADER + copasiModel->getComments() + SBMLExporter::HTML_FOOTER).c_str());
    }
  /* if the copasi volume unit does not correspond to the default SBML volume
  ** unit, we have to create a UnitDefinition and make it the default in the
  ** SBML model.
  */
  if (!(copasiModel->getVolumeUnit() == "l"))
    {
      UnitDefinition uDef = this->createSBMLVolumeUnitDefinitionFromCopasiVolumeUnit(copasiModel->getVolumeUnit());
      sbmlModel->addUnitDefinition(uDef);
    }
  /* if the copasi time unit does not correspond to the default SBML time
  ** unit, we have to create a UnitDefinition and make it the default in the
  ** SBML model.
  */
  if (!(copasiModel->getTimeUnit() == "s"))
    {
      UnitDefinition uDef = this->createSBMLTimeUnitDefinitionFromCopasiTimeUnit(copasiModel->getTimeUnit());
      sbmlModel->addUnitDefinition(uDef);
    }
  /* if the copasi quantity unit does not correspond to the default SBML
  ** substance
  ** unit, we have to create a UnitDefinition and make it the default in the
  ** SBML model.
  */
  if (!(copasiModel->getQuantityUnit() == "Mol"))
    {
      UnitDefinition uDef = this->createSBMLSubstanceUnitDefinitionFromCopasiQuantityUnit(copasiModel->getQuantityUnit());
      sbmlModel->addUnitDefinition(uDef);
    }
  /* create all compartments */
  unsigned int counter;
  for (counter = 0; counter < copasiModel->getCompartments().size(); counter++)
    {
      Compartment sbmlCompartment = this->createSBMLCompartmentFromCCompartment(copasiModel->getCompartments()[counter]);
      sbmlModel->addCompartment(sbmlCompartment);
    }
  /* create all metabolites */
  for (counter = 0; counter < copasiModel->getMetabolites().size(); counter++)
    {
      Species sbmlSpecies = this->createSBMLSpeciesFromCMetab(copasiModel->getMetabolites()[counter]);
      sbmlModel->addSpecies(sbmlSpecies);
    }
  /* create all reactions */
  for (counter = 0; counter < copasiModel->getReactions().size(); counter++)
    {
      Reaction sbmlReaction = this->createSBMLReactionFromCReaction(copasiModel->getReactions()[counter]);
      sbmlModel->addReaction(sbmlReaction);
    }
  return sbmlModel;
}

/**
 ** This method takes a string that specifies the time unit used in the
 ** copasi model and returns a pointer to the corresponding SBML
 ** UnitDefinition object.
 */
UnitDefinition SBMLExporter::createSBMLTimeUnitDefinitionFromCopasiTimeUnit(const std::string u)
{
  UnitDefinition uDef("time");
  Unit unit;

  if (u == "d")
    {
      unit = Unit(UNIT_KIND_SECOND, 1, 0);
      unit.setMultiplier(86400);
    }
  else if (u == "h")
    {
      unit = Unit(UNIT_KIND_SECOND, 1, 0);
      unit.setMultiplier(3600);
    }
  else if (u == "m")
    {
      unit = Unit(UNIT_KIND_SECOND, 1, 0);
      unit.setMultiplier(60);
    }

  else if (u == "ms")
    {
      unit = Unit(UNIT_KIND_SECOND, 1, -3);
    }
  else if (u == "\xc2\xb5s")
    {
      unit = Unit(UNIT_KIND_SECOND, 1, -6);
    }
  else if (u == "ns")
    {
      unit = Unit(UNIT_KIND_SECOND, 1, -9);
    }
  else if (u == "ps")
    {
      unit = Unit(UNIT_KIND_SECOND, 1, -12);
    }
  else if (u == "fs")
    {
      unit = Unit(UNIT_KIND_SECOND, 1, -15);
    }
  else
    {
      throw StdException("Error. Unknown copasi time unit.");
    }

  uDef.addUnit(unit);
  return uDef;
}

/**
 ** This method takes a string that specifies the substance unit used in the
 ** copasi model and returns a pointer to the corresponding SBML
 ** UnitDefinition object.
 */
UnitDefinition SBMLExporter::createSBMLSubstanceUnitDefinitionFromCopasiQuantityUnit(const std::string u)
{
  UnitDefinition uDef("substance");
  Unit unit;
  if (u == "mMol")
    {
      unit = Unit(UNIT_KIND_MOLE, 1, -3);
    }
  else if (u == "\xc2\xb5Mol")
    {
      unit = Unit(UNIT_KIND_MOLE, 1, -6);
    }
  else if (u == "nMol")
    {
      unit = Unit(UNIT_KIND_MOLE, 1, -9);
    }
  else if (u == "pMol")
    {
      unit = Unit(UNIT_KIND_MOLE, 1, -12);
    }
  else if (u == "fMol")
    {
      unit = Unit(UNIT_KIND_MOLE, 1, -15);
    }
  else if (u == "#")
    {
      unit = Unit(UNIT_KIND_ITEM, 1, 1);
    }
  else
    {
      throw StdException("Error. Unknown copasi quantity unit.");
    }
  uDef.addUnit(unit);
  return uDef;
}

/**
 ** This method takes a string that specifies the volume unit used in the
 ** copasi model and returns a pointer to the corresponding SBML
 ** UnitDefinition object.
 */
UnitDefinition SBMLExporter::createSBMLVolumeUnitDefinitionFromCopasiVolumeUnit(const std::string u)
{
  UnitDefinition uDef("volume");
  Unit unit;
  if (u == "ml")
    {
      unit = Unit(UNIT_KIND_LITER, 1, -3);
    }
  else if (u == "\xc2\xb5l")
    {
      unit = Unit(UNIT_KIND_LITER, 1, -6);
    }
  else if (u == "nl")
    {
      unit = Unit(UNIT_KIND_LITER, 1, -9);
    }
  else if (u == "pl")
    {
      unit = Unit(UNIT_KIND_LITER, 1, -12);
    }
  else if (u == "fl")
    {
      unit = Unit(UNIT_KIND_LITER, 1, -15);
    }
  else if (u == "m3")
    {
      unit = Unit(UNIT_KIND_METER, 3, 1);
    }
  else
    {
      throw StdException("Error. Unknown copasi volume unit.");
    }
  uDef.addUnit(unit);
  return uDef;
}

/**
 ** This method takes a pointer to a copasi CCompartment object and creates
 ** a SBML Compartment. The pointer to the SBML Comprtment is returned.
 */
Compartment SBMLExporter::createSBMLCompartmentFromCCompartment(const CCompartment* copasiCompartment)
{
  Compartment sbmlCompartment;
  sbmlCompartment.setId(copasiCompartment->getKey().c_str());
  sbmlCompartment.setName(copasiCompartment->getObjectName().c_str());
  sbmlCompartment.setSpatialDimensions(3);
  sbmlCompartment.setConstant(1);
  sbmlCompartment.setVolume(copasiCompartment->getInitialVolume());
  return sbmlCompartment;
}

/**
 ** This method takes a pointer to a copasi CMetab object and creates a SBML 
 ** Species object. The pointer to the species object is returned.
 */
Species SBMLExporter::createSBMLSpeciesFromCMetab(const CMetab* copasiMetabolite)
{
  Species sbmlSpecies;
  sbmlSpecies.setId(copasiMetabolite->getKey().c_str());
  sbmlSpecies.setName(copasiMetabolite->getObjectName().c_str());
  sbmlSpecies.setBoundaryCondition(false);
  sbmlSpecies.setConstant(copasiMetabolite->getStatus() == CMetab::METAB_FIXED);
  sbmlSpecies.setCompartment(copasiMetabolite->getCompartment()->getKey().c_str());
  sbmlSpecies.setInitialConcentration(copasiMetabolite->getInitialConcentration());
  return sbmlSpecies;
}

/**
 ** This method takes a pointer to a copasi CReaction object and creates an
 ** SBML Reaction object. The pointer to the created reaction object is
 ** returned.
 */
Reaction SBMLExporter::createSBMLReactionFromCReaction(const CReaction* copasiReaction)
{
  /* create a new reaction object */
  Reaction sbmlReaction;
  sbmlReaction.setId(copasiReaction->getKey().c_str());
  sbmlReaction.setName(copasiReaction->getObjectName().c_str());
  sbmlReaction.setReversible(copasiReaction->isReversible());
  const CChemEq chemicalEquation = copasiReaction->getChemEq();
  /* Add all substrates */
  unsigned int counter;
  for (counter = 0; counter < chemicalEquation.getSubstrates().size(); counter++)
    {
      CChemEqElement* element = chemicalEquation.getSubstrates()[counter];
      SpeciesReference sRef;
      sRef.setSpecies(element->getMetaboliteKey().c_str());
      sRef.setStoichiometry(element->getMultiplicity());
      sRef.setDenominator(1);
      sbmlReaction.addReactant(sRef);
    }
  /* Add all products */
  for (counter = 0; counter < chemicalEquation.getProducts().size(); counter++)
    {
      CChemEqElement* element = chemicalEquation.getProducts()[counter];
      SpeciesReference sRef;
      sRef.setSpecies(element->getMetaboliteKey().c_str());
      sRef.setStoichiometry(element->getMultiplicity());
      sRef.setDenominator(1);
      sbmlReaction.addProduct(sRef);
    }
  /* Add all modifiers */
  for (counter = 0; counter < chemicalEquation.getModifiers().size(); counter++)
    {
      CChemEqElement* element = chemicalEquation.getModifiers()[counter];
      ModifierSpeciesReference sRef;
      sRef.setSpecies(element->getMetaboliteKey().c_str());
      sbmlReaction.addModifier(sRef);
    }
  /* create the kinetic law */
  KineticLaw kLaw = this->createSBMLKineticLawFromCReaction(copasiReaction);
  sbmlReaction.setKineticLaw(kLaw);
  return sbmlReaction;
}

/**
 ** This method takes a pointer to a copasi CReation object and creates a
 ** SBML KineticLaw object from the kintik function of the copasi reaction
 ** object. The pointer to the created KineticLaw is returned.
 */
KineticLaw SBMLExporter::createSBMLKineticLawFromCReaction(const CReaction* copasiReaction)
{
  /* create a new KineticLaw */
  KineticLaw kLaw;
  /* if the copasi CFunction specifies a mass-action kinetic */
  if (copasiReaction->getFunction().getType() == CFunction::MassAction)
    {
      const CMassAction cMassAction = static_cast<const CMassAction>(copasiReaction->getFunction());
      /* create the ASTNode that multiplies all substrates with the first
      ** kinetic constant.
      */
      ASTNode* forwardNode = new ASTNode(AST_TIMES);

      ASTNode* parameterNode1 = new ASTNode(AST_NAME);
      std::string parameterName1 = cMassAction.getParameters()[0]->getObjectName();
      parameterNode1->setName(parameterName1.c_str());
      Parameter parameter1;
      parameter1.setId(parameterName1.c_str());
      parameter1.setValue(copasiReaction->getParameterValue(parameterName1));
      kLaw.addParameter(parameter1);

      forwardNode->addChild(parameterNode1);
      forwardNode->addChild(this->createTimesTree(copasiReaction->getChemEq().getSubstrates()));
      /* if the reaction is reversible, create the ASTNode tree that
      ** multiplies all products with the second kinetic constant and
      ** subtract this tree from the tree of the forward reaction.
      */
      if (cMassAction.isReversible() == TriTrue)
        {
          ASTNode* backwardNode = new ASTNode(AST_TIMES);

          ASTNode* parameterNode2 = new ASTNode(AST_NAME);
          std::string parameterName2 = cMassAction.getParameters()[2]->getObjectName();
          parameterNode2->setName(parameterName2.c_str());
          Parameter parameter2;
          parameter2.setId(parameterName2.c_str());
          parameter2.setValue(copasiReaction->getParameterValue(parameterName2));
          kLaw.addParameter(parameter2);
          backwardNode->addChild(parameterNode2);

          backwardNode->addChild(this->createTimesTree(copasiReaction->getChemEq().getProducts()));
          ASTNode* tempNode = new ASTNode(AST_MINUS);
          tempNode->addChild(forwardNode);
          tempNode->addChild(backwardNode);
          forwardNode = tempNode;
        }

      /*
       ** If the reaction takes place in a single compartment, the rate law has
       ** to be converted from concentration/time to substance/time by
       ** multiplying the rate law with the volume of the compartment.
       */
      if (copasiReaction->getCompartmentNumber() == 1)
        {
          ASTNode* tNode = new ASTNode(AST_TIMES);
          ASTNode* vNode = new ASTNode(AST_REAL);
          double volume = 0.0;
          if (copasiReaction->getChemEq().getSubstrates().size() != 0)
            {
              volume = copasiReaction->getChemEq().getSubstrates()[0]->getMetabolite().getCompartment()->getInitialVolume();
            }
          else
            {
              volume = copasiReaction->getChemEq().getProducts()[0]->getMetabolite().getCompartment()->getInitialVolume();
            }
          /* only multiply if the volume is neither 1 nor 0 */
          if (volume != 1.0 && volume != 0.0)
            {
              /* if the whole function already has been divided by the same
              ** volume, e.g. by a formaer export, drop one level instead of
              ** adding another one */
              if ((forwardNode->getType() == AST_DIVIDE) && (forwardNode->getRightChild()->getType() == AST_REAL) && (forwardNode->getRightChild()->getReal() == volume))
                {
                  forwardNode = forwardNode->getLeftChild();
                }
              else
                {
                  vNode->setValue(volume);
                  tNode->addChild(forwardNode);
                  tNode->addChild(vNode);
                  forwardNode = tNode;
                }
            }
        }
      kLaw.setMath(forwardNode);
    }
  /* if the copasi CFunction does not specify a mass-action kinetic, it is a
  ** CKinFunction */
  else
    {
      CKinFunction cKinFunction = static_cast<CKinFunction>(copasiReaction->getFunction());
      ASTNode* node = this->createASTNodeFromCNodeK(cKinFunction.getNodes()[0]->getLeft(), cKinFunction, copasiReaction->getParameterMappings());

      /*
       ** If the reaction takes place in a single compartment, the rate law has
       ** to be converted from concentration/time to substance/time by
       ** multiplying the rate law with the volume of the compartment.
       */
      if (copasiReaction->getCompartmentNumber() == 1)
        {
          ASTNode* tNode = new ASTNode(AST_TIMES);
          ASTNode* vNode = new ASTNode(AST_REAL);
          double volume = 0.0;
          if (copasiReaction->getChemEq().getSubstrates().size() != 0)
            {
              volume = copasiReaction->getChemEq().getSubstrates()[0]->getMetabolite().getCompartment()->getInitialVolume();
            }
          else
            {
              volume = copasiReaction->getChemEq().getProducts()[0]->getMetabolite().getCompartment()->getInitialVolume();
            }
          if (volume != 1.0 && volume != 0.0)
            {
              /* if the whole function already has been divided by the same
              ** volume, e.g. by a formaer export, drop one level instead of
              ** adding another one */
              if ((node->getType() == AST_DIVIDE) && (node->getRightChild()->getType() == AST_REAL) && (node->getRightChild()->getReal() == volume))
                {
                  node = node->getLeftChild();
                }
              else
                {
                  vNode->setValue(volume);
                  tNode->addChild(vNode);
                  tNode->addChild(node);
                  node = tNode;
                }
            }
        }

      kLaw.setMath(node);
      /* add the parameters */
      unsigned int counter;
      for (counter = 0; counter < copasiReaction->getFunctionParameters().size(); counter++)
        {
          const CFunctionParameter* para = copasiReaction->getFunctionParameters()[counter];
          if (para->getUsage() == "PARAMETER")
            {
              Parameter sbmlPara;

              std::string parameterKey = copasiReaction->getParameterMappings()[counter][0];

              sbmlPara.setId(para->getObjectName().c_str());
              sbmlPara.setValue(copasiReaction->getParameterValue(para->getObjectName()));
              kLaw.addParameter(sbmlPara);
            }
        }
    }
  return kLaw;
}

/**
 ** This method creates an ASTNode tree where all the species specified in
 ** the given vector are multiplied. This is used to create the mass action
 ** kinetic law.
 */
ASTNode* SBMLExporter::createASTNodeFromCNodeK(const CNodeK& cNodeK, const CKinFunction& kinFunction, const std::vector< std::vector < std::string > >& vect)
{
  ASTNode* node = new ASTNode();
  char mType = cNodeK.getType();
  char mSubtype = cNodeK.getSubtype();
  ASTNode* childNode = NULL;
  switch (mType)
    {
    case N_NUMBER:
      //ASTNode_setType(node, AST_REAL);
      node->setValue(cNodeK.getConstant());
      break;
    case N_IDENTIFIER:
      node->setType(AST_NAME);
      CFunctionParameter::DataType dataType;
      /* resolve the parameter name mapping */
      if (mSubtype == N_KCONSTANT)
        {
          node->setName(cNodeK.getName().c_str());
        }
      else
        {
          node->setName(vect[kinFunction.getParameters().findParameterByName(cNodeK.getName(), dataType)][0].c_str());
        }
      break;
    case N_OPERATOR:
      switch (mSubtype)
        {
        case '+':
          node->setType(AST_PLUS);
          childNode = this->createASTNodeFromCNodeK(cNodeK.getLeft(), kinFunction, vect);
          node->addChild(childNode);
          childNode = this->createASTNodeFromCNodeK(cNodeK.getRight(), kinFunction, vect);
          node->addChild(childNode);
          break;
        case '-':
          node->setType(AST_MINUS);
          childNode = this->createASTNodeFromCNodeK(cNodeK.getLeft(), kinFunction, vect);
          node->addChild(childNode);
          childNode = this->createASTNodeFromCNodeK(cNodeK.getRight(), kinFunction, vect);
          node->addChild(childNode);
          break;
        case '*':
          node->setType(AST_TIMES);
          childNode = this->createASTNodeFromCNodeK(cNodeK.getLeft(), kinFunction, vect);
          node->addChild(childNode);
          childNode = this->createASTNodeFromCNodeK(cNodeK.getRight(), kinFunction, vect);
          node->addChild(childNode);
          break;
        case '/':
          node->setType(AST_DIVIDE);
          childNode = this->createASTNodeFromCNodeK(cNodeK.getLeft(), kinFunction, vect);
          node->addChild(childNode);
          childNode = this->createASTNodeFromCNodeK(cNodeK.getRight(), kinFunction, vect);
          node->addChild(childNode);
          break;
        case '^':
          node->setType(AST_POWER);
          childNode = this->createASTNodeFromCNodeK(cNodeK.getLeft(), kinFunction, vect);
          node->addChild(childNode);
          childNode = this->createASTNodeFromCNodeK(cNodeK.getRight(), kinFunction, vect);
          node->addChild(childNode);
          break;
        default:
          break;
        }
      break;
    case N_FUNCTION:
      switch (mSubtype)
        {
        case '+':
          node = this->createASTNodeFromCNodeK(cNodeK.getLeft(), kinFunction, vect);
          break;
        case '-':
          node->setType(AST_MINUS);
          childNode = this->createASTNodeFromCNodeK(cNodeK.getLeft(), kinFunction, vect);
          node->addChild(childNode);
          break;
        case N_EXP:
          node->setType(AST_FUNCTION_EXP);
          node->setName("exp");
          childNode = this->createASTNodeFromCNodeK(cNodeK.getLeft(), kinFunction, vect);
          node->addChild(childNode);
          childNode = this->createASTNodeFromCNodeK(cNodeK.getRight(), kinFunction, vect);
          node->addChild(childNode);
          break;
        case N_LOG:
          node->setType(AST_FUNCTION_LN);
          node->setName("ln");
          childNode = this->createASTNodeFromCNodeK(cNodeK.getLeft(), kinFunction, vect);
          node->addChild(childNode);
          break;
        case N_LOG10:
          node->setType(AST_FUNCTION_LOG);
          node->setName("log");
          childNode = this->createASTNodeFromCNodeK(cNodeK.getLeft(), kinFunction, vect);
          node->addChild(childNode);
          break;
        case N_SIN:
          node->setType(AST_FUNCTION_SIN);
          node->setName("sin");
          childNode = this->createASTNodeFromCNodeK(cNodeK.getLeft(), kinFunction, vect);
          node->addChild(childNode);
          break;
        case N_COS:
          node->setType(AST_FUNCTION_COS);
          node->setName("cos");
          childNode = this->createASTNodeFromCNodeK(cNodeK.getLeft(), kinFunction, vect);
          node->addChild(childNode);
          break;
        default:
          break;
        }
      break;
    default:
      break;
    }
  return node;
}

/**
 ** This method creates an ASTNode tree where all the species specified in
 ** the given vector are multiplied. This is used to create the mass action
 ** kinetic law.
 */
ASTNode* SBMLExporter::createTimesTree(const CCopasiVector<CChemEqElement >& vect, unsigned int pos)
{
  ASTNode* node = NULL;
  double multiplicity = vect[pos]->getMultiplicity();
  if (pos == vect.size() - 1)
    {
      node = new ASTNode(AST_NAME);
      node->setName(vect[pos]->getMetaboliteKey().c_str());
      /* if the stoichiometry is not 1.0, we have to add it to the exponent */
      if (multiplicity != 1.0)
        {
          ASTNode* tmpNode1 = new ASTNode(AST_POWER);
          ASTNode* tmpNode2 = new ASTNode(AST_REAL);
          tmpNode2->setValue(multiplicity);
          tmpNode1->addChild(node);
          tmpNode1->addChild(tmpNode2);
          node = tmpNode1;
        }
    }
  else
    {
      node = new ASTNode(AST_TIMES);
      ASTNode* child = new ASTNode(AST_NAME);
      child->setName(vect[pos]->getMetaboliteKey().c_str());

      /* if the stoichiometry is not 1.0, we have to add it to the exponent */
      if (multiplicity != 1.0)
        {
          ASTNode* tmpNode1 = new ASTNode(AST_POWER);
          ASTNode* tmpNode2 = new ASTNode(AST_REAL);
          tmpNode2->setValue(multiplicity);
          tmpNode1->addChild(child);
          tmpNode1->addChild(tmpNode2);
          child = tmpNode1;
        }

      node->addChild(child);
      node->addChild(this->createTimesTree(vect, pos + 1));
    }
  return node;
}

/**
 ** This method tests if a string only consists of whitespace characters
 */
bool SBMLExporter::isEmptyString(const std::string str)
{
  bool result = true;
  unsigned int counter;
  for (counter = 0; counter < str.size(); counter++)
    {
      if ((str[counter] != ' ') && (str[counter] != '\n') && (str[counter] != '\t') && (str[counter] != '\r'))
        {
          result = false;
          break;
        }
    }
  return result;
}
