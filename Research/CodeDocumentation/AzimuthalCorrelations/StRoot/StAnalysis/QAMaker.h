#ifndef QAMaker_h
#define QAMaker_h

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

#include "StHighPtEvaluator/IsGoodTrack.h"

#include "PhiMaker.h"
#include "RawSpectraMaker.h"


class QAMaker : public StMaker {
 public:
  QAMaker(char *mydataset, AnalysisMaker *myAnalysisMaker, PhiMaker *myPhiMaker, RawSpectraMaker *myPtMaker);
  ~QAMaker(){;}

  //Required maker functions
  void   Clear(Option_t *option="") {StMaker::Clear();}    
  Int_t  Init();                      
  Int_t  Make();//This will be empty because tracks must be added to the maker by another maker
  Int_t  Finish();    
  void WriteTIdentified(){writeTIdentified = true;}
  void WriteV0s(){writeV0s = true;}
  void WriteXis(){writeXis = true;}
  void WriteTResonances(){writeTRes = true;}

 private:
  string dataset;
  AnalysisMaker *anaMaker;
  PhiMaker *phiMaker;
  RawSpectraMaker *ptMaker;
  //booleans to control what actually gets written
  bool writeTIdentified, writeV0s, writeXis, writeTRes;
  ClassDef(QAMaker,1)
};
#endif
