#ifndef StXiGeometricCuts_h
#define StXiGeometricCuts_h

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

class StXiGeometricCuts : public StMaker {
 public:
  StXiGeometricCuts(char *mydataset);
  ~StXiGeometricCuts(){;}

  //Required maker functions
  void   Clear(Option_t *option="") {StMaker::Clear();}    
  Int_t  Init();                      
  Int_t  Make();//This will be empty because tracks must be added to the maker by another maker
  Int_t  Finish();    

  void SetFileName(char *myFileName) {fileName = myFileName;}
  void DoLowPtXis(){doLowPt = true;}
  //void FillPhiHisto(int partID, float pt, float phi, int centBin);
  void FillCutHistos(int partID, float pt,float Ximass,float V0mass, float DcaXiToPV, float DcaV0ToPV, float DcaNeg, float DcaPos, float DcaBach, float DcaXiDaughters, float DcaV0Daughters, float NHitsNeg, float NHitsPos, float NHitsBach, float NSigNeg, float NSigPos, float NSigBach, float V0DecayLength, float XiDecayLength); 

 protected:
  TObjArray *histoList; //This will be an array of histograms to get written out to the file

 private:
  bool doLowPt;
  string dataset;
  char *fileName;//!
  TFile   *file;   //! output root file 
  //TDirectory *top;
  void BookParticleHistos(); 
  void FillHisto1D(char histname[100], Float_t x);
  void FillHisto2D(char histname[100], Float_t x, Float_t y);
  void CreateHisto1D(char name[100],char title[100], char xtitle[100], char ytitle[100],Int_t xbins,Float_t xlow,Float_t xhigh);
  void CreateHisto2D(char name[100],char title[100], char xtitle[100], char ytitle[100],Int_t xbins,Float_t xlow,Float_t xhigh,Int_t ybins, Float_t ylow,Float_t yhigh);

  static float highPtCuts[2][2];
  static float lowPtCuts[2][4];
  static int numHighPtCuts;
  static int numLowPtCuts;
  static int numCutHistos;
  static int numParticles;
  static float histoBoundsX[4][2];//partID, xlow/xhigh
  static float histoBoundsY[15][4][2];//partID,cut, ylow/yhigh
  static float v0MassBounds[2];
  static int nBins;
  int GetArrayIndex(int partID);
  ClassDef(StXiGeometricCuts,1)
};
#endif
