#!/usr/bin/perl

#change these lines to change the:
#output directory
$outfiledir = "/data3/nattrass/sevil/partialChainedStep2";
#directory where scripts will be written
$workingdir = "/data3/nattrass/sevil";
#input file list
@dir_array  = `ls /data3/nattrass/sevil/partialChained/*short*.root`;

#don't change this line
$max_lines = $#dir_array; 

#this is the starting file number minus 1
$firstFile = 0;
#don't touch this line
$id=$firstFile-1;

#change this line to change the number of files grouped together
$nFilesToChain = 10;

$nFiles=0;
#=====================Loop==========================================
print "$max_lines files will be added together ... \n";
for ($i=0; $i <=$max_lines; $i++) # Loop through all lines
  {
    if ($i%$nFilesToChain==0) {
      $nFiles++;

      print OUTFILE "MergeRootfile( Target, FileList );\n";
      print OUTFILE "\}\n";
      print OUTFILE "void MergeRootfile( TDirectory *target, TList *sourcelist )\{\n";
      print OUTFILE "TString path( (char*)strstr( target->GetPath(), \":\" ) );\n";
      print OUTFILE "path.Remove( 0, 2 );\n";
      print OUTFILE "TFile *first_source = (TFile*)sourcelist->First();\n";
      print OUTFILE "first_source->cd( path );\n";
      print OUTFILE "TDirectory *current_sourcedir = gDirectory;\n";
      print OUTFILE "TChain *globChain = 0;\n";
      print OUTFILE "TIter nextkey( current_sourcedir->GetListOfKeys() );\n";
      print OUTFILE "TKey *key;\n";
      print OUTFILE "while ( (key = (TKey*)nextkey())) {\n";
      print OUTFILE "first_source->cd( path );\n";
      print OUTFILE "TObject *obj = key->ReadObj();\n";
      print OUTFILE "if ( obj->IsA()->InheritsFrom( \"TH1\" ) ) {\n";
      print OUTFILE "TH1 *h1 = (TH1*)obj;\n";
      print OUTFILE "TFile *nextsource = (TFile*)sourcelist->After( first_source );\n";
      print OUTFILE "while ( nextsource ) {\n";
      print OUTFILE "nextsource->cd( path );\n";
      print OUTFILE "TH1 *h2 = (TH1*)gDirectory->Get( h1->GetName() );\n";
      print OUTFILE "if ( h2 ) {\n";
      print OUTFILE "h1->Add( h2 );\n";
      print OUTFILE "delete h2; \n";
      print OUTFILE "}\n";
      print OUTFILE "nextsource = (TFile*)sourcelist->After( nextsource );\n";
      print OUTFILE "}\n";
      print OUTFILE "}\n";
      print OUTFILE "else if ( obj->IsA()->InheritsFrom( \"TTree\" ) ) {\n";
      print OUTFILE "const char* obj_name= obj->GetName();\n";
      print OUTFILE "globChain = new TChain(obj_name);\n";
      print OUTFILE "globChain->Add(first_source->GetName());\n";
      print OUTFILE "TFile *nextsource = (TFile*)sourcelist->After( first_source );\n";
      print OUTFILE "while ( nextsource ) {\n";
      print OUTFILE "globChain->Add(nextsource->GetName());\n";
      print OUTFILE "nextsource = (TFile*)sourcelist->After( nextsource );\n";
      print OUTFILE "}\n";
      print OUTFILE "} else if ( obj->IsA()->InheritsFrom( \"TDirectory\" ) ) {\n";
      print OUTFILE "cout << \"Found subdirectory\" << obj->GetName() << endl;\n";
      print OUTFILE "target->cd();\n";
      print OUTFILE "TDirectory *newdir = target->mkdir( obj->GetName(), obj->GetTitle() );\n";     
      print OUTFILE "MergeRootfile( newdir, sourcelist );\n";
      print OUTFILE "} else {\n";
      print OUTFILE "cout << \"Unknown object type, name: \"\n";
      print OUTFILE "    << obj->GetName() << \" title: \" << obj->GetTitle() << endl;\n";
      print OUTFILE "}\n";
      print OUTFILE " if ( obj ) {\n";
      print OUTFILE "target->cd();\n";
      print OUTFILE "if(obj->IsA()->InheritsFrom( \"TTree\" ))\n";
      print OUTFILE "globChain->Write( key->GetName() );\n";
      print OUTFILE "else\n";
      print OUTFILE "obj->Write( key->GetName() );\n";
      print OUTFILE "}\n";
      print OUTFILE "}\n";
      print OUTFILE "target->Write();\n";
      print OUTFILE "}\n";      
      close (OUTFILE);
      $id=$id+1;
      
      $outfile = "$outfiledir/ridgefiles$id.root";
      open (OUTFILE, ">$workingdir/haddqa$id.C");
      print OUTFILE "#include <string.h>\n";
      print OUTFILE "#include \"TChain.h\"\n";
      print OUTFILE "#include \"TFile.h\"\n";
      print OUTFILE "#include \"TH1.h\"\n";
      print OUTFILE "#include \"TTree.h\"\n";
      print OUTFILE "#include \"TKey.h\"\n";
      print OUTFILE "#include \"Riostream.h\"\n";
      print OUTFILE "TList *FileList;\n";
      print OUTFILE "TFile *Target;\n";
      print OUTFILE "void MergeRootfile( TDirectory *target, TList *sourcelist );\n";

      print OUTFILE "void haddqa$id() {\n";
      print OUTFILE "Target = TFile::Open(\"$outfile\", \"RECREATE\" );\n";

      print OUTFILE "FileList = new TList();\n";
    }
#for ($i=0; $i <=$max_lines; $i++) # Loop through all lines
#{
    ($fname, $garb)  = split ("\n",$dir_array[$i]);
    print OUTFILE "FileList->Add( TFile::Open(\"$fname\") );\n";
  }
