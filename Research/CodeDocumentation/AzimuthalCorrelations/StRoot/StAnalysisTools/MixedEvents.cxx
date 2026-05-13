#include "MixedEvents.h"
TH1F *MixedEvents(TH1F* trigger, TH1F* associated, TH1I *numAssoc, char *name, char *title){
  Double_t mypi = TMath::Pi();
   TH1F *mixedEvent=  new TH1F(name,title,1200,-mypi,mypi);
   mixedEvent->Sumw2();

   for(int i=0;i<1000000;i++){
     //if(i%100000==0) cout << "Event " << i << endl;
     float trigPhi=trigger->GetRandom();
     //int nassoc = 1;
     int nassoc=int(numAssoc->GetRandom());//need more for this, gotta add a histogram for nAssoc
     if(nassoc>0) {
       for(int j=1;j<=nassoc;j++) {
	 float assocPhi =associated->GetRandom();
	 float deltaPhi = dPhi(trigPhi, assocPhi);
	 mixedEvent->Fill(fabs(deltaPhi));
	 mixedEvent->Fill(-fabs(deltaPhi));
       }
     }
   }

   return mixedEvent;

}
