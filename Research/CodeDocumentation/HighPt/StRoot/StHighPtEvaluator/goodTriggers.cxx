#include "goodTriggers.h"
int* goodTriggers(const string dataset){
  return goodTriggers( dataset.c_str() );
}
int* goodTriggers(const char *dataset){
  string myDataSet = dataset;
  string AuAu200 = "AuAu200";
  string AuAu200Y2 = "AuAu200Y2";
  string dAu200 = "dAu200";
  string CuCu200 = "CuCu200";
  string CuCu62 = "CuCu62";
  string AuAu62 = "AuAu62";
  int triggers[]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
  if(dataset == AuAu200Y2){
    triggers[0]=4096;
    triggers[1]=4352;
  }
  if(dataset == AuAu200){
    triggers[0] = 15007;
    triggers[1] = 15105;
  }
  if(dataset == CuCu200){
    triggers[0] = 66007;//min bias
    triggers[1] = 66203;//high tower
  }
  if(dataset == AuAu62){
    triggers[0] = 35004;
    triggers[1] = 35007;
    //careful!
    //these two triggers need to have ctb multiplicity over 15
    cout<<"Warning:  Using triggers 35001 and 35009 for 62 GeV AuAu.  If you are not using the default event cuts, be sure to cut on the number of counts in the ctb being greater than 15."<<endl;
    triggers[2] = 35001;
    triggers[3] = 35009;
  }
  if(dataset == CuCu62){
    triggers[0] = 76007;
    triggers[1] = 76011;
  }
  return triggers;
}
