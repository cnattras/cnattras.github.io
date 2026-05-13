#include "IsGoodV0Track.h"

bool IsGoodV0Track(const char *dataset, TV0Track *track, int type, const char *cuts, float ptmin, float ptmax, float eta){
  //cout<<endl<<"|1|";
  if(!track) {return false;}
  //cout<<"z";
  if(track->GetType()!=type){return false;}
  //cout<<"a";
  if((int) track->GetNHitsPosDaughter() <= (int) GetDefaultV0Cut(dataset, cuts, "NHitsPos", type) ){return false;}
  //cout<<"b";
  if((int) track->GetNHitsNegDaughter() <= (int) GetDefaultV0Cut(dataset, cuts, "NHitsNeg", type)) {return false;}
  //cout<<"c";
  if(fabs(track->GetDcaV0ToPV()) > GetDefaultV0Cut(dataset, cuts, "DcaV0ToPV", type) ) {return false;}
  //cout<<"d";
  //cout<<" dca daughters "<< fabs(track->GetDcaDaughters()) <<" cut "<< GetDefaultV0Cut(dataset, cuts, "DcaDaughters", type) <<" pt "<< track->GetPt();
  if(fabs(track->GetDcaDaughters()) > GetDefaultV0Cut(dataset, cuts, "DcaDaughters", type) ) {return false;}
  //cout<<"e";
  if(fabs(track->GetDcaPosDaughterToPV()) < GetDefaultV0Cut(dataset, cuts, "DcaPosToPV", type) || fabs(track->GetDcaNegDaughterToPV()) < GetDefaultV0Cut(dataset, cuts, "DcaNegToPV", type) ) {return false;} 
  //cout<<"f";
  if(fabs(track->GetDecayLength()) < GetDefaultV0Cut(dataset, cuts, "DecayLength", type) ) {return false;}
  //cout<<"g";

  double pt = track->GetPt();
  if(pt<ptmin || pt>ptmax) {return false;}
  //cout<<"h";

  //To be added later, must comment out now so I can debug correlations on TTrees made with Nsigma entered wrong
//   float nSigmaCut = 3.0;
//   if(fabs(track->GetdEdxPosDaughter())>nSigmaCut){return false;}
//   if(fabs(track->GetdEdxNegDaughter())>nSigmaCut){return false;}

  if(fabs(track->GetEta())> eta) {return false;}
  //cout<<"i";

  ////cout<<" mass "<<GetV0Mass(track,type);
  //last check - is mass reasonable?
  if(type ==3){
    if( GetV0Mass(track,type) < .44 || GetV0Mass(track,type) > .56 ){return false;}
  }
  if(type ==1 || type ==2){
    if( GetV0Mass(track,type) < 1.08 || GetV0Mass(track,type) > 1.15 ){return false;}
  }
  //cout<<"j";
  return true;
}

bool IsGoodV0Track(const char *dataset, StV0MuDst *track, int type, const char *cuts, float ptmin, float ptmax, float eta){
  //cout<<endl<<"|2|";
  if(!track) {return false;}
  if(track->topologyMapPos().numberOfHits(kTpcId) <= (int) GetDefaultV0Cut(dataset, cuts, "NHitsPos", type) ){return false;}
  if(track->topologyMapNeg().numberOfHits(kTpcId) <= (int) GetDefaultV0Cut(dataset, cuts, "NHitsNeg", type)) {return false;}
  if(fabs(track->dcaV0ToPrimVertex()) > GetDefaultV0Cut(dataset, cuts, "DcaV0ToPV", type) ) {return false;}
  if(fabs(track->dcaV0Daughters()) > GetDefaultV0Cut(dataset, cuts, "DcaDaughters", type) ) {return false;}
  if(fabs(track->dcaPosToPrimVertex()) < GetDefaultV0Cut(dataset, cuts, "DcaPosToPV", type) ||fabs( track->dcaNegToPrimVertex()) < GetDefaultV0Cut(dataset, cuts, "DcaNegToPV", type) ) {return false;} 
  if(fabs(track->decayLengthV0()) < GetDefaultV0Cut(dataset, cuts, "DecayLength", type) ) {return false;}

  double pt = sqrt(track->momV0X()*track->momV0X()+track->momV0Y()*track->momV0Y());
  if(pt<ptmin || pt>ptmax) {return false;}


  if(fabs(track->pseudoRapV0())> eta) {return false;}

  //cout<<" mass "<<GetV0Mass(track,type);
  //last check - is mass reasonable?
  if(type ==3){
    if( GetV0Mass(track,type) < .44 || GetV0Mass(track,type) > .56 ){return false;}
  }
  if(type ==1 || type ==2){
    if( GetV0Mass(track,type) < 1.08 || GetV0Mass(track,type) > 1.15 ){return false;}
  }
  return true;
}



