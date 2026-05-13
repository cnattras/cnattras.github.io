#include "TTreeMaker.h"
ClassImp(TTreeMaker)
TTreeMaker::TTreeMaker(AnalysisMaker *maker, char *mydataset): StMaker() {
  anaMaker = maker;
  dataset = mydataset;
  nEventsPassed = nEventsFailed = 0;
  fileName = "";
  nStMuEvent = 0;
  minV0pT = 0.0;
  minXipT = 0.0;
  minChargedPt = 1.0;
  useTIDTracks = false;
  useTResTracks = false;
  highPtNSigmaCut = 10000;
  lowPtNSigmaCut = 3;
}

Int_t TTreeMaker::Init(){
  file =  new TFile(fileName, "RECREATE","HistoFile");
  cout << "The output filename is " << fileName << endl;

  
  //---- Event-wise histograms ----//
  eventHistos = new TStMuEventAna();
  eventHistos->CreateHisto("all");
  hEventStat = new TH1F("hEventStat","Event Statistics", 5, 0.5, 5.5);

  //---- Track-wise histograms ----//
  float mypi = TMath::Pi();
  // Lambda
  hLambdaMass = new TH1F("hLambdaMass","#Lambda mass (GeV)",5000,0.0,2.0);  
  hLambdaMass->SetYTitle("number of entries");
  hLambdaMass->SetXTitle("Mass (GeV)");
  //Anti-Lambda
  hAntiLambdaMass = new TH1F("hAntiLambdaMass","#bar{#Lambda} mass (GeV)",5000,0.0,2.0);  
  hAntiLambdaMass->SetYTitle("number of entries");
  hAntiLambdaMass->SetXTitle("Mass (GeV)");
  // K0s
  hK0Mass = new TH1F("hK0Mass","K^{0}_{s} mass (GeV)",500,0.0,1.0);  
  hK0Mass->SetYTitle("number of entries");
  hK0Mass->SetXTitle("Mass (GeV)");
  // Xi
  hXiMass = new TH1F("hXiMass","#Xi mass (GeV)",500,1.1,1.5);  
  hXiMass->SetYTitle("number of entries");
  hXiMass->SetXTitle("Mass (GeV)");
  // Anti-Xi
  hAntiXiMass = new TH1F("hAntiXiMass","#bar{#Xi} mass (GeV)",500,1.1,1.5);  
  hAntiXiMass->SetYTitle("number of entries");
  hAntiXiMass->SetXTitle("Mass (GeV)");
  // Omega
  hOmegaMass = new TH1F("hOmegaMass","#Omega mass (GeV)",500,1.5,1.9);  
  hOmegaMass->SetYTitle("number of entries");
  hOmegaMass->SetXTitle("Mass (GeV)");
  // Anti-Omega
  hAntiOmegaMass = new TH1F("hAntiOmegaMass","#bar{#Omega} mass (GeV)",500,1.5,1.9);  
  hAntiOmegaMass->SetYTitle("number of entries");
  hAntiOmegaMass->SetXTitle("Mass (GeV)");
  
    //----Create a tree with branches: lambda, charged particle, event properties
    
  Int_t split = 99;//for Oana
  file->SetCompressionLevel(1);//for Oana
  ttree = new TTree("Correlation","Correlation tree", split);
  ttree->SetAutoSave(1000000000);  // autosave when 1 Gbyte written
  Int_t bufsize = 64000;
  //Int_t split = 1;
  //if (split)  bufsize /= 4;
  tevent = new TEvent();
  tv0s   = new TV0();
  TTree::SetBranchStyle(1); //new style by default
  TBranch *branch1 = ttree->Branch("Event", "TEvent", &tevent, bufsize,split);     
  branch1->SetAutoDelete(kFALSE); 
  TBranch *branch2 = ttree->Branch("V0", "TV0", &tv0s, bufsize,split);     
  branch2->SetAutoDelete(kFALSE); 
  ttree->SetDirectory(file);//for Oana



  hLambdaResMass = new TH1F("hLambdaResMass","#Lambda mass (GeV) (resonance)",100,1.0,1.2);
  hLambdaResMass->SetYTitle("number of entries");
  hLambdaResMass->SetXTitle("Mass (GeV)");
  hAntiLambdaResMass = new TH1F("hAntiLambdaResMass","#bar{#Lambda} mass (GeV) (resonance)",100,1.0,1.2);
  hAntiLambdaResMass->SetYTitle("number of entries");
  hAntiLambdaResMass->SetXTitle("Mass (GeV)");
  hK0ResMass = new TH1F("hK0ResMass","K^{0}_{s} mass (GeV) (resonance)",100,.4,.6);
  hK0ResMass->SetYTitle("number of entries");
  hK0ResMass->SetXTitle("Mass (GeV)");
  hPhiResMass = new TH1F("hPhiResMass","#phi mass (GeV)#",100,.9,1.1);
  hPhiResMass->SetYTitle("number of entries");
  hPhiResMass->SetXTitle("Mass (GeV)");


  return StMaker::Init();
}

