
#ifndef DoMixEveCorrections_h
#define DoMixEveCorrections_h
#ifndef __CINT__
#  include "Riostream.h"//needed to use things like cout, which I will use primarily for debugging
#endif
#include "TObjString.h"//needed for Form
#include "TH1F.h"
#include "TFile.h"
#include "StAnalysisTools/MixedEvents.h"
#include "StAnalysisTools/GetHistoName.h"
//#include "StHighPtTools/dPhi.h"
void DoMixEveCorrections(char *infile, string dataset, char *outfile);
#endif