bool IsGoodV0Track(const string dataset, StV0MuDst *track, int type, const string cuts, float ptmin, float ptmax, float eta){
  //cout<<"|3|";
  if(!track) {return false;}
  return IsGoodV0Track((char*) dataset.c_str(), track,type, (char*) cuts.c_str(), ptmin, ptmax, eta);
}
bool IsGoodV0Track(const char *dataset, StV0MuDst *track, int type, const string cuts, float ptmin, float ptmax, float eta){
  //cout<<"|4|";
  if(!track) {return false;}
  return IsGoodV0Track(dataset, track,type, (char*) cuts.c_str(), ptmin, ptmax, eta);
}
bool IsGoodV0Track(const string dataset, TV0Track *track, int type, const string cuts, float ptmin, float ptmax, float eta){
  //cout<<"|5|";
  if(!track) {return false;}
  return IsGoodV0Track((char*) dataset.c_str(),track,type,  (char*) cuts.c_str(), ptmin, ptmax, eta);
}
bool IsGoodV0Track(const char *dataset, TV0Track *track, int type, const string cuts, float ptmin, float ptmax, float eta){
  //cout<<"|6|";
  if(!track) {return false;}
  return IsGoodV0Track(dataset, track,type, (char*)  cuts.c_str(), ptmin, ptmax, eta);
}
bool IsGoodV0Track(const string dataset, StV0MuDst *track, int type, const char *cuts, float ptmin, float ptmax, float eta){
  //cout<<"|7|";
  if(!track) {return false;}
  ////cout<<" leaving |7| ";
  return IsGoodV0Track((char*) dataset.c_str(), track, type, cuts, ptmin, ptmax, eta);
}
bool IsGoodV0Track(const string dataset, TV0Track *track, int type, const char *cuts, float ptmin, float ptmax, float eta){
  //cout<<"|8|";
  if(!track) {return false;}
  return IsGoodV0Track((char*) dataset.c_str(), track, type, cuts, ptmin, ptmax, eta);
}



bool IsGoodV0Track(const char *dataset, StV0MuDst *track,int type, float decaylength, float dcaV0, float dcaDaughter, float dcaNeg, float dcaPos, int nHitsNeg, int nHitsPos, float ptmin, float ptmax, float eta){//defaults to loosest cuts in production and accepting all tracks
  //cout<<"|9|";
  if(!track) {return false;}
  if(track->topologyMapPos().numberOfHits(kTpcId) <= nHitsPos){return false;}
  if(track->topologyMapNeg().numberOfHits(kTpcId) <= nHitsNeg) {return false;}
  if(fabs(track->decayLengthV0()) < decaylength) {return false;}
  if(fabs(track->dcaPosToPrimVertex()) < dcaPos || track->dcaNegToPrimVertex() < dcaNeg) {return false;} 
  if(fabs(track->dcaV0Daughters()) > dcaDaughter) {return false;}
  if(fabs(track->dcaV0ToPrimVertex()) > dcaV0) {return false;}

  double pt = sqrt(track->momV0X()*track->momV0X()+track->momV0Y()*track->momV0Y());
  if(pt<ptmin || pt>ptmax) {return false;}


  if(fabs(track->pseudoRapV0())> eta) {return false;}


  //last check - is mass reasonable?
  if(type ==3){
    if( GetV0Mass(track,type) < .44 || GetV0Mass(track,type) > .56 ){return false;}
  }
  if(type ==1 || type ==2){
    if( GetV0Mass(track,type) < 1.08 || GetV0Mass(track,type) > 1.15 ){return false;}
  }

  ////cout<<type;
  return true;
}

