#include "AnalysisMaker.h"
ClassImp(AnalysisMaker)
//initializing static strings which hold information on data set
string  AnalysisMaker::CuCu200 = "CuCu200";
string  AnalysisMaker::AuAu200Y2 = "AuAu200Y2";
string  AnalysisMaker::AuAu200 = "AuAu200";
string  AnalysisMaker::CuCu62 = "CuCu62";
string  AnalysisMaker::AuAu62 = "AuAu62";
string  AnalysisMaker::dAu200 = "dAu200";


void AnalysisMaker::Initialize(){
  //I don't know what type off Event Loop it will be yet
  IsTEvent = false;
  IsStEvent = false;
  goodEvent = false;
  //the default is to use the default cuts (duh)
  useDefaultEventCuts = true;
  //set default triggers to those for the data set using the function goodTriggers in the StHighPtEvaluator library
 SetDefaultTriggers();
 //Initialize pointers to NULL
 SetNullPointers();


 zvertex = -1000;

 //Set the number of events to 0
 nevent = 0;

 //default track cuts
 nHitsFit = 15;
 ptMin = 1.0;
 ptMax = 10.0;
 eta = 1.0;
 dca = 1.0;

 nEvents = 0;

 //by default don't make TIdentifiedTracks (they take up more space/ memory)
 MakeIdentifiedTrack = false;

 //V0 cuts
 UseCustomCuts = false;
 UseDefaultV0CutsTree = true;
 UseDefaultV0CutsCorrelation = false;
 UseDefaultV0CutsSpectra = false;
 UseLoosestV0Cuts = false;
 decayLengthLam = 0.;
 dcaV0ToPVLam = 100.;
 dcaDaughtersLam = 100.;
 dcaNegToPVLam = 0.0;
 dcaPosToPVLam = 0.0;
 nHitsPosLam = 15;
 nHitsNegLam = 15;
 decayLengthAlam = 0.;
 dcaV0ToPVAlam = 100.;
 dcaDaughtersAlam = 100.;
 dcaNegToPVAlam = 0.0;
 dcaPosToPVAlam = 0.0;
 nHitsPosAlam = 15;
 nHitsNegAlam = 15;
 decayLengthK0 = 0.;
 dcaV0ToPVK0 = 100.;
 dcaDaughtersK0 = 100.;
 dcaNegToPVK0 = 0.0;
 dcaPosToPVK0 = 0.0;
 nHitsPosK0 = 15;
 nHitsNegK0 = 15;
 v0ptmin = 0.0;
 v0ptmax = 10.0;
 v0eta = 1.0;
 xiptmin = 0.0;
 xiptmax = 10.0;
 xieta = 1.0;

 trigger[0]=-1;
 trigger[1]=-1;

  makeTResTracks = false;
  lowResPt = 2.0;


  hLambdaResMass = new TH1F("hLambdaResMass","#Lambda mass (GeV) (resonance)",100,1.0,1.2);
  hLambdaResMass->SetYTitle("number of entries");
  hLambdaResMass->SetXTitle("Mass (GeV)");
  hAntilambdaResMass = new TH1F("hAntilambdaResMass","#bar{#Lambda} mass (GeV) (resonance)",100,1.0,1.2);
  hAntilambdaResMass->SetYTitle("number of entries");
  hAntilambdaResMass->SetXTitle("Mass (GeV)");
  hK0sResMass = new TH1F("hK0sResMass","K^{0}_{s} mass (GeV) (resonance)",100,.4,.6);
  hK0sResMass->SetYTitle("number of entries");
  hK0sResMass->SetXTitle("Mass (GeV)");
  hPhiResMass = new TH1F("hPhiResMass","#phi mass (GeV)#",100,.9,1.1);
  hPhiResMass->SetYTitle("number of entries");
  hPhiResMass->SetXTitle("Mass (GeV)");
}
AnalysisMaker::AnalysisMaker(StMuDstMaker *maker, char *mydataset) : StMaker(){
  Initialize();
  muDstMaker = maker;
  IsStEvent = true;
  //set the StHighPtEventLoop's data set to the one passed
  dataset = mydataset;
  nevent = 1000000;
}

AnalysisMaker::AnalysisMaker(TTree *mytree, char *mydataset) : StMaker(){
  Initialize();
  tree = mytree;
  IsTEvent = true;
  //set the StHighPtEventLoop's data set to the one passed
  dataset = mydataset;
  event = new TEvent();   //object must be created before setting the branch address
  branch  = tree->GetBranch("Event");
  branch->SetAddress(&event);
  int bufsize = 64000/4;//back to what Jana had for buffer size
  //int bufsize = 640000;//this doesn't seem to matter much.  The limiting factor is still CPU
  branch->SetBasketSize(bufsize);//setting how much of the TTree can be read into memory
  v0s = new TV0();
  branchV0 = tree->GetBranch("V0");
  branchV0->SetAddress(&v0s);
  branchV0->SetBasketSize(bufsize);//setting how much of the TTree can be read into memory
  nevent = tree->GetEntries();
  eventnum = 0;
}

void AnalysisMaker::SetDefaultTriggers(){
  int *defaultTrigs = goodTriggers(dataset);
  for(int i = 0;i<10;i++){triggers[i] = defaultTrigs[i];}
}
void AnalysisMaker::SetNullTriggers(){
  useDefaultEventCuts = false;
  for(int i = 0;i<10;i++){triggers[i] = -1;}
}
bool AnalysisMaker::AddTrigger(int trig){
  for(int i = 0;i<10;i++){
    if(triggers[i] == -1){
      triggers[i] = trig;
      return true;
    }
  }
  return false;
}
void AnalysisMaker::SetNullPointers(){//Sets pointers I might not need to NULL
  //Things for reading a TTree
  tree = NULL;
  event = NULL;
  branch = NULL;
  v0s = NULL;
  branchV0 = NULL;
  treeIter = NULL;
  tree = NULL;
  muDstMaker = NULL;

  chTracks = NULL;
  nextStMuTrack = NULL;
  globTracks = NULL;
  nextGlobStMuTrack = NULL;

  v0Tracks = NULL;
  xiTracks = NULL;
  nextv0Track = NULL;
  nextXiTrack = NULL;
  nextTResonanceTrack = NULL;

  tIdentifiedTrack = NULL;
  tResonanceTrack = NULL;
  tTrack = NULL;
  //tV0 = NULL;
  tV0Track = NULL;
  tXiTrack = NULL;
  gStMuTrack = NULL;
  pStMuTrack = NULL;

  lambdas = NULL;
  antilambdas = NULL;
  K0s = NULL;
  lamIter = NULL;
  K0Iter = NULL;
  alamIter = NULL;

}


