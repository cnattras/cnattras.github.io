#ifndef TIdentifiedTrack_h
#define TIdentifiedTrack_h
#include "TTrack.h"
class TIdentifiedTrack : public TTrack {
 public:
  TIdentifiedTrack(){};
  TIdentifiedTrack(const TIdentifiedTrack* orig);
  TIdentifiedTrack(const TTrack* orig);//Copies everything but the new variables.  Sets defaults for new variables.
  virtual ~TIdentifiedTrack(){Clear();}
  void Clear(Option_t *option="") { ;}

  double GetNSigmaProton() const {return nSigmaProton;}
  double GetNSigmaPion() const {return nSigmaPion;}
  double GetNSigmaKaon() const {return nSigmaKaon;}
  double GetNSigmaElectron() const {return nSigmaElectron;}
  double GetdEdX() const {return dEdX;} 

  void SetNSigmaProton(float value){ nSigmaProton= value;}
  void SetNSigmaPion(float value){ nSigmaPion= value;}
  void SetNSigmaKaon(float value){ nSigmaKaon= value;}
  void SetNSigmaElectron(float value){ nSigmaElectron= value;}
  void SetdEdX(float value){ dEdX = value;}

 private:
  double nSigmaProton, nSigmaElectron, nSigmaPion, nSigmaKaon;
  double dEdX;

  ClassDef(TIdentifiedTrack,1)
};
#endif
