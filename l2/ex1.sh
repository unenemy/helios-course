#cat passwd | sed 's/\([^:]*\)\(:[^:]*\)\{4\}:\([^:]*\).*/Home directory of \1=\3/'
cat "$1" | sed "$2"
