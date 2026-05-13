#include "GetTrack.h"

TTrack* GetTTrack(char *dataset, StMuTrack *intrack){
  TTrack *tTrack = new TTrack();
  //delete tTrack;
  
  //tTrack->SetPx(intrack->p().x());
  // tTrack->SetPy(intrack->p().y());
  //tTrack->SetPz(intrack->p().z());
  tTrack->SetPt(intrack->pt());
  tTrack->SetPhi(intrack->phi());
  tTrack->SetEta(intrack->eta());
  tTrack->SetCharge(intrack->charge());
  // Charged tTrack is type 1
  tTrack->SetType(1);
  tTrack->SetNHits(intrack->nHitsFit());
  tTrack->SetNPossHits(intrack->nHitsPoss());
  // tTrack->SetdEdx(intrack->dEdx());
  // tTrack->SetDca(intrack->dcaGlobal().mag());
  tTrack->SetTrackId(intrack->id());  
  return tTrack;

}
TIdentifiedTrack* GetTIdentifiedTrack(char *dataset, StMuTrack *intrack){
  TIdentifiedTrack *tIdTrack = new TIdentifiedTrack( GetTTrack(dataset, intrack) );
  tIdTrack->SetNSigmaProton( intrack->nSigmaProton() );
  tIdTrack->SetNSigmaPion( intrack->nSigmaPion() );
  tIdTrack->SetNSigmaKaon( intrack->nSigmaKaon() );
  tIdTrack->SetNSigmaElectron( intrack->nSigmaElectron() );
  tIdTrack->SetdEdX( intrack->dEdx() );

  return tIdTrack;
}


TV0Track* GetTTrack( char *dataset, StV0MuDst *intrack, int type){
  TV0Track *tV0Track = new TV0Track();
  int particleType = 0;
//   for(int i=1;i<=3;i++){
//     if(IsGoodV0Track(dataset,intrack,i,"Loosest")){
//       particleType = i;
//       cout<<" type="<<i<<" ";
//     }
//   }
  particleType = type;
  if(particleType==0){return NULL;}
  tV0Track->SetPx(intrack->momPosX()+intrack->momNegX()); 
  tV0Track->SetPy(intrack->momPosY()+intrack->momNegY());
  tV0Track->SetPz(intrack->momPosZ()+intrack->momNegZ());
  //tV0Track->SetPt(sqrt(intrack->momV0X()*intrack->momV0X()+intrack->momV0Y()*intrack->momV0Y()));
  //tV0Track->SetPhi(atan2(intrack->momV0Y(),intrack->momV0X()));
  tV0Track->SetMass( GetV0Mass(intrack, type) );
  tV0Track->SetCharge(0);	  
  tV0Track->SetType(particleType);
  tV0Track->SetEta(intrack->pseudoRapV0());
  if(particleType<4) { //Lambda,AntiLambda 
    tV0Track->SetRapidity(intrack->rapLambda());
  }
  if(particleType==4) { //K0short 
    tV0Track->SetRapidity(intrack->rapK0Short());
  }
  tV0Track->SetDecayLength(intrack->decayLengthV0());
  tV0Track->SetDcaPosDaughterToPV(intrack->dcaPosToPrimVertex()); 
  tV0Track->SetDcaNegDaughterToPV(intrack->dcaNegToPrimVertex());
  tV0Track->SetDcaV0ToPV(intrack->dcaV0ToPrimVertex());  
  tV0Track->SetDcaDaughters(intrack->dcaV0Daughters()); 
  tV0Track->SetNHitsPosDaughter(intrack->topologyMapPos().numberOfHits(kTpcId));
  tV0Track->SetNHitsNegDaughter(intrack->topologyMapNeg().numberOfHits(kTpcId));
  //These really should hold nSigma but they don't yet
  tV0Track->SetdEdxPosDaughter(intrack->dedxPos());
  tV0Track->SetdEdxNegDaughter(intrack->dedxNeg());
  tV0Track->SetPosDaughterTrackId(intrack->keyPos());
  tV0Track->SetNegDaughterTrackId(intrack->keyNeg());

  return tV0Track;

}

