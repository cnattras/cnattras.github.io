#include "TIdentifiedTrack.h"
ClassImp(TIdentifiedTrack)


TIdentifiedTrack::TIdentifiedTrack(const TIdentifiedTrack *orig) : TTrack(orig) 
{
    SetNSigmaProton(orig->GetNSigmaProton());
    SetNSigmaPion(orig->GetNSigmaPion());
    SetNSigmaKaon(orig->GetNSigmaKaon());
    SetNSigmaElectron(orig->GetNSigmaElectron());
    SetdEdX(orig->GetdEdX());
}
TIdentifiedTrack::TIdentifiedTrack(const TTrack *orig) : TTrack(orig) 
{
  //All other variables copied from the TTrack constructor
  nSigmaProton = 10000;
  nSigmaPion = 10000;
  nSigmaElectron = 10000;
  nSigmaKaon = 10000;
  dEdX = 10000;
}