#}
#==========Finishing last file===========================
      print OUTFILE "MergeRootfile( Target, FileList );\n";
      print OUTFILE "\}\n";
      print OUTFILE "void MergeRootfile( TDirectory *target, TList *sourcelist )\{\n";
      print OUTFILE "TString path( (char*)strstr( target->GetPath(), \":\" ) );\n";
      print OUTFILE "path.Remove( 0, 2 );\n";
      print OUTFILE "TFile *first_source = (TFile*)sourcelist->First();\n";
      print OUTFILE "first_source->cd( path );\n";
      print OUTFILE "TDirectory *current_sourcedir = gDirectory;\n";
      print OUTFILE "TChain *globChain = 0;\n";
      print OUTFILE "TIter nextkey( current_sourcedir->GetListOfKeys() );\n";
      print OUTFILE "TKey *key;\n";
      print OUTFILE "while ( (key = (TKey*)nextkey())) {\n";
      print OUTFILE "first_source->cd( path );\n";
      print OUTFILE "TObject *obj = key->ReadObj();\n";
      print OUTFILE "if ( obj->IsA()->InheritsFrom( \"TH1\" ) ) {\n";
      print OUTFILE "TH1 *h1 = (TH1*)obj;\n";
      print OUTFILE "TFile *nextsource = (TFile*)sourcelist->After( first_source );\n";
      print OUTFILE "while ( nextsource ) {\n";
      print OUTFILE "nextsource->cd( path );\n";
      print OUTFILE "TH1 *h2 = (TH1*)gDirectory->Get( h1->GetName() );\n";
      print OUTFILE "if ( h2 ) {\n";
      print OUTFILE "h1->Add( h2 );\n";
      print OUTFILE "delete h2; \n";
      print OUTFILE "}\n";
      print OUTFILE "nextsource = (TFile*)sourcelist->After( nextsource );\n";
      print OUTFILE "}\n";
      print OUTFILE "}\n";
      print OUTFILE "else if ( obj->IsA()->InheritsFrom( \"TTree\" ) ) {\n";
      print OUTFILE "const char* obj_name= obj->GetName();\n";
      print OUTFILE "globChain = new TChain(obj_name);\n";
      print OUTFILE "globChain->Add(first_source->GetName());\n";
      print OUTFILE "TFile *nextsource = (TFile*)sourcelist->After( first_source );\n";
      print OUTFILE "while ( nextsource ) {\n";
      print OUTFILE "globChain->Add(nextsource->GetName());\n";
      print OUTFILE "nextsource = (TFile*)sourcelist->After( nextsource );\n";
      print OUTFILE "}\n";
      print OUTFILE "} else if ( obj->IsA()->InheritsFrom( \"TDirectory\" ) ) {\n";
      print OUTFILE "cout << \"Found subdirectory\" << obj->GetName() << endl;\n";
      print OUTFILE "target->cd();\n";
      print OUTFILE "TDirectory *newdir = target->mkdir( obj->GetName(), obj->GetTitle() );\n";     
      print OUTFILE "MergeRootfile( newdir, sourcelist );\n";
      print OUTFILE "} else {\n";
      print OUTFILE "cout << \"Unknown object type, name: \"\n";
      print OUTFILE "    << obj->GetName() << \" title: \" << obj->GetTitle() << endl;\n";
      print OUTFILE "}\n";
      print OUTFILE " if ( obj ) {\n";
      print OUTFILE "target->cd();\n";
      print OUTFILE "if(obj->IsA()->InheritsFrom( \"TTree\" ))\n";
      print OUTFILE "globChain->Write( key->GetName() );\n";
      print OUTFILE "else\n";
      print OUTFILE "obj->Write( key->GetName() );\n";
      print OUTFILE "}\n";
      print OUTFILE "}\n";
      print OUTFILE "target->Write();\n";
      print OUTFILE "}\n";      
