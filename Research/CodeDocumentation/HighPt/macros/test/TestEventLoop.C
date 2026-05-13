#ifndef __CINT__
#  include "tools.h"
#  include "TROOT.h"
#  include "TSystem.h"
#  include "Riostream.h"
#endif

void TestEventLoop(){
  cout<<"Loading library StHighPtLoop"<<endl;
  gSystem->Load("libStHighPtLoop");
  gSystem->Load("libStHighPtEvaluator");
  gSystem->Load("libStHighPtTree");

  gROOT->LoadMacro("macros/loadSharedLibraries.C");
  loadSharedLibraries();

  gSystem->Load("StMuDSTMaker");

  cout<<"Testing loops"<<endl;

  cout<<"Making an StHighPtEventLoop out of a file with a TTree:"<<endl;
  StHighPtEventLoop *TreeLoop = new StHighPtEventLoop("/data4/nattrass/CuCu200_P06id/OutputMinBias/files1.root","CuCu200");
  TreeLoop->GetEvents();
  delete TreeLoop;

  cout<<"Making an StHighPtEventLoop out of a file with a MuDst:"<<endl;
  StHighPtEventLoop *StLoop = new StHighPtEventLoop("/data4/nattrass/st_physics_adc_6020017_raw_1050003.MuDst.root","CuCu200");
  StLoop->GetEvents();
  delete StLoop;
}
