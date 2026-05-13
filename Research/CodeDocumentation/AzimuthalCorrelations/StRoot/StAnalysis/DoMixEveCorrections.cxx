#include "DoMixEveCorrections.h"
void DoMixEveCorrections(char *infile, string dataset, char *outfile){
  static int CentBin = 1;//Jana showed that mixed events didn't need to be done by centrality
  static float triggerCuts[4][2] = {2.0,3.0,
				  3.0,4.0,
				  4.0,5.0,
				  5.0,10};
  static float highPtAssocCuts[4][2] = {1.0,1.5,
				      1.5,2.0,
				      2.0,3.0,
				      3.0,10};
  static float lowPtAssocCuts[4][2] = {.2,.4,
				     .4,.6,
				     .6,.8,
				     .8,1.0};
  static float phiDistCuts[7][2] ={2.0,3.0,
				 3.0,4.0,
				 4.0,5.0,
				 5.0,10,
				 1.0,1.5,
				 1.5,2.0,
				 3.0,10};
  
  static int maxNParticles = 24;
  static int numPhiDistCuts = 7;
  static int numLowPtCuts = 4;
  static int numTrigCuts = 4;
  static int numAssocCuts = 4;
  TFile *file = new TFile(infile);
  TFile *outFile = new TFile(outfile,"RECREATE");
  file->cd();
  TDirectory *phi = (TDirectory*)file->Get("PhiDistributions");
  TDirectory *outCorrelations = (TDirectory*)file->Get("CorrectedCorrelations");
  //make a directory for the correlations in the output file
  outFile->cd();
  TDirectory *correlations = new TDirectory("Correlations","Correlations");
  file->cd();
  if(phi && correlations){//make sure the directory exists
    for(int trigPartNum = 0; trigPartNum<maxNParticles;trigPartNum++){
      correlations->cd();
      TDirectory *triggerCorrDir = (TDirectory*)correlations->Get( Form("Trigger_%s",GetSimpleParticleName(trigPartNum)) );
      if(triggerCorrDir){
	//make a directory for the trigger in the correlations
	//outCorrelations->cd();
	//TDirectory *outTriggerCorrDir = new TDirectory( Form("Trigger_%s",GetSimpleParticleName(trigPartNum)), Form("Trigger_%s",GetSimpleParticleName(trigPartNum)) );
	triggerCorrDir->cd();
	for(int assocPartNum = 0; assocPartNum<maxNParticles;assocPartNum++){
	  TDirectory *assocCorrDir = (TDirectory*)triggerCorrDir->Get( Form("Associated_%s",GetSimpleParticleName(assocPartNum)) );
	  for(int trigCutNum = 0;  trigCutNum<numTrigCuts; trigCutNum++){
	    if(assocCorrDir){
	      assocCorrDir->cd();
	      TDirectory *trigCutCorrDir = assocCorrDir->Get( Form("TrigPt%i-%i",(int)(triggerCuts[trigCutNum][0]*10),(int)(triggerCuts[trigCutNum][1]*10)) );
	      if(trigCutCorrDir){
		trigCutCorrDir->cd();




		//==============================  High Pt Associated Cuts  ================================

		for(int assocCutNum=0;assocCutNum<numAssocCuts;assocCutNum++){//low pt associated cuts
		  TDirectory *assocCorrCutDir = trigCutCorrDir->Get( Form("AssocPt%i-%i",(int)(highPtAssocCuts[assocCutNum][0]*10),(int)(highPtAssocCuts[assocCutNum][1]*10)) );//make directory for trigger particle
		  if(assocCorrCutDir){
		    assocCorrCutDir->cd();//change to that directory
		    TDirectory *phiTrig = phi->Get( GetSimpleParticleName( trigPartNum)  );
		    if(phiTrig){
		      phiTrig->cd();
		      TDirectory *TrigpTcutDir = phiTrig->Get( Form("Pt%i-%i",(int)(10*triggerCuts[trigCutNum][0]),(int)(10*triggerCuts[trigCutNum][1])) );
		      if(TrigpTcutDir){
			char *trigname = GetPhiHistoName( trigPartNum , triggerCuts[trigCutNum][0] , triggerCuts[trigCutNum][1] ,CentBin);
			TH1F *trigPhiDist = TrigpTcutDir->Get(trigname);
			if(trigPhiDist){
			  TDirectory *phiAssoc = phi->Get(GetSimpleParticleName(assocPartNum) );
			  if(phiAssoc){
			    phiAssoc->cd();
			    TDirectory *AssocpTcutDir = phiAssoc->Get( Form("Pt%i-%i",(int)(10*highPtAssocCuts[assocCutNum][0]),(int)(10*highPtAssocCuts[assocCutNum][1])) );
			    if(AssocpTcutDir){
			      char *assocname = GetPhiHistoName( assocPartNum , highPtAssocCuts[assocCutNum][0] , highPtAssocCuts[assocCutNum][1] ,CentBin);
			      AssocpTcutDir->cd();
			      TH1F *assocPhiDist = AssocpTcutDir->Get(assocname);
			      char *npartname = GetNPartHistoName( assocPartNum , highPtAssocCuts[assocCutNum][0] , highPtAssocCuts[assocCutNum][1] ,CentBin);
			      TH1I *assocNPart = AssocpTcutDir->Get(npartname);
			      if(assocNPart && assocPhiDist && trigPhiDist->GetEntries()>0 && assocPhiDist->GetEntries()>0 && assocNPart->GetEntries()>0){
				cout<<"Doing mixed events for trigger "<<GetSimpleParticleName(trigPartNum)<<" "<<triggerCuts[trigCutNum][0]<<"<pT<"<<triggerCuts[trigCutNum][1]<<" associated "<<GetSimpleParticleName(assocPartNum)<<" "<<highPtAssocCuts[assocCutNum][0]<<"<pT<"<<highPtAssocCuts[assocCutNum][1]<<endl;
				assocCorrCutDir->cd();
				char *mixevename = GetMixedEventHistoName(trigPartNum, triggerCuts[trigCutNum][0], triggerCuts[trigCutNum][1],assocPartNum, highPtAssocCuts[assocCutNum][0], highPtAssocCuts[assocCutNum][1], CentBin);
				char *mixevetitle = GetMixedEventHistoTitle(dataset,trigPartNum, triggerCuts[trigCutNum][0], triggerCuts[trigCutNum][1],assocPartNum, highPtAssocCuts[assocCutNum][0], highPtAssocCuts[assocCutNum][1], CentBin);
				//TH1F *mixedevent = MixedEvents(trigPhiDist,assocPhiDist,assocNPart,mixevename,mixevetitle);
			      }
			    }
			  }
			}
		      }  
		    }
		  }
		}





		//===============================  Low Pt Associated Cuts  ================================

		for(int assocCutNum=0;assocCutNum<numLowPtCuts;assocCutNum++){//low pt associated cuts
		  TDirectory *assocCorrCutDir = trigCutCorrDir->Get( Form("AssocPt%i-%i",(int)(lowPtAssocCuts[assocCutNum][0]*10),(int)(lowPtAssocCuts[assocCutNum][1]*10)) );//make directory for trigger particle
		  if(assocCorrCutDir){
		    assocCorrCutDir->cd();//change to that directory
		    TDirectory *phiTrig = phi->Get( GetSimpleParticleName( trigPartNum)  );
		    if(phiTrig){
		      phiTrig->cd();
		      TDirectory *TrigpTcutDir = phiTrig->Get( Form("Pt%i-%i",(int)(10*triggerCuts[trigCutNum][0]),(int)(10*triggerCuts[trigCutNum][1])) );
		      if(TrigpTcutDir){
			char *trigname = GetPhiHistoName( trigPartNum , triggerCuts[trigCutNum][0] , triggerCuts[trigCutNum][1] ,CentBin);
			TH1F *trigPhiDist = TrigpTcutDir->Get(trigname);
			if(trigPhiDist){
			  TDirectory *phiAssoc = phi->Get(GetSimpleParticleName(assocPartNum) );
			  if(phiAssoc){
			    phiAssoc->cd();
			    TDirectory *AssocpTcutDir = phiAssoc->Get( Form("Pt%i-%i",(int)(10*lowPtAssocCuts[assocCutNum][0]),(int)(10*lowPtAssocCuts[assocCutNum][1])) );
			    if(AssocpTcutDir){
			      char *assocname = GetPhiHistoName( assocPartNum , lowPtAssocCuts[assocCutNum][0] , lowPtAssocCuts[assocCutNum][1] ,CentBin);
			      AssocpTcutDir->cd();
			      TH1F *assocPhiDist = AssocpTcutDir->Get(assocname);
			      char *npartname = GetNPartHistoName( assocPartNum , lowPtAssocCuts[assocCutNum][0] , lowPtAssocCuts[assocCutNum][1] ,CentBin);
			      TH1I *assocNPart = AssocpTcutDir->Get(npartname);
			      if(assocNPart && assocPhiDist && trigPhiDist->GetEntries()>0 && assocPhiDist->GetEntries()>0 && assocNPart->GetEntries()>0){
				cout<<"Doing mixed events for trigger "<<GetSimpleParticleName(trigPartNum)<<" "<<triggerCuts[trigCutNum][0]<<"<pT<"<<triggerCuts[trigCutNum][1]<<" associated "<<GetSimpleParticleName(assocPartNum)<<" "<<lowPtAssocCuts[assocCutNum][0]<<"<pT<"<<lowPtAssocCuts[assocCutNum][1]<<endl;
				assocCorrCutDir->cd();
				char *mixevename = GetMixedEventHistoName(trigPartNum, triggerCuts[trigCutNum][0], triggerCuts[trigCutNum][1],assocPartNum, lowPtAssocCuts[assocCutNum][0], lowPtAssocCuts[assocCutNum][1], CentBin);
				char *mixevetitle = GetMixedEventHistoTitle(dataset,trigPartNum, triggerCuts[trigCutNum][0], triggerCuts[trigCutNum][1],assocPartNum, lowPtAssocCuts[assocCutNum][0], lowPtAssocCuts[assocCutNum][1], CentBin);
				//TH1F *mixedevent = MixedEvents(trigPhiDist,assocPhiDist,assocNPart,mixevename,mixevetitle);
			      }
			    }
			  }
			}
		      }  
		    }
		  }
		}





	      }
	    }
	  }
	}
      }else{cerr<<" Oh no!  Your file is missing either correlations or phi distributions!  Doh! "<<endl;}
    }
  }
  outFile->Write();
  outFile->Close();
}
			
