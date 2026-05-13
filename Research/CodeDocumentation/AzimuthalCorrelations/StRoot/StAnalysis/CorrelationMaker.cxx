#include "CorrelationMaker.h"

ClassImp(CorrelationMaker)
  int CorrelationMaker::totalNumParticles = 24;
int CorrelationMaker::particleClass[24] = {0, 1,1,1, 2,2,2,2, 3,3,3,3,3,3,3,3, 4,4,4,4,4,4,4,4};
int CorrelationMaker::particleIDs[5][8] = {0,-1,-1,-1,-1,-1,-1,-1,
					   1, 2, 3,-1,-1,-1,-1,-1,
					   4, 5,18,19,-1,-1,-1,-1,
					   6, 7, 8, 9,10,11,12,13,
					   14,15,16,17,20,21,22,23};
int CorrelationMaker::numClasses = 5;
int CorrelationMaker::maxNumPartID = 8;
float CorrelationMaker::lowPtAssocCuts[4][2] = {.2,.4,
						.4,.6,
						.6,.8,
						.8,1.0};
float CorrelationMaker::highPtAssocCuts[4][2] = {1.0,1.5,
						 1.5,2.0,
						 2.0,3.0,
						 3.0,10};
float CorrelationMaker::triggerCuts[4][2] = {2.0,3.0,
					     3.0,4.0,
					     4.0,5.0,
					     5.0,10};
float CorrelationMaker::phiDistCuts[7][2] ={2.0,3.0,
					    3.0,4.0,
					    4.0,5.0,
					    5.0,10,
					    1.0,1.5,
					    1.5,2.0,
					    3.0,10};
int CorrelationMaker::numCuts = 4;
int CorrelationMaker::numPhiDistCuts = 7;
int CorrelationMaker::maxNumTriggers = 400;
CorrelationMaker::CorrelationMaker(char *mydataset, AnalysisMaker *myAnaMaker){	       
  dataset = mydataset;
  fileName = "junk.root";
  histoList = new TObjArray();
  for(int i=0;i<numClasses;i++){for(int j=0;j<numClasses;j++) combos[i][j] = false;}
  //by default, always run unidentified-unidentified correlations
  combos[0][0] = true;
  nCentBins = NumberOfCentralityBins(dataset.c_str());
  doLowPtCorr=false;
  anaMaker = myAnaMaker;
  eventnum = 0;
}

Int_t CorrelationMaker::Init(){
  file =  new TFile(fileName, "RECREATE","HistoFile");
  cout << "The output filename is " << fileName << endl;
  BookParticleHistos();
  trigDaughterIds[0] = new int[maxNumTriggers];
  trigDaughterIds[1] = new int[maxNumTriggers];
  trigDaughterIds[2] = new int[maxNumTriggers];
  trigID = new int[maxNumTriggers];
  trigPt = new float[maxNumTriggers];
  trigPhi = new float[maxNumTriggers];
  return StMaker::Init();
}

