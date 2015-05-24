#!/usr/bin/perl

use strict;

use Log;
use Option;

my $MAKEFILE	=	shift @ARGV;

if(substr($MAKEFILE, length($MAKEFILE) - length("Makefile"), length("Makefile")) ne "Makefile") {
	Log::Write("\x1b[033;91mMakefile is not specified");
	exit;
}

sub Readfile(@) {
	my $FILE	= shift;
	my $text;
	open INFILE, "$FILE";
	Log::Write("File ".Log::Highlight($FILE)." is opened for ".Log::Highlight("READING")) or die "Could not open file $FILE.";
	while(<INPUT>) {
		$text .= $_;
	}
	close INFILE;
	Log::Write("Read file ".Log::Highlight($FILE).".");
	return $text;
}

sub PerceptFile(@) {
	Log::Write("Started perception.");
	my $text	= shift;
	#
	#	Here the makefile is being percepted.
	#	To launch other file, simply do:
	#		system <interpreter/compiler> \"$MAKEFILE\" OTHERARGS;
	#		exit;
	#
	Log::Write("Completed perception.");
	return $text;
}

sub Writefile(@) {
	my $FILE	= shift;
	my $text	= shift;
	open OUTFILE, ">$FILE";
	Log::Write("File ".Log::Highlight($FILE)." is opened for ".Log::Highlight("WRITING")) or die "Could not open file $FILE.";
	print OUTFILE $text;
	close OUTFILE;
	Log::Write("Wrote file ".Log::Highlight($FILE).".");
}

Log::Write(Log::Highlight((split("/", $0))[-1])." is launched.");
eval {
	Writefile($MAKEFILE, PerceptFile(Readfile($MAKEFILE)));
}; if($@) {
	Log::Writefile("\x1b[033;91mErrors generated : \"$@\"");
}
Log::Write(Log::Highlight((split("/", $0))[-1])." is finished.");
