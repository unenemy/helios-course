filename=$1
from=$2
to=$3

# slow version
echo "slow version using awk"
cat $1 | awk -v from=$from -v to=$to 'NR >= from && NR <=to'

#faster version
echo "\nfaster version with tail and head"
range=`expr $to - $from + 1`
tail -n+$from $filename | head -$range