Int_t TTreeMaker::Make(){
  if(anaMaker->GoodEvent()){
    //anaMaker->Make();
    //TList trigTracks,assocTracks;
    //TList lambdaTracks,alambdaTracks,k0Tracks;
    //in principle this could be used in a chain of many makers so I'll make sure I'm starting at the 0th track in the event
    //cerr<<" 102 ";
    anaMaker->ResetTrackIterators();

    //Filling the ttree
    tevent = new TEvent();
  
    tevent->SetHeader(anaMaker->RunId(),anaMaker->EventId(),anaMaker->GetTrigger1(),anaMaker->GetTrigger2());
    tevent->SetZVertex(anaMaker->VertexZ());
    tevent->SetMultiplicity(anaMaker->RefMult());

    int nCharged =0;
    int nChargedTotal = 0;
    int nV0 = 0;
    int nLambda = 0;
    int nAntilambda = 0;
    int nK0s = 0;
    int nXi = 0;
    int nAntiXi = 0;
    int nOmega = 0;
    int nAntiOmega = 0;
    //cerr<<" 122 ";
    anaMaker->ResetTrackIterators();
    while(anaMaker->GetNextChargedTrack()){
      //cerr<<"h";
      //cout<<" TTreeMaker 124 "<<endl;
      nChargedTotal++;
      if(useTIDTracks){
	//this belongs to anaMaker and it's its job to clean it up
	TIdentifiedTrack *tidTrack = anaMaker->GetNextTIdentifiedTrack();
	if(!tidTrack){cout<<"no tidTrack!"<<endl;}
	//add the TIdentifiedTrack to its relevant TClonesArray if its dEdx is within 2 sigma of the appropriate daughter
	if(tidTrack && tidTrack->GetPt()>minChargedPt){
	  tevent->AddTIdentifiedTrack( tidTrack, (Float_t) minChargedPt, (Int_t)0);
	  nCharged++;
	}
      }
      else{
	if(anaMaker->GetNextTTrack()->GetPt()>minChargedPt){
	  tevent->AddTrack(anaMaker->GetNextTTrack(),minChargedPt,0);
	  nCharged++;
	}
      }
    }
    //cerr<<endl;
    anaMaker->ResetTrackIterators();
    //Writing V0s
    tv0s  = new TV0();
    //cerr<<" 149 ";
    while(anaMaker->GetNextV0Track()){
      //cerr<<"v0";
      TV0Track *track = anaMaker->GetNextTV0Track();
      if(track->GetPt()>=minV0pT && PassesNSigmaCuts(track) ){
	nV0++;
	//all of the tracks have already been checked by AnalysisMaker and therefore we don't need to check whether they're good or not
	if(track->GetType()==1){//lambda
	  hLambdaMass->Fill( track->GetMass() );
	  tv0s->AddV0Track(track,minV0pT,1);
	  nLambda++;
	}
	if(track->GetType()==2){//antilambda
	  hAntiLambdaMass->Fill( track->GetMass() );
	  tv0s->AddV0Track(track,minV0pT,2);
	  nAntilambda++;
	}
	if(track->GetType()==3){//K0s
	  hK0Mass->Fill( track->GetMass() );
	  tv0s->AddV0Track(track,minV0pT,3);
	  nK0s++;
	}
      }
    }
    //cerr<<endl;
    anaMaker->ResetTrackIterators();
    int xiCan = 0;
    //cerr<<" 176 ";
    while(anaMaker->GetNextXiTrack()){
      cout<<"Xi";
      TXiTrack *track = anaMaker->GetNextTXiTrack();
      if(track->GetPt()>=minXipT && PassesNSigmaCuts(track) ){
	xiCan++;
	//cerr<<"Xi "<<xiCan<<endl;
	//all of the tracks have already been checked by AnalysisMaker and therefore we don't need to check whether they're good or not
	if(track->GetType()==4){//Xi
	  cout<<" adding xi "<<endl;
	  hXiMass->Fill( track->GetMass() );
	  tevent->AddXiTrack(track,minXipT,0);
	  nXi++;
	}
	if(track->GetType()==18){//AntiXi
	  cout<<" adding anti-xi "<<endl;
	  hAntiXiMass->Fill( track->GetMass() );
	  tevent->AddXiTrack(track,minXipT,0);
	  nAntiXi++;
	}
	if(track->GetType()==5){//Omega
	  cout<<" adding omega "<<endl;
	  hOmegaMass->Fill( track->GetMass() );
	  tevent->AddXiTrack(track,minXipT,0);
	  nOmega++;
	}
	if(track->GetType()==19){//AntiOmega
	  cout<<" adding anti-omega "<<endl;
	  hAntiOmegaMass->Fill( track->GetMass() );
	  tevent->AddXiTrack(track,minXipT,0);
	  nAntiOmega++;
	}
      }
    }
    //cerr<<endl;
    anaMaker->ResetTrackIterators();
    int nK0Res = 0;
    int nPhiRes = 0;
    int nLamRes = 0;
    int nAlamRes = 0;
    //cerr<<" 216 ";
    if(useTResTracks){
      while(anaMaker->GetNextResonanceTrack()){
	//cerr<<"TRes";
	TResonanceTrack* track = anaMaker->GetNextTResonanceTrack();
	tevent->AddTResonanceTrack(track);
	if(track->GetType()==14) nLamRes++;
	if(track->GetType()==15) nAlamRes++;
	if(track->GetType()==16) nK0Res++;
	if(track->GetType()==17) nPhiRes++;
      }
    }
    //cerr<<endl;
    cout <<"h "<<nCharged;
    cout<<" v0s "<< nV0<<" lambda  " << nLambda << " antilambda  " << nAntilambda << " K0s  " << nK0s;
    cout<<" xi "<< nXi<<" antixi "<<nAntiXi<<" omega "<<nOmega<<" antiomega "<<nAntiOmega;
    cout<< " lam res "<<nLamRes<<" alam res "<< nAlamRes<<" K0 res "<<nK0Res<<" Phi res "<<nPhiRes;
    cout<<endl;





    ttree->Fill();
    delete tevent;	  
    delete tv0s;
  }

  return kStOk;
}
  
  

