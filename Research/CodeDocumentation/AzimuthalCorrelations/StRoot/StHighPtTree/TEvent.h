//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TEvent                                                               //
//                                                                      //
// Description of the event           parameters                        //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#ifndef TEvent_h
#define TEvent_h
#include "TObject.h"
#include "TClonesArray.h"
#include "TRefArray.h"
#include "TRef.h"
#include "TMath.h"
#include "TIdentifiedTrack.h"
#include "TResonanceTrack.h"
#include "TXiTrack.h"

#include "StTriggerId.h"

//class TDirectory;
class TTrack;
//class TV0Track;

class TEventHeader {

private:
   Int_t   fRun;
   Int_t   fEvtNum;
   Int_t fTrigger1;
   Int_t fTrigger2;
   

public:
   TEventHeader() :  fRun(0), fEvtNum(0), fTrigger1(), fTrigger2() { }
   virtual ~TEventHeader() { }
   void   Set(Int_t r, Int_t i, Int_t trigger1, Int_t trigger2) { fRun = r; fEvtNum = i; fTrigger1 = trigger1; fTrigger2 = trigger2;}
   Int_t  GetEvtNum() const { return fEvtNum; }
   Int_t  GetRun() const { return fRun; }
   Int_t GetTrigger1() {return fTrigger1;}
   Int_t GetTrigger2() {return fTrigger2;}
   ClassDef(TEventHeader,1)  //Event Header
};


class TEvent : public TObject {

 private:
  // char           fType[20];          //event type
  char          *fEventName;         //run+event number in character format
  Int_t          fNtrack;            //Number of charged tracks
  Int_t          fNIDtrack;            //Number of charged tracks
  Int_t          fNRestrack;            //Number of charged tracks
  Int_t          fNXitrack;
  Int_t          fMultiplicity;      //Event multiplicity of all detected charged particles
  Float_t        fZVertex;           //z position of vertex
  TEventHeader   fEvtHdr;
  TClonesArray  *fResTracks;               //->array with all TResonance tracks
  TClonesArray  *fIDTracks;               //->array with all charged identified tracks
  TClonesArray  *fTracks;               //->array with all charged tracks
  TClonesArray  *fXiTracks;               //->array with all V0 tracks
  //   TRefArray     *fChargedTracks;        //array of Charged tracks only
  //   TRefArray     *fLambdas;              //array of Lambda tracks only
  //   TRefArray     *faLambdas;              //array of AntiLambda tracks only
  TRef           fLastTrack;         //reference pointer to last track
  TRef           fLastXiTrack;
  
  static TClonesArray *fgResTracks;
  static TClonesArray *fgIDTracks;
  static TClonesArray *fgTracks;
  static TClonesArray *fgXiTracks;
  Int_t highPtFlag[3];
  
 public:
  TEvent();
  virtual ~TEvent();
  void          Clear(Option_t *option ="");
  static void   Reset(Option_t *option ="");
  void          SetNtrack(Int_t n) { fNtrack = n; }
  void          SetMultiplicity(Int_t n) {fMultiplicity = n;}
  void          SetZVertex(Float_t n) {fZVertex = n;}
  // void          SetType(char *type) {strcpy(fType,type);}
  //  void          SetHeader(Int_t i, Int_t run, StTriggerId trigger);
  void          SetHeader(Int_t i, Int_t run, Int_t trigger1, Int_t trigger2);
  void SetHighPtFlag(int val1, int val2, int val3)  {highPtFlag[0]=val1; highPtFlag[1]=val2; highPtFlag[2]=val3;}
  
  TTrack        *AddTrack(TTrack*,Float_t, Int_t);
  TIdentifiedTrack        *AddTIdentifiedTrack(TIdentifiedTrack*,Float_t, Int_t);
  TResonanceTrack        *AddTResonanceTrack(TResonanceTrack*);
  TXiTrack  *AddXiTrack(TXiTrack*,Float_t, Int_t);
  
  // char         *GetType() {return fType;}
  Int_t         GetNtrack() const { return fNtrack; }
  Int_t         GetMultiplicity() const { return fMultiplicity;}
  Float_t       GetZVertex() const {return fZVertex;}
  TEventHeader  *GetHeader() { return &fEvtHdr; }
  //I actually want GetTracks to do something more complicated now...
  TClonesArray *GetTracks() const {if(fIDTracks->GetEntries()>0){return fIDTracks;}else{return fTracks;}}
  //TClonesArray *GetTracks() const {return fTracks;}
  //TClonesArray *GetTracks();

  TClonesArray *GetTResonanceTracks() const {return fResTracks;}
  TClonesArray *GetTIdentifiedTracks() const {return fIDTracks;}
  TClonesArray *GetXiTracks() const {return fXiTracks;}
  // TRefArray    *GetChargedTracks() const {return fChargedTracks;}
  //   TRefArray    *GetLambdas() const {return fLambdas;}
  // TRefArray    *GetaLambdas() const {return faLambdas;}
  TTrack        *GetLastTrack() const {return (TTrack*)fLastTrack.GetObject();}
  TXiTrack      *GetLastXiTrack() const {return (TXiTrack*)fLastXiTrack.GetObject();}
  Int_t GetHighPtFlag(Int_t i) {return highPtFlag[i];}
  ClassDef(TEvent,1)  //Event structure
};

#endif

