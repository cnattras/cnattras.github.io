void SetPtAssocRange(TH3 *histo,Float_t assoclow, Float_t assochigh){
  Int_t lowbin = histo->GetXaxis()->FindBin(assoclow+0.01);
  Int_t highbin = histo->GetXaxis()->FindBin(assochigh-0.01);
  histo->GetXaxis()->SetRange(lowbin,highbin);
}
void SetPtTrigRange(TH3 *histo,Float_t assoclow, Float_t assochigh){
  Int_t lowbin = histo->GetYaxis()->FindBin(assoclow+0.01);
  Int_t highbin = histo->GetYaxis()->FindBin(assochigh-0.01);
  histo->GetYaxis()->SetRange(lowbin,highbin);
}
Float_t FindMinimum(TH1 *histo, Float_t &err){
  Float_t min = histo->GetBinContent(1);
  err = histo->GetBinError(1);
  for(int i=2;i<=histo->GetNbinsX();i++){
    if(histo->GetBinContent(i)<min){
      min = histo->GetBinContent(i);
      err = histo->GetBinError(i);
    }
  }
  return min;
}
TF1 *GetBackground(TH1 *histo, char *name, Float_t &err){
  TF1 *background = new TF1(name,"[0]",-TMath::Pi(),TMath::Pi());
  background->SetParameter(0,FindMinimum(histo,err));
  return background;
}
void SubtractBackground(TH1 *histo,Float_t &err){
  TF1 *background = GetBackground(histo,"junk",err);
  histo->Add(background,-1);
  delete background;
}
Float_t CalculateYield(TH1 *histo,Float_t & yielderr){
  //Float_t yielderr = 0;
  Float_t dphicut = 1.0;
  Float_t bkgderr = 0.0;
  SubtractBackground(histo,bkgderr);
  Float_t yield = histo->IntegralAndError( histo->FindBin(-dphicut), histo->FindBin(dphicut),yielderr,"width");
  float scaleerr = bkgderr*(histo->FindBin(dphicut)-histo->FindBin(-dphicut)+1)* histo->GetBinWidth(1);
  //cout<<"yield "<<yield<<" yielderr "<<yielderr<<" bkgderr "<<bkgderr<<" scaleerr "<<scaleerr;
  if(bkgderr>0) yielderr = TMath::Sqrt(TMath::Power(yielderr,2)+TMath::Power(scaleerr,2));
  //cout<<" final err "<<yielderr<<endl;
  return yield;

}
Float_t CalculateYieldForPtTrig(TH3 *histo3D, TH1 *trighisto, Int_t ybin, Int_t ybin2, Float_t& yielderr){
  histo3D->GetYaxis()->SetRange(ybin,ybin2);
  TH1D *histo = histo3D->Project3D("z");
  histo->SetName("junk");
  histo->Sumw2();
  //Float_t ntriggers = trighisto->GetBinContent(trighisto->FindBin(histo3D->GetYaxis()->GetBinCenter(ybin)));
  Float_t ntriggers = trighisto->Integral(trighisto->FindBin(histo3D->GetYaxis()->GetBinCenter(ybin)),trighisto->FindBin(histo3D->GetYaxis()->GetBinCenter(ybin2)));
  histo->Rebin(3.0);
  Float_t scale = 1.0/(ntriggers * histo->GetBinWidth(1));
  if(ntriggers>0){
    histo->Scale(scale);
  }
  Float_t yield = CalculateYield(histo,yielderr);
  delete histo;
  return yield;
}
Float_t CalculateYieldForPtAssoc(TH3 *histo3D, TH1 *trighisto,Int_t xbin,Float_t triglow, Float_t trighigh, Float_t& yielderr){
  histo3D->GetYaxis()->SetRange(xbin,xbin);
  TH1D *histo = histo3D->Project3D("z");
  histo->SetName("junk");
  histo->Sumw2();
  Float_t ntriggers = trighisto->Integral(trighisto->FindBin(triglow+0.01),trighisto->FindBin(trighigh-0.01));
  //Float_t ntriggers = trighisto->GetBinContent(trighisto->FindBin(histo3D->GetYaxis()->GetBinCenter(ybin)));
  histo->Rebin(3.0);
  Float_t scale = 1.0/(ntriggers * histo->GetBinWidth(1));
  if(ntriggers>0){
    histo->Scale(scale);
  }
  Float_t yield = CalculateYield(histo,yielderr);
  delete histo;
  return yield;
}
TH1D * GetHistogramForPtTrig(TH3 *histo3D, TH1 *trighisto, Int_t ybin, Float_t& yielderr){
  histo3D->GetYaxis()->SetRange(ybin,ybin);
  TH1D *histo = histo3D->Project3D("z");
  histo->SetName("junk");
  histo->Sumw2();
  Float_t ntriggers = trighisto->GetBinContent(trighisto->FindBin(histo3D->GetYaxis()->GetBinCenter(ybin)));
  histo->Rebin(3.0);
  Float_t scale = 1.0/(ntriggers * histo->GetBinWidth(1));
  if(ntriggers>0){
    histo->Scale(scale);
  }
  Float_t yield = CalculateYield(histo,yielderr);
  return histo;
}
Float_t CalculateYieldForNPart(TH3 *histo3D, TH1 *trighisto,Float_t triglow, Float_t trighigh, Float_t& yielderr){
  TH1D *histo = histo3D->Project3D("z");
  histo->SetName("junk");
  histo->Sumw2();
  //Float_t ntriggers = trighisto->GetBinContent(trighisto->FindBin(histo3D->GetYaxis()->GetBinCenter(ybin)));
  Float_t ntriggers = trighisto->Integral(trighisto->FindBin(triglow+0.01),trighisto->FindBin(trighigh-0.01));
  histo->Rebin(3.0);
  Float_t scale = 1.0/(ntriggers * histo->GetBinWidth(1));
  if(ntriggers>0){
    histo->Scale(scale);
  }
  Float_t yield = CalculateYield(histo,yielderr);
  delete histo;
  return yield;
}
TH1D * GetHistogramForNPart(TH3 *histo3D, TH1 *trighisto,Float_t triglow, Float_t trighigh, Float_t& yielderr){
  TH1D *histo = histo3D->Project3D("z");
  histo->SetName("junk");
  histo->Sumw2();
  //Float_t ntriggers = trighisto->GetBinContent(trighisto->FindBin(histo3D->GetYaxis()->GetBinCenter(ybin)));
  Float_t ntriggers = trighisto->Integral(trighisto->FindBin(triglow+0.01),trighisto->FindBin(trighigh-0.01));
  histo->Rebin(3.0);
  Float_t scale = 1.0/(ntriggers * histo->GetBinWidth(1));
  if(ntriggers>0){
    histo->Scale(scale);
  }
  //Float_t yield = CalculateYield(histo,yielderr);
  return histo;
}


