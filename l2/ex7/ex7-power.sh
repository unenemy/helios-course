#!/bin/bash
if [ $1 ] && [ $2 ]
then
  bc <<< "$1^$2"
else
  echo "command needs 2 arguments"
fi
