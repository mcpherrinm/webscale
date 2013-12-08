#!/usr/bin/env bash

if [[ "$QUERY_STRING" =~ [a-zA-Z0-9.]* ]]; then
  make "$QUERY_STRING" > /dev/null 2> /dev/null || exit 10
  if [[ -f "$QUERY_STRING" ]]; then
    echo "Content-Type: `file -bi $QUERY_STRING`"
    echo
    cat $QUERY_STRING
    exit 0
  fi
fi

exit 1
