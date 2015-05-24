#!/usr/bin/perl

use strict;

package Log;

our   $bcolor = "\e[033;40m";

our   $fcolor = "\e[033;92m";
our   $fsystem = "\e[033;93m";
our   $fhlight = "\e[095;96m";

our   $freset = "\e[033;0m";
our   $fbold = "\e[033;1m";
our   $fundl = "\e[033;4m";
our   $fblink = "\e[033;5m";

sub Format(@) {
	my $codes	= shift;
	return "\033[0;$codes";
}

sub Log(@) {
	my $background = shift;
	my $foreground = shift;
	print $background.$foreground;
	foreach my $word(@_) {
		print $word;
	}
	print $freset."\n";
}

sub SysLog(@) {
	Log($bcolor, $fsystem, @_);
}

sub Write(@) {
	unshift @_, "🍺\t";
	Log($bcolor, $fcolor, @_);
}

sub Highlight(@) {
	my $str;
	foreach my $word(@_) {
		$str .= $word;
	}
	return $fhlight.$str.$freset.$bcolor.$fcolor;
}

1;