Int_t AnalysisMaker::Init() {
 return StMaker::Init();
}
//====================================    Make   =====================================================
Int_t AnalysisMaker::Make(){
  //cerr<<" anaMaker 187 ";
  //cout<<"event "<<nEvents;
  //if(event) cout<<"mult "<<event->GetMultiplicity()<<" trig "<<event->GetHeader()->GetTrigger1()<<" "<<event->GetHeader()->GetTrigger1()<<" "<<" vertexz "<<event->GetZVertex()<<endl;
  if(AcceptEvent()){
    //cout<<" event accepted "<<endl;
    //cerr<<" anaMaker 191 ";
    goodEvent = true;
    nGoodEvents++;
    //cerr<<" 192 ";
    if(IsStEvent){
      //if we have an StEvent we don't want to clear the TClonesArrays because they belong to MuDstMaker
      chTracks = muDstMaker->muDst()->primaryTracks();
      globTracks = muDstMaker->muDst()->globalTracks();
      v0Tracks = muDstMaker->muDst()->v0s();
      xiTracks = muDstMaker->muDst()->xis();
      //cout<<"xi candidates "<<xiTracks->GetEntries()<<endl;
      if(nextGlobStMuTrack) delete nextGlobStMuTrack;
      nextGlobStMuTrack = new TIter(globTracks);
      TResVarsMade=false;
    }
    if(IsTEvent){
      if(event->GetTIdentifiedTracks()->GetEntries()>0) chTracks = event->GetTIdentifiedTracks();
      else{chTracks = event->GetTracks();}
      //if(xiTracks) xiTracks->Clear();
      xiTracks = event->GetXiTracks();
      if(resTracks) resTracks = event->GetTResonanceTracks();
      else{resTracks=NULL;}
      delete nextTResonanceTrack;
      nextTResonanceTrack = new TIter(resTracks);
      if(v0Tracks) v0Tracks->Clear();
      v0Tracks = v0s->GetV0s();//this is already the right pointer
      lambdas = v0s->GetLambdas();
      antilambdas = v0s->GetAntiLambdas();
      K0s = v0s->GetK0short();
      if(lamIter) delete lamIter;
      lamIter = lambdas->MakeIterator();
      if(alamIter) delete alamIter;
      alamIter = antilambdas->MakeIterator();
      if(K0Iter) delete K0Iter;
      K0Iter = K0s->MakeIterator();
      readLambdas = false;
      readAntilambdas = false;
      readK0s = false;
      lamIter->Reset();
      alamIter->Reset();
      K0Iter->Reset();
    }
    if(nextStMuTrack) delete nextStMuTrack;
    if(nextv0Track) delete nextv0Track;
    if(nextXiTrack) delete nextXiTrack;
    nextStMuTrack = new TIter(chTracks);
    nextv0Track = new TIter(v0Tracks);
    nextXiTrack = xiTracks->MakeIterator();
    if(IsStEvent){
      //fill stV0MuDst with the next track
      stV0MuDst = (StV0MuDst*)nextv0Track->Next();
      stXiMuDst = (StXiMuDst*)nextXiTrack->Next();
    }
    if(IsTEvent){
      //testXiTrack = (TXiTrack*)nextXiTrack->Next();
    }
    v0Type = 1;
    //cerr<<" 25 ";
    if(makeTResTracks){
      InitTResVars();
      ResetTrackIterators();
    }
    //cerr<<" 254 ";

    int nXi = 0;
    ResetTrackIterators();
    //while(anaMaker->GetNextXiTrack()){
    while(GetNextXiTrack()){
      nXi++;
    }
    cout<<"nXi "<<nXi<<endl;
//     nXi = 0;
//     ResetTrackIterators();
//     //while(anaMaker->GetNextXiTrack()){
//     while(GetNextXiTrack()){
//       nXi++;
//     }
//     cout<<"nXi "<<nXi<<endl;

    //cerr<<" anaMaker 277 ";
  }
  else{
    nBadEvents++;
    goodEvent = false;
  }

  //cerr<<" anaMaker 285 ";
  nEvents++;
  if(goodEvent && IsTEvent){if(resTracks) resTracks->Clear();}
  //cerr<<" anaMaker 295 ";
  return kStOk;
}
//==============================  Event acceptance functions  ==============================
bool AnalysisMaker::AcceptEvent(){
  if(IsStEvent){
    //there is no elegant way to code this.  Evidently there is nothing returned by primaryVertex pre-CuCu200!
    if(dataset == CuCu200){
      if(muDstMaker->muDst() && muDstMaker->muDst()->primaryVertex() && muDstMaker->muDst()->primaryVertex()->ranking()){
	float ranking  = (float) (muDstMaker->muDst()->primaryVertex()->ranking());
	if(!(IsGoodVertexRank(dataset,ranking))) return false;//rejects fake vertices (currently only applicable to CuCu200)
      }
      else{
	if(!(muDstMaker->muDst())) {cerr<<"no muDst!"<<endl; return false;}
	else{
	  if(!(muDstMaker->muDst()->primaryVertex())) {cerr<<"no primary vertex!"<<endl;return false;}
	  else{
	    if(!(muDstMaker->muDst()->primaryVertex()->ranking())) {cerr<<"no ranking!"<<endl;return false;}
	  }
	}
      }
    }
    muEvent = muDstMaker->muDst()->event();
    //    vector<unsigned int> triggers = muEvent->triggerIdCollection().nominal().triggerIds();
//     vector<unsigned int>::iterator i;
//     i = triggers.begin();
//     int trig1 = *i;
//     i++;
//     int trig2 = *i;
    //if(muEvent) cout<<"mult "<<muEvent->refMult()<<" vertexz "<<muEvent->primaryVertexPosition().z()<<endl;
    
    if(useDefaultEventCuts) {
      SetDefaultTriggers();
      //reset triggers
      trigger[0]=-1;
      trigger[1]=-1;
      for(int i=0;i<10;i++){
	if(triggers[i]!=-1){
	  if( IsTrigger(dataset, muEvent, triggers[i]) ){
	    if(trigger[0]==-1){trigger[0]=triggers[i];}
	    else{if(trigger[1]==-1){trigger[1]=triggers[i];}}
	  }
	}
      }
      return IsGoodEvent(dataset,muEvent);
    }
    else{
      //reset triggers
      trigger[0]=-1;
      trigger[1]=-1;
      for(int i=0;i<10;i++){
	if(triggers[i]!=-1){
	  if( IsTrigger(dataset, muEvent, triggers[i]) ){
	    if(trigger[0]==-1){trigger[0]=triggers[i];}
	    else{if(trigger[1]==-1){trigger[1]=triggers[i];}}
	  }
	}
      }
      bool goodTrig = IsGoodTrigger(dataset, triggers, muEvent );
      bool goodVert = true;
      if(zvertex != -1000) goodVert = IsGoodVertex(dataset, zvertex, muEvent) ;
      bool goodRefM = IsGoodRefMult(dataset, muEvent);
      return goodTrig && goodVert && goodRefM;
    }
  }
  if(IsTEvent){
    if(eventnum<nevent){
      tree->GetEvent(eventnum);  
      eventnum++;
      if(useDefaultEventCuts){
	SetDefaultTriggers();
	//reset triggers
	trigger[0]=-1;
	trigger[1]=-1;
	for(int i=0;i<10;i++){
	  if(triggers[i]!=-1){
	    if( IsTrigger(dataset, event, triggers[i]) ){
	      if(trigger[0]==-1){trigger[0]=triggers[i];}
	      else{if(trigger[1]==-1){trigger[1]=triggers[i];}}
	    }
	  }
	}
	return IsGoodEvent(dataset,event);
      }
      else{
	//reset triggers
	trigger[0]=-1;
	trigger[1]=-1;
	for(int i=0;i<10;i++){
	  if(triggers[i]!=-1){
	    if( IsTrigger(dataset, muEvent, triggers[i]) ){
	      if(trigger[0]==-1){trigger[0]=triggers[i];}
	      else{if(trigger[1]==-1){trigger[1]=triggers[i];}}
	    }
	  }
	}
	bool goodTrig = IsGoodTrigger(dataset, triggers, event );
	bool goodVert = true;
	if(zvertex != -1000) goodVert = IsGoodVertex(dataset, zvertex, event) ;
	bool goodRefM = IsGoodRefMult(dataset, event);
	return goodTrig && goodVert && goodRefM;
      }
    }
  }
  return false;
  //right now I have no reason not to use a default cut.  Currently I check multiplicity, vertex, and triggers.  Presumably trigger cuts might be of interest but not right now.
}
Int_t AnalysisMaker::Finish(){
  cout<<"Analyzed "<<nGoodEvents+nBadEvents<<" events.  "<<nGoodEvents<<" good "<<nBadEvents<<" bad"<<endl;
  return kStOk;
}

