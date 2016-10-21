#!/usr/bin/perl

use warnings;
use strict;

my %ratings;

open(my $fh, '<', 'films.txt');
foreach (<$fh>)
{
  chomp();
  my $str = substr($_, index($_, '",'));
  my @a = split(',', $str);
  $ratings{substr($a[2], 1, length($a[2])-2)}++;
}

my @keys = sort(keys(%ratings));
foreach (@keys)
{
  print "$_\n";
}
