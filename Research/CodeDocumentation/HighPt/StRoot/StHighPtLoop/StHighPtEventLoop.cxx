#include "StHighPtEventLoop.h"
ClassImp(StHighPtEventLoop)
//initializing static strings which hold information on data set
string  StHighPtEventLoop::CuCu200 = "CuCu200";
string  StHighPtEventLoop::AuAu200Y2 = "AuAu200Y2";
string  StHighPtEventLoop::AuAu200 = "AuAu200";
string  StHighPtEventLoop::CuCu62 = "CuCu62";
string  StHighPtEventLoop::AuAu62 = "AuAu62";
string  StHighPtEventLoop::dAu200 = "dAu200";

StHighPtEventLoop::StHighPtEventLoop(char *infilename, char *mydataset){
  //I don't know what type off Event Loop it will be yet
  IsTEvent = false;
  IsStEvent = false;
  //The default is not to use any particles
  for(int i = 0; i<100; i++){useParticle[i]=false;}
  //the default is to use the default cuts (duh)
  useDefaultEventCuts = true;
  //set the StHighPtEventLoop's data set to the one passed
  dataset = mydataset;
  //set default triggers to those for the data set using the function goodTriggers in the StHighPtEvaluator library
 SetDefaultTriggers();
 //Initialize pointers to NULL
 SetNullPointers();

 //Set the number of events to 0
 nevent = 0;
 
 //Here I will make a muDstMaker but I will delete it if I don't have a MuDst
 muDstMaker = new StMuDstMaker(0,0,"",infilename,"",100);//Maximum number of files is 100
 muDstMaker->Init();
 infile = new TFile(infilename,"infile");
 if(infile){cout<<"Opened file "<<infilename<<endl;}
 else{cerr<<"Unable to open file "<<infilename<<endl;}
}
void StHighPtEventLoop::SetDefaultTriggers(){
  int *defaultTrigs = goodTriggers(dataset);
  for(int i = 0;i<10;i++){triggers[i] = defaultTrigs[i];}
}
void StHighPtEventLoop::GetEvents(){
  if(infile){
    if(infile->Get("Correlation")){//this fetches the TTree from a file containing a TTree
      delete muDstMaker;//If I have a TTree named "Correlation" I don't need to read events through a StMuDstMaker
      IsTEvent = true;
      //copied out of Jana's MyDPhiMakerNe
      tree = dynamic_cast<TTree*>(infile->Get("Correlation"));
      event = new TEvent();   //object must be created before setting the branch address
      branch  = tree->GetBranch("Event");
      branch->SetAddress(&event);
      v0s = new TV0();
      branchV0 = tree->GetBranch("V0");
      branchV0->SetAddress(&v0s);
      nevent = tree->GetEntries();
      cout<<" This file contains a TTree."<<endl;
      cout << "The tree contains " << nevent  << " events" << endl;
      cout << "Starting the analysis ..." << endl;
      int nEventsPassed = 0;
      int nEventsFailed = 0;
      for (Int_t i=0;i<nevent;i++) {
	tree->GetEvent(i);                  //read complete accepted event in memory
	if(IsGoodEvent(dataset, event)){
	  nEventsPassed++;
	  if(i%1000==0) { cout<<i<<" events processed.  Passed: "<<nEventsPassed<<"  Failed: "<<nEventsFailed<<endl;}
	  //analysis here
	}
	else{
	  nEventsFailed++;
	}
      }
    }
    else{
      if(infile->Get("MuDst")){
	cout<<"This file contains a MuDst."<<endl;
	IsStEvent = true;
	muDstMaker->Make();
      }
    }
  }
  else{cerr<<"Unable to get events out of this file"<<endl;}
  muDstMaker->Finish();
}
void StHighPtEventLoop::SetNullPointers(){//Sets pointers I might not need to NULL
  //Things for reading a TTree
  tree = NULL;
  event = NULL;
  branch = NULL;
  v0s = NULL;
  branchV0 = NULL;

  //Things for reading a MuDst
  muDstMaker = NULL;
}


void StHighPtEventLoop::DeleteJunk(){
  delete tree;
  delete event;
  delete branch;
  delete v0s;
  delete branchV0;

  delete muDstMaker;
}


bool StHighPtEventLoop::AcceptEvent(TEvent *myevent){
  if(useDefaultEventCuts){return IsGoodEvent(dataset,myevent);}
  else {return false;}
}
