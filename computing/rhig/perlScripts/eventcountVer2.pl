#!/bin/perl
$jobID = "AB494D5652576E9B68D9CAC92C035970";
$logDir = "/data3/nattrass/CuCu200/logMinBias";
$rootDir = "/data3/nattrass/CuCu200/rootMinBias";
$rootName = "CuCu-correlation-";

$testname = "$rootDir/$rootName$jobID"."*";
@rootfiles = `ls $testname`;
$nFiles = $#rootfiles;
#initialize the number of passed and failed events
$npassed = 0;
$nfailed = 0;
$ntotal = 0;
print "Number of events processed by job $jobID\n";
for($i=0;$i<$nFiles;$i++){
  ($garb,$num) = split("_",$rootfiles[$i]);
  ($num,$garb) = split(".root",$num);
 #print "|$num|\n";
  $logfile = "$logDir/$jobID"."_"."$num".".log";
  #print "$logfile\n";
  @TotalArray = ` grep 'StQAInfo: QAInfo: Done with Event ' $logfile`;
  $ntotFile = $#TotalArray;

  @PassArray=`grep v0s $logfile`;
  $npassFile = $#PassArray;
  $nfailedFile = $ntotFile -$npassFile;
  print "File $num Total $ntotFile Passed $npassFile Failed $nfailedFile\n";
  $npassed += $npassFile;
  $nfailed += $nfailedFile;
  $ntotal += $ntotFile;
}
print "===================================================\n";
print "Total: $ntotal  Passed: $npassed  Failed: $nfailed\n";
#$start = 0;
#$finish = 871;
#for($i = $start; $i<=$finish;$i++){
#	$testLogFile = "$logDir/"."$jobID"."_"."$i.log";
#	$testRootFile = "$rootDir/$rootName$jobID"."_"."$i.root";
#	#print "$testLogFile\n";
#	$test1 = `ls $testRootFile`;
#	print "$test1\n";
#}
