#include "dPhi.h"
Float_t dPhi(float phi1, float phi2) {
  float deltaPhi;
  deltaPhi = phi1 - phi2;
  if (deltaPhi>TMath::Pi()) deltaPhi-=2*(TMath::Pi());
  if (deltaPhi<-TMath::Pi()) deltaPhi+=2*(TMath::Pi());  
  return deltaPhi;
}
