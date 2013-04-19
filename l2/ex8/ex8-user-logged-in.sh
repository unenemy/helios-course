#!/bin/bash
if who | awk -v user=$1 '{ print $1 == user }' | grep 1 > /dev/null
then
  echo User $1 logged in system
else
  echo User $1 is not logged in system
fi