bool IsGoodV0Track(const char *dataset, TV0Track *track, int type, float decaylength, float dcaV0, float dcaDaughter, float dcaNeg , float dcaPos , int nHitsNeg, int nHitsPos , float ptmin, float ptmax, float eta){  
  //cout<<"|10|";
  if(!track) {return false;}
  if(track->GetNHitsPosDaughter() <= nHitsPos){return false;}
  if(track->GetNHitsNegDaughter() <= nHitsNeg) {return false;}
  if(fabs(track->GetDecayLength()) < decaylength) {return false;}
  if(fabs(track->GetDcaPosDaughterToPV()) < dcaPos || fabs(track->GetDcaNegDaughterToPV()) < dcaNeg) {return false;} 
  if(fabs(track->GetDcaDaughters()) > dcaDaughter) {return false;}
  if(fabs(track->GetDcaV0ToPV()) > dcaV0) {return false;}

  double pt = track->GetPt();
  if(pt<ptmin || pt>ptmax) {return false;}


  if(fabs(track->GetEta())> eta) {return false;}

  //last check - is mass reasonable?
  if(type ==3){
    if( GetV0Mass(track,type) < .44 || GetV0Mass(track,type) > .56 ){return false;}
  }
  if(type ==1 || type ==2){
    if( GetV0Mass(track,type) < 1.08 || GetV0Mass(track,type) > 1.15 ){return false;}
  }
  return true;
}

bool IsGoodV0Track(const string dataset, StV0MuDst *track,int type, float decaylength, float dcaV0, float dcaDaughter, float dcaNeg , float dcaPos , int nHitsNeg, int nHitsPos, float ptmin, float ptmax, float eta){
  //cout<<"|11|";
  return IsGoodV0Track( (char*) dataset.c_str() ,track,type,decaylength,dcaV0,dcaDaughter,dcaNeg,dcaPos,nHitsNeg,nHitsPos,ptmin,ptmax,eta);
}


bool IsGoodV0Track(const string dataset, TV0Track *track, int type, float decaylength, float dcaV0, float dcaDaughter, float dcaNeg , float dcaPos , int nHitsNeg, int nHitsPos, float ptmin, float ptmax, float eta){
  //cout<<"|12|";
  if(!track) {return false;}
  return IsGoodV0Track((char*) dataset.c_str(), track, type, decaylength, dcaV0, dcaDaughter, dcaNeg, dcaPos, nHitsNeg, nHitsPos, ptmin, ptmax, eta);
}



bool IsGoodV0Track(const string dataset, StV0MuDst *track, const string cuts, float ptmin, float ptmax, float eta){
  //cout<<"|13|";
  if(!track) {return false;}
  return IsGoodV0Track(dataset, track, (char*) cuts.c_str(), ptmin, ptmax, eta);
}
bool IsGoodV0Track(const char *dataset, StV0MuDst *track, const string cuts, float ptmin, float ptmax, float eta){
  //cout<<"|14|";
  if(!track) {return false;}
  return IsGoodV0Track(dataset, track, (char*) cuts.c_str(), ptmin, ptmax, eta);
}
bool IsGoodV0Track(const string dataset, TV0Track *track, const string cuts, float ptmin, float ptmax, float eta){
  //cout<<"|15|";
  if(!track) {return false;}
  return IsGoodV0Track(dataset, track, (char*) cuts.c_str(), ptmin, ptmax, eta);
}
bool IsGoodV0Track(const char *dataset, TV0Track *track, const string cuts, float ptmin, float ptmax, float eta){
  //cout<<"|16|";
  if(!track) {return false;}
  return IsGoodV0Track(dataset, track, (char*) cuts.c_str(), ptmin, ptmax, eta);
}


