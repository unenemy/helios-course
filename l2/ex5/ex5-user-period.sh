from=`who | grep $1 | head -1 | awk '{ print $3 " " $4 }'`
to=`date +"%Y-%m-%d %H:%M"`
echo "user $1 is working from $from till $to"
