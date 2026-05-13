#include "GetVertexZ.h"
float GetVertexZ(char *dataset, StMuEvent *event){
  if(!event){return -1;}
  return event->primaryVertexPosition().z();
}
float GetVertexZ(string dataset, StMuEvent *event){
  return GetVertexZ( (char*) dataset.c_str(), event);
}
float GetVertexZ(char *dataset, TEvent *event){
  if(!event){return -1;}
  return event->GetZVertex();
}
float GetVertexZ(string dataset, TEvent *event){
  return GetVertexZ( (char*) dataset.c_str(), event);
}
