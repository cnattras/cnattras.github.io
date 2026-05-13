#ifndef GetRefMult_h
#define GetRefMult_h
//c++ stuff
#ifndef __CINT__
#  include <string> 
#  include "Riostream.h"//needed to use things like cout, which I will use primarily for debugging
#include "../StHighPtTree/TEvent.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"
#endif
int GetRefMult(char *dataset, StMuEvent *event);
int GetRefMult(string dataset, StMuEvent *event);
int GetRefMult(char *dataset, TEvent *event);
int GetRefMult(string dataset, TEvent *event);
#endif
