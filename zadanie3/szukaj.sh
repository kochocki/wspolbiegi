declare -i licznik=0
declare -i korzen=0
declare -i procesy=0
katalog=$2
pliki=`ls -1 $katalog`

if [ "$3" == "" ]
  then
  korzen=1
fi

for plik in $pliki
do
  if [ $plik == $1 ]
    then
    echo $katalog/$plik
    licznik=`expr $licznik+1`
  elif [ -d $katalog/$plik ]
    then
    $0 $1 $2/$plik "syn" &
    procesy=`expr $procesy+1`
  fi
done

declare -i i=0

#for proces in $procesy
while [ $i -lt $procesy ]
do
  wait $!
  licznik=$[$licznik+$?]
  i=`expr $i+1`
done

if [ $korzen != 1 ]
  then
  exit $licznik
elif [ $licznik == 0 ]
then
  echo "nie znaleziono"
fi