StMuEvent* AnalysisMaker::GetStMuEvent(){
  if(goodEvent)  return muEvent;
  else{
    return NULL;
  }
}
TEvent* AnalysisMaker::GetTEvent(){
  if(goodEvent){
    return event;
  }  else{
    return NULL;
  }
}
//==========================  Charged track functions  =================================
bool AnalysisMaker::GetNextChargedTrack(){
  if(goodEvent){
    if(IsTEvent){
      TTrack *myTTrack = (TTrack*)nextStMuTrack->Next();
      while(!AcceptTrack(myTTrack)){//keeps going until it accepts a track
	delete myTTrack;
	myTTrack = (TTrack*)nextStMuTrack->Next();
	//Get the next track but if there are no tracks return false
	if(!(myTTrack ) ){return false;}
      }
      //Make a TTrack
      if(MakeIdentifiedTrack){MakeTIdentifiedTrack(myTTrack);}//fix
      else{MakeTTrack(myTTrack);}//fix
      //Then return true because the next track was stored successfully as a TTrack
      //now the function GetTTrack returns the good TTrack
      return true;
    }
    if(IsStEvent){
      StMuTrack *stMuTrack = NULL;
      while(!AcceptTrack(stMuTrack)){//keeps going until it accepts a track
	//Get the next track but if there are no tracks return false
	if( !(nextStMuTrack) ) {cerr<<"no iterator"<<endl; return false;}
	stMuTrack = (StMuTrack*)nextStMuTrack->Next();
	if(   !(stMuTrack)   ){
	  return false;
	}
      }
      //Make a TTrack
      if(MakeIdentifiedTrack){MakeTIdentifiedTrack(stMuTrack);}
      MakeTTrack(stMuTrack);
      //Then return true because the next track was stored successfully as a TTrack
      //now the function GetTTrack returns the good TTrack
      return true;
    }
  }
  return false;
}
bool AnalysisMaker::AcceptTrack(TTrack *track){
  return IsGoodTrack(dataset, track, ptMin, ptMax, eta, dca, nHitsFit);
}
bool AnalysisMaker::AcceptTrack(StMuTrack *track){
  return IsGoodTrack(dataset, track, ptMin, ptMax, eta, dca, nHitsFit);
}


