
#ifndef GetdEdXNSigma_h
#define GetdEdXNSigma_h
#ifndef __CINT__
#  include <string> 
#  include "Riostream.h"//needed to use things like cout, which I will use primarily for debugging
#endif
#include "StStrangeMuDstMaker/StV0MuDst.hh"
#include "../StHighPtTree/TV0Track.h"
#include "StarClassLibrary/BetheBloch.h" 
#include "StBichsel/Bichsel.h"

double GetPosDaughtdEdXNSigma(char *dataset, StV0MuDst *track, int type);
double GetNegDaughtdEdXNSigma(string dataset, StV0MuDst *track, int type);
double GetPosDaughtdEdXNSigma(char *dataset, TV0Track *track, int type);
double GetNegDaughtdEdXNSigma(string dataset, TV0Track *track, int type);
double GetdEdXNSigma(char *dataset, double momOverMass, double realDedx,double numDedx,double errDedx,double trackLength = -100.,double eta = -100.);

#endif
