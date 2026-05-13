// @(#)root/test:$Name:  $:$Id: Event.cxx,v 1.22 2003/08/23 00:08:13 rdm Exp $
// Author: Rene Brun   19/08/96
// Modified by Jana Bielcikova

////////////////////////////////////////////////////////////////////////
//
//                       TEvent class
//                       =======================
//
//  The TEvent class is a naive/simple example of an event structure.
//     public:
//        char           fType[20];
//        Int_t          fNtrack;
//        EventHeader    fEvtHdr;
//        TClonesArray  *fTracks;
//        TRefArray     *fChargedTracks;
//        TRefArray     *fLambdas;
//        TRef           fLastTrack;         //pointer to last track
//        TH1F          *fH;
//
//   The EventHeader class has 2 data members (integers):
//     public:
//        Int_t          fEvtNum;
//        Int_t          fRun;
//      PUT TRIGGER INFO HERE LATER 
//
//
//   The Event data member fTracks is a pointer to a TClonesArray.
//   It is an array of a variable number of tracks per event.
//   Each element of the array is an object of class Track with the members:
//     private:
//        Float_t      fPx;           //X component of the momentum
//        Float_t      fPy;           //Y component of the momentum
//        Float_t      fPz;           //Z component of the momentum
//        Float_t      fMass;        //The mass of this particle
//        Float_t      fCharge;       //Charge of this track
//        Int_t        fNpoint;       //Number of points for this track

//
//   An example of a batch program to use the Event/Track classes is given
//   in this directory: MainEvent.
//   Look also in the same directory at the following macros:
//     - eventa.C  an example how to read the tree
//     - eventb.C  how to read events conditionally
//
//   During the processing of the event (optionally) also a large number
//   of histograms can be filled. The creation and handling of the
//   histograms is taken care of by the HistogramManager class.
//
////////////////////////////////////////////////////////////////////////


#include <iostream>
using namespace std;
#include <math.h>
#include <string>
#include "TDirectory.h"
#include "TProcessID.h"

#include "TEvent.h"
#include "TTrack.h"
//#include "TV0Track.h"

ClassImp(TEventHeader)
ClassImp(TEvent)



TClonesArray *TEvent::fgIDTracks = 0;
TClonesArray *TEvent::fgTracks = 0;
TClonesArray *TEvent::fgResTracks = 0;
TClonesArray *TEvent::fgXiTracks = 0;

//______________________________________________________________________________
TEvent::TEvent()
{
   // Create an TEvent object.
   // When the constructor is invoked for the first time, the class static
   // variable fgTracks is 0 and the TClonesArray fgTracks is created.
  // was 1000 !
   if (!fgTracks) fgTracks = new TClonesArray("TTrack", 1000);
   fTracks = fgTracks;
   if (!fgIDTracks) fgIDTracks = new TClonesArray("TIdentifiedTrack", 1000);
   fIDTracks = fgIDTracks;
   if (!fgResTracks) fgResTracks = new TClonesArray("TResonanceTrack", 1000);
   fResTracks = fgResTracks;
   if (!fgXiTracks) fgXiTracks = new TClonesArray("TXiTrack", 1000);
    fXiTracks = fgXiTracks;
   //  fChargedTracks = new TRefArray;
   // fLambdas  = new TRefArray;
   // faLambdas = new TRefArray;
   fNtrack = 0;
   fNIDtrack = 0;
   fNRestrack = 0;
   fNXitrack = 0;
   fMultiplicity = 0;
   fZVertex = -1000;
   fEventName = 0;
}

//______________________________________________________________________________
TEvent::~TEvent()
{
   Clear();
   //   delete fChargedTracks; fChargedTracks = 0;
   // delete fLambdas;  fLambdas = 0;
   // delete faLambdas;  faLambdas = 0;
   if (fEventName) delete [] fEventName;
}


//______________________________________________________________________________
TTrack *TEvent::AddTrack(TTrack *tr, Float_t ptmin, Int_t particleType)
{
   // Add a new track to the list of tracks for this event.
   // To avoid calling the very time consuming operator new for each track,
   // the standard but not well know C++ operator "new with placement"
   // is called. If tracks[i] is 0, a new Track object will be created
   // otherwise the previous Track[i] will be overwritten.

   TClonesArray &tracks = *fTracks;
   TTrack *track = new(tracks[fNtrack++]) TTrack(tr);
   //Save reference to last Track in the collection of Tracks
   fLastTrack = track;

   //Save reference in fChargedTracks if track is a good charged track
   // if (track->GetPt() > ptmin && particleType==1) fChargedTracks->Add(track);
   //Save reference in fLambdas if track is a lambda candidate
   //   if (track->GetPt() > ptmin && particleType==2) fLambdas->Add(track);
   //Save reference in faLambdas if track is an Anti-lambda candidate
   // if (track->GetPt() > ptmin && particleType==3) faLambdas->Add(track);

   return track;
}

