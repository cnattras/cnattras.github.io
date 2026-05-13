#!/bin/perl
open (FILE, "<textFiles/parameters-RunQAMaker.txt") || die "Can't oupen file with list of files.\n";
while (<FILE>)  # While still input lines in the file...
  {
    ($data,$garb) = split ("#",$_);
    ($data,$garb) = split ("\n",$data);
    ($par[0],$par[1],$par[2],$par[3],$par[4],$par[5]) = split (" ",$data);
    #print "Parameters $par[0] $par[1] $par[2] $par[3] $par[4] $par[5]\n";
    system "perl perlScripts/ChainQAPtFilesAuAu200Y7WithArgs.pl $par[0] $par[1] $par[2] $par[3] $par[4] $par[5] \n";
    system "perl perlScripts/ChainQAPhiFilesAuAu200Y7WithArgs.pl $par[0] $par[1] $par[2] $par[3] $par[4] $par[5]\n";

  }
