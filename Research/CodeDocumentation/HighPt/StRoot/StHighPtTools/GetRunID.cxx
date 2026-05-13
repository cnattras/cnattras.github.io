#include "GetRunID.h"
int GetRunID(char *dataset, StMuEvent *event){
  if(!event){return -1;}
  return event->runId();
}
int GetRunID(string dataset, StMuEvent *event){
  return GetRunID( (char*) dataset.c_str(), event);
}
int GetRunID(char *dataset, TEvent *event){
  if(!event){return -1;}
  return event->GetHeader()->GetRun();
}
int GetRunID(string dataset, TEvent *event){
  return GetRunID( (char*) dataset.c_str(), event);
}
