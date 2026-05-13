#ifndef GetVertexZ_h
#define GetVertexZ_h
//c++ stuff
#ifndef __CINT__
#  include <string> 
#  include "Riostream.h"//needed to use things like cout, which I will use primarily for debugging
#include "../StHighPtTree/TEvent.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"
#include <vector>
#endif
float GetVertexZ(char *dataset, StMuEvent *event);
float GetVertexZ(string dataset, StMuEvent *event);
float GetVertexZ(char *dataset, TEvent *event);
float GetVertexZ(string dataset, TEvent *event);
#endif
