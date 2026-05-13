#include "GetHistoName.h"
char* GetPhiHistoName(int partID, float pt, int centBin){
  //the hard part about this is getting the pt bin
  int lowPt = ((int)(((int)((pt)*10))/5))*5;
  int highPt = lowPt+5;
  char *partName = GetSimpleParticleName(partID);
  return Form("Phi_%s_pT%i_%i_CentBin%i", partName, lowPt, highPt, centBin);
}

char* GetPhiHistoName(int partID, float ptlow, float pthigh, int centBin){
  char *partName = GetSimpleParticleName(partID);
  return Form("Phi_%s_pT%i_%i_CentBin%i", partName, (int)(10*ptlow), (int)(10*pthigh), centBin);
}
char *GetPhiHistoTitle(string dataset, int partID, float pt, int centBin){
  //the hard part about this is getting the pt bin
  int lowPt = ((int)(((int)((pt)*10))/5))*5;
  int highPt = lowPt+5;
  float fLowPt =( (float)lowPt)/10;
  float fHighPt =( (float)highPt)/10;
  char *centlabel = GetCentralityLabel(dataset.c_str(), centBin);
  char *partname = GetParticleName(partID);
  return Form("#phi distribution of %s, %s centrality, %2.1f<p_{T}<%2.1f",partname,centlabel,fLowPt,fHighPt);
}
char *GetPhiHistoTitle(string dataset, int partID, float ptlow, float pthigh, int centBin){
  //the hard part about this is getting the pt bin
  char *centlabel = GetCentralityLabel(dataset.c_str(), centBin);
  char *partname = GetParticleName(partID);
  return Form("#phi distribution of %s, %s centrality, %2.1f<p_{T}<%2.1f",partname,centlabel,ptlow,pthigh);
}
char *GetSpectraHistoName(int partID, int centBin){
  char *partName = GetSimpleParticleName(partID);
  return Form("Pt_%s_CentBin%i", partName, centBin);
}
char *GetSpectraHistoTitle(string dataset, int partID, int centBin){
  char *centlabel = GetCentralityLabel(dataset.c_str(), centBin);
  char *partname = GetParticleName(partID);
  return Form("p_{T} distribution of %s, %s centrality",partname,centlabel);
}
char *GetCorrelationHistoName(int trigID, float lowTrigPt, float highTrigPt, int assocID, float lowAssocPt, float highAssocPt, int centBin){
  char *trigName = GetSimpleParticleName(trigID);
  char *assocName = GetSimpleParticleName(assocID);
  return Form("dPhi_trig_%s_pT%i_%i_assoc_%s_pT%i_%i_CentBin%i",trigName,(int)(lowTrigPt*10),(int)(highTrigPt*10),assocName,(int)(lowAssocPt*10),(int)(highAssocPt*10),centBin);
}
char *GetCorrelationHistoTitle(string dataset,int trigID, float lowTrigPt, float highTrigPt, int assocID, float lowAssocPt, float highAssocPt, int centBin){
  char *centlabel = GetCentralityLabel(dataset.c_str(), centBin);
  char *trigName = GetParticleName(trigID);
  char *assocName = GetParticleName(assocID);
  return Form("#Delta#phi, %s trigger %2.1f<p_{T}<%2.1f, %s associated %2.1f<p_{T}<%2.1f, %s centrality",trigName,lowTrigPt,highTrigPt,assocName,lowAssocPt,highAssocPt,centlabel);
}
char *GetCorrelationHistoTitle(string dataset,int trigID, float lowTrigPt, float highTrigPt, int assocID, float lowAssocPt, int centBin){
  char *centlabel = GetCentralityLabel(dataset.c_str(), centBin);
  char *trigName = GetParticleName(trigID);
  char *assocName = GetParticleName(assocID);
  return Form("#Delta#phi, %s trigger %2.1f<p_{T}<%2.1f, %s associated %2.1f<p_{T}<trigger, %s centrality",trigName,lowTrigPt,highTrigPt,assocName,lowAssocPt,centlabel);
}
char* GetNPartHistoName(int partID, float pt, int centBin){
  //the hard part about this is getting the pt bin
  int lowPt = ((int)(((int)((pt)*10))/5))*5;
  int highPt = lowPt+5;
  char *partName = GetSimpleParticleName(partID);
  return Form("NPart_%s_pT%i_%i_CentBin%i", partName, lowPt, highPt, centBin);
}

