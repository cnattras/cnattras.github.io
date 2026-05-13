#!/usr/bin/perl

#This file was originally written by Jana Bielcikova and was mutated by Christine Nattrass
#This is for chaining together files which contain TTrees.  It will not copy over histograms properly.
#What this does is take a directory of files and chain it in smaller batches
#WARNING:  THIS IS A STUPID SCRIPT
#It will submit more jobs than a node can handle if you ask it to.  You need to be careful.  $nFilesToChain is set on roughly line 20 and this says how many files to chain into smaller chunks.  Let's say you have 1000 files and $nFilesToChain = 20 and you have 6 nodes.  Ideally since root4star is only compiled for one CPU you should submit two jobs to each node to get them to run through as fast as possible.  However, in this case you will have 50 total jobs which will be divided evenly among the nodes, meaning each node will get 8 or 9 jobs.  This will choke the node and you do not want to do this.  If you have $n files you should chain roughly $n/12 files in each chunk.  It isn't a huge deal if you submit 3 jobs to one node rather than two - although it will make your jobs run slower - but it is a huge deal if you submit 8 jobs to each node and you will regret it.
#You need to change the
#1.  Input/output directories (roughly lines 15 & 17)
#2.  Macro name and location (roughly lines 97 & 187)
#3.  The name of the TTree you are chaining (The sample in this file has the name "Xi".  This file only chains together one TTree properly.)
#to test without running comment out the lines beginning with "system" at approximately line 187
#To change the nodes which this submits to change the array and the number of nodes at approximatley lines 179 and 180

#directory for output files which are partially chained
$outfiledir = "/data3/nattrass/CuCu200/Correlations/partialChained";
#the command below should return the fiels which need to be chained together
@dir_array  = `ls /data3/nattrass/CuCu200/Correlations/correlation-part2--2*.root`;
$max_lines = $#dir_array; 

#this is the starting file number minus 1
$firstFile = 0;
$id=$firstFile-1;

#LOOOK HERE!!!!!!
#This is the line that you must pay attention to if you don't want to kill the nodes.  See the warning at the top.
$nFilesToChain = 15;

$nFiles=0;
#=====================Loop==========================================
#The lines below write the macros which will chain together the files.
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
      open (OUTFILE, ">/home/nattrass/tmp/haddqa$id.C");
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


@host = ("irhig02","irhig03","irhig04","irhig05","irhig06","irhig07","irhig02","irhig03","irhig04","irhig05","irhig06","irhig07");
$imaxhost=12;

$hostn = 0;

print "This will make $nFiles output files\n";
for ($i=$firstFile; $i <$firstFile+$nFiles; $i++) # Loop through all lines
  {
    system "/usr/bin/ssh -l nattrass $host[$hostn] -q root4star -b -q /home/nattrass/tmp/haddqa$i.C >& /home/nattrass/tmp/haddqa$i.txt &\n";
    $hostn++;
    if( $hostn == $imaxhost ){ $hostn = 0;}
  }

   






