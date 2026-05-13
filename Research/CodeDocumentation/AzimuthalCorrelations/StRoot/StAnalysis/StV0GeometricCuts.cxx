#include "StV0GeometricCuts.h"
float StV0GeometricCuts::highPtCuts[2][2]={1.0,2.0,  2.0,10.0};
float StV0GeometricCuts::lowPtCuts[2][4] = {.2,.4,.6,.8,  .4,.6,.8,1.0};
int StV0GeometricCuts::numHighPtCuts = 2;
int StV0GeometricCuts::numLowPtCuts = 4;
int StV0GeometricCuts::numCutHistos = 9;
int StV0GeometricCuts::numParticles = 3;
int StV0GeometricCuts::nBins = 200;
float StV0GeometricCuts::histoBoundsX[3][2] = {1.08,1.15,
					      1.08,1.15,
					      .44,.56};
//[cut number][partID][ylow/yhigh]
//order of cuts:
// 1 DcaV0ToPV
// 2 DcaNegToPV
// 3 DcaPosToPV
// 4 DcaDaughters
// 5 NHitsNeg
// 6 NHitsPos
// 7 NSigmaNeg
// 8 DecayLength
// 9 NSigmaPos
// 10 Mass
float StV0GeometricCuts::histoBoundsY[9][3][2] = {0,2.,     0,2.,     0,2.,
						  0,6,      0,6,      0,6,
						  0,6,      0,6,      0,6,
						  0,1.0,    0,1.0,    0,1.0,          
						  0,50,     0,50,     0,50,
						  0,50,     0,50,     0,50,
						  0,5,      0,5,      0,5,
						  0,50,     0,50,     0,50,
						  0,5,      0,5,      0,5};

ClassImp(StV0GeometricCuts)
StV0GeometricCuts::StV0GeometricCuts(char *mydataset){	       
  dataset = mydataset;
  fileName = "junk.root";
  histoList = new TObjArray();
  doLowPt = false;
}

Int_t StV0GeometricCuts::Init(){
  file =  new TFile(fileName, "RECREATE","HistoFile");
  cout << "The output filename is " << fileName << endl;
  BookParticleHistos();
  return StMaker::Init();
}

Int_t StV0GeometricCuts::Make(){//This does nothing because tracks must be added to the maker by an external maker
  return kStOk;
}
Int_t StV0GeometricCuts::Finish(){
  file->Write();
  file->Close();
  return kStOk;
}

void StV0GeometricCuts::CreateHisto2D(char name[100], char title[100], char xtitle[100], char ytitle[100],Int_t xbins, Float_t xlow,Float_t xhigh,Int_t ybins, Float_t ylow,Float_t yhigh)
{     
  TString *histoname   = new TString();
  TString *histotitle   = new TString();
  
  histoname->Append(name);
  histotitle->Append(title);
  // printf("%s \n ",histoname->Data());
  TH2F *histo = new TH2F(histoname->Data(),histotitle->Data(),xbins,xlow,xhigh,ybins,ylow,yhigh);
  histo->SetYTitle(ytitle);
  histo->SetXTitle(xtitle);
  //histo->Sumw2();
  histoList->Add(histo);
  delete histoname;
  delete histotitle;
    
}
void StV0GeometricCuts::CreateHisto1D(char name[100], char title[100], char xtitle[100], char ytitle[100],Int_t xbins, Float_t xlow,Float_t xhigh)
{     
  TString *histoname   = new TString();
  TString *histotitle   = new TString();
  
  histoname->Append(name);
  histotitle->Append(title);
  // printf("%s \n ",histoname->Data());
  TH1F *histo = new TH1F(histoname->Data(),histotitle->Data(),xbins,xlow,xhigh);
  histo->SetYTitle(ytitle);
  histo->SetXTitle(xtitle);
  histo->Sumw2();
  histoList->Add(histo);
  delete histoname;
  delete histotitle;
    
}
void StV0GeometricCuts::FillHisto1D(char histname[100], Float_t x)
{
  TH1F     *histo; 
  TString  *name   = new TString();
  
  name->Append(histname);       
  histo = (TH1F *)histoList->FindObject(name->Data()); 
  if(histo){
    histo->Fill((Double_t)x);
  }
  else{cerr<<"StV0GeometricCuts::FillHisto1D : unable to find "<<name->Data()<<endl;}
  delete name;
}
void StV0GeometricCuts::FillHisto2D(char histname[100], Float_t x, Float_t y)
{
  TH2F     *histo; 
  TString  *name   = new TString();
  
  name->Append(histname);       
  histo = (TH2F *)histoList->FindObject(name->Data()); 
  if(histo){
    histo->Fill((Double_t)x, (Double_t)y);
  }
  else{cerr<<"StV0GeometricCuts::FillHisto1D : unable to find "<<name->Data()<<endl;}
  delete name;
}