char* GetNPartHistoName(int partID, float ptlow, float pthigh, int centBin){
  char *partName = GetSimpleParticleName(partID);
  return Form("NPart_%s_pT%i_%i_CentBin%i", partName, (int)(10*ptlow), (int)(10*pthigh), centBin);
}
char *GetNPartHistoTitle(string dataset, int partID, float pt, int centBin){
  //the hard part about this is getting the pt bin
  int lowPt = ((int)(((int)((pt)*10))/5))*5;
  int highPt = lowPt+5;
  float fLowPt =( (float)lowPt)/10;
  float fHighPt =( (float)highPt)/10;
  char *centlabel = GetCentralityLabel(dataset.c_str(), centBin);
  char *partname = GetParticleName(partID);
  return Form("Number of %s at %s centrality, %2.1f<p_{T}<%2.1f",partname,centlabel,fLowPt,fHighPt);
}
char *GetNPartHistoTitle(string dataset, int partID, float ptlow, float pthigh, int centBin){
  //the hard part about this is getting the pt bin
  char *centlabel = GetCentralityLabel(dataset.c_str(), centBin);
  char *partname = GetParticleName(partID);
  return Form("Number of %s at %s centrality, %2.1f<p_{T}<%2.1f",partname,centlabel,ptlow,pthigh);
}
char *GetMixedEventHistoName(int trigID, float lowTrigPt, float highTrigPt, int assocID, float lowAssocPt, float highAssocPt, int centBin){
  char *trigName = GetSimpleParticleName(trigID);
  char *assocName = GetSimpleParticleName(assocID);
  //cout<<"trigID "<<trigID<<" "<<lowTrigPt<<"<pT<"<<highTrigPt<<" assocID "<<assocID<<" "<<lowAssocPt<<"<pT<"<<highAssocPt<<endl;
  return Form("MixEve_trig_%s_pT%i_%i_assoc_%s_pT%i_%i_CentBin%i",trigName,(int)(lowTrigPt*10),(int)(highTrigPt*10),assocName,(int)(lowAssocPt*10),(int)(highAssocPt*10),centBin);
}
char *GetMixedEventHistoTitle(string dataset,int trigID, float lowTrigPt, float highTrigPt, int assocID, float lowAssocPt, float highAssocPt, int centBin){
  char *centlabel = GetCentralityLabel(dataset.c_str(), centBin);
  char *trigName = GetParticleName(trigID);
  char *assocName = GetParticleName(assocID);
  return Form("#Delta#phi mixed events, %s trigger %2.1f<p_{T}<%2.1f, %s associated %2.1f<p_{T}<%2.1f, %s centrality",trigName,lowTrigPt,highTrigPt,assocName,lowAssocPt,highAssocPt,centlabel);
}
char *GetMixedEventHistoTitle(string dataset,int trigID, float lowTrigPt, float highTrigPt, int assocID, float lowAssocPt, int centBin){
  char *centlabel = GetCentralityLabel(dataset.c_str(), centBin);
  char *trigName = GetParticleName(trigID);
  char *assocName = GetParticleName(assocID);
  return Form("#Delta#phi mixed events, %s trigger %2.1f<p_{T}<%2.1f, %s associated %2.1f<p_{T}<trigger, %s centrality",trigName,lowTrigPt,highTrigPt,assocName,lowAssocPt,centlabel);
}

