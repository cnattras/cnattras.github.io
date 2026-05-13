void MakeComparisons(){
  gROOT->LoadMacro("~nattrass/HighPt/macros/loadHighPtLibraries.C");
  loadHighPtLibraries();
  gSystem->Load("/home/nattrass/AzimuthalCorrelations/.i386_linux24/lib/StAnalysisTools");
  gSystem->Load("/home/nattrass/AzimuthalCorrelations/.i386_linux24/lib/StAnalysis");
  //gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);


  TFile *newFile = new TFile("rootFiles/ConsistencyChecks.root");
  TFile *oldFile = new TFile("~/consistencyChecks/cucu-centcombined-2.0-0.0-1.0-2.0-1.0-7.root");
  TFile *P05id = new TFile("~/consistencyChecks/cucu-centcombined-2.0-0.0-1.0-2.0-1.0-7_P05id.root");

  TCanvas *c1 = new TCanvas("c1","c1",500,400);
  c1->cd();  
  c1->SetGridx(kFALSE);
  c1->SetGridy(kFALSE);
  TH1F *oldLambda = oldFile->Get("hDPhilamch_1");
  TH1F *newLambda = newFile->Get("LambdaCent0-10Pt20-30New");
  TH1F *P05idlam = P05id->Get("hDPhilamch_1")->Clone("P05idlam");
  oldLambda->SetMarkerStyle(28);
  oldLambda->SetMarkerColor(4);
  newLambda->SetMarkerStyle(30);
  newLambda->SetMarkerColor(2);
  P05idlam->SetMarkerStyle(24);
  P05idlam->SetMarkerColor(3);
  newLambda->SetTitle( GetCorrelationHistoTitle("CuCu200",1,2,3,0,1,2,1) );
  lleg = new TLegend(0.7,0.85,0.98,0.98);//(left,bottom,right,top)  .25, .75, .8, .85
  lleg->AddEntry(newLambda,"#Lambda P06ib new code","p");//l=line p=point f=box
  lleg->AddEntry(oldLambda,"#Lambda P06ib old code","p");//l=line p=point f=box
  lleg->AddEntry(P05idlam,"#Lambda P05id old code","p");//l=line p=point f=box
  //aleg->AddEntry(hnewa,"#bar{#Lambda}","p");//l=line p=point f=box
  //aleg->AddEntry(hnewk0,"K^{0}_{s}","p");//l=line p=point f=box
  lleg->SetTextSize(0.02);
  lleg->SetFillColor(0);
  lleg->SetLineColor(0);
  float max = P05idlam->GetMaximum();
  float min = oldLambda->GetMinimum();
  newLambda->SetMaximum(max+.05);
  newLambda->SetMinimum(min-.05);
  newLambda->Draw();
  oldLambda->Rebin(3);
  oldLambda->Scale(1./3.);
  oldLambda->Draw("same");
  P05idlam->Rebin(3);
  P05idlam->Scale(1./3.);
  P05idlam->Draw("same");
  lleg->Draw();
  c1->Print("LambdaComparison.eps");
  c1->Print("LambdaComparison.pdf");



  TCanvas *c2 = new TCanvas("c2","c2",500,400);
  c2->cd();
  c2->SetGridx(kFALSE);
  c2->SetGridy(kFALSE);
  TH1F *oldAntiLambda = oldFile->Get("hDPhialamch_1");
  TH1F *newAntiLambda = newFile->Get("AntiLambdaCent0-10Pt20-30New");
  TH1F *P05idalam = P05id->Get("hDPhialamch_1")->Clone("P05idalam");
  oldAntiLambda->SetMarkerStyle(28);
  oldAntiLambda->SetMarkerColor(4);
  newAntiLambda->SetMarkerStyle(30);
  newAntiLambda->SetMarkerColor(2);
  P05idalam->SetMarkerStyle(24);
  P05idalam->SetMarkerColor(3);
  newAntiLambda->SetTitle( GetCorrelationHistoTitle("CuCu200",2,2,3,0,1,2,1) );
  aleg = new TLegend(0.7,0.85,0.98,0.98);//(left,bottom,right,top)  .25, .75, .8, .85
  aleg->AddEntry(newAntiLambda,"#bar{#Lambda} P06ib new code","p");//l=line p=point f=box
  aleg->AddEntry(oldAntiLambda,"#bar{#Lambda} P06ib old code","p");//l=line p=point f=box
  aleg->AddEntry(P05idalam,"#bar{#Lambda} P05id old code","p");//l=line p=point f=box
  //aleg->AddEntry(hnewa,"#bar{#Lambda}","p");//l=line p=point f=box
  //aleg->AddEntry(hnewk0,"K^{0}_{s}","p");//l=line p=point f=box
  aleg->SetTextSize(0.02);
  aleg->SetFillColor(0);
  aleg->SetLineColor(0);
  max = P05idalam->GetMaximum();
  min = oldAntiLambda->GetMinimum();
  newAntiLambda->SetMaximum(max+.05);
  newAntiLambda->SetMinimum(min-.05);
  newAntiLambda->Draw();
  oldAntiLambda->Rebin(3);
  oldAntiLambda->Scale(1./3.);
  oldAntiLambda->Draw("same");
  P05idalam->Rebin(3);
  P05idalam->Scale(1./3.);
  P05idalam->Draw("same");
  aleg->Draw();
  c2->Print("AntiLambdaComparison.eps");
  c2->Print("AntiLambdaComparison.pdf");

  TCanvas *c3 = new TCanvas("c3","c3",500,400);
  c3->cd();
  c3->SetGridx(kFALSE);
  c3->SetGridy(kFALSE);
  TH1F *oldK0 = oldFile->Get("hDPhik0ch_1");
  TH1F *newK0 = newFile->Get("K0Cent0-10Pt20-30New");
  TH1F *P05idK0 = P05id->Get("hDPhik0ch_1")->Clone("P05idK0");
  oldK0->SetMarkerStyle(28);
  oldK0->SetMarkerColor(4);
  newK0->SetMarkerStyle(30);
  newK0->SetMarkerColor(2);
  P05idK0->SetMarkerStyle(24);
  P05idK0->SetMarkerColor(3);
  newK0->SetTitle( GetCorrelationHistoTitle("CuCu200",3,2,3,0,1,2,1) );
  kleg = new TLegend(0.7,0.85,0.98,0.98);//(left,bottom,right,top)  .25, .75, .8, .85
  kleg->AddEntry(newLambda,"K^{0}_{s} P06ib new code","p");//l=line p=point f=box
  kleg->AddEntry(oldLambda,"K^{0}_{s} P06ib old code","p");//l=line p=point f=box
  kleg->AddEntry(P05idK0,"K^{0}_{s} P05id old code","p");//l=line p=point f=box
  //aleg->AddEntry(hnewa,"#bar{#Lambda}","p");//l=line p=point f=box
  //aleg->AddEntry(hnewk0,"K^{0}_{s}","p");//l=line p=point f=box
  kleg->SetTextSize(0.02);
  kleg->SetFillColor(0);
  kleg->SetLineColor(0);
  max = P05idK0->GetMaximum();
  min = oldK0->GetMinimum();
  newK0->SetMaximum(max+.05);
  newK0->SetMinimum(min-.05);
  newK0->Draw();
  oldK0->Rebin(3);
  oldK0->Scale(1./3.);
  oldK0->Draw("same");
  P05idK0->Rebin(3);
  P05idK0->Scale(1./3.);
  P05idK0->Draw("same");
  kleg->Draw();
  c3->Print("K0sComparison.eps");
  c3->Print("K0sComparison.pdf");
}
