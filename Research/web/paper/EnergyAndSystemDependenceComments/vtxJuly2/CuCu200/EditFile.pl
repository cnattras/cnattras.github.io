#!/bin/perl
$histo = $ARGV[0];
$zbin = $ARGV[1];
$function = $ARGV[2];
$infilename = "VtxCutBin$zbin$histo".".C";
#print "Input file $infilename will have the function $function added to it\n";
$outfilename = "$infilename".".new";
print "cp $outfilename $infilename\n";

open (IN, "<$infilename") or die "Can't open $infilename: $!\n";
open (OUT, ">$outfilename") or die "Can't open $outfilename: $!\n";
print OUT "TH1D *$function(float max, float min)";
while ( $line = <IN> ) {
	print OUT "$line";
	($garb,$test) = split("->","$line");
	if($test =~"SetStats"){
	  #print "We have a winner\n";
#add these lines to the file
	  print OUT "   TH1D *histo = $histo;\n";
	  print OUT "   histo->Rebin(4);\n";
   	  print OUT "   histo->Scale(1.0/4.0);\n";
#	  print OUT "   TF1 *bkgd = new TF1("bkgd","([2]/sqrt(2*acos(-1))/[1])*exp((-1.*pow((x-[3]),2))/(2*(pow([1],2))))+[0]",-1.99,1.99);";
#	  print OUT "   bkgd->SetParameter(0,13.68641);\n";
#	  print OUT "   histo->Add(bkgd,-1);\n";
	  print OUT "   histo->SetMaximum(max);\n";
	  print OUT "   histo->SetMinimum(min);\n";
	  print OUT "   histo->Draw();\n";
#   CorrJetdEtaMethodCanvas->SaveAs(Form("VtxCutBinn14%s.png",histo->GetName()));
 	  print OUT "  return histo;\n";
	}
}


close IN;
close OUT;
