trap "" SIGHUP
trap "" SIGTERM

if [ ! -p serwerfifo ]
  then
  mkfifo serwerfifo
fi

while true
do
  wiadomosc=`cat < serwerfifo`
  IFS=";"
  tablica=($wiadomosc)
  ./liczydlo.sh ${tablica[0]} ${tablica[1]} &
done
