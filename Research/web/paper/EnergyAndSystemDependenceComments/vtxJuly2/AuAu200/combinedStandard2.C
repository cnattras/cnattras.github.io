void combinedStandard2(int mycb = 4,bool write = false){
  gROOT->LoadMacro("VtxCutBin10dEtadPhi_trig_h_pT30_60_assoc_h_pT15_100_CentBin42DdEtaMethod.C");
  //TH1D *hn10CB4 = Cut10CB4(0.5,-0.2);
  //return;
  gROOT->LoadMacro("VtxCutBin10dEtadPhi_trig_h_pT30_60_assoc_h_pT15_100_CentBin62DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBin14dEtadPhi_trig_h_pT30_60_assoc_h_pT15_100_CentBin42DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBin14dEtadPhi_trig_h_pT30_60_assoc_h_pT15_100_CentBin62DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBin18dEtadPhi_trig_h_pT30_60_assoc_h_pT15_100_CentBin42DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBin18dEtadPhi_trig_h_pT30_60_assoc_h_pT15_100_CentBin62DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBin22dEtadPhi_trig_h_pT30_60_assoc_h_pT15_100_CentBin42DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBin22dEtadPhi_trig_h_pT30_60_assoc_h_pT15_100_CentBin62DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBin26dEtadPhi_trig_h_pT30_60_assoc_h_pT15_100_CentBin42DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBin26dEtadPhi_trig_h_pT30_60_assoc_h_pT15_100_CentBin62DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBin2dEtadPhi_trig_h_pT30_60_assoc_h_pT15_100_CentBin42DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBin2dEtadPhi_trig_h_pT30_60_assoc_h_pT15_100_CentBin62DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBin6dEtadPhi_trig_h_pT30_60_assoc_h_pT15_100_CentBin42DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBin6dEtadPhi_trig_h_pT30_60_assoc_h_pT15_100_CentBin62DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBinn10dEtadPhi_trig_h_pT30_60_assoc_h_pT15_100_CentBin42DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBinn10dEtadPhi_trig_h_pT30_60_assoc_h_pT15_100_CentBin62DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBinn14dEtadPhi_trig_h_pT30_60_assoc_h_pT15_100_CentBin42DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBinn14dEtadPhi_trig_h_pT30_60_assoc_h_pT15_100_CentBin62DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBinn18dEtadPhi_trig_h_pT30_60_assoc_h_pT15_100_CentBin42DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBinn18dEtadPhi_trig_h_pT30_60_assoc_h_pT15_100_CentBin62DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBinn22dEtadPhi_trig_h_pT30_60_assoc_h_pT15_100_CentBin42DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBinn22dEtadPhi_trig_h_pT30_60_assoc_h_pT15_100_CentBin62DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBinn26dEtadPhi_trig_h_pT30_60_assoc_h_pT15_100_CentBin42DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBinn26dEtadPhi_trig_h_pT30_60_assoc_h_pT15_100_CentBin62DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBinn2dEtadPhi_trig_h_pT30_60_assoc_h_pT15_100_CentBin42DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBinn2dEtadPhi_trig_h_pT30_60_assoc_h_pT15_100_CentBin62DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBinn30dEtadPhi_trig_h_pT30_60_assoc_h_pT15_100_CentBin42DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBinn30dEtadPhi_trig_h_pT30_60_assoc_h_pT15_100_CentBin62DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBinn6dEtadPhi_trig_h_pT30_60_assoc_h_pT15_100_CentBin42DdEtaMethod.C");
  gROOT->LoadMacro("VtxCutBinn6dEtadPhi_trig_h_pT30_60_assoc_h_pT15_100_CentBin62DdEtaMethod.C");

  float max = 0.5;
  float min = -0.2;

   TH1D *hn2CB6 = Cutn2CB6(max,min);
   TH1D *h2CB6 = Cut2CB6(max,min);
   TH1D *hn2CB4 = Cutn2CB4(max,min);
   TH1D *h2CB4 = Cut2CB4(max,min);

   TH1D *hn6CB6 = Cutn6CB6(max,min);
   TH1D *h6CB6 = Cut6CB6(max,min);
   TH1D *hn6CB4 = Cutn6CB4(max,min);
   TH1D *h6CB4 = Cut6CB4(max,min);

   TH1D *hn10CB6 = Cutn10CB6(max,min);
   TH1D *h10CB6 = Cut10CB6(max,min);
   TH1D *hn10CB4 = Cutn10CB4(max,min);
   TH1D *h10CB4 = Cut10CB4(max,min);

   TH1D *hn14CB6 = Cutn14CB6(max,min);
   TH1D *h14CB6 = Cut14CB6(max,min);
   TH1D *hn14CB4 = Cutn14CB4(max,min);
   TH1D *h14CB4 = Cut14CB4(max,min);

   TH1D *hn18CB6 = Cutn18CB6(max,min);
   TH1D *h18CB6 = Cut18CB6(max,min);
   TH1D *hn18CB4 = Cutn18CB4(max,min);
   TH1D *h18CB4 = Cut18CB4(max,min);

   TH1D *hn22CB6 = Cutn22CB6(max,min);
   TH1D *h22CB6 = Cut22CB6(max,min);
   TH1D *hn22CB4 = Cutn22CB4(max,min);
   TH1D *h22CB4 = Cut22CB4(max,min);

   TH1D *hn26CB6 = Cutn26CB6(max,min);
   TH1D *h26CB6 = Cut26CB6(max,min);
   TH1D *hn26CB4 = Cutn26CB4(max,min);
   TH1D *h26CB4 = Cut26CB4(max,min);

   TH1D *hn30CB6 = Cutn30CB6(max,min);
   TH1D *hn30CB4 = Cutn30CB4(max,min);
//txtfiles/junkVtxCut10PtAssoc15Trig30To60CB4.txt:Number of trigger particles 121628
float ntrig10cb4 = 121628;
//txtfiles/junkVtxCut14PtAssoc15Trig30To60CB4.txt:Number of trigger particles 109841
float ntrig14cb4 = 109841;
//txtfiles/junkVtxCut18PtAssoc15Trig30To60CB4.txt:Number of trigger particles 96570
float ntrig18cb4 = 96570;
//txtfiles/junkVtxCut22PtAssoc15Trig30To60CB4.txt:Number of trigger particles 81558
float ntrig22cb4 = 81558;
//txtfiles/junkVtxCut26PtAssoc15Trig30To60CB4.txt:Number of trigger particles 65449
float ntrig26cb4 = 65449;
//txtfiles/junkVtxCut2PtAssoc15Trig30To60CB4.txt:Number of trigger particles 136725
float ntrig2cb4 = 136725;
//txtfiles/junkVtxCut6PtAssoc15Trig30To60CB4.txt:Number of trigger particles 130309
float ntrig6cb4 = 130309;
//txtfiles/junkVtxCutn10PtAssoc15Trig30To60CB4.txt:Number of trigger particles 128833
float ntrign10cb4 = 128833;
//txtfiles/junkVtxCutn14PtAssoc15Trig30To60CB4.txt:Number of trigger particles 93676
float ntrign14cb4 = 93676;
//txtfiles/junkVtxCutn18PtAssoc15Trig30To60CB4.txt:Number of trigger particles 83464
float ntrign18cb4 = 83464;
//txtfiles/junkVtxCutn22PtAssoc15Trig30To60CB4.txt:Number of trigger particles 70055
float ntrign22cb4 = 70055;
//txtfiles/junkVtxCutn26PtAssoc15Trig30To60CB4.txt:Number of trigger particles 51737
float ntrign26cb4 = 51737;
//txtfiles/junkVtxCutn2PtAssoc15Trig30To60CB4.txt:Number of trigger particles 139240
float ntrign2cb4 = 139240;
//txtfiles/junkVtxCutn30PtAssoc15Trig30To60CB4.txt:Number of trigger particles 33362
float ntrign30cb4 = 33362;
//txtfiles/junkVtxCutn6PtAssoc15Trig30To60CB4.txt:Number of trigger particles 136195
float ntrign6cb4 = 136195;


//txtfiles/junkVtxCut10PtAssoc15Trig30To60CB6.txt:Number of trigger particles 111002
float ntrig10cb6 = 111002;
//txtfiles/junkVtxCut14PtAssoc15Trig30To60CB6.txt:Number of trigger particles 100380
float ntrig14cb6 = 100380;
//txtfiles/junkVtxCut18PtAssoc15Trig30To60CB6.txt:Number of trigger particles 88119
float ntrig18cb6 = 88119;
//txtfiles/junkVtxCut22PtAssoc15Trig30To60CB6.txt:Number of trigger particles 75457
float ntrig22cb6 = 75457;
//txtfiles/junkVtxCut26PtAssoc15Trig30To60CB6.txt:Number of trigger particles 60092
float ntrig26cb6 = 60092;
//txtfiles/junkVtxCut2PtAssoc15Trig30To60CB6.txt:Number of trigger particles 124964
float ntrig2cb6 = 124964;
//txtfiles/junkVtxCut6PtAssoc15Trig30To60CB6.txt:Number of trigger particles 118298
float ntrig6cb6 = 118298;
//txtfiles/junkVtxCutn10PtAssoc15Trig30To60CB6.txt:Number of trigger particles 116530
float ntrign10cb6 = 116530;
//txtfiles/junkVtxCutn14PtAssoc15Trig30To60CB6.txt:Number of trigger particles 85409
float ntrign14cb6 = 85409;
//txtfiles/junkVtxCutn18PtAssoc15Trig30To60CB6.txt:Number of trigger particles 75563
float ntrign18cb6 = 75563;
//txtfiles/junkVtxCutn22PtAssoc15Trig30To60CB6.txt:Number of trigger particles 64093
float ntrign22cb6 = 64093;
//txtfiles/junkVtxCutn26PtAssoc15Trig30To60CB6.txt:Number of trigger particles 48478
float ntrign26cb6 = 48478;
//txtfiles/junkVtxCutn2PtAssoc15Trig30To60CB6.txt:Number of trigger particles 126075
float ntrign2cb6 = 126075;
//txtfiles/junkVtxCutn30PtAssoc15Trig30To60CB6.txt:Number of trigger particles 31571
float ntrign30cb6 = 31571;
//txtfiles/junkVtxCutn6PtAssoc15Trig30To60CB6.txt:Number of trigger particles 123010
float ntrign6cb6 = 123010;

 float totalLowz =0;
 float totalHighz = 0;

 if(mycb==4){
   totalLowz += ntrig2cb4;
   totalLowz += ntrign2cb4;
   totalLowz += ntrig6cb4;
   totalLowz += ntrign6cb4;
   totalLowz += ntrig10cb4;
   totalLowz += ntrign10cb4;
   totalLowz += ntrign14cb4;
 }
 else{
   totalLowz += ntrign10cb6;
   totalLowz += ntrig10cb6;
   totalLowz += ntrign6cb6;
   totalLowz += ntrign2cb6;
   totalLowz += ntrig2cb6;
   totalLowz += ntrig6cb6;
   totalLowz += ntrign14cb6;
 }
 cout<<"totalLowz "<<totalLowz<<endl;

 if(mycb==4){
   totalHighz += ntrig14cb4;
   totalHighz += ntrig18cb4;
   totalHighz += ntrign18cb4;
   totalHighz += ntrig22cb4;
   totalHighz += ntrign22cb4;
   totalHighz += ntrig26cb4;
   totalHighz += ntrign26cb4;
   totalHighz += ntrign30cb4;
 }
 else{
   totalHighz += ntrig18cb6;
   totalHighz += ntrig14cb6;
   totalHighz += ntrign18cb6;
   totalHighz += ntrig22cb6;
   totalHighz += ntrign22cb6;
   totalHighz += ntrig26cb6;
   totalHighz += ntrign26cb6;
   totalHighz += ntrign30cb6;
 }
 cout<<"totalHighz "<<totalHighz<<endl;

 float totaln2to2,total2to6,total6to14,total14to22,total22to30,totaln22to30,totaln14to22,totaln6to14,totaln2to6;

 if(mycb==4){
   totaln2to2 =ntrign2cb4;
   total2to6 =ntrig2cb4;
   total6to14 =ntrig6cb4+ntrig10cb4;
   total14to22 =ntrig14cb4+ntrig18cb4;
   total22to30 =ntrig22cb4+ntrig26cb4;
   totaln22to30 =ntrign30cb4+ntrign26cb4;
   totaln14to22 =ntrign22cb4+ntrign18cb4;
   totaln6to14 =ntrign14cb4+ntrign10cb4;
   totaln2to6 =ntrign6cb4;
 }
 else{
   totaln2to2 =ntrign2cb6;
   total2to6 =ntrig2cb6;
   total6to14 =ntrig6cb6+ntrig10cb6;
   total14to22 =ntrig14cb6+ntrig18cb6;
   total22to30 =ntrig22cb6+ntrig26cb6;
   totaln22to30 =ntrign30cb6+ntrign26cb6;
   totaln14to22 =ntrign22cb6+ntrign18cb6;
   totaln6to14 =ntrign14cb6+ntrign10cb6;
   totaln2to6 =ntrign6cb6;
 }

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

 TH1D *lowz;
 if(mycb==4) lowz = (TH1D*)hn2CB4->Clone("lowz");
 else{lowz = (TH1D*)hn2CB6->Clone("lowz");}
 if(mycb==4){
   lowz->Scale(ntrign2cb4/totalLowz);
   lowz->Add(h2CB4,ntrig2cb4/totalLowz);
   lowz->Add(hn6CB4,ntrign6cb4/totalLowz);
   lowz->Add(h6CB4,ntrig6cb4/totalLowz);
   lowz->Add(hn10CB4,ntrign10cb4/totalLowz);
   lowz->Add(h10CB4,ntrig10cb4/totalLowz);
   lowz->Add(hn14CB4,ntrign14cb4/totalLowz);
 }
 else{
   lowz->Scale(ntrign2cb6/totalLowz);
   lowz->Add(h2CB6,ntrig2cb6/totalLowz);
   lowz->Add(hn6CB6,ntrign6cb6/totalLowz);
   lowz->Add(h6CB6,ntrig6cb6/totalLowz);
   lowz->Add(hn10CB6,ntrign10cb6/totalLowz);
   lowz->Add(h10CB6,ntrig10cb6/totalLowz);
   lowz->Add(hn14CB6,ntrign14cb6/totalLowz);
 }



 TH1D *highz;
 if(mycb==4) highz =(TH1D*) h14CB4->Clone("highz");//14-18 cm
 else{highz =(TH1D*) h14CB6->Clone("highz");}//14-18 cm

 if(mycb==4){
   highz->Scale(ntrig14cb4/totalHighz);
   highz->Add(h18CB4,ntrig14cb4/totalHighz);
   highz->Add(hn18CB4,ntrign14cb4/totalHighz);
   highz->Add(h22CB4,ntrig22cb4/totalHighz);
   highz->Add(hn22CB4,ntrign22cb4/totalHighz);
   highz->Add(h26CB4,ntrig26cb4/totalHighz);
   highz->Add(hn26CB4,ntrign26cb4/totalHighz);
   highz->Add(hn30CB4,ntrign30cb4/totalHighz);
 }
 else{
   highz->Scale(ntrig14cb6/totalHighz);
   highz->Add(h18CB6,ntrig14cb6/totalHighz);
   highz->Add(hn18CB6,ntrign14cb6/totalHighz);
   highz->Add(h22CB6,ntrig22cb6/totalHighz);
   highz->Add(hn22CB6,ntrign22cb6/totalHighz);
   highz->Add(h26CB6,ntrig26cb6/totalHighz);
   highz->Add(hn26CB6,ntrign26cb6/totalHighz);
   highz->Add(hn30CB6,ntrign30cb6/totalHighz);
 }



 TH1D *hn2to2;
 TH1D *h2to2;
 TH1D *h6to14;
 TH1D *hn6to14;
 TH1D *h14to22;
 TH1D *hn14to22;
 TH1D *hn6to14;
 TH1D *h6to14;

 if(mycb==4){
   hn2to2 = (TH1D*)hn2CB4->Clone("hn2to2");
   hn2to2->Scale(ntrign2cb4/totaln2to2);
   h2to6 = (TH1D*)h2CB4->Clone("h2to6");
   h2to6->Scale(ntrig2cb4/total2to6);
   h6to14 =(TH1D*) h6CB4->Clone("h6to14");
   h6to14->Scale(ntrig6cb4/total6to14);
   h6to14->Add(h10CB4,ntrig10cb4/total6to14);
   h14to22 =(TH1D*) h14CB4->Clone("h14to22");
   h14to22->Scale(ntrig14cb4/total14to22);
   h14to22->Add(h18CB4,ntrig18cb4/total14to22);
   h22to30 = (TH1D*)h22CB4->Clone("h22to30");
   h22to30->Scale(ntrig22cb4/total22to30);
   h22to30->Add(h26CB4,ntrig26cb4/total22to30);
   hn22to30 =(TH1D*) hn30CB4->Clone("hn22to30");
   hn22to30->Scale(ntrign30cb4/totaln22to30);
   hn22to30->Add(hn26CB4,ntrign26cb4/totaln22to30);
   hn14to22 = (TH1D*)hn22CB4->Clone("hn14to22");
   hn14to22->Scale(ntrign22cb4/totaln14to22);
   hn14to22->Add(hn18CB4,ntrign18cb4/totaln14to22);
   hn6to14 =(TH1D*) hn14CB4->Clone("hn6to14");
   hn6to14->Scale(ntrign14cb4/totaln6to14);
   hn6to14->Add(hn10CB4,ntrign10cb4/totaln6to14);
   hn2to6 = (TH1D*)hn6CB4->Clone("hn2to6");
   hn2to6->Scale(ntrign6cb4/totaln2to6);
 }
 else{
   hn2to2 = (TH1D*)hn2CB6->Clone("hn2to2");
   hn2to2->Scale(ntrign2cb6/totaln2to2);
   h2to6 =(TH1D*) h2CB6->Clone("h2to6");
   h2to6->Scale(ntrig2cb6/total2to6);
   h6to14 =(TH1D*) h6CB6->Clone("h6to14");
   h6to14->Scale(ntrig6cb6/total6to14);
   h6to14->Add(h10CB6,ntrig10cb6/total6to14);
   h14to22 =(TH1D*) h14CB6->Clone("h14to22");
   h14to22->Scale(ntrig14cb6/total14to22);
   h14to22->Add(h18CB6,ntrig18cb6/total14to22);
   h22to30 =(TH1D*) h22CB6->Clone("h22to30");
   h22to30->Scale(ntrig22cb6/total22to30);
   h22to30->Add(h26CB6,ntrig26cb6/total22to30);
   hn22to30 =(TH1D*) hn30CB6->Clone("hn22to30");
   hn22to30->Scale(ntrign30cb6/totaln22to30);
   hn22to30->Add(hn26CB6,ntrign26cb6/totaln22to30);
   hn14to22 =(TH1D*) hn22CB6->Clone("hn14to22");
   hn14to22->Scale(ntrign22cb6/totaln14to22);
   hn14to22->Add(hn18CB6,ntrign18cb6/totaln14to22);
   hn6to14 = (TH1D*)hn14CB6->Clone("hn6to14");
   hn6to14->Scale(ntrign14cb6/totaln6to14);
   hn6to14->Add(hn10CB6,ntrign10cb6/totaln6to14);
   hn2to6 =(TH1D*) hn6CB6->Clone("hn2to6");
   hn2to6->Scale(ntrign6cb6/totaln2to6);
 }



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
   float nominalpeak = total->GetBinContent(total->FindBin(0.0));
   float lowpeak = lowz->GetBinContent(lowz->FindBin(0.0));
   float scalediff =(nominalpeak-lowpeak)/nominalpeak ;//( total->GetMaximum()-lowz->GetMaximum() )/ total->GetMaximum();
   float myscale = lowpeak/nominalpeak ;//lowz->GetMaximum()/total->GetMaximum();
   //now to get the error because these have slightly different dphi ranges we need another scale...
   //this is the peak in the dphi range used in the paper divided by the nominal range
   float scaleforerror = 5.487713/nominalpeak;
   //cout<<"nominal peak "<<nominalpeak<<" lowpeak "<<lowpeak<<"Scale difference "<< scalediff<<" scale "<<myscale<<" scaleforerror "<<scaleforerror<<endl;
   int point = 0;
   cout<<"Nbins "<<total->GetNbinsX()<<endl;
   for(int i=1;i<=total->GetNbinsX();i++){
     float nominal = total->GetBinContent(i);
     float lower = lowz->GetBinContent(i);
     //float err = (nominal - lower)/nominal;
     //cout<<"eta "<<total->GetBinCenter(i)<<" nominal "<<nominal<<" lower "<<lower<<" error "<< nominal-lower/myscale<<" error for paper "<<scaleforerror*(nominal-lower/myscale) <<" % ";
     //if(TMath::Abs(nominal)>1e-4) cout<< (nominal-lower/myscale)/nominal*100;
     //cout<<endl;
     //sets the upper bound at the nominal value
     if(TMath::Abs(total->GetBinCenter(i))<1.755){
       cout<<"YieldAuAu200Error->SetPoint("<<point<<","
	   <<"AuAu200EtaJet->GetBinCenter(AuAu200EtaJet->FindBin("<<total->GetBinCenter(i)<<"))"//total->GetBinCenter(i)
	   <<",AuAu200EtaJet->GetBinContent(AuAu200EtaJet->FindBin("<<total->GetBinCenter(i)<<")));"<<endl;
       point++;
     }
   }
   for(int i=total->GetNbinsX();i>=1;i--){
     float nominal = total->GetBinContent(i);
     float lower = lowz->GetBinContent(i);
     float err = scaleforerror*(nominal-lower/myscale);
     //sets the lower bound at the nominal value minus the error
     if(TMath::Abs(total->GetBinCenter(i))<1.755){
       cout<<"YieldAuAu200Error->SetPoint("<<point<<","
	 //<<total->GetBinCenter(i)
	   <<"AuAu200EtaJet->GetBinCenter(AuAu200EtaJet->FindBin("<<total->GetBinCenter(i)<<"))"//total->GetBinCenter(i)
	   <<",AuAu200EtaJet->GetBinContent(AuAu200EtaJet->FindBin("<<total->GetBinCenter(i)<<")) + "<<TMath::Abs(err)<<");"<<endl;
       point++;
     }
   }
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
   canvas->SaveAs("comparisonStandard.png");
   canvas->SaveAs("comparisonStandard.C");

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
   canvasratio->SaveAs("comparisonratioStandard.png");

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
   canvasposneg->SaveAs("comparisonposnegStandard.png");


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
   total->SetMarkerStyle(3);
   total->Draw("same");
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
   canvasMany->SaveAs("comparisonManyStandard.png");
   if(write){
     if(mycb==4){
       canvasMany->SaveAs("comparisonManyStandardCB20to30.C");
     }
     else{
       canvasMany->SaveAs("comparisonManyStandardCB40to80.C");
     }
   }


}
 
