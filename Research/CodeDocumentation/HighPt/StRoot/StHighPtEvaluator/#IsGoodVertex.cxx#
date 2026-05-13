#include "IsGoodVertex.h"
#include "TMath.h"

bool IsGoodVertex(const string dataset, StMuEvent *event){
  return IsGoodVertex( dataset.c_str(), event);
}
bool IsGoodVertex(const char *dataset, StMuEvent *event){
  return IsGoodVertex( dataset, event->primaryVertexPosition().x(), event->primaryVertexPosition().y(), event->primaryVertexPosition().z() );
}
bool IsGoodVertex(const string dataset, TEvent *event){
  return IsGoodVertex( dataset.c_str() , event);
}
bool IsGoodVertex(const char *dataset, TEvent *event){
  return IsGoodVertex( dataset, event->GetZVertex() );
}

bool IsGoodVertex(const string dataset, float zvertex){
  return IsGoodVertex( dataset.c_str(), zvertex);
}
bool IsGoodVertex(const string dataset, float xvertex, float yvertex, float zvertex){
  return IsGoodVertex( dataset.c_str(), xvertex, yvertex, zvertex);
}

bool IsGoodVertex(const char *dataset, float zvertex){
  float max = 0;//defaults to saying every vertex is bad
  string myDataSet = dataset;
  string AuAu200 = "AuAu200";
  string dAu200 = "dAu200";
  string CuCu200 = "CuCu200";
  string CuCu62 = "CuCu62";
  string AuAu62 = "AuAu62";
  if(dataset == AuAu200){
    max = 25;
  }
  if(dataset == CuCu200){
    max = 30;
  }
  if(dataset == AuAu62){
    max = 30;
  }
  if(dataset == CuCu62){
    max = 50;
  }
  return (fabs(zvertex) < max);
}

bool IsGoodVertex(const char *dataset, float xvertex, float yvertex, float zvertex){
  float min = 1e-5;
  return (fabs(xvertex) > min && fabs(yvertex) > min && IsGoodVertex(dataset, zvertex) );
}

bool IsGoodVertex(const string dataset, float zvertexcut, StMuEvent *event){
  return IsGoodVertex( dataset.c_str() , zvertexcut, event);
}
bool IsGoodVertex(const char *dataset, float zvertexcut, StMuEvent *event){
  return IsGoodVertex( dataset, zvertexcut, 1e-5, 1e-5, event);
}
bool IsGoodVertex(const string dataset, float xvertexcut, float yvertexcut, float zvertexcut, StMuEvent *event){
  return IsGoodVertex( dataset.c_str() , xvertexcut, yvertexcut, zvertexcut, event );
}

bool IsGoodVertex(const char *dataset, float xvertexcut, float yvertexcut, float zvertexcut, StMuEvent *event){
  StThreeVectorF v = event->primaryVertexPosition();
  if( fabs( v.x() ) < xvertexcut && fabs ( v.y() ) < yvertexcut && fabs( v.z() ) < zvertexcut ){return true;}
  else{return false;}
}

bool IsGoodVertex(const string dataset, float zvertexcut, TEvent *event){
  return IsGoodVertex( dataset.c_str() , zvertexcut, event );
}
bool IsGoodVertex(const char *dataset, float zvertexcut, TEvent *event){
  return fabs( event->GetZVertex() ) < zvertexcut;
}
bool IsGoodVertex(const string dataset, float xvertexcut, float yvertexcut, float zvertexcut, TEvent *event){
  return IsGoodVertex( dataset.c_str(), xvertexcut, yvertexcut, zvertexcut, event);
}
bool IsGoodVertex(const char *dataset, float xvertexcut, float yvertexcut, float zvertexcut, TEvent *event){
  return IsGoodVertex( dataset, zvertexcut, event);
}