void StV0GeometricCuts::BookParticleHistos(){
  float mypi = TMath::Pi();
  //Three types of V0s, lambda (1), antilambda (2), K0s (3)
  //we will make 3 directories, one for each particle
  //(since any low pt associated V0s will have to have cuts tuned specially.  Sigh.)
  //low pt:
  //.2-.4 GeV, .4-.6 GeV, .6-.8 GeV, and .8-1.0 GeV
  //high pt:
  //1.0-2.0 GeV, >2.0 GeV
  //These cuts are similar to the analysis ranges
  //Each V0 will have 10 2-D histograms:
  //mass vs dca daughters
  //mass vs dca of v0 to PV
  //mass vs dca of neg/pos daughter to PV
  //mass vs decay length
  //mass vs nHits of neg/pos daughter
  //mass vs nSigma of neg/pos daughter
   for(int partID = 1; partID <=numParticles; partID++){//part IDs 0-23 have been allocated
     TDirectory *particleDir = file->mkdir( GetSimpleParticleName(partID) );
     particleDir->cd();

     for(int ptCutNum=0;ptCutNum<numHighPtCuts;ptCutNum++){
       for(int histoNum = 1; histoNum<=numCutHistos;histoNum++){
	 char *xTitle = "Mass";
	 char *yTitle = GetV0GeometricCutHistoYTitle(histoNum);
	 char *title = GetV0GeometricCutHistoTitle(histoNum, partID, highPtCuts[0][ptCutNum]+.1);
	 char *name = GetV0GeometricCutHistoName(histoNum, partID, highPtCuts[0][ptCutNum]+.1);
	 //cerr<<name<<" "<<nBins<<" "<<histoBoundsX[partID-1][0]<<" "<<histoBoundsX[partID-1][1]<<" "<<nBins<<" "<<histoBoundsY[histoNum-1][partID-1][0]<<" "<<histoBoundsY[histoNum-1][partID-1][1]<<endl;
	 CreateHisto2D(name,title,xTitle,yTitle,nBins,histoBoundsX[partID-1][0],histoBoundsX[partID-1][1],nBins,histoBoundsY[histoNum-1][partID-1][0],histoBoundsY[histoNum-1][partID-1][1]);
       }
       int histoNum = 10;
       char *name = GetV0GeometricCutHistoName(histoNum, partID, highPtCuts[0][ptCutNum]+.1);
       char *xTitle = "Mass";
       char *yTitle = GetV0GeometricCutHistoYTitle(histoNum);
       char *title = GetV0GeometricCutHistoTitle(histoNum, partID, highPtCuts[0][ptCutNum]+.1);
       CreateHisto1D(name,title,xTitle,yTitle,nBins,histoBoundsX[partID-1][0],histoBoundsX[partID-1][1]);
     }

     if(doLowPt){
       for(int ptCutNum=0;ptCutNum<numLowPtCuts;ptCutNum++){
	 for(int histoNum = 1; histoNum<=numCutHistos;histoNum++){
	   char *xTitle = "Mass";
	   char *yTitle = GetV0GeometricCutHistoYTitle(histoNum);
	   char *title = GetV0GeometricCutHistoTitle(histoNum, partID, lowPtCuts[0][ptCutNum]+.1);
	   char *name = GetV0GeometricCutHistoName(histoNum, partID, lowPtCuts[0][ptCutNum]+.1);
	   CreateHisto2D(name,title,xTitle,yTitle,nBins,histoBoundsX[partID-1][0],histoBoundsX[partID-1][1],nBins,histoBoundsY[histoNum-1][partID-1][0],histoBoundsY[histoNum-1][partID-1][1]);
	 }
	 int histoNum = 10;
	 char *name = GetV0GeometricCutHistoName(histoNum, partID, lowPtCuts[0][ptCutNum]+.1);
	 char *xTitle = "Mass";
	 char *yTitle = GetV0GeometricCutHistoYTitle(histoNum);
	 char *title = GetV0GeometricCutHistoTitle(histoNum, partID, lowPtCuts[0][ptCutNum]+.1);
	 CreateHisto1D(name,title,xTitle,yTitle,nBins,histoBoundsX[partID-1][0],histoBoundsX[partID-1][1]);
       }
     }


   }
}

void StV0GeometricCuts::FillCutHistos(int partID, float pt,float mass, float DcaV0ToPV, float DcaNeg, float DcaPos, float DcaDaughters, float NHitsNeg, float NHitsPos, float NSigNeg, float NSigPos, float DecayLength){
  FillHisto2D(GetV0GeometricCutHistoName(1, partID, pt),mass,DcaV0ToPV);
  FillHisto2D(GetV0GeometricCutHistoName(2, partID, pt),mass,DcaNeg);
  FillHisto2D(GetV0GeometricCutHistoName(3, partID, pt),mass,DcaPos);
  FillHisto2D(GetV0GeometricCutHistoName(4, partID, pt),mass,DcaDaughters);
  FillHisto2D(GetV0GeometricCutHistoName(5, partID, pt),mass,NHitsNeg);
  FillHisto2D(GetV0GeometricCutHistoName(6, partID, pt),mass,NHitsPos);
  FillHisto2D(GetV0GeometricCutHistoName(7, partID, pt),mass,NSigNeg);
  FillHisto2D(GetV0GeometricCutHistoName(8, partID, pt),mass,DecayLength);
  FillHisto2D(GetV0GeometricCutHistoName(9, partID, pt),mass,NSigPos);
  FillHisto1D(GetV0GeometricCutHistoName(10, partID, pt),mass);
}
// void StV0GeometricCuts::FillPhiHisto(int partID, float pt, float phi, int centBin){
//   char *name = GetPhiHistoName(partID, pt, centBin);
//   FillHisto1D(name, phi);
// }