bool IsGoodV0Track(const string dataset, StV0MuDst *track, const char *cuts, float ptmin, float ptmax, float eta){//checks all three types
  //cout<<"|17|";
  if(!track) {return false;}
  ////cout<<" lambda? ";
  if(IsGoodV0Track(dataset, track, 1, cuts, ptmin, ptmax, eta)) {return true;}
  ////cout<<" antilambda? ";
  if(IsGoodV0Track(dataset, track, 2, cuts, ptmin, ptmax, eta)) {return true;}
  ////cout<<" k0s ";
  if(IsGoodV0Track(dataset, track, 3, cuts, ptmin, ptmax, eta)) {return true;}
//   for(int i=1;i<=3;i++){
//     if(IsGoodV0Track(dataset, track, i, cuts, ptmin, ptmax, eta)) return true;
//   }
  ////cout<<" leaving |17| ";
  return false;
}
bool IsGoodV0Track(const char *dataset, StV0MuDst *track, const char *cuts, float ptmin, float ptmax, float eta){//checks all three types
  //cout<<"|18|";
  if(!track) {return false;}
  for(int i=1;i<=3;i++){
    if(IsGoodV0Track(dataset, track, i, cuts, ptmin, ptmax, eta)) return true;
  }
  return false;
}
bool IsGoodV0Track(const string dataset, TV0Track *track, const char *cuts, float ptmin, float ptmax, float eta){
  //cout<<"|19|";
  if(!track) {return false;}
  //checks all three types
  for(int i=1;i<=3;i++){
    if(IsGoodV0Track(dataset, track, i, cuts, ptmin, ptmax, eta)) return true;
  }
  return false;
}
bool IsGoodV0Track(const char *dataset, TV0Track *track, const char *cuts, float ptmin, float ptmax, float eta){
  //cout<<"|20|";
  if(!track) {return false;}
  //checks all three types
  for(int i=1;i<=3;i++){
    if(IsGoodV0Track(dataset, track, i, cuts, ptmin, ptmax, eta)) return true;
  }
  return false;
}


bool IsGoodV0Track(const string dataset, StV0MuDst *track, float decaylength, float dcaV0, float dcaDaughter, float dcaNeg , float dcaPos , int nHitsNeg, int nHitsPos, float ptmin, float ptmax, float eta){//checks all three types
  //cout<<"|21|";
  if(!track) {return false;}

  for(int i=1;i<=3;i++){
    if( IsGoodV0Track(dataset, track, i, decaylength, dcaV0, dcaDaughter, dcaNeg, dcaPos, nHitsNeg, nHitsPos,ptmin, ptmax, eta) ){ return true; }
  }
  return false;
}
bool IsGoodV0Track(const char *dataset, StV0MuDst *track, float decaylength, float dcaV0, float dcaDaughter, float dcaNeg , float dcaPos , int nHitsNeg, int nHitsPos, float ptmin, float ptmax, float eta){//checks all three types
  //cout<<"|22|";
  if(!track) {return false;}
  for(int i=1;i<=3;i++){
    if(IsGoodV0Track(dataset, track, i, decaylength, dcaV0, dcaDaughter, dcaNeg, dcaPos, nHitsNeg, nHitsPos,ptmin, ptmax, eta)) return true;
  }
  return false;
}
bool IsGoodV0Track(const string dataset, TV0Track *track, float decaylength, float dcaV0, float dcaDaughter, float dcaNeg , float dcaPos , int nHitsNeg, int nHitsPos, float ptmin, float ptmax, float eta){//checks all three types
  //cout<<"|23|";
  if(!track) {return false;}
  for(int i=1;i<=3;i++){
    if(IsGoodV0Track(dataset, track, i, decaylength, dcaV0, dcaDaughter, dcaNeg, dcaPos, nHitsNeg, nHitsPos,ptmin, ptmax, eta)) return true;
  }
  return false;
}
bool IsGoodV0Track(const char *dataset, TV0Track *track, float decaylength, float dcaV0, float dcaDaughter, float dcaNeg , float dcaPos , int nHitsNeg, int nHitsPos, float ptmin, float ptmax, float eta){//checks all three types
  //cout<<"|24|";
  if(!track) {return false;}
  for(int i=1;i<=3;i++){
    if(IsGoodV0Track(dataset, track, i, decaylength, dcaV0, dcaDaughter, dcaNeg, dcaPos, nHitsNeg, nHitsPos,ptmin, ptmax, eta)) return true;
  }
  return false;
}

