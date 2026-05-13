#include "StXiGeometricCuts.h"
float StXiGeometricCuts::highPtCuts[2][2]={1.0,2.0,  2.0,10.0};
float StXiGeometricCuts::lowPtCuts[2][4] = {.2,.4,.6,.8,  .4,.6,.8,1.0};
int StXiGeometricCuts::numHighPtCuts = 2;
int StXiGeometricCuts::numLowPtCuts = 4;
int StXiGeometricCuts::numCutHistos = 15;
int StXiGeometricCuts::numParticles = 4;
int StXiGeometricCuts::nBins = 200;
float StXiGeometricCuts::histoBoundsX[4][2] = {1.25,1.5,
					      1.5,1.9,
					       1.25,1.5,
					      1.5,1.9};
float StXiGeometricCuts::v0MassBounds[2]={1.1,1.2};
//[cut number][partID][ylow/yhigh]
//order of cuts:
// 1 DcaXiToPV
// 2 DcaV0ToPV
// 3 DcaNegToPV
// 4 DcaPosToPV
// 5 DcaBachToPV
// 6 DcaXiDaughters
// 7 DcaV0Daughters
// 8 NHitsNeg
// 9 NHitsPos
// 10 NHitsBach
// 11 NSigmaNeg
// 12 NSigmaPos
// 13 NSigmaBach
// 14 V0DecayLength
// 15 XiDecayLength
// 16 V0Mass
// 17 XiMass
float StXiGeometricCuts::histoBoundsY[15][4][2] = {0,.8,     0,.8,     0,.8,     0,.8,
						   0,2.,     0,2.,     0,2.,     0,2.,
						   0,20,     0,20,     0,20,     0,20,
						   0,20,     0,20,     0,20,     0,20,
						   0,20,     0,20,     0,20,     0,20,
						   0,.8,     0,.8,     0,.8,     0,.8,  
						   0,.8,     0,.8,     0,.8,     0,.8,
						   0,50,     0,50,     0,50,     0,50,
						   0,50,     0,50,     0,50,     0,50,
						   0,50,     0,50,     0,50,     0,50,
						   0,10,     0,10,     0,10,     0,10,
						   0,10,     0,10,     0,10,     0,10,
						   0,10,     0,10,     0,10,     0,10,
						   0,50,     0,50,     0,50,     0,50,
						   0,20,     0,20,     0,20,     0,20};

ClassImp(StXiGeometricCuts)
StXiGeometricCuts::StXiGeometricCuts(char *mydataset){	       
  dataset = mydataset;
  fileName = "junk.root";
  histoList = new TObjArray();
  doLowPt = false;
}

Int_t StXiGeometricCuts::Init(){
  file =  new TFile(fileName, "RECREATE","HistoFile");
  cout << "The output filename is " << fileName << endl;
  BookParticleHistos();
  return StMaker::Init();
}

Int_t StXiGeometricCuts::Make(){//This does nothing because tracks must be added to the maker by an external maker
  return kStOk;
}
Int_t StXiGeometricCuts::Finish(){
  file->Write();
  file->Close();
  return kStOk;
}

