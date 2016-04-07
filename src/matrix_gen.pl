#!/usr/bin/env perl

use strict;
use 5.16.2;

die if(@ARGV != 2);
my($w, $h) = @ARGV;

my @range = -15..15;
# say join " ", @ARGV;
# say;

sub num { return $range[rand @range]; }

foreach my $i(0..$h) {
	foreach my $j(0..$w) {
        my $num = num();
		print $num.(" "x(4 - length($num)));
	}
	say;
}