close (OUTFILE);

print "This will make $nFiles output files\n";


#change the number of hosts in this array to add or delete machines
#@host = ("irhig02","irhig03","irhig04","irhig05","irhig06","irhig07","irhig02","irhig03","irhig04","irhig05","irhig06","irhig07");
#$imaxhost=12;
#@host = ("irhig03","irhig04","irhig05","irhig06","irhig07","irhig03","irhig04","irhig05","irhig06","irhig07");
#$imaxhost=10;
#@host = ("irhig02","irhig05","irhig06","irhig07");
#$imaxhost=4;
@host = ("irhig02","irhig03","irhig04","irhig05","irhig06","irhig07");
$imaxhost=6;

$nBunch=int($nFiles/$imaxhost);
$nAboveBunch=$nFiles-$imaxhost*$nBunch;

#making output directory
open (OUTFILE, ">$workingdir/submit.pl");
print OUTFILE  "#!/usr/bin/perl\n";
print OUTFILE "\$min = \$ARGV[0];\n";
print OUTFILE "\$max = \$ARGV[1];\n";
print OUTFILE "for (\$i=\$min;\$i<=\$max;\$i++) {\n";
print OUTFILE "system \"root4star -b -q $workingdir/haddqa\$i.C >& $workingdir/haddqa\$i.log\";\n";
print OUTFILE "}\n";
close (OUTFILE);

#submitting files to nodes
$username= `whoami`; # contains end of line character !!! We have to get rid of it ...
($username,$garb) = split("\n",$username);


$nToRun = $nFiles;
$nExcess = $nAboveBunch;
print "The number of files per bunch is $nBunch and the number of excess files is $nExcess\n";
for ($i=0; $i<$imaxhost; $i++) {
  if($nExcess>0){
    $begin = $firstFile+$nToRun-$nBunch-1;
    $end = $firstFile+$nToRun-1;
    #print "/usr/bin/ssh -l $username $host[$i] -q perl $workingdir/submit.pl $begin $end &\n";
    print "node $host[$i] will run jobs $begin to $end\n";
    system "/usr/bin/ssh -l $username $host[$i] -q perl $workingdir/submit.pl $begin $end &";
    $nToRun += -$nBunch-1;
    $nExcess--;
  }
  else{
    $begin = $firstFile+$nToRun-$nBunch;
    $end = $firstFile+$nToRun-1;
    #print "/usr/bin/ssh -l $username $host[$i] -q perl $workingdir/submit.pl $begin $end &\n";
    print "node $host[$i] will run jobs $begin to $end\n";
    system "/usr/bin/ssh -l $username $host[$i] -q perl $workingdir/submit.pl $begin $end &";
    $nToRun += -$nBunch;
  }
}
   






