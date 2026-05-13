#include "CutMaker.h"

ClassImp(CutMaker)
CutMaker::CutMaker(char *mydataset, AnalysisMaker *myAnalysisMaker){
  dataset = mydataset;
  anaMaker = myAnalysisMaker;
  v0CutMaker = NULL;
  writeTIdentified = false;
  writeV0s = false;
  writeXis = false;
  writeTRes = false;
}
CutMaker::CutMaker(char *mydataset, AnalysisMaker *myAnalysisMaker, StV0GeometricCuts *myV0CutMaker){
  dataset = mydataset;
  anaMaker = myAnalysisMaker;
  xiCutMaker = NULL;
  writeTIdentified = false;
  writeV0s = false;
  writeXis = false;
  writeTRes = false;
  v0CutMaker = myV0CutMaker;
  int high = 10000;//for upper limits
  int low = 0;//for lower limits
  for(int i=0;i<7;i++){
    DcaV0ToPV[i] = high;
    DcaXiToPV[i] = high;
    DcaNegToPV[i]=low;
    DcaPosToPV[i]=low;
    DcaBachToPV[i]=low;
    DcaV0Daughters[i]=high;
    DcaXiDaughters[i]=high;
    NHitsNeg[i]=low;
    NHitsPos[i]=low;
    NHitsBach[i]=low;
    NSigmaNeg[i]=high;
    NSigmaPos[i]=high;
    NSigmaBach[i]=high;
    V0DecayLength[i]=low;
    XiDecayLength[i]=low;
  }
}
CutMaker::CutMaker(char *mydataset, AnalysisMaker *myAnalysisMaker, StXiGeometricCuts *myXiCutMaker){
  dataset = mydataset;
  anaMaker = myAnalysisMaker;
  v0CutMaker = NULL;
  writeTIdentified = false;
  writeV0s = false;
  writeXis = false;
  writeTRes = false;
  //v0CutMaker = myV0CutMaker;
  int high = 10000;//for upper limits
  int low = 0;//for lower limits
  for(int i=0;i<7;i++){
    DcaV0ToPV[i] = high;
    DcaXiToPV[i] = high;
    DcaNegToPV[i]=low;
    DcaPosToPV[i]=low;
    DcaBachToPV[i]=low;
    DcaV0Daughters[i]=high;
    DcaXiDaughters[i]=high;
    NHitsNeg[i]=low;
    NHitsPos[i]=low;
    NHitsBach[i]=low;
    NSigmaNeg[i]=high;
    NSigmaPos[i]=high;
    NSigmaBach[i]=high;
    V0DecayLength[i]=low;
    XiDecayLength[i]=low;
  }
}
CutMaker::CutMaker(char *mydataset, AnalysisMaker *myAnalysisMaker, StV0GeometricCuts *myV0CutMaker, StXiGeometricCuts *myXiCutMaker){
  dataset = mydataset;
  anaMaker = myAnalysisMaker;
  v0CutMaker = NULL;
  writeTIdentified = false;
  writeV0s = false;
  writeXis = false;
  writeTRes = false;
  v0CutMaker = myV0CutMaker;
  xiCutMaker = myXiCutMaker;
  int high = 10000;//for upper limits
  int low = 0;//for lower limits
  for(int i=0;i<7;i++){
    DcaV0ToPV[i] = high;
    DcaXiToPV[i] = high;
    DcaNegToPV[i]=low;
    DcaPosToPV[i]=low;
    DcaBachToPV[i]=low;
    DcaV0Daughters[i]=high;
    DcaXiDaughters[i]=high;
    NHitsNeg[i]=low;
    NHitsPos[i]=low;
    NHitsBach[i]=low;
    NSigmaNeg[i]=high;
    NSigmaPos[i]=high;
    NSigmaBach[i]=high;
    V0DecayLength[i]=low;
    XiDecayLength[i]=low;
  }
}

