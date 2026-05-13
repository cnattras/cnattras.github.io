// @(#)root/test:$Name:  $:$Id: Event.cxx,v 1.22 2003/08/23 00:08:13 rdm Exp $
// Author: Jana Bielcikova

////////////////////////////////////////////////////////////////////////
//
//                       TXiTrack class
//                       =======================
//
////////////////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;
#include <math.h>
#include <string>
#include "TDirectory.h"
#include "TProcessID.h"

#include "TXiTrack.h"



ClassImp(TXiTrack)

//______________________________________________________________________________
TXiTrack::TXiTrack(const TXiTrack *orig) : TObject()
{
   // Copy a track object

  SetPtDecay(orig->GetPtDecay());
  SetPt(orig->GetPt());
  SetPhi(orig->GetPhi());
  SetMass(orig->GetMass());
  SetMassV0(orig->GetMassV0());
  SetCharge(orig->GetCharge());
  SetType(orig->GetType());
  SetEta(orig->GetEta());
  SetRapidity(orig->GetRapidity());
  SetDecayLengthV0(orig->GetDecayLengthV0());
  SetDecayLengthXi(orig->GetDecayLengthXi());
  SetDcaPosDaughterToPV(orig->GetDcaPosDaughterToPV()); 
  SetDcaNegDaughterToPV(orig->GetDcaNegDaughterToPV()); 
  SetDcaBachDaughterToPV(orig->GetDcaBachDaughterToPV());
  SetDcaV0ToPV(orig->GetDcaV0ToPV()); 
  SetDcaXiToPV(orig->GetDcaXiToPV()); 
  SetDcaV0Daughters(orig->GetDcaV0Daughters()); 
  SetDcaXiDaughters(orig->GetDcaXiDaughters()); 
  SetNHitsPosDaughter(orig->GetNHitsPosDaughter());
  SetNHitsNegDaughter(orig->GetNHitsNegDaughter());
  SetNHitsBachDaughter(orig->GetNHitsBachDaughter());
  SetdEdxPosDaughter(orig->GetdEdxPosDaughter());
  SetdEdxNegDaughter(orig->GetdEdxNegDaughter());
  SetdEdxBachDaughter(orig->GetdEdxBachDaughter());
  SetdEdxErrPosDaughter(orig->GetdEdxErrPosDaughter());
  SetdEdxErrNegDaughter(orig->GetdEdxErrNegDaughter());
  SetdEdxErrBachDaughter(orig->GetdEdxErrBachDaughter());
  SetPosDaughterTrackId(orig->GetPosDaughterTrackId());
  SetNegDaughterTrackId(orig->GetNegDaughterTrackId());
  SetBachDaughterTrackId(orig->GetBachDaughterTrackId());

}