void AnalysisMaker::MakeTTrack(TTrack *track){
  delete tTrack;
    //For this function all I have done is load the TTrack which already existed into memory by a call to the iterator on the TClonesArray.  So I don't actually want to delete this track, just move the pointer to TTrack to this
  tTrack = track;
}
void AnalysisMaker::MakeTTrack(StMuTrack *stmutrack){
    //for this function I actually make a new TTrack so I need to delete the old one before making a new TTrack
  delete tTrack;
  tTrack = GetTTrack(dataset, stmutrack);
}
//==========================  TIdentifiedTrack functions  =================================
void AnalysisMaker::MakeTIdentifiedTrack(StMuTrack *stmutrack){
  delete tIdentifiedTrack;
  tIdentifiedTrack = GetTIdentifiedTrack(dataset, stmutrack);
}
void AnalysisMaker::MakeTIdentifiedTrack(TTrack *track){
  if(track->InheritsFrom("TIdentifiedTrack")){
    if(IsStEvent) delete tIdentifiedTrack;//this line doesn't actually do anything
    tIdentifiedTrack = (TIdentifiedTrack*) track;
  }
  else{tIdentifiedTrack = NULL;}
}
//================================  V0 functions  ======================================
bool AnalysisMaker::GetNextV0Track(){
  if(goodEvent){
    if(IsStEvent){
      //AcceptV0Track asks if the current track is a good track of type = v0Type
      //whatever the answer is, it increases v0Type by 1
      //AcceptV0Track never resets v0Type to 1
      while(!AcceptV0Track(stV0MuDst)){//keeps going until it accepts a track
	//If the track wasn't accepted it might be because there was no track, in which case we're done with this event
	if(!stV0MuDst){
	  v0Type =1;//The next track which is read (which will be the first track in the next event) should be checked to see if it's a lambda
	  return false;
	}
	//If the track existed but it wasn't good and it's already been checked for every v0 type move to the next track
	if(v0Type>=3) {
	  stV0MuDst = (StV0MuDst*)nextv0Track->Next();//move to the next track if the v0Type isn't good
	  v0Type=1;//after moving to the next track the first thing to do is check if it's a lambda
	}
	else{
	  v0Type++;
	}//if it's not accepted if it hasn't been checked for everything, check the next type
      }
      MakeTV0Track(stV0MuDst);
      //If the track was accepted, it still needs to be checked for other things if it ain't good
      if(v0Type>=3) {
	stV0MuDst = (StV0MuDst*)nextv0Track->Next();//move to the next track if the v0Type isn't good
	v0Type=1;//after moving to the next track the first thing to do is check if it's a lambda
      }
      else{
	  v0Type++;
      }//if it hasn't been checked for everything, check the next type
      //Then return true because the next track was stored successfully as a TTrack
      //now the function GetTTrack returns the good TTrack
      //cout<<"anaMaker pt "<<tV0Track->GetPt()<<" type "<<tV0Track->GetType()<<endl;
      return true;
    }
    if(IsTEvent){
      //TV0Track *myTV0Track = (TV0Track*)nextv0Track->Next();
      //cout<<"getting next V0 track 473 ";
      TV0Track *myTV0Track = GetNextV0();
      if(myTV0Track){
	while(!AcceptV0Track(myTV0Track)){//keeps going until it accepts a track
	  //Get the next track but if there are no tracks return false
	  //cout<<" bad ";
	  if(IsStEvent) delete myTV0Track;
	  //myTV0Track = (TV0Track*)nextv0Track->Next();
	  myTV0Track = GetNextV0();
	  if(!myTV0Track){
	    //cout<<"out of tracks"<<endl;
	    return false;
	  }
	}
      }
      else{return false;}
      //Make a TV0Track
      MakeTV0Track(myTV0Track);
      //Then return true because the next track was stored successfully as a TTrack
      //now the function GetTTrack returns the good TTrack
      return true;
    }
  }
  return false;
}

bool AnalysisMaker::AcceptV0Track(TV0Track *track){
  if(UseCustomCuts){ 
    //check each of the three types
    if(IsGoodV0Track(dataset,track,1,decayLengthLam,dcaV0ToPVLam,dcaDaughtersLam,dcaNegToPVLam,dcaPosToPVLam,nHitsNegLam,nHitsPosLam,v0ptmin,v0ptmax,v0eta)){return true;}
    if(IsGoodV0Track(dataset,track,2,decayLengthAlam,dcaV0ToPVAlam,dcaDaughtersAlam,dcaNegToPVAlam,dcaPosToPVAlam,nHitsNegAlam,nHitsPosAlam,v0ptmin,v0ptmax,v0eta)){return true;}
    if(IsGoodV0Track(dataset,track,3,decayLengthK0,dcaV0ToPVK0,dcaDaughtersK0,dcaNegToPVK0,dcaPosToPVK0,nHitsNegK0,nHitsPosK0,v0ptmin,v0ptmax,v0eta)){return true;}
    return false;
  }
  if(UseLoosestV0Cuts) return IsGoodV0Track(dataset, track);
  //cout<<" 508 ";
  if(UseDefaultV0CutsTree) return IsGoodV0Track(dataset,track,"TTree");
  //cout<<" 510 ";
  if(UseDefaultV0CutsCorrelation) return IsGoodV0Track(dataset,track,"Correlation");
  //cout<<" 512 ";
  if(UseDefaultV0CutsSpectra) return IsGoodV0Track(dataset,track,"Spectra");
  
  return false;
}
bool AnalysisMaker::AcceptV0Track(StV0MuDst *track){
  if(v0Type>3 || !track) {
    return false;//If the type is not a valid type or the track doesn't exist, you can't check it
  }
  if(track){
    if(UseCustomCuts){ 
      if(IsGoodV0Track(dataset,track,v0Type,decayLengthLam,dcaV0ToPVLam,dcaDaughtersLam,dcaNegToPVLam,dcaPosToPVLam,nHitsNegLam,nHitsPosLam,v0ptmin,v0ptmax,v0eta)){
	return true;
      }
      return false;
    }
    if(UseLoosestV0Cuts) {
      return IsGoodV0Track(dataset, track, v0Type);
    }
    if(UseDefaultV0CutsTree) {
      return IsGoodV0Track(dataset,track,v0Type,"TTree");
    }
    if(UseDefaultV0CutsCorrelation) {
//       if(IsGoodV0Track(dataset,track,v0Type,"Correlation")){
// 	cout<<"hi"<<endl;
// 	return true;
//       }
//       else{
// 	cout<<"burp"<<endl;
// 	return false;
//       }
      return IsGoodV0Track(dataset,track,v0Type,"Correlation");
    }
    if(UseDefaultV0CutsSpectra) {
      return IsGoodV0Track(dataset,track,v0Type,"Spectra");
    }
  }
  return false;
}


void AnalysisMaker::MakeTV0Track(StV0MuDst *stmutrack){
  delete tV0Track;
  tV0Track = GetTTrack(dataset, stmutrack, v0Type);
  if(tV0Track){
    //filling global variables
    StMuTrack *PosTrack = GetGlobalStMuTrackN(tV0Track->GetPosDaughterTrackId());
    StMuTrack *NegTrack = GetGlobalStMuTrackN(tV0Track->GetNegDaughterTrackId());
    if(PosTrack &&NegTrack){
      GetTTrack(tV0Track,PosTrack,NegTrack);
    }
  }
}
void AnalysisMaker::MakeTV0Track(TV0Track *track){
    //For this function all I have done is load the TTrack which already existed into memory by a call to the iterator on the TClonesArray.  So I don't actually want to delete this track, just move the pointer to TTrack to this
  //if(IsStEvent) delete tV0Track;
  tV0Track = track;
}