Int_t CutMaker::Init(){
  return StMaker::Init();
}
Int_t CutMaker::Make(){
  anaMaker->ResetTrackIterators();
  int centbin = centrality(dataset,anaMaker->RefMult());
//   //writing out charged tracks and tracks identified by dEdx
//   while(anaMaker->GetNextChargedTrack()){
//     if(anaMaker->GetNextTIdentifiedTrack()->InheritsFrom("TIdentifiedTrack")){
//       TIdentifiedTrack *tidTrack = anaMaker->GetNextTIdentifiedTrack();
//       //  void FillPhiHisto(int partID, float pt, float phi, int centBin);
//       //phiMaker->FillPhiHisto(0, tidTrack->GetPt(),tidTrack->GetPhi(),centbin);
//       //ptMaker->FillPhiHisto(0, tidTrack->GetPt(),centbin);
//       if(writeTIdentified){
// 	if(IsGoodProton(dataset,tidTrack)){
// 	  if(tidTrack->GetCharge()>0){//proton
// 	    //phiMaker->FillPhiHisto(8, tidTrack->GetPt(),tidTrack->GetPhi(),centbin);
// 	    //ptMaker->FillPhiHisto(8, tidTrack->GetPt(),centbin);
// 	  }
// 	  else{//antiproton
// 	    //phiMaker->FillPhiHisto(9, tidTrack->GetPt(),tidTrack->GetPhi(),centbin);
// 	    //ptMaker->FillPhiHisto(9, tidTrack->GetPt(),centbin);
// 	  }
// 	}
// 	if(IsGoodPion(dataset,tidTrack)){
// 	  if(tidTrack->GetCharge()>0){//pi+
// 	    //phiMaker->FillPhiHisto(6, tidTrack->GetPt(),tidTrack->GetPhi(),centbin);
// 	    //ptMaker->FillPhiHisto(6, tidTrack->GetPt(),centbin);
// 	  }
// 	  else{//pi-
// 	    //phiMaker->FillPhiHisto(7, tidTrack->GetPt(),tidTrack->GetPhi(),centbin);
// 	    //ptMaker->FillPhiHisto(7, tidTrack->GetPt(),centbin);
// 	  }
// 	}
// 	if(IsGoodKaon(dataset,tidTrack)){
// 	  if(tidTrack->GetCharge()>0){//K+
// 	    //phiMaker->FillPhiHisto(10, tidTrack->GetPt(),tidTrack->GetPhi(),centbin);
// 	    //ptMaker->FillPhiHisto(10, tidTrack->GetPt(),centbin);
// 	  }
// 	  else{//K-
// 	    //phiMaker->FillPhiHisto(11, tidTrack->GetPt(),tidTrack->GetPhi(),centbin);
// 	    //ptMaker->FillPhiHisto(11, tidTrack->GetPt(),centbin);
// 	  }
// 	}
// 	if(IsGoodElectron(dataset,tidTrack)){
// 	  if(tidTrack->GetCharge()>0){//electron
// 	    //phiMaker->FillPhiHisto(12, tidTrack->GetPt(),tidTrack->GetPhi(),centbin);
// 	    //ptMaker->FillPhiHisto(12, tidTrack->GetPt(),centbin);
// 	  }
// 	  else{//electron
// 	    //phiMaker->FillPhiHisto(13, tidTrack->GetPt(),tidTrack->GetPhi(),centbin);
// 	    //ptMaker->FillPhiHisto(13, tidTrack->GetPt(),centbin);
// 	  }
// 	}
//       }
//     }
//     else{//if I don't have TIdentifiedTracks to work will I'll fill up the charged hadrons
//       TTrack *tTrack = anaMaker->GetNextTTrack();
//       //phiMaker->FillPhiHisto(0, tTrack->GetPt(),tTrack->GetPhi(),centbin);
//       //ptMaker->FillPhiHisto(0, tTrack->GetPt(),centbin);
//     }
//   }
  anaMaker->ResetTrackIterators();
  if(writeV0s && v0CutMaker){
    while(anaMaker->GetNextV0Track()){
      TV0Track *track = anaMaker->GetNextTV0Track();
      int cut = GetCutNum(track->GetType());
      float ptmin = 0;
      float ptmax = 10.;
      float eta = 1.0;
      //cout<<"partID "<<track->GetType()<<" cut num "<<cut<<endl;
      if(cut!=-1){
	//cerr<<" cutmaker 173 ";
	if( IsGoodV0Track(dataset, track, V0DecayLength[cut], DcaV0ToPV[cut], DcaV0Daughters[cut],DcaNegToPV[cut],DcaPosToPV[cut],NHitsPos[cut],NHitsNeg[cut],ptmin,ptmax,eta) ){
	  if( fabs(track->GetdEdxNegDaughter()) < NSigmaNeg[cut]  &&  fabs(track->GetdEdxPosDaughter()) < NSigmaPos[cut] ){
	    
	    if( track->GetdEdxNegDaughter() < NSigmaNeg[cut] &&  track->GetdEdxPosDaughter() < NSigmaPos[cut] ){
	      v0CutMaker->FillCutHistos(track->GetType(),track->GetPt(),track->GetMass(),track->GetDcaV0ToPV(),track->GetDcaNegDaughterToPV(),track->GetDcaPosDaughterToPV(),fabs(track->GetDcaDaughters()),track->GetNHitsNegDaughter(),track->GetNHitsPosDaughter(),track->GetdEdxNegDaughter(),track->GetdEdxPosDaughter(),track->GetDecayLength());
	    }
	  }
	}
      }
      //cout<<"v0 vals"<<" "<<track->GetMass()<<" "<<track->GetDcaV0ToPV()<<" "<<track->GetDcaNegDaughterToPV()<<" "<<track->GetDcaPosDaughterToPV()<<" "<<track->GetDcaDaughters()<<" "<<track->GetNHitsNegDaughter()<<" "<<track->GetNHitsPosDaughter()<<" "<<track->GetdEdxNegDaughter()<<" "<<track->GetdEdxPosDaughter()<<" "<<track->GetDecayLength()<<endl;
    }
  }
  anaMaker->ResetTrackIterators();
  if(writeXis && xiCutMaker){
    //cout<<" 185 ";
    while(anaMaker->GetNextXiTrack()){
      TXiTrack *track = anaMaker->GetNextTXiTrack();
      //cout<<" hi"<<endl;
      int cut = GetCutNum(track->GetType());
      //cout<<"part ID "<<track->GetType()<<" cut "<<cut<<endl;
      float ptmin = 0;
      float ptmax = 10.;
      float eta = 1.0;
      if(cut!=-1){
	//cout<<" 193 ";
	if( IsGoodXiTrack(dataset, track,track->GetType(), XiDecayLength[cut], V0DecayLength[cut], DcaXiToPV[cut], DcaV0ToPV[cut], DcaXiDaughters[cut], DcaV0Daughters[cut],DcaNegToPV[cut],DcaPosToPV[cut],DcaBachToPV[cut],NHitsPos[cut],NHitsNeg[cut],NHitsBach[cut],ptmin,ptmax,eta) ){
	  
	  if( fabs(track->GetdEdxNegDaughter()) < NSigmaNeg[cut] && fabs(track->GetdEdxBachDaughter()) < NSigmaBach[cut] &&  fabs(track->GetdEdxPosDaughter()) < NSigmaPos[cut] ){
	    if( fabs(track->GetdEdxNegDaughter()) >  NSigmaNeg[cut]) cerr<<"ah!"<<endl;
	    if( fabs(track->GetdEdxPosDaughter()) >  NSigmaPos[cut]) cerr<<"ah!"<<endl;
	    if( fabs(track->GetdEdxBachDaughter()) >  NSigmaBach[cut]) cerr<<"ah!"<<endl;
	    xiCutMaker->FillCutHistos(track->GetType(),track->GetPt(),track->GetMass(),track->GetMassV0(),fabs(track->GetDcaXiToPV()),fabs(track->GetDcaV0ToPV()),fabs(track->GetDcaNegDaughterToPV()),fabs(track->GetDcaPosDaughterToPV()),fabs(track->GetDcaBachDaughterToPV()),fabs(track->GetDcaXiDaughters()),fabs(track->GetDcaV0Daughters()),track->GetNHitsNegDaughter(),track->GetNHitsPosDaughter(),track->GetNHitsBachDaughter(),fabs(track->GetdEdxNegDaughter()),fabs(track->GetdEdxPosDaughter()),fabs(track->GetdEdxBachDaughter()),fabs(track->GetDecayLengthV0()),fabs(track->GetDecayLengthXi()));
	  }
	}

      }
    }
  }
//   if(writeTRes){
//     while(anaMaker->GetNextResonanceTrack()){
//       TResonanceTrack* track = anaMaker->GetNextTResonanceTrack();
//       if(track->GetType()==14){
// 	//phiMaker->FillPhiHisto(14, track->GetPt(),track->GetPhi(),centbin);
// 	//ptMaker->FillPhiHisto(14, track->GetPt(),centbin);
//       }
//       if(track->GetType()==15){
// 	//phiMaker->FillPhiHisto(15, track->GetPt(),track->GetPhi(),centbin);
// 	//ptMaker->FillPhiHisto(15, track->GetPt(),centbin);
//       }
//       if(track->GetType()==16){
// 	//phiMaker->FillPhiHisto(16, track->GetPt(),track->GetPhi(),centbin);
// 	//ptMaker->FillPhiHisto(16, track->GetPt(),centbin);
//       }
//       if(track->GetType()==17){
// 	//phiMaker->FillPhiHisto(17, track->GetPt(),track->GetPhi(),centbin);
// 	//ptMaker->FillPhiHisto(17, track->GetPt(),centbin);
//       }
//     }
//   }

  return kStOk;
}
Int_t CutMaker::Finish(){
  return kStOk;
}
int CutMaker::GetCutNum(int partID){
  switch(partID){
  case 1:
    return 0;
  case 2:
    return 1;
  case 3:
    return 2;
  case 4:
    return 3;//Xi
  case 5:
    return 5;//Omega
  case 18:
    return 4;//antiXi
  case 19:
    return 6;//anti-Omega
  default:
    return -1;
  }
  return -1;
}


