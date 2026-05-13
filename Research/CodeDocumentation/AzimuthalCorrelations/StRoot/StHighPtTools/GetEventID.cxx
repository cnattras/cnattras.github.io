#include "GetEventID.h"
int GetEventID(char *dataset, StMuEvent *event){
  if(!event){return -1;}
  return event->eventId();
}
int GetEventID(string dataset, StMuEvent *event){
  return GetEventID( (char*) dataset.c_str(), event);
}
int GetEventID(char *dataset, TEvent *event){
  if(!event){return -1;}
  return event->GetHeader()->GetEvtNum();
}
int GetEventID(string dataset, TEvent *event){
  return GetEventID( (char*) dataset.c_str(), event);
}