void StXiGeometricCuts::CreateHisto2D(char name[100], char title[100], char xtitle[100], char ytitle[100],Int_t xbins, Float_t xlow,Float_t xhigh,Int_t ybins, Float_t ylow,Float_t yhigh)
{     
  TString *histoname   = new TString();
  TString *histotitle   = new TString();
  //cerr<<"creating "<<name<<endl;
  
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
void StXiGeometricCuts::CreateHisto1D(char name[100], char title[100], char xtitle[100], char ytitle[100],Int_t xbins, Float_t xlow,Float_t xhigh)
{     
  TString *histoname   = new TString();
  TString *histotitle   = new TString();
  //cerr<<"creating "<<name<<endl;
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
void StXiGeometricCuts::FillHisto1D(char histname[100], Float_t x)
{
  TH1F     *histo; 
  TString  *name   = new TString();
  
  name->Append(histname);       
  histo = (TH1F *)histoList->FindObject(name->Data()); 
  if(histo){
    histo->Fill((Double_t)x);
  }
  else{cerr<<"StXiGeometricCuts::FillHisto1D : unable to find "<<name->Data()<<endl;}
  delete name;
}
void StXiGeometricCuts::FillHisto2D(char histname[100], Float_t x, Float_t y)
{
  TH2F     *histo; 
  TString  *name   = new TString();
  
  name->Append(histname);       
  histo = (TH2F *)histoList->FindObject(name->Data()); 
  if(histo){
    histo->Fill((Double_t)x, (Double_t)y);
  }
  else{cerr<<"StXiGeometricCuts::FillHisto1D : unable to find "<<name->Data()<<endl;}
  delete name;
}

void StXiGeometricCuts::BookParticleHistos(){
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
     int index = GetArrayIndex(partID);
     TDirectory *particleDir = file->mkdir( GetSimpleParticleName(index) );
     particleDir->cd();

     for(int ptCutNum=0;ptCutNum<numHighPtCuts;ptCutNum++){
       for(int histoNum = 1; histoNum<=numCutHistos;histoNum++){
	 char *xTitle = "Mass";
	 char *yTitle = GetXiGeometricCutHistoYTitle(histoNum);
	 char *title = GetXiGeometricCutHistoTitle(histoNum, index, highPtCuts[0][ptCutNum]+.1);
	 char *name = GetXiGeometricCutHistoName(histoNum, index, highPtCuts[0][ptCutNum]+.1);
	 //cerr<<name<<" "<<partID<<" "<<index<<" "<<nBins<<" "<<histoBoundsX[partID-1][0]<<" "<<histoBoundsX[partID-1][1]<<" "<<nBins<<" "<<histoBoundsY[histoNum-1][partID-1][0]<<" "<<histoBoundsY[histoNum-1][partID-1][1]<<endl;
	 CreateHisto2D(name,title,xTitle,yTitle,nBins,histoBoundsX[partID-1][0],histoBoundsX[partID-1][1],nBins,histoBoundsY[histoNum-1][partID-1][0],histoBoundsY[histoNum-1][partID-1][1]);
       }
       //V0 mass histo
       int histoNum = 16;
       char *name = GetXiGeometricCutHistoName(histoNum, index, highPtCuts[0][ptCutNum]+.1);
       char *xTitle = "Mass";
       char *yTitle = GetXiGeometricCutHistoYTitle(histoNum);
       char *title = GetXiGeometricCutHistoTitle(histoNum, index, highPtCuts[0][ptCutNum]+.1);
       //cerr<<name<<" "<<partID<<" "<<index<<" "<<nBins<<" "<<histoBoundsX[partID-1][0]<<" "<<histoBoundsX[partID-1][1]<<" "<<nBins<<endl;
       CreateHisto1D(name,title,xTitle,yTitle,nBins,v0MassBounds[0],v0MassBounds[1]);
       //Xi mass histo
       histoNum = 17;
       name = GetXiGeometricCutHistoName(histoNum, index, highPtCuts[0][ptCutNum]+.1);
       xTitle = "Mass";
       yTitle = GetXiGeometricCutHistoYTitle(histoNum);
       title = GetXiGeometricCutHistoTitle(histoNum, index, highPtCuts[0][ptCutNum]+.1);
       //cerr<<name<<" "<<partID<<" "<<index<<" "<<nBins<<" "<<histoBoundsX[partID-1][0]<<" "<<histoBoundsX[partID-1][1]<<" "<<nBins<<endl;
       CreateHisto1D(name,title,xTitle,yTitle,nBins,histoBoundsX[partID-1][0],histoBoundsX[partID-1][1]);
     }

     if(doLowPt){
       for(int ptCutNum=0;ptCutNum<numLowPtCuts;ptCutNum++){
	 for(int histoNum = 1; histoNum<=numCutHistos;histoNum++){
	   //cerr<<"ptCutNum "<<ptCutNum<<" histoNum "<<histoNum<<" pt "<<lowPtCuts[0][ptCutNum]+.1<<endl;
	   char *xTitle = "Mass";
	   char *yTitle = GetXiGeometricCutHistoYTitle(histoNum);
	   char *title = GetXiGeometricCutHistoTitle(histoNum, index, lowPtCuts[0][ptCutNum]+.1);
	   char *name = GetXiGeometricCutHistoName(histoNum, index, lowPtCuts[0][ptCutNum]+.1);
	   //cerr<<name<<" "<<partID<<" "<<index<<" "<<nBins<<" "<<histoBoundsX[partID-1][0]<<" "<<histoBoundsX[partID-1][1]<<" "<<nBins<<" "<<histoBoundsY[histoNum-1][partID-1][0]<<" "<<histoBoundsY[histoNum-1][partID-1][1]<<endl;
	   CreateHisto2D(name,title,xTitle,yTitle,nBins,histoBoundsX[partID-1][0],histoBoundsX[partID-1][1],nBins,histoBoundsY[histoNum-1][partID-1][0],histoBoundsY[histoNum-1][partID-1][1]);
	 }
	 int histoNum = 16;
	 char *name = GetXiGeometricCutHistoName(histoNum, index, lowPtCuts[0][ptCutNum]+.1);
	 char *xTitle = "V^{0} Mass";
	 char *yTitle = GetXiGeometricCutHistoYTitle(histoNum);
	 char *title = GetXiGeometricCutHistoTitle(histoNum, index, lowPtCuts[0][ptCutNum]+.1);
	 CreateHisto1D(name,title,xTitle,yTitle,nBins,v0MassBounds[0],v0MassBounds[1]);

	 histoNum = 17;
	 name = GetXiGeometricCutHistoName(histoNum, index, lowPtCuts[0][ptCutNum]+.1);
	 xTitle = Form("%s Mass",GetParticleName(index));
	 yTitle = GetXiGeometricCutHistoYTitle(histoNum);
	 title = GetXiGeometricCutHistoTitle(histoNum, index, lowPtCuts[0][ptCutNum]+.1);
	 CreateHisto1D(name,title,xTitle,yTitle,nBins,histoBoundsX[partID-1][0],histoBoundsX[partID-1][1]);
       }
     }


   }
}

void StXiGeometricCuts::FillCutHistos(int partID, float pt,float Ximass,float V0mass, float DcaXiToPV, float DcaV0ToPV, float DcaNeg, float DcaPos, float DcaBach, float DcaXiDaughters, float DcaV0Daughters, float NHitsNeg, float NHitsPos, float NHitsBach, float NSigNeg, float NSigPos, float NSigBach, float V0DecayLength, float XiDecayLength){
//void StXiGeometricCuts::FillCutHistos(int partID, float pt,float mass, float DcaV0ToPV, float DcaNeg, float DcaPos, float DcaDaughters, float NHitsNeg, float NHitsPos, float NSigNeg, float NSigPos, float DecayLength){
  FillHisto2D(GetXiGeometricCutHistoName(1, partID, pt),Ximass,DcaXiToPV);
  FillHisto2D(GetXiGeometricCutHistoName(2, partID, pt),Ximass,DcaV0ToPV);
  FillHisto2D(GetXiGeometricCutHistoName(3, partID, pt),Ximass,DcaNeg);
  FillHisto2D(GetXiGeometricCutHistoName(4, partID, pt),Ximass,DcaPos);
  FillHisto2D(GetXiGeometricCutHistoName(5, partID, pt),Ximass,DcaBach);
  FillHisto2D(GetXiGeometricCutHistoName(6, partID, pt),Ximass,DcaXiDaughters);
  FillHisto2D(GetXiGeometricCutHistoName(7, partID, pt),Ximass,DcaV0Daughters);
  FillHisto2D(GetXiGeometricCutHistoName(8, partID, pt),Ximass,NHitsNeg);
  FillHisto2D(GetXiGeometricCutHistoName(9, partID, pt),Ximass,NHitsPos);
  FillHisto2D(GetXiGeometricCutHistoName(10, partID, pt),Ximass,NHitsBach);
  FillHisto2D(GetXiGeometricCutHistoName(11, partID, pt),Ximass,NSigNeg);
  FillHisto2D(GetXiGeometricCutHistoName(12, partID, pt),Ximass,NSigPos);
  FillHisto2D(GetXiGeometricCutHistoName(13, partID, pt),Ximass,NSigBach);
  FillHisto2D(GetXiGeometricCutHistoName(14, partID, pt),Ximass,V0DecayLength);
  FillHisto2D(GetXiGeometricCutHistoName(15, partID, pt),Ximass,XiDecayLength);
  //cout<<"filling "<<GetXiGeometricCutHistoName(16, partID, pt)<<" with "<<V0mass<<endl;
  FillHisto1D(GetXiGeometricCutHistoName(16, partID, pt),V0mass);
  //cout<<"filling "<<GetXiGeometricCutHistoName(17, partID, pt)<<" with "<<Ximass<<endl;
  FillHisto1D(GetXiGeometricCutHistoName(17, partID, pt),Ximass);
}
// void StV0GeometricCuts::FillPhiHisto(int partID, float pt, float phi, int centBin){
//   char *name = GetPhiHistoName(partID, pt, centBin);
//   FillHisto1D(name, phi);
// }

int StXiGeometricCuts::GetArrayIndex(int partID){
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