Int_t TTreeMaker::Finish(){

  cout << "The histograms are now written to the output file " << fileName << endl;
  cout << "\tEvents passed: " << anaMaker->GetNGoodEvents() << endl;
  cout << "\tEvents failed: " << anaMaker->GetNBadEvents() << endl;

  hEventStat->Fill(1.0,anaMaker->GetNGoodEvents());
  hEventStat->Fill(2.0,anaMaker->GetNBadEvents());

  //get TResonanceTrack mass histos from anaMaker
  file->cd();
  anaMaker->LambdaMassHisto()->Copy(*hLambdaResMass);
  anaMaker->AntilambdaMassHisto()->Copy(*hAntiLambdaResMass);
  anaMaker->K0sMassHisto()->Copy(*hK0ResMass);
  anaMaker->PhiMassHisto()->Copy(*hPhiResMass);

  file->Write();
  file->Close();
  return kStOk;
}
bool TTreeMaker::PassesNSigmaCuts(TV0Track *track){
  if( track->GetPt() >1){//high pt
    if(track->GetdEdxPosDaughter() > highPtNSigmaCut || track->GetdEdxNegDaughter()> highPtNSigmaCut){ return false;}
  }
  if(track->GetPt()<1){//low pt
    if(track->GetdEdxPosDaughter()> lowPtNSigmaCut || track->GetdEdxNegDaughter()> lowPtNSigmaCut){ return false;}
  }
  return true;
}
bool TTreeMaker::PassesNSigmaCuts(TXiTrack *track){
  if( track->GetPt() >1){//high pt
    if(track->GetdEdxPosDaughter() > highPtNSigmaCut || track->GetdEdxNegDaughter()> highPtNSigmaCut || track->GetdEdxBachDaughter()> highPtNSigmaCut){ 
      return false;
    }
    else{
    }
  }
  if(track->GetPt()<1){//low pt
    if(track->GetdEdxPosDaughter()> lowPtNSigmaCut || track->GetdEdxNegDaughter()> lowPtNSigmaCut || track->GetdEdxBachDaughter()> lowPtNSigmaCut){ 
      return false;
    }
    else{
    }
  }
  return true;
}
