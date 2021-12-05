use v6;

use Test;

my @lines = "../input/day03.txt".IO.lines;

sub powerConsumption(@input) {
    my $gamma = 0;
    my $epsilon = 0;
    my @count = 0;

    for @input -> $line {
        my $comb = $line.comb;
	@count = @count <<+<< $comb;
	say @count;
    }
    my @ave = (@count >>/>> @input.elems)>>.round;
    $gamma = ([~] @ave).parse-base(2);
    $epsilon = ([~] (!<<@ave)>>.Int).parse-base(2);

    return $gamma * $epsilon;
}

my $testinput = "00100
11110
10110
10111
10101
01111
00111
11100
10000
11001
00010
01010";

my @testlines = $testinput.lines;
is powerConsumption(@testlines), 198;

say powerConsumption(@lines);
