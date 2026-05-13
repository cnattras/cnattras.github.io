
#ifndef IsGoodEvent_h
#define IsGoodEvent_h
#ifndef __CINT__
#  include "IsGoodEvent.h"
#  include <string> 
#  include "Riostream.h"//needed to use things like cout, which I will use primarily for debugging
#include "../StHighPtTree/TEvent.h"
#include "IsGoodVertex.h"
#include "IsGoodRefMult.h"
#include "IsGoodTrigger.h"
#include "goodTriggers.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"
#include "StPrimaryVertex.h"
#include <vector>
#endif

bool IsGoodEvent(const char *, TEvent *);
bool IsGoodEvent(const char *, StMuEvent *);
bool IsGoodEvent(const string, TEvent *);
bool IsGoodEvent(const string, StMuEvent *);
#endif
