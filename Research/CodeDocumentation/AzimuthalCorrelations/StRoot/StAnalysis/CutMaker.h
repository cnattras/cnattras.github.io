#ifndef CutMaker_h
#define CutMaker_h

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
#include "StHighPtEvaluator/IsGoodV0Track.h"
//I need the analysis maker
#include "StHighPtLoop/AnalysisMaker.h"
#include "StHighPtTools/centrality.h"
#include "StHighPtTools/GetParticleName.h"
#include "StChain/StMaker.h"

#include "StHighPtEvaluator/IsGoodTrack.h"

#include "PhiMaker.h"
#include "RawSpectraMaker.h"
#include "StV0GeometricCuts.h"
#include "StXiGeometricCuts.h"


class CutMaker : public StMaker {
 public:
  CutMaker(char *mydataset, AnalysisMaker *myAnalysisMaker);
  CutMaker(char *mydataset, AnalysisMaker *myAnalysisMaker, StV0GeometricCuts *myV0CutMaker);
  CutMaker(char *mydataset, AnalysisMaker *myAnalysisMaker, StXiGeometricCuts *myXiCutMaker);
  CutMaker(char *mydataset, AnalysisMaker *myAnalysisMaker, StV0GeometricCuts *myV0CutMaker, StXiGeometricCuts *myXiCutMaker);
  ~CutMaker(){;}

  //Required maker functions
  void   Clear(Option_t *option="") {StMaker::Clear();}    
  Int_t  Init();                      
  Int_t  Make();//This will be empty because tracks must be added to the maker by another maker
  Int_t  Finish();    
  void WriteTIdentified(){writeTIdentified = true;}
  void WriteV0s(){writeV0s = true;}
  void WriteXis(){writeXis = true;}
  void WriteTResonances(){writeTRes = true;}
  void SetDcaXiToPV(int partID, float cut);
  void SetDcaV0ToPV(int partID, float cut);
  void SetDcaNegToPV(int partID, float cut);
  void SetDcaPosToPV(int partID, float cut);
  void SetDcaBachToPV(int partID, float cut);
  void SetDcaV0Daughters(int partID, float cut);
  void SetDcaXiDaughters(int partID, float cut);
  void SetNHitsNeg(int partID, float cut);
  void SetNHitsPos(int partID, float cut);
  void SetNHitsBach(int partID, float cut);
  void SetNSigmaNeg(int partID, float cut);
  void SetNSigmaPos(int partID, float cut);
  void SetNSigmaBach(int partID, float cut);
  void SetV0DecayLength(int partID, float cut);
  void SetXiDecayLength(int partID, float cut);

 private:
  float DcaV0ToPV[7];//lambda, antilambda, K0s, xi, anti-xi, omega, anti-omega
  float DcaXiToPV[7];//lambda, antilambda, K0s, xi, anti-xi, omega, anti-omega
  float DcaNegToPV[7];
  float DcaPosToPV[7];
  float DcaBachToPV[7];
  float DcaV0Daughters[7];
  float DcaXiDaughters[7];
  int NHitsNeg[7];
  int NHitsPos[7];
  int NHitsBach[7];
  float NSigmaNeg[7];
  float NSigmaPos[7];
  float NSigmaBach[7];
  float V0DecayLength[7];
  float XiDecayLength[7];
  int GetArrayIndex(int partID);
  
  int GetCutNum(int partID);

  string dataset;
  AnalysisMaker *anaMaker;
  StV0GeometricCuts *v0CutMaker;
  StXiGeometricCuts *xiCutMaker;
  //PhiMaker *phiMaker;
  //RawSpectraMaker *ptMaker;
  //booleans to control what actually gets written
  bool writeTIdentified, writeV0s, writeXis, writeTRes;
  ClassDef(CutMaker,1)
};
#endif
