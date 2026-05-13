
#ifndef IsGoodV0Mass_h
#define IsGoodV0Mass_h
#ifndef __CINT__
#  include <string> 
#  include "Riostream.h"//needed to use things like cout, which I will use primarily for debugging
#endif
bool IsGoodV0Mass(char *dataset, float pt, float mass, int type);
bool IsGoodV0Mass(string dataset, float pt, float mass, int type);
bool IsGoodXiMass(char *dataset, float pt, float mass, int type);
bool IsGoodXiMass(string dataset, float pt, float mass, int type);
#endif
