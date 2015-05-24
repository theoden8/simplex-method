#!/usr/bin/perl

use strict;
use warnings;
use Log;

package Option;

our $SHELL_MARK		= "SHELL";
our $CXX_MARK		= "CXX";
our $CXXFLAGS_MARK	= "CXXFLAGS";
our $BIN_MARK		= "BIN";
our $OBJECTS_MARK	= "OBJECTS";
our $LIBRARIES_MARK	= "LIBRARIES";

our $PLUGIN_DIR		= "plugins";

sub Declare(@) {
	my ($NAME, $VALUE)	= @_;
	my $TEXT = $NAME." "x(10 - length($NAME))."= ".$VALUE;
	chomp($TEXT);
	Log::Write("Declared Variable:\n\t\t".Log::Highlight($TEXT));
	return "$TEXT\n";
}

sub AddOption(@) {
	my $cmd = shift;
	my $postcmd = shift;
	my $text = shift;
	$text = "\n$cmd : $postcmd\n\t$text\n";
	my $separator = "\n"."=" x 140;
	Log::Write(Log::Highlight("\U$cmd\E")."$separator\n\t\t$text$separator");
	return $text;
}

sub AddPlugins(@) {
	my ($DIR, $REL)	 = @_;

	my $plugins	= File::ReadFile($DIR, $PLUGIN_DIR, "sh");
	chomp($plugins);
	my @plugins	= split(".sh ", $plugins);
	my @opts;
	foreach my $plugin(@plugins) {
		my $plugin_filename = (split ("/", $plugin))[-1];
		Log::Write("Adding plugin ".Log::Highlight($plugin));
		my $EXEC_DIR = "$DIR/$PLUGIN_DIR"."/".(substr($plugin, 0, (length($plugin) - length($plugin_filename) - 1)));
		push(@opts, Option::AddOption(
			(split ("/", $plugin))[0], "",
			"bash \"$EXEC_DIR/$plugin_filename\" \"$EXEC_DIR\"",
		));
	}
	return @opts;
}

sub AddSeparator(@) {
	my $section = shift;

	my $SEPARATOR	= "⚌" x 40;
	my $append;
	for(my $i = 0; $i < (20 - length($section))/2; ++$i) {
		$append = $append."⚌";
	}
	return "\n#$SEPARATOR$append$section$append$SEPARATOR\n\n"
}

1;
