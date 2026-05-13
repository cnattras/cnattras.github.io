
#ifndef IsGoodRefMult_h
#define IsGoodRefMult_h
#ifndef __CINT__
#  include "IsGoodRefMult.h"
#  include <string> 
#  include "Riostream.h"//needed to use things like cout, which I will use primarily for debugging
#endif
#include "../StHighPtTree/TEvent.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"
bool IsGoodRefMult(const string dataset,int refmult);
bool IsGoodRefMult(const char *dataset, int refmult);
bool IsGoodRefMult(const string dataset,StMuEvent *event);
bool IsGoodRefMult(const char *dataset, StMuEvent *event);
bool IsGoodRefMult(const string dataset,TEvent *event);
bool IsGoodRefMult(const char *dataset, TEvent *event);
#endif
