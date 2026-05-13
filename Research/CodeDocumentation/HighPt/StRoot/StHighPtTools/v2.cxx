#ifndef __CINT__
#  include "v2.h"
#  include "centrality.h"
#  include <string> 
#  include "Riostream.h"//needed to use things like cout, which I will use primarily for debugging
#endif

float v2(const char *dataset, float pt, int multiplicity, int partID=0){
  string myDataSet = dataset;
  string AuAu200 = "AuAu200";
  string CuCu200 = "CuCu200";
  string AuAu62 = "AuAu62";
  float myv2 = 0;

  if(dataset == AuAu200){
    int centBin = centrality(dataset,multiplicity);
    //There are four parameters in the fit for v2
    //Below are the pars for charged particles
    //pars0[parameter number][centrality bin]
    //Note that Jana's numbering for centrality bins is different from Fuqiang's
    //values for the first line of pars0 w/ the reaction plane method
    //{.04969,.09257,.13223,.15053,.17179,.22424,.21279,.29552,.57844,.00001,
    if(partID==0){
      float pars0[4][9]=
	{.02485,.07175,.11651,.13469,.15303,.19429,.17544,.23388,.28922,
	 1.273,1.341,1.308,1.213,1.208,1.303,1.258,1.410,1.587,
	 3.133,2.357,2.326,2.846,2.750,2.002,2.241,1.376,.514,
	 1.352,.924,.883,1.027,1.097,0.925,.981,.809,.568};
      // Jana added: this is necessary above pt>3.0 GeV/c as the parametrization falls off ...
      float v2high[9]={0.06396,0.10629,0.14183,0.18441,0.19075,0.20646,0.21647,0.26423,0.25673};
      if(pt<3.0) {
	myv2=pars0[0][centBin]*pow(pt,pars0[1][centBin])*exp(-pow(pt/pars0[2][centBin],pars0[3][centBin]));
      } else {
	myv2=v2high[centBin];
      }    
    }
    if(partID==1 || partID==2){//lambda or antilambda
      if(pt<3.0) {
	float polk[4]={-3.98188e-002,1.53380e-001,-3.96073e-002,3.25804e-003};
	float poll[4]={-3.03115e-002,5.65700e-002,3.04548e-002,-8.52369e-003};
	float factor=(poll[0]+poll[1]*pt+poll[2]*pt*pt+poll[3]*pt*pt*pt)/(polk[0]+polk[1]*pt+polk[2]*pt*pt+polk[3]*pt*pt*pt);
	myv2=factor*v2(dataset,pt,multiplicity,0);
      } 
      else {
	myv2=1.22*v2(dataset,pt,multiplicity,0);
      }
    }
    if(partID==3){
      myv2=v2(dataset,pt,multiplicity,0);
    }
  }



  if(dataset == CuCu200){
    myv2 = v2("AuAu200",pt,multiplicity, partID);//This actually isn't correct but it's a temporary fix because I have to put in the real v2's
  }

    return myv2;
}
