for file in $@
do
  file=`echo $file | tr '[a-z]' '[A-Z]'`
  if [ -e "./$file" ]
  then
    echo "$file is in current directory"
  else
    echo "$file may be somewhere else, but not in this dir =("
  fi
done