void AnalysisMaker::SetV0CutsToDataSetTreeDefaults(){
  UseDefaultV0CutsTree=true;
  UseDefaultV0CutsCorrelation=false;
  UseDefaultV0CutsSpectra=false;
  UseLoosestV0Cuts = false;
  decayLengthLam = GetDefaultV0Cut(dataset, "TTree","DecayLength",1);
  dcaV0ToPVLam = GetDefaultV0Cut(dataset, "TTree","DcaV0ToPV",1);
  dcaDaughtersLam = GetDefaultV0Cut(dataset, "TTree","DcaDaughters",1);
  dcaNegToPVLam = GetDefaultV0Cut(dataset, "TTree","DcaNegToPV",1);
  dcaPosToPVLam = GetDefaultV0Cut(dataset, "TTree","DcaPosToPV",1);
  nHitsPosLam = (int) GetDefaultV0Cut(dataset, "TTree","NHitsPos",1);
  nHitsNegLam = (int) GetDefaultV0Cut(dataset, "TTree","NHitsNeg",1);
  decayLengthAlam = GetDefaultV0Cut(dataset, "TTree","DecayLength",2);
  dcaV0ToPVAlam = GetDefaultV0Cut(dataset, "TTree","DcaV0ToPV",2);
  dcaDaughtersAlam = GetDefaultV0Cut(dataset, "TTree","DcaDaughters",2);
  dcaNegToPVAlam = GetDefaultV0Cut(dataset, "TTree","DcaNegToPV",2);
  dcaPosToPVAlam = GetDefaultV0Cut(dataset, "TTree","DcaPosToPV",2);
  nHitsPosAlam = (int) GetDefaultV0Cut(dataset, "TTree","NHitsPos",2);
  nHitsNegAlam = (int) GetDefaultV0Cut(dataset, "TTree","NHitsNeg",2);
  decayLengthK0 = GetDefaultV0Cut(dataset, "TTree","DecayLength",3);
  dcaV0ToPVK0 = GetDefaultV0Cut(dataset, "TTree","DcaV0ToPV",3);
  dcaDaughtersK0 = GetDefaultV0Cut(dataset, "TTree","DcaDaughters",3);
  dcaNegToPVK0 = GetDefaultV0Cut(dataset, "TTree","DcaNegToPV",3);
  dcaPosToPVK0 = GetDefaultV0Cut(dataset, "TTree","DcaPosToPV",3);
  nHitsPosK0 = (int) GetDefaultV0Cut(dataset, "TTree","NHitsPos",3);
  nHitsNegK0 = (int) GetDefaultV0Cut(dataset, "TTree","NHitsNeg",3);
}

void AnalysisMaker::SetV0CutsToDataSetCorrelationDefaults(){
  UseDefaultV0CutsTree=false;
  UseDefaultV0CutsCorrelation=true;
  UseDefaultV0CutsSpectra=false;
  UseLoosestV0Cuts = false;
  decayLengthLam = GetDefaultV0Cut(dataset, "Correlation","DecayLength",1);
  dcaV0ToPVLam = GetDefaultV0Cut(dataset, "Correlation","DcaV0ToPV",1);
  dcaDaughtersLam = GetDefaultV0Cut(dataset, "Correlation","DcaDaughters",1);
  dcaNegToPVLam = GetDefaultV0Cut(dataset, "Correlation","DcaNegToPV",1);
  dcaPosToPVLam = GetDefaultV0Cut(dataset, "Correlation","DcaPosToPV",1);
  nHitsPosLam = (int) GetDefaultV0Cut(dataset, "Correlation","NHitsPos",1);
  nHitsNegLam = (int) GetDefaultV0Cut(dataset, "Correlation","NHitsNeg",1);
  decayLengthAlam = GetDefaultV0Cut(dataset, "Correlation","DecayLength",2);
  dcaV0ToPVAlam = GetDefaultV0Cut(dataset, "Correlation","DcaV0ToPV",2);
  dcaDaughtersAlam = GetDefaultV0Cut(dataset, "Correlation","DcaDaughters",2);
  dcaNegToPVAlam = GetDefaultV0Cut(dataset, "Correlation","DcaNegToPV",2);
  dcaPosToPVAlam = GetDefaultV0Cut(dataset, "Correlation","DcaPosToPV",2);
  nHitsPosAlam = (int) GetDefaultV0Cut(dataset, "Correlation","NHitsPos",2);
  nHitsNegAlam = (int) GetDefaultV0Cut(dataset, "Correlation","NHitsNeg",2);
  decayLengthK0 = GetDefaultV0Cut(dataset, "Correlation","DecayLength",3);
  dcaV0ToPVK0 = GetDefaultV0Cut(dataset, "Correlation","DcaV0ToPV",3);
  dcaDaughtersK0 = GetDefaultV0Cut(dataset, "Correlation","DcaDaughters",3);
  dcaNegToPVK0 = GetDefaultV0Cut(dataset, "Correlation","DcaNegToPV",3);
  dcaPosToPVK0 = GetDefaultV0Cut(dataset, "Correlation","DcaPosToPV",3);
  nHitsPosK0 = (int) GetDefaultV0Cut(dataset, "Correlation","NHitsPos",3);
  nHitsNegK0 = (int) GetDefaultV0Cut(dataset, "Correlation","NHitsNeg",3);
}

