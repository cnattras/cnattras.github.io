#ifndef centrality_h
#define centrality_h
#ifndef __CINT__
#  include <string> 
#  include "Riostream.h"//needed to use things like cout, which I will use primarily for debugging
#endif
int centrality(const char *dataset, int multiplicity);
int centrality(string dataset, int multiplicity);
int NumberOfCentralityBins(const char *dataset);
char* GetCentralityLabel(const char *dataset, int centbin);
#endif
