#include "GetTResonanceP.h"

float GetTResonanceP(StMuTrack *posTrack, StMuTrack *negTrack){
  float px = posTrack->p().x() + negTrack->p().x();
  float py = posTrack->p().y() + negTrack->p().y();
  float pz = posTrack->p().z() + negTrack->p().z();
  return sqrt(px*px+py*py+pz*pz);
}

float GetTResonancePt(StMuTrack *posTrack, StMuTrack *negTrack){
  float px = posTrack->p().x() + negTrack->p().x();
  float py = posTrack->p().y() + negTrack->p().y();
  return sqrt(px*px+py*py);
}
float GetTResonancePx(StMuTrack *posTrack, StMuTrack *negTrack){
  return posTrack->p().x() + negTrack->p().x();
}
float GetTResonancePy(StMuTrack *posTrack, StMuTrack *negTrack){
  return posTrack->p().y() + negTrack->p().y();
}

float GetTResonancePhi(StMuTrack *posTrack, StMuTrack *negTrack){
  float py = GetTResonancePy(posTrack,negTrack);
  float px = GetTResonancePx(posTrack,negTrack);
  return atan2(py,px);
}

float GetTResonanceOpeningAngle(StMuTrack *posTrack, StMuTrack *negTrack){
  float posPhi = atan2( posTrack->p().y() , posTrack->p().x() );
  float negPhi = atan2( negTrack->p().y() , negTrack->p().x() );
  return dPhi(posPhi, negPhi);
}
