// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CMetab.i,v $ 
//   $Revision: 1.6 $ 
//   $Name:  $ 
//   $Author: shoops $ 
//   $Date: 2009/01/07 18:51:30 $ 
// End CVS Header 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

%{

#include "model/CMetab.h"

%}

#ifdef SWIGJAVA
// remove some const methods to get rid of warnings
%ignore CMetab::operator =;

#endif // SWIGJAVA


%include "model/CMetab.h"


