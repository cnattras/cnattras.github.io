//____________________________________________________________________
//
// Using Pythia6 with ROOT
// To make an event sample (of size 100) do
//
//    shell> root
//    root [0] .L pythiaExample.C
//    root [1] makeEventSample(1000)
//
// To start the tree view on the generated tree, do
//
//    shell> root
//    root [0] .L pythiaExample.C
//    root [1] showEventSample()
//
//
// The following session:
//    shell> root
//    root [0] .x pythiaExample.C(500)
// will execute makeEventSample(500) and showEventSample()
//
// Alternatively, you can compile this to a program
// and then generate 1000 events with
//
//    ./pythiaExample 1000
//
// To use the program to start the viewer, do
//
//    ./pythiaExample -1
//
// NOTE 1: To run this example, you must have a version of ROOT
// compiled with the Pythia6 version enabled and have Pythia6 installed.
// The statement gSystem->Load("$HOME/pythia6/libPythia6");  (see below)
// assumes that the directory containing the Pythia6 library
// is in the pythia6 subdirectory of your $HOME.  Locations
// that can specify this, are:
//
//  Root.DynamicPath resource in your ROOT configuration file
//    (/etc/root/system.rootrc or ~/.rootrc).
//  Runtime load paths set on the executable (Using GNU ld,
//    specified with flag `-rpath').
//  Dynamic loader search path as specified in the loaders
//    configuration file (On GNU/Linux this file is
//    etc/ld.so.conf).
//  For Un*x: Any directory mentioned in LD_LIBRARY_PATH
//  For Windows: Any directory mentioned in PATH
//
// NOTE 2: The example can also be run with ACLIC:
//  root > gSystem->Load("libEG");
//  root > gSystem->Load("$ROOTSYS/../pythia6/libPythia6"); //change to your setup
//  root > gSystem->Load("libEGPythia6");
//  root > .x pythiaExample.C+
//
//
//____________________________________________________________________
//
// Author: Christian Holm Christensen <cholm@hilux15.nbi.dk>
// Update: 2002-08-16 16:40:27+0200
// Copyright: 2002 (C) Christian Holm Christensen
// Copyright (C) 2006, Rene Brun and Fons Rademakers.
// For the licensing terms see $ROOTSYS/LICENSE.
//
#ifndef __CINT__
#include "TApplication.h"
#include "TPythia6.h"
#include "TFile.h"
#include "TError.h"
#include "TTree.h"
#include "TClonesArray.h"
#include "TH1.h"
#include "TF1.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TCanvas.h"
#include "Riostream.h"
#include <cstdlib>
#include "TH3F.h"
#include "TH2F.h"
#include "TH1F.h"
#include "TMath.h"
#include "TMCParticle.h"
#include <TSystem.h>
using namespace std;
#endif

#define FILENAME   "pythia.root"
#define TREENAME   "tree"
#define BRANCHNAME "particles"
#define HISTNAME   "ptSpectra"
#define PDGNUMBER  211
class TH3F;
class TH1F;
class TPythia6;

// This function just load the needed libraries if we're executing from
// an interactive session.
int test(){
return 0;
}

TH3F *CreateHistogram(char *name){
  //assoc pt, trig pt, dphi
  TH3F *histo = new TH3F(name,name,20,1.0,6.0,20,2.0,7.0,144,-TMath::Pi(),TMath::Pi());
  histo->GetXaxis()->SetTitle("p_{T}^{assoc}");
  histo->GetYaxis()->SetTitle("p_{T}^{trig}");
  histo->GetZaxis()->SetTitle("#Delta#phi");
  return histo;
}
TH1F *CreateTriggerHistogram(char *name){
  //assoc pt, trig pt, dphi
  TH1F *histo = new TH1F(name,name,20,2.0,7.0);
  histo->GetYaxis()->SetTitle("N_{trig}");
  histo->GetXaxis()->SetTitle("p_{T}^{trig}");
  return histo;
}
Double_t dPhi(Double_t phi1, Double_t phi2) {
  Double_t deltaPhi;
  deltaPhi = phi1 - phi2;
  if (deltaPhi>TMath::Pi()) deltaPhi-=2*(TMath::Pi());
  if (deltaPhi<-TMath::Pi()) deltaPhi+=2*(TMath::Pi());  
  return deltaPhi;
}