Int_t CorrelationMaker::Make(){
  //if(anaMaker->GoodEvent()){
    ResetNParticles();
    int centbin = centrality(dataset,anaMaker->RefMult());
    //============================================================================
    //==========================  TRIGGERS  ======================================
    //============================================================================
    anaMaker->ResetTrackIterators();
    triggers = 0;
    //initialize arrays
    for(int i=0;i<maxNumTriggers;i++){
      trigID[i] = -1;
      trigPt[i]=-1;
      trigPhi[i]=-1;
      for(int j=0;j<3;j++){trigDaughterIds[j][i]=-1;}
    }//set all IDs to -1
    //=============  unidentified and dEdx identified  ============================
    while(anaMaker->GetNextChargedTrack()){
      if(anaMaker->GetNextTIdentifiedTrack()){//if there is a TIdentifiedTrack
	//we don't delete this track because it belongs to anaMaker
	TIdentifiedTrack *tidTrack = anaMaker->GetNextTIdentifiedTrack();
	//if(trigBin[0] != -1 && trigBin[1] != -1){
	if(tidTrack->GetPt()>triggerCuts[0][0] && triggers<maxNumTriggers){
	  trigID[triggers] = 0;
	  trigPt[triggers] = tidTrack->GetPt();
	  trigPhi[triggers] = tidTrack->GetPhi();
	  trigDaughterIds[0][triggers] = tidTrack->GetTrackId();
	  //cout<<"trig pt "<<trigPt[triggers]<<" "<<tidTrack->GetPt()<<" phi "<<trigPhi[triggers]<<" trigID "<<trigID[triggers]<<endl;
	  triggers++;
	}

	if(combos[3][0] || combos[3][1] || combos[3][2] || combos[3][3] || combos[3][4]){// if any dEdx identified triggers will be used

	  if(IsGoodProton(dataset,tidTrack)){
	    if(tidTrack->GetCharge()>0){//proton
	      if(tidTrack->GetPt()>triggerCuts[0][0] && triggers<maxNumTriggers){
		trigID[triggers] = 8;
		trigPt[triggers] = tidTrack->GetPt();
		trigPhi[triggers] = tidTrack->GetPhi();
		trigDaughterIds[0][triggers] = tidTrack->GetTrackId();
		triggers++;
	      }
	    }
	    else{//antiproton
	      if(tidTrack->GetPt()>triggerCuts[0][0] && triggers<maxNumTriggers){
		trigID[triggers] = 9;
		trigPt[triggers] = tidTrack->GetPt();
		trigPhi[triggers] = tidTrack->GetPhi();
		trigDaughterIds[0][triggers] = tidTrack->GetTrackId();
		triggers++;
	      }
	    }
	  }
	  if(IsGoodPion(dataset,tidTrack)){
	    if(tidTrack->GetCharge()>0){//pi+
	      if(tidTrack->GetPt()>triggerCuts[0][0] && triggers<maxNumTriggers){
		trigID[triggers] = 6;
		trigPt[triggers] = tidTrack->GetPt();
		trigPhi[triggers] = tidTrack->GetPhi();
		trigDaughterIds[0][triggers] = tidTrack->GetTrackId();
		triggers++;
	      }
	    }
	    else{//pi-
	      if(tidTrack->GetPt()>triggerCuts[0][0] && triggers<maxNumTriggers){
		trigID[triggers] = 7;
		trigPt[triggers] = tidTrack->GetPt();
		trigPhi[triggers] = tidTrack->GetPhi();
		trigDaughterIds[0][triggers] = tidTrack->GetTrackId();
		triggers++;}
	    }
	  }
	  if(IsGoodKaon(dataset,tidTrack)){
	    if(tidTrack->GetCharge()>0){//K+
	      if(tidTrack->GetPt()>triggerCuts[0][0] && triggers<maxNumTriggers){
		trigID[triggers] = 10;
		trigPt[triggers] = tidTrack->GetPt();
		trigPhi[triggers] = tidTrack->GetPhi();
		trigDaughterIds[0][triggers] = tidTrack->GetTrackId();
		triggers++;
	      }
	    }
	    else{//K-
	      if(tidTrack->GetPt()>triggerCuts[0][0] && triggers<maxNumTriggers){
		trigID[triggers] = 11;
		trigPt[triggers] = tidTrack->GetPt();
		trigPhi[triggers] = tidTrack->GetPhi();
		trigDaughterIds[0][triggers] = tidTrack->GetTrackId();
		triggers++;
	      }
	    }
	  }
	  if(IsGoodElectron(dataset,tidTrack)){
	    if(tidTrack->GetCharge()>0){//electron
	      if(tidTrack->GetPt()>triggerCuts[0][0] && triggers<maxNumTriggers){
		trigID[triggers] = 12;
		trigPt[triggers] = tidTrack->GetPt();
		trigPhi[triggers] = tidTrack->GetPhi();
		trigDaughterIds[0][triggers] = tidTrack->GetTrackId();
		triggers++;
	      }
	    }
	    else{//electron
	      if(tidTrack->GetPt()>triggerCuts[0][0] && triggers<maxNumTriggers){
		trigID[triggers] = 13;
		trigPt[triggers] = tidTrack->GetPt();
		trigPhi[triggers] = tidTrack->GetPhi();
		trigDaughterIds[0][triggers] = tidTrack->GetTrackId();
		triggers++;}
	    }
	  }
	}
      }
      else{//if I don't have TIdentifiedTracks to work will I'll fill up the charged hadrons
	TTrack *tTrack = anaMaker->GetNextTTrack();
	if(tTrack->GetPt()>triggerCuts[0][0] && triggers<maxNumTriggers){
	  trigID[triggers] = 0;
	  trigPt[triggers] = tTrack->GetPt();
	  trigPhi[triggers] = tTrack->GetPhi();
	  trigDaughterIds[0][triggers] = tTrack->GetTrackId();
	  triggers++;
	}
      }
    }
    //======================== V0s=========================
    if(combos[1][0] || combos[1][1] || combos[1][2] || combos[1][3] || combos[1][4]){
      //cout<<"begin V0 triggers"<<endl;
      while(anaMaker->GetNextV0Track()){
	TV0Track *track = anaMaker->GetNextTV0Track();
	//cout<<endl<<"event "<<eventnum<<" candidate type "<<track->GetType()<<" pt "<<track->GetPt()<<" mass "<<track->GetMass()<<" "<<track->GetNHitsPosDaughter()<<" "<<track->GetNHitsNegDaughter()<<" "<<track->GetDecayLength()<<" "<<track->GetDcaPosDaughterToPV()<<" "<<track->GetDcaDaughters()<<" "<<track->GetDcaV0ToPV()<<" ";
	//if(track->GetType()==1 && track->GetPt() >2 && track->GetPt()<3){cout<<"lambda"<<endl;}
	if(track->GetPt()>triggerCuts[0][0] && triggers<maxNumTriggers && IsGoodV0Mass(dataset,track->GetPt(),track->GetMass(),track->GetType()) ){
	  //if(track->GetPt()>2 && track->GetPt() <3) cout<<" pass"<<endl;
	  //else{
	  //cout<<" fail"<<endl;
	  //}
	  //if(track->GetPt()>2 && track->GetPt()<3) cout<<"trig "<<track->GetType()<<" pt "<<track->GetPt()<<endl;

	  //if(track->GetPt()>2 && track->GetPt()<3) cout<<"type "<<track->GetType()<<" pt "<<track->GetPt()<<endl;
	  //cout<<"trigger "<<track->GetType()<<" pt "<<track->GetPt()<<endl;
	  trigID[triggers] = track->GetType();
	  trigPt[triggers] = track->GetPt();
	  trigPhi[triggers] = track->GetPhi();
	  trigDaughterIds[0][triggers] = (int) (track->GetPosDaughterTrackId());
	  trigDaughterIds[1][triggers] = (int) (track->GetNegDaughterTrackId());
	  triggers++;
	}
	else{
	  //cout<<" fail "<<endl;
	  //if(!(track->GetPt()>triggerCuts[0][0])) cout<<" trig cut range "<<endl; 
	  //if(!(triggers<maxNumTriggers)) cout<<" max n triggers"<<endl;
	  //if(!(IsGoodV0Mass(dataset,track->GetPt(),track->GetMass(),track->GetType()))) cout<<" bad mass "<<endl;
	}
      }
      //cout<<"end v0 triggers"<<endl;
    }
    //=======================  Xis  =============================
    if(combos[2][0] || combos[2][1] || combos[2][2] || combos[2][3] || combos[2][4]){
      while(anaMaker->GetNextXiTrack()){
	TXiTrack *track = anaMaker->GetNextTXiTrack();
	if(track->GetPt()>triggerCuts[0][0] && triggers<maxNumTriggers &&  IsGoodXiMass(dataset,track->GetPt(),track->GetMass(),track->GetType()) ){
	  //if(track->GetPt()>triggerCuts[0][0] && triggers<maxNumTriggers  ){
	  trigID[triggers] = track->GetType();
	  trigPt[triggers] = track->GetPt();
	  trigPhi[triggers] = track->GetPhi();
	  trigDaughterIds[0][triggers] = (int) (track->GetPosDaughterTrackId());
	  trigDaughterIds[1][triggers] = (int) (track->GetNegDaughterTrackId());
	  trigDaughterIds[2][triggers] = (int) (track->GetBachDaughterTrackId());
	  triggers++;
	}
      }
    }
    //=============================  Resonances  ============================
    if(combos[4][0] || combos[4][1] || combos[4][2] || combos[4][3] || combos[4][4]){
      while(anaMaker->GetNextResonanceTrack()){
	TResonanceTrack* track = anaMaker->GetNextTResonanceTrack();
	if(track->GetPt()>triggerCuts[0][0] && triggers<maxNumTriggers){
	  trigID[triggers] = track->GetType();
	  trigPt[triggers] = track->GetPt();
	  trigPhi[triggers] = track->GetPhi();
	  trigDaughterIds[0][triggers] = (int) (track->GetTrackIdPos());
	  trigDaughterIds[1][triggers] = (int) (track->GetTrackIdNeg());
	  triggers++;
	}
      }
    }
    if(triggers == (maxNumTriggers-1)) cerr<<"Warning: reached maximum number of triggers!!!"<<endl;
    //=================================================================================================
    //==========================  ASSOCIATED  AND PHI DISTRIBUTIONS====================================
    //=================================================================================================
    //cout<<"reading associated particles"<<endl;
    anaMaker->ResetTrackIterators();
    float lowAssocCut = highPtAssocCuts[0][0];
    if(doLowPtCorr) lowAssocCut = lowPtAssocCuts[0][0];
    //=============  unidentified and dEdx identified  ============================
    while(anaMaker->GetNextChargedTrack()){
      if(anaMaker->GetNextTIdentifiedTrack()){//if there is a TIdentifiedTrack
	TIdentifiedTrack *tidTrack = anaMaker->GetNextTIdentifiedTrack();
	if(tidTrack->GetPt()>lowAssocCut){
	  //if(tidTrack->GetPt()>1 && tidTrack->GetPt()<2) cout<<"assoc pt "<<tidTrack->GetPt()<<endl;
	  //cout<<"assoc pt "<<tidTrack->GetPt()<<endl;
	  //if(trig->GetType()==1) cout<<"trig"<<endl;
	  FillPhiHisto(0,tidTrack->GetPt(),tidTrack->GetPhi(),centbin);
	  FillCorrelationHistos(0,tidTrack->GetPt(),tidTrack->GetPhi(),centbin,tidTrack->GetTrackId());
	}

	if(combos[0][3] || combos[1][3] || combos[2][3] || combos[3][3] || combos[4][3]){// if any dEdx identified associated particles will be used

	  if(IsGoodProton(dataset,tidTrack)){
	    if(tidTrack->GetCharge()>0){//proton
	      if(tidTrack->GetPt()>lowAssocCut){
		FillCorrelationHistos(8,tidTrack->GetPt(),tidTrack->GetPhi(),centbin,tidTrack->GetTrackId());
		FillPhiHisto(8,tidTrack->GetPt(),tidTrack->GetPhi(),centbin);
	      }
	    }
	    else{//antiproton
	      if(tidTrack->GetPt()>lowAssocCut){
		FillCorrelationHistos(9,tidTrack->GetPt(),tidTrack->GetPhi(),centbin,tidTrack->GetTrackId());
		FillPhiHisto(9,tidTrack->GetPt(),tidTrack->GetPhi(),centbin);
	      }
	    }
	  }
	  if(IsGoodPion(dataset,tidTrack)){
	    if(tidTrack->GetCharge()>0){//pi+
	      if(tidTrack->GetPt()>lowAssocCut){
		FillCorrelationHistos(6,tidTrack->GetPt(),tidTrack->GetPhi(),centbin,tidTrack->GetTrackId());
		FillPhiHisto(6,tidTrack->GetPt(),tidTrack->GetPhi(),centbin);
	      }
	    }
	    else{//pi-
	      if(tidTrack->GetPt()>lowAssocCut){
		FillPhiHisto(7,tidTrack->GetPt(),tidTrack->GetPhi(),centbin);
		FillCorrelationHistos(7,tidTrack->GetPt(),tidTrack->GetPhi(),centbin,tidTrack->GetTrackId());
	      }
	    }
	  }
	  if(IsGoodKaon(dataset,tidTrack)){
	    if(tidTrack->GetCharge()>0){//K+
	      if(tidTrack->GetPt()>lowAssocCut){
		FillPhiHisto(10,tidTrack->GetPt(),tidTrack->GetPhi(),centbin);
		FillCorrelationHistos(10,tidTrack->GetPt(),tidTrack->GetPhi(),centbin,tidTrack->GetTrackId());
	      }
	    }
	    else{//K-
	      if(tidTrack->GetPt()>lowAssocCut){
		FillPhiHisto(11,tidTrack->GetPt(),tidTrack->GetPhi(),centbin);
		FillCorrelationHistos(11,tidTrack->GetPt(),tidTrack->GetPhi(),centbin,tidTrack->GetTrackId());
	      }
	    }
	  }
	  if(IsGoodElectron(dataset,tidTrack)){
	    if(tidTrack->GetCharge()>0){//electron
	      if(tidTrack->GetPt()>lowAssocCut){
		FillPhiHisto(12,tidTrack->GetPt(),tidTrack->GetPhi(),centbin);
		FillCorrelationHistos(12,tidTrack->GetPt(),tidTrack->GetPhi(),centbin,tidTrack->GetTrackId());
	      }
	    }
	    else{//electron
	      if(tidTrack->GetPt()>lowAssocCut){
		FillPhiHisto(13,tidTrack->GetPt(),tidTrack->GetPhi(),centbin);
		FillCorrelationHistos(13,tidTrack->GetPt(),tidTrack->GetPhi(),centbin,tidTrack->GetTrackId());
	      }
	    }
	  }
	}
      }
      else{//if I don't have TIdentifiedTracks to work will I'll fill up the charged hadrons
	//we don't delete this because it belongs to anaMaker
	TTrack *tTrack = anaMaker->GetNextTTrack();
	if(tTrack->GetPt()>lowAssocCut){
	  FillPhiHisto(0,tTrack->GetPt(),tTrack->GetPhi(),centbin);
	  FillCorrelationHistos(0,tTrack->GetPt(),tTrack->GetPhi(),centbin,tTrack->GetTrackId());
	}
      }
    }
    //======================== V0s=========================
    if(combos[0][1] || combos[1][1] || combos[2][1] || combos[3][1] || combos[4][1]){
    
      while(anaMaker->GetNextV0Track()){
	//we don't delete this because it belongs to anaMaker
	TV0Track *track = anaMaker->GetNextTV0Track();
	if(track->GetPt()>lowAssocCut && IsGoodV0Mass(dataset,track->GetPt(),track->GetMass(),track->GetType()) ){
	  //if(track->GetPt()>2 && track->GetPt()<3) cout<<"type "<<track->GetType()<<" pt "<<track->GetPt()<<endl;
	  //cerr<<"type "<<track->GetType()<<" pt "<<track->GetPt()<<" phi "<< track->GetPhi()<<" centbin "<< centbin;
	  FillCorrelationHistos(track->GetType(),track->GetPt(),track->GetPhi(),centbin,track->GetPosDaughterTrackId(),track->GetNegDaughterTrackId());
	  //FillCorrelationHistos(track->GetType(),track->GetPt(),track->GetPhi(),centbin);
	  FillPhiHisto(track->GetType(),track->GetPt(),track->GetPhi(),centbin);
	}
      }
    } 
    //=======================  Xis  =============================
    if(combos[0][2] || combos[1][2] || combos[2][2] || combos[3][2] || combos[4][2]){
      while(anaMaker->GetNextXiTrack()){
	TXiTrack *track = anaMaker->GetNextTXiTrack();
	if(track->GetPt()>lowAssocCut &&  IsGoodXiMass(dataset,track->GetPt(),track->GetMass(),track->GetType()) ){
	  //if(track->GetPt()>lowAssocCut  ){
	  FillPhiHisto(track->GetType(),track->GetPt(),track->GetPhi(),centbin);
	  FillCorrelationHistos(track->GetType(),track->GetPt(),track->GetPhi(),centbin,track->GetPosDaughterTrackId(),track->GetNegDaughterTrackId(),track->GetBachDaughterTrackId());
	  //FillCorrelationHistos(track->GetType(),track->GetPt(),track->GetPhi(),centbin);
	}
      }
    }
    //=============================  Resonances  ============================
    if(combos[0][4] || combos[1][4] || combos[2][4] || combos[3][4] || combos[4][4]){
      while(anaMaker->GetNextResonanceTrack()){
	//we don't delete this because it belongs to anaMaker
	TResonanceTrack* track = anaMaker->GetNextTResonanceTrack();
	if(track->GetPt()>lowAssocCut){
	  FillPhiHisto(track->GetType(),track->GetPt(),track->GetPhi(),centbin);
	  FillCorrelationHistos(track->GetType(),track->GetPt(),track->GetPhi(),centbin,track->GetTrackIdPos(),track->GetTrackIdNeg());
	}
      }
    }
    FillNPartHistos();
    //}
  eventnum++;
  return kStOk;
}
Int_t CorrelationMaker::Finish(){
  file->Write();
  file->Close();
  return kStOk;
}

