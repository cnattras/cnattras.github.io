#include "GetV0Mass.h"

double GetV0Mass(StV0MuDst* v0Candidate, int particleType) {
  Double_t epos,eneg,invmass;
  Double_t fPosMass,fNegMass;
  if(particleType==1){
    fPosMass   = 0.93827231;
    fNegMass   = 0.13957018;
  }
  if(particleType==2) {
    fPosMass   = 0.13957018;
    fNegMass   = 0.93827231;
  }
  if(particleType==3) {
    fPosMass   = 0.13957018;
    fNegMass   = 0.13957018;
  }
  
  epos = sqrt(v0Candidate->momPosX()*v0Candidate->momPosX()+v0Candidate->momPosY()*v0Candidate->momPosY()+
		 v0Candidate->momPosZ()*v0Candidate->momPosZ()+fPosMass*fPosMass);
  eneg = sqrt(v0Candidate->momNegX()*v0Candidate->momNegX()+v0Candidate->momNegY()*v0Candidate->momNegY()+
	       v0Candidate->momNegZ()*v0Candidate->momNegZ()+ fNegMass*fNegMass);
  invmass = sqrt((epos+eneg)*(epos+eneg) - (v0Candidate->momV0X()*v0Candidate->momV0X()+
	       v0Candidate->momV0Y()*v0Candidate->momV0Y()+v0Candidate->momV0Z()*v0Candidate->momV0Z()));
  return invmass;
}

double GetV0Mass(TV0Track *v0Candidate, int particleType) {
  return v0Candidate->GetMass();
}
