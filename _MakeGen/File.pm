#!/usr/bin/perl

package File;

use strict;
#use warnings;

use Log;
use Option;

sub ReadFile(@) {
	my($DIR, $REL, $key) = @_;

	my $output_file = "$REL/$key"."files";
	system("cd \"$DIR/$REL\"; find .  | sed 's/^\\\.\\\///g' | grep \"\.$key\$\" | grep -v \"$output_file\" | sed 's/ /\\\ /g' > \"$DIR/$output_file\"");
	system("echo \$(cat \"$output_file\") > \"$output_file\"");
	Log::Write("Collecting all files with ".Log::Highlight($key)." extention to file ".Log::Highlight($output_file).".");
	open INFILE, "$output_file";
	Log::Write("File ".Log::Highlight($output_file)." is opened for ".Log::Highlight("READING")) or die "Could not open file.";
	my $text;
	while(<INFILE>) {
		$text .= $_;
	}
	close INFILE;
	system("srm \"$output_file\"");
	Log::Write("Deleted file ".Log::Highlight($output_file).".");
	return $text;
}

sub WriteFile(@) {
	my($DIR, $REL, $MAIN, $MAKEFILE, $BIN) = @_;
	$MAKEFILE	= "$DIR/$REL/$MAKEFILE";

	my %osX_frameworks = {
		"GLUT"		=>	"-framework GLUT",
		"OpenGL"	=>	"-framework OpenGL",
	};

	# make options:
	my @OPTIONS = (
		Option::AddSeparator("DECLARATION"),

		Option::Declare($Option::SHELL_MARK,		"/bin/bash"),
		Option::Declare($Option::CXX_MARK,		"g++ -std=c++0x -Wno-deprecated"),
		Option::Declare($Option::CXXFLAGS_MARK,		"-framework OpenGL -framework GLUT"),
		Option::Declare($Option::BIN_MARK,		$BIN),
		Option::Declare($Option::OBJECTS_MARK,		File::ReadFile($DIR, $REL, "cpp")),
		Option::Declare($Option::LIBRARIES_MARK,	File::ReadFile($DIR, $REL, "hpp")),

		Option::AddSeparator("MAIN"),

		Option::AddOption	(
			"all",		"\$($Option::OBJECTS_MARK) \$($Option::LIBRARIES_MARK)",
			"\$($Option::CXX_MARK) \$($Option::OBJECTS_MARK) -o \"\$($Option::BIN_MARK)\" \$($Option::CXXFLAGS_MARK)",
		),
		Option::AddOption	(
			"compile","",
			"\$($Option::CXX_MARK) -std=c++0x -Wno-deprecated \"$MAIN\" -o \"\$($Option::BIN_MARK)\" \$($Option::CXXFLAGS_MARK)",
		),
		Option::AddOption	(
			"run","",
			"./\"\$($Option::BIN_MARK)\"",
		),
		Option::AddOption	(
			"remake","",
			"cd \"$DIR\"".								"&& \\".
			"\n\tperl \"$0\" \"$REL\" \"$MAIN\" \"$BIN\"".		"&& \\".
			"\n\tcd \"$REL\"",
		),
		Option::AddOption	(
			"open","",
			"vim -p *.hpp",
		),
		Option::AddSeparator("PLUGINS"),
	);

	push(@OPTIONS, Option::AddPlugins($DIR, $REL));

	open OUTFILE, ">$MAKEFILE";
	Log::Write("File ".Log::Highlight($MAKEFILE)." is opened for ".Log::Highlight("REWRITING.")) or die "Could not open file.";
	my $text;
	for my $each(@OPTIONS) {
		$text .= $each;
	}
	print OUTFILE $text;
	close OUTFILE;
}

1;
