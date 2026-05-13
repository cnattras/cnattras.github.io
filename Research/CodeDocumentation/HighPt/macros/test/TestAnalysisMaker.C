void TestAnalysisMaker(char *list){
  gROOT->LoadMacro("~nattrass/HighPt/macros/loadHighPtLibraries.C");
  loadHighPtLibraries();

   char *dataset = "CuCu200";

  StChain *chain = new StChain;
  StMuDstMaker *muDstMaker = new StMuDstMaker(0,0,"",list,"",100);
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
  anaMaker->MakeTIdentifiedTracks();
  anaMaker->SetV0CutsToDataSetCorrelationDefaults();
  anaMaker->SetV0PtMin(1.0);
  anaMaker->MakeTResonanceTracks();
  anaMaker->SetTResonanceLowPt(2.0);

  //int nEvents=100000;
  int nEvents = anaMaker ->GetNEvents();
  cout<<"Running over "<<nEvents<<" events"<<endl;
  chain->Init();
  chain->EventLoop(1,nEvents);
  chain->Finish();
  
  delete chain;

}
