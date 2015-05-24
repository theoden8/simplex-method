#!/usr/bin/perl

use strict;
use warnings;

use Cwd;

use Log;
use Option;
use File;

my $DIR = cwd();
$DIR	=~ s/\\/\\\\/g;
$DIR	=~ s/"/\\"/g;

Log::SysLog(		$Log::fbold.Log::Highlight("Executing the program from ")."\n\t".$Log::fundl.$Log::fblink.$Log::fsystem.$DIR		);
Log::Write(		Log::Highlight("Makefile")." generating program is started."								);

my $REL		= (exists $ARGV[0]) ? (shift @ARGV) : "..";

if(
	substr($REL, 0, 1) eq "~" or
	substr($REL, 0, 1) eq "/"
) {
	$DIR = $REL;
	$REL = '.';
}

my $MAIN	= (exists $ARGV[0]) ? (shift @ARGV) : "main.cpp";
my $BIN		= (exists $ARGV[0]) ? (shift @ARGV) : "_bin";
my $MAKEFILE	= "Makefile";
my $POST	= "Post.pl";

File::WriteFile($DIR, $REL, $MAIN, $MAKEFILE, $BIN);

Log::Write(		"Task is completed. Open generated file ".Log::Highlight("Makefile")." to see what happened."				);
Log::Write(		"If you want to have post-perception, you can use file ".Log::Highlight($POST)." that is run after this program."	);
Log::SysLog(		$Log::fbold.$Log::fblink.Log::Highlight("If you reached this line, no errors occured.")					);
#system "perl ".cwd()."/$POST \"$REL/$MAKEFILE\"";
