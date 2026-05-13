/// new  14. aug.  2001

#include <math.h>
#include "stdlib.h"
#include "TStMuEventAna.h"


// StRoot
#include "StChain.h"
#include "St_DataSet.h"
#include "St_DataSetIter.h"
#include "StMessMgr.h"

// StEvent
#include "StEvent.h"
#include "StPrimaryVertex.h"
#include "StPrimaryTrack.h"
#include "StDedxPidTraits.h"
#include "StTrackFitTraits.h"
#include "StTrackDetectorInfo.h"
#include "StTrackGeometry.h"
#include "StTpcDedxPidAlgorithm.h"
#include "StTriggerDetectorCollection.h"
#include "StCtbTriggerDetector.h"
#include "StZdcTriggerDetector.h"
//#include "StEventTypes.h"
#include "StMemoryInfo.hh"

#include "StMaker.h"

#include "StMuDSTMaker/COMMON/StMuTrack.h"
#include "StMuDSTMaker/COMMON/StMuDstMaker.h"
#include "StMuDSTMaker/COMMON/StMuDst.h"
//#include "AnaMaker/TStMuCutEvent.h"

//#include "PhysConst.h"

//*-*-* ROOT includes

#include "TROOT.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TH2.h"
#include "TNtuple.h"
#include "TBranch.h"
#include "TObjArray.h"
#include "TObject.h"
#include "TString.h"

ClassImp(TStMuEventAna)


TStMuEventAna::TStMuEventAna()
{  
     
    fHistoList    = new TObjArray();  
    fhname        = new TString();
    fmass         = 0.1395700;
}
  

TStMuEventAna::~TStMuEventAna()
{

}    




void TStMuEventAna::CreateHisto(char name[50])
{     
  

    fhname->Append(name);
    printf("histoname %s \n ",fhname->Data());
  
  
    CreateHisto1D("Mult_",2000,0,2000);
    CreateHisto1D("RefMult_",200,0,2000);
    //    CreateHisto1D("RefMultPos_",100,0,1000);
    // CreateHisto1D("RefMultNeg_",100,0,1000);


    CreateHisto1D("VertexX_",100,-10,10);
    CreateHisto1D("VertexY_",100,-10,10);
    CreateHisto1D("VertexZ_",100,-150,150);   

}
 

void TStMuEventAna::FillEventHisto(StMuEvent *Event)
{
  
    FillHisto1D("Mult_",GetNumTracks(Event));   
    FillHisto1D("RefMult_",GetRefMult(Event));
    // FillHisto1D("RefMultPos_",GetRefMultPos(Event));
    // FillHisto1D("RefMultNeg_",GetRefMultNeg(Event));


    FillHisto1D("VertexX_",GetVertexX(Event));
    FillHisto1D("VertexY_",GetVertexY(Event));
    FillHisto1D("VertexZ_",GetVertexZ(Event));

        
   
}

void TStMuEventAna::CreateHisto1D(char name[50], Float_t xbins, Float_t xlow,Float_t xhigh)
{     
   TString *hname   = new TString();

    hname->Append(name);
    hname->Append(fhname->Data());  
    printf("%s \n ",hname->Data());
    TH1D *histo = new TH1D(hname->Data(),hname->Data(),xbins,xlow,xhigh);
    fHistoList->Add(histo);
    delete hname;
    
}

void TStMuEventAna::CreateHisto2D(char name[50],Float_t xbins,Float_t xlow,Float_t xhigh,Float_t ybins,Float_t ylow,Float_t yhigh)
{     
   TString *hname   = new TString();

    hname->Append(name);
    hname->Append(fhname->Data());  
    printf("%s \n ",hname->Data());
    TH2D *histo = new TH2D(hname->Data(),hname->Data(),xbins,xlow,xhigh,ybins,ylow,yhigh);
    fHistoList->Add(histo);

    delete hname;
   
}



void TStMuEventAna::FillHisto1D(char histname[50], Float_t x)
{
   TH1D     *histo; 
   TString  *name   = new TString();
  
   name->Append(histname);
   name->Append(fhname->Data());          
   histo = (TH1D *)fHistoList->FindObject(name->Data()); 
   histo->Fill((Double_t)x);
   delete name;
  
}


void TStMuEventAna::FillHisto2D(char histname[50], Float_t x, Float_t y)
{
   TH2D     *histo; 
   TString  *name   = new TString();
  
   name->Append(histname);
   name->Append(fhname->Data());          
   histo = (TH2D *)fHistoList->FindObject(name->Data()); 
   histo->Fill((Double_t)x,(Double_t)y);

   delete name;
  
 
}





Int_t  TStMuEventAna::GetNumTracks(StMuEvent *Event)
{
  StEventSummary &eventsum = Event->eventSummary();
    return eventsum.numberOfTracks();
}

Int_t  TStMuEventAna::GetRefMult(StMuEvent *Event)
{
    return Event->refMult();
}


Int_t  TStMuEventAna::GetRefMultPos(StMuEvent *Event)
{
    return Event->refMultPos();
}

Int_t  TStMuEventAna::GetRefMultNeg(StMuEvent *Event)
{
    return Event->refMultNeg();
}




Float_t  TStMuEventAna::GetVertexZ(StMuEvent *Event)
{
   StEventSummary &eventsum = Event->eventSummary();
   return (eventsum.primaryVertexPosition()).z() ;   
}


Float_t  TStMuEventAna::GetVertexY(StMuEvent *Event)
{
   StEventSummary &eventsum = Event->eventSummary();
   return (eventsum.primaryVertexPosition()).y() ;  
}

Float_t  TStMuEventAna::GetVertexX(StMuEvent *Event)
{
   StEventSummary &eventsum = Event->eventSummary();
   return (eventsum.primaryVertexPosition()).x() ;    
}


UInt_t TStMuEventAna::GetL0TriggerWord(StMuEvent *Event)
{ 
  StL0Trigger& l0Trigger  = Event->l0Trigger();
    return l0Trigger.triggerWord();
}


Double_t  TStMuEventAna::GetReactionPlane(StMuEvent *Event, UShort_t s)
{
  return Event->reactionPlane(s);
}


Double_t  TStMuEventAna::GetReactionPlanePtWgt(StMuEvent *Event, UShort_t s)
{
  return Event->reactionPlanePtWgt(s); 
}