void CorrelationMaker::CreateHisto1D(char name[100], char title[100], char xtitle[100], char ytitle[100],Int_t xbins, Float_t xlow,Float_t xhigh)
{     
  TString *histoname   = new TString();
  TString *histotitle   = new TString();
  
  histoname->Append(name);
  histotitle->Append(title);
  // printf("%s \n ",histoname->Data());
  TH1F *histo = new TH1F(histoname->Data(),histotitle->Data(),xbins,xlow,xhigh);
  histo->SetYTitle(ytitle);
  histo->SetXTitle(xtitle);
  histo->Sumw2();
  histoList->Add(histo);
  delete histoname;
  delete histotitle;
    
}
void CorrelationMaker::CreateIntHisto1D(char name[100], char title[100], char xtitle[100], char ytitle[100],Int_t xbins, Float_t xlow,Float_t xhigh)
{     
  TString *histoname   = new TString();
  TString *histotitle   = new TString();
  
  histoname->Append(name);
  histotitle->Append(title);
  // printf("%s \n ",histoname->Data());
  TH1I *histo = new TH1I(histoname->Data(),histotitle->Data(),xbins,xlow,xhigh);
  histo->SetYTitle(ytitle);
  histo->SetXTitle(xtitle);
  histo->Sumw2();
  histoList->Add(histo);
  delete histoname;
  delete histotitle;
    
}
void CorrelationMaker::FillHisto1D(char histname[100], Float_t x, Float_t weight)
{
  TH1F     *histo; 
  TString  *name   = new TString();
  
  name->Append(histname);       
  histo = (TH1F *)histoList->FindObject(name->Data()); 
  if(histo){
    histo->Fill((Double_t)x, weight);
  }
  else{cerr<<"CorrelationMaker::FillHisto1D: no histogram "<< name->Data()<<endl;}
  //cout<<"filled "<<name->Data()<<endl;
  delete name;
}
void CorrelationMaker::FillIntHisto1D(char histname[100], Float_t x)
{
  TH1I     *histo; 
  TString  *name   = new TString();
  
  name->Append(histname);       
  histo = (TH1I *)histoList->FindObject(name->Data()); 
  if(histo){
    histo->Fill((Double_t)x);
  }
  else{cerr<<"CorrelationMaker::FillHisto1D: no histogram "<< name->Data()<<endl;}
  delete name;
}

