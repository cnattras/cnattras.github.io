void combined(){
  gROOT->LoadMacro("VtxCutBin10dEtadPhi_trig_h_pT30_60_assoc_h_pT10_100_CentBin12DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBin10dEtadPhi_trig_h_pT30_60_assoc_h_pT10_100_CentBin22DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBin14dEtadPhi_trig_h_pT30_60_assoc_h_pT10_100_CentBin12DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBin14dEtadPhi_trig_h_pT30_60_assoc_h_pT10_100_CentBin22DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBin18dEtadPhi_trig_h_pT30_60_assoc_h_pT10_100_CentBin12DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBin18dEtadPhi_trig_h_pT30_60_assoc_h_pT10_100_CentBin22DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBin22dEtadPhi_trig_h_pT30_60_assoc_h_pT10_100_CentBin12DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBin22dEtadPhi_trig_h_pT30_60_assoc_h_pT10_100_CentBin22DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBin26dEtadPhi_trig_h_pT30_60_assoc_h_pT10_100_CentBin12DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBin26dEtadPhi_trig_h_pT30_60_assoc_h_pT10_100_CentBin22DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBin2dEtadPhi_trig_h_pT30_60_assoc_h_pT10_100_CentBin12DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBin2dEtadPhi_trig_h_pT30_60_assoc_h_pT10_100_CentBin22DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBin6dEtadPhi_trig_h_pT30_60_assoc_h_pT10_100_CentBin12DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBin6dEtadPhi_trig_h_pT30_60_assoc_h_pT10_100_CentBin22DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBinn10dEtadPhi_trig_h_pT30_60_assoc_h_pT10_100_CentBin12DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBinn10dEtadPhi_trig_h_pT30_60_assoc_h_pT10_100_CentBin22DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBinn14dEtadPhi_trig_h_pT30_60_assoc_h_pT10_100_CentBin12DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBinn14dEtadPhi_trig_h_pT30_60_assoc_h_pT10_100_CentBin22DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBinn18dEtadPhi_trig_h_pT30_60_assoc_h_pT10_100_CentBin12DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBinn18dEtadPhi_trig_h_pT30_60_assoc_h_pT10_100_CentBin22DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBinn22dEtadPhi_trig_h_pT30_60_assoc_h_pT10_100_CentBin12DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBinn22dEtadPhi_trig_h_pT30_60_assoc_h_pT10_100_CentBin22DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBinn26dEtadPhi_trig_h_pT30_60_assoc_h_pT10_100_CentBin12DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBinn26dEtadPhi_trig_h_pT30_60_assoc_h_pT10_100_CentBin22DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBinn2dEtadPhi_trig_h_pT30_60_assoc_h_pT10_100_CentBin12DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBinn2dEtadPhi_trig_h_pT30_60_assoc_h_pT10_100_CentBin22DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBinn30dEtadPhi_trig_h_pT30_60_assoc_h_pT10_100_CentBin12DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBinn30dEtadPhi_trig_h_pT30_60_assoc_h_pT10_100_CentBin22DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBinn6dEtadPhi_trig_h_pT30_60_assoc_h_pT10_100_CentBin12DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBinn6dEtadPhi_trig_h_pT30_60_assoc_h_pT10_100_CentBin22DdEtaMethod.C");

  float max = 0.5;
  float min = -0.2;

   TH1D *hn2CB2 = Cutn2CB2(max,min);
   TH1D *h2CB2 = Cut2CB2(max,min);
   TH1D *hn2CB1 = Cutn2CB1(max,min);
   TH1D *h2CB1 = Cut2CB1(max,min);

   TH1D *hn6CB2 = Cutn6CB2(max,min);
   TH1D *h6CB2 = Cut6CB2(max,min);
   TH1D *hn6CB1 = Cutn6CB1(max,min);
   TH1D *h6CB1 = Cut6CB1(max,min);

   TH1D *hn10CB2 = Cutn10CB2(max,min);
   TH1D *h10CB2 = Cut10CB2(max,min);
   TH1D *hn10CB1 = Cutn10CB1(max,min);
   TH1D *h10CB1 = Cut10CB1(max,min);

   TH1D *hn14CB2 = Cutn14CB2(max,min);
   TH1D *h14CB2 = Cut14CB2(max,min);
   TH1D *hn14CB1 = Cutn14CB1(max,min);
   TH1D *h14CB1 = Cut14CB1(max,min);

   TH1D *hn18CB2 = Cutn18CB2(max,min);
   TH1D *h18CB2 = Cut18CB2(max,min);
   TH1D *hn18CB1 = Cutn18CB1(max,min);
   TH1D *h18CB1 = Cut18CB1(max,min);

   TH1D *hn22CB2 = Cutn22CB2(max,min);
   TH1D *h22CB2 = Cut22CB2(max,min);
   TH1D *hn22CB1 = Cutn22CB1(max,min);
   TH1D *h22CB1 = Cut22CB1(max,min);

   TH1D *hn26CB2 = Cutn26CB2(max,min);
   TH1D *h26CB2 = Cut26CB2(max,min);
   TH1D *hn26CB1 = Cutn26CB1(max,min);
   TH1D *h26CB1 = Cut26CB1(max,min);

   TH1D *hn30CB2 = Cutn30CB2(max,min);
   TH1D *hn30CB1 = Cutn30CB1(max,min);

//    Pics/tmp/junkVtxCut10.2.txt 
float ntrig10cb2 = 590896;
//    Pics/tmp/junkVtxCut10.txt 
float ntrig10cb1 = 662497;
//    Pics/tmp/junkVtxCut14.2.txt 
float ntrig14cb2 = 531135;
//    Pics/tmp/junkVtxCut14.txt 
float ntrig14cb1 = 594288;
//    Pics/tmp/junkVtxCut18.2.txt 
float ntrig18cb2 = 458017;
//    Pics/tmp/junkVtxCut18.txt 
float ntrig18cb1 = 493440;
//    Pics/tmp/junkVtxCut22.2.txt 
float ntrig22cb2 = 355609;
//    Pics/tmp/junkVtxCut2.2.txt 
float ntrig2cb2 = 656963;
//    Pics/tmp/junkVtxCut22.txt 
float ntrig22cb1 = 726976;
//    Pics/tmp/junkVtxCut26.2.txt 
float ntrig26cb2 = 238166;
//    Pics/tmp/junkVtxCut26.txt 
float ntrig26cb1 = 237605;
//    Pics/tmp/junkVtxCut2.txt 
float ntrig2cb1 = 730692;
//    Pics/tmp/junkVtxCut6.2.txt 
float ntrig6cb2 = 634253;
//    Pics/tmp/junkVtxCut6.txt 
float ntrig6cb1 = 710068;

//    Pics/tmp/junkVtxCutn10.2.txt 
float ntrign10cb2 = 599199;
//    Pics/tmp/junkVtxCutn10.txt 
float ntrign10cb1 = 663531;
//    Pics/tmp/junkVtxCutn14.2.txt 
float ntrign14cb2 = 536463;
//    Pics/tmp/junkVtxCutn14.txt 
float ntrign14cb1 = 588336;;
//    Pics/tmp/junkVtxCutn18.2.txt 
float ntrign18cb2 = 440609;
//    Pics/tmp/junkVtxCutn18.txt 
float ntrign18cb1 = 477292;
//    Pics/tmp/junkVtxCutn22.2.txt 
float ntrign22cb2 = 324207;
//    Pics/tmp/junkVtxCutn2.2.txt 
float ntrign2cb2 = 659086;
//    Pics/tmp/junkVtxCutn22.txt 
float ntrign22cb1 = 329406;
//    Pics/tmp/junkVtxCutn26.2.txt 
float ntrign26cb2 = 198258;
//    Pics/tmp/junkVtxCutn26.txt 
float ntrign26cb1 = 184908;
//    Pics/tmp/junkVtxCutn2.txt 
float ntrign2cb1 = 733164;
//    Pics/tmp/junkVtxCutn30.2.txt 
float ntrign30cb2 = 99911;
//    Pics/tmp/junkVtxCutn30.txt 
float ntrign30cb1 = 82041;
//    Pics/tmp/junkVtxCutn6.2.txt 
float ntrign6cb2 = 641297;
//    Pics/tmp/junkVtxCutn6.txt 
float ntrign6cb1 = 709593;

 float totalLowz =0;
 float totalHighz = 0;

 totalLowz += ntrig2cb2;
 totalLowz += ntrig2cb1;
 totalLowz += ntrign2cb2;
 totalLowz += ntrign2cb1;
 totalLowz += ntrig6cb2;
 totalLowz += ntrig6cb1;
 totalLowz += ntrign6cb2;
 totalLowz += ntrign6cb1;
 totalLowz += ntrig10cb2;
 totalLowz += ntrig10cb1;
 totalLowz += ntrign10cb2;
 totalLowz += ntrign10cb1;
 totalLowz += ntrign14cb2;
 totalLowz += ntrign14cb1;
 cout<<"totalLowz "<<totalLowz<<endl;

 totalHighz += ntrig14cb2;
 totalHighz += ntrig14cb1;
 totalHighz += ntrig18cb2;
 totalHighz += ntrig18cb1;
 totalHighz += ntrign18cb2;
 totalHighz += ntrign18cb1;
 totalHighz += ntrig22cb2;
 totalHighz += ntrig22cb1;
 totalHighz += ntrign22cb2;
 totalHighz += ntrign22cb1;
 totalHighz += ntrig26cb2;
 totalHighz += ntrig26cb1;
 totalHighz += ntrign26cb2;
 totalHighz += ntrign26cb1;
 totalHighz += ntrign30cb2;
 totalHighz += ntrign30cb1;
 cout<<"totalHighz "<<totalHighz<<endl;


 float totaln2to2 =ntrign2cb1+ntrign2cb2;
 float total2to6 =ntrig2cb1+ntrig2cb2;
 float total6to14 =ntrig6cb1+ntrig6cb2+ntrig10cb1+ntrig10cb2;
 float total14to22 =ntrig14cb1+ntrig14cb2+ntrig18cb1+ntrig18cb2;
 float total22to30 =ntrig22cb1+ntrig22cb2+ntrig26cb1+ntrig26cb2;
 float totaln22to30 =ntrign30cb1+ntrign30cb2+ntrign26cb1+ntrign26cb2;
 float totaln14to22 =ntrign22cb1+ntrign22cb2+ntrign18cb1+ntrign18cb2;
 float totaln6to14 =ntrign14cb1+ntrign14cb2+ntrign10cb1+ntrign10cb2;
 float totaln2to6 =ntrign6cb1+ntrign6cb2;

 float totalNegative = totaln2to6+totaln6to14+totaln14to22+totaln22to30;
 float totalPositive = total2to6 +total6to14 +total14to22 +total22to30 ;

 float totalNarrow = totaln2to2+total2to6+totaln2to6;

 cout<<"-2 to 2 "<<totaln2to2<<endl;
 cout<<"2 to 6 "<<total2to6<<endl;
 cout<<"-6 to -2 "<<totaln2to6<<endl;
 cout<<"6 to 14 "<<total6to14<<endl;
 cout<<"-14 to -6 "<<totaln6to14<<endl;
 cout<<"14 to 22 "<<total14to22<<endl;
 cout<<"-22 to -14 "<<totaln14to22<<endl;
 cout<<"22 to 30 "<<total22to30<<endl;
 cout<<"-30 to -22 "<<totaln22to30<<endl;
 float totaltest =  totaln2to2 + total2to6+ totaln2to6+totaln6to14+total6to14+total14to22+totaln14to22+total22to30+totaln22to30;
 cout<<"total "<<totaltest<<" "<<totalHighz+totalLowz<<endl;

   TH1D *lowz = hn2CB2->Clone("lowz");
   lowz->Scale(ntrign2cb2/totalLowz);
   lowz->Add(h2CB2,ntrig2cb2/totalLowz);
   lowz->Add(hn2CB1,ntrign2cb1/totalLowz);
   lowz->Add(h2CB1,ntrig2cb1/totalLowz);

   lowz->Add(hn6CB2,ntrign6cb2/totalLowz);
   lowz->Add(h6CB2,ntrig6cb2/totalLowz);
   lowz->Add(hn6CB1,ntrign6cb1/totalLowz);
   lowz->Add(h6CB1,ntrig6cb1/totalLowz);

   lowz->Add(hn10CB2,ntrign10cb2/totalLowz);
   lowz->Add(h10CB2,ntrig10cb2/totalLowz);
   lowz->Add(hn10CB1,ntrign10cb1/totalLowz);
   lowz->Add(h10CB1,ntrig10cb1/totalLowz);

   lowz->Add(hn14CB2,ntrign14cb2/totalLowz);
   lowz->Add(hn14CB1,ntrign14cb1/totalLowz);

   TH1D *highz = h14CB2->Clone("highz");//14-18 cm
   highz->Scale(ntrig14cb2/totalHighz);
   highz->Add(h14CB1,ntrig14cb1/totalHighz);

   highz->Add(h18CB1,ntrig14cb1/totalHighz);
   highz->Add(h18CB2,ntrig14cb2/totalHighz);
   highz->Add(hn18CB1,ntrign14cb1/totalHighz);
   highz->Add(hn18CB2,ntrign14cb2/totalHighz);

   highz->Add(h22CB1,ntrig22cb1/totalHighz);
   highz->Add(h22CB2,ntrig22cb2/totalHighz);
   highz->Add(hn22CB1,ntrign22cb1/totalHighz);
   highz->Add(hn22CB2,ntrign22cb2/totalHighz);

   highz->Add(h26CB1,ntrig26cb1/totalHighz);
   highz->Add(h26CB2,ntrig26cb2/totalHighz);
   highz->Add(hn26CB1,ntrign26cb1/totalHighz);
   highz->Add(hn26CB2,ntrign26cb2/totalHighz);

   highz->Add(hn30CB1,ntrign30cb1/totalHighz);
   highz->Add(hn30CB2,ntrign30cb2/totalHighz);


   TH1D *hn2to2 = hn2CB2->Clone("hn2to2");
   hn2to2->Scale(ntrign2cb2/totaln2to2);
   hn2to2->Add(h2CB1,ntrig2cb1/totaln2to2);

   TH1D *h2to6 = h2CB2->Clone("h2to6");
   h2to6->Scale(ntrig2cb2/total2to6);
   h2to6->Add(h2CB1,ntrig2cb1/total2to6);

   TH1D *h6to14 = h6CB2->Clone("h6to14");
   h6to14->Scale(ntrig6cb2/total6to14);
   h6to14->Add(h6CB1,ntrig6cb1/total6to14);
   h6to14->Add(h10CB2,ntrig10cb2/total6to14);
   h6to14->Add(h10CB1,ntrig10cb1/total6to14);

   TH1D *h14to22 = h14CB2->Clone("h14to22");
   h14to22->Scale(ntrig14cb2/total14to22);
   h14to22->Add(h14CB1,ntrig14cb1/total14to22);
   h14to22->Add(h18CB2,ntrig18cb2/total14to22);
   h14to22->Add(h18CB1,ntrig18cb1/total14to22);

   TH1D *h22to30 = h22CB2->Clone("h22to30");
   h22to30->Scale(ntrig22cb2/total22to30);
   h22to30->Add(h22CB1,ntrig22cb1/total22to30);
   h22to30->Add(h26CB2,ntrig26cb2/total22to30);
   h22to30->Add(h26CB1,ntrig26cb1/total22to30);

   TH1D *hn22to30 = hn30CB2->Clone("hn22to30");
   hn22to30->Scale(ntrign30cb2/totaln22to30);
   hn22to30->Add(hn30CB1,ntrign30cb1/totaln22to30);
   hn22to30->Add(hn26CB2,ntrign26cb2/totaln22to30);
   hn22to30->Add(hn26CB1,ntrign26cb1/totaln22to30);

   TH1D *hn14to22 = hn22CB2->Clone("hn14to22");
   hn14to22->Scale(ntrign22cb2/totaln14to22);
   hn14to22->Add(hn22CB1,ntrign22cb1/totaln14to22);
   hn14to22->Add(hn18CB2,ntrign18cb2/totaln14to22);
   hn14to22->Add(hn18CB1,ntrign18cb1/totaln14to22);

   TH1D *hn6to14 = hn14CB2->Clone("hn6to14");
   hn6to14->Scale(ntrign14cb2/totaln6to14);
   hn6to14->Add(hn14CB1,ntrign14cb1/totaln6to14);
   hn6to14->Add(hn10CB2,ntrign10cb2/totaln6to14);
   hn6to14->Add(hn10CB1,ntrign10cb1/totaln6to14);

   TH1D *hn2to6 = hn6CB2->Clone("hn2to6");
   hn2to6->Scale(ntrign6cb2/totaln2to6);
   hn2to6->Add(hn6CB1,ntrign6cb1/totaln2to6);

   TH1D *hNegative = hn22to30->Clone("hNegative");
   hNegative->Scale(totaln22to30/totalNegative);
   hNegative->Add(hn14to22,totaln14to22/totalNegative);
   hNegative->Add(hn6to14,totaln6to14/totalNegative);
   hNegative->Add(hn2to6,totaln2to6/totalNegative);

   TH1D *hPositive = h22to30->Clone("hPositive");
   hPositive->Scale(total22to30/totalPositive);
   hPositive->Add(h14to22,total14to22/totalPositive);
   hPositive->Add(h6to14,total6to14/totalPositive);
   hPositive->Add(h2to6,total2to6/totalPositive);

   TH1D *hNarrow = hn2to2->Clone("hNarrow");
   hNarrow->Scale(totaln2to2/totalNarrow);
   hNarrow->Add(hn2to6,totaln2to6/totalNarrow);
   hNarrow->Add(h2to6,total2to6/totalNarrow);

   TH1D *hTotal6to14 = h6to14->Clone("hTotal6to14");
   hTotal6to14->Scale(total6to14/(total6to14+totaln6to14));
   hTotal6to14->Add(hn6to14,totaln6to14/(total6to14+totaln6to14));

   TH1D *hTotal14to22 = h14to22->Clone("hTotal14to22");
   hTotal14to22->Scale(total14to22/(total14to22+totaln14to22));
   hTotal14to22->Add(hn14to22,totaln14to22/(total14to22+totaln14to22));

   TH1D *hTotal22to30 = h22to30->Clone("hTotal22to30");
   hTotal22to30->Scale(total22to30/(total22to30+totaln22to30));
   hTotal22to30->Add(hn22to30,totaln22to30/(total22to30+totaln22to30));

   TCanvas *canvas = new TCanvas("canvas", "canvas",0,0,500,400);
   gStyle->SetOptStat(0);
   canvas->Range(0,0,1,1);
   canvas->SetBorderSize(2);
   canvas->SetFrameFillColor(0);
   TH1D *total = (TH1D*) highz->Clone("total");
   total->Scale(totalHighz/(totalLowz+totalHighz));
   total->Add(lowz,totalLowz/(totalLowz+totalHighz));
   total->SetLineColor(1);
   TF1 *constBkgd = new TF1("constBkgd","[0]",-1.99,1.99);
   constBkgd->SetParameter(0,total->GetMaximum()-highz->GetMaximum());
   highz->Add(constBkgd);
   constBkgd->SetParameter(0,total->GetMaximum()-lowz->GetMaximum());
   lowz->Add(constBkgd);
   highz->SetMaximum(0.5);
   highz->SetLineColor(4);
   highz->Draw();
   //float scale = (highz->GetMaximum() - highz->GetMinimum()) / (lowz->GetMaximum() - lowz->GetMinimum()) ;
   //float scale = 1.05;
   //cout<<"Scale "<<scale<<endl;
   //lowz->Scale(scale);
   lowz->SetLineColor(2);
   lowz->Draw("same");
   total->Draw("same");
   TLegend *leg = new TLegend(0.243952,0.188172,0.344758,0.384409);
   leg->SetBorderSize(1);
   leg->SetTextSize(0.0537634);
   leg->SetLineColor(0);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   leg->AddEntry(total,"total");
   leg->AddEntry(lowz,"|Vtx_{z}|<14 cm");
   leg->AddEntry(highz,"14 cm<|Vtx_{z}|<30 cm");
   leg->Draw();
   canvas->SaveAs("comparison.png");
   canvas->SaveAs("comparison.C");

   TCanvas *canvasratio = new TCanvas("canvasratio", "canvasratio",0,0,500,400);
   gStyle->SetOptStat(0);
   canvasratio->Range(0,0,1,1);
   canvasratio->SetBorderSize(2);
   canvasratio->SetFrameFillColor(0);
   canvasratio->cd();
   highz->Divide(total);
   lowz->Divide(total);
   highz->SetMaximum(3.0);
   highz->SetMinimum(-1.0);
   highz->Draw();
   lowz->Draw("same");
   canvasratio->SaveAs("comparisonratio.png");

   TCanvas *canvasposneg = new TCanvas("canvasposneg", "canvasposneg",0,0,500,400);
   gStyle->SetOptStat(0);
   canvasposneg->Range(0,0,1,1);
   canvasposneg->SetBorderSize(2);
   canvasposneg->SetFrameFillColor(0);
   canvasposneg->cd();
   total->Draw();
   hPositive->SetLineColor(2);
   hNegative->SetLineColor(4);
   hNegative->Draw("same");
   hPositive->Draw("same");
   canvasposneg->SaveAs("comparisonposneg.png");


   TCanvas *canvasMany = new TCanvas("canvasMany", "canvasMany",0,0,500,400);
   canvasMany->Range(0,0,1,1);
   canvasMany->SetBorderSize(2);
   canvasMany->SetFrameFillColor(0);

   constBkgd->SetParameter(0,total->GetMaximum()-hNarrow->GetMaximum());
   hNarrow->Add(constBkgd);
   constBkgd->SetParameter(0,total->GetMaximum()-hTotal6to14->GetMaximum());
   hTotal6to14->Add(constBkgd);
   constBkgd->SetParameter(0,total->GetMaximum()-hTotal14to22->GetMaximum());
   hTotal14to22->Add(constBkgd);
   constBkgd->SetParameter(0,total->GetMaximum()-hTotal22to30->GetMaximum());
   hTotal22to30->Add(constBkgd);
   hNarrow->SetMarkerStyle(20);
   hNarrow->SetLineColor(2);
   hNarrow->SetMarkerColor(2);
   hTotal6to14->SetMarkerStyle(21);
   hTotal6to14->SetLineColor(4);
   hTotal6to14->SetMarkerColor(4);
   hTotal14to22->SetMarkerStyle(22);
   hTotal14to22->SetLineColor(TColor::kGreen+4);
   hTotal14to22->SetMarkerColor(TColor::kGreen+4);
   hTotal22to30->SetMarkerStyle(23);
   hTotal22to30->SetLineColor(TColor::kOrange+1);
   hTotal22to30->SetMarkerColor(TColor::kOrange+1);
   total->Draw();
   hNarrow->Draw("same");
   hTotal6to14->Draw("same");
   hTotal14to22->Draw("same");
   hTotal22to30->Draw("same");
   TLegend *leg2 = new TLegend(0.243952,0.188172,0.344758,0.494624);
   leg2->SetBorderSize(1);
   leg2->SetTextSize(0.0537634);
   leg2->SetLineColor(0);
   leg2->SetLineStyle(1);
   leg2->SetLineWidth(1);
   leg2->SetFillColor(0);
   leg2->SetFillStyle(1001);
   leg2->AddEntry(total,"total");
   leg2->AddEntry(hNarrow,"|Vtx_{z}|<6 cm");
   leg2->AddEntry(hTotal6to14,"6 cm<|Vtx_{z}|<14 cm");
   leg2->AddEntry(hTotal14to22,"14 cm<|Vtx_{z}|<22 cm");
   leg2->AddEntry(hTotal22to30,"22 cm<|Vtx_{z}|<30 cm");
   leg2->Draw();
   canvasMany->SaveAs("comparisonMany.png");
   canvasMany->SaveAs("comparisonMany.C");


}
