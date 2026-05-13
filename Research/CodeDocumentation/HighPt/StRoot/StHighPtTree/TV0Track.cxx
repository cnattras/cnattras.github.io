// @(#)root/test:$Name:  $:$Id: Event.cxx,v 1.22 2003/08/23 00:08:13 rdm Exp $
// Author: Jana Bielcikova

////////////////////////////////////////////////////////////////////////
//
//                       TV0Track class
//                       =======================
//
////////////////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;
#include <math.h>
#include <string>
#include "TDirectory.h"
#include "TProcessID.h"

#include "TV0Track.h"



ClassImp(TV0Track)

//______________________________________________________________________________
TV0Track::TV0Track(const TV0Track *orig) : TObject()
{
   // Copy a track object

  SetPx(orig->GetPx()); 
  SetPy(orig->GetPy());
  SetPz(orig->GetPz());
  //SetPt(orig->GetPt());
  //SetPhi(orig->GetPhi());
  SetMass(orig->GetMass());
  SetCharge(orig->GetCharge());
  SetType(orig->GetType());
  SetEta(orig->GetEta());
  SetRapidity(orig->GetRapidity());
  SetDecayLength(orig->GetDecayLength());
  SetDcaPosDaughterToPV(orig->GetDcaPosDaughterToPV()); 
  SetDcaNegDaughterToPV(orig->GetDcaNegDaughterToPV());
  SetDcaV0ToPV(orig->GetDcaV0ToPV()); 
  SetDcaDaughters(orig->GetDcaDaughters()); 
  SetNHitsPosDaughter(orig->GetNHitsPosDaughter());
  SetNHitsNegDaughter(orig->GetNHitsNegDaughter());
  SetdEdxPosDaughter(orig->GetdEdxPosDaughter());
  SetdEdxNegDaughter(orig->GetdEdxNegDaughter());
  SetPosDaughterTrackId(orig->GetPosDaughterTrackId());
  SetNegDaughterTrackId(orig->GetNegDaughterTrackId());

  //SetCurvaturePos(orig->GetCurvaturePos()); 
  //SetDipAnglePos(orig->GetDipAnglePos()); 
  //SetPhasePos(orig->GetPhasePos()); 
  SetOrigXPos(orig->GetOrigXPos()); 
  SetOrigYPos(orig->GetOrigYPos()); 
  SetOrigZPos(orig->GetOrigZPos()); 
  //SetHPos(orig->GetHPos()); 
  
  //SetCurvatureNeg(orig->GetCurvatureNeg()); 
  //SetDipAngleNeg(orig->GetDipAngleNeg()); 
  //SetPhaseNeg(orig->GetPhaseNeg()); 
  SetOrigXNeg(orig->GetOrigXNeg()); 
  SetOrigYNeg(orig->GetOrigYNeg()); 
  SetOrigZNeg(orig->GetOrigZNeg()); 
  //SetHNeg(orig->GetHNeg()); 
}








