#include "IsGoodVertexRank.h"
bool IsGoodVertexRank(char *dataset, float ranking){
  string myDataSet = dataset;
  string AuAu200 = "AuAu200";
  string dAu200 = "dAu200";
  string CuCu200 = "CuCu200";
  string CuCu62 = "CuCu62";
  string AuAu62 = "AuAu62";
  //Dataset dependent functions:
  if(dataset==CuCu200){
    if(ranking<-2.5) return false;
  }
  return true;
}
bool IsGoodVertexRank(string dataset, float ranking){
  return IsGoodVertexRank((char*)dataset.c_str(),ranking);
}
