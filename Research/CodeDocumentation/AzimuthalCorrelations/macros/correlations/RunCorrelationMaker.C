void RunCorrelationMaker(char *list, char *outfile){
  gROOT->LoadMacro("~nattrass/HighPt/macros/loadHighPtLibraries.C");
  loadHighPtLibraries();
  gSystem->Load("/home/nattrass/AzimuthalCorrelations/.i386_linux24/lib/StAnalysisTools");
  gSystem->Load("/home/nattrass/AzimuthalCorrelations/.i386_linux24/lib/StAnalysis");
  char *dataset = "CuCu200";

  //This macro has been made into something to run over only TTrees.  These lines can be uncommented for running over StMuDsts
  StChain *chain = new StChain;
  //cerr<<"10"<<endl;
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
  anaMaker->SetXiPtMin(0.0);
  anaMaker->SetMinPt(0.0);
  anaMaker->SetV0PtMin(1.0);

  CorrelationMaker *corrMaker = new CorrelationMaker(dataset, anaMaker);
  corrMaker->SetFileName(outfile);
  corrMaker->UseUnidentifiedTriggers(true);
  corrMaker->UseV0Triggers();
  //corrMaker->UseXiTriggers();
  corrMaker->DoLowPtCorrelations();
  //corrMaker->UsedEdxTriggers();
  //corrMaker->UseResonanceTriggers();

   
  int nEvents = anaMaker ->GetNEvents();
  cout<<"Running over "<<nEvents<<" events"<<endl;
  chain->Init();
  chain->EventLoop(1,nEvents);
  chain->Finish();
  
  delete chain;

 
}