TV0Track* GetTTrack( char *dataset, StV0MuDst *intrack, int type, StMuTrack *globalNeg, StMuTrack *globalPos){
  TV0Track *tV0Track = new TV0Track();
  int particleType = 0;
//   for(int i=1;i<=3;i++){
//     if(IsGoodV0Track(dataset,intrack,i,"Loosest")){
//       particleType = i;
//       cout<<" type="<<i<<" ";
//     }
//   }
  particleType = type;
  if(particleType==0){return NULL;}
  tV0Track->SetPx(intrack->momPosX()+intrack->momNegX()); 
  tV0Track->SetPy(intrack->momPosY()+intrack->momNegY());
  tV0Track->SetPz(intrack->momPosZ()+intrack->momNegZ());
  //tV0Track->SetPt(sqrt(intrack->momV0X()*intrack->momV0X()+intrack->momV0Y()*intrack->momV0Y()));
  //tV0Track->SetPhi(atan2(intrack->momV0Y(),intrack->momV0X()));
  tV0Track->SetMass( GetV0Mass(intrack, type) );
  tV0Track->SetCharge(0);	  
  tV0Track->SetType(particleType);
  tV0Track->SetEta(intrack->pseudoRapV0());
  if(particleType<4) { //Lambda,AntiLambda 
    tV0Track->SetRapidity(intrack->rapLambda());
  }
  if(particleType==4) { //K0short 
    tV0Track->SetRapidity(intrack->rapK0Short());
  }
  tV0Track->SetDecayLength(intrack->decayLengthV0());
  tV0Track->SetDcaPosDaughterToPV(intrack->dcaPosToPrimVertex()); 
  tV0Track->SetDcaNegDaughterToPV(intrack->dcaNegToPrimVertex());
  tV0Track->SetDcaV0ToPV(intrack->dcaV0ToPrimVertex());  
  tV0Track->SetDcaDaughters(intrack->dcaV0Daughters()); 
  tV0Track->SetNHitsPosDaughter(intrack->topologyMapPos().numberOfHits(kTpcId));
  tV0Track->SetNHitsNegDaughter(intrack->topologyMapNeg().numberOfHits(kTpcId));
  //These really should hold nSigma but they don't yet
  //tV0Track->SetdEdxPosDaughter(intrack->dedxPos());
  //tV0Track->SetdEdxNegDaughter(intrack->dedxNeg());
  tV0Track->SetPosDaughterTrackId(intrack->keyPos());
  tV0Track->SetNegDaughterTrackId(intrack->keyNeg());
  GetTTrack(tV0Track, globalPos, globalNeg);
  return tV0Track;

}
TV0Track* GetTTrack(TV0Track *tV0Track, StMuTrack *globalPos, StMuTrack *globalNeg){
  if(!globalPos || ! globalNeg){
    cerr<<"TV0Track *GetTTrack::Missing a global track!  Track not modified."<<endl;
    return tV0Track;
  }
  int type = tV0Track->GetType();
  if(type==1){//lambda
    tV0Track->SetdEdxPosDaughter(globalPos->nSigmaProton());//proton
    tV0Track->SetdEdxNegDaughter(globalNeg->nSigmaPion());  //pion
  }
  if(type==2){//antilambda
    tV0Track->SetdEdxPosDaughter(globalPos->nSigmaPion());//pion
    tV0Track->SetdEdxNegDaughter(globalNeg->nSigmaProton());  //proton
  }
  if(type==3){//K0s
    tV0Track->SetdEdxPosDaughter(globalPos->nSigmaPion());//pion
    tV0Track->SetdEdxNegDaughter(globalNeg->nSigmaPion());  //pion
  }
  tV0Track->SetOrigXPos((float)(globalPos->helix().origin().x()));
  tV0Track->SetOrigYPos((float)(globalPos->helix().origin().y()));
  tV0Track->SetOrigZPos((float)(globalPos->helix().origin().z()));

  // negative daughter
  tV0Track->SetOrigXNeg((float)(globalNeg->helix().origin().x()));
  tV0Track->SetOrigYNeg((float)(globalNeg->helix().origin().y()));
  tV0Track->SetOrigZNeg((float)(globalNeg->helix().origin().z())); 

  return tV0Track;

}
TXiTrack* GetTTrack(TXiTrack *tXiTrack, StMuTrack *globalPos, StMuTrack *globalNeg, StMuTrack *globalBach){
  if(!globalPos || ! globalNeg){
    cerr<<"TXiTrack *GetTTrack::Missing a global track!  Track not modified."<<endl;
    return tXiTrack;
  }
  int type = tXiTrack->GetType();
  if(type==4){//Xi -> Lambda + pi-
    tXiTrack->SetdEdxPosDaughter(globalPos->nSigmaProton());//proton
    tXiTrack->SetdEdxNegDaughter(globalNeg->nSigmaPion());  //pion
    tXiTrack->SetdEdxBachDaughter(globalBach->nSigmaPion());  //Pion
  }
  if(type==18){//AntiXi -> AntiLambda + pi+
    tXiTrack->SetdEdxPosDaughter(globalPos->nSigmaPion());//pion
    tXiTrack->SetdEdxNegDaughter(globalNeg->nSigmaProton());  //proton
    tXiTrack->SetdEdxBachDaughter(globalBach->nSigmaPion());  //pion
  }
  if(type==5){//Omega -> Lambda + K-
    tXiTrack->SetdEdxPosDaughter(globalPos->nSigmaProton());//proton
    tXiTrack->SetdEdxNegDaughter(globalNeg->nSigmaPion());  //pion
    tXiTrack->SetdEdxBachDaughter(globalBach->nSigmaKaon());  //Kaon
  }
  if(type==19){//Omega -> Lambda + K-
    tXiTrack->SetdEdxPosDaughter(globalPos->nSigmaPion());//pion
    tXiTrack->SetdEdxNegDaughter(globalNeg->nSigmaProton());  //proton
    tXiTrack->SetdEdxBachDaughter(globalBach->nSigmaKaon());  //Kaon
  }
  return tXiTrack;

}