//=====================================   Xi functions   ========================================

bool IsGoodXiTrack(const char *dataset, TXiTrack *track, int type, const char *cuts, float ptmin, float ptmax, float eta){
  //cout<<endl<<"|1|";
  if(!track) {return false;}

  if(track->GetNHitsPosDaughter() <= (int) GetDefaultXiCut(dataset, cuts, "NHitsPos", type) ){return false;}
  if(track->GetNHitsNegDaughter() <= (int) GetDefaultXiCut(dataset, cuts, "NHitsNeg", type)) {return false;}
  if(track->GetNHitsNegDaughter() <= (int) GetDefaultXiCut(dataset, cuts, "NHitsBach", type)) {return false;}
  if(fabs(track->GetDcaV0ToPV()) > GetDefaultXiCut(dataset, cuts, "DcaV0ToPV", type) ) {return false;}
  if(fabs(track->GetDcaXiToPV()) > GetDefaultXiCut(dataset, cuts, "DcaXiToPV", type) ) {return false;}
  if(fabs(track->GetDcaV0Daughters()) > GetDefaultXiCut(dataset, cuts, "DcaV0Daughters", type) ) {return false;}
  if(fabs(track->GetDcaXiDaughters()) > GetDefaultXiCut(dataset, cuts, "DcaXiDaughters", type) ) {return false;}
  if(fabs(track->GetDcaPosDaughterToPV()) < GetDefaultXiCut(dataset, cuts, "DcaPosToPV", type) || fabs(track->GetDcaNegDaughterToPV()) < GetDefaultXiCut(dataset, cuts, "DcaNegToPV", type)|| fabs(track->GetDcaBachDaughterToPV()) < GetDefaultXiCut(dataset, cuts, "DcaBachToPV", type) ) {return false;} 
  if(fabs(track->GetDecayLengthV0()) < GetDefaultXiCut(dataset, cuts, "DecayLengthV0", type) ) {return false;}
  if(fabs(track->GetDecayLengthXi()) < GetDefaultXiCut(dataset, cuts, "DecayLengthXi", type) ) {return false;}

  double pt = track->GetPt();
  if(pt<ptmin || pt>ptmax) {return false;}


  if(fabs(track->GetEta())> eta) {return false;}

  if(track->GetMassV0() < 1.0 || track->GetMassV0() > 1.2 ){return false;}

  //Sanity check on the mass of Xis and Omegas too
  if(type==4 || type == 18){//Xi and anti-Xi, true mass 1.321 GeV
    if(track->GetMass() > 1.5 || track->GetMass()<1.1 ) {return false;}
  }
  if(type==5 || type == 19){//Omega and anti-Omega, true mass 1.672 GeV
    if(track->GetMass() > 1.9 || track->GetMass()<1.5 ) {return false;}
  }

  return true;
}

