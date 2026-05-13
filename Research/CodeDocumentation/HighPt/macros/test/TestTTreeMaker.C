void TestTTreeMaker(char*list){
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


  TTreeMaker *treeMaker = new TTreeMaker(anaMaker, dataset);
  treeMaker->SetFileName("junk.root");
  treeMaker->UseTIdentifiedTracks();
  treeMaker->SetMinV0Pt(0.0);
  treeMaker->UseTResonanceTracks();
  treeMaker->SetMinXiPt(0.0);
  //treeMaker->SetHighPtV0NSigmaCut(3.);

  anaMaker->MakeTResonanceTracks();
  anaMaker->MakeTIdentifiedTracks();
  anaMaker->SetV0CutsToDataSetTreeDefaults();
  anaMaker->SetXiPtMin(0.0);
  anaMaker->SetV0PtMin(0.0);

  //int nEvents=100000;
  int nEvents = anaMaker ->GetNEvents();
  cout<<"Running over "<<nEvents<<" events"<<endl;
  chain->Init();
  chain->EventLoop(1,nEvents);
  chain->Finish();
  
  delete chain;

}
