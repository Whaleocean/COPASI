/**
 * CTrajectory.cpp
 * copyright            : (C) 2001 by
 */

#include "copasi.h"
#include "CTrajectory.h"


//default constructor
CTrajectory::CTrajectory()
{
  mPoints = 0;
  mEndTime = 0.0;	
  mN = 0;
  mMethod = 0;

  mY = NULL;
  mModel = NULL;
  mODESolver = NULL;
}
	

//Constructor
CTrajectory::CTrajectory(CModel * aModel, C_INT32 aPoints,
                         C_FLOAT64 aEndTime, C_INT32 aMethod)
{
  mPoints = aPoints;
  mEndTime = aEndTime;
  mMethod = aMethod;

  mN = 0;

  mY = NULL;
  mModel = NULL;
  mODESolver = NULL;
    
  initialize(aModel);
}

// Object assignment overloading,
CTrajectory & CTrajectory::operator = (const CTrajectory& source)
{
  cleanup();
    
  if(this != &source)
    {
      mMethod = source.mMethod;
      mPoints = source.mPoints;
      mEndTime = source.mEndTime; 	
    }

  initialize(source.mModel);
    
  return *this;
}


//destructor
CTrajectory::~CTrajectory()
{
  cout << "~CTrajectory " << endl;
}

void CTrajectory::initialize(CModel * aModel)
{
  cleanup();
    
  // we really need a copy of the model here
  mModel = aModel;
  mN = mModel->getIndMetab();
    
  mY = mModel->getInitialNumbers();
    
  switch (mMethod)
    {
    case 1:
      mODESolver = new CODESolver();
      mODESolver->initialize(* mModel, mY, mN, mMethod);
      break;
    default:
      fatalError();
    }
    
  return;
}

void CTrajectory::cleanup()
{
  if (mY) delete [] mY;
  mY = NULL;
    
  //if (mModel) delete mModel;
  mModel = NULL;

  if (mODESolver) 
    {
      mODESolver->cleanup();
      delete mODESolver;
    }
    
  mODESolver = NULL;
    
  return;
}

C_INT32 CTrajectory::load(CReadConfig & configbuffer)
{
  C_INT32 Fail = 0;

  if((Fail = configbuffer.getVariable("EndTime", "C_FLOAT64",
				      (void *) &mEndTime,
				      CReadConfig::LOOP)))
    return Fail;
  
  if((Fail = configbuffer.getVariable("Points", "C_INT32",
				      (void *) &mPoints)))
    return Fail;
  
  return Fail;
}

C_INT32 CTrajectory::save(CWriteConfig & configbuffer)
{
  C_INT32 Fail = 0;

  if((Fail = configbuffer.setVariable("EndTime", "C_FLOAT64",
				      (void *) &mEndTime)))
    return Fail;
  
  if((Fail = configbuffer.setVariable("Points", "C_FLOAT64",
				      (void *) &mPoints)))
    return Fail;

  return Fail;
}

void CTrajectory::setModel(CModel * aModel)
{
  mModel = aModel;
}


CModel * CTrajectory::getModel() const
{
  return mModel;
}


void CTrajectory::setODESolver(CODESolver * aSolver)
{
  mODESolver = aSolver;
}


CODESolver * CTrajectory::getODESolver() const
{
  return mODESolver;
}


void CTrajectory::setPoints(const C_INT32 anInt)
{
  mPoints = anInt;	
}

C_INT32 CTrajectory::getPoints() const
{
  return mPoints;
}


void CTrajectory::setArrSize(const C_INT32 anInt)
{
  mN = anInt;
}


C_INT32 CTrajectory::getArrSize() const
{
  return mN;
}

	
void CTrajectory::setEndTime(const C_FLOAT64 aDouble)
{
  mEndTime = aDouble;
}

const C_FLOAT64 & CTrajectory::getEndTime() const
{
  return mEndTime;
}

const C_FLOAT64 & CTrajectory::getTime() const
{
  return mTime;
}

	
void CTrajectory::setMethod(const C_INT32 anInt)
{
  mMethod = anInt;
}

C_INT32 CTrajectory::getMethod() const
{
  return mMethod;
}

void CTrajectory::process()
{
  // mODESolver->initialize(* mModel, mY, mN, mMethod);
    
  // COutputEvent *OutInit = NULL, *OutPoint = NULL, *OutEnd = NULL;

  // mOutInit = COutputEvent(TIME_INIT, this);
  // mOutPoint = COutputEvent(TIME_POINT, this);		
  // mOutEnd = COutputEvent(TIME_END, this);


  //calculates number of iterations and time intervals
  C_FLOAT64 length = mEndTime/mPoints;
  mTime = 0.0;

  // print for the initial time point	
  // if (mOutInit) mOutInit->Print();
  // if (mOutPoint) mOutPoint->Print();
        
  for(C_INT32 i = 0; i < mPoints; i++)
    {
      //update the CODESolver from current time to end time
      cout << mTime << "  ";
      
      mODESolver->step(mTime, mTime+length);

      //update CModel
      mModel->setConcentrations(mY);

      //print for current time point in the outputEvent
      // if (OutPoint) OutPoint.Print();

      mTime += length;
    }
	
  // if (OutEnd) OutEnd.Print();

  // delete OutInit; -> to cleanup
  // delete OutPoint;
  // delete OutEnd;
    
  // mODESolver->cleanup();
}


