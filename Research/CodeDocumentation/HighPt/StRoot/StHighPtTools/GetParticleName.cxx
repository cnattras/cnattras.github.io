#include "GetParticleName.h"
char *GetParticleName(int partID){
  switch(partID){
  case 0:
    return "h";
  case 1:
    return "#Lambda";
  case 2:
    return "#bar{#Lambda}";
  case 3:
    return "K^{0}_{s}";
  case 4:
    return "#Xi";
  case 5:
    return "#Omega";
  case 6:
    return "#pi^{+}";
  case 7:
    return "#pi^{-}";
  case 8:
    return "p";
  case 9:
    return "#bar{p}";
  case 10:
    return "K^{+}";
  case 11:
    return "K^{-}";
  case 12:
    return "e^{+}";
  case 13:
    return "e^{-}";
  case 14:
    return "#Lambda (resonance)";
  case 15:
    return "#bar{#Lambda} (resonance)";
  case 16:
    return "K^{0}_{s} (resonance)";
  case 17:
    return "#phi";
  case 18:
    return "#bar{#Xi}";
  case 19:
    return "#bar{#Omega}";
  case 20:
    return "#Lambda (resonance, fake)";
  case 21:
    return "#bar{#Lambda} (resonance, fake)";
  case 22:
    return "K^{0}_{s} (resonance, fake)";
  case 23:
    return "#phi (fake)";
  default:
    return "junk";
  }
}
char *GetSimpleParticleName(int partID){
  switch(partID){
  case 0:
    return "h";
  case 1:
    return "Lambda";
  case 2:
    return "AntiLambda";
  case 3:
    return "K0";
  case 4:
    return "Xi";
  case 5:
    return "Omega";
  case 6:
    return "piPlus";
  case 7:
    return "piMinus";
  case 8:
    return "p";
  case 9:
    return "Antip";
  case 10:
    return "KPlus";
  case 11:
    return "KMinus";
  case 12:
    return "ePlus";
  case 13:
    return "eMinus";
  case 14:
    return "LambdaRes";
  case 15:
    return "AntiLambdaRes";
  case 16:
    return "K0Res";
  case 17:
    return "phi";
  case 18:
    return "AntiXi";
  case 19:
    return "AntiOmega";
  case 20:
    return "LambdaFakeRes";
  case 21:
    return "AntiLambdaFakeRes";
  case 22:
    return "K0sFakeRes";
  case 23:
    return "phiFake";
  default:
    return "junk";
  }
}
