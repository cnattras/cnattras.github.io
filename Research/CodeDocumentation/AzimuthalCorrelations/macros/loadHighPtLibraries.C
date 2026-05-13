#include "TSystem.h"

extern TSystem* gSystem;


void loadHighPtLibraries() {
   gROOT->LoadMacro("~nattrass/HighPt/macros/loadSharedLibraries.C");
  loadSharedLibraries();
  // Dynamically link needed shared libs
  gSystem->Load("~/HighPt/.i386_linux24/lib/StHighPtEvaluator");
  gSystem->Load("~/HighPt/.i386_linux24/lib/StHighPtTree");
  gSystem->Load("~/HighPt/.i386_linux24/lib/StHighPtLoop");
  gSystem->Load("~/HighPt/.i386_linux24/lib/StHighPtTools");
  cout << " loading of StHighPt libraries done" << endl;
}
