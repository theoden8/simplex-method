#!/usr/bin/env perl

use strict;
use 5.16.2;

exit if(@ARGV != 2);

my($w, $h) = @ARGV;

# say join " ", @ARGV;
# say;

my @range = -15..15;

sub num { return $range[rand @range]; }

foreach my $i(0..($h - 1)) {
	foreach my $j(0..($w - 1)) {
		my $num = num();
		print $num.(" "x(4 - length($num)));
	}
	say;
}
