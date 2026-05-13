void MixEveCorrections(char *infile, char *outfile){

  gROOT->LoadMacro("~nattrass/HighPt/macros/loadHighPtLibraries.C");
  loadHighPtLibraries();
  gSystem->Load("/home/nattrass/AzimuthalCorrelations/.i386_linux24/lib/StAnalysisTools");
  gSystem->Load("/home/nattrass/AzimuthalCorrelations/.i386_linux24/lib/StAnalysis");
  string dataset = "CuCu200";
  DoMixEveCorrections(infile, dataset, outfile);

}
