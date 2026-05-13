void SetRootStyles(){
  //These things belong in almost every root macro where you draw stuff...
  //gotta love Root.  Defaults that don't work for anyone.  No one but a couple hundred people
  //who are over worked and under paid and hardly ever talk to each other could have come up with
  //this stuff.
  gStyle->SetPadGridX(kFALSE);
  gStyle->SetPadGridY(kFALSE);
  gStyle->SetPadGridX(0);
  gStyle->SetPadGridY(0);
  //gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);
  gStyle->SetTitleSize(0.07,"xyz");
  gStyle->SetTitleOffset(0.7,"x");
  gStyle->SetTitleOffset(1.2,"y");
  gStyle->SetLabelSize(0.05,"xyz");
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadRightMargin(0.01);
  gStyle->SetPadBottomMargin(0.16);
  gStyle->SetPadLeftMargin(0.2);
  gStyle->SetOptDate(0);
  gStyle->SetPaperSize(20,24);//(20,24) is letter and (20,26) is A4.  Damn the world and its A4 paper!
  gStyle->SetPalette(1);
  gROOT->ForceStyle();

}