int CutMaker::GetArrayIndex(int partID){
  switch(partID){
  case 1:
    return 0;
  case 2:
    return 1;
  case 3:
    return 2;
  case 4:
    return 3;
  case 5:
    return 5;
  case 18:
    return 4;
  case 19:
    return 6;
  default:
    return -1;
  }
  return -1;
}
void CutMaker::SetDcaXiToPV(int partID, float cut){
  if( GetArrayIndex(partID) ==-1 ) {
    cerr<<"Error: "<<partID<<" not a valid particle id!"<<endl;
    return;
  }
  cout<<"Setting Dca "<<GetSimpleParticleName(partID)<<" to PV to "<<cut<<endl;
  DcaXiToPV[ GetArrayIndex(partID) ] = cut;
}
void CutMaker::SetDcaV0ToPV(int partID, float cut){
  if( GetArrayIndex(partID) ==-1 ) {
    cerr<<"Error: "<<partID<<" not a valid particle id!"<<endl;
    return;
  }
  cout<<"Setting Dca of V0 of "<<GetSimpleParticleName(partID)<<" to PV to "<<cut<<endl;
  DcaV0ToPV[ GetArrayIndex(partID) ] = cut;
}
void CutMaker::SetDcaNegToPV(int partID, float cut){
  if( GetArrayIndex(partID) ==-1 ) {
    cerr<<"Error: "<<partID<<" not a valid particle id!"<<endl;
    return;
  }
  cout<<"Setting Dca of Neg of "<<GetSimpleParticleName(partID)<<" to PV to "<<cut<<endl;
  DcaNegToPV[ GetArrayIndex(partID) ] = cut;
}
void CutMaker::SetDcaPosToPV(int partID, float cut){
  if( GetArrayIndex(partID) ==-1 ) {
    cerr<<"Error: "<<partID<<" not a valid particle id!"<<endl;
    return;
  }
  cout<<"Setting Dca of Pos of "<<GetSimpleParticleName(partID)<<" to PV to "<<cut<<endl;
  DcaPosToPV[ GetArrayIndex(partID) ] = cut;
}
void CutMaker::SetDcaBachToPV(int partID, float cut){
  if( GetArrayIndex(partID) ==-1 ) {
    cerr<<"Error: "<<partID<<" not a valid particle id!"<<endl;
    return;
  }
  cout<<"Setting Dca of bach of "<<GetSimpleParticleName(partID)<<" to PV to "<<cut<<endl;
  DcaBachToPV[ GetArrayIndex(partID) ] = cut;
}
void CutMaker::SetDcaV0Daughters(int partID, float cut){
  if( GetArrayIndex(partID) ==-1 ) {
    cerr<<"Error: "<<partID<<" not a valid particle id!"<<endl;
    return;
  }
  cout<<"Setting Dca of V0 daughters of "<<GetSimpleParticleName(partID)<<" to "<<cut<<endl;
  DcaV0Daughters[ GetArrayIndex(partID) ] = cut;
}
void CutMaker::SetDcaXiDaughters(int partID, float cut){
  if( GetArrayIndex(partID) ==-1 ) {
    cerr<<"Error: "<<partID<<" not a valid particle id!"<<endl;
    return;
  }
  cout<<"Setting Dca of Xi daughters of "<<GetSimpleParticleName(partID)<<" to "<<cut<<endl;
  DcaXiDaughters[ GetArrayIndex(partID) ] = cut;
}
void CutMaker::SetNHitsNeg(int partID, float cut){
  if( GetArrayIndex(partID) ==-1 ) {
    cerr<<"Error: "<<partID<<" not a valid particle id!"<<endl;
    return;
  }
  cout<<"Setting NHits Neg "<<GetSimpleParticleName(partID)<<" to "<<cut<<endl;
  NHitsNeg[ GetArrayIndex(partID) ] = cut;
}
void CutMaker::SetNHitsPos(int partID, float cut){
  if( GetArrayIndex(partID) ==-1 ) {
    cerr<<"Error: "<<partID<<" not a valid particle id!"<<endl;
    return;
  }
  cout<<"Setting NHits Pos "<<GetSimpleParticleName(partID)<<" to "<<cut<<endl;
  NHitsPos[ GetArrayIndex(partID) ] = cut;
}
void CutMaker::SetNHitsBach(int partID, float cut){
  if( GetArrayIndex(partID) ==-1 ) {
    cerr<<"Error: "<<partID<<" not a valid particle id!"<<endl;
    return;
  }
  cout<<"Setting NHits Bach "<<GetSimpleParticleName(partID)<<" to "<<cut<<endl;
  NHitsBach[ GetArrayIndex(partID) ] = cut;
}
void CutMaker::SetNSigmaNeg(int partID, float cut){
  if( GetArrayIndex(partID) ==-1 ) {
    cerr<<"Error: "<<partID<<" not a valid particle id!"<<endl;
    return;
  }
  cout<<"Setting NSigma Neg "<<GetSimpleParticleName(partID)<<" to "<<cut<<endl;
  NSigmaNeg[ GetArrayIndex(partID) ] = cut;
}
void CutMaker::SetNSigmaPos(int partID, float cut){
  if( GetArrayIndex(partID) ==-1 ) {
    cerr<<"Error: "<<partID<<" not a valid particle id!"<<endl;
    return;
  }
  cout<<"Setting NSigma Pos "<<GetSimpleParticleName(partID)<<" to "<<cut<<endl;
  NSigmaPos[ GetArrayIndex(partID) ] = cut;
}
void CutMaker::SetNSigmaBach(int partID, float cut){
  if( GetArrayIndex(partID) ==-1 ) {
    cerr<<"Error: "<<partID<<" not a valid particle id!"<<endl;
    return;
  }
  cout<<"Setting NSigma Bach "<<GetSimpleParticleName(partID)<<" to "<<cut<<endl;
  NSigmaBach[ GetArrayIndex(partID) ] = cut;
}
void CutMaker::SetV0DecayLength(int partID, float cut){
  if( GetArrayIndex(partID) ==-1 ) {
    cerr<<"Error: "<<partID<<" not a valid particle id!"<<endl;
    return;
  }
  cout<<"Setting V0 Decay Length of "<<GetSimpleParticleName(partID)<<" to "<<cut<<endl;
  V0DecayLength[ GetArrayIndex(partID) ] = cut;
}
void CutMaker::SetXiDecayLength(int partID, float cut){
  if( GetArrayIndex(partID) ==-1 ) {
    cerr<<"Error: "<<partID<<" not a valid particle id!"<<endl;
    return;
  }
  cout<<"Setting Xi Decay Length of "<<GetSimpleParticleName(partID)<<" to "<<cut<<endl;
  XiDecayLength[ GetArrayIndex(partID) ] = cut;
}
