#ifndef GetDefaultV0Cut_h
#define GetDefaultV0Cut_h

#ifndef __CINT__
#  include <string> 
#  include "Riostream.h"//needed to use things like cout, which I will use primarily for debugging
#endif

float GetDefaultV0Cut(char *dataset, char *type, char *cut, int partID);
float GetDefaultV0Cut(char *dataset, char *type, string cut, int partID);
float GetDefaultV0Cut(char *dataset, string type, char *cut, int partID);
float GetDefaultV0Cut(char *dataset, string type, string cut, int partID);
float GetDefaultV0Cut(string dataset, char *type, char *cut, int partID);
float GetDefaultV0Cut(string dataset, char *type, string cut, int partID);
float GetDefaultV0Cut(string dataset, string type, char *cut, int partID);
float GetDefaultV0Cut(string dataset, string type, string cut, int partID);

//=====================================   Xi functions   ========================================

float GetDefaultXiCut(char *dataset, char *type, char *cut, int partID);
float GetDefaultXiCut(char *dataset, char *type, string cut, int partID);
float GetDefaultXiCut(char *dataset, string type, char *cut, int partID);
float GetDefaultXiCut(char *dataset, string type, string cut, int partID);
float GetDefaultXiCut(string dataset, char *type, char *cut, int partID);
float GetDefaultXiCut(string dataset, char *type, string cut, int partID);
float GetDefaultXiCut(string dataset, string type, char *cut, int partID);
float GetDefaultXiCut(string dataset, string type, string cut, int partID);

#endif
