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

Log::SysLog(		$Log::fbold.Log::Highlight("Executing the program from ")."\n\t".$Log::fundl.$Log::fblink.$Log::fsystem.$DIR	);
Log::Write(		Log::Highlight("Makefile")." generating program is started."							);

my $Relative = "..";
if(exists $ARGV[0]) {
	$Relative = shift @ARGV;
}

my $main = "main.cpp";
if(exists $ARGV[0]) {
	$main = shift @ARGV;
}
my $MAKEFILE = "Makefile";
my $binary = "_bin";
if(exists $ARGV[0]) {
	$binary = shift @ARGV;
}

File::WriteFile($DIR, $Relative, $main, $MAKEFILE, $binary);

Log::Write(		"Task is completed. Open generated file ".Log::Highlight("Makefile")." to see what happened."			);
Log::SysLog(		$Log::fbold.$Log::fblink.Log::Highlight("If you reached this line, no errors occured.")				);
