#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main () {
  int plik_dane, plik_wyniki, plik_gotowy;
  int i = 0;
  char wiadomosc_od_uzytkownika[1024];
  char odpowiedz[1024];
  char znak;


  while (1) {
    for (i = 0; i < 1024; i++) odpowiedz[i] = 0;
    while (access("/home/krzysztof/tmp/gotowy", F_OK) == -1);
    unlink("/home/krzysztof/tmp/gotowy");
    while ((plik_dane = open("/home/krzysztof/tmp/dane", O_RDONLY)) == -1);
    read(plik_dane, wiadomosc_od_uzytkownika, 1024);
    i = 0;
    printf("Uzytkownik ");
    while ((znak = wiadomosc_od_uzytkownika[i]) != '\n') {
      putchar(znak);
      i++;
    }
    printf(" przesyla wiadomosc: ");
    while ((znak = wiadomosc_od_uzytkownika[i]) != 27) {
      putchar(znak);
      i++;
    }
    close(plik_dane);
    unlink("/home/krzysztof/tmp/dane");

    printf("\nWpisz odpowiedz:\n");
    i = 0;
    while ((znak = getchar()) != 27) {
      odpowiedz[i] = znak;
      i++;
    }
    odpowiedz[i] = 27;
    plik_wyniki = open("/home/krzysztof/tmp/wyniki", O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, S_IRWXU);
    write(plik_wyniki, odpowiedz, strlen(odpowiedz));
    close(plik_wyniki);
    open("/home/krzysztof/tmp/gotowy2", O_CREAT, 0);
    unlink("/home/krzysztof/tmp/lockfile");
    printf("A\n");
  }
  return 0;
}