char *GetV0GeometricCutHistoName(char *cut, int id, float pt){
  char *name = GetSimpleParticleName(id);
  string myCut = cut;   
  string DcaV0ToPV = "DcaV0ToPV";
  string DcaNegToPV = "DcaNegToPV";
  string DcaPosToPV = "DcaPosToPV";
  string DcaDaughters = "DcaDaughters";
  string NHitsNeg = "NHitsNeg";
  string NHitsPos = "NHitsPos";
  string Mass = "Mass";
  string DecayLength = "DecayLength";
  string NSigmaPos = "NSigmaPos";
  string NSigmaNeg = "NSigmaNeg";
  if(myCut != DcaV0ToPV && myCut != DcaNegToPV && myCut != DcaPosToPV && myCut != DcaDaughters && myCut != NHitsNeg && myCut != NHitsPos && myCut != Mass && myCut != DecayLength && myCut != NSigmaPos && myCut != NSigmaNeg ){return "junk";}
  if(id<1 || id>3) {
    return "junk";
  }//if this isn't
  int ptlow, pthigh;
  if(pt<1){//low pt particles;
    ptlow = ((int)(pt*10/2))*2;
    pthigh = ptlow+2;
  }
  if(pt>=1 && pt<=2){
    ptlow = 10;
    pthigh = 20;
  }
  if(pt>2){
    ptlow = 20;
    pthigh = 100;
  }
  return Form("%s%sPt%i_%i",name,cut,ptlow,pthigh);
}

char *GetV0GeometricCutHistoName(int cutNum, int id, float pt){
  if(cutNum==1) return GetV0GeometricCutHistoName("DcaV0ToPV",id,pt);
  if(cutNum==2) return GetV0GeometricCutHistoName("DcaNegToPV",id,pt);
  if(cutNum==3) return GetV0GeometricCutHistoName("DcaPosToPV",id,pt);
  if(cutNum==4) return GetV0GeometricCutHistoName("DcaDaughters",id,pt);
  if(cutNum==5) return GetV0GeometricCutHistoName("NHitsNeg",id,pt);
  if(cutNum==6) return GetV0GeometricCutHistoName("NHitsPos",id,pt);
  if(cutNum==7) return GetV0GeometricCutHistoName("NSigmaNeg",id,pt);
  if(cutNum==8) return GetV0GeometricCutHistoName("DecayLength",id,pt);
  if(cutNum==9) return GetV0GeometricCutHistoName("NSigmaPos",id,pt);
  if(cutNum==10) return GetV0GeometricCutHistoName("Mass",id,pt);
  return "junk";
}

char *GetV0GeometricCutHistoTitle(char *cut, int id, float pt){
  char *name = GetSimpleParticleName(id);
  string myCut = cut;   
  string DcaV0ToPV = "DcaV0ToPV";
  string DcaNegToPV = "DcaNegToPV";
  string DcaPosToPV = "DcaPosToPV";
  string DcaDaughters = "DcaDaughters";
  string NHitsNeg = "NHitsNeg";
  string NHitsPos = "NHitsPos";
  string Mass = "Mass";
  string DecayLength = "DecayLength";
  string NSigmaPos = "NSigmaPos";
  string NSigmaNeg = "NSigmaNeg";
  if(myCut != DcaV0ToPV && myCut != DcaNegToPV && myCut != DcaPosToPV && myCut != DcaDaughters && myCut != NHitsNeg && myCut != NHitsPos && myCut != Mass && myCut != DecayLength && myCut != NSigmaPos && myCut != NSigmaNeg ){return "junk";}
  if(id<1 || id>3) {
    return "junk";//if this isn't
  }
  int ptlow, pthigh;
  if(pt<1){//low pt particles;
    ptlow = ((int)(pt*10/2))*2;
    pthigh = ptlow+2;
  }
  if(pt>=1 && pt<=2){
    ptlow = 10;
    pthigh = 20;
  }
  if(pt>2){
    ptlow = 20;
    pthigh = 10;
  }
  if(myCut==DcaV0ToPV) return Form("%s DCA of V^{0} to primary vertex, %2.1f < p_{T} < %2.1f",name,((float)ptlow)/10,((float)pthigh)/10);
  if(myCut==DcaNegToPV) return Form("%s DCA of negative daughter to primary vertex, %2.1f < p_{T} < %2.1f",name,((float)ptlow)/10,((float)pthigh)/10);
  if(myCut==DcaPosToPV) return Form("%s DCA of positive daughter to primary vertex, %2.1f < p_{T} < %2.1f",name,((float)ptlow)/10,((float)pthigh)/10);
  if(myCut==DcaDaughters) return Form("%s DCA of daughters, %2.1f < p_{T} < %2.1f",name,((float)ptlow)/10,((float)pthigh)/10);
  if(myCut==NHitsNeg) return Form("%s Number of hits on negative daughter, %2.1f < p_{T} < %2.1f",name,((float)ptlow)/10,((float)pthigh)/10);
  if(myCut==NHitsPos) return Form("%s Number of hits on positive daughter, %2.1f < p_{T} < %2.1f",name,((float)ptlow)/10,((float)pthigh)/10);
  if(myCut==Mass) return Form("%s Mass, %2.1f < p_{T} < %2.1f",name,((float)ptlow)/10,((float)pthigh)/10);
  if(myCut==DecayLength) return Form("%s Decay length, %2.1f < p_{T} < %2.1f",name,((float)ptlow)/10,((float)pthigh)/10);
  if(myCut==NSigmaPos) return Form("%s #sigma_{dE/dx} of positive daughter, %2.1f < p_{T} < %2.1f",name,((float)ptlow)/10,((float)pthigh)/10);
  if(myCut==NSigmaNeg) return Form("%s #sigma_{dE/dx} of negative daughter, %2.1f < p_{T} < %2.1f",name,((float)ptlow)/10,((float)pthigh)/10);
  return "junk";
}

