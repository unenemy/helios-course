#!/bin/bash
if test $# == 2
then
  message=`diff $1 $2`
  case $? in
    0)
      rm $2
      echo "Files $1 and $2 are equal by content. File $2 is removed." ;;
    1)
      echo "Files $1 and $2 are different by content." ;;
    *) print $message ;;
  esac
else
  echo "Wrong number of arguments ($#). Should be 2"
fi
