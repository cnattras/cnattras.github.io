#!/opt/star/sl302_gcc323/bin/perl
@dir_array  = `ls *.png`;
$max_lines = $#dir_array;
for ($i=0; $i <=$max_lines; $i++) # Loop through all lines
  {
($epsname, $garb) = split("\n",$dir_array[$i]);
($gifname, $garb)  = split ("png",$dir_array[$i]);
$gif = "eps";
$gifname = $gifname.$gif;#"." concatenates
system "convert $epsname $gifname";
print "converted $epsname to $gifname\n";

  }
