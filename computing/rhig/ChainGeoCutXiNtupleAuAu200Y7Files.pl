#!/usr/bin/perl
#This file was originally written by Jana Bielcikova and was mutated by Christine Nattrass
#This is for chaining together files which contain TTrees.  It will not copy over histograms properly.
#You need to change the
#1.  Macro to load libraries (roughly line 13)
#2.  Input directory/output (roughly lines 16 & 18)
#3.  Macro name and location (roughly lines 25 & 120)
#to test without running comment out the line beginning with "system" at approximately line 120


#shared libraries necessary to read your TTrees.  If your TTrees contain TObjects, this should contain the header for the TObjects stored in the TTrees
$loadSharedLibraries = "~nattrass/AzimuthalCorrelations/macros/loadHighPtLibraries.C";

#the command below should return the fiels which need to be chained together
@dir_array  = `ls /data1/nattrass/AuAu200Y7/geoCuts/xi*.root`;
#Below is the name of the file you would like to make
$outfile = "~nattrass/AzimuthalCorrelations/rootFiles/xiNtupleAuAu200Y7.root";

$max_lines = $#dir_array; 

#Note:  this always undercounts by one since the counting starts at zero
print "$max_lines files will be added together ... \n";

#name of macro you're using is set here
open (OUTFILE, ">/tmp/haddqa.C");
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

print OUTFILE "void haddqa() {\n";
print OUTFILE "gROOT->Reset()\;\n";
print OUTFILE "gROOT->LoadMacro(\"$loadSharedLibraries\")\;\n";

print OUTFILE "loadHighPtLibraries()\;\n";
print OUTFILE "TChain *chain1 = new TChain(\"Xi\")\;\n";

for ($i=0; $i <=$max_lines; $i++) # Loop through all lines
{
    ($fname, $garb)  = split ("\n",$dir_array[$i]);
    print OUTFILE "chain1->Add(\"$fname\")\;\n";
}
print OUTFILE "TFile* file = new TFile(\"$outfile\",\"RECREATE\");\n";
print OUTFILE "chain1->Merge(file,10000,\"keep\");\n";
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

#And this has to be the name of the macro...
system "root4star -b -q /tmp/haddqa.C";


   






