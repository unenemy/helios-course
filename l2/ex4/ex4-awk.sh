while true; do
  read -p "Enter a word:" word
  read -p "Enter a filename:" filename
  awk -v word=$word '$0~word{ matches++ } END { print "found " matches " matches" }' $filename
done
