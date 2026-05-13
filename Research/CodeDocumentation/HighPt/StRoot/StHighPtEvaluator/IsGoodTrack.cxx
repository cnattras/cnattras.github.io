#include "IsGoodTrack.h"
bool IsGoodTrack(const string dataset, StMuTrack *track, float ptmin, float ptmax, float eta = 1.0, float dca = 1.0, int nHitsFit = 15){
  return IsGoodTrack(dataset.c_str(), track, ptmin, ptmax, eta, dca, nHitsFit);
}
bool IsGoodTrack(const char* dataset, StMuTrack *track, float ptmin, float ptmax, float eta = 1.0, float dca = 1.0, int nHitsFit = 15){
  //currently no dependence on data set, may need to be added
  return track && track->flag() >= 0 && track->nHitsFit() >= nHitsFit && track->pt() >= ptmin && track->pt() <= ptmax && fabs(track->eta()) <= eta && track->dcaGlobal().mag()<= dca;
}
bool IsGoodTrack(const string dataset, TTrack *track, float ptmin, float ptmax, float eta = 1.0, float dca = 1.0, int nHitsFit = 15){
  return IsGoodTrack((char*)dataset.c_str(), track, ptmin, ptmax, eta, dca, nHitsFit);
}
bool IsGoodTrack(const char* dataset, TTrack *track, float ptmin, float ptmax, float eta = 1.0, float dca = 1.0, int nHitsFit = 15){
  //currently no dependence on data set, may need to be added
  return track && track->GetNHits() >= nHitsFit && track->GetPt() >= ptmin && track->GetPt() <= ptmax && fabs(track->GetEta()) <= eta;
}




bool IsGoodProton(const string dataset, TIdentifiedTrack *track, float ptmin, float ptmax, float eta , float dca , int nHitsFit){
  return IsGoodProton((char*)dataset.c_str(),track,ptmin,ptmax,eta,dca,nHitsFit);
}
bool IsGoodProton(const char* dataset, TIdentifiedTrack *track, float ptmin, float ptmax, float eta , float dca , int nHitsFit){
  if(!(IsGoodTrack(dataset,(TTrack*) track,ptmin,ptmax,eta,dca,nHitsFit))) return false;
  if(fabs(track->GetNSigmaProton())>2) return false;
  return true;
}
bool IsGoodPion(const string dataset, TIdentifiedTrack *track, float ptmin, float ptmax, float eta , float dca , int nHitsFit){
  return IsGoodPion((char*)dataset.c_str(),track,ptmin,ptmax,eta,dca,nHitsFit);
}
bool IsGoodPion(const char* dataset, TIdentifiedTrack *track, float ptmin, float ptmax, float eta , float dca , int nHitsFit){
  if(!(IsGoodTrack(dataset,(TTrack*) track,ptmin,ptmax,eta,dca,nHitsFit))) return false;
  if(fabs(track->GetNSigmaPion())>2) return false;
  return true;
}
bool IsGoodKaon(const string dataset, TIdentifiedTrack *track, float ptmin, float ptmax, float eta , float dca , int nHitsFit){
  return IsGoodKaon((char*)dataset.c_str(),track,ptmin,ptmax,eta,dca,nHitsFit);
}
bool IsGoodKaon(const char* dataset, TIdentifiedTrack *track, float ptmin, float ptmax, float eta , float dca , int nHitsFit){
  if(!(IsGoodTrack(dataset,(TTrack*) track,ptmin,ptmax,eta,dca,nHitsFit))) return false;
  if(fabs(track->GetNSigmaKaon())>2) return false;
  return true;
}
bool IsGoodElectron(const string dataset, TIdentifiedTrack *track, float ptmin, float ptmax, float eta , float dca , int nHitsFit){
  return IsGoodElectron((char*)dataset.c_str(),track,ptmin,ptmax,eta,dca,nHitsFit);
}
bool IsGoodElectron(const char* dataset, TIdentifiedTrack *track, float ptmin, float ptmax, float eta , float dca , int nHitsFit){
  if(!(IsGoodTrack(dataset,(TTrack*) track,ptmin,ptmax,eta,dca,nHitsFit))) return false;
  if(fabs(track->GetNSigmaElectron())>2) return false;
  return true;
}
