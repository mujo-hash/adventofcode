use v6;

my @lines = "../input/day02.txt".IO.lines;


# read lines into a key value array, where the key is forward|up|down and the value is the amount.
# iterate through the list and apply each operation to forward count and up|down count.

sub totalDistance(@input){
    my $horizontal = 0;
    my $depth = 0;

    for @input -> $line {
	my @split = split(" ", $line);
	if "forward" (elem) @split {
	    $horizontal += @split[1];
	} elsif "up" (elem) @split {
	    $depth -= @split[1];
	} elsif "down" (elem) @split {
	    $depth += @split[1];
	} else {
	    say "unexpected line: $line\n";
	}
    }

    return ($horizontal, $depth);
}

sub totalAimDistance(@input) {
    my $horizontal = 0;
    my $depth = 0;
    my $aim = 0;

    for @input -> $line {
	my @split = split(" ", $line);
	if "forward" (elem) @split {
	    $horizontal += @split[1];
	    $depth += $aim * @split[1];
	} elsif "up" (elem) @split {
	    $aim -= @split[1];
	} elsif "down" (elem) @split {
	    $aim += @split[1];
	} else {
	    say "unexpected line: $line\n";
	}
    }
    return ($horizontal, $depth);
}

say [*] totalDistance(@lines);
say [*] totalAimDistance(@lines);