bool IsGoodXiTrack(const char *dataset, StXiMuDst *track, int type, const char *cuts, float ptmin, float ptmax, float eta){
  //cout<<endl<<"|2|";
  if(!track) {return false;}
  if(track->topologyMapPos().numberOfHits(kTpcId) <= (int) GetDefaultXiCut(dataset, cuts, "NHitsPos", type) ){return false;}
  if(track->topologyMapNeg().numberOfHits(kTpcId) <= (int) GetDefaultXiCut(dataset, cuts, "NHitsNeg", type)) {return false;}
  if(track->topologyMapBachelor().numberOfHits(kTpcId) <= (int) GetDefaultXiCut(dataset, cuts, "NHitsBach", type)) {return false;}
  if(fabs(track->dcaXiToPrimVertex()) > GetDefaultXiCut(dataset, cuts, "DcaXiToPV", type) ) {return false;}
  if(fabs(track->dcaV0ToPrimVertex()) > GetDefaultXiCut(dataset, cuts, "DcaV0ToPV", type) ) {return false;}
  if(fabs(track->dcaXiDaughters()) > GetDefaultXiCut(dataset, cuts, "DcaXiDaughters", type) ) {return false;}
  if(fabs(track->dcaV0Daughters()) > GetDefaultXiCut(dataset, cuts, "DcaV0Daughters", type) ) {return false;}
  if(fabs(track->dcaPosToPrimVertex()) < GetDefaultXiCut(dataset, cuts, "DcaPosToPV", type) || fabs(track->dcaNegToPrimVertex()) < GetDefaultXiCut(dataset, cuts, "DcaNegToPV", type)|| fabs(track->dcaBachelorToPrimVertex()) < GetDefaultXiCut(dataset, cuts, "DcaBachToPV", type) ) {return false;} 
  if(fabs(track->decayLengthXi()) < GetDefaultXiCut(dataset, cuts, "DecayLengthXi", type) ) {return false;}
  if(fabs(track->decayLengthV0()) < GetDefaultXiCut(dataset, cuts, "DecayLengthV0", type) ) {return false;}

  double pt = sqrt(track->momXiX()*track->momXiX()+track->momXiY()*track->momXiY());
  if(pt<ptmin || pt>ptmax) {return false;}


  if(fabs(track->pseudoRapXi())> eta) {return false;}

  //The V0 in the Xi must be a lambda or antilambda so I can apply some reasonable cuts on the mass
  //I'll make these looser than for the V0s
  float massV0;
  //the Xi and omega decay into a lambda + something else
  if(type==4 || type ==5){
    massV0 = track->massLambda() ;
  }
  //where as the anti-Xi and anti-Omega decay into an antilambda + something else
  if(type==18 || type ==19){
    massV0 = track->massAntiLambda() ;
  }
  if(massV0 < 1.0 || massV0 > 1.2 ){return false;}

  //Sanity check on the mass of Xis and Omegas too
  if(type==4 || type == 18){//Xi and anti-Xi, true mass 1.321 GeV
    if(track->massXi() > 1.5 || track->massXi()<1.1 ) {return false;}
  }
  if(type==5 || type == 19){//Omega and anti-Omega, true mass 1.672 GeV
    if(track->massOmega() > 1.9 || track->massOmega()<1.5 ) {return false;}
  }

  return true;
}