char *GetV0GeometricCutHistoTitle(int cutNum, int id, float pt){
  if(cutNum==1) return GetV0GeometricCutHistoTitle("DcaV0ToPV",id,pt);
  if(cutNum==2) return GetV0GeometricCutHistoTitle("DcaNegToPV",id,pt);
  if(cutNum==3) return GetV0GeometricCutHistoTitle("DcaPosToPV",id,pt);
  if(cutNum==4) return GetV0GeometricCutHistoTitle("DcaDaughters",id,pt);
  if(cutNum==5) return GetV0GeometricCutHistoTitle("NHitsNeg",id,pt);
  if(cutNum==6) return GetV0GeometricCutHistoTitle("NHitsPos",id,pt);
  if(cutNum==7) return GetV0GeometricCutHistoTitle("NSigmaNeg",id,pt);
  if(cutNum==8) return GetV0GeometricCutHistoTitle("DecayLength",id,pt);
  if(cutNum==9) return GetV0GeometricCutHistoTitle("NSigmaPos",id,pt);
  if(cutNum==10) return GetV0GeometricCutHistoTitle("Mass",id,pt);
  return "junk";
}
char *GetV0GeometricCutHistoYTitle(int cutNum){
  if(cutNum==1) return "DCA of V^{0} to primary vertex";
  if(cutNum==2) return "DCA of negative daughter to primary vertex";
  if(cutNum==3) return "DCA of positive daughter to primary vertex";
  if(cutNum==4) return "DCA of daughters";
  if(cutNum==5) return "Number of hits on negative daughter";
  if(cutNum==6) return "Number of hits on positive daughter";
  if(cutNum==7) return "#sigma_{dEdx} of negative daughter";
  if(cutNum==8) return "Decay length of V^{0}";
  if(cutNum==9) return "#sigma_{dEdx} of positive daughter";
  if(cutNum==10) return "Number of entries";
  return "junk";
}


