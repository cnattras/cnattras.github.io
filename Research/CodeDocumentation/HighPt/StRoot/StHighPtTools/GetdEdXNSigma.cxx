#include "GetdEdXNSigma.h"

double GetdEdXNSigma(char *dataset, double momOverMass, double realDedx,double numDedx,double errDedx,double trackLength,double eta){
  double nSigma = 10000.;
  string myDataSet = dataset;
  string AuAu200 = "AuAu200";
  string AuAu200Y2 = "AuAu200Y2";
  string dAu200 = "dAu200";
  string CuCu200 = "CuCu200";
  string CuCu62 = "CuCu62";
  string AuAu62 = "AuAu62";
  if(dataset == AuAu200Y2){//from Jana's code DeltaPhiStrangeMakerNew
    if (numDedx<=0||errDedx<=0) nSigma = 10000;
    else{
      double corCentRes = 0.45;
      double resolution = corCentRes/sqrt(numDedx);
      Bichsel mBichsel;   
      double xpctdDedx = mBichsel.GetI70(log10(momOverMass),1,0); 
      nSigma = log(1e6*realDedx/xpctdDedx)/resolution; 
    }
  }
  if(dataset==AuAu200 || dataset==CuCu200){//This is only in the code temporarily!  I will have to change for the CuCu data
    if(trackLength !=-100 && eta != -100){//check for default arguments, this needs all of them
      //From Matt's code
      double texpectedDedx = 0;
      BetheBloch betheBloch;
      if (trackLength>0)
	texpectedDedx = 1.e-6*betheBloch.Sirrf(momOverMass,trackLength,0);
      else
	texpectedDedx = betheBloch(momOverMass); 
      
      if ((numDedx<=0)||(trackLength<=0)) nSigma= 10000;
      else{
	double corEtaRes    = 0;
	double finalRes     = 0;
	double resEtaBin[10];
	// 0 to 10% central
	resEtaBin[0]= 0.565451;
	resEtaBin[1]= 0.567282;
	resEtaBin[2]= 0.570028;
	resEtaBin[3]= 0.553112;
	resEtaBin[4]= 0.534385;
	resEtaBin[5]= 0.533169;
	resEtaBin[6]= 0.525529;
	resEtaBin[7]= 0.519565;
	resEtaBin[8]= 0.49704;
	resEtaBin[9]= 0.521292;
	
	if (TMath::Abs(eta)>1) eta = 0.99;
	corEtaRes = resEtaBin[(int)(TMath::Abs(eta*10))];
	finalRes = corEtaRes/sqrt(numDedx);
	nSigma = log(realDedx/texpectedDedx)/finalRes; 
      }
    }
  }
  return nSigma;
}

double GetPosDaughtdEdXNSigma(char *dataset, StV0MuDst *track, int type){
  double fPosMass = -1.;
  if(type==1){
    fPosMass   = 0.93827231;
  }
  if(type==2) {
    fPosMass   = 0.13957018;
  }
  if(type==3) {
    fPosMass   = 0.13957018;
  }
  return GetdEdXNSigma(dataset, (track->ptotPos())/fPosMass, track->dedxPos(), track->numDedxPos(), track->errDedxPos(), track->lenDedxPos(), track->pseudoRapV0() );//This function has a problem because I shouldn't pass the eta of the V0
}
double GetNegDaughtdEdXNSigma(char *dataset, StV0MuDst *track, int type){
  double fNegMass;
  if(type==1){
    fNegMass   = 0.13957018;
  }
  if(type==2) {
    fNegMass   = 0.93827231;
  }
  if(type==3) {
    fNegMass   = 0.13957018;
  }

  return GetdEdXNSigma(dataset, (track->ptotNeg())/fNegMass, track->dedxNeg(), track->numDedxNeg(), track->errDedxNeg(), track->lenDedxNeg(), track->pseudoRapV0() );//This function has a problem because I shouldn't pass the eta of the V0
}
double GetPosDaughtdEdXNSigma(char *dataset, TV0Track *track, int type){
  return track->GetdEdxPosDaughter();
}


double GetNegDaughtdEdXNSigma(string dataset, StV0MuDst *track, int type){
  return GetNegDaughtdEdXNSigma( (char*) dataset.c_str(), track, type);
}
double GetNegDaughtdEdXNSigma(string dataset, TV0Track *track, int type){
  return GetNegDaughtdEdXNSigma( (char*) dataset.c_str(), track, type);
}