bool IsGoodXiTrack(const string dataset, StXiMuDst *track, int type, const string cuts, float ptmin, float ptmax, float eta){
  //cout<<"|3|";
  if(!track) {return false;}
  return IsGoodXiTrack((char*) dataset.c_str(), track,type, (char*) cuts.c_str(), ptmin, ptmax, eta);
}
bool IsGoodXiTrack(const char *dataset, StXiMuDst *track, int type, const string cuts, float ptmin, float ptmax, float eta){
  //cout<<"|4|";
  if(!track) {return false;}
  return IsGoodXiTrack(dataset, track,type, (char*) cuts.c_str(), ptmin, ptmax, eta);
}
bool IsGoodXiTrack(const string dataset, TXiTrack *track, int type, const string cuts, float ptmin, float ptmax, float eta){
  //cout<<"|5|";
  if(!track) {return false;}
  return IsGoodXiTrack((char*) dataset.c_str(),track,type,  (char*) cuts.c_str(), ptmin, ptmax, eta);
}
bool IsGoodXiTrack(const char *dataset, TXiTrack *track, int type, const string cuts, float ptmin, float ptmax, float eta){
  //cout<<"|6|";
  if(!track) {return false;}
  return IsGoodXiTrack(dataset, track,type, (char*)  cuts.c_str(), ptmin, ptmax, eta);
}
bool IsGoodXiTrack(const string dataset, StXiMuDst *track, int type, const char *cuts, float ptmin, float ptmax, float eta){
  //cout<<"|7|";
  if(!track) {return false;}
  ////cout<<" leaving |7| ";
  return IsGoodXiTrack((char*) dataset.c_str(), track, type, cuts, ptmin, ptmax, eta);
}
bool IsGoodXiTrack(const string dataset, TXiTrack *track, int type, const char *cuts, float ptmin, float ptmax, float eta){
  //cout<<"|8|";
  if(!track) {return false;}
  return IsGoodXiTrack((char*) dataset.c_str(), track, type, cuts, ptmin, ptmax, eta);
}



bool IsGoodXiTrack(const char *dataset, StXiMuDst *track,int type, float decaylengthXi, float decaylengthV0, float dcaXi, float dcaV0, float dcaDaughterXi, float dcaDaughterV0, float dcaNeg, float dcaPos, float dcaBach, int nHitsNeg, int nHitsPos, int nHitsBach, float ptmin, float ptmax, float eta){//defaults to loosest cuts in production and accepting all tracks
  //cout<<"|9|";
  if(!track) {return false;}
  if(track->topologyMapPos().numberOfHits(kTpcId) <= nHitsPos){return false;}
  if(track->topologyMapNeg().numberOfHits(kTpcId) <= nHitsNeg) {return false;}
  if(track->topologyMapBachelor().numberOfHits(kTpcId) <= nHitsBach) {return false;}
  if(fabs(track->decayLengthXi()) < decaylengthXi) {return false;}
  if(fabs(track->decayLengthV0()) < decaylengthV0) {return false;}
  if(fabs(track->dcaPosToPrimVertex()) < dcaPos || fabs(track->dcaNegToPrimVertex()) < dcaNeg || fabs(track->dcaBachelorToPrimVertex()) < dcaBach) {return false;} 
  if(fabs(track->dcaXiDaughters()) > dcaDaughterXi) {return false;}
  if(fabs(track->dcaV0Daughters()) > dcaDaughterV0) {return false;}
  if(fabs(track->dcaXiToPrimVertex()) > dcaXi) {return false;}
  if(fabs(track->dcaV0ToPrimVertex()) > dcaV0) {return false;}

  double pt = sqrt(track->momXiX()*track->momXiX()+track->momXiY()*track->momXiY());
  if(pt<ptmin || pt>ptmax) {return false;}


  if(fabs(track->pseudoRapXi())> eta) {return false;}


  //last check - is mass reasonable?
  //The V0 in the Xi must be a lambda or antilambda so I can apply some reasonable cuts on the mass
  //I'll make these looser than for the V0s
  float massV0;
  //the Xi and omega decay into a lambda + something else
  if(type==4 || type ==5){
    massV0 = track->massLambda() ;
  }
  //where as the anti-Xi and anti-Omega decay into an antilambda + something else
  if(type==18 || type ==19){
    massV0 = track->massAntiLambda() ;
  }
  if(massV0 < 1.0 || massV0 > 1.2 ){return false;}

  //Sanity check on the mass of Xis and Omegas too
  if(type==4 || type == 18){//Xi and anti-Xi, true mass 1.321 GeV
    if(track->massXi() > 1.5 || track->massXi()<1.1 ) {return false;}
  }
  if(type==5 || type == 19){//Omega and anti-Omega, true mass 1.672 GeV
    if(track->massOmega() > 1.9 || track->massOmega()<1.5 ) {return false;}
  }

  return true;
}