void loadLibraries()
{
#ifdef __CINT__
  // Load the Event Generator abstraction library, Pythia 6
  // library, and the Pythia 6 interface library.
  gSystem->Load("libEG");
//gSystem->Load("/data/rhip/alice/cnattras/pythia6/libPythia6");
//gSystem->Load("$PYTHIA6/pythia6_common_address");
      gSystem->Load("$PYTHIA6/pythia6416.o");
  gSystem->Load("$ROOTSYS/../pythia6/libPythia6"); //change to your setup
  gSystem->Load("libEGPythia6");
  cout<<"loading libraries..."<<endl;
#endif
}

// nEvents is how many events we want.
int makeEventSample(Int_t nEvents, Int_t jobID, Int_t tune)
{
  cout<<"I made it here, running "<<nEvents<<" events, job id "<<jobID<<", tune "<<tune<<endl;
  char *filename = Form("/tmp/outfile%i.root",jobID);
  // Load needed libraries
  //loadLibraries();
//  gSystem->Load("$PYTHIA6/pythia6_common_address");
  //gSystem->Load("$PYTHIA6/pythia6416.o");
  gSystem->Load("$PYTHIA6/libPythia6"); //change to your setup
  gSystem->Load("libEGPythia6");
  //cout<<"loading libraries..."<<endl;

  //cout<<"I made it here line 144"<<endl;
  TString piplus = "pi+";
  TString piminus = "pi-";
  TString kplus = "K+";
  TString kminus = "K-";
  TString pplus = "p+";
  TString pminus = "pbar-";
  TString kshort = "K_S0";
  TString lambda = "Lambda0";
  TString antilambda = "Lambdabar0";

  //cout<<"I made it here line 155"<<endl;
  // Create an instance of the Pythia event generator ...
  TPythia6* pythia = new TPythia6();


  // set the random seed

  UInt_t seed = (jobID+1)*17;
  if( (seed>=0) && (seed<=900000000) ) {
    pythia->SetMRPY(1, seed);			// set seed
    pythia->SetMRPY(2, 0);			// use new seed
    cout<<"Random Seed : "<<seed<<endl; 
  } else {cout << "error: time " << seed << " is not valid" << endl; exit(2);}


  //cout<<"I made it here line 157"<<endl;
  //turn on decays
  //pythia->SetMSTJ(21,2);
  //pythia->SetMSTJ(22,1);
  //add switches for tunes
//   switch(tune){
//   case 0:
//     //tune A
//     cout<<"Using Tune A"<<endl;
//     pythia->SetPARP(67,4.0);           // Regulates Initial State Radiation (value from best fit to D0 dijet analysis)
//     //pythia->SetMSTP(81,1);             // Double Gaussian Model
//     //pythia->SetMSTP(82,4);             // Double Gaussian Model
//     pythia->SetPARP(82,2.0);           // [GeV]    PT_min at Ref. energy
//     pythia->SetPARP(83,0.5);           // Core radius
//     pythia->SetPARP(84,0.4);           // Core radius
//     pythia->SetPARP(85,0.90) ;         // Regulates gluon prod. mechanism
//     pythia->SetPARP(86,0.95);          // Regulates gluon prod. mechanism
//     pythia->SetPARP(89,1800.);         // [GeV]   Ref. energy
//     pythia->SetPARP(90,0.25);          // 2*epsilon (exponent in power law)
//     //pythia->SetPARP(91,2.0);          // 2*epsilon (exponent in power law)
//     break;
//   }
  pythia->SetMSTP(5,tune);//TuneA


  // ... and initialise it to run p+p at sqrt(200) GeV in CMS
  pythia->Initialize("cms", "p", "p", 200);
  //pythia->Dump();
  // Open an output file

  //cout<<"I made it here line 180"<<endl;
  TFile* file = TFile::Open(filename, "RECREATE");
  if (!file || !file->IsOpen()) {
    Error("makeEventSample", "Couldn;t open file %s", filename);
    return 1;
  }


    TFile *outfile = new TFile(filename,"RECREATE");
    TH3F *hUnidentifiedCorrelations = CreateHistogram("hUnidentifiedCorrelations");
    TH3F *hK0Correlations = CreateHistogram("hK0Correlations");
    TH3F *hLambdaCorrelations = CreateHistogram("hLambdaCorrelations");
    TH3F *hK0AssocCorrelations = CreateHistogram("hK0AssocCorrelations");
    TH3F *hLambdaAssocCorrelations = CreateHistogram("hLambdaAssocCorrelations");


    TH1F *hUnidentifiedTriggers = CreateTriggerHistogram("hUnidentifiedTriggers");
    TH1F *hK0Triggers = CreateTriggerHistogram("hK0Triggers");
    TH1F *hLambdaTriggers = CreateTriggerHistogram("hLambdaTriggers");


    TH3F *hPiCorrelations = CreateHistogram("hPiCorrelations");
    TH3F *hPiAssocCorrelations = CreateHistogram("hPiAssocCorrelations");
    TH1F *hPiTriggers = CreateTriggerHistogram("hPiTriggers");
    TH3F *hProtonCorrelations = CreateHistogram("hProtonCorrelations");
    TH3F *hProtonAssocCorrelations = CreateHistogram("hProtonAssocCorrelations");
    TH1F *hProtonTriggers = CreateTriggerHistogram("hProtonTriggers");
    TH3F *hKCorrelations = CreateHistogram("hKCorrelations");
    TH3F *hKAssocCorrelations = CreateHistogram("hKAssocCorrelations");
    TH1F *hKTriggers = CreateTriggerHistogram("hKTriggers");


    TH1F *hNEvents = new TH1F("hNEvents","Number of events",1,0,1.0);
    hNEvents->GetYaxis()->SetTitle("N_{events}");
    hNEvents->GetXaxis()->SetTitle("no title");
    TH1F *hDistVtx = new TH1F("hDistVtx","log of radius of vertex position",100,0,1e-4);
    hDistVtx->GetYaxis()->SetTitle("N_{events}");
    hDistVtx->GetXaxis()->SetTitle("no title");

    Float_t binBoundaries[35] = {0.0,0.1,0.2,0.3,0.4,  0.5,0.6,0.7,0.8,0.9,  1.0,1.2,1.4,1.6,1.8, 2.0,2.25,2.5,2.75,3.0,  3.25,3.5,3.75,4.0,4.25,  4.5,4.75,5.0,5.25,5.5,  5.75,6.0,6.25,6.5,6.75};
    Int_t nbins = 34;
    TH1F *hK0Spectra = new TH1F("hK0Spectra","K^0_{S} spectra",nbins,binBoundaries);
    TH1F *hLamSpectra = new TH1F("hLamSpectra","#Lambda spectra",nbins,binBoundaries);
    TH1F *hAntiLamSpectra = new TH1F("hAntiLamSpectra","#bar{#Lambda} spectra",nbins,binBoundaries);


    Float_t lamTrigPt[2][25] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
    Float_t k0TrigPt[2][25] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
    Float_t hTrigPt[2][25] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
    Float_t piTrigPt[2][25] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
    Float_t kTrigPt[2][25] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
    Float_t pTrigPt[2][25] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
    Int_t hPartNumber[25] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    Int_t hPiPartNumber[25] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    Int_t hKPartNumber[25] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    Int_t hPPartNumber[25] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    Int_t nLamTrig, nK0Trig, nHTrig, nPiTrig, nKTrig, nPTrig;
    Int_t maxNtrig = 25;


    pythia->SetPtCut(1.0);//Don't bother with particles below 1 GeV since we don't use them anyways.
  // Make a tree in that file ...
  //TTree* tree = new TTree(TREENAME, "Pythia 6 tree");

  // ... and register a the cache of pythia on a branch (It's a
  // TClonesArray of TMCParticle objects. )
    //we are only interested in primary particles
    TClonesArray* particles = (TClonesArray*)pythia->GetPrimaries();//GetListOfParticles();
  //tree->Branch(BRANCHNAME, &particles);
  //cout<<"I made it here line 235"<<endl;
  // Now we make some events
  for (Int_t event = 0; event < nEvents; event++) {
    // Show how far we got every 100'th event.
    if (event % 100 == 0)
      cout << "Event # " << event << endl;

    // Make one event.
    pythia->GenerateEvent();

      hNEvents->Fill(0.5);
      nLamTrig = 0;
      nK0Trig = 0;
      nHTrig = 0;
      nPiTrig = 0;
      nKTrig = 0;
      nPTrig = 0;
      for(int i=0;i<25;i++){
	for(int j=0;j<2;j++){
	  lamTrigPt[j][i] = 0;
	  k0TrigPt[j][i] = 0;
	  hTrigPt[j][i] = 0;
	  piTrigPt[j][i] = 0;
	  kTrigPt[j][i] = 0;
	  pTrigPt[j][i] = 0;
	}
      }


      Int_t npart = particles->GetEntries();
      //printf("Analyse %d Particles\n", npart);
      for (Int_t part=0; part<npart; part++) {
	//TObject *object = particles->At(part);
	//cout<<"I am a "<<object->ClassName()<<endl;
	TMCParticle *MPart = (TMCParticle *) particles->At(part);
	Double_t pt= TMath::Sqrt(MPart->GetPx() * MPart->GetPx() + MPart->GetPy() * MPart->GetPy()); 
	Double_t phi = TMath::Pi()+TMath::ATan2(-MPart->GetPy(),-MPart->GetPx());
	Double_t p =  TMath::Sqrt(MPart->GetPx() * MPart->GetPx() + MPart->GetPy() * MPart->GetPy() +  MPart->GetPz() * MPart->GetPz()); 
	Double_t eta = 0.5*TMath::Log((p+MPart->GetPz())/(p-MPart->GetPz()));
	Double_t vtx =  TMath::Sqrt(MPart->GetVx() * MPart->GetVx() + MPart->GetVy() * MPart->GetVy() +  MPart->GetVz() * MPart->GetVz()); 
	//cout<<"vtx ("<<MPart->GetVx()<<","<<MPart->GetVy()<<","<<MPart->GetVz()<<")"<<endl;
	//cout<<"phi "<<phi<<" pt "<<pt<<" p "<<p<<" eta "<<eta<<endl;
	//if(MPart && MPart->GetPDG()) cout<<MPart->GetPDG()->GetName()<<endl;
	//hDistVtx->Fill(TMath::Log(vtx));
	//cout<<"vtx "<<vtx<<" log(vtx) "<<TMath::Log(vtx)<<endl;
	TString mpart = MPart->GetName();
	if(mpart==kshort &&  TMath::Abs(eta)<0.5){//K0S
	  hK0Spectra->Fill(pt);
	}
	if(mpart==lambda && TMath::Abs(eta)<0.5){//K0S
	  hLamSpectra->Fill(pt);
	}
	if(mpart==antilambda && TMath::Abs(eta)<0.5){//K0S
	  hAntiLamSpectra->Fill(pt);
	}
	if(pt>2.0 && TMath::Abs(eta)<1.0 && vtx<1e-4){//select only particles which may be triggers in our acceptance which also are primary particles
	  //Int_t mpart  = MPart->GetPdgCode();
	  //cout<<"Part ID "<<mpart;
	  //cout<<" MPart name "<<MPart->GetName();
	  //if(MPart->GetPDG())cout<<" code "<<MPart->GetPDG()->PdgCode();
	  //cout<<endl;
	  if(mpart==kshort && nK0Trig<maxNtrig){//K0S
	    k0TrigPt[0][nK0Trig] = pt;
	    k0TrigPt[1][nK0Trig] = phi;
	    //cout<<"Kaon pt "<<pt<<" "<< k0TrigPt[0][nK0Trig] <<endl;
	    nK0Trig++;
	    hK0Triggers->Fill(pt);
	    //printf("Particle %d\n", mpart);
	  }
	  if((mpart==lambda || mpart==antilambda) && nLamTrig<maxNtrig){//Lambda
	    //printf("Particle %d\n", mpart);
	    lamTrigPt[0][nLamTrig] =pt;
	    lamTrigPt[1][nLamTrig] = phi;
	    nLamTrig++;
	    hLambdaTriggers->Fill(pt);
	  }
	  if((mpart==piplus || mpart==piminus || mpart==kplus || mpart==kminus || mpart==pplus || mpart==pminus)  && nHTrig<maxNtrig){//pi+- or p/pbar or K+-
	    hTrigPt[0][nHTrig] =pt;
	    hTrigPt[1][nHTrig] = phi;
	    hPartNumber[nHTrig] = part;
	    nHTrig++;
	    hUnidentifiedTriggers->Fill(pt);
	    if((mpart==piplus || mpart==piminus) && nPiTrig<maxNtrig){//pi
	      piTrigPt[0][nPiTrig] =pt;
	      piTrigPt[1][nPiTrig] = phi;
	      hPiPartNumber[nPiTrig] = part;
	      nPiTrig++;
	      hPiTriggers->Fill(pt);
	    }
	    if((mpart==pplus || mpart==pminus) && nPTrig<maxNtrig){//p/pbar
	      pTrigPt[0][nPTrig] =pt;
	      pTrigPt[1][nPTrig] = phi;
	      hPPartNumber[nPTrig] = part;
	      nPTrig++;
	      hProtonTriggers->Fill(pt);
	    }
	    if((mpart==kplus || mpart==kminus) && nKTrig<maxNtrig){//K+-
	      kTrigPt[0][nKTrig] =pt;
	      kTrigPt[1][nKTrig] = phi;
	      hKPartNumber[nKTrig] = part;
	      nKTrig++;
	      hKTriggers->Fill(pt);
	    }
	  }
	}
      }//end particle loop

      if(nLamTrig>0 || nK0Trig>0 || nHTrig>0){//if any of the trigger particles have triggers, then and only then do we associate with particles
	for (Int_t part=0; part<npart; part++) {
	  TMCParticle *MPart = (TMCParticle *) particles->At(part);
	  Double_t pt= TMath::Sqrt(MPart->GetPx() * MPart->GetPx() + MPart->GetPy() * MPart->GetPy()); 
	  Double_t phi = TMath::Pi()+TMath::ATan2(-MPart->GetPy(),-MPart->GetPx());
	  Double_t p =  TMath::Sqrt(MPart->GetPx() * MPart->GetPx() + MPart->GetPy() * MPart->GetPy() +  MPart->GetPz() * MPart->GetPz()); 
	  Double_t eta = 0.5*TMath::Log((p+MPart->GetPz())/(p-MPart->GetPz()));
	Double_t vtx =  TMath::Sqrt(MPart->GetVx() * MPart->GetVx() + MPart->GetVy() * MPart->GetVy() +  MPart->GetVz() * MPart->GetVz()); 
	  if(pt>1.0 && TMath::Abs(eta)<1.0 && vtx<1e-4){
	    hDistVtx->Fill(vtx);
	    //Int_t mpart  = MPart->GetPdgCode();
	    TString mpart = MPart->GetName();
	    if((mpart==piplus || mpart==piminus || mpart==kplus || mpart==kminus || mpart==pplus || mpart==pminus)){//for all charged pi/K/p
	      for(int i=0;i<nK0Trig;i++){
		if(k0TrigPt[0][i]>pt){
		  hK0Correlations->Fill(pt,k0TrigPt[0][i],dPhi(k0TrigPt[1][i],phi));
		}
	      }
	      for(int i=0;i<nLamTrig;i++){
		if(lamTrigPt[0][i]>pt){
		  hLambdaCorrelations->Fill(pt,lamTrigPt[0][i],dPhi(lamTrigPt[1][i],phi));
		}
	      }
	      for(int i=0;i<nHTrig;i++){
		if(hTrigPt[0][i]>pt){
		  if(part!=hPartNumber[i]){//don't correlate with itself.  This is only necessary for h-h correlations
		    hUnidentifiedCorrelations->Fill(pt,hTrigPt[0][i],dPhi(hTrigPt[1][i],phi));
		    if(mpart==piplus || mpart==piminus){//pi assoc
		      hPiAssocCorrelations->Fill(pt,hTrigPt[0][i],dPhi(hTrigPt[1][i],phi));
		    }
		    if(mpart==pplus || mpart==pminus){//p/pbar assoc
		      hProtonAssocCorrelations->Fill(pt,hTrigPt[0][i],dPhi(hTrigPt[1][i],phi));
		    }
		    if(mpart==kplus || mpart==kminus){//K+- assoc
		      hKAssocCorrelations->Fill(pt,hTrigPt[0][i],dPhi(hTrigPt[1][i],phi));
		    }
		  }
		}
	      }
	      for(int i=0;i<nPiTrig;i++){
		if(piTrigPt[0][i]>pt){
		  if(part!=hPiPartNumber[i]){//don't correlate with itself.  This is only necessary for h-h correlations
		    hPiCorrelations->Fill(pt,piTrigPt[0][i],dPhi(piTrigPt[1][i],phi));
		  }
		}
	      }
	      for(int i=0;i<nPTrig;i++){
		if(pTrigPt[0][i]>pt){
		  if(part!=hPPartNumber[i]){//don't correlate with itself.  This is only necessary for h-h correlations
		    hProtonCorrelations->Fill(pt,pTrigPt[0][i],dPhi(pTrigPt[1][i],phi));
		  }
		}
	      }
	      for(int i=0;i<nKTrig;i++){
		if(kTrigPt[0][i]>pt){
		  if(part!=hKPartNumber[i]){//don't correlate with itself.  This is only necessary for h-h correlations
		    hKCorrelations->Fill(pt,kTrigPt[0][i],dPhi(kTrigPt[1][i],phi));
		  }
		}
	      }
	    }
	    if(mpart==kshort){//Kaon
	      for(int i=0;i<nHTrig;i++){
		if(hTrigPt[0][i]>pt){
		  hK0AssocCorrelations->Fill(pt,hTrigPt[0][i],dPhi(hTrigPt[1][i],phi));
		}
	      }
	    }
	    if(mpart==lambda || mpart==antilambda){//Lambda
	      for(int i=0;i<nHTrig;i++){
		if(hTrigPt[0][i]>pt){
		  hLambdaAssocCorrelations->Fill(pt,hTrigPt[0][i],dPhi(hTrigPt[1][i],phi));
		}
	      }
	    }
	  }
	}//end particle loop
      }
    // Maybe you want to have another branch with global event
    // information.  In that case, you should process that here.
    // You can also filter out particles here if you want.

    // Now we're ready to fill the tree, and the event is over.
    //tree->Fill();
  }

  // Show tree structure
  //tree->Print();

    outfile->Write();
    outfile->Close();
  return 0;
}