//______________________________________________________________________________
TIdentifiedTrack *TEvent::AddTIdentifiedTrack(TIdentifiedTrack *tr, Float_t ptmin, Int_t particleType)
{
   // Add a new track to the list of tracks for this event.
   // To avoid calling the very time consuming operator new for each track,
   // the standard but not well know C++ operator "new with placement"
   // is called. If tracks[i] is 0, a new Track object will be created
   // otherwise the previous Track[i] will be overwritten.
   TClonesArray &tracks = *fIDTracks;
   TIdentifiedTrack *track = new(tracks[fNIDtrack++]) TIdentifiedTrack(tr);
   //Save reference to last Track in the collection of Tracks
   fLastTrack = track;

   //Save reference in fChargedTracks if track is a good charged track
   // if (track->GetPt() > ptmin && particleType==1) fChargedTracks->Add(track);
   //Save reference in fLambdas if track is a lambda candidate
   //   if (track->GetPt() > ptmin && particleType==2) fLambdas->Add(track);
   //Save reference in faLambdas if track is an Anti-lambda candidate
   // if (track->GetPt() > ptmin && particleType==3) faLambdas->Add(track);

   return track;
}
TResonanceTrack *TEvent::AddTResonanceTrack(TResonanceTrack *tr)
{
   // Add a new track to the list of tracks for this event.
   // To avoid calling the very time consuming operator new for each track,
   // the standard but not well know C++ operator "new with placement"
   // is called. If tracks[i] is 0, a new Track object will be created
   // otherwise the previous Track[i] will be overwritten.
   TClonesArray &tracks = *fResTracks;
   TResonanceTrack *track = new(tracks[fNRestrack++]) TResonanceTrack(tr);
   //Save reference to last Track in the collection of Tracks
   //fLastTrack = track;

   //Save reference in fChargedTracks if track is a good charged track
   // if (track->GetPt() > ptmin && particleType==1) fChargedTracks->Add(track);
   //Save reference in fLambdas if track is a lambda candidate
   //   if (track->GetPt() > ptmin && particleType==2) fLambdas->Add(track);
   //Save reference in faLambdas if track is an Anti-lambda candidate
   // if (track->GetPt() > ptmin && particleType==3) faLambdas->Add(track);

   return track;
}


//______________________________________________________________________________
TXiTrack *TEvent::AddXiTrack(TXiTrack *tr, Float_t ptmin, Int_t particleType)
{
   // Add a new track to the list of tracks for this event.
   // To avoid calling the very time consuming operator new for each track,
   // the standard but not well know C++ operator "new with placement"
   // is called. If tracks[i] is 0, a new Track object will be created
   // otherwise the previous Track[i] will be overwritten.

   TClonesArray &Xitracks = *fXiTracks;
   TXiTrack *Xitrack = new(Xitracks[fNXitrack++]) TXiTrack(tr);
   //Save reference to last Track in the collection of Tracks
   fLastXiTrack = Xitrack;

   //Save reference in fChargedTracks if track is a good charged track
   // if (track->GetPt() > ptmin && particleType==1) fChargedTracks->Add(track);
   //Save reference in fLambdas if track is a lambda candidate
   //   if (track->GetPt() > ptmin && particleType==2) fLambdas->Add(track);
   //Save reference in faLambdas if track is an Anti-lambda candidate
   // if (track->GetPt() > ptmin && particleType==3) faLambdas->Add(track);

   return Xitrack;
}



//______________________________________________________________________________
 void TEvent::Clear(Option_t *option)
{
   fTracks->Clear("C"); //will also call Track::Clear
   fXiTracks->Clear("C"); //will also call Track::Clear
   fResTracks->Clear("C"); //will also call Track::Clear
   fIDTracks->Clear("C"); //will also call Track::Clear
   // fChargedTracks->Delete();
   // fLambdas->Delete();
   // faLambdas->Delete();
}

//______________________________________________________________________________
 void TEvent::Reset(Option_t *option)
{
// Static function to reset all static objects for this event
//   fgTracks->Delete(option);

   delete fgTracks; fgTracks = 0;
   delete fgXiTracks; fgXiTracks = 0;
   delete fgResTracks; fgResTracks = 0;
   delete fgIDTracks; fgIDTracks = 0;
   
}

//______________________________________________________________________________
//void TEvent::SetHeader(Int_t run, Int_t i, StTriggerId trigger)
void TEvent::SetHeader(Int_t run, Int_t i, Int_t trigger1, Int_t trigger2)
{
   fNtrack = 0;
   // fNV0track = 0;
   fEvtHdr.Set(run, i, trigger1, trigger2);
}

/*
TClonesArray* TEvent::GetTracks(){
  if(fIDTracks->GetEntries()>0) return fIDTracks;
  else{ return fTracks;}
}


*/
