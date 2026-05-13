#!/bin/perl

#perlScripts/RunRootFilesAssocPt62.pl  perlScripts/RunRootFilesNpart62.pl  perlScripts/RunRootFilesTrigPt62.pl
system "perl perlScripts/RunRootFilesAssocPt62.pl >& RunRootFilesAssocPt62.pl.out";
system "perl perlScripts/RunRootFilesNpart62.pl >& RunRootFilesNpart62.pl.out";
system "perl perlScripts/RunRootFilesTrigPt62.pl >& RunRootFilesTrigPt62.pl.out";


#perlScripts/RunPlotAssocPt62.pl  perlScripts/RunPlotNpart62.pl  perlScripts/RunPlotTrigPt62.pl
system "perl perlScripts/RunPlotAssocPt62.pl >& RunPlotAssocPt62.pl.out";
system "perl perlScripts/RunPlotNpart62.pl >& RunPlotNpart62.pl.out";
system "perl perlScripts/RunPlotTrigPt62.pl >& RunPlotTrigPt62.pl.out";
