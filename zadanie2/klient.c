#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main (int argc, char *argv[]) {
  int plik_dane, plik_wyniki, plik_gotowy, i = 0;
  char wiadomosc[1024], odpowiedz[1024], znak, nazwa_uzytkownika[32];
  char sciezka_lockfile[256];
  char sciezka_dane[256];
  char sciezka_wyniki[256];
  char sciezka_gotowy[256];
  char sciezka_gotowy2[256];


  for (i = 0; i < 256; i++) {
    sciezka_lockfile[i] = 0;
    sciezka_dane[i] = 0;
    sciezka_wyniki[i] = 0;
    sciezka_gotowy[i] = 0;
    sciezka_gotowy2[i] = 0;
    }

    strcat(sciezka_lockfile, "/home/");
    strcat(sciezka_dane, "/home/");
    strcat(sciezka_wyniki, "/home/");
    strcat(sciezka_gotowy, "/home/");
    strcat(sciezka_gotowy2, "/home/");

  for (i = 0; i < 1024; i++) wiadomosc[i] = 0;
  for (i = 0; i < 1024; i++) odpowiedz[i] = 0;
  for (i = 0; i < 32; i++) nazwa_uzytkownika[i] = 0;
  strcat(sciezka_lockfile, argv[1]);
  strcat(sciezka_lockfile, "/tmp/lockfile");
  strcat(sciezka_dane, argv[1]);
  strcat(sciezka_dane, "/tmp/dane");
  strcat(sciezka_wyniki, argv[1]);
  strcat(sciezka_wyniki, "/tmp/wyniki");
  strcat(sciezka_gotowy, argv[1]);
  strcat(sciezka_gotowy, "/tmp/gotowy");
  strcat(sciezka_gotowy2, argv[1]);
  strcat(sciezka_gotowy2, "/tmp/gotowy2");
  i = 0;
  while (open(sciezka_lockfile,O_CREAT|O_EXCL,0)==-1) {
   printf("Serwer zajety, prosze czekac\n");
   sleep(2);
  }
  printf("Wpisz wiadomosc:\n");
  getlogin_r(nazwa_uzytkownika, 32);
  while (nazwa_uzytkownika[i] != 0) {
    wiadomosc[i] = nazwa_uzytkownika[i];
    i++;
  }
  wiadomosc[i] = '\n';
  //printf("%s", username);
  //wczytanie wiadomosci
  while ((znak = getchar()) != 27) {
    wiadomosc[i+1] = znak;
    i++;
  }
  wiadomosc[i+1] = 27;
  //wiadomosc[1023] = '\0';
  //zapisanie do pliku

  plik_dane = open(sciezka_dane, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, S_IRWXU);

  write(plik_dane, wiadomosc, i+2);

  close(plik_dane);
  ////////////////////////////////////////////
  //plik gotowy do odczytu

  open(sciezka_gotowy, O_CREAT, 0);

  ////////////////////////////////
  //czekanie na gotowosc pliku z odpowiedzia od serwera

  while (access(sciezka_gotowy2, F_OK) == -1);
  unlink(sciezka_gotowy2);
  ////////////////////////////////

  while ((plik_wyniki = open(sciezka_wyniki, O_RDONLY)) == -1);
  read(plik_wyniki, odpowiedz, 1024);
  //printf("odpowiedz: %s\n", odpowiedz);
  i = 0;
  while ((znak = odpowiedz[i]) != 27) {
    putchar(znak);
    i++;
  }
  close(plik_wyniki);
  unlink("sciezka_wyniki");
  return 0;
}
