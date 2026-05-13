#ifndef GetTResonanceP_h
#define GetTResonanceP_h
#ifndef __CINT__
#  include <string> 
#  include "Riostream.h"//needed to use things like cout, which I will use primarily for debugging
#endif
#include "StMuDSTMaker/COMMON/StMuTrack.h"
#include "dPhi.h"

float GetTResonanceP(StMuTrack *posTrack, StMuTrack *negTrack);
float GetTResonancePt(StMuTrack *posTrack, StMuTrack *negTrack);
float GetTResonancePx(StMuTrack *posTrack, StMuTrack *negTrack);
float GetTResonancePy(StMuTrack *posTrack, StMuTrack *negTrack);
float GetTResonancePhi(StMuTrack *posTrack, StMuTrack *negTrack);
float GetTResonanceOpeningAngle(StMuTrack *posTrack, StMuTrack *negTrack);
#endif
