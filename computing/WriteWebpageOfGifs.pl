#!/usr/bin/perl
system " ls *.gif > listofps.txt";

unless($#ARGV==0){
print "Wrong number of parameters.";
die;
}
$INFILENAME = "listofps.txt";
$OUTFILENAME = $ARGV[0];

open (PICFILES, "<$INFILENAME") || die "Can't open configuration file $INFILENAME.\n";
open(OUTFILE, ">$OUTFILENAME");
print "Writing $OUTFILENAME from $INFILENAME.\n";
#intro lines in the html file
print OUTFILE "<meta content=\"text/html; charset=ISO-8859-1\" http-equiv=\"content-type\"><title>$OUTFILENAME</title></head>\n";
print OUTFILE "<body><br>\n";
while (<PICFILES>) # while there are still lines in the file PICFILES
  {# here write HTML lines that print the pictures
    ($data,$garb) = split ("#",$_);
    ($data, $garb)  = split ("\n",$data);
print OUTFILE "<a href=\"$data\">$data</a><br>\n";
  }

print OUTFILE "</body></html>\n";

close (OUTFILE);


   






