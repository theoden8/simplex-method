#!/usr/bin/perl

package File;

use strict;
use warnings;

use Log;
use Option;

sub ReadFile(@) {
	my $DIR = shift;
	my $REL = shift;
	my $extension = shift;
	my $output_file = shift; $output_file = "$REL/$output_file";

	system("cd \"$DIR/$REL\"; find .  | sed 's/^\\\.\\\///g' | grep \"$extension\$\" | grep -v \"$output_file\" | sed 's/ /\\\ /g' > \"$DIR/$output_file\"");
	system("echo \$(cat \"$output_file\") > \"$output_file\"");
	Log::Write("Collecting all files with ".Log::Highlight($extension)." extention to file ".Log::Highlight($output_file).".");
	open INFILE, "$output_file";
	Log::Write("File ".Log::Highlight($output_file)." is opened for ".Log::Highlight("READING")) or die "Could not open file.";
	my $text;
	while(<INFILE>) {
		if($_ eq $output_file) {
			continue;
		}
		$text = $text.$_;
	}
	close INFILE;
	system("srm \"$output_file\"");
	Log::Write("Deleted file ".Log::Highlight($output_file).".");
	return $text;
}

sub WriteFile(@) {
	my $DIR		= shift;
	my $REL		= shift;
	my $main	= shift;
	my $MAKEFILE	= "$DIR/$REL/".shift;
	my $binary	= shift;
	my $perlscript = $0;

	# make options:
	my @OPTIONS = (
		Option::Separate("DECLARATION"),
		my $declare	= Option::Declare	(
			"g++ -std=c++0x -Wno-deprecated",
			"-framework OpenGL -framework GLUT",
			$binary,
			$DIR,
			$REL
		),
		Option::Separate("MAIN"),
		Option::AddOption	(
			"all",		"\$($Option::OBJECTS_MARK) \$($Option::LIBRARIES_MARK)",
			"\$($Option::CC_MARK) \$(".$Option::EXTENSIONS{".cpp"}.") -o \"\$($Option::BIN_MARK)\" \$($Option::CFLAGS_MARK)",
		),
		Option::AddOption	(
			"compile",,
			"\$($Option::CC_MARK) -std=c++0x -Wno-deprecated \"$main\" -o \"\$($Option::BIN_MARK)\" \$($Option::CFLAGS_MARK)",
		),
		Option::AddOption	(
			"run",,
			"./\"\$($Option::BIN_MARK)\"",
		),
		Option::AddOption	(
			"remake",,
			"cd \"$DIR\"".								"&& \\".
			"\n\tperl \"$perlscript\" \"$REL\" \"$main\" \"$binary\"".		"&& \\".
			"\n\tcd \"$REL\"",
		),
		Option::AddOption	(
			"open",,
			"vim -p *.hpp",
		),
		Option::Separate("PLUGINS"),
	);

	my @PLUGINS	= Option::GetPlugins($DIR, $REL);
	foreach my $plugin(@PLUGINS) {
		my $EXEC_DIR = "$DIR/$Option::PLUGIN_DIR";
		my $plugin_filename = (split ("/", $plugin))[-1];
		$EXEC_DIR = $EXEC_DIR.(substr $plugin, 0, (length($plugin) - length($plugin_filename)));
		push @OPTIONS,	Option::AddOption(
			(split ("/", $plugin))[0], "",
			"bash \"$EXEC_DIR/$plugin_filename.sh\" \"$EXEC_DIR\"",
		);
	}

	open OUTFILE, ">$MAKEFILE";
	Log::Write("File ".Log::Highlight($MAKEFILE)." is opened for ".Log::Highlight("REWRITING.")) or die "Could not open file.";
	my $text;
	for my $each(@OPTIONS) {
		$text = $text.$each;
	}
	print OUTFILE $text;
	close OUTFILE;
}

1;
