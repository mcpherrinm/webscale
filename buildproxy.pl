#!/usr/bin/env perl

use HTTP::Proxy;

my $proxy = HTTP::Proxy->new( port => 1080 );

# Todo add a filter?

$proxy->start;
