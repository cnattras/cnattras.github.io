#!/bin/perl
@cases = (2,4,5);
for($i=0;$i<3;$i++){
  #void PlotNPart62(float assocPT = 1.5, float assocHigh = 6.,float trigLow = 3., float trigHigh = 6., int nCB = 3,int mycase=4,bool CuCu = true)

  #Cu+Cu 62 GeV jobs
  system "root4star -b -q macros/JetYields/PlotNPart62.C'(1.0,6.,3.0,6.0,3,$cases[$i],true)'\n";
  system "root4star -b -q macros/JetYields/PlotNPart62.C'(1.0,6.,4.0,6.0,3,$cases[$i],true)'\n";
  system "root4star -b -q macros/JetYields/PlotNPart62.C'(1.5,6.,3.0,6.0,3,$cases[$i],true)'\n";
  system "root4star -b -q macros/JetYields/PlotNPart62.C'(1.5,6.,4.0,6.0,3,$cases[$i],true)'\n";
  system "root4star -b -q macros/JetYields/PlotNPart62.C'(2.0,6.,3.0,6.0,3,$cases[$i],true)'\n";
  system "root4star -b -q macros/JetYields/PlotNPart62.C'(2.0,6.,4.0,6.0,3,$cases[$i],true)'\n";
  
  #Au+Au 62 GeV jobs
  system "root4star -b -q macros/JetYields/PlotNPart62.C'(1.0,6.,3.0,6.0,3,$cases[$i],false)'\n";
  system "root4star -b -q macros/JetYields/PlotNPart62.C'(1.0,6.,4.0,6.0,3,$cases[$i],false)'\n";
  system "root4star -b -q macros/JetYields/PlotNPart62.C'(1.5,6.,3.0,6.0,3,$cases[$i],false)'\n";
  system "root4star -b -q macros/JetYields/PlotNPart62.C'(1.5,6.,4.0,6.0,3,$cases[$i],false)'\n";
  system "root4star -b -q macros/JetYields/PlotNPart62.C'(2.0,6.,3.0,6.0,3,$cases[$i],false)'\n";
  system "root4star -b -q macros/JetYields/PlotNPart62.C'(2.0,6.,4.0,6.0,3,$cases[$i],false)'\n";
}
