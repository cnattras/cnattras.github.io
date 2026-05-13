void PrintResults(TF1 *fitTrue, TF1 *fit, Bool_t isYield = kTRUE){
  Float_t yieldTrue = fitTrue->GetParameter(0);
  Float_t yieldFit = fit->GetParameter(0);
  Float_t yieldFitErr = fit->GetParError(0);
  Float_t bkgdTrue = fitTrue->GetParameter(2);
  Float_t bkgdFit = fit->GetParameter(2);
  Float_t bkgdFitErr = fit->GetParError(2);
  Float_t bkgdYieldDifference = (bkgdFit-bkgdTrue)*0.78*2;
  TString sYield = Form("Yield true %2.4f fit %2.4f +/- %2.4f (%2.2f\%) difference %2.4f (%2.2f\%)",yieldTrue,yieldFit,yieldFitErr,yieldFitErr/yieldFit*100,yieldFit-yieldTrue,(yieldFit-yieldTrue)/yieldTrue*100);
  TString sBkgd = Form("Bkgd true %2.4f fit %2.4f +/- %2.4f (%2.2f\%) difference %2.4f (%2.2f\%) yield difference due to background %2.4f (%2.4f\%)",bkgdTrue,bkgdFit,bkgdFitErr,bkgdFitErr/bkgdFit*100,bkgdFit-bkgdTrue,(bkgdFit-bkgdTrue)/bkgdTrue*100,bkgdYieldDifference,bkgdYieldDifference/yieldTrue*100.0);
  if(isYield)  cout<<sYield.Data()<<endl;
  else cout<<sBkgd.Data()<<endl;
}
void FitGausPlusConst(Int_t nEntries = 1e7, UInt_t seed = 0, Int_t nbins = 32,Double_t yieldfactor = 1.0){
  if(seed !=0){
    gRandom->SetSeed(seed);
  }
  TFile  *myFile = new TFile(Form("runs/tree%i.root",seed),"recreate");
   TTree *myTree = new TTree("myTree","TTree with information on accuracy of fits");
   Float_t yieldTrue,yieldFit1,yieldFit2,yieldFit3,yieldFitErr1,yieldFitErr2,yieldFitErr3;
   Float_t bkgdTrue,bkgdFit1,bkgdFit2,bkgdFit3,bkgdFitErr1,bkgdFitErr2,bkgdFitErr3;
   Float_t Chi2Fit1,Chi2Fit2,Chi2Fit3;//,NDFFit1,NDFFit2,NDFFit3;
   myTree->Branch("yieldTrue",&yieldTrue,"yieldTrue/F");
   myTree->Branch("yieldFit1",&yieldFit1,"yieldFit1/F");
   myTree->Branch("yieldFit2",&yieldFit2,"yieldFit2/F");
   myTree->Branch("yieldFit3",&yieldFit3,"yieldFit3/F");
   myTree->Branch("yieldFitErr1",&yieldFitErr1,"yieldFitErr1/F");
   myTree->Branch("yieldFitErr2",&yieldFitErr2,"yieldFitErr2/F");
   myTree->Branch("yieldFitErr3",&yieldFitErr3,"yieldFitErr3/F");
   myTree->Branch("bkgdTrue",&bkgdTrue,"bkgdTrue/F");
   myTree->Branch("bkgdFit1",&bkgdFit1,"bkgdFit1/F");
   myTree->Branch("bkgdFit2",&bkgdFit2,"bkgdFit2/F");
   myTree->Branch("bkgdFit3",&bkgdFit3,"bkgdFit3/F");
   myTree->Branch("bkgdFitErr1",&bkgdFitErr1,"bkgdFitErr1/F");
   myTree->Branch("bkgdFitErr2",&bkgdFitErr2,"bkgdFitErr2/F");
   myTree->Branch("bkgdFitErr3",&bkgdFitErr3,"bkgdFitErr3/F");
   myTree->Branch("Chi2Fit1",&Chi2Fit1,"Chi2Fit1/F");
   myTree->Branch("Chi2Fit2",&Chi2Fit2,"Chi2Fit2/F");
   myTree->Branch("Chi2Fit3",&Chi2Fit3,"Chi2Fit3/F");


  TF1 *fTrue = new TF1("fTrue","[0]/[1]/TMath::Sqrt(2*TMath::Pi())*exp(-x*x/2/[1]/[1])+[2]",-2,2);
  fTrue->SetParameter(2,9.46991e-01);
  fTrue->SetParameter(1,0.4);
  fTrue->SetParameter(0,0.01*yieldfactor);
  fTrue->Draw();
  TH1F *hMeas = new TH1F("hMeas","hMeas",nbins,-2,2);
  hMeas->Sumw2();
  for(Int_t i = 0; i<nEntries; i++){
    Float_t dphi = fTrue->GetRandom();
    hMeas->Fill(dphi);
    hMeas->Fill(-dphi);
  }
  Float_t binwidth = hMeas->GetBinWidth(1);
  hMeas->Scale(1.0/binwidth/nEntries*1.862745098/0.98);
  //the normalization of the function we threw from is kind of arbitrary so we renormaliza to make sure the yields are comparable.  The numbers above are a fudge factor to get it about right but if we're going to compare statistics we need it to be exactly right.
  Float_t trueintegral = fTrue->Integral(-2,2);
  Float_t measintegral = hMeas->Integral("width");
  cout<<"integrals - true: "<<trueintegral<<" meas "<<measintegral<<" scale "<<trueintegral/measintegral<<endl;
  hMeas->Scale(trueintegral/measintegral);


  TF1 *fFit1 = new TF1("fFit1","[0]/[1]/TMath::Sqrt(2*TMath::Pi())*exp(-x*x/2/[1]/[1])+[2]",-1.75,0);
  fFit1->SetParameter(2,0.95);
  fFit1->SetParameter(1,0.4);
  fFit1->SetParameter(0,0.01);
  fFit1->SetLineColor(TColor::kBlack);
  hMeas->Fit(fFit1,"","",-1.75,0);


  TF1 *fFit2 = new TF1("fFit2","[0]/[1]/TMath::Sqrt(2*TMath::Pi())*exp(-x*x/2/[1]/[1])+[2]",-1.75,-0.3);
  fFit2->SetParameter(2,0.95);
  fFit2->SetParameter(1,0.4);
  fFit2->SetParameter(0,0.01);
  fFit2->SetLineColor(TColor::kBlue);
  hMeas->Fit(fFit2,"","",-1.75,-0.3);


  TF1 *fFit3 = new TF1("fFit3","[0]/[1]/TMath::Sqrt(2*TMath::Pi())*exp(-x*x/2/[1]/[1])+[2]",0.0,1.65);
  fFit3->SetParameter(2,0.95);
  fFit3->SetParameter(1,0.4);
  fFit3->SetParameter(0,0.01);
  fFit3->SetLineColor(TColor::kBlue);
  fFit3->SetLineStyle(2);
  hMeas->Fit(fFit3,"","",0.3,1.65);

  hMeas->Draw();
  fTrue->Draw("same");
  fFit1->Draw("same");
  fFit2->Draw("same");
  fFit3->Draw("same");
  PrintResults(fTrue,fFit1);
  PrintResults(fTrue,fFit2);
  PrintResults(fTrue,fFit3);
  PrintResults(fTrue,fFit1,kFALSE);
  PrintResults(fTrue,fFit2,kFALSE);
  PrintResults(fTrue,fFit3,kFALSE);

  yieldTrue = fTrue->GetParameter(0);
  yieldFit1 = fFit1->GetParameter(0);
  yieldFit2 = fFit2->GetParameter(0);
  yieldFit3 = fFit3->GetParameter(0);
  yieldFitErr1 = fFit1->GetParError(0);
  yieldFitErr2 = fFit2->GetParError(0);
  yieldFitErr3 = fFit3->GetParError(0);
  bkgdTrue = fTrue->GetParameter(2);
  bkgdFit1 = fFit1->GetParameter(2);
  bkgdFit2 = fFit2->GetParameter(2);
  bkgdFit3 = fFit3->GetParameter(2);
  bkgdFitErr1 = fFit1->GetParError(2);
  bkgdFitErr2 = fFit2->GetParError(2);
  bkgdFitErr3 = fFit3->GetParError(2);
  Chi2Fit1 = fFit1->GetChisquare()/fFit1->GetNDF();
  Chi2Fit2 = fFit2->GetChisquare()/fFit2->GetNDF();
  Chi2Fit3 = fFit3->GetChisquare()/fFit3->GetNDF();
  myTree->Fill();
  Float_t diff12 = TMath::Abs(fFit1->GetParameter(0) - fFit2->GetParameter(0));
  Float_t diff23 = TMath::Abs(fFit2->GetParameter(0) - fFit3->GetParameter(0));
  Float_t diff13 = TMath::Abs(fFit1->GetParameter(0) - fFit3->GetParameter(0));
  Float_t largestdiff = diff12;
  if(diff23>largestdiff) largestdiff = diff23;
  if(diff13>largestdiff) largestdiff = diff13;
  
  cout<<Form("diff 1-2 %2.4f diff 2-3 %2.4f diff 3-1 %2.4f Largest diff %2.4f Largest diff/nominal value %2.4f (%2.4f\%)",diff12,diff23,diff13,largestdiff,largestdiff/fTrue->GetParameter(0),100* largestdiff/fTrue->GetParameter(0))<<endl;
  c1->SaveAs("ToyModelFit.png");

  myFile->Write();
  //myFile->Close();
}
