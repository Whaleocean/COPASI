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

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

%{

#include "utilities/CCopasiProblem.h"

%}

%ignore CCopasiProblem::CCopasiProblem(const CCopasiTask::Type& type, const CDataContainer* pParent);
//%ignore CCopasiProblem::setCallBack;
%ignore CCopasiProblem::initialize();
%ignore CCopasiProblem::calculate();
%ignore CCopasiProblem::restore(const bool& updateModel);
%ignore CCopasiProblem::checkParametricConstraints();
%ignore CCopasiProblem::checkFunctionalConstraints();
%ignore CCopasiProblem::print(std::ostream* ostream) const;
%ignore CCopasiProblem::printResult(std::ostream* ostream) const;
%ignore operator<<(std::ostream& os,const CCopasiProblem& o);

%include "utilities/CCopasiProblem.h"