char *GetXiGeometricCutHistoName(char *cut, int id, float pt){
  char *name = GetSimpleParticleName(id);
  string myCut = cut;   
  string DcaV0ToPV = "DcaV0ToPV";
  string DcaXiToPV = "DcaXiToPV";
  string DcaNegToPV = "DcaNegToPV";
  string DcaPosToPV = "DcaPosToPV";
  string DcaBachToPV = "DcaBachToPV";
  string DcaV0Daughters = "DcaV0Daughters";
  string DcaXiDaughters = "DcaXiDaughters";
  string NHitsNeg = "NHitsNeg";
  string NHitsPos = "NHitsPos";
  string NHitsBach = "NHitsBach";
  string V0Mass = "V0Mass";
  string XiMass = "XiMass";
  string V0DecayLength = "V0DecayLength";
  string XiDecayLength = "XiDecayLength";
  string NSigmaPos = "NSigmaPos";
  string NSigmaNeg = "NSigmaNeg";
  string NSigmaBach = "NSigmaBach";
  if(myCut != DcaXiToPV && myCut != DcaV0ToPV && myCut != DcaNegToPV && myCut != DcaPosToPV&& myCut != DcaBachToPV && myCut != DcaV0Daughters&& myCut != DcaXiDaughters && myCut != NHitsNeg && myCut != NHitsPos && myCut != NHitsBach && myCut != V0Mass && myCut != XiMass && myCut != V0DecayLength && myCut != XiDecayLength && myCut != NSigmaPos && myCut != NSigmaNeg && myCut != NSigmaBach ){return "junk";}
  if(id!=4 && id!=5 && id!=18 && id!=19) {
    return "junk";
  }//if this isn't
  int ptlow, pthigh;
  if(pt<1){//low pt particles;
    ptlow = ((int)(pt*10/2))*2;
    pthigh = ptlow+2;
  }
  if(pt>=1 && pt<=2){
    ptlow = 10;
    pthigh = 20;
  }
  if(pt>2){
    ptlow = 20;
    pthigh = 100;
  }
  return Form("%s%sPt%i_%i",name,cut,ptlow,pthigh);
}

char *GetXiGeometricCutHistoName(int cutNum, int id, float pt){
  if(cutNum==1) return GetXiGeometricCutHistoName("DcaXiToPV",id,pt);
  if(cutNum==2) return GetXiGeometricCutHistoName("DcaV0ToPV",id,pt);
  if(cutNum==3) return GetXiGeometricCutHistoName("DcaNegToPV",id,pt);
  if(cutNum==4) return GetXiGeometricCutHistoName("DcaPosToPV",id,pt);
  if(cutNum==5) return GetXiGeometricCutHistoName("DcaBachToPV",id,pt);
  if(cutNum==6) return GetXiGeometricCutHistoName("DcaXiDaughters",id,pt);
  if(cutNum==7) return GetXiGeometricCutHistoName("DcaV0Daughters",id,pt);
  if(cutNum==8) return GetXiGeometricCutHistoName("NHitsNeg",id,pt);
  if(cutNum==9) return GetXiGeometricCutHistoName("NHitsPos",id,pt);
  if(cutNum==10) return GetXiGeometricCutHistoName("NHitsBach",id,pt);
  if(cutNum==11) return GetXiGeometricCutHistoName("NSigmaNeg",id,pt);
  if(cutNum==12) return GetXiGeometricCutHistoName("NSigmaPos",id,pt);
  if(cutNum==13) return GetXiGeometricCutHistoName("NSigmaBach",id,pt);
  if(cutNum==14) return GetXiGeometricCutHistoName("V0DecayLength",id,pt);
  if(cutNum==15) return GetXiGeometricCutHistoName("XiDecayLength",id,pt);
  if(cutNum==16) return GetXiGeometricCutHistoName("V0Mass",id,pt);
  if(cutNum==17) return GetXiGeometricCutHistoName("XiMass",id,pt);
  return "junk";
}

