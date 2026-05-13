
#ifndef IsGoodTrack_h
#define IsGoodTrack_h
#ifndef __CINT__
#  include <string> 
#  include "Riostream.h"//needed to use things like cout, which I will use primarily for debugging
#endif
#include "StMuDSTMaker/COMMON/StMuTrack.h"
#include "../StHighPtTree/TTrack.h"
#include "../StHighPtTree/TIdentifiedTrack.h"

bool IsGoodTrack(const string dataset, StMuTrack *track, float ptmin, float ptmax, float eta , float dca , int nHitsFit);
bool IsGoodTrack(const char* dataset, StMuTrack *track, float ptmin, float ptmax, float eta , float dca, int nHitsFit);
bool IsGoodTrack(const string dataset, TTrack *track, float ptmin, float ptmax, float eta , float dca , int nHitsFit);
bool IsGoodTrack(const char* dataset, TTrack *track, float ptmin, float ptmax, float eta , float dca , int nHitsFit);

//Currently these check whether the TIdentifedTrack is good as a TTrack and then they do a 2 sigma cut on dEdx.  This will have to be adjusted to give a pt dependent cut
bool IsGoodProton(const string dataset, TIdentifiedTrack *track, float ptmin = 0.0, float ptmax = 10.0, float eta = 1.0 , float dca = 1.0 , int nHitsFit = 15);
bool IsGoodProton(const char* dataset, TIdentifiedTrack *track, float ptmin = 0.0, float ptmax = 10.0, float eta = 1.0 , float dca = 1.0 , int nHitsFit = 15);
bool IsGoodPion(const string dataset, TIdentifiedTrack *track, float ptmin = 0.0, float ptmax = 10.0, float eta = 1.0 , float dca = 1.0 , int nHitsFit = 15);
bool IsGoodPion(const char* dataset, TIdentifiedTrack *track, float ptmin = 0.0, float ptmax = 10.0, float eta = 1.0 , float dca = 1.0 , int nHitsFit = 15);
bool IsGoodKaon(const string dataset, TIdentifiedTrack *track, float ptmin = 0.0, float ptmax = 10.0, float eta = 1.0 , float dca = 1.0 , int nHitsFit = 15);
bool IsGoodKaon(const char* dataset, TIdentifiedTrack *track, float ptmin = 0.0, float ptmax = 10.0, float eta = 1.0 , float dca = 1.0 , int nHitsFit = 15);
bool IsGoodElectron(const string dataset, TIdentifiedTrack *track, float ptmin = 0.0, float ptmax = 10.0, float eta = 1.0 , float dca = 1.0 , int nHitsFit = 15);
bool IsGoodElectron(const char* dataset, TIdentifiedTrack *track, float ptmin = 0.0, float ptmax = 10.0, float eta = 1.0 , float dca = 1.0 , int nHitsFit = 15);

#endif
