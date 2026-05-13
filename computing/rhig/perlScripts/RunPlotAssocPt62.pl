#!/bin/perl
#Cu+Cu 62 GeV jobs
system "root4star -b -q macros/JetYields/PlotAssocPt62.C'(3.0,6.0,true,3)'\n";
system "root4star -b -q macros/JetYields/PlotAssocPt62.C'(4.0,6.0,true,3)'\n";
system "root4star -b -q macros/JetYields/PlotAssocPt62.C'(3.0,6.0,true,1)'\n";
system "root4star -b -q macros/JetYields/PlotAssocPt62.C'(4.0,6.0,true,1)'\n";


##Au+Au 62 GeV jobs
system "root4star -b -q macros/JetYields/PlotAssocPt62.C'(3.0,6.0,false,3)'\n";
system "root4star -b -q macros/JetYields/PlotAssocPt62.C'(4.0,6.0,false,3)'\n";
system "root4star -b -q macros/JetYields/PlotAssocPt62.C'(3.0,6.0,false,1)'\n";
system "root4star -b -q macros/JetYields/PlotAssocPt62.C'(4.0,6.0,false,1)'\n";
system "root4star -b -q macros/JetYields/PlotAssocPt62.C'(3.0,6.0,false,3,2)'\n";
system "root4star -b -q macros/JetYields/PlotAssocPt62.C'(4.0,6.0,false,3,2)'\n";
system "root4star -b -q macros/JetYields/PlotAssocPt62.C'(3.0,6.0,false,1,2)'\n";
system "root4star -b -q macros/JetYields/PlotAssocPt62.C'(4.0,6.0,false,1,2)'\n";
