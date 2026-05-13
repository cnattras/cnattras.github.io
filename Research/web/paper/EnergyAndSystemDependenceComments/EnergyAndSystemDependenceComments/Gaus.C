void Gaus(){

  func1 = new TF1("fv3","cos(3*x)*(exp(-0.5*((x-[1])/[0])^2)+exp(-0.5*((x+[1])/[0])^2))", -TMath::Pi(),TMath::Pi());
  func2 = new TF1("fv3","exp(-0.5*((x-[1])/[0])^2)+exp(-0.5*((x+[1])/[0])^2) ", -TMath::Pi(),TMath::Pi());
  func1->SetParameter(1,TMath::Pi());
  func2->SetParameter(1,TMath::Pi());
  TH1F *histo = new TH1F("histo","v_{3} vs Gaussian width",1000,0,TMath::Pi());
  //float width = 0.5;
  TGraph *graph = new TGraph(63);
  int npoints = 0;
  for(float width = 0.05; width<TMath::Pi(); width+=0.05){
    func1->SetParameter(0,width);
    func2->SetParameter(0,width);
    float int1 = func1->Integral(-TMath::Pi(),TMath::Pi());
    float int2 = func2->Integral(-TMath::Pi(),TMath::Pi());
    histo->Fill(width,int1/int2);
    histo->SetBinError(histo->FindBin(width),int1/int2*0.0001);
    graph->SetPoint(npoints,width,int1/int2);
    npoints++;
    cout<<"width "<<width<<" v3 "<<int1/int2<<endl;
  }
  cout<<"npoints "<<npoints<<endl;
  //func2->SetParameter(0,1.5);
  //func2->Draw();
  //histo->Draw("L");
  graph->SetLineWidth(2);
  graph->Draw("AC");
  graph->GetYaxis()->SetTitle("v_{3}");
  graph->GetXaxis()->SetTitle("width");
  c1->SaveAs("Gaussv3.png");
}