char *GetXiGeometricCutHistoTitle(char *cut, int id, float pt){
  char *name = GetSimpleParticleName(id);
  string myCut = cut;   
  string DcaV0ToPV = "DcaV0ToPV";
  string DcaXiToPV = "DcaXiToPV";
  string DcaNegToPV = "DcaNegToPV";
  string DcaPosToPV = "DcaPosToPV";
  string DcaBachToPV = "DcaBachToPV";
  string DcaV0Daughters = "DcaV0Daughters";
  string DcaXiDaughters = "DcaXiDaughters";
  string NHitsNeg = "NHitsNeg";
  string NHitsPos = "NHitsPos";
  string NHitsBach = "NHitsBach";
  string V0Mass = "V0Mass";
  string XiMass = "XiMass";
  string V0DecayLength = "V0DecayLength";
  string XiDecayLength = "XiDecayLength";
  string NSigmaPos = "NSigmaPos";
  string NSigmaNeg = "NSigmaNeg";
  string NSigmaBach = "NSigmaBach";
  if(myCut != DcaXiToPV && myCut != DcaV0ToPV && myCut != DcaNegToPV && myCut != DcaPosToPV&& myCut != DcaBachToPV && myCut != DcaV0Daughters&& myCut != DcaXiDaughters && myCut != NHitsNeg && myCut != NHitsPos && myCut != NHitsBach && myCut != XiMass && myCut != V0Mass && myCut != V0DecayLength && myCut != XiDecayLength && myCut != NSigmaPos && myCut != NSigmaNeg && myCut != NSigmaBach ){return "junk";}
  if(id!=4 && id!=5 && id!=18 && id!=19) {
    return "junk";//if this isn't
  }
  int ptlow, pthigh;
  if(pt<1){//low pt particles;
    ptlow = ((int)(pt*10/2))*2;
    pthigh = ptlow+2;
  }
  if(pt>=1 && pt<=2){
    ptlow = 10;
    pthigh = 20;
  }
  if(pt>2){
    ptlow = 20;
    pthigh = 100;
  }
  if(myCut==DcaXiToPV) return Form("%s DCA of #Xi to primary vertex, %2.1f < p_{T} < %2.1f",name,((float)ptlow)/10,((float)pthigh)/10);
  if(myCut==DcaV0ToPV) return Form("%s DCA of V^{0} to primary vertex, %2.1f < p_{T} < %2.1f",name,((float)ptlow)/10,((float)pthigh)/10);
  if(myCut==DcaNegToPV) return Form("%s DCA of negative daughter to primary vertex, %2.1f < p_{T} < %2.1f",name,((float)ptlow)/10,((float)pthigh)/10);
  if(myCut==DcaPosToPV) return Form("%s DCA of positive daughter to primary vertex, %2.1f < p_{T} < %2.1f",name,((float)ptlow)/10,((float)pthigh)/10);
  if(myCut==DcaBachToPV) return Form("%s DCA of bachelor to primary vertex, %2.1f < p_{T} < %2.1f",name,((float)ptlow)/10,((float)pthigh)/10);
  if(myCut==DcaV0Daughters) return Form("%s DCA of V^{0} daughters, %2.1f < p_{T} < %2.1f",name,((float)ptlow)/10,((float)pthigh)/10);
  if(myCut==DcaXiDaughters) return Form("%s DCA of #Xi daughters, %2.1f < p_{T} < %2.1f",name,((float)ptlow)/10,((float)pthigh)/10);
  if(myCut==NHitsNeg) return Form("%s Number of hits on negative daughter, %2.1f < p_{T} < %2.1f",name,((float)ptlow)/10,((float)pthigh)/10);
  if(myCut==NHitsPos) return Form("%s Number of hits on positive daughter, %2.1f < p_{T} < %2.1f",name,((float)ptlow)/10,((float)pthigh)/10);
  if(myCut==NHitsBach) return Form("%s Number of hits on bachelor, %2.1f < p_{T} < %2.1f",name,((float)ptlow)/10,((float)pthigh)/10);
  if(myCut==XiMass) return Form("%s Xi Mass, %2.1f < p_{T} < %2.1f",name,((float)ptlow)/10,((float)pthigh)/10);
  if(myCut==V0Mass) return Form("%s V^{0} Mass, %2.1f < p_{T} < %2.1f",name,((float)ptlow)/10,((float)pthigh)/10);
  if(myCut==V0DecayLength) return Form("%s Decay length of V^{0}, %2.1f < p_{T} < %2.1f",name,((float)ptlow)/10,((float)pthigh)/10);
  if(myCut==XiDecayLength) return Form("%s Decay length of #Xi, %2.1f < p_{T} < %2.1f",name,((float)ptlow)/10,((float)pthigh)/10);
  if(myCut==NSigmaPos) return Form("%s #sigma_{dE/dx} of positive daughter, %2.1f < p_{T} < %2.1f",name,((float)ptlow)/10,((float)pthigh)/10);
  if(myCut==NSigmaNeg) return Form("%s #sigma_{dE/dx} of negative daughter, %2.1f < p_{T} < %2.1f",name,((float)ptlow)/10,((float)pthigh)/10);
  if(myCut==NSigmaBach) return Form("%s #sigma_{dE/dx} of bachelor, %2.1f < p_{T} < %2.1f",name,((float)ptlow)/10,((float)pthigh)/10);
  return "junk";
}