void CorrelationMaker::BookParticleHistos(){
  float mypi = TMath::Pi();
  TDirectory *correlations = file->mkdir("Correlations");
  for(int trigClass = 0; trigClass<numClasses;trigClass++){//loop over possible trigger classes
    for(int trigPartNum=0;trigPartNum<maxNumPartID;trigPartNum++){
      int trigID = particleIDs[trigClass][trigPartNum];
      if(trigID != -1){
	TDirectory *triggerDir = correlations->mkdir( Form("Trigger_%s",GetSimpleParticleName(trigID)) );//make directory for trigger particle
	triggerDir->cd();//change to that directory
	for(int assocClass = 0; assocClass<numClasses;assocClass++){//loop over possible associated classes
	      
	  if(combos[trigClass][assocClass]){//only make histograms if these correlations will be done
	    for(int assocPartNum=0;assocPartNum<maxNumPartID;assocPartNum++){
	      int assocID = particleIDs[assocClass][assocPartNum];
	      if(assocID != -1){
		TDirectory *assocDir = triggerDir->mkdir( Form("Associated_%s",GetSimpleParticleName(assocID)) );//make directory for trigger particle
		assocDir->cd();//change to that directory
		for(int trigCutNum=0;trigCutNum<numCuts;trigCutNum++){
		  float lowTrigPt = triggerCuts[trigCutNum][0];
		  float highTrigPt = triggerCuts[trigCutNum][1];
		  TDirectory *trigCutDir = assocDir->mkdir( Form("TrigPt%i-%i",(int)(lowTrigPt*10),(int)(highTrigPt*10)) );//make directory for trigger particle
		  trigCutDir->cd();//change to that directory


		  for(int assocCutNum=0;assocCutNum<numCuts;assocCutNum++){//high pt associated cuts
		    float lowAssocPt = highPtAssocCuts[assocCutNum][0];
		    float highAssocPt = highPtAssocCuts[assocCutNum][1];
		    TDirectory *assocCutDir = trigCutDir->mkdir( Form("AssocPt%i-%i",(int)(lowAssocPt*10),(int)(highAssocPt*10)) );//make directory for trigger particle
		    assocCutDir->cd();//change to that directory
		    for(int CentBin=1;CentBin<=nCentBins;CentBin++){
		      char *name = GetCorrelationHistoName(trigID,lowTrigPt,highTrigPt,assocID,lowAssocPt,highAssocPt,CentBin);
		      char *title = GetCorrelationHistoTitle(dataset,trigID,lowTrigPt,highTrigPt,assocID,lowAssocPt,highAssocPt,CentBin);
		      CreateHisto1D(name,title,"#DeltaPhi","number of entries",1200,-mypi,mypi);
		    }
		  }

		  if(doLowPtCorr){
		    for(int assocCutNum=0;assocCutNum<numCuts;assocCutNum++){//low pt associated cuts
		      float lowAssocPt = lowPtAssocCuts[assocCutNum][0];
		      float highAssocPt = lowPtAssocCuts[assocCutNum][1];
		      TDirectory *assocCutDir = trigCutDir->mkdir( Form("AssocPt%i-%i",(int)(lowAssocPt*10),(int)(highAssocPt*10)) );//make directory for trigger particle
		      assocCutDir->cd();//change to that directory
		      for(int CentBin=1;CentBin<=nCentBins;CentBin++){
			char *name = GetCorrelationHistoName(trigID,lowTrigPt,highTrigPt,assocID,lowAssocPt,highAssocPt,CentBin);
			char *title = GetCorrelationHistoTitle(dataset,trigID,lowTrigPt,highTrigPt,assocID,lowAssocPt,highAssocPt,CentBin);
			CreateHisto1D(name,title,"#Delta#phi","number of entries",1200,-mypi,mypi);
		      }
		    }
		  }


		}
	      }
	    }
	  }
	}
      }
    }
  }
  TDirectory *phi = file->mkdir("PhiDistributions");
  phi->cd();
  for(int classNum = 0; classNum <numClasses; classNum++){
    if(combos[classNum][0] ||combos[classNum][1]||combos[classNum][2]||combos[classNum][3]||combos[classNum][4]||combos[0][classNum] ||combos[1][classNum]||combos[2][classNum]||combos[3][classNum]||combos[4][classNum]){//if this particle will be used as an associated particle or a trigger particle
      for(int partNum =0; partNum < maxNumPartID; partNum++){
	if(particleIDs[classNum][partNum]!=-1){
	  TDirectory *partDir = phi->mkdir( GetSimpleParticleName( particleIDs[classNum][partNum] ) );
	  partDir->cd();
	  for(int phiCut = 0; phiCut<numPhiDistCuts; phiCut++){
	    TDirectory *pTcutDir = partDir->mkdir( Form("Pt%i-%i",(int)(10*phiDistCuts[phiCut][0]),(int)(10*phiDistCuts[phiCut][1])) );
	    pTcutDir->cd();
	    for(int CentBin=1;CentBin<=nCentBins;CentBin++){
	      float lowpt = phiDistCuts[phiCut][0];
	      float highpt = phiDistCuts[phiCut][1];
	      int partID = particleIDs[classNum][partNum];
	      char *name = GetPhiHistoName( partID , lowpt , highpt ,CentBin);
	      char *title = GetPhiHistoTitle(dataset, partID , lowpt , highpt ,CentBin);
	      CreateHisto1D(name, title, "#phi","number of entries",1200, -mypi,mypi);
	      name = GetNPartHistoName( partID , lowpt , highpt ,CentBin);
	      title = GetNPartHistoTitle(dataset, partID , lowpt , highpt ,CentBin);
	      CreateIntHisto1D(name, title, "Number of Particles","number of entries",100,0,100);
	    }
	  }
	  if(doLowPtCorr){
	    for(int phiCut = 0; phiCut<numCuts; phiCut++){
	      TDirectory *pTcutDir = partDir->mkdir( Form("Pt%i-%i",(int)(10*lowPtAssocCuts[phiCut][0]),(int)(10*lowPtAssocCuts[phiCut][1])) );
	      pTcutDir->cd();
	      for(int CentBin=1;CentBin<=nCentBins;CentBin++){
		float lowpt = lowPtAssocCuts[phiCut][0];
		float highpt = lowPtAssocCuts[phiCut][1];
		int partID = particleIDs[classNum][partNum];
		char *name = GetPhiHistoName( partID , lowpt , highpt ,CentBin);
		char *title = GetPhiHistoTitle(dataset, partID , lowPtAssocCuts[phiCut][0] , lowPtAssocCuts[phiCut][1] ,CentBin);
		CreateHisto1D(name, title, "#phi","number of entries",1200, -mypi,mypi);
		name = GetNPartHistoName( partID , lowpt , highpt ,CentBin);
		title = GetNPartHistoTitle(dataset, partID , lowpt , highpt ,CentBin);
		CreateIntHisto1D(name, title, "Number of Particles","number of entries",500,0,500);
		//if(CentBin==1&&partID==0) cout<<"made "<<name<<endl;
	      }
	    }
	  }
	}
      }
    }
  }
}

