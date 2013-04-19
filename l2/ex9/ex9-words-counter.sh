#!/bin/bash
while true; do
  read -p "Enter filename: " file
  read -p "Enter word to count: " word
  echo There are `grep -ow $word $file | wc -w` words \"$word\" in the file $file
done
