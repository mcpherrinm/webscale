#!/usr/bin/env bash

make "$QUERY_STRING" > /dev/null 2> /dev/null
echo "Content-Type: `file -bi $QUERY_STRING`"
echo
cat $QUERY_STRING
