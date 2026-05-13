#ifndef PhiMaker_h
#define PhiMaker_h

//c++ stuff
#include <string> 


//ROOT stuff
#include "TObject.h"
#include "TFile.h"
#include "TClonesArray.h"
#include "TObjArray.h"
#include "TList.h"
#include "TIterator.h"
#  include "Riostream.h"//needed to use things like cout, which I will use primarily for debugging

//All of the container classes from the StHighPt library
#include "StHighPtTree/TTrack.h"
#include "StHighPtTree/TV0Track.h"
#include "StHighPtTree/TXiTrack.h"
#include "StHighPtTree/TIdentifiedTrack.h"
#include "StHighPtTree/TResonanceTrack.h"
#include "StHighPtTree/TEvent.h"
#include "StHighPtTree/TV0.h"
//I need the analysis maker
#include "StHighPtLoop/AnalysisMaker.h"
#include "StHighPtTools/centrality.h"
#include "StHighPtTools/GetParticleName.h"
#include "StChain/StMaker.h"

#include "StAnalysisTools/GetHistoName.h"

class PhiMaker : public StMaker {
 public:
  PhiMaker(char *mydataset);
  ~PhiMaker(){;}

  //Required maker functions
  void   Clear(Option_t *option="") {StMaker::Clear();}    
  Int_t  Init();                      
  Int_t  Make();//This will be empty because tracks must be added to the maker by another maker
  Int_t  Finish();    

  void SetFileName(char *myFileName) {fileName = myFileName;}

  void FillPhiHisto(int partID, float pt, float phi, int centBin);

 protected:
  TObjArray *histoList; //This will be an array of histograms to get written out to the file

 private:
  string dataset;
  char *fileName;//!
  TFile   *file;   //! output root file 
  TDirectory *top;
  void BookParticleHistos(); 
  void FillHisto1D(char histname[100], Float_t x);
  void CreateHisto1D(char name[100],char title[100], char xtitle[100], char ytitle[100],Int_t xbins,Float_t xlow,Float_t xhigh);

  ClassDef(PhiMaker,1)
};
#endif
