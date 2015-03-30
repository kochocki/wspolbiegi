echo -n 'Podaj liczbę: '
read liczba
echo $liczba > dane
wynik=`cat wynik`
while [[ wynik -eq '' ]]; do
  wynik=`cat wynik`
done
echo $wynik
echo '' > wynik
