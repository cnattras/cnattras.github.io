#!/opt/star/sl302_gcc323/bin/perl
system "rm *.jpg";
@pdf_array  = `ls *.pdf`;
$num_ps = $#pdf_array;
for ($i=0; $i <=$num_ps; $i++) # Loop through all lines
  {
($pdfname, $garb) = split("\n",$pdf_array[$i]);
($jpgname, $garb)  = split ("pdf",$pdf_array[$i]);
$psname = $jpgname;
$jpg = "jpg";
$jpgname = $jpgname.$jpg;#"." concatenates
$ps = "ps";
$psname = $psname.$ps;
system "pdf2ps $pdfname";
print "converted $pdfname to $psname\n";
system "convert $psname $jpgname";
print "converted $psname to $jpgname\n";

  }


@jpg_array = `ls *.jpg*`;
$num_jpg = $#jpg_array;
for ($j=0; $j <=$num_jpg; $j++) # Loop through all lines
  {
($jpgname, $garb)  = split ("\n",$jpg_array[$j]);
($truncatedjpgname,$pagenumber)  = split (".jpg.",$jpg_array[$j]);
($truncatedjpgname, $garb)=split("\n",$truncatedjpgname);
($pagenumber, $garb)=split("\n",$pagenumber);
$page = "_page";
$jpg = ".jpg";
$newjpgname = $truncatedjpgname.$page.$pagenumber.$jpg;

if($jpgname ne $truncatedjpgname)
  {
system "cp $jpgname $newjpgname";
system "rm $jpgname";
print "copied $jpgname to $newjpgname and removed $jpgname.\n";
  }
}

