#ifdef __CINT__
//IncFile="efficiency.h"
//IncFile="efficiencyCorrection.h"
//IncFile="centrality.h"
//IncFile="v2.h"
//IncFile="StMuDSTMaker/COMMON/StMuTrack.h"
//IncFile="../StHighPtTree/TV0Track.h"
//IncFile="../StHighPtTree/TXiTrack.h"
//IncFile="../StHighPtTree/TTrack.h"
//IncFile="../StHighPtTree/TIdentifiedTrack.h"
//IncFile="StStrangeMuDstMaker/StV0MuDst.hh"
//IncFile="StStrangeMuDstMaker/StXiMuDst.hh"
//IncFile="../StHighPtTree/TEvent.h"
//IncFile="StMuDSTMaker/COMMON/StMuEvent.h"
//IncFile="GetTrack.h"
//IncFile="GetV0Mass.h"
//IncFile="GetdEdXNSigma.h"
//IncFile="GetRunID.h"
//IncFile="GetEventID.h"
//IncFile="GetTResonanceMass.h"
//IncFile="GetTResonanceP.h"
//IncFile="GetParticleName.h"
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ function centrality(const char *, int );
#pragma link C++ function centrality(const string, int );
#pragma link C++ function NumberOfCentralityBins(const char *);
#pragma link C++ function GetCentralityLabel(const char *, int);
#pragma link C++ function efficiency(const char *, float , int, int );
#pragma link C++ function efficiencyCorrection(const char *, float , int, int );
#pragma link C++ function v2(const char *, float , int , int);
#pragma link C++ function GetTTrack(char *, StMuTrack *);
#pragma link C++ function GetTIdentifiedTrack(char *, StMuTrack *);
#pragma link C++ function GetTTrack(string , StMuTrack *);
#pragma link C++ function GetTIdentifiedTrack(string , StMuTrack *);
#pragma link C++ function GetTV0Track(char *, StV0MuDst *);
#pragma link C++ function GetTV0Track(string , StV0MuDst *);
#pragma link C++ function GetTV0Track(char *, StV0MuDst *, int);
#pragma link C++ function GetTV0Track(string , StV0MuDst *, int);
#pragma link C++ function GetTTrack(TV0Track *, StMuTrack *, StMuTrack *);
#pragma link C++ function GetTXiTrack(char *, StXiMuDst *, int);
#pragma link C++ function GetTXiTrack(string , StXiMuDst *, int);
#pragma link C++ function GetTTrack(TXiTrack *, StMuTrack*, StMuTrack*, StMuTrack*);
#pragma link C++ function GetV0Mass(StV0MuDst*, int);
#pragma link C++ function GetV0Mass(TV0Track *, int);
#pragma link C++ function GetPosDaughtdEdXNSigma(char *, StV0MuDst *, int );
#pragma link C++ function GetNegDaughtdEdXNSigma(string , StV0MuDst *, int );
#pragma link C++ function GetPosDaughtdEdXNSigma(char *, StV0MuDst *, int, StMuTrack * , StMuTrack *);
#pragma link C++ function GetNegDaughtdEdXNSigma(string , StV0MuDst *, int, StMuTrack *, StMuTrack * );
#pragma link C++ function GetPosDaughtdEdXNSigma(char *, TV0Track *, int );
#pragma link C++ function GetNegDaughtdEdXNSigma(string , TV0Track *, int );
#pragma link C++ function GetdEdXNSigma(char *, double, double,double,double,double,double);
#pragma link C++ function GetRunID(char *, StMuEvent *);
#pragma link C++ function GetRunID(string , StMuEvent *);
#pragma link C++ function GetRunID(char *, TEvent *);
#pragma link C++ function GetRunID(string , TEvent *);
#pragma link C++ function GetEventID(char *, StMuEvent *);
#pragma link C++ function GetEventID(string , StMuEvent *);
#pragma link C++ function GetEventID(char *, TEvent *);
#pragma link C++ function GetEventID(string , TEvent *);
#pragma link C++ function GetVertexZ(char *, StMuEvent *);
#pragma link C++ function GetVertexZ(string , StMuEvent *);
#pragma link C++ function GetVertexZ(char *, TEvent *);
#pragma link C++ function GetVertexZ(string , TEvent *);
#pragma link C++ function GetRefMult(char *, StMuEvent *);
#pragma link C++ function GetRefMult(string , StMuEvent *);
#pragma link C++ function GetRefMult(char *, TEvent *);
#pragma link C++ function GetRefMult(string , TEvent *);
#pragma link C++ function GetTResonanceMass(StMuTrack *, StMuTrack *, int);
#pragma link C++ function GetTResonanceP(StMuTrack *, StMuTrack *);
#pragma link C++ function GetTResonancePt(StMuTrack *, StMuTrack *);
#pragma link C++ function GetTResonancePx(StMuTrack *, StMuTrack *);
#pragma link C++ function GetTResonancePy(StMuTrack *, StMuTrack *);
#pragma link C++ function GetTResonancePhi(StMuTrack *, StMuTrack *);
#pragma link C++ function GetTResonanceOpeningAngle(StMuTrack *, StMuTrack *);
#pragma link C++ function GetTTrack(char *, StMuTrack *, StMuTrack *, int );
#pragma link C++ function GetTTrack(string , StMuTrack *, StMuTrack *, int );
#pragma link C++ function dPhi(float, float);
#pragma link C++ function GetParticleName(int);
#pragma link C++ function GetSimpleParticleName(int);
#endif
