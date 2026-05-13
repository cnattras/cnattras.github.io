void plots(Int_t statoption = 0, Bool_t yielddouble = kFALSE){
  TFile *file = NULL;
  if(yielddouble){
    switch(statoption){
    case 1:
      file = new TFile("alltrees1e7entriesdoubleamplitude.root");
      break;
    case 2:
      file = new TFile("alltrees1e8entriesdoubleamplitude.root");
      break;
    default:
      file = new TFile("alltrees4e6entriesdoubleamplitude.root");
    }
  }
  else{
    switch(statoption){
    case 1:
      file = new TFile("alltrees1e7entries.root");
      break;
    case 2:
      file = new TFile("alltrees1e8entries.root");
      break;
    default:
      file= new TFile("alltrees4e6entries.root");
    }
  }


  TString yieldFit1 = "yieldFit1";
  TString cutlessthan3sigma = "TMath::Abs((yieldFit3-yieldFit1)/yieldFitErr1)<3&&TMath::Abs((yieldFit2-yieldFit1)/yieldFitErr2)<3&&TMath::Abs((yieldFit2-yieldFit3)/yieldFitErr2)<3";
  TString cutanygreaterthan1sigma = "(TMath::Abs((yieldFit3-yieldFit1)/yieldFitErr1)>1||TMath::Abs((yieldFit2-yieldFit1)/yieldFitErr2)>1||TMath::Abs((yieldFit2-yieldFit3)/yieldFitErr2)>1)";
  TString myand = "&&";
  TString cutfitlessthan1sigmaFit1 = "TMath::Abs(yieldFit1-yieldTrue)/yieldFitErr1<1";
  TString cutfitlessthan1sigmaFit2 = "TMath::Abs(yieldFit2-yieldTrue)/yieldFitErr2<1";
  TString cutfitlessthan1sigmaFit3 = "TMath::Abs(yieldFit3-yieldTrue)/yieldFitErr3<1";
  TString cutfitlessthan2sigmaFit1 = "TMath::Abs(yieldFit1-yieldTrue)/yieldFitErr1<2";
  TString cutfitlessthan2sigmaFit2 = "TMath::Abs(yieldFit2-yieldTrue)/yieldFitErr2<2";
  TString cutfitlessthan2sigmaFit3 = "TMath::Abs(yieldFit3-yieldTrue)/yieldFitErr3<2";
  TString relativeyieldFit1 = "(yieldFit1-yieldTrue)/yieldTrue";
  TString relativeyieldFit2 = "(yieldFit2-yieldTrue)/yieldTrue";
  TString relativeyieldFit3 = "(yieldFit3-yieldTrue)/yieldTrue";
  TString relativeyieldFit2outliers = "TMath::Abs(yieldFit2-yieldTrue)/yieldTrue<10";

  TString bkgdFit1 = "bkgdFit1";
  TString bkgdcutlessthan3sigma = "TMath::Abs((bkgdFit3-bkgdFit1)/bkgdFitErr1)<3&&TMath::Abs((bkgdFit2-bkgdFit1)/bkgdFitErr2)<3&&TMath::Abs((bkgdFit2-bkgdFit3)/bkgdFitErr2)<3";
  TString bkgdcutanygreaterthan1sigma = "(TMath::Abs((bkgdFit3-bkgdFit1)/bkgdFitErr1)>1||TMath::Abs((bkgdFit2-bkgdFit1)/bkgdFitErr2)>1||TMath::Abs((bkgdFit2-bkgdFit3)/bkgdFitErr2)>1)";
  TString bkgdcutfitlessthan1sigmaFit1 = "TMath::Abs(bkgdFit1-bkgdTrue)/bkgdFitErr1<1";
  TString bkgdcutfitlessthan1sigmaFit2 = "TMath::Abs(bkgdFit2-bkgdTrue)/bkgdFitErr2<1";
  TString bkgdcutfitlessthan1sigmaFit3 = "TMath::Abs(bkgdFit3-bkgdTrue)/bkgdFitErr3<1";
  TString bkgdcutfitlessthan2sigmaFit1 = "TMath::Abs(bkgdFit1-bkgdTrue)/bkgdFitErr1<2";
  TString bkgdcutfitlessthan2sigmaFit2 = "TMath::Abs(bkgdFit2-bkgdTrue)/bkgdFitErr2<2";
  TString bkgdcutfitlessthan2sigmaFit3 = "TMath::Abs(bkgdFit3-bkgdTrue)/bkgdFitErr3<2";
  TString bkgdrelativebkgdFit1 = "(bkgdFit1-bkgdTrue)/bkgdTrue";
  TString bkgdrelativebkgdFit2 = "(bkgdFit2-bkgdTrue)/bkgdTrue";
  TString bkgdrelativebkgdFit3 = "(bkgdFit3-bkgdTrue)/bkgdTrue";
  TString bkgdrelativebkgdErrFit1 = "(bkgdFit1-bkgdTrue)/bkgdFitErr1";
  TString bkgdrelativebkgdErrFit2 = "(bkgdFit2-bkgdTrue)/bkgdFitErr2";
  TString bkgdrelativebkgdErrFit3 = "(bkgdFit3-bkgdTrue)/bkgdFitErr3";
  TString bkgdyieldDiffFit1 = "(bkgdFit1-bkgdTrue)*0.78*2/yieldTrue";
  TString bkgdyieldDiffFit2 = "(bkgdFit2-bkgdTrue)*0.78*2/yieldTrue";
  TString bkgdyieldDiffFit3 = "(bkgdFit3-bkgdTrue)*0.78*2/yieldTrue";
  TString bkgdrelativebkgdFit2outliers = "TMath::Abs(bkgdFit2-bkgdTrue)/bkgdTrue<10";
  
  myTree->Draw("(yieldTrue-yieldFit1)/yieldFitErr1","TMath::Abs(yieldTrue-yieldFit1)/yieldFitErr3<5","e");
  c1->SaveAs("plots/truevsfit1overerr.png");
  myTree->Draw("(yieldTrue-yieldFit2)/yieldFitErr2","TMath::Abs(yieldTrue-yieldFit2)/yieldFitErr2<5","e");
  c1->SaveAs("plots/truevsfit2overerr.png");
  myTree->Draw("(yieldTrue-yieldFit3)/yieldFitErr3","TMath::Abs(yieldTrue-yieldFit3)/yieldFitErr3<5","e");
  c1->SaveAs("plots/truevsfit3overerr.png");
  myTree->Draw("(yieldTrue-yieldFit1)/yieldTrue","TMath::Abs(yieldTrue-yieldFit1)/yieldTrue<5","e");
  c1->SaveAs("plots/truevsfit1overtrue.png");
  myTree->Draw("(yieldTrue-yieldFit2)/yieldTrue","TMath::Abs(yieldTrue-yieldFit2)/yieldTrue<5","e");
  c1->SaveAs("plots/truevsfit2overtrue.png");
  myTree->Draw("(yieldTrue-yieldFit3)/yieldTrue","TMath::Abs(yieldTrue-yieldFit3)/yieldTrue<5","e");
  c1->SaveAs("plots/truevsfit3overtrue.png");
  
  myTree->Draw("(yieldFit2-yieldFit1)/yieldFitErr2","TMath::Abs((yieldFit2-yieldFit1)/yieldFitErr2)<3","e");
  c1->SaveAs("plots/Fit2MinusFit1OverFit2Err.png");
  myTree->Draw("(yieldFit2-yieldFit1)/TMath::Sqrt(yieldFitErr1*yieldFitErr1+yieldFitErr2*yieldFitErr2)","TMath::Abs((yieldFit2-yieldFit1)/yieldFitErr2)<3","e");
  c1->SaveAs("plots/Fit2MinusFit1OverFit1And2Err.png");
  myTree->Draw("(yieldFit2-yieldFit1)/yieldFitErr1","TMath::Abs((yieldFit2-yieldFit1)/yieldFitErr1)<3","e");
  c1->SaveAs("plots/Fit2MinusFit1OverFit1Err.png");
  
  myTree->Draw("(yieldFit3-yieldFit1)/yieldFitErr1","TMath::Abs((yieldFit3-yieldFit1)/yieldFitErr1)<3","e");
  c1->SaveAs("plots/Fit3MinusFit1OverFit1Err.png");
  myTree->Draw("(yieldFit3-yieldFit1)/yieldFitErr3","TMath::Abs((yieldFit3-yieldFit1)/yieldFitErr3)<3","e");
  c1->SaveAs("plots/Fit3MinusFit1OverFit3Err.png");
  myTree->Draw("(yieldFit3-yieldFit1)/TMath::Sqrt(yieldFitErr1*yieldFitErr1+yieldFitErr3*yieldFitErr3)","TMath::Abs((yieldFit3-yieldFit1)/yieldFitErr3)<3","e");
  c1->SaveAs("plots/Fit3MinusFit1OverFit1And3Err.png");
  
  //Figuring out how many outliers there are
  
  myTree->Draw("(yieldFit1)","TMath::Abs((yieldFit3-yieldFit1)/yieldFitErr1)<3&&TMath::Abs((yieldFit2-yieldFit1)/yieldFitErr2)<3&&TMath::Abs((yieldFit2-yieldFit3)/yieldFitErr2)<3","e");
  Double_t numberofentries = htemp->GetEntries();
  myTree->Draw("(yieldFit1)","TMath::Abs((yieldFit3-yieldFit1)/yieldFitErr1)<1&&TMath::Abs((yieldFit2-yieldFit1)/yieldFitErr2)<1&&TMath::Abs((yieldFit2-yieldFit3)/yieldFitErr2)<1","e");
  Double_t numberwithin1sigma = htemp->GetEntries();
  //cout<<"number of entries within 3 sigma: "<<numberofentries<<" number of entries within 1 sigma "<<numberwithin1sigma<<" fraction within 1 sigma "<<numberwithin1sigma/numberofentries<<endl;
  //calculate the number of entries that are within 1 and 2 sigma of true value with various cuts
  //use TStrings because it will make the answer easier to come by
  
  myTree->Draw(yieldFit1.Data(),(cutlessthan3sigma+myand+cutanygreaterthan1sigma),"e");
  numberwithin1sigma = htemp->GetEntries();
  cout<<"number of entries within 3 sigma: "<<numberofentries<<" number of entries within 1 sigma "<<numberwithin1sigma<<" fraction within 1 sigma "<<numberwithin1sigma/numberofentries<<endl;
  
  
  Double_t numberbadfits = numberwithin1sigma;
  myTree->Draw(yieldFit1.Data(),(cutlessthan3sigma+myand+cutanygreaterthan1sigma+myand+cutfitlessthan1sigmaFit1),"e");
  Double_t badFitsWithin1SigmaFit1 = htemp->GetEntries();
  myTree->Draw(yieldFit1.Data(),(cutlessthan3sigma+myand+cutanygreaterthan1sigma+myand+cutfitlessthan1sigmaFit2),"e");
  Double_t badFitsWithin1SigmaFit2 = htemp->GetEntries();
  myTree->Draw(yieldFit1.Data(),(cutlessthan3sigma+myand+cutanygreaterthan1sigma+myand+cutfitlessthan1sigmaFit3),"e");
  Double_t badFitsWithin1SigmaFit3 = htemp->GetEntries();
  myTree->Draw(yieldFit1.Data(),(cutlessthan3sigma+myand+cutanygreaterthan1sigma+myand+cutfitlessthan2sigmaFit1),"e");
  Double_t badFitsWithin2SigmaFit1 = htemp->GetEntries();
  myTree->Draw(yieldFit1.Data(),(cutlessthan3sigma+myand+cutanygreaterthan1sigma+myand+cutfitlessthan2sigmaFit2),"e");
  Double_t badFitsWithin2SigmaFit2 = htemp->GetEntries();
  myTree->Draw(yieldFit1.Data(),(cutlessthan3sigma+myand+cutanygreaterthan1sigma+myand+cutfitlessthan2sigmaFit3),"e");
  Double_t badFitsWithin2SigmaFit3 = htemp->GetEntries();

  cout<<"Of the "<<numberbadfits<<" fits where at least one of the yields is not within 1 sigma of the others:"<<endl;
  cout<<badFitsWithin1SigmaFit1<<" ("<<badFitsWithin1SigmaFit1/numberbadfits*100<<"%) fits are within 1 sigma and "<<badFitsWithin2SigmaFit1<<" ("<<badFitsWithin2SigmaFit1/numberbadfits*100<<"%) within 2 sigma of the true yield for Fit 1"<<endl;
  cout<<badFitsWithin1SigmaFit2<<" ("<<badFitsWithin1SigmaFit2/numberbadfits*100<<"%) fits are within 1 sigma and "<<badFitsWithin2SigmaFit2<<" ("<<badFitsWithin2SigmaFit2/numberbadfits*100<<"%) within 2 sigma of the true yield for Fit 2"<<endl;
  cout<<badFitsWithin1SigmaFit3<<" ("<<badFitsWithin1SigmaFit3/numberbadfits*100<<"%) fits are within 1 sigma and "<<badFitsWithin2SigmaFit3<<" ("<<badFitsWithin2SigmaFit3/numberbadfits*100<<"%) within 2 sigma of the true yield for Fit 3"<<endl;
  //cout<<badFitsWithin1SigmaFit2<<" fits are within 1 sigma and "<<badFitsWithin2SigmaFit2<<" within 2 sigma of the true yield for Fit 2"<<endl;
  //cout<<badFitsWithin1SigmaFit3<<" fits are within 1 sigma and "<<badFitsWithin2SigmaFit3<<" within 2 sigma of the true yield for Fit 3"<<endl;

  cout<<"Of all fits where the yield is within 3 sigma for all fits:"<<endl;
  myTree->Draw(relativeyieldFit1.Data(),(cutlessthan3sigma),"e");
  cout<<"Mean for Fit 1: "<<htemp->GetMean()<<" +/- "<<htemp->GetMeanError()<<endl;
  myTree->Draw(relativeyieldFit2.Data(),(cutlessthan3sigma+myand+relativeyieldFit2outliers),"e");
  cout<<"Mean for Fit 2: "<<htemp->GetMean()<<" +/- "<<htemp->GetMeanError()<<endl;
  //return;
  myTree->Draw(relativeyieldFit3.Data(),(cutlessthan3sigma),"e");
  cout<<"Mean for Fit 3: "<<htemp->GetMean()<<" +/- "<<htemp->GetMeanError()<<endl;

  cout<<endl<<endl<<endl;

  myTree->Draw("(bkgdTrue-bkgdFit1)/bkgdFitErr1","TMath::Abs(bkgdTrue-bkgdFit1)/bkgdFitErr1<5","e");
  c1->SaveAs("plots/bkgdtruevsfit1overerr.png");
  myTree->Draw("(bkgdTrue-bkgdFit2)/bkgdFitErr2","TMath::Abs(bkgdTrue-bkgdFit2)/bkgdFitErr2<5","e");
  c1->SaveAs("plots/bkgdtruevsfit2overerr.png");
  myTree->Draw("(bkgdTrue-bkgdFit3)/bkgdFitErr3","TMath::Abs(bkgdTrue-bkgdFit3)/bkgdFitErr3<5","e");
  c1->SaveAs("plots/bkgdtruevsfit3overerr.png");
  myTree->Draw("(bkgdTrue-bkgdFit1)/bkgdTrue","TMath::Abs(bkgdTrue-bkgdFit1)/bkgdTrue<1e-2","e");
  c1->SaveAs("plots/bkgdtruevsfit1overtrue.png");
  myTree->Draw("(bkgdTrue-bkgdFit2)/bkgdTrue","TMath::Abs(bkgdTrue-bkgdFit2)/bkgdTrue<1e-2","e");
  c1->SaveAs("plots/bkgdtruevsfit2overtrue.png");
  myTree->Draw("(bkgdTrue-bkgdFit3)/bkgdTrue","TMath::Abs(bkgdTrue-bkgdFit3)/bkgdTrue<1e-2","e");
  c1->SaveAs("plots/bkgdtruevsfit3overtrue.png");

  
  myTree->Draw("(bkgdFit2-bkgdFit1)/bkgdFitErr2","TMath::Abs((bkgdFit2-bkgdFit1)/bkgdFitErr2)<3","e");
  c1->SaveAs("plots/bkgdFit2MinusFit1OverFit2Err.png");
  myTree->Draw("(bkgdFit2-bkgdFit1)/TMath::Sqrt(bkgdFitErr1*bkgdFitErr1+bkgdFitErr2*bkgdFitErr2)","TMath::Abs((bkgdFit2-bkgdFit1)/bkgdFitErr2)<3","e");
  c1->SaveAs("plots/bkgdFit2MinusFit1OverFit1And2Err.png");
  myTree->Draw("(bkgdFit2-bkgdFit1)/bkgdFitErr1","TMath::Abs((bkgdFit2-bkgdFit1)/bkgdFitErr1)<3","e");
  c1->SaveAs("plots/bkgdFit2MinusFit1OverFit1Err.png");
  
  myTree->Draw("(bkgdFit3-bkgdFit1)/bkgdFitErr1","TMath::Abs((bkgdFit3-bkgdFit1)/bkgdFitErr1)<3","e");
  c1->SaveAs("plots/bkgdFit3MinusFit1OverFit1Err.png");
  myTree->Draw("(bkgdFit3-bkgdFit1)/bkgdFitErr3","TMath::Abs((bkgdFit3-bkgdFit1)/bkgdFitErr3)<3","e");
  c1->SaveAs("plots/bkgdFit3MinusFit1OverFit3Err.png");
  myTree->Draw("(bkgdFit3-bkgdFit1)/TMath::Sqrt(bkgdFitErr1*bkgdFitErr1+bkgdFitErr3*bkgdFitErr3)","TMath::Abs((bkgdFit3-bkgdFit1)/bkgdFitErr3)<3","e");
  c1->SaveAs("plots/bkgdFit3MinusFit1OverFit1And3Err.png");

  //Figuring out how many outliers there are
  
  myTree->Draw("(bkgdFit1)","TMath::Abs((bkgdFit3-bkgdFit1)/bkgdFitErr1)<3&&TMath::Abs((bkgdFit2-bkgdFit1)/bkgdFitErr2)<3&&TMath::Abs((bkgdFit2-bkgdFit3)/bkgdFitErr2)<3","e");
  numberofentries = htemp->GetEntries();
  myTree->Draw("(bkgdFit1)","TMath::Abs((bkgdFit3-bkgdFit1)/bkgdFitErr1)<1&&TMath::Abs((bkgdFit2-bkgdFit1)/bkgdFitErr2)<1&&TMath::Abs((bkgdFit2-bkgdFit3)/bkgdFitErr2)<1","e");
  numberwithin1sigma = htemp->GetEntries();
  //cout<<"number of entries within 3 sigma: "<<numberofentries<<" number of entries within 1 sigma "<<numberwithin1sigma<<" fraction within 1 sigma "<<numberwithin1sigma/numberofentries<<endl;
  //calculate the number of entries that are within 1 and 2 sigma of true value with various cuts
  //use TStrings because it will make the answer easier to come by
  
  myTree->Draw(bkgdFit1.Data(),(bkgdcutlessthan3sigma+myand+bkgdcutanygreaterthan1sigma),"e");
  numberwithin1sigma = htemp->GetEntries();
  cout<<"number of entries within 3 sigma: "<<numberofentries<<" number of entries within 1 sigma "<<numberwithin1sigma<<" fraction within 1 sigma "<<numberwithin1sigma/numberofentries<<endl;
  
  
   numberbadfits = numberwithin1sigma;
  myTree->Draw(bkgdFit1.Data(),(bkgdcutlessthan3sigma+myand+bkgdcutanygreaterthan1sigma+myand+bkgdcutfitlessthan1sigmaFit1),"e");
   badFitsWithin1SigmaFit1 = htemp->GetEntries();
  myTree->Draw(bkgdFit1.Data(),(bkgdcutlessthan3sigma+myand+bkgdcutanygreaterthan1sigma+myand+bkgdcutfitlessthan1sigmaFit2),"e");
   badFitsWithin1SigmaFit2 = htemp->GetEntries();
  myTree->Draw(bkgdFit1.Data(),(bkgdcutlessthan3sigma+myand+bkgdcutanygreaterthan1sigma+myand+bkgdcutfitlessthan1sigmaFit3),"e");
   badFitsWithin1SigmaFit3 = htemp->GetEntries();
  myTree->Draw(bkgdFit1.Data(),(bkgdcutlessthan3sigma+myand+bkgdcutanygreaterthan1sigma+myand+bkgdcutfitlessthan2sigmaFit1),"e");
   badFitsWithin2SigmaFit1 = htemp->GetEntries();
  myTree->Draw(bkgdFit1.Data(),(bkgdcutlessthan3sigma+myand+bkgdcutanygreaterthan1sigma+myand+bkgdcutfitlessthan2sigmaFit2),"e");
   badFitsWithin2SigmaFit2 = htemp->GetEntries();
  myTree->Draw(bkgdFit1.Data(),(bkgdcutlessthan3sigma+myand+bkgdcutanygreaterthan1sigma+myand+bkgdcutfitlessthan2sigmaFit3),"e");
   badFitsWithin2SigmaFit3 = htemp->GetEntries();

  cout<<"Of the "<<numberbadfits<<" fits where at least one of the bkgds is not within 1 sigma of the others:"<<endl;
  cout<<badFitsWithin1SigmaFit1<<" ("<<badFitsWithin1SigmaFit1/numberbadfits*100<<"%) fits are within 1 sigma and "<<badFitsWithin2SigmaFit1<<" ("<<badFitsWithin2SigmaFit1/numberbadfits*100<<"%) within 2 sigma of the true bkgd for Fit 1"<<endl;
  cout<<badFitsWithin1SigmaFit2<<" ("<<badFitsWithin1SigmaFit2/numberbadfits*100<<"%) fits are within 1 sigma and "<<badFitsWithin2SigmaFit2<<" ("<<badFitsWithin2SigmaFit2/numberbadfits*100<<"%) within 2 sigma of the true bkgd for Fit 2"<<endl;
  cout<<badFitsWithin1SigmaFit3<<" ("<<badFitsWithin1SigmaFit3/numberbadfits*100<<"%) fits are within 1 sigma and "<<badFitsWithin2SigmaFit3<<" ("<<badFitsWithin2SigmaFit3/numberbadfits*100<<"%) within 2 sigma of the true bkgd for Fit 3"<<endl;
  //cout<<badFitsWithin1SigmaFit2<<" fits are within 1 sigma and "<<badFitsWithin2SigmaFit2<<" within 2 sigma of the true bkgd for Fit 2"<<endl;
  //cout<<badFitsWithin1SigmaFit3<<" fits are within 1 sigma and "<<badFitsWithin2SigmaFit3<<" within 2 sigma of the true bkgd for Fit 3"<<endl;

  cout<<"Of all fits where the bkgd is within 3 sigma for all fits:"<<endl;
  myTree->Draw(bkgdrelativebkgdFit1.Data(),(bkgdcutlessthan3sigma),"e");
  cout<<"Mean (fit - true)/true for Fit 1: "<<htemp->GetMean()<<" +/- "<<htemp->GetMeanError()<<endl;
  myTree->Draw(bkgdrelativebkgdFit2.Data(),(bkgdcutlessthan3sigma+myand+bkgdrelativebkgdFit2outliers),"e");
  cout<<"Mean (fit - true)/true for Fit 2: "<<htemp->GetMean()<<" +/- "<<htemp->GetMeanError()<<endl;
  //return;
  myTree->Draw(bkgdrelativebkgdFit3.Data(),(cutlessthan3sigma),"e");
  cout<<"Mean (fit - true)/true for Fit 3: "<<htemp->GetMean()<<" +/- "<<htemp->GetMeanError()<<endl;

  cout<<"Of all fits where the bkgd is within 3 sigma for all fits:"<<endl;
  myTree->Draw(bkgdrelativebkgdErrFit1.Data(),(bkgdcutlessthan3sigma),"e");
  cout<<"Mean (fit - true)/fit err for Fit 1: "<<htemp->GetMean()<<" +/- "<<htemp->GetMeanError()<<endl;
  myTree->Draw(bkgdrelativebkgdErrFit2.Data(),(bkgdcutlessthan3sigma+myand+bkgdrelativebkgdFit2outliers),"e");
  cout<<"Mean (fit - true)/fit err for Fit 2: "<<htemp->GetMean()<<" +/- "<<htemp->GetMeanError()<<endl;
  //return;
  myTree->Draw(bkgdrelativebkgdErrFit3.Data(),(cutlessthan3sigma),"e");
  cout<<"Mean (fit - true)/fit err for Fit 3: "<<htemp->GetMean()<<" +/- "<<htemp->GetMeanError()<<endl;

  cout<<"Of all fits where the bkgd is within 3 sigma for all fits:"<<endl;
  myTree->Draw(bkgdyieldDiffFit1.Data(),bkgdcutlessthan3sigma,"e");
  cout<<"Mean yield diff/true yield for Fit 1: "<<htemp->GetMean()<<" +/- "<<htemp->GetMeanError()<<endl;
  myTree->Draw(bkgdyieldDiffFit2.Data(),bkgdcutlessthan3sigma,"e");
  cout<<"Mean yield diff/true yield for Fit 2: "<<htemp->GetMean()<<" +/- "<<htemp->GetMeanError()<<endl;
  myTree->Draw(bkgdyieldDiffFit3.Data(),bkgdcutlessthan3sigma,"e");
  cout<<"Mean yield diff/true yield for Fit 3: "<<htemp->GetMean()<<" +/- "<<htemp->GetMeanError()<<endl;
  c1->SaveAs("plots/bkgdyielderrorFit1.png");


}