void CorrelationMaker::UseUnidentifiedTriggers(bool V0assoc, bool Xiassoc, bool dEdxassoc, bool resassoc){
  combos[0][1]=V0assoc;
  combos[0][2]=Xiassoc;
  combos[0][3]=dEdxassoc;
  combos[0][4]=resassoc;
}
void CorrelationMaker::UseV0Triggers(bool V0assoc, bool Xiassoc, bool dEdxassoc, bool resassoc){
  combos[1][0]=true;
  combos[1][1]=V0assoc;
  combos[1][2]=Xiassoc;
  combos[1][3]=dEdxassoc;
  combos[1][4]=resassoc;
}
void CorrelationMaker::UseXiTriggers(bool V0assoc, bool Xiassoc, bool dEdxassoc, bool resassoc){
  combos[2][0]=true;
  combos[2][1]=V0assoc;
  combos[2][2]=Xiassoc;
  combos[2][3]=dEdxassoc;
  combos[2][4]=resassoc;
}
void CorrelationMaker::UsedEdxTriggers(bool V0assoc, bool Xiassoc, bool dEdxassoc, bool resassoc){
  combos[3][0]=true;
  combos[3][1]=V0assoc;
  combos[3][2]=Xiassoc;
  combos[3][3]=dEdxassoc;
  combos[3][4]=resassoc;
}
void CorrelationMaker::UseResonanceTriggers(bool V0assoc, bool Xiassoc, bool dEdxassoc, bool resassoc){
  combos[4][0]=true;
  combos[4][1]=V0assoc;
  combos[4][2]=Xiassoc;
  combos[4][3]=dEdxassoc;
  combos[4][4]=resassoc;
}
float CorrelationMaker::GetLowTrigPtBin(float trigPt){
  for(int trigCut = 0; trigCut< numCuts; trigCut++){
    if(trigPt>triggerCuts[trigCut][0] && trigPt < triggerCuts[trigCut][1]) return triggerCuts[trigCut][0];
  }
  return -1;
}
float CorrelationMaker::GetHighTrigPtBin(float trigPt){
  for(int trigCut = 0; trigCut< numCuts; trigCut++){
    if(trigPt>triggerCuts[trigCut][0] && trigPt < triggerCuts[trigCut][1]) return triggerCuts[trigCut][1];
  }
  return -1;
}

