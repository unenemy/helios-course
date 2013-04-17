for file in $@
do
  if [ -d "$file" ]
  then
    echo "$file is a directory"
  elif [ -e "$file" ]
  then
    echo "$file is a file"
  else
    echo "$file is something else"
  fi
done
