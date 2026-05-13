#include "GetRefMult.h"
int GetRefMult(char *dataset, StMuEvent *event){
  if(!event){return -1;}
  return event->refMult();
}
int GetRefMult(string dataset, StMuEvent *event){
  return GetRefMult( (char*) dataset.c_str(), event);
}
int GetRefMult(char *dataset, TEvent *event){
  if(!event){return -1;}
  return event->GetMultiplicity();
}
int GetRefMult(string dataset, TEvent *event){
  return GetRefMult( (char*) dataset.c_str(), event);
}
