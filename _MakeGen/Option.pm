#!/usr/bin/perl

use strict;
use warnings;
use Log;

package Option;

our $OBJECTS_MARK	= "OBJECTS";
our $LIBRARIES_MARK	= "LIBRARIES";
our $CC_MARK		= "CC";
our $CFLAGS_MARK	= "CFLAGS";
our $BIN_MARK		= "BIN";

our $PLUGIN_DIR		= "plugins";

our %EXTENSIONS = (
	".cpp"	=>	$OBJECTS_MARK,
	".hpp"	=>	$LIBRARIES_MARK,
);

sub AddOption(@) {
	my $cmd = shift;
	my $postcmd = shift;
	my $text = shift;
	$text = "\n$cmd : $postcmd\n\t$text\n";
	my $separator = "\n=============================================================";
	Log::Write("$separator\n\tAdded option ".Log::Highlight($cmd).":\t$postcmd\n\t\t$text$separator");
	return $text;
}

sub Declare(@) {
	my $CC		= shift;
	my $CFLAGS	= shift;
	my $BIN		= shift;
	my $DIR		= shift;
	my $REL		= shift;

	my $declare;

	my $OBJECTS;
	my $LIBRARIES;
	my @tmp;
	while( (my $key, my $category) = each %EXTENSIONS) {
		my $output_file = $key."files";
		$output_file =~ s/^.//g;
		my $outputlist = "$category = ".File::ReadFile($DIR, $REL, $key, $output_file);
		unshift @tmp, $outputlist;
	}
	$OBJECTS	= shift @tmp;
	$LIBRARIES	= shift @tmp;

	$declare = $declare.$OBJECTS;
	$declare = $declare.$LIBRARIES;
	$declare = $declare."$CC_MARK=\"$CC\"\n";
	$declare = $declare."$CFLAGS_MARK=\"$CFLAGS\"\n";
	$declare = $declare."$BIN_MARK=\"$BIN\"\n";
	Log::Write("Declared variable ".Log::Highlight("$OBJECTS_MARK=$OBJECTS"));
	Log::Write("Declared variable ".Log::Highlight("$LIBRARIES_MARK=$LIBRARIES"));
	Log::Write("Declared variable ".Log::Highlight("$CC_MARK=\"$CC\""));
	Log::Write("Declared variable ".Log::Highlight("$CFLAGS_MARK=\"$CFLAGS\""));
	Log::Write("Declared variable ".Log::Highlight("$BIN_MARK=\"$BIN\""));
	return $declare
}

sub GetPlugins(@) {
	my $DIR		= shift;
	my $REL		= shift;

	my $SCRIPT_KEY		= ".sh";

	my $output_file = $SCRIPT_KEY."files";
	$output_file =~ s/^.//g;

	my $plugins	= File::ReadFile($DIR, $PLUGIN_DIR, $SCRIPT_KEY, $output_file)." ";
	$plugins	=~ s/[\n\r]//g;
	my @plugins	= split(".sh ", $plugins);
	return @plugins;
}

sub Separate(@) {
	my $section = shift;

	my $SEPARATOR	= "⚌" x 40;
	my $append;
	for(my $i = 0; $i < (20 - length($section))/2; ++$i) {
		$append = $append."⚌";
	}
	return "\n#$SEPARATOR$append$section$append$SEPARATOR\n\n"
}

1;