float CorrelationMaker::GetLowAssocPtBin(float trigPt){
  for(int assocCut = 0; assocCut< numCuts; assocCut++){
    if(trigPt>highPtAssocCuts[assocCut][0] && trigPt < highPtAssocCuts[assocCut][1]) return highPtAssocCuts[assocCut][0];
  }
  if(doLowPtCorr){
    for(int assocCut = 0; assocCut< numCuts; assocCut++){
      if(trigPt>lowPtAssocCuts[assocCut][0] && trigPt < lowPtAssocCuts[assocCut][1]) return lowPtAssocCuts[assocCut][0];
    }
  }
  return -1;
}
float CorrelationMaker::GetHighAssocPtBin(float trigPt){
  for(int assocCut = 0; assocCut< numCuts; assocCut++){
    if(trigPt>highPtAssocCuts[assocCut][0] && trigPt < highPtAssocCuts[assocCut][1]) return highPtAssocCuts[assocCut][1];
  }
  if(doLowPtCorr){
    for(int assocCut = 0; assocCut< numCuts; assocCut++){
      if(trigPt>lowPtAssocCuts[assocCut][0] && trigPt < lowPtAssocCuts[assocCut][1]) return lowPtAssocCuts[assocCut][1];
    }
  }
  return -1;
}
void CorrelationMaker::FillCorrelationHisto(int triggerID, float triggerPt, float triggerPhi, int assocID, float assocPt, float assocPhi, int centBin){
  //if(triggerID==1 && triggerPt>2 && triggerPt<3 && assocID==0 && assocPt >1 && assocPt<2) cout<<"assoc"<<endl;
  //float *trigBin = GetTrigPtBin(trigPt);
  //float *assocBin = GetAssocPtBin(assocPt);
  float trigLow = GetLowTrigPtBin(triggerPt);
  float trigHigh = GetHighTrigPtBin(triggerPt);
  float assocLow = GetLowAssocPtBin(assocPt);
  float assocHigh = GetHighAssocPtBin(assocPt);
  //cout<<" 494 "<<triggerPt<<" "<<trigLow<<" "<<trigHigh<<" "<<assocPt<<" "<<assocLow<<" "<<assocHigh<<" ";
  if(trigLow!=-1 && trigHigh!=-1 && assocLow!=-1 && assocHigh!=-1){//if this trigger and associated pt combination fits into one of the pt bins given
    char *histoName = GetCorrelationHistoName(triggerID,trigLow,trigHigh,assocID,assocLow,assocHigh,centBin);
    float deltaPhi = dPhi(triggerPhi, assocPhi);
    //float effCorr = efficiencyCorrection((char*)dataset.c_str(), assocPt,anaMaker->RefMult(),assocID);
    float effCorr = 1;//temp in order to do checks
    //cout<<"efficiency correction : "<<effCorr<<endl;
    //cout<<histoName<<" trigID "<<triggerID<<endl;
    //if(triggerID==1) cout<<"filling "<<histoName<<" 2x"<<endl; 
    FillHisto1D(histoName, deltaPhi,effCorr);
    FillHisto1D(histoName, -deltaPhi,effCorr);//reflection
  }
}
void CorrelationMaker::FillCorrelationHistos(int assocID, float assocPt, float assocPhi, int centBin, int posID, int negID, int bachID){
  //here we also have to check that the ids of the associated and trigger particles aren't the same
  int assocClass = particleClass[assocID];
  if(triggers>0){
    for(int trig = 0; trig<triggers;trig++){
      int trigClass = particleClass[trigID[trig]];
      if(combos[trigClass][assocClass]){
	//cout<<" 503 "<<" trigpt "<<trigPt[trig]<<" trig id "<<trigID[trig]<<" trig class "<<trigClass<<" assoc id "<<assocID<<" assocClass "<<assocClass<< endl;
	if(trigPt[trig]>assocPt){//trigger pt must be greater than associated pt
	  bool write = true;
	  for(int i=0;i<3;i++){
	    if(trigDaughterIds[i][trig]!=-1){//if this id got filled
	      //if these variables are -1 they never got filled but we already know that what they'll be compared to is not -1
	      if(posID==trigDaughterIds[i][trig]) {
		write = false;
		break;
	      }
	      if(negID==trigDaughterIds[i][trig]) {
		write = false;
		break;
	      }
	      if(bachID==trigDaughterIds[i][trig]) {
		write = false;
		break;
	      }
	    }
	  }
	  if(write){
	    FillCorrelationHisto(trigID[trig],trigPt[trig],trigPhi[trig],assocID,assocPt,assocPhi,centBin);
	  }
	}
      }
    }
  }
}
void CorrelationMaker::FillV0CorrelationHistos(int assocID, float assocPt, float assocPhi, int centBin, int posID, int negID){
  //if(combos[1][0]) cout<<"hi Christine"<<endl;
  int assocClass = particleClass[assocID];
  if(triggers>0){
    for(int trig = 0; trig<triggers;trig++){
      int trigClass = particleClass[trigID[trig]];
      if(combos[trigClass][assocClass]){
	  //cout<<"filling V0 correlation histos"<<endl;
	//cout<<" 503 "<<" trigpt "<<trigPt[trig]<<" trig id "<<trigID[trig]<<" trig class "<<trigClass<<" assoc id "<<assocID<<" assocClass "<<assocClass<< endl;
	if(trigPt[trig]>assocPt && posID != trigDaughterIds[0][trig] && posID != trigDaughterIds[1][trig] && posID != trigDaughterIds[2][trig] && negID != trigDaughterIds[0][trig] && negID != trigDaughterIds[1][trig] && negID != trigDaughterIds[2][trig] ){//trigger pt must be greater than associated pt, trigger ID must not be associated ptID
	  FillCorrelationHisto(trigID[trig],trigPt[trig],trigPhi[trig],assocID,assocPt,assocPhi,centBin);
	}
      }
    }
  }
}

