#include "QAMaker.h"

ClassImp(QAMaker)
QAMaker::QAMaker(char *mydataset, AnalysisMaker *myAnalysisMaker, PhiMaker *myPhiMaker, RawSpectraMaker *myPtMaker){
  dataset = mydataset;
  anaMaker = myAnalysisMaker;
  phiMaker = myPhiMaker;
  ptMaker = myPtMaker;
  writeTIdentified = false;
  writeV0s = false;
  writeXis = false;
  writeTRes = false;
}
Int_t QAMaker::Init(){
  return StMaker::Init();
}
Int_t QAMaker::Make(){
  int centbin = centrality(dataset,anaMaker->RefMult());
  //writing out charged tracks and tracks identified by dEdx
  while(anaMaker->GetNextChargedTrack()){
    if(anaMaker->GetNextTIdentifiedTrack()->InheritsFrom("TIdentifiedTrack")){
      TIdentifiedTrack *tidTrack = anaMaker->GetNextTIdentifiedTrack();
      //  void FillPhiHisto(int partID, float pt, float phi, int centBin);
      phiMaker->FillPhiHisto(0, tidTrack->GetPt(),tidTrack->GetPhi(),centbin);
      ptMaker->FillPhiHisto(0, tidTrack->GetPt(),centbin);
      if(writeTIdentified){
	if(IsGoodProton(dataset,tidTrack)){
	  if(tidTrack->GetCharge()>0){//proton
	    phiMaker->FillPhiHisto(8, tidTrack->GetPt(),tidTrack->GetPhi(),centbin);
	    ptMaker->FillPhiHisto(8, tidTrack->GetPt(),centbin);
	  }
	  else{//antiproton
	    phiMaker->FillPhiHisto(9, tidTrack->GetPt(),tidTrack->GetPhi(),centbin);
	    ptMaker->FillPhiHisto(9, tidTrack->GetPt(),centbin);
	  }
	}
	if(IsGoodPion(dataset,tidTrack)){
	  if(tidTrack->GetCharge()>0){//pi+
	    phiMaker->FillPhiHisto(6, tidTrack->GetPt(),tidTrack->GetPhi(),centbin);
	    ptMaker->FillPhiHisto(6, tidTrack->GetPt(),centbin);
	  }
	  else{//pi-
	    phiMaker->FillPhiHisto(7, tidTrack->GetPt(),tidTrack->GetPhi(),centbin);
	    ptMaker->FillPhiHisto(7, tidTrack->GetPt(),centbin);
	  }
	}
	if(IsGoodKaon(dataset,tidTrack)){
	  if(tidTrack->GetCharge()>0){//K+
	    phiMaker->FillPhiHisto(10, tidTrack->GetPt(),tidTrack->GetPhi(),centbin);
	    ptMaker->FillPhiHisto(10, tidTrack->GetPt(),centbin);
	  }
	  else{//K-
	    phiMaker->FillPhiHisto(11, tidTrack->GetPt(),tidTrack->GetPhi(),centbin);
	    ptMaker->FillPhiHisto(11, tidTrack->GetPt(),centbin);
	  }
	}
	if(IsGoodElectron(dataset,tidTrack)){
	  if(tidTrack->GetCharge()>0){//electron
	    phiMaker->FillPhiHisto(12, tidTrack->GetPt(),tidTrack->GetPhi(),centbin);
	    ptMaker->FillPhiHisto(12, tidTrack->GetPt(),centbin);
	  }
	  else{//electron
	    phiMaker->FillPhiHisto(13, tidTrack->GetPt(),tidTrack->GetPhi(),centbin);
	    ptMaker->FillPhiHisto(13, tidTrack->GetPt(),centbin);
	  }
	}
      }
    }
    else{//if I don't have TIdentifiedTracks to work will I'll fill up the charged hadrons
      TTrack *tTrack = anaMaker->GetNextTTrack();
      phiMaker->FillPhiHisto(0, tTrack->GetPt(),tTrack->GetPhi(),centbin);
      ptMaker->FillPhiHisto(0, tTrack->GetPt(),centbin);
    }
  }
  if(writeV0s){
    while(anaMaker->GetNextV0Track()){
      TV0Track *track = anaMaker->GetNextTV0Track();
      if(track->GetType()==1){//lambda
	phiMaker->FillPhiHisto(1, track->GetPt(),track->GetPhi(),centbin);
	ptMaker->FillPhiHisto(1, track->GetPt(),centbin);
      }
      if(track->GetType()==2){//antilambda
	phiMaker->FillPhiHisto(2, track->GetPt(),track->GetPhi(),centbin);
	ptMaker->FillPhiHisto(2, track->GetPt(),centbin);
      }
      if(track->GetType()==3){//K0s
	phiMaker->FillPhiHisto(3, track->GetPt(),track->GetPhi(),centbin);
	ptMaker->FillPhiHisto(3, track->GetPt(),centbin);
      }
    }
  }
  if(writeXis){
    while(anaMaker->GetNextXiTrack()){
      TXiTrack *track = anaMaker->GetNextTXiTrack();
      if(track->GetType()==4){//Xi
	phiMaker->FillPhiHisto(4, track->GetPt(),track->GetPhi(),centbin);
	ptMaker->FillPhiHisto(4, track->GetPt(),centbin);
      }
      if(track->GetType()==18){//AntiXi
	phiMaker->FillPhiHisto(18, track->GetPt(),track->GetPhi(),centbin);
	ptMaker->FillPhiHisto(18, track->GetPt(),centbin);
      }
      if(track->GetType()==5){//Omega
	phiMaker->FillPhiHisto(5, track->GetPt(),track->GetPhi(),centbin);
	ptMaker->FillPhiHisto(5, track->GetPt(),centbin);
      }
      if(track->GetType()==19){//AntiOmega
	phiMaker->FillPhiHisto(19, track->GetPt(),track->GetPhi(),centbin);
	ptMaker->FillPhiHisto(19, track->GetPt(),centbin);
      }
    }
  }
  if(writeTRes){
    while(anaMaker->GetNextResonanceTrack()){
      TResonanceTrack* track = anaMaker->GetNextTResonanceTrack();
      if(track->GetType()==14){
	phiMaker->FillPhiHisto(14, track->GetPt(),track->GetPhi(),centbin);
	ptMaker->FillPhiHisto(14, track->GetPt(),centbin);
      }
      if(track->GetType()==15){
	phiMaker->FillPhiHisto(15, track->GetPt(),track->GetPhi(),centbin);
	ptMaker->FillPhiHisto(15, track->GetPt(),centbin);
      }
      if(track->GetType()==16){
	phiMaker->FillPhiHisto(16, track->GetPt(),track->GetPhi(),centbin);
	ptMaker->FillPhiHisto(16, track->GetPt(),centbin);
      }
      if(track->GetType()==17){
	phiMaker->FillPhiHisto(17, track->GetPt(),track->GetPhi(),centbin);
	ptMaker->FillPhiHisto(17, track->GetPt(),centbin);
      }
    }
  }

  return kStOk;
}
Int_t QAMaker::Finish(){
  return kStOk;
}

