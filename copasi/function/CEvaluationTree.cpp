/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationTree.cpp,v $
   $Revision: 1.11 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/14 17:34:38 $
   End CVS Header */

#include "copasi.h"

#include <sstream>
#include <vector>

#include "CEvaluationNode.h"
#include "CEvaluationTree.h"

#include "sbml/math/ASTNode.h"

#undef yyFlexLexer
#define yyFlexLexer CEvaluationFlexLexer
#include "CEvaluationLexer.h"

CEvaluationTree::CEvaluationTree():
    mInfix(),
    mErrorPosition(std::string::npos),
    mpNodeList(NULL),
    mpRoot(NULL)
{}

CEvaluationTree::CEvaluationTree(const CEvaluationTree & src):
    mInfix(),
    mErrorPosition(std::string::npos),
    mpNodeList(NULL),
    mpRoot(NULL)
{setInfix(src.mInfix);}

CEvaluationTree::~CEvaluationTree()
{
  if (mpNodeList != NULL) CEvaluationParser::freeNodeList(mpNodeList);
}

bool CEvaluationTree::setInfix(const std::string & infix)
{
  if (infix == mInfix) return true;

  mInfix = infix;

  return parse();
}

const std::string & CEvaluationTree::getInfix() const
{return mInfix;}

unsigned C_INT32 CEvaluationTree::getVariableIndex(const std::string & /*name*/) const
  {return C_INVALID_INDEX;}

const C_FLOAT64 & CEvaluationTree::getVariableValue(const unsigned C_INT32 & /*index*/) const
  {
    static C_FLOAT64 Value = std::numeric_limits<C_FLOAT64>::signaling_NaN();
    return Value;
  }

C_FLOAT64 * CEvaluationTree::getObjectValue(const CCopasiObjectName & /*CN*/) const
  {return NULL;}

bool CEvaluationTree::parse()
{
  bool success = true;

  // clean up
  CEvaluationParser::freeNodeList(mpNodeList);
  mpNodeList = NULL;
  mpRoot = NULL;

  // parse the description into a linked node tree
  std::istringstream buffer(mInfix);
  CEvaluationLexer Parser(&buffer);

  CCopasiMessage::clearDeque();

  success = (Parser.yyparse() == 0);

  mpNodeList = Parser.getNodeList();
  mpRoot = Parser.getRootNode();

  // clean up if parsing failed
  if (!success)
    {
      mErrorPosition = Parser.getErrorPosition();

      CEvaluationParser::freeNodeList(mpNodeList);
      mpNodeList = NULL;
      mpRoot = NULL;
    }

  return success;
}

bool CEvaluationTree::compileNodes()
{
  if (mpNodeList == NULL) return false;

  bool success = true;

  std::vector< CEvaluationNode * >::iterator it;
  std::vector< CEvaluationNode * >::iterator end = mpNodeList->end();

  for (it = mpNodeList->begin(); it != end && success; ++it)
    success = (*it)->compile(this);

  if (!success)
    {
      end = it;
      mErrorPosition = 0;

      for (it = mpNodeList->begin(); it != end; ++it)
        mErrorPosition += (*it)->getData().length();

      mErrorPosition -= (*--it)->getData().length();
      CCopasiMessage(CCopasiMessage::ERROR, MCFunction + 3, mErrorPosition);
    }

  return success;
}

bool CEvaluationTree::setTree(const ASTNode& pRootNode)
{
  mpRoot = CEvaluationTree::convertASTNode(pRootNode);
  return true;
}

CEvaluationNode* CEvaluationTree::convertASTNode(const ASTNode& node)
{
  CEvaluationNode* pResultNode = NULL;
  ASTNodeType_t nodeType = node.getType();
  CCopasiMessage Message;
  switch (nodeType)
    {
    case AST_LAMBDA:
      break;
    case AST_PLUS:
    case AST_MINUS:
    case AST_TIMES:
    case AST_DIVIDE:
    case AST_POWER:
    case AST_FUNCTION_POWER:
      // create a CEvaluationNodeOperator
      pResultNode = CEvaluationNodeOperator::createNodeFromASTTree(node);
      break;
    case AST_INTEGER:
    case AST_REAL:
    case AST_REAL_E:
    case AST_RATIONAL:
      // create a CEvaluationNodeNumber
      pResultNode = CEvaluationNodeNumber::createNodeFromASTTree(node);
      break;
    case AST_NAME:
    case AST_NAME_TIME:
      // create a CEvaluationNodeObject
      pResultNode = CEvaluationNodeObject::createNodeFromASTTree(node);
      break;
    case AST_CONSTANT_E:
    case AST_CONSTANT_PI:
      // create a CEvaluationNodeConstant
      pResultNode = CEvaluationNodeConstant::createNodeFromASTTree(node);
      break;
    case AST_FUNCTION:
      // create a function call node
      //pRoot=CEvaluationNode???::createNodeFromASTTree(pRootNode);
      break;
    case AST_FUNCTION_ABS:
    case AST_FUNCTION_ARCCOS:
    case AST_FUNCTION_ARCCOSH:
    case AST_FUNCTION_ARCCOT:
    case AST_FUNCTION_ARCCOTH:
    case AST_FUNCTION_ARCCSC:
    case AST_FUNCTION_ARCCSCH:
    case AST_FUNCTION_ARCSEC:
    case AST_FUNCTION_ARCSECH:
    case AST_FUNCTION_ARCSIN:
    case AST_FUNCTION_ARCSINH:
    case AST_FUNCTION_ARCTAN:
    case AST_FUNCTION_ARCTANH:
    case AST_FUNCTION_CEILING:
    case AST_FUNCTION_COS:
    case AST_FUNCTION_COSH:
    case AST_FUNCTION_COT:
    case AST_FUNCTION_COTH:
    case AST_FUNCTION_CSC:
    case AST_FUNCTION_CSCH:
    case AST_FUNCTION_EXP:
    case AST_FUNCTION_FACTORIAL:
    case AST_FUNCTION_FLOOR:
    case AST_FUNCTION_LN:
    case AST_FUNCTION_LOG:
    case AST_FUNCTION_ROOT:
    case AST_FUNCTION_SEC:
    case AST_FUNCTION_SECH:
    case AST_FUNCTION_SIN:
    case AST_FUNCTION_SINH:
    case AST_FUNCTION_TAN:
    case AST_FUNCTION_TANH:
      // create a CEvaluationNodeFunction
      pResultNode = CEvaluationNodeFunction::createNodeFromASTTree(node);
      break;

    case AST_CONSTANT_FALSE:
    case AST_CONSTANT_TRUE:
    case AST_FUNCTION_DELAY:
    case AST_FUNCTION_PIECEWISE:
    case AST_LOGICAL_AND:
    case AST_LOGICAL_NOT:
    case AST_LOGICAL_OR:
    case AST_LOGICAL_XOR:
    case AST_RELATIONAL_EQ:
    case AST_RELATIONAL_GEQ:
    case AST_RELATIONAL_GT:
    case AST_RELATIONAL_LEQ:
    case AST_RELATIONAL_LT:
    case AST_RELATIONAL_NEQ:
      // create an unsupported element error
      Message = CCopasiMessage(CCopasiMessage::EXCEPTION, MCMathML + 1,
                               node.getName());
      break;

    case AST_UNKNOWN:
      // create an unknown element error
      Message = CCopasiMessage(CCopasiMessage::EXCEPTION, MCMathML + 2);

      break;
    }
  return pResultNode;
}
