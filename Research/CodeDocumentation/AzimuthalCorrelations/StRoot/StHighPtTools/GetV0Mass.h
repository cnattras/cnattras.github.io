
#ifndef GetV0Mass_h
#define GetV0Mass_h
#ifndef __CINT__
#  include <string> 
#  include "Riostream.h"//needed to use things like cout, which I will use primarily for debugging
#endif
//#include "StMuDSTMaker/COMMON/StMuTrack.h"
#include "StStrangeMuDstMaker/StV0MuDst.hh"
#include "../StHighPtTree/TV0Track.h"
double GetV0Mass(StV0MuDst* v0Candidate, int particleType);
double GetV0Mass(TV0Track *v0Candidate, int particleType);

#endif