void AnalysisMaker::SetV0CutsToDataSetSpectraDefaults(){
  UseDefaultV0CutsTree=false;
  UseDefaultV0CutsCorrelation=false;
  UseDefaultV0CutsSpectra=true;
  UseLoosestV0Cuts = false;
  decayLengthLam = GetDefaultV0Cut(dataset, "Spectra","DecayLength",1);
  dcaV0ToPVLam = GetDefaultV0Cut(dataset, "Spectra","DcaV0ToPV",1);
  dcaDaughtersLam = GetDefaultV0Cut(dataset, "Spectra","DcaDaughters",1);
  dcaNegToPVLam = GetDefaultV0Cut(dataset, "Spectra","DcaNegToPV",1);
  dcaPosToPVLam = GetDefaultV0Cut(dataset, "Spectra","DcaPosToPV",1);
  nHitsPosLam = (int) GetDefaultV0Cut(dataset, "Spectra","NHitsPos",1);
  nHitsNegLam = (int) GetDefaultV0Cut(dataset, "Spectra","NHitsNeg",1);
  decayLengthAlam = GetDefaultV0Cut(dataset, "Spectra","DecayLength",2);
  dcaV0ToPVAlam = GetDefaultV0Cut(dataset, "Spectra","DcaV0ToPV",2);
  dcaDaughtersAlam = GetDefaultV0Cut(dataset, "Spectra","DcaDaughters",2);
  dcaNegToPVAlam = GetDefaultV0Cut(dataset, "Spectra","DcaNegToPV",2);
  dcaPosToPVAlam = GetDefaultV0Cut(dataset, "Spectra","DcaPosToPV",2);
  nHitsPosAlam = (int) GetDefaultV0Cut(dataset, "Spectra","NHitsPos",2);
  nHitsNegAlam = (int) GetDefaultV0Cut(dataset, "Spectra","NHitsNeg",2);
  decayLengthK0 = GetDefaultV0Cut(dataset, "Spectra","DecayLength",3);
  dcaV0ToPVK0 = GetDefaultV0Cut(dataset, "Spectra","DcaV0ToPV",3);
  dcaDaughtersK0 = GetDefaultV0Cut(dataset, "Spectra","DcaDaughters",3);
  dcaNegToPVK0 = GetDefaultV0Cut(dataset, "Spectra","DcaNegToPV",3);
  dcaPosToPVK0 = GetDefaultV0Cut(dataset, "Spectra","DcaPosToPV",3);
  nHitsPosK0 = (int) GetDefaultV0Cut(dataset, "Spectra","NHitsPos",3);
  nHitsNegK0 = (int) GetDefaultV0Cut(dataset, "Spectra","NHitsNeg",3);
}
void AnalysisMaker::SetV0CutsToDataSetLoosest(){
  UseLoosestV0Cuts = true;
  UseDefaultV0CutsTree=false;
  UseDefaultV0CutsCorrelation=false;
  UseDefaultV0CutsSpectra=false;
}
//===================================  Housekeeping  =================================================
void AnalysisMaker::ResetTrackIterators(){
  if(nextXiTrack){
    nextXiTrack->Reset();
    if(IsStEvent) stXiMuDst = (StXiMuDst*)nextXiTrack->Next();
    //if(IsTEvent) testXiTrack = (TXiTrack*)nextXiTrack->Next();
  }
  if(nextStMuTrack){
    nextStMuTrack->Reset();
  }
  if(nextGlobStMuTrack){
    nextGlobStMuTrack->Reset();
  }
  if(nextv0Track){
    nextv0Track->Reset();
    //now because of the complicated way I had to check the V0 tracks I have to fill stV0MuDst
    stV0MuDst = (StV0MuDst*)nextv0Track->Next();
  }
  if(nextTResonanceTrack){
    nextTResonanceTrack->Reset();
  }
  if(lamIter) lamIter->Reset();
  if(alamIter) alamIter->Reset();
  if(K0Iter) K0Iter->Reset();
}

int AnalysisMaker::EventId(){
  if(IsTEvent){
    return GetEventID(dataset, event);
  }
  if(IsStEvent){
    return GetEventID(dataset, muEvent);
  }
  return -1;
}
int AnalysisMaker::RunId(){
  if(IsTEvent){
    return GetRunID(dataset, event);
  }
  if(IsStEvent){
    return GetRunID(dataset, muEvent);
  }
  return -1;
}

float AnalysisMaker::VertexZ(){
  if(IsTEvent){
    return GetVertexZ(dataset, event);
  }
  if(IsStEvent){
    return GetVertexZ(dataset, muEvent);
  }
  return -1;
}
int AnalysisMaker::RefMult(){
  if(IsTEvent){
    return GetRefMult(dataset, event);
  }
  if(IsStEvent){
    return GetRefMult(dataset, muEvent);
  }
  return -1;
}
//===============================  TResonance functions  ==============================================
void AnalysisMaker::InitTResVars(){
  ResetTrackIterators();
  if(IsStEvent){
  
    lamResDone = false;
    alamResDone = false;
    k0ResDone = false;
    phiResDone = false;
    //Clear the TLists from the last time
    piPlus.Clear();
    piMinus.Clear();
    proton.Clear();
    pbar.Clear();
    kPlus.Clear();
    kMinus.Clear();
    //Global tracks for V0s, which means pions and protons
    StMuTrack *myTrack = (StMuTrack*) nextGlobStMuTrack->Next();
    while( myTrack ){
      if( IsGoodTrack(dataset, myTrack, 0.0, ptMax, eta, dca, nHitsFit)  ){//minimum pt is 0 because I don't want to bias results
	if(myTrack->nSigmaProton() <=2.0){
	  if(myTrack->charge() < 0){ pbar.Add(myTrack);}
	  if(myTrack->charge() > 0){ proton.Add(myTrack);}
	}
	if(myTrack->nSigmaPion() <=2.0){
	  if(myTrack->charge() < 0){ piMinus.Add(myTrack);}
	  if(myTrack->charge() > 0){ piPlus.Add(myTrack);}
	}
      }
      myTrack = (StMuTrack*) nextGlobStMuTrack->Next();
    }
    //primaries for Kaons (for the phi)
    myTrack = (StMuTrack*) nextStMuTrack->Next();
    while( myTrack ){
      if( IsGoodTrack(dataset, myTrack, 0.0, ptMax, eta, dca, nHitsFit)  ){//minimum pt is 0 because I don't want to bias results
	if(myTrack->nSigmaKaon() <=2.0){
	  if(myTrack->charge() < 0){ kMinus.Add(myTrack);}
	  if(myTrack->charge() > 0){ kPlus.Add(myTrack);}
	}
      }
      myTrack = (StMuTrack*) nextStMuTrack->Next();
    }
    piPlusIt = piPlus.MakeIterator();
    piMinusIt = piMinus.MakeIterator();
    kPlusIt = kPlus.MakeIterator();
    kMinusIt = kMinus.MakeIterator();
    protonIt = proton.MakeIterator();
    pbarIt = pbar.MakeIterator();
    posTrack = NULL;
    negTrack = NULL;
    ResetTrackIterators();
  }
}


