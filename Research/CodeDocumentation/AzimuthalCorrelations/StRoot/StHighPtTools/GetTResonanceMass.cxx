#include "GetTResonanceMass.h"

float GetTResonanceMass(StMuTrack *posTrack, StMuTrack *negTrack, int particleType){
  Double_t epos,eneg,invmass;
  Double_t fPosMass,fNegMass;
  if(particleType==14){
    fPosMass   = 0.93827231;
    fNegMass   = 0.13957018;
  }
  if(particleType==15) {
    fPosMass   = 0.13957018;
    fNegMass   = 0.93827231;
  }
  if(particleType==16) {
    fPosMass   = 0.13957018;
    fNegMass   = 0.13957018;
  }
  if(particleType==17) {
    fPosMass   = 0.4937;
    fNegMass   = 0.4937;
  }
  
  epos = sqrt(posTrack->p().x()*posTrack->p().x()+posTrack->p().y()*posTrack->p().y()+
	      posTrack->p().z()*posTrack->p().z()+fPosMass*fPosMass);
  eneg = sqrt(negTrack->p().x()*negTrack->p().x()+negTrack->p().y()*negTrack->p().y()+
	      negTrack->p().z()*negTrack->p().z()+ fNegMass*fNegMass);
  float p = GetTResonanceP(posTrack,negTrack);
  invmass = sqrt((epos+eneg)*(epos+eneg) - p*p );
  return invmass;
  
}
