void TestPhiMaker(){
  gROOT->LoadMacro("~nattrass/HighPt/macros/loadHighPtLibraries.C");
  loadHighPtLibraries();
  gSystem->Load("/home/nattrass/AzimuthalCorrelations/.i386_linux24/lib/StAnalysis");
  gSystem->Load("/home/nattrass/AzimuthalCorrelations/.i386_linux24/lib/StAnalysisTools");
  char *dataset = "CuCu200";
  PhiMaker *phiMaker = new PhiMaker(dataset);
  phiMaker->SetFileName("phi.root");
  phiMaker->Init();
  phiMaker->Make();
  phiMaker->Finish();
}