bool AnalysisMaker::GetNextResonanceTrack(){
  if(!TResVarsMade){
    InitTResVars();
    TResVarsMade = true;
  }
  if(goodEvent){
    if(IsStEvent){
      //antilambda (type = 15)
      //cerr<<" 819 ";
      if(!alamResDone){
	//cerr<<" 821 ";
	negTrack = (StMuTrack*)pbarIt->Next();
	posTrack = (StMuTrack*)piPlusIt->Next();
	//cerr<<" 824 ";
	while(posTrack){
	  while(negTrack){
	    //cerr<<" 827 ";
	    if( GetTResonancePt(posTrack,negTrack) >=lowResPt ){//is the pt in the trigger range?
	      //cerr<<" 829 ";
	      float mass = GetTResonanceMass(posTrack,negTrack,15);
	      if( mass > 1.0 && mass < 1.2){
		//cerr<<" 832 ";
		hLambdaResMass->Fill(mass);
		if( mass > 1.08 && mass < 1.15){
		  //cerr<<" 835 ";
		  delete tResonanceTrack;
		  //cerr<<" 837 ";
		  tResonanceTrack = GetTTrack(dataset, posTrack, negTrack, 15);
		  return true;
		}
	      }
	    }
	    negTrack = (StMuTrack*)pbarIt->Next();
	  }
	  posTrack = (StMuTrack*)piPlusIt->Next();
	}
	alamResDone = true;
      }
      if(!lamResDone){
	//lambda (type = 14)
	negTrack = (StMuTrack*)protonIt->Next();
	posTrack = (StMuTrack*)piMinusIt->Next();
	while(posTrack){
	  while(negTrack){
	    if( GetTResonancePt(posTrack,negTrack) >=lowResPt ){//is the pt in the trigger range?
	      float mass = GetTResonanceMass(posTrack,negTrack,14);
	      if( mass > 1.0 && mass < 1.2){
		hAntilambdaResMass->Fill(mass);
		if( mass > 1.08 && mass < 1.15){
		  delete tResonanceTrack;
		  tResonanceTrack = GetTTrack(dataset, posTrack, negTrack, 14);
		  return true;
		}
	      }
	    }
	    negTrack = (StMuTrack*)protonIt->Next();
	  }
	  posTrack = (StMuTrack*)piMinusIt->Next();
	}
	lamResDone = true;
	piPlusIt->Reset();
	piMinusIt->Reset();
      }
      if(!k0ResDone){
	//K0s (type = 16)
	negTrack = (StMuTrack*)piMinusIt->Next();
	posTrack = (StMuTrack*)piPlusIt->Next();
	while(posTrack){
	  while(negTrack){
	    if( GetTResonancePt(posTrack,negTrack) >=lowResPt ){//is the pt in the trigger range?
	      float mass = GetTResonanceMass(posTrack,negTrack,16);
	      if( mass > .4 && mass < .6){
		hK0sResMass->Fill(mass);
		if( mass > .44 && mass < .56){
		  delete tResonanceTrack;
		  tResonanceTrack = GetTTrack(dataset, posTrack, negTrack, 16);
		  return true;
		}
	      }
	    }
	    negTrack = (StMuTrack*)piMinusIt->Next();
	  }
	  posTrack = (StMuTrack*)piPlusIt->Next();
	}
	k0ResDone = true;
      }
      //cerr<<" 903 ";
      if(!phiResDone){
	//Phi (type = 17)
	negTrack = (StMuTrack*)kMinusIt->Next();
	posTrack = (StMuTrack*)kPlusIt->Next();
	while(posTrack){
	  while(negTrack){
	    if( GetTResonancePt(posTrack,negTrack) >=lowResPt ){//is the pt in the trigger range?
	      float mass = GetTResonanceMass(posTrack,negTrack,17);
	      if( mass > .9 && mass < 1.1){
		hPhiResMass->Fill(mass);
		if( mass > .98 && mass < 1.05){
		  delete tResonanceTrack;
		  tResonanceTrack = GetTTrack(dataset, posTrack, negTrack, 17);
		  return true;
		}
	      }
	    }
	    negTrack = (StMuTrack*)kMinusIt->Next();
	  }
	  posTrack = (StMuTrack*)kPlusIt->Next();
	}	
	phiResDone = true;
      }
    }
    if(IsTEvent){//this just loops over the TResonance tracks in the TTree with no cuts
      tResonanceTrack = (TResonanceTrack*)nextTResonanceTrack->Next();
      if(tResonanceTrack) return true;
    }
  }
  return false;
}
//====================  Xi functions  ==============================
bool AnalysisMaker::GetNextXiTrack(){
  //cerr<<" 938 ";
  if(goodEvent){
    if(IsStEvent){
      //AcceptXiTrack asks if the current track is a good track of type = xiType [xiType 0 = xi, 1 = omega, 2 = anti-xi, 3 = anti omega] had to deviate from part type numbering to make it easy to increment because I missed particles during my numbering scheme
      //whatever the answer is, it increases xiType by 1
      //AcceptXiTrack never resets xiType to 0
      //cerr<<" 938 ";
      while(!AcceptXiTrack(stXiMuDst)){//keeps going until it accepts a track
	//If the track wasn't accepted it might be because there was no track, in which case we're done with this event
	if(!stXiMuDst){
	  xiType =0;//The next track which is read (which will be the first track in the next event) should be checked to see if it's a lambda
	  return false;
	}
	//If the track existed but it wasn't good and it's already been checked for every v0 type move to the next track
	if(xiType>=3) {
	  stXiMuDst = (StXiMuDst*)nextXiTrack->Next();//move to the next track if the v0Type isn't good
	  xiType=0;//after moving to the next track the first thing to do is check if it's a lambda
	}
	else{
	  xiType++;
	}//if it's not accepted if it hasn't been checked for everything, check the next type
      }
      //cerr<<" 960 ";

      MakeTXiTrack(stXiMuDst);
      //cerr<<" 963 ";
      //If the track was accepted, it still needs to be checked for other things if it ain't good
      if(xiType>=3) {
	stXiMuDst = (StXiMuDst*)nextXiTrack->Next();//move to the next track if the xiType isn't good
	xiType=0;//after moving to the next track the first thing to do is check if it's a lambda
      }
      else{
	  xiType++;
      }//if it hasn't been checked for everything, check the next type
      //Then return true because the next track was stored successfully as a TTrack
      //now the function GetTTrack returns the good TTrack
      //cerr<<" 973 ";
      return true;
    }
    if(IsTEvent){
      //cout<<" anamaker 939 ";
      //cout<<"xi candidates "<<xiTracks->GetEntries()<<" "<<event->GetXiTracks()->GetEntries()<<endl;    
      testXiTrack = (TXiTrack*)nextXiTrack->Next();
      //TXiTrack *myTXiTrack = (TXiTrack*)nextXiTrack->Next();
      //if(!testXiTrack) cout<<" no track "<<endl;
      if(testXiTrack){
	while(!AcceptXiTrack(testXiTrack)){//keeps going until it accepts a track
	  //Get the next track but if there are no tracks return false
	  testXiTrack = (TXiTrack*)nextXiTrack->Next();
	  //cout<<" 945 ";
	  if(!(testXiTrack)){
	    return false;
	  }
	}
      }
      else{return false;}
      //Make a TXiTrack
      MakeTXiTrack(testXiTrack);
      //Then return true because the next track was stored successfully as a TTrack
      //now the function GetTTrack returns the good TTrack
      return true;
    }
  }
  return false;
}

