#ifndef __CINT__
#  include "tools.h"
#  include "TROOT.h"
#  include "TSystem.h"
#  include "Riostream.h"
#endif

void testtools(){
  
//int main(){
  
  cout<<"Loading library StHighPtTools"<<endl;
  gSystem->Load("libStHighPtTools");
  cout<<"Testing tools"<<endl;

  cout<<"Testing centrality for AuAu200"<<endl;
  for(int i=0;i<600;i+=20){
    int cent = centrality("AuAu200",i);
    cout<<"multiplicity :"<<i<<" centrality :"<<cent<<endl;
  }
  cout<<endl<<endl;

  cout<<"Testing centrality for CuCu200"<<endl;
  for(int i=0;i<150;i+=10){
    cent = centrality("CuCu200",i);
    cout<<"multiplicity :"<<i<<" centrality :"<<cent<<endl;
  }
  cout<<endl<<endl;

  cout<<"Testing centrality for AuAu62"<<endl;
  for(int i=0;i<400;i+=20){
    cent = centrality("AuAu62",i);
    cout<<"multiplicity :"<<i<<" centrality :"<<cent<<endl;
  }
  cout<<endl<<endl;


  cout<<"Testing efficiencies for AuAu200"<<endl;
  for(int i=0;i<400;i+=30){
    for(float pt=1.0; pt<4.0; pt+=0.5){
      float eff = efficiency("AuAu200",pt,i);
      cout<<"efficiency "<<eff<<" for centrality "<<centrality("AuAu200",i)<<endl;
    }
  }
  cout<<endl<<endl;

  cout<<"Testing efficiencies for CuCu200"<<endl;
  for(int i=0;i<200;i+=20){
    for(float pt=1.0; pt<4.0; pt+=0.5){
      float eff = efficiency("CuCu200",pt,i);
      cout<<"efficiency "<<eff<<" for centrality "<<centrality("CuCu200",i)<<endl;
    }
  }
  cout<<endl<<endl;

  cout<<"Testing v2 for AuAu200"<<endl;
  for(int partID =0;partID<=3;partID++){
    for(int i=0;i<200;i+=20){
      for(float pt=1.0; pt<4.0; pt+=0.5){
	float v2 = v2("AuAu200",pt,i,partID);
	cout<<"v2 "<<v2<<" for centrality "<<centrality("CuCu200",i)<<" and pt "<<pt<<" for partID "<<partID<<endl;
      }
    }
    cout<<endl;
  }
  cout<<endl<<endl;


  cout<<"Testing v2 for CuCu200"<<endl;
  for(int partID =0;partID<=3;partID++){
    for(int i=0;i<200;i+=20){
      for(float pt=1.0; pt<4.0; pt+=0.5){
	float v2 = v2("CuCu200",pt,i,partID);
	cout<<"v2 "<<v2<<" for centrality "<<centrality("CuCu200",i)<<" and pt "<<pt<<" for partID "<<partID<<endl;
      }
    }
    cout<<endl;
  }
  cout<<endl<<endl;

 }
