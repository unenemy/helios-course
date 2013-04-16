while true; do
  read -p "Enter a word:" word
  read -p "Enter a filename:" filename
  matches=`grep -c $word $filename`
  echo "found $matches matches"
done