bool AnalysisMaker::AcceptXiTrack(TXiTrack *track){
  //for now we will just use loosest Xi cuts and not have a gazillion options for Xis.  In principle I'm the only one using them
  return IsGoodXiTrack(dataset, track, track->GetType(), "TTree",xiptmin, xiptmax,xieta);
  return false;
}
bool AnalysisMaker::AcceptXiTrack(StXiMuDst *track){
  if(xiType>3 || !track) {
    return false;//If the type is not a valid type or the track doesn't exist, you can't check it
  }
  if(track){
    int realType = -1;
    if(xiType==0) realType = 4;
    if(xiType==1) realType = 5;
    if(xiType==2) realType = 18;
    if(xiType==3) realType = 19;
    if(realType==-1) return false;
    //using loose cuts (which means TTree cuts right now)
    return IsGoodXiTrack(dataset,track,realType,"TTree",xiptmin, xiptmax,xieta);
  }
  return false;
}


void AnalysisMaker::MakeTXiTrack(StXiMuDst *stmutrack){
  int realType = -1;
  if(xiType==0) realType = 4;
  if(xiType==1) realType = 5;
  if(xiType==2) realType = 18;
  if(xiType==3) realType = 19;
  if(realType==-1) return;
  delete tXiTrack;
  tXiTrack = GetTTrack(dataset, stmutrack, realType);
  if(tXiTrack){
    //cerr<<" 1037 ";
    StMuTrack *PosTrack = GetGlobalStMuTrackN(tXiTrack->GetPosDaughterTrackId());
    //cerr<<" 1039 ";
    StMuTrack *NegTrack = GetGlobalStMuTrackN(tXiTrack->GetNegDaughterTrackId());
    //cerr<<" 1041 ";
    StMuTrack *BachTrack = GetGlobalStMuTrackN(tXiTrack->GetBachDaughterTrackId());
    //cerr<<" 1043 ";
    if(PosTrack && NegTrack && BachTrack){
      GetTTrack(tXiTrack,PosTrack,NegTrack,BachTrack);
    }
  }
  return;
}
void AnalysisMaker::MakeTXiTrack(TXiTrack *track){
  //For this function all I have done is load the TTrack which already existed into memory by a call to the iterator on the TClonesArray.  So I don't actually want to delete this track, just move the pointer to TTrack to this
  tXiTrack = track;
}

bool AnalysisMaker::GetNextPrimaryStMuTrack(){
  pStMuTrack = (StMuTrack*) nextStMuTrack->Next();
  if(pStMuTrack) return true;
  return false;
}
bool AnalysisMaker::GetNextGlobalStMuTrack(){
  if(nextGlobStMuTrack){
    gStMuTrack = (StMuTrack*) nextGlobStMuTrack->Next();
    if(gStMuTrack) return true;
  }
  return false;
}

StMuTrack *AnalysisMaker::GetGlobalStMuTrackN(int N){
  if(IsStEvent && globTracks){//if this is an StEvent and the array of global tracks has been retrieved
    StMuTrack *track = (StMuTrack*) (*globTracks)[N];
    int entryNum = N;
    int numIterations = 0;
    int lastEntryNum[2];
    //cerr<<" 1074 "<<endl;
    //cerr<<" N "<<N;
    while(track->id() != N){
      //the Nth entry in the array will be more likely to have an id higher than the one desired than lower on the first iteration
      //cerr<<" id "<<track->id();
      lastEntryNum[1]=lastEntryNum[0];
      lastEntryNum[0] = entryNum;
      entryNum += N-track->id();
      //cerr<<" 1080 ";
      if(entryNum <0) entryNum = 0;
      track = (StMuTrack*) (*globTracks)[entryNum];
      numIterations++;
      if(lastEntryNum[1]==entryNum){
	int oldEntryNum = entryNum;
	//if this happens we try somewhere halfway in between lastEntryNum[0] and lastEntryNum[1]
	if(lastEntryNum[0]>lastEntryNum[1]) entryNum = lastEntryNum[1] + (lastEntryNum[0]-lastEntryNum[1])/2;
	if(lastEntryNum[1]>lastEntryNum[0]) entryNum = lastEntryNum[0] + (lastEntryNum[1]-lastEntryNum[0])/2;
	lastEntryNum[1]=lastEntryNum[0];
	lastEntryNum[0] = oldEntryNum;
	track = (StMuTrack*) (*globTracks)[entryNum];
	numIterations++;
      }
      if(numIterations>50){//just start stepping through tracks
	//cerr<<" 1095 "<<endl;
	entryNum = 0;//some ids are negative so if we don't find the track fast we have to stop being smart and do this in a brute force method
	while(track->id()!= N){
	  //cerr<<" id "<<track->id();
	  if(track->id() < N){
	    entryNum++;
	    numIterations++;
	    track = (StMuTrack*) (*globTracks)[entryNum];
	    if(!track) return NULL;//stops at the end of all tracks
	    if(track->id()==N) {
	      return track;
	    }
	  }
	  else{//if N< track->id() so we are too far ahead so we step backwards
	    entryNum--;
	    numIterations++;
	    track = (StMuTrack*) (*globTracks)[entryNum];
	    if(!track) return NULL;//stops at the end of all tracks
	    if(track->id()==N) {
	      return track;
	    }
	  }
	}
	return track;
      }
    }
    return track;
  }
  return NULL;
}
TV0Track* AnalysisMaker::GetNextV0(){
  //cout<<" 1044 "<<endl;
  //if(!readLambdas){
  TV0Track *track = lamIter->Next();
  if(track) {
    //cout<<"Ana candidate type "<<track->GetType()<<" pt "<<track->GetPt()<<endl;
    //cout<<" lam "<<endl;
    return track;
  }
  //     if(!track){
  //       readLambdas = true;
  //       lamIter->Reset();
  //       alamIter->Reset();
  //       K0Iter->Reset();
  //     }
  //   }
  //   if(!readAntilambdas){
  track = alamIter->Next();
  //track = alamIter->Next();
  if(track){
    //cout<<" alam "<<endl;
    //cout<<"Ana candidate type "<<track->GetType()<<" pt "<<track->GetPt()<<endl;
    return track;
  }
  //     if(!track){
  //       readAntilambdas = true;
  //       lamIter->Reset();
  //       alamIter->Reset();
  //       K0Iter->Reset();
  //     }
  //   }
  //   if(!readK0s){
  track = K0Iter->Next();
  if(track) {
    //cout<<" k0 "<<endl;
    //cout<<"Ana candidate type "<<track->GetType()<<" pt "<<track->GetPt()<<endl;
    return track;
  }
  //     if(!track){readK0s = true;}
  //   }
  
  return NULL;
}