bool IsGoodXiTrack(const char *dataset, TXiTrack *track, int type, float decaylengthXi, float decaylengthV0, float dcaXi, float dcaV0, float dcaDaughterXi, float dcaDaughterV0, float dcaNeg , float dcaPos, float dcaBach , int nHitsNeg, int nHitsPos, int nHitsBach , float ptmin, float ptmax, float eta){  
  //cout<<"|10|";
  //cout<<"hi"<<endl;
  if(!track) {return false;}
  if(track->GetNHitsPosDaughter() <= nHitsPos){return false;}
  if(track->GetNHitsNegDaughter() <= nHitsNeg) {return false;}
  if(track->GetNHitsBachDaughter() <= nHitsBach) {return false;}
  if(fabs(track->GetDecayLengthXi()) < decaylengthXi) {return false;}
  if(fabs(track->GetDecayLengthV0()) < decaylengthV0) {return false;}
  if(fabs(track->GetDcaPosDaughterToPV()) < dcaPos || fabs(track->GetDcaNegDaughterToPV()) < dcaNeg || fabs(track->GetDcaBachDaughterToPV()) < dcaBach) {return false;} 
  if(fabs(track->GetDcaXiDaughters()) > dcaDaughterXi) {return false;}
  if(fabs(track->GetDcaV0Daughters()) > dcaDaughterV0) {return false;}
  if(fabs(track->GetDcaXiToPV()) > dcaXi) {return false;}
  if(fabs(track->GetDcaV0ToPV()) > dcaV0) {return false;}

  double pt = track->GetPt();
  if(pt<ptmin || pt>ptmax) {return false;}


  if(fabs(track->GetEta())> eta) {return false;}

  //last check - is mass reasonable?
  if(track->GetMassV0() < 1.0 || track->GetMassV0() > 1.2 ){return false;}

  //Sanity check on the mass of Xis and Omegas too
  if(type==4 || type == 18){//Xi and anti-Xi, true mass 1.321 GeV
    if(track->GetMass() > 1.5 || track->GetMass()<1.1 ) {return false;}
  }
  if(type==5 || type == 19){//Omega and anti-Omega, true mass 1.672 GeV
    if(track->GetMass() > 1.9 || track->GetMass()<1.5 ) {return false;}
  }

  return true;
}

bool IsGoodXiTrack(const string dataset, StXiMuDst *track,int type, float decaylengthXi, float decaylengthV0, float dcaXi, float dcaV0, float dcaDaughterXi, float dcaDaughterV0, float dcaNeg , float dcaPos, float dcaBach , int nHitsNeg, int nHitsPos, int nHitsBach, float ptmin, float ptmax, float eta){
  //cout<<"|11|";
  if(!track) {return false;}
  return IsGoodXiTrack( (char*) dataset.c_str(),track, type,  decaylengthXi,  decaylengthV0,  dcaXi,  dcaV0,  dcaDaughterXi,  dcaDaughterV0,  dcaNeg ,  dcaPos,  dcaBach ,  nHitsNeg,  nHitsPos,  nHitsBach,  ptmin,  ptmax,  eta);
}


bool IsGoodXiTrack(const string dataset, TXiTrack *track, int type, float decaylengthXi, float decaylengthV0, float dcaXi, float dcaV0, float dcaDaughterXi, float dcaDaughterV0, float dcaNeg , float dcaPos, float dcaBach , int nHitsNeg, int nHitsPos, int nHitsBach, float ptmin, float ptmax, float eta){
  //cout<<"|12|";
  if(!track) {return false;}
  return  IsGoodXiTrack((char*) dataset.c_str(), track,  type,  decaylengthXi,  decaylengthV0,  dcaXi,  dcaV0,  dcaDaughterXi,  dcaDaughterV0,  dcaNeg ,  dcaPos,  dcaBach ,  nHitsNeg,  nHitsPos,  nHitsBach,  ptmin,  ptmax,  eta);
}


