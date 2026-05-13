#!/opt/star/sl302_gcc323/bin/perl
@dir_array  = `ls *.ps`;
$max_lines = $#dir_array;
for ($i=0; $i <=$max_lines; $i++) # Loop through all lines
  {
($psname, $garb) = split("\n",$dir_array[$i]);
($gifname, $garb)  = split ("ps",$dir_array[$i]);
$gif = "gif";
$gifname = $gifname.$gif;#"." concatenates
system "convert $psname $gifname:page";
print "converted $psname to $gifname\n";

  }
