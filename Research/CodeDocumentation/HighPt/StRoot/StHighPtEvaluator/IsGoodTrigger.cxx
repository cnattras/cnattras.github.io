#include "IsGoodTrigger.h"
bool IsGoodTrigger(const string dataset, int trig){
  return IsGoodTrigger( dataset.c_str() , trig);
}

bool IsGoodTrigger(const char *dataset, int trig){
  int *triggers = goodTriggers(dataset);
  for(int i=0;i<10;i++){
    if(trig==triggers[i] && triggers[i]!=-1){return true;}
  }
  return false;
}


//TEvent functions
bool IsGoodTrigger(const char *dataset, TEvent *event){
  int trig1 = event->GetHeader()->GetTrigger1();
  int trig2 = event->GetHeader()->GetTrigger2();
  if(trig1==-1 && trig2==-1) return false;
  int *trigs = goodTriggers(dataset);
  int triggers[10];
  for(int i=0;i<10;i++){triggers[i]=trigs[i];}
  return IsGoodTrigger( dataset , triggers , event);
}
bool IsGoodTrigger(const string dataset, TEvent *event){
  int trig1 = event->GetHeader()->GetTrigger1();
  int trig2 = event->GetHeader()->GetTrigger2();
  if(trig1==-1 && trig2==-1) return false;
  int *trigs = goodTriggers(dataset);
  int triggers[10];
  for(int i=0;i<10;i++){triggers[i]=trigs[i];}
  return IsGoodTrigger( dataset , triggers , event);
}
bool IsGoodTrigger(const string dataset, int* trigs, TEvent *event){
  int trig1 = event->GetHeader()->GetTrigger1();
  int trig2 = event->GetHeader()->GetTrigger2();
  if(trig1==-1 && trig2==-1) return false;
  return IsGoodTrigger( dataset.c_str() , goodTriggers(dataset) , event);
}
bool IsGoodTrigger(const char *dataset, int* trigs, TEvent *event){
//   if( !(IsGoodTrigger(dataset,event->GetHeader()->GetTrigger1()) || IsGoodTrigger(dataset,event->GetHeader()->GetTrigger1())) ){return false;}
//   return true;
  int trig1 = event->GetHeader()->GetTrigger1();
  int trig2 = event->GetHeader()->GetTrigger2();
  if(trig1==-1 && trig2==-1) return false;
  for(int i=0;i<10;i++){if(trigs[i]==trig1 || trigs[i]==trig2) return true;}
  return false;
}


//StMuEvent functions
bool IsGoodTrigger(const char *dataset, StMuEvent *event){
  int *trigs = goodTriggers(dataset);
  int triggers[10];
  for(int i=0;i<10;i++){triggers[i]=trigs[i];}
  return IsGoodTrigger(dataset, triggers, event);
}
bool IsGoodTrigger(const string dataset, StMuEvent *event){
  int *trigs = goodTriggers(dataset);
  int triggers[10];
  for(int i=0;i<10;i++){triggers[i]=trigs[i];}
  return IsGoodTrigger(dataset, triggers, event);
}
bool IsGoodTrigger(const string dataset, int* trigs, StMuEvent *event){
  return IsGoodTrigger( dataset.c_str() , trigs, event);
}
bool IsGoodTrigger(const char *dataset, int* trigs, StMuEvent *event){
  string myDataSet = dataset;
  string AuAu200 = "AuAu200";
  string AuAu200Y2 = "AuAu200Y2";
  string dAu200 = "dAu200";
  string CuCu200 = "CuCu200";
  string CuCu62 = "CuCu62";
  string AuAu62 = "AuAu62";
  //triggers are, alas, heavily data set dependent :(  Even the syntax changed.
  bool badTrig = true;
  //This set of functions should work for AuAu200 year 4, CuCu200, CuCu62, AuAu62, dAu200(?)
  if(myDataSet != AuAu200Y2){
    vector<unsigned int> triggers = event->triggerIdCollection().nominal().triggerIds();
    vector<unsigned int>::iterator i;
    for(i = triggers.begin(); i != triggers.end(); i++){
      int trigger = *i;
      for(int j = 0; j<10; j++){
	if(trigs[j]==trigger && trigs[j]!=-1) {badTrig = false;}
      }
    }
  }
  if(myDataSet == AuAu62 && ( event->triggerIdCollection().nominal().isTrigger(35001) ||
			    event->triggerIdCollection().nominal().isTrigger(35009) )){
    if(event->ctbMultiplicity()<15){badTrig = true;}//these triggers are special for the AuAu62 GeV data and they have an extra condition
  }
  if(myDataSet == AuAu200Y2){
    int trigger = event->l0Trigger().triggerWord();
    for(int j = 0; j<10; j++){
      if(trigs[j]== trigger && trigs[j]!=-1) badTrig = false;
    }
  }
  //Now if at any time any of the triggers were recognized as good we're golden and we can accept this event
  if(badTrig){return false;}
  


  //If none of these things are bad, it's a good event
  return true;

}

bool IsTrigger(const char *dataset, TEvent *event, int testTrig){
  if(testTrig==-1) return false;
  return (testTrig == event->GetHeader()->GetTrigger1() || testTrig ==event->GetHeader()->GetTrigger2() );
}
bool IsTrigger(const string dataset, TEvent *event, int testTrig){
  return IsTrigger( (char*) dataset.c_str(), event, testTrig);
}
bool IsTrigger(const char *dataset, StMuEvent *event, int testTrig){
  string myDataSet = dataset;
  string AuAu200 = "AuAu200";
  string AuAu200Y2 = "AuAu200Y2";
  string dAu200 = "dAu200";
  string CuCu200 = "CuCu200";
  string CuCu62 = "CuCu62";
  string AuAu62 = "AuAu62";
  bool goodTrig = false;
  if(myDataSet != AuAu200Y2){
    vector<unsigned int> triggers = event->triggerIdCollection().nominal().triggerIds();
    vector<unsigned int>::iterator i;
    for(i = triggers.begin(); i != triggers.end(); i++){
      int trigger = *i;
      if(testTrig==trigger && trigger!=-1) {goodTrig= true;}
    }
  }
  if(myDataSet == AuAu62 && ( event->triggerIdCollection().nominal().isTrigger(35001) ||
			    event->triggerIdCollection().nominal().isTrigger(35009) )){
    if(event->ctbMultiplicity()<15){goodTrig = false;}//these triggers are special for the AuAu62 GeV data and they have an extra condition
  }
  if(myDataSet == AuAu200Y2){
    int trigger = event->l0Trigger().triggerWord();
    if(testTrig == trigger ) goodTrig = true;
  }
  return goodTrig;
}
bool IsTrigger(const string dataset, StMuEvent *event, int testTrig){
  return IsTrigger( (char*) dataset.c_str(), event, testTrig);
}
