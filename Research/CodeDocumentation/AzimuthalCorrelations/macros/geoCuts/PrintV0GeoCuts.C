
float highPtCuts[2][2]={1.0,2.0,  2.0,10.0};
float lowPtCuts[2][4] = {.2,.4,.6,.8,  .4,.6,.8,1.0};
int numHighPtCuts = 2;
int numLowPtCuts = 4;
int numCutHistos = 9;
int numParticles = 3;
int nBins = 200;
float histoBoundsX[3][2] = {1.08,1.15,
					      1.08,1.15,
					      .44,.56};
//int GetArrayIndex(int partID);
void PrintV0GeoCuts(char *infile){
  gROOT->LoadMacro("~nattrass/HighPt/macros/loadHighPtLibraries.C");
  loadHighPtLibraries();
  gSystem->Load("StAnalysisTools");
  gSystem->Load("StAnalysis");
  gROOT->LoadMacro("~nattrass/AzimuthalCorrelations/macros/tools/SetRootStyles.C");
  SetRootStyles();
  file = new TFile(infile);
  for(int partID = 1; partID <=numParticles; partID++){//part IDs 0-23 have been allocated
    //int index = GetArrayIndex(partID);
    int index = partID;
    TDirectory *particleDir = file->Get( GetSimpleParticleName(index) );
    particleDir->cd();
    cout<<GetSimpleParticleName(index)<<endl;
    for(int ptCutNum=0;ptCutNum<numHighPtCuts;ptCutNum++){
      cout<<ptCutNum<<endl;
      for(int histoNum = 1; histoNum<=numCutHistos;histoNum++){
	cout<<" "<<histoNum<<endl;
	char *name = GetV0GeometricCutHistoName(histoNum, index, highPtCuts[0][ptCutNum]+.1);
	TH2F *histo = particleDir->Get(name);
	if(histo){//try to print the histogram if it exists.  If it doesn't this won't crash the code.
	  TCanvas *c1 = new TCanvas("c1","c1",500,400);
	  c1->cd();  
	  c1->SetGridx(kFALSE);
	  c1->SetGridy(kFALSE);
	  histo->Draw("COLZ");
	  c1->Print( Form("geoCuts/%s/%s.eps",GetSimpleParticleName(index),name) );
	}
      }
      //V0 mass histo
      int histoNum = 10;
      char *name = GetV0GeometricCutHistoName(histoNum, index, highPtCuts[0][ptCutNum]+.1);
      TH1F *histo1 = particleDir->Get(name);
      if(histo1){//try to print the histogram if it exists.  If it doesn't this won't crash the code.
	TCanvas *c1 = new TCanvas("c1","c1",500,400);
	TCanvas *c1 = new TCanvas("c1","c1",500,400);
	c1->cd();  
	c1->SetGridx(kFALSE);
	c1->SetGridy(kFALSE);
	histo1->Draw("");
	c1->Print( Form("geoCuts/%s/%s.eps",GetSimpleParticleName(index),name) );
      }
    }

    for(int ptCutNum=0;ptCutNum<numLowPtCuts;ptCutNum++){
      for(int histoNum = 1; histoNum<=numCutHistos;histoNum++){
	char *name = GetV0GeometricCutHistoName(histoNum, index, lowPtCuts[0][ptCutNum]+.1);
	TH2F *histo3 = particleDir->Get(name);
	if(histo3){//try to print the histogram if it exists.  If it doesn't this won't crash the code.
	  TCanvas *c1 = new TCanvas("c1","c1",500,400);
	  c1->cd();  
	  c1->SetGridx(kFALSE);
	  c1->SetGridy(kFALSE);
	  histo3->Draw("COLZ");
	  c1->Print( Form("geoCuts/%s/%s.eps",GetSimpleParticleName(index),name) );
	}
      }
      int histoNum = 10;
      char *name = GetV0GeometricCutHistoName(histoNum, index, lowPtCuts[0][ptCutNum]+.1);
      TH1F *histo4 = particleDir->Get(name);
      if(histo4){//try to print the histogram if it exists.  If it doesn't this won't crash the code.
	TCanvas *c1 = new TCanvas("c1","c1",500,400);
	TCanvas *c1 = new TCanvas("c1","c1",500,400);
	c1->cd();  
	c1->SetGridx(kFALSE);
	c1->SetGridy(kFALSE);
	histo4->Draw("");
	c1->Print( Form("geoCuts/%s/%s.eps",GetSimpleParticleName(index),name) );
      }
    }
  }


}


int GetArrayIndex(int partID){
  switch(partID){
  case 1:
    return 4;
  case 2:
    return 5;
  case 3:
    return 18;
  case 4:
    return 19;
  default:
    return -1;
  }
  return -1;
}
