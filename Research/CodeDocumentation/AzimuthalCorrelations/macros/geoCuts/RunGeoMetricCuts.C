void RunGeoMetricCuts(char *list, char *v0file, char *xifile){
  gROOT->LoadMacro("~nattrass/HighPt/macros/loadHighPtLibraries.C");
  loadHighPtLibraries();
  gSystem->Load("StAnalysisTools");
  gSystem->Load("StAnalysis");
  char *dataset = "CuCu200";

  StChain *chain = new StChain;
  StMuDstMaker *muDstMaker = new StMuDstMaker(0,0,"",list,"",100);
  infile = new TFile(list);
  //cerr<<"13"<<endl;
  tree = dynamic_cast<TTree*>(infile->Get("Correlation"));
  //cerr<<"10"<<endl;
  if(tree) {
    if(tree) cout<<"This file contains a TTree"<<endl;
    AnalysisMaker *anaMaker = new AnalysisMaker(tree, dataset);
  }
  else{
    cout<<"This file contains a MuDst"<<endl;
    AnalysisMaker *anaMaker = new AnalysisMaker(muDstMaker,dataset);
  }
  anaMaker->MakeTResonanceTracks();
  anaMaker->MakeTIdentifiedTracks();
  anaMaker->SetV0CutsToDataSetCorrelationDefaults();
  anaMaker->SetXiPtMin(0.2);
  anaMaker->SetMinPt(0.0);
  anaMaker->SetV0PtMin(.2);

  StV0GeometricCuts *v0CutMaker = new StV0GeometricCuts(dataset);
  v0CutMaker->SetFileName(v0file);
  v0CutMaker->DoLowPtV0s();
  StXiGeometricCuts *xiCutMaker = new StXiGeometricCuts(dataset);
  xiCutMaker->SetFileName(xifile);
  xiCutMaker->DoLowPtXis();
  CutMaker *myCutMaker = new CutMaker(dataset,anaMaker, v0CutMaker, xiCutMaker);
  myCutMaker->WriteV0s();
  myCutMaker->WriteXis();

//   //default V0 Cuts
//   //particles:
  myCutMaker->SetDcaNegToPV(1,1.3);
//   myCutMaker->SetDcaNegToPV(4,1.0);
//   myCutMaker->SetDcaNegToPV(5,1.0);
//   //antiparticles
  myCutMaker->SetDcaPosToPV(2,1.3);
//   myCutMaker->SetDcaPosToPV(18,1.0);
//   myCutMaker->SetDcaPosToPV(19,1.0);
//   //K0s
//   myCutMaker->SetDcaV0Daughters(3,.4);
//   myCutMaker->SetV0DecayLength(3,3.);
  myCutMaker->SetDcaV0ToPV(3,4.);

//   //2.5 sigma cuts, added after 1st iteration for all vertices
//   //V0s
//   myCutMaker->SetNSigmaNeg(1,2.5);
//   myCutMaker->SetNSigmaPos(1,2.5);
//   myCutMaker->SetNSigmaNeg(2,2.5);
//   myCutMaker->SetNSigmaPos(2,2.5);
//   myCutMaker->SetNSigmaNeg(3,2.5);
//   myCutMaker->SetNSigmaPos(3,2.5);
//   //Xis
//   myCutMaker->SetNSigmaNeg(4,2);
//   myCutMaker->SetNSigmaNeg(5,2);
//   myCutMaker->SetNSigmaNeg(18,2);
//   myCutMaker->SetNSigmaNeg(19,2);
//   myCutMaker->SetNSigmaPos(4,2);
//   myCutMaker->SetNSigmaPos(5,2);
//   myCutMaker->SetNSigmaPos(18,2);
//   myCutMaker->SetNSigmaPos(19,2);
//   myCutMaker->SetNSigmaBach(4,2);
//   myCutMaker->SetNSigmaBach(5,2);
//   myCutMaker->SetNSigmaBach(18,2);
//   myCutMaker->SetNSigmaBach(19,2);

  //first iteration - a bunch of tighter DCAs
  //dca xi to pv
  myCutMaker->SetDcaXiToPV(4, .45);
  myCutMaker->SetDcaXiToPV(18, .45);
  myCutMaker->SetDcaXiToPV(5, .35);
  myCutMaker->SetDcaXiToPV(19, .35);
//   //dca V0 to pv
//   myCutMaker->SetDcaV0ToPV(5,.6);
//   myCutMaker->SetDcaV0ToPV(19,.6);
//   //dca V0 daughters
//   myCutMaker->SetDcaV0Daughters(5,.35);
//   myCutMaker->SetDcaV0Daughters(19,.35);
//   myCutMaker->SetDcaV0Daughters(4,.35);
//   myCutMaker->SetDcaV0Daughters(18,.35);
//   //dca Xi daughters
//   myCutMaker->SetDcaXiDaughters(4,.35);
//   myCutMaker->SetDcaXiDaughters(5,.35);
//   myCutMaker->SetDcaXiDaughters(18,.35);
//   myCutMaker->SetDcaXiDaughters(19,.35);

  //Setting cuts:
//   myCutMaker->SetDcaXiToPV(int partID, float cut);
//   myCutMaker->SetDcaV0ToPV(int partID, float cut);
//   myCutMaker->SetDcaNegToPV(int partID, float cut);
//   myCutMaker->SetDcaPosToPV(int partID, float cut);
//   myCutMaker->SetDcaBachToPV(int partID, float cut);
//   myCutMaker->SetDcaV0Daughters(int partID, float cut);
//   myCutMaker->SetDcaXiDaughters(int partID, float cut);
//   myCutMaker->SetNHitsNeg(int partID, float cut);
// myCutMaker->SetNHitsNeg(4,20);
// myCutMaker->SetNHitsNeg(5,20);
// myCutMaker->SetNHitsNeg(18,20);
// myCutMaker->SetNHitsNeg(19,20);
// myCutMaker->SetNHitsPos(4,20);
// myCutMaker->SetNHitsPos(5,20);
// myCutMaker->SetNHitsPos(18,20);
// myCutMaker->SetNHitsPos(19,20);
// myCutMaker->SetNHitsBach(4,20);
// myCutMaker->SetNHitsBach(5,20);
// myCutMaker->SetNHitsBach(18,20);
// myCutMaker->SetNHitsBach(19,20);
//   myCutMaker->SetNHitsPos(int partID, float cut);
//   myCutMaker->SetNHitsBach(int partID, float cut);
//   myCutMaker->SetNSigmaNeg(int partID, float cut);
//   myCutMaker->SetNSigmaPos(int partID, float cut);
//   myCutMaker->SetNSigmaBach(int partID, float cut);
//   myCutMaker->SetV0DecayLength(int partID, float cut);
//   myCutMaker->SetXiDecayLength(int partID, float cut);


  int nEvents = anaMaker ->GetNEvents();
  cout<<"Running over "<<nEvents<<" events"<<endl;
  chain->Init();
  chain->EventLoop(1,nEvents);
  chain->Finish();
  
  delete chain;

 
}

