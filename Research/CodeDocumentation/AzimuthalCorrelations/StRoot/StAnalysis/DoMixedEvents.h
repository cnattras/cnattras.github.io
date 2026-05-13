
#ifndef DoMixedEvents_h
#define DoMixedEvents_h
#ifndef __CINT__
#  include "Riostream.h"//needed to use things like cout, which I will use primarily for debugging
#endif
#include "TObjString.h"//needed for Form
#include "TH1F.h"
#include "TFile.h"
#include "StAnalysisTools/MixedEvents.h"
#include "StAnalysisTools/GetHistoName.h"
//#include "StHighPtTools/dPhi.h"
void DoMixedEvents(char *infile, string dataset);
#endif
