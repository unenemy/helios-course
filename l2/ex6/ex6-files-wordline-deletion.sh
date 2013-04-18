#!/bin/bash
# args: first arguments are files, last - word to delete lines, containing it
word=${@: -1}
i=1
for file in $@
do
  if test $i -lt $#
  then
    i=`expr $i + 1`
    if sed -i "/$word/d" $file
    then
      echo all lines containing \"$word\" deleted from $file 
    fi
  fi
done
