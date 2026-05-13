#ifndef _TStMuEventAna_INCLUDED_
#define _TStMuEventAna_INCLUDED_

#include "TObject.h"
#include "TH1.h"
#include "TH2.h"
#include "TObjArray.h"
#include "TClonesArray.h"
#include "TCutG.h"
#include "TString.h"
#include "StMaker.h"

#include "StMuDSTMaker/COMMON/StMuTrack.h"
#include "StMuDSTMaker/COMMON/StMuDstMaker.h"
#include "StMuDSTMaker/COMMON/StMuDst.h"

#include "StMuDSTMaker/COMMON/StMuEvent.h"

//Forward Declarations
class TFile;
class TH1F;
class StEvent;
class StPrimaryVertex;
class TNtuple;
class StTrack;
class StMuTrack;
class StMuEvent;

//class T49Stat;
//class T49Dedx;
//class T49ParticleRoot;
//class StTrack;

class TStMuEventAna : public TObject {
    
  public: 
    TStMuEventAna();
    virtual ~TStMuEventAna();
   
 
    void       CreateHisto(char name[50]);  
    void       CreateHisto1D(char name[50],Float_t xbins,Float_t xlow,Float_t xhigh);
    void       CreateHisto2D(char name[50],Float_t xbins,Float_t xlow,Float_t xhigh,Float_t ybins,Float_t ylow,Float_t yhigh);     
    void       FillEventHisto(StMuEvent *Event);
    void       FillHisto1D(char histname[50], Float_t x);
    void       FillHisto2D(char histname[50], Float_t x, Float_t y);
      
    Float_t   GetVertexX(StMuEvent *Event);
    Float_t   GetVertexY(StMuEvent *Event);
    Float_t   GetVertexZ(StMuEvent *Event);
    Int_t     GetRefMult(StMuEvent *Event);
    Int_t     GetRefMultPos(StMuEvent *Event);
    Int_t     GetRefMultNeg(StMuEvent *Event);
    Int_t     GetNumTracks(StMuEvent *Event);
    UInt_t    GetL0TriggerWord(StMuEvent *Event);
    Double_t  GetReactionPlane(StMuEvent *Event,UShort_t s);
    Double_t  GetReactionPlanePtWgt(StMuEvent *Event,UShort_t s);
   
       

    void       SetMass(Double_t x)           { fmass = x; }
  

    ClassDef(TStMuEventAna,1)  // TLambdaStern top class    
     
  protected:
  
   

    TObjArray *fHistoList;     //! List of histograms
    char       hname[50];      //! name of histograms
    TString   *fhname;         //! histoname  
    TH1D      *fhisto;         //!
    Double_t  fmass;           //! mass of particle
   
  
    
}; 

#endif

