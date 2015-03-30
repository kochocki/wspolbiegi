if [ ! -p klientfifo ]
  then
  mkfifo klientfifo
fi
echo "$1;$2" > serwerfifo
wynik=`cat < klientfifo`
echo "wynik: $wynik"
