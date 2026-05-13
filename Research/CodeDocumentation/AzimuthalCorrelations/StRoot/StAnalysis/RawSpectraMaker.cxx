#include "RawSpectraMaker.h"

ClassImp(RawSpectraMaker)
RawSpectraMaker::RawSpectraMaker(char *mydataset){	       
  dataset = mydataset;
  fileName = "junk.root";
  histoList = new TObjArray();
}

Int_t RawSpectraMaker::Init(){
  file =  new TFile(fileName, "RECREATE","HistoFile");
  cout << "The output filename is " << fileName << endl;
  BookParticleHistos();
  return StMaker::Init();
}

Int_t RawSpectraMaker::Make(){//This does nothing because tracks must be added to the maker by an external maker
  return kStOk;
}
Int_t RawSpectraMaker::Finish(){
  file->Write();
  file->Close();
  return kStOk;
}

void RawSpectraMaker::CreateHisto1D(char name[100], char title[100], char xtitle[100], char ytitle[100],Int_t xbins, Float_t xlow,Float_t xhigh)
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
void RawSpectraMaker::FillHisto1D(char histname[100], Float_t x)
{
  TH1F     *histo; 
  TString  *name   = new TString();
  
  name->Append(histname);       
  histo = (TH1F *)histoList->FindObject(name->Data()); 
  histo->Fill((Double_t)x);
  delete name;
}

void RawSpectraMaker::BookParticleHistos(){
  int numCentBins = NumberOfCentralityBins((char*)dataset.c_str());
  for(int partID = 0; partID <24; partID++){//part IDs 0-23 have been allocated
    TDirectory *particleDir = file->mkdir( GetSimpleParticleName(partID) );
    particleDir->cd();
    for(int centBin = 1; centBin <= numCentBins; centBin++){
      char *name = GetSpectraHistoName(partID, centBin);
      char *title = GetSpectraHistoTitle(dataset,partID, centBin);
      float maxpt = 7.;
      CreateHisto1D(name,title,"p_{T}","number of entries",1200,0.,maxpt);
    }
  }
}
void RawSpectraMaker::FillPhiHisto(int partID, float pt, int centBin){
  char *name = GetSpectraHistoName(partID, centBin);
  FillHisto1D(name, pt);
}
