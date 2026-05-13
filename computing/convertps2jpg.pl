#!/opt/star/sl302_gcc323/bin/perl
system "rm *.jpg";
@ps_array  = `ls *.ps`;
$num_ps = $#ps_array;
for ($i=0; $i <=$num_ps; $i++) # Loop through all lines
  {
($psname, $garb) = split("\n",$ps_array[$i]);
($jpgname, $garb)  = split ("ps",$ps_array[$i]);
$jpg = "jpg";
$jpgname = $jpgname.$jpg;#"." concatenates
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

