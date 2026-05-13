#!/bin/perl
open (FILE, "<textFiles/AuAu200Y7V0FileList.txt") || die "Can't oupen file with list of files.\n";
while (<FILE>)  # While still input lines in the file...
  {
    $data = $_;
    chomp($data);
    #print "$data\n";
    system "root4star -b -q macros/geoCuts/PlotV0MassPeaks.C\'(\"$data\",\"junky.root\")\'";
    ($garb1,$i,$j,$k1,$garb2) = split("-",$data);
    #print "|$i| |$j| |$k1|\n";
    ($k,$garb) = split(".root",$k1);
    #print "|$i| |$j| |$k|\n";
    system "mkdir geoCuts/Plots/AuAu200V0"."_"."$i"."_"."$j"."_"."$k";
    system "mkdir geoCuts/Plots/AuAu200V0"."_"."$i"."_"."$j"."_"."$k/Plots";
    system "mv geoCuts/Plots/K0*.eps geoCuts/Plots/AuAu200V0"."_"."$i"."_"."$j"."_"."$k/Plots";
    system "mv geoCuts/Plots/Lam*.eps geoCuts/Plots/AuAu200V0"."_"."$i"."_"."$j"."_"."$k/Plots";
    system "mv geoCuts/Plots/Anti*.eps geoCuts/Plots/AuAu200V0"."_"."$i"."_"."$j"."_"."$k/Plots";
    #print "$garb1 $i $j $k $garb2\n";
    #($data,$garb) = split ("#",$_);
    #($data,$garb) = split ("\n",$data);
    #($par[0],$par[1],$par[2],$par[3],$par[4],$par[5]) = split (" ",$data);
    #print "Parameters $par[0] $par[1] $par[2] $par[3] $par[4] $par[5]\n";
    #system "perl perlScripts/ChainQAPtFilesAuAu200Y7WithArgs.pl $par[0] $par[1] $par[2] $par[3] $par[4] $par[5] \n";
    #system "perl perlScripts/ChainQAPhiFilesAuAu200Y7WithArgs.pl $par[0] $par[1] $par[2] $par[3] $par[4] $par[5]\n";

  }
