#!/bin/perl
@lines = `cat eventnumfile.txt`;
for($i=0;$i<=$#lines;$i++){
chomp($lines[$i]);
#print "$lines[$i]\n";
#line like //txtfiles/junkVtxCut10PtAssoc15Trig30To60CB4.txt:Number of trigger particles 121628
#to make a line like float ntrig6cb4 = 1909574;
($garb,$remainder) = split("Cut",$lines[$i]);
($vtxbin,$remainder) = split("PtAssoc",$remainder);
($garb,$remainder) = split("CB",$lines[$i]);
($cb,$neve) = split(".txt:Number of trigger particles ",$remainder);
print "$lines[$i]\n";
print "float ntrig$vtxbin";
print "cb$cb";
print " = $neve\;\n";
#print "$cb $neve $vtxbin\n";
} 
