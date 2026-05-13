#ifndef CorrelationMaker_h
#define CorrelationMaker_h

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
#include "StHighPtTools/dPhi.h"
#include "StHighPtTools/efficiency.h"
#include "StHighPtTools/efficiencyCorrection.h"
#include "StHighPtEvaluator/IsGoodV0Mass.h"
#include "StChain/StMaker.h"

#include "StAnalysisTools/GetHistoName.h"

class CorrelationMaker : public StMaker {
 public:
  CorrelationMaker(char *mydataset, AnalysisMaker *myAnaMaker);
  ~CorrelationMaker(){;}

  //Required maker functions
  void   Clear(Option_t *option="") {StMaker::Clear();}    
  Int_t  Init();                      
  Int_t  Make();//This will be empty because tracks must be added to the maker by another maker
  Int_t  Finish();    

  void SetFileName(char *myFileName) {fileName = myFileName;}

  void UseUnidentifiedTriggers(bool V0assoc = false, bool Xiassoc=false, bool dEdxassoc = false, bool resassoc = false);
  void UseV0Triggers(bool V0assoc = false, bool Xiassoc=false, bool dEdxassoc = false, bool resassoc = false);
  void UseXiTriggers(bool V0assoc = false, bool Xiassoc=false, bool dEdxassoc = false, bool resassoc = false);
  void UsedEdxTriggers(bool V0assoc = false, bool Xiassoc=false, bool dEdxassoc = false, bool resassoc = false);
  void UseResonanceTriggers(bool V0assoc = false, bool Xiassoc=false, bool dEdxassoc = false, bool resassoc = false);
  
  void DoLowPtCorrelations(){doLowPtCorr=true;}

 protected:
  TObjArray *histoList; //This will be an array of histograms to get written out to the file

 private:
  int eventnum;
  AnalysisMaker *anaMaker;
  bool doLowPtCorr;
  bool combos[5][5];//boolean array which keeps track of which classes of associated particles are run with which classes of trigger particles
  static int particleIDs[5][8];
  static int numClasses;
  static int maxNumPartID;
  static float lowPtAssocCuts[4][2];//array of low and high bounds for low pt associated cuts
  static float highPtAssocCuts[4][2];//array of low and high bounds for high pt associated cuts
  static float triggerCuts[4][2];//array of low and high bounds for trigger cuts
  static int numCuts;
  static float phiDistCuts[7][2];
  static int numPhiDistCuts;
  static int maxNumTriggers;
  static int totalNumParticles;
  static int particleClass[24];
  int nLowPtPart[24][4];
  int nPart[24][7];
  void ResetNParticles();
  void FillNPartHistos();
  string dataset;
  int nCentBins;
  char *fileName;//!
  TFile   *file;   //! output root file 
  TDirectory *top;
  void BookParticleHistos(); //This is more of a beast than in the last version.  It makes histograms but only if those histograms will be used.
  void FillHisto1D(char histname[100], Float_t x, Float_t weight = 1.0);
  void FillIntHisto1D(char histname[100], Float_t x);
  void FillPhiHisto(int partID, float pt, float phi, int centBin);
  void FillCorrelationHisto(int triggerID, float triggerPt, float triggerPhi, int assocID, float assocPt, float assocPhi, int centBin);//only fills one histogram
  void FillCorrelationHistos(int assocID, float assocPt, float assocPhi, int centBin, int posID = -1, int negID= -1, int bachID = -1);//fills all histograms for that associated particle
  void FillV0CorrelationHistos(int assocID, float assocPt, float assocPhi, int centBin, int posID, int negID);//fills all histograms for that associated particle
  void FillXiCorrelationHistos(int assocID, float assocPt, float assocPhi, int centBin, int posID, int negID, int bachID);//fills all histograms for that associated particle
  float GetLowTrigPtBin(float trigPt);
  float GetHighTrigPtBin(float trigPt);
  float GetLowAssocPtBin(float assocPt);
  float GetHighAssocPtBin(float assocPt);
  //float* GetTrigPtBin(float trigPt);//returns 2-d array with low and high bounds of appropriate trigger pt bin
  //float* GetAssocPtBin(float assocPt);//likewise but for associated pt bin
  void CreateHisto1D(char name[100],char title[100], char xtitle[100], char ytitle[100],Int_t xbins,Float_t xlow,Float_t xhigh);
  void CreateIntHisto1D(char name[100],char title[100], char xtitle[100], char ytitle[100],Int_t xbins,Float_t xlow,Float_t xhigh);
  int *trigID;
  float *trigPt;
  float *trigPhi;
  int *trigDaughterIds[3];//pos daughter, neg daughter, bachelor
  int triggers;
  ClassDef(CorrelationMaker,1)
};
#endif
