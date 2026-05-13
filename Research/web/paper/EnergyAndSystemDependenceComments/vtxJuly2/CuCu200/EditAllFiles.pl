#!/bin/perl
#perl EditFile.pl dEtadPhi_trig_h_pT30_60_assoc_h_pT10_100_CentBin22DdEtaMethod n6 Cutn6CB2
@cuts  = (-30,-26,-22,-18,-14,-10,-6,-2,2,6,10,14,18,22,26);
@names = ("n30","n26","n22","n18","n14","n10","n6","n2","2","6","10","14","18","22","26");
@centbins = (1,2,3,4,5,6);
$assoclowname = $ARGV[0];
$assoclowcut = $triglowname/10;
$assochighname = $ARGV[1];
$assochighcut = $trighighname/10;
$triglowname = $ARGV[2];
$triglowcut = $triglowname/10;
$trighighname = $ARGV[3];
$trighighcut = $trighighname/10;
#$centbin = $ARGV[4];
for($cb=0;$cb<=$#centbins;$cb++){
  $centbin=$centbins[$cb];
  for($i=0;$i<=$#cuts;$i++){
    #$centbin = 1;
    $command = "perl EditFile.pl dEtadPhi_trig_h_pT"."$triglowname"."_"."$trighighname"."_assoc_h_pT"."$assoclowname"."_"."$assochighname"."_CentBin"."$centbin"."2DdEtaMethod $names[$i] Cut$names[$i]"."CB$centbin";
    print "$command\n";
    system "$command\n";
    #$centbin++;
    #$command = "perl EditFile.pl dEtadPhi_trig_h_pT"."$triglowname"."_"."$trighighname"."_assoc_h_pT"."$assoclowname"."_"."$assochighname"."_CentBin"."$centbin"."2DdEtaMethod $names[$i] Cut$names[$i]"."CB$centbin";
    #system "$command\n";
  }
}
