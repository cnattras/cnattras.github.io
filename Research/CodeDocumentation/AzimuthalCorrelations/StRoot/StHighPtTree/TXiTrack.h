#ifndef TXiTrack_h
#define TXiTrack_h
//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TXiTrack                                                             //
//                                                                      //
// Description of the event           parameters                        //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "TObject.h"
#include "TClonesArray.h"
#include "TRefArray.h"
#include "TRef.h"
#include "TMath.h"


class TXiTrack : public TObject {

private:
   Float_t      fPt;           // transverse momentum at primary vertex
   Float_t      fPtDecay;           // transverse momentum at decay vertex
   Float_t      fMass;        // The mass of this particle
   Float_t      fMassV0;        // The mass of the V0
   Int_t      fCharge;
   Float_t      fPhi;         // azimuthal angle
   Int_t        fType;         //Particle type: 0 charged particle, 1 lambda, 2 antilambda, 3 K0s
   Float_t      fPseudoRapidity;
   Float_t      fRapidity;
   Float_t      fDecayLengthXi;
   Float_t      fDecayLengthV0;
   Float_t      fDcaPosDaughterToPV;
   Float_t      fDcaNegDaughterToPV;
   Float_t      fDcaBachDaughterToPV;
   Float_t      fDcaV0ToPV;
   Float_t      fDcaXiToPV;
   Float_t      fDcaV0Daughters;
   Float_t      fDcaXiDaughters;
   Int_t        fNHitsPosDaughter;
   Int_t        fNHitsNegDaughter;
   Int_t        fNHitsBachDaughter;
   Float_t      fdEdxPosDaughter;
   Float_t      fdEdxNegDaughter;
   Float_t      fdEdxBachDaughter;
   Float_t      fdEdxErrPosDaughter;
   Float_t      fdEdxErrNegDaughter;
   Float_t      fdEdxErrBachDaughter;
   Int_t        fPosDaughterTrackId;
   Int_t        fNegDaughterTrackId;
   Int_t        fBachDaughterTrackId;

   
public:
   TXiTrack() { }
   TXiTrack(const TXiTrack* orig);
   virtual ~TXiTrack() {Clear();}
   void     Clear(Option_t *option="") { }
   Float_t  GetPt() const { return fPt; }
   Float_t  GetPtDecay() const { return fPtDecay; }
   Float_t  GetPhi() const { return fPhi; }
   Float_t  GetMass() const { return fMass; }
   Float_t  GetMassV0() const { return fMassV0; }
   Int_t    GetCharge() const { return fCharge; }
   Int_t    GetType() const { return fType;}
   Float_t  GetRapidity() const { return fRapidity;}
   Float_t  GetEta() const { return fPseudoRapidity;}
   Float_t  GetDecayLengthXi() const { return fDecayLengthXi;}
   Float_t  GetDecayLengthV0() const { return fDecayLengthV0;}
   Float_t  GetDcaPosDaughterToPV() const   {  return fDcaPosDaughterToPV;}
   Float_t  GetDcaNegDaughterToPV() const    {  return fDcaNegDaughterToPV;}
   Float_t  GetDcaBachDaughterToPV() const    {  return fDcaBachDaughterToPV;}
   Float_t  GetDcaV0ToPV() const   { return fDcaV0ToPV;}
   Float_t  GetDcaXiToPV() const   { return fDcaXiToPV;}
   Float_t  GetDcaV0Daughters() const   { return fDcaV0Daughters;}
   Float_t  GetDcaXiDaughters() const   { return fDcaXiDaughters;}
   Int_t    GetNHitsPosDaughter()  const { return fNHitsPosDaughter;}
   Int_t    GetNHitsNegDaughter()  const {  return fNHitsNegDaughter;}
   Int_t    GetNHitsBachDaughter()  const {  return fNHitsBachDaughter;}
   Float_t  GetdEdxPosDaughter() const  { return fdEdxPosDaughter;}
   Float_t  GetdEdxNegDaughter() const  { return fdEdxNegDaughter;}
   Float_t  GetdEdxBachDaughter() const  { return fdEdxBachDaughter;}
   Float_t  GetdEdxErrPosDaughter() const  { return fdEdxErrPosDaughter;}
   Float_t  GetdEdxErrNegDaughter() const  { return fdEdxErrNegDaughter;}
   Float_t  GetdEdxErrBachDaughter() const  { return fdEdxErrBachDaughter;}
   Int_t    GetPosDaughterTrackId() const { return  fPosDaughterTrackId;}
   Int_t    GetNegDaughterTrackId() const { return  fNegDaughterTrackId;}
   Int_t    GetBachDaughterTrackId() const { return  fBachDaughterTrackId;}

   void    SetPt(Float_t x)     { fPt = x;       }
   void    SetPtDecay(Float_t x)     { fPtDecay = x;       }
   void    SetPhi(Float_t x)    { fPhi = x;      }
   void    SetMass(Float_t x)   { fMass = x; }
   void    SetMassV0(Float_t x)   { fMassV0 = x; }
   void    SetCharge(Int_t x)   { fCharge = x;   }
   void    SetType(Int_t x) { fType = x;}
   void    SetEta(Float_t x) {fPseudoRapidity = x;}
   void    SetRapidity(Float_t x) {fRapidity = x;}
   void    SetDecayLengthV0(Float_t x) { fDecayLengthV0=x;}
   void    SetDecayLengthXi(Float_t x) { fDecayLengthXi=x;}
   void    SetDcaPosDaughterToPV(Float_t x)  {fDcaPosDaughterToPV = x;}
   void    SetDcaNegDaughterToPV(Float_t x)   {fDcaNegDaughterToPV = x;}
   void    SetDcaBachDaughterToPV(Float_t x)   {fDcaBachDaughterToPV = x;}
   void    SetDcaV0ToPV(Float_t x)  {fDcaV0ToPV = x;}
   void    SetDcaXiToPV(Float_t x)  {fDcaXiToPV = x;}
   void    SetDcaV0Daughters(Float_t x)  {fDcaV0Daughters = x;}
   void    SetDcaXiDaughters(Float_t x)  {fDcaXiDaughters = x;}
   void    SetNHitsPosDaughter(Int_t x) {fNHitsPosDaughter = x;}
   void    SetNHitsNegDaughter(Int_t x) {fNHitsNegDaughter = x;}
   void    SetNHitsBachDaughter(Int_t x) {fNHitsBachDaughter = x;}
   void    SetdEdxPosDaughter(Float_t x) {fdEdxPosDaughter = x;}
   void    SetdEdxNegDaughter(Float_t x) {fdEdxNegDaughter = x;}
   void    SetdEdxBachDaughter(Float_t x) {fdEdxBachDaughter = x;}
   void    SetdEdxErrPosDaughter(Float_t x) {fdEdxErrPosDaughter = x;}
   void    SetdEdxErrNegDaughter(Float_t x) {fdEdxErrNegDaughter = x;}
   void    SetdEdxErrBachDaughter(Float_t x) {fdEdxErrBachDaughter = x;}
   void    SetPosDaughterTrackId(Int_t x) {fPosDaughterTrackId = x;}
   void    SetNegDaughterTrackId(Int_t x) {fNegDaughterTrackId = x;}
   void    SetBachDaughterTrackId(Int_t x) {fBachDaughterTrackId = x;}

   

   ClassDef(TXiTrack,1)  //Event structure
};
#endif