TTrack* GetTTrack(string dataset, StMuTrack *intrack){
  return GetTTrack( (char*) dataset.c_str(), intrack);
}
TIdentifiedTrack* GetTIdentifiedTrack(string dataset, StMuTrack *intrack){
  
  return GetTIdentifiedTrack( (char*) dataset.c_str(), intrack);
}


TV0Track* GetTTrack( string dataset, StV0MuDst *intrack, int type){
  return GetTTrack( (char*)dataset.c_str(), intrack, type);
}

TV0Track* GetTTrack( string dataset, StV0MuDst *intrack, int type, StMuTrack *globalPos, StMuTrack *globalNeg){
  return GetTTrack( (char*)dataset.c_str(), intrack, type, globalPos, globalNeg);
}

TV0Track* GetTTrack( string dataset, StV0MuDst *intrack){ 
  for(int i=1;i<=3;i++){
    if(IsGoodV0Track(dataset,intrack,i,"Loosest")){
      return GetTTrack( (char*)dataset.c_str(), intrack, i);
    }
  }
  return NULL;
}
TV0Track* GetTTrack( char *dataset, StV0MuDst *intrack){ 
  for(int i=1;i<=3;i++){
    if(IsGoodV0Track(dataset,intrack,i,"Loosest")){
      return GetTTrack(dataset, intrack, i);
    }
  }
  return NULL;
}

TResonanceTrack* GetTTrack(char *dataset, StMuTrack *posTrack, StMuTrack *negTrack, int type){
  //make TResonance starting with positive track
  TResonanceTrack *track = new TResonanceTrack( GetTTrack(dataset, posTrack), type );
  //copy negative track variables:
  track->SetNHitsNeg(negTrack->nHitsFit());
  track->SetNPossHitsNeg(negTrack->nHitsPoss());
  //the dEdx is actually the nSigmaDaughter and it needs to be particle type dependent
  if(type == 14)  track->SetdEdxNeg(negTrack->nSigmaPion());//lambda: negative track is proton
  if(type == 15)  track->SetdEdxNeg(negTrack->nSigmaProton());//antilambda: negative track is pion
  if(type == 16)  track->SetdEdxNeg(negTrack->nSigmaPion());//K0s: negative track is pion
  if(type == 17)  track->SetdEdxNeg(negTrack->nSigmaKaon());//Phi: negative track is kaon
  if(type == 14)  track->SetdEdxNeg(posTrack->nSigmaProton());//lambda: positive track is pion
  if(type == 15)  track->SetdEdxNeg(posTrack->nSigmaPion());//antilambda: positive track is proton
  if(type == 16)  track->SetdEdxNeg(posTrack->nSigmaPion());//K0s: positive track is pion
  if(type == 17)  track->SetdEdxNeg(posTrack->nSigmaKaon());//Phi: positive track is kaon

  track->SetTrackIdNeg(negTrack->id());
  //positive track variables ok from TTrack method
  track->SetMass( GetTResonanceMass(posTrack,negTrack,type) );
  track->SetOpeningAngle(GetTResonanceOpeningAngle(posTrack, negTrack) );

  track->SetType(type);
  
  return track;
}
TResonanceTrack* GetTTrack(string dataset, StMuTrack *posTrack, StMuTrack *negTrack, int type){
  return GetTTrack((char *) dataset.c_str(),posTrack, negTrack, type);
}



