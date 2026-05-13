
#ifndef GetTResonanceMass_h
#define GetTResonanceMass_h
#ifndef __CINT__
#  include <string> 
#  include "Riostream.h"//needed to use things like cout, which I will use primarily for debugging
#endif
#include "StMuDSTMaker/COMMON/StMuTrack.h"
#include "GetTResonanceP.h"

float GetTResonanceMass(StMuTrack *posTrack, StMuTrack *negTrack, int type);
#endif
