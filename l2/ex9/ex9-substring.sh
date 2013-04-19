#!/bin/bash
if test $# == 3
then
  echo Substring of \"$1\" from $2 to $3 = \"`echo $1 | cut -c $2-$3`\"
else
  echo Wrong number of arguments \($#\). Should be 3. Example \"script string from_index to_index\"
fi
