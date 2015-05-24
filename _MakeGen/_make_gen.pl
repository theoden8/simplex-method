#!/usr/bin/perl

use strict;
use warnings;

use Cwd;

use Log;
use Option;
use File;

my $DIR = cwd();
my $POST = "Post.pl";
$DIR	=~ s/\\/\\\\/g;
$DIR	=~ s/"/\\"/g;

Log::SysLog(		$Log::fbold.Log::Highlight("Executing the program from ")."\n\t".$Log::fundl.$Log::fblink.$Log::fsystem.$DIR	);
Log::Write(		Log::Highlight("Makefile")." generating program is started."							);

my $REL	= "..";
$REL	= shift @ARGV	if(exists $ARGV[0]);
if(
	$REL eq "~" or
	$REL eq "/"
) {
	$DIR = $REL;
	$REL = '.';
}

my $MAIN = "main.cpp";
if(exists $ARGV[0]) {
	$MAIN = shift @ARGV;
}
my $MAKEFILE = "Makefile";
my $BIN = "_bin";
if(exists $ARGV[0]) {
	$BIN = shift @ARGV;
}

File::WriteFile($DIR, $REL, $MAIN, $MAKEFILE, $BIN);

Log::Write(		"Task is completed. Open generated file ".Log::Highlight("Makefile")." to see what happened."			);
Log::Write(		"If you want to have post-perception, you can use file ".Log::Highlight($POST)." that is run after this program.");
Log::SysLog(		$Log::fbold.$Log::fblink.Log::Highlight("If you reached this line, no errors occured.")				);
#system "perl ".cwd()."/$POST \"$REL/$MAKEFILE\"";
