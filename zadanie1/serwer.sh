function f
{
    return $(($1*$1))
}

while true; do
  liczba=`cat dane`
  if [[ $liczba != "" ]]
  then
    f $liczba
    wynik_f=$?
    echo $wynik_f > wynik
    echo '' > dane
  fi
  echo '' > dane
done
