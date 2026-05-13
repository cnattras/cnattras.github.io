#ifndef TResonanceTrack_h
#define TResonanceTrack_h
#include "TTrack.h"
class TResonanceTrack : public TTrack {
 public:
   TResonanceTrack() { };
   TResonanceTrack(const TResonanceTrack* orig);
   TResonanceTrack(const TTrack* orig, int type);
   //positive track variables are stored in TTrack varibles
   Int_t         GetNHitsPos() const {return GetNHits(); }
   Int_t         GetNPossHitsPos() const {return GetNPossHits(); }
   Float_t       GetdEdxPos() const {return GetdEdx();}
   Int_t         GetTrackIdPos() const {return GetTrackId();}
   void    SetNHitsPos(Int_t x)   { SetNHitsPos(x);   }
   void    SetNPossHitsPos(Int_t x)   { SetNPossHits(x);   }
   void    SetdEdxPos(Float_t x) { SetdEdx(x);}
   void    SetTrackIdPos(Int_t x) {SetTrackId(x);}
   //negative track variables
   Int_t         GetNHitsNeg() const { return fNHitsNeg; }
   Int_t         GetNPossHitsNeg() const { return fNPossHitsNeg; }
   Float_t       GetdEdxNeg() const {return fdEdxNeg;}
   Int_t         GetTrackIdNeg() const {return fTrackIdNeg;}
   void    SetNHitsNeg(Int_t x)   { fNHitsNeg = x;   }
   void    SetNPossHitsNeg(Int_t x)   { fNPossHitsNeg = x;   }
   void    SetdEdxNeg(Float_t x) { fdEdxNeg = x;}
   void    SetTrackIdNeg(Int_t x) {fTrackIdNeg = x;}

   //Parent particle information
   Float_t       GetMass() const { return fMass; }
   void    SetMass(Float_t x)   { fMass = x; }
   Float_t       GetOpeningAngle() const { return openingAngle; }
   void    SetOpeningAngle(Float_t x)   { openingAngle = x; }

 private:
   //negative daughter track information (positive daughter info stored in the same variables minus the "Neg")
   Int_t        fTrackIdNeg;
   Int_t        fNHitsNeg;       //Number of hits on track for this track
   Int_t fNPossHitsNeg;         //Possible number of hits, added on January 19, 2006
   Float_t      fdEdxNeg;        // measured dEdx added on January 19,2006

   //Parent info
   Float_t fMass;
   Float_t openingAngle;

   ClassDef(TResonanceTrack,1)  //A track segment
};
#endif
