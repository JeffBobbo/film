#!/usr/bin/perl

use warnings;
use strict;

my %categories;

open(my $fh, '<', 'films.txt');
foreach (<$fh>)
{
  chomp();
  my $str = substr($_, index($_, '",'));
  my @a = split(',', $str);
  my @cats = split('/', substr($a[3], 1, length($a[3])-2));
  $categories{$_}++ foreach (@cats);
}

my @keys = sort(keys(%categories));
foreach (@keys)
{
  print "$_\n";
}
