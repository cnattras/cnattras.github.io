#!/bin/perl
#$jobID =$ARGV[0];
$dir = $ARGV[0];#`pwd`;
#chomp($dir);
#print "Job ID $jobID\n";
#print "Working directory $dir\n";
$test = "ls $dir"."/*.root";
#print "$test\n";
#die;
@files = `$test`;
$nfiles = $#files;
#print "$nfiles files to resubmit\n";
$nEvents = 0;
$nEventsCent = 0;
$nEventsMid = 0;
$nEventsPeriph = 0;
for($i=0;$i<=$nfiles;$i++){  
  chomp($files[$i]);
  $command = "root4star -b -q /home/nattrass/AzimuthalCorrelations/macros/eventcountCuCu62CB.C\'(\"$files[$i]\")\'";
  @test = `$command`;
  $ntest = $#test;
  for($j=0;$j<=$ntest;$j++){  
    if($test[$j] =~ "centeve"){
      #print "$test[$j]\n";
      ($neve,$garb) = split(" ",$test[$j]);
      #print "Events: $neve\n";
      $nEventsCent += $neve;
    } 
    if($test[$j] =~ "mideve"){
      #print "$test[$j]\n";
      ($neve,$garb) = split(" ",$test[$j]);
      #print "Events: $neve\n";
      $nEventsMid += $neve;
    } 
    if($test[$j] =~ "peripheve"){
      #print "$test[$j]\n";
      ($neve,$garb) = split(" ",$test[$j]);
      #print "Events: $neve\n";
      $nEventsPeriph += $neve;
    }
    if($test[$j] =~ "events"){
      #print "$test[$j]\n";
      ($neve,$garb) = split(" ",$test[$j]);
      #print "Events: $neve\n";
      $nEvents += $neve;
    }
  }
  print "$command\n";
}

$nGoodEvents = $nEvents;
#print "$nEvents good events\n";
#--------TOTAL EVENTS-------------------------------
##iteration 1
##$test = "ls $dir"."/root*/*"."$jobID"."_?.root";
##@files = `$test`;
##$nfiles = $#files;
##print "$nfiles files to resubmit\n";
#$nEvents = 0;
#for($i=0;$i<=$nfiles;$i++){  
#  chomp($files[$i]);
#  $command = "root4star -b -q eventcountTotal.C\'(\"$files[$i]\")\'";
#  @test = `$command`;
#  $ntest = $#test;
#  for($j=0;$j<=$ntest;$j++){  
#    if($test[$j] =~ "events"){
#      #print "$test[$j]\n";
#      ($neve,$garb) = split(" ",$test[$j]);
#      #print "Events: $neve\n";
#      $nEvents += $neve;
#    }
#  }
#  #print "$command\n";
#}
print "$nGoodEvents good events\n";
print "$nEventsCent 0-10% events\n";
print "$nEventsMid 10-30% events\n";
print "$nEventsPeriph 30-60% events\n";
#print "$nEvents total events\n";