// Show the Pt spectra, and start the tree viewer.
int showEventSample()
{
  // Load needed libraries
  loadLibraries();

  // Open the file
  TFile* file = TFile::Open(FILENAME, "READ");
  if (!file || !file->IsOpen()) {
    Error("showEventSample", "Couldn;t open file %s", FILENAME);
    return 1;
  }

  // Get the tree
  TTree* tree = (TTree*)file->Get(TREENAME);
  if (!tree) {
    Error("showEventSample", "couldn't get TTree %s", TREENAME);
    return 2;
  }

  // Start the viewer.
  tree->StartViewer();

  // Get the histogram
  TH1D* hist = (TH1D*)file->Get(HISTNAME);
  if (!hist) {
    Error("showEventSample", "couldn't get TH1D %s", HISTNAME);
    return 4;
  }

  // Draw the histogram in a canvas
  gStyle->SetOptStat(1);
  TCanvas* canvas = new TCanvas("canvas", "canvas");
  canvas->SetLogy();
  hist->Draw("e1");
  TF1* func = hist->GetFunction("expo");

  char expression[64];
  sprintf(expression,"T #approx %5.1f", -1000 / func->GetParameter(1));
  TLatex* latex = new TLatex(1.5, 1e-4, expression);
  latex->SetTextSize(.1);
  latex->SetTextColor(4);
  latex->Draw();

  return 0;
}

void pythiaExample(Int_t n=1000, Int_t jobID=0, Int_t tune = 0) {
  makeEventSample(n,jobID,tune);
  //showEventSample();
}

#ifndef __CINT__
int main(int argc, char** argv)
{
  TApplication app("app", &argc, argv);

  Int_t n = 100;
  if (argc > 1)
    n = strtol(argv[1], NULL, 0);

  int retVal = 0;
  if (n > 0)
    retVal = makeEventSample(n,0,0);
  else {
    retVal = showEventSample();
    app.Run();
  }

  return retVal;
}
#endif

//____________________________________________________________________
//
// EOF
//