void CorrelationMaker::FillXiCorrelationHistos(int assocID, float assocPt, float assocPhi, int centBin, int posID, int negID, int bachID){
  int assocClass = particleClass[assocID];
  if(triggers>0){
    for(int trig = 0; trig<triggers;trig++){
      int trigClass = particleClass[trigID[trig]];
      if(combos[trigClass][assocClass]){
	if(trigPt[trig]>assocPt && posID != trigDaughterIds[0][trig] && posID != trigDaughterIds[1][trig] && posID != trigDaughterIds[2][trig] && negID != trigDaughterIds[0][trig] && negID != trigDaughterIds[1][trig] && negID != trigDaughterIds[2][trig]&& bachID != trigDaughterIds[0][trig] && bachID != trigDaughterIds[1][trig] && bachID != trigDaughterIds[2][trig] ){//trigger pt must be greater than associated pt, trigger ID must not be associated ptID
	  FillCorrelationHisto(trigID[trig],trigPt[trig],trigPhi[trig],assocID,assocPt,assocPhi,centBin);
	}
      }
    }
  }
}

void CorrelationMaker::FillPhiHisto(int partID, float pt, float phi, int centBin){
  int classNum = particleClass[partID];
  bool write = false;
  for(int i=0;i<numClasses;i++){if(combos[i][classNum]) write = true;}
  for(int i=0;i<numClasses;i++){if(combos[classNum][i]) write = true;}
  if(write){
    for(int i=0; i<numPhiDistCuts; i++){
      if(pt >phiDistCuts[i][0] && pt < phiDistCuts[i][1]){//if the pt is in the right range
	char *name = GetPhiHistoName(partID, phiDistCuts[i][0],phiDistCuts[i][1],centBin);
	FillHisto1D(name,phi);
	nPart[partID][i]++;
      }
    }
    if(doLowPtCorr){
      for(int i=0; i<numCuts;i++){
	if(pt > lowPtAssocCuts[i][0] && pt < lowPtAssocCuts[i][1]){
	  char *name = GetPhiHistoName(partID, lowPtAssocCuts[i][0], lowPtAssocCuts[i][1], centBin);
	  //cerr<<name;
	  FillHisto1D(name, phi);
	  nLowPtPart[partID][i]++;
	}
      }
    }
  }
}
void CorrelationMaker::ResetNParticles(){
  for(int i=0;i<totalNumParticles;i++){
    for(int j=0;j<numCuts;j++){
      nLowPtPart[i][j]=0;
    }
    for(int j=0;j<numPhiDistCuts;j++){
      nPart[i][j]=0;
    }
  }
}
void CorrelationMaker::FillNPartHistos(){
  int centbin = centrality(dataset,anaMaker->RefMult());
  for(int i=0;i<totalNumParticles;i++){//partID
    for(int j=0;j<numCuts;j++){//low pt cut
      if(nLowPtPart[i][j]!=0){
	char *name = GetNPartHistoName(i,lowPtAssocCuts[j][0],lowPtAssocCuts[j][1],centbin );
	FillIntHisto1D(name, nLowPtPart[i][j]);
      }
    }
    for(int j=0;j<numPhiDistCuts;j++){
      if(nPart[i][j]!=0){
	char *name = GetNPartHistoName(i,phiDistCuts[j][0],phiDistCuts[j][1], centbin);
	FillIntHisto1D(name, nPart[i][j]);
	//cout<<"filling "<<name<<endl;
      }
      //nPart[i][j]=0;
    }
  }
}
