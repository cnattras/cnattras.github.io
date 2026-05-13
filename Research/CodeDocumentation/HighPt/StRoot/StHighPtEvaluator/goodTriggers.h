#ifndef goodTriggers_h
#define goodTriggers_h
#ifndef __CINT__
#  include "goodTriggers.h"
#  include <string> 
#  include "Riostream.h"//needed to use things like cout, which I will use primarily for debugging
#endif

int* goodTriggers(const string dataset);
int* goodTriggers(const char *dataset);
#endif
