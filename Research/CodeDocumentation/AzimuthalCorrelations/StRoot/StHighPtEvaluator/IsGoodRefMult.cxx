#include "IsGoodRefMult.h"
bool IsGoodRefMult(const string dataset, int refmult){
  return IsGoodRefMult( dataset.c_str() , refmult);
}

bool IsGoodRefMult(const char *dataset, int refmult){//In principle this could be a dataset dependent quantity.  However, practically this isn't a concern.
  int max = 9999;
  int min = 0;
  //if this needs to be added, uncomment
  /*
  string myDataSet = dataset;
  string AuAu200Y2 = "AuAu200Y2";
  string AuAu200 = "AuAu200";
  string dAu200 = "dAu200";
  string CuCu200 = "CuCu200";
  string CuCu62 = "CuCu62";
  string AuAu62 = "AuAu62";
  if(dataset == AuAu200){
  }
  if(dataset == CuCu200){
  }
  if(dataset == AuAu62){
  }
  if(dataset == CuCu62){
  }
  */
  if(refmult>0 && refmult <9999){return true;}
  //return (refmult>min && refmult<max);
  return false;
}


bool IsGoodRefMult(const string dataset,StMuEvent *event){
  return IsGoodRefMult( dataset.c_str(), event );
}
bool IsGoodRefMult(const char *dataset, StMuEvent *event){
  return IsGoodRefMult(dataset, event->refMult() );
}
bool IsGoodRefMult(const string dataset,TEvent *event){
  return IsGoodRefMult( dataset.c_str(), event );
}
bool IsGoodRefMult(const char *dataset, TEvent *event){
  return IsGoodRefMult( dataset, event->GetMultiplicity() );
}