char *GetXiGeometricCutHistoTitle(int cutNum, int id, float pt){
  if(cutNum==1) return GetXiGeometricCutHistoTitle("DcaXiToPV",id,pt);
  if(cutNum==2) return GetXiGeometricCutHistoTitle("DcaV0ToPV",id,pt);
  if(cutNum==3) return GetXiGeometricCutHistoTitle("DcaNegToPV",id,pt);
  if(cutNum==4) return GetXiGeometricCutHistoTitle("DcaPosToPV",id,pt);
  if(cutNum==5) return GetXiGeometricCutHistoTitle("DcaBachToPV",id,pt);
  if(cutNum==6) return GetXiGeometricCutHistoTitle("DcaXiDaughters",id,pt);
  if(cutNum==7) return GetXiGeometricCutHistoTitle("DcaV0Daughters",id,pt);
  if(cutNum==8) return GetXiGeometricCutHistoTitle("NHitsNeg",id,pt);
  if(cutNum==9) return GetXiGeometricCutHistoTitle("NHitsPos",id,pt);
  if(cutNum==10) return GetXiGeometricCutHistoTitle("NHitsBach",id,pt);
  if(cutNum==11) return GetXiGeometricCutHistoTitle("NSigmaNeg",id,pt);
  if(cutNum==12) return GetXiGeometricCutHistoTitle("NSigmaPos",id,pt);
  if(cutNum==13) return GetXiGeometricCutHistoTitle("NSigmaBach",id,pt);
  if(cutNum==14) return GetXiGeometricCutHistoTitle("V0DecayLength",id,pt);
  if(cutNum==15) return GetXiGeometricCutHistoTitle("XiDecayLength",id,pt);
  if(cutNum==16) return GetXiGeometricCutHistoTitle("V0Mass",id,pt);
  if(cutNum==17) return GetXiGeometricCutHistoTitle("XiMass",id,pt);
  return "junk";
}
char *GetXiGeometricCutHistoYTitle(int cutNum){
  if(cutNum==1) return "DCA of #Xi to primary vertex";
  if(cutNum==2) return "DCA of V^{0} to primary vertex";
  if(cutNum==3) return "DCA of negative daughter to primary vertex";
  if(cutNum==4) return "DCA of positive daughter to primary vertex";
  if(cutNum==5) return "DCA of bachelor to primary vertex";
  if(cutNum==6) return "DCA of #Xi daughters";
  if(cutNum==7) return "DCA of V^{0} daughters";
  if(cutNum==8) return "Number of hits on negative daughter";
  if(cutNum==9) return "Number of hits on positive daughter";
  if(cutNum==10) return "Number of hits on bachelor";
  if(cutNum==11) return "#sigma_{dEdx} of negative daughter";
  if(cutNum==12) return "#sigma_{dEdx} of positive daughter";
  if(cutNum==13) return "#sigma_{dEdx} of bachelor";
  if(cutNum==14) return "Decay length of V^{0}";
  if(cutNum==15) return "Decay length of #Xi";
  if(cutNum==16) return "Number of entries";
  if(cutNum==17) return "Number of entries";
  return "junk";
}
