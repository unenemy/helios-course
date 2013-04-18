#!/bin/bash
while true; do
  read -p "Enter basic salary: " salary
  if test $salary -le 1500
  then
    HRA=`bc <<< "scale=2; $salary/10"`
    DA=`bc <<< "scale=2; $salary*0.9"`
  else
    HRA=500.00
    DA=`bc <<< "scale=2; $salary*0.98"`
  fi
  echo "HRA = $HRA"
  echo "DA = $DA"
done