TXiTrack* GetTTrack( string dataset, StXiMuDst *intrack, int type){
  return GetTTrack( (char*) dataset.c_str(),intrack, type);
}

TXiTrack* GetTTrack( char *dataset, StXiMuDst *intrack, int type){
  TXiTrack *tXiTrack = new TXiTrack();
  int particleType = 0;
//   for(int i=1;i<=3;i++){
//     if(IsGoodXiTrack(dataset,intrack,i,"Loosest")){
//       particleType = i;
//       cout<<" type="<<i<<" ";
//     }
//   }
  particleType = type;
  if(particleType==0){return NULL;}
  tXiTrack->SetPt(sqrt(intrack->momXiAtPrimVertexX()*intrack->momXiAtPrimVertexX()+intrack->momXiAtPrimVertexY()*intrack->momXiAtPrimVertexY()));
  tXiTrack->SetPtDecay(sqrt(intrack->momXiX()*intrack->momXiX()+intrack->momXiY()*intrack->momXiY()));
  tXiTrack->SetPhi(atan2(intrack->momXiAtPrimVertexY(),intrack->momXiAtPrimVertexX()));
  tXiTrack->SetCharge(intrack->charge());	  
  tXiTrack->SetType(particleType);
  tXiTrack->SetEta(intrack->pseudoRapXi());
  //the Xi and omega decay into a lambda + something else
  if(particleType==4 || particleType ==5){
    tXiTrack->SetMassV0( intrack->massLambda() );
  }
  //where as the anti-Xi and anti-Omega decay into an antilambda + something else
  if(particleType==18 || particleType ==19){
    tXiTrack->SetMassV0( intrack->massAntiLambda() );
  }
  if(particleType==4 || particleType==18) { //Xi
    tXiTrack->SetRapidity(intrack->rapXi());
    tXiTrack->SetMass( intrack->massXi() );
  }
  if(particleType==5 || particleType==19) { //Omega
    tXiTrack->SetRapidity(intrack->rapOmega());
    tXiTrack->SetMass( intrack->massOmega() );
  }
  tXiTrack->SetDecayLengthXi(intrack->decayLengthXi());
  tXiTrack->SetDecayLengthV0(intrack->decayLengthV0());
  tXiTrack->SetDcaPosDaughterToPV(intrack->dcaPosToPrimVertex()); 
  tXiTrack->SetDcaNegDaughterToPV(intrack->dcaNegToPrimVertex()); 
  tXiTrack->SetDcaBachDaughterToPV(intrack->dcaBachelorToPrimVertex());
  tXiTrack->SetDcaXiToPV(intrack->dcaXiToPrimVertex());  
  tXiTrack->SetDcaV0ToPV(intrack->dcaV0ToPrimVertex());  
  tXiTrack->SetDcaV0Daughters(intrack->dcaV0Daughters());  
  tXiTrack->SetDcaXiDaughters(intrack->dcaXiDaughters()); 
  tXiTrack->SetNHitsPosDaughter(intrack->topologyMapPos().numberOfHits(kTpcId));
  tXiTrack->SetNHitsNegDaughter(intrack->topologyMapNeg().numberOfHits(kTpcId));
  tXiTrack->SetNHitsBachDaughter(intrack->topologyMapBachelor().numberOfHits(kTpcId));
  tXiTrack->SetdEdxPosDaughter(intrack->dedxPos());
  tXiTrack->SetdEdxNegDaughter(intrack->dedxNeg());
  tXiTrack->SetdEdxBachDaughter(intrack->dedxBachelor());
  tXiTrack->SetdEdxErrPosDaughter(intrack->errDedxPos());
  tXiTrack->SetdEdxErrNegDaughter(intrack->errDedxNeg());
  tXiTrack->SetdEdxErrBachDaughter(intrack->errDedxBachelor());
  tXiTrack->SetPosDaughterTrackId(intrack->keyPos());
  tXiTrack->SetNegDaughterTrackId(intrack->keyNeg());
  tXiTrack->SetBachDaughterTrackId(intrack->keyBachelor());

  return tXiTrack;

}
