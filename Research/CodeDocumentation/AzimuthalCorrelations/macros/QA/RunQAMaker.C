void RunQAMaker(char *list){
  gROOT->LoadMacro("~nattrass/HighPt/macros/loadHighPtLibraries.C");
  loadHighPtLibraries();
  gSystem->Load("/home/nattrass/AzimuthalCorrelations/.i386_linux24/lib/StAnalysisTools");
  gSystem->Load("/home/nattrass/AzimuthalCorrelations/.i386_linux24/lib/StAnalysis");
  char *dataset = "CuCu200";

  StChain *chain = new StChain;
  StMuDstMaker *muDstMaker = new StMuDstMaker(0,0,"",list,"",100);

  PhiMaker *phiMaker = new PhiMaker(dataset);
  phiMaker->SetFileName("phi.root");

  RawSpectraMaker *ptMaker = new RawSpectraMaker(dataset);
  ptMaker->SetFileName("pt.root");

  infile = new TFile(list);
  tree = dynamic_cast<TTree*>(infile->Get("Correlation"));
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
  anaMaker->SetV0CutsToDataSetTreeDefaults();
  anaMaker->SetXiPtMin(0.0);
  anaMaker->SetMinPt(0.0);
   
  QAMaker *qaMaker = new QAMaker(dataset, anaMaker, phiMaker, ptMaker);
  qaMaker->WriteTIdentified();
  qaMaker->WriteV0s();
  qaMaker->WriteXis();
  qaMaker->WriteTResonances();

  int nEvents = anaMaker ->GetNEvents();
  cout<<"Running over "<<nEvents<<" events"<<endl;
  chain->Init();
  chain->EventLoop(1,nEvents);
  chain->Finish();
  
  delete chain;

 
}
