#!/bin/perl
open (FILE, "<textFiles/parameters-RunV0CutTunerAuAu200Y7.txt") || die "Can't oupen file with list of files.\n";
while (<FILE>)  # While still input lines in the file...
  {
    ($data,$garb) = split ("#",$_);
    ($data,$garb) = split ("\n",$data);
    ($par[0],$par[1],$par[2]) = split (" ",$data);
    #print "Parameters $par[0] $par[1] $par[2] $par[3] $par[4] $par[5]\n";
    system "perl perlScripts/ChainGeoCutsV0FilesAuAu200Y7WithArgs.pl $par[0] $par[1] $par[2]";

  }
