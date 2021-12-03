use v6;

my @input = "../input/day01.txt".IO.lines;
my $pline = "";
my $ppline = "";
my $pppline = "";

my $acount = 0;
my $bcount = 0;

for @input -> $line {
    if $pline == "" {
        $pline = $line;
        next;
    }
    if $line - $pline > 0 { # increased
        $acount++;
    }
    if $ppline == "" {
	$ppline = $pline;
	$pline = $line;
	next;
    }
    if $pppline == "" {
	$pppline = $ppline;
	$ppline = $pline;
	$pline = $line;
	next;
    }
    if $line - $pppline > 0 {
	$bcount++;
    }
    $pppline = $ppline;
    $ppline = $pline;
    $pline = $line;
}

say "part1: there were $acount increases\n";
say "part2: there were $bcount increases\n";
