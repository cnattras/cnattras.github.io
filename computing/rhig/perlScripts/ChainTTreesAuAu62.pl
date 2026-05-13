#!/usr/bin/perl


$inputDir = "/data1/nattrass/AuAu62/rootMinBias";
$outputDir = "/data4/nattrass/AuAu62/TTreesMinBias";
$loadSharedLibraries = "~nattrass/HighPtVer3/macros/loadHighPtLibraries.C";
#$dirData = "/data4/nattrass/CuCu200_P06ic/rootMinBias";
#@dir_array  = `ls $inputDir/*_????.root`;
@dir_array = `cat $inputDir/filelist.txt`;

$max_lines = $#dir_array; 
#this is the starting file number minus 1
$firstFile = 1;
$id=$firstFile-1;
$nFiles=0;
system "rm /tmp/*.C";
for ($i=0; $i <=$max_lines; $i++) # Loop through all lines
  {
    if ($i%6==0) {
	$nFiles++;
      print OUTFILE "chain.Merge(\"$outputDir/files$id.root\");\n";
      
      print OUTFILE "}\n";

      close (OUTFILE);
      $id=$id+1;
      open (OUTFILE, ">/tmp/hrootlambda$id.C");
      print OUTFILE "#include <string.h>\n";
      print OUTFILE "#include \"TChain.h\"\n";
      print OUTFILE "#include \"TFile.h\"\n";
      print OUTFILE "#include \"TH1.h\"\n";
      print OUTFILE "#include \"TTree.h\"\n";
      print OUTFILE "#include \"TKey.h\"\n";
      print OUTFILE "#include \"Riostream.h\"\n";
      print OUTFILE "void hrootlambda$id() {\n";
      
      print OUTFILE "gROOT->Reset()\;\n";
      print OUTFILE "gROOT->LoadMacro(\"$loadSharedLibraries\")\;\n";
      
      print OUTFILE "loadHighPtLibraries()\;\n";
      #print OUTFILE "gSystem->Load(\"StJet\")\;\n";
      
      print OUTFILE "TEvent *event = new TEvent()\;\n";  
      print OUTFILE "TChain chain(\"Correlation\")\;\n";
    }

    ($fname, $garb)  = split ("\n",$dir_array[$i]);
    print OUTFILE "chain.Add(\"$fname\")\;\n";
  }

print OUTFILE "chain.Merge(\"$outputDir/files$id.root\");\n";
print OUTFILE "}\n";

close (OUTFILE);


for ($i=$firstFile; $i <$firstFile+$nFiles; $i++) # Loop through all lines
  {
#    system "root4star -b -q /tmp/hrootlambda$i.C >& /dev/null\n";
    system "root4star -b -q /tmp/hrootlambda$i.C";
  }

print "nFiles $nFiles\n";


