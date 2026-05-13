#ifndef GetEventID_h
#define GetEventID_h
//c++ stuff
#ifndef __CINT__
#  include <string> 
#  include "Riostream.h"//needed to use things like cout, which I will use primarily for debugging
#include "../StHighPtTree/TEvent.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"
#endif
int GetEventID(char *dataset, StMuEvent *event);
int GetEventID(string dataset, StMuEvent *event);
int GetEventID(char *dataset, TEvent *event);
int GetEventID(string dataset, TEvent *event);
#endif
