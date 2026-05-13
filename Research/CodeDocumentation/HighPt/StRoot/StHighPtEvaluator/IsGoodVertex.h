#ifndef IsGoodVertex_h
#define IsGoodVertex_h
#ifndef __CINT__
#  include <string> 
#  include "Riostream.h"//needed to use things like cout, which I will use primarily for debugging
#endif
#include "../StHighPtTree/TEvent.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"
//#include "StPrimaryVertex.h"
#include <vector>

bool IsGoodVertex(const string dataset, StMuEvent *event);
bool IsGoodVertex(const char *dataset, StMuEvent *event);
bool IsGoodVertex(const string dataset, TEvent *event);
bool IsGoodVertex(const char *dataset, TEvent *event);

bool IsGoodVertex(const string dataset, float zvertex);
bool IsGoodVertex(const char *dataset, float zvertex);
bool IsGoodVertex(const string dataset, float xvertex, float yvertex, float zvertex);
bool IsGoodVertex(const char *dataset, float xvertex, float yvertex, float zvertex);

bool IsGoodVertex(const string dataset, float zvertexcut, StMuEvent *);
bool IsGoodVertex(const char *dataset, float zvertexcut, StMuEvent *);
bool IsGoodVertex(const string dataset, float xvertexcut, float yvertexcut, float zvertexcut, StMuEvent *);
bool IsGoodVertex(const char *dataset, float xvertexcut, float yvertexcut, float zvertexcut, StMuEvent *);

bool IsGoodVertex(const string dataset, float zvertexcut, TEvent *);
bool IsGoodVertex(const char *dataset, float zvertexcut, TEvent *);
bool IsGoodVertex(const string dataset, float xvertexcut, float yvertexcut, float zvertexcut, TEvent *);
bool IsGoodVertex(const char *dataset, float xvertexcut, float yvertexcut, float zvertexcut, TEvent *);

#endif