void PlotTrigPt(char *infilename = "outfileVer2.root"){

    TFile *infile = new TFile(infilename);
    TH3F *hUnidentifiedCorrelations = infile->Get("hUnidentifiedCorrelations");
    TH3F *hK0Correlations = infile->Get("hK0Correlations");
    TH3F *hLambdaCorrelations = infile->Get("hLambdaCorrelations");
    TH3F *hK0AssocCorrelations = infile->Get("hK0AssocCorrelations");
    TH3F *hLambdaAssocCorrelations = infile->Get("hLambdaAssocCorrelations");
    TH1F *hUnidentifiedTriggers = infile->Get("hUnidentifiedTriggers");
    TH1F *hK0Triggers = infile->Get("hK0Triggers");
    TH1F *hLambdaTriggers = infile->Get("hLambdaTriggers");
    TH3F *hPiCorrelations = infile->Get("hPiCorrelations");
    TH3F *hPiAssocCorrelations = infile->Get("hPiAssocCorrelations");
    TH1F *hPiTriggers = infile->Get("hPiTriggers");
    TH3F *hProtonCorrelations = infile->Get("hProtonCorrelations");
    TH3F *hProtonAssocCorrelations = infile->Get("hProtonAssocCorrelations");
    TH1F *hProtonTriggers = infile->Get("hProtonTriggers");
    TH3F *hKCorrelations = infile->Get("hKCorrelations");
    TH3F *hKAssocCorrelations = infile->Get("hKAssocCorrelations");
    TH1F *hKTriggers = infile->Get("hKTriggers");

    TH1F *hK0Spectra = infile->Get("hK0Spectra");
    TH1F *hLamSpectra = infile->Get("hLamSpectra");
    TH1F *hAntiLamSpectra = infile->Get("hAntiLamSpectra");

//     TH1F *hK0Spectra = new TH1F("hK0Spectra","K^0_{S} spectra",nbins,binBoundaries);
//     TH1F *hLamSpectra = new TH1F("hLamSpectra","#Lambda spectra",nbins,binBoundaries);
//     TH1F *hAntiLamSpectra = new TH1F("hAntiLamSpectra","#bar{#Lambda} spectra",nbins,binBoundaries);


    //======================Pt Trig====================

    ofstream myfile;
    TString textfilename = "TrigPt.dat";
    myfile.open (textfilename.Data());
    //set to be everything except stuff below 1.5 because we have a cut on pTtrig>pTassoc
    Float_t ptassoclow = 1.5;
    Float_t ptassochigh = 6.0;
    SetPtAssocRange(hUnidentifiedCorrelations,ptassoclow,ptassochigh);
    SetPtAssocRange(hK0Correlations,ptassoclow,ptassochigh);
    SetPtAssocRange(hLambdaCorrelations,ptassoclow,ptassochigh);
    SetPtAssocRange(hK0AssocCorrelations,ptassoclow,ptassochigh);
    SetPtAssocRange(hLambdaAssocCorrelations,ptassoclow,ptassochigh);
    SetPtAssocRange(hPiCorrelations,ptassoclow,ptassochigh);
    SetPtAssocRange(hProtonCorrelations,ptassoclow,ptassochigh);
    SetPtAssocRange(hKCorrelations,ptassoclow,ptassochigh);


    Int_t ntrigbins = 20;
    for(Int_t i=1;i<=ntrigbins;i++){
      Int_t lowbin = i;
      Int_t highbin = i;
      Float_t pttriglow = hLambdaAssocCorrelations->GetYaxis()->GetBinLowEdge(lowbin);
      Float_t pttrighigh = hLambdaAssocCorrelations->GetYaxis()->GetBinLowEdge(highbin+1);
      Float_t pttrig = pttriglow + 1.0/3.0*(pttrighigh-pttriglow);
      Float_t hyielderr = 0;
      Float_t hyield = CalculateYieldForPtTrig(hUnidentifiedCorrelations,hUnidentifiedTriggers,i,i,hyielderr);
      Float_t k0yielderr = 0;
      Float_t k0yield = CalculateYieldForPtTrig(hK0Correlations,hK0Triggers,i,i,k0yielderr);
      Float_t lamyielderr = 0;
      Float_t lamyield = CalculateYieldForPtTrig(hLambdaCorrelations,hLambdaTriggers,i,i,lamyielderr);
      Float_t k0assocyielderr = 0;
      Float_t k0assocyield = CalculateYieldForPtTrig(hK0AssocCorrelations,hUnidentifiedTriggers,i,i,k0assocyielderr);
      Float_t lamassocyielderr = 0;
      Float_t lamassocyield = CalculateYieldForPtTrig(hLambdaCorrelations,hUnidentifiedTriggers,i,i,lamassocyielderr);
      Float_t piyielderr = 0;
      Float_t piyield = CalculateYieldForPtTrig(hPiCorrelations,hPiTriggers,i,i,piyielderr);
      Float_t protonyielderr = 0;
      Float_t protonyield = CalculateYieldForPtTrig(hProtonCorrelations,hProtonTriggers,i,i,protonyielderr);
      Float_t kyielderr = 0;
      Float_t kyield = CalculateYieldForPtTrig(hKCorrelations,hKTriggers,i,i,kyielderr);
      Float_t piassocyielderr = 0;
      Float_t piassocyield = CalculateYieldForPtTrig(hPiAssocCorrelations,hPiTriggers,i,i,piassocyielderr);
      Float_t protonassocyielderr = 0;
      Float_t protonassocyield = CalculateYieldForPtTrig(hProtonAssocCorrelations,hProtonTriggers,i,i,protonassocyielderr);
      Float_t kassocyielderr = 0;
      Float_t kassocyield = CalculateYieldForPtTrig(hKAssocCorrelations,hKTriggers,i,i,kassocyielderr);
      TString toprint = Form("%2.5f %2.5f %2.5f %2.5f %2.5f %2.5f %2.5f %2.5f %2.5f %2.5f %2.5f %2.5f",pttrig,hyield,k0yield,lamyield,k0assocyield,lamassocyield,piyield,protonyield,kyield,piassocyield,protonassocyield,kassocyield);
      myfile<<toprint.Data()<<endl;
      i = highbin;
      //return;
    }
    myfile.close();



    //======================Pt Assoc====================
    ofstream myfileptassoc;
    TString textfilename = "AssocPt.dat";
    myfileptassoc.open (textfilename.Data());
    Float_t pttriglow = 3.01;
    Float_t pttrighigh = 5.99;
    SetPtTrigRange(hUnidentifiedCorrelations,pttriglow,pttrighigh);
    SetPtTrigRange(hK0Correlations,pttriglow,pttrighigh);
    SetPtTrigRange(hLambdaCorrelations,pttriglow,pttrighigh);
    SetPtTrigRange(hK0AssocCorrelations,pttriglow,pttrighigh);
    SetPtTrigRange(hLambdaAssocCorrelations,pttriglow,pttrighigh);
    SetPtTrigRange(hPiCorrelations,pttriglow,pttrighigh);
    SetPtTrigRange(hProtonCorrelations,pttriglow,pttrighigh);
    SetPtTrigRange(hKCorrelations,pttriglow,pttrighigh);
    for(Int_t i=1;i<=ntrigbins;i++){
      Float_t ptassoc = hLambdaAssocCorrelations->GetXaxis()->GetBinCenter(i);
      Float_t hyielderr = 0;
      Float_t hyield = CalculateYieldForPtAssoc(hUnidentifiedCorrelations,hUnidentifiedTriggers,i,pttriglow,pttrighigh,hyielderr);
      Float_t k0yielderr = 0;
      Float_t k0yield = CalculateYieldForPtAssoc(hK0Correlations,hK0Triggers,i,pttriglow,pttrighigh,k0yielderr);
      Float_t lamyielderr = 0;
      Float_t lamyield = CalculateYieldForPtAssoc(hLambdaCorrelations,hLambdaTriggers,i,pttriglow,pttrighigh,lamyielderr);
      Float_t k0assocyielderr = 0;
      Float_t k0assocyield = CalculateYieldForPtAssoc(hK0AssocCorrelations,hUnidentifiedTriggers,i,pttriglow,pttrighigh,k0assocyielderr);
      Float_t lamassocyielderr = 0;
      Float_t lamassocyield = CalculateYieldForPtAssoc(hLambdaCorrelations,hUnidentifiedTriggers,i,pttriglow,pttrighigh,lamassocyielderr);
      Float_t piyielderr = 0;
      Float_t piyield = CalculateYieldForPtAssoc(hPiCorrelations,hPiTriggers,i,pttriglow,pttrighigh,piyielderr);
      Float_t protonyielderr = 0;
      Float_t protonyield = CalculateYieldForPtAssoc(hProtonCorrelations,hProtonTriggers,i,pttriglow,pttrighigh,protonyielderr);
      Float_t kyielderr = 0;
      Float_t kyield = CalculateYieldForPtAssoc(hKCorrelations,hKTriggers,i,pttriglow,pttrighigh,kyielderr);
      Float_t piassocyielderr = 0;
      Float_t piassocyield = CalculateYieldForPtAssoc(hPiAssocCorrelations,hPiTriggers,i,pttriglow,pttrighigh,piassocyielderr);
      Float_t protonassocyielderr = 0;
      Float_t protonassocyield = CalculateYieldForPtAssoc(hProtonAssocCorrelations,hProtonTriggers,i,pttriglow,pttrighigh,protonassocyielderr);
      Float_t kassocyielderr = 0;
      Float_t kassocyield = CalculateYieldForPtAssoc(hKAssocCorrelations,hKTriggers,i,pttriglow,pttrighigh,kassocyielderr);
      TString toprint = Form("%2.5f %2.5f %2.5f %2.5f %2.5f %2.5f %2.5f %2.5f %2.5f %2.5f %2.5f %2.5f",ptassoc,hyield,k0yield,lamyield,k0assocyield,lamassocyield,piyield,protonyield,kyield,piassocyield,protonassocyield,kassocyield);
      myfileptassoc<<toprint.Data()<<endl;
    }

    myfileptassoc.close();
    //=======================NPart======================

    ofstream myfilenpart;
    TString textfilenpartname = "NPart.dat";
    myfilenpart.open (textfilenpartname.Data());
    //set to be everything except stuff below 1.5 because we have a cut on pTtrig>pTassoc
    ptassoclow = 1.5;
    ptassochigh = 6.0;
    SetPtAssocRange(hUnidentifiedCorrelations,ptassoclow,ptassochigh);
    SetPtAssocRange(hK0Correlations,ptassoclow,ptassochigh);
    SetPtAssocRange(hLambdaCorrelations,ptassoclow,ptassochigh);
    SetPtAssocRange(hK0AssocCorrelations,ptassoclow,ptassochigh);
    SetPtAssocRange(hLambdaAssocCorrelations,ptassoclow,ptassochigh);
    SetPtAssocRange(hPiCorrelations,ptassoclow,ptassochigh);
    SetPtAssocRange(hProtonCorrelations,ptassoclow,ptassochigh);
    SetPtAssocRange(hKCorrelations,ptassoclow,ptassochigh);
    pttriglow = 3.01;
    pttrighigh = 5.99;
    SetPtTrigRange(hUnidentifiedCorrelations,pttriglow,pttrighigh);
    SetPtTrigRange(hK0Correlations,pttriglow,pttrighigh);
    SetPtTrigRange(hLambdaCorrelations,pttriglow,pttrighigh);
    SetPtTrigRange(hK0AssocCorrelations,pttriglow,pttrighigh);
    SetPtTrigRange(hLambdaAssocCorrelations,pttriglow,pttrighigh);
    SetPtTrigRange(hPiCorrelations,pttriglow,pttrighigh);
    SetPtTrigRange(hProtonCorrelations,pttriglow,pttrighigh);
    SetPtTrigRange(hKCorrelations,pttriglow,pttrighigh);
    Float_t hyielderr = 0;
    Float_t hyield = CalculateYieldForNPart(hUnidentifiedCorrelations,hUnidentifiedTriggers,pttriglow,pttrighigh,hyielderr);
    cout<<"Error on h-h 3-6 GeV trigger: "<<hyield<<"+/-"<<hyielderr<<" ("<<Form("%2.2f",100.0*hyielderr/hyield)<<"%)"<<endl;
    TH1D *histo = GetHistogramForNPart(hUnidentifiedCorrelations,hUnidentifiedTriggers,pttriglow,pttrighigh,hyielderr);
    histo->Draw();
    Float_t k0yielderr = 0;
    Float_t k0yield = CalculateYieldForNPart(hK0Correlations,hK0Triggers,pttriglow,pttrighigh,k0yielderr);
    Float_t lamyielderr = 0;
    Float_t lamyield = CalculateYieldForNPart(hLambdaCorrelations,hLambdaTriggers,pttriglow,pttrighigh,lamyielderr);
    Float_t k0assocyielderr = 0;
    Float_t k0assocyield = CalculateYieldForNPart(hK0AssocCorrelations,hUnidentifiedTriggers,pttriglow,pttrighigh,k0assocyielderr);
    Float_t lamassocyielderr = 0;
    Float_t lamassocyield = CalculateYieldForNPart(hLambdaAssocCorrelations,hUnidentifiedTriggers,pttriglow,pttrighigh,lamassocyielderr);
    cout<<"Error on lam-h 3-6 GeV trigger: "<<lamyield<<"+/-"<<lamyielderr<<" ("<<Form("%2.2f",100.0*lamyielderr/lamyield)<<"%)"<<endl;
    cout<<"Error on k0-h 3-6 GeV trigger: "<<k0yield<<"+/-"<<k0yielderr<<" ("<<Form("%2.2f",100.0*k0yielderr/k0yield)<<"%)"<<endl;
    cout<<"Error on h-lam 3-6 GeV trigger: "<<lamassocyield<<"+/-"<<lamassocyielderr<<" ("<<Form("%2.2f",100.0*lamassocyielderr/lamassocyield)<<"%)"<<endl;
    cout<<"Error on h-k0 3-6 GeV trigger: "<<k0assocyield<<"+/-"<<k0assocyielderr<<" ("<<Form("%2.2f",100.0*k0assocyielderr/k0assocyield)<<"%)"<<endl;
      Float_t piyielderr = 0;
      Float_t piyield = CalculateYieldForNPart(hPiCorrelations,hPiTriggers,pttriglow,pttrighigh,piyielderr);
      Float_t protonyielderr = 0;
      Float_t protonyield = CalculateYieldForNPart(hProtonCorrelations,hProtonTriggers,pttriglow,pttrighigh,protonyielderr);
      Float_t kyielderr = 0;
      Float_t kyield = CalculateYieldForNPart(hKCorrelations,hKTriggers,pttriglow,pttrighigh,kyielderr);
      Float_t piassocyielderr = 0;
      Float_t piassocyield = CalculateYieldForNPart(hPiAssocCorrelations,hPiTriggers,pttriglow,pttrighigh,piassocyielderr);
      Float_t protonassocyielderr = 0;
      Float_t protonassocyield = CalculateYieldForNPart(hProtonAssocCorrelations,hProtonTriggers,pttriglow,pttrighigh,protonassocyielderr);
      Float_t kassocyielderr = 0;
      Float_t kassocyield = CalculateYieldForNPart(hKAssocCorrelations,hKTriggers,pttriglow,pttrighigh,kassocyielderr);
    //TString toprint = Form("%2.5f %2.5f %2.5f %2.5f %2.5f %2.5f %2.5f %2.5f %2.5f %2.5f %2.5f",pttrig,hyield,hyielderr,k0yield,k0yielderr,lamyield,lamyielderr,k0assocyield,k0assocyielderr,lamassocyield,lamassocyielderr);
    
    TString toprint = Form("%2.5f %2.5f %2.5f %2.5f %2.5f %2.5f %2.5f %2.5f %2.5f %2.5f %2.5f",hyield,k0yield,lamyield,k0assocyield,lamassocyield,piyield,protonyield,kyield,piassocyield,protonassocyield,kassocyield);
    myfilenpart<<toprint.Data()<<endl;
    myfilenpart.close();

    //=======================Inclusive Particle Ratios======================
    hLamSpectra->Sumw2();
    hAntiLamSpectra->Sumw2();
    hK0Spectra->Sumw2();
    hLamSpectra->Add(hAntiLamSpectra);
    hLamSpectra->Divide(hK0Spectra);
    hLamSpectra->Scale(0.5);
    ofstream myfile3;
    TString textfilename3 = "InclusiveRatio.dat";
    myfile3.open (textfilename3.Data());
    for(int i=1;i<=hLamSpectra->GetNbinsX();i++){
      TString toprint = Form("%2.5f %2.5f",hLamSpectra->GetBinCenter(i),hLamSpectra->GetBinContent(i));
      myfile3<<toprint.Data()<<endl;
      //myfile3<<hLamSpectra->GetBinCenter(i)<<
      //cout<<"x="<<hLamSpectra->GetBinCenter(i)<<" y="<<hLamSpectra->GetBinContent(i)<<"+/-"<<hLamSpectra->GetBinError(i)<<endl;
    }

    myfile3.close();
}
