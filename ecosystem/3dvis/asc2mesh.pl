#!/usr/bin/perl

open(ASC, "<ground2.asc");
$ncols = <ASC>;
$nrows = <ASC>;
$xllcorner = <ASC>; $xllcorner = -125;
$yllcorner = <ASC>; $yllcorner = -75;
$cellsize = <ASC>;  $cellsize  = 1; 
$NODATA_value = <ASC>;
@asc = <ASC>; # rest = actual data
close(ASC);


$x = $xllcorner;
$y = $yllcorner; 
for ($i = 0; $i <= $#asc; $i++) {
    $x = $xllcorner;
    @values = split ' ', $asc[$i];
    for ($j = 0; $j <= $#values; $j++) {
	$z = $values[$j] * 1.0;
	print "v $x $z $y\n";
	$x = $x + $cellsize;
    }
    $y = $y + $cellsize;
}

for ($i = 0; $i <= ($#asc-1); $i++) {
    @values = split ' ', $asc[$i];

 #   print "vv @values\n";
    
    for ($j = 0; $j < ($#values); $j++) {
	$a = $j+($i*($#values+1)) +1;
	$b = $a+1;
	$c = $a+($#values+1);
	$d = $c + 1;
	print "f $b $a $d\n";
	print "f $d $a $c\n";
    }
}

print "\n";
