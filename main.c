#include <stdio.h>
#include <string.h>
/*
 *      OPCJA Z HASHOWANIEM TAK /NIE -> suma ascii nazwiska -> modulo pewnej liczby.
 *
 *      dodawanie studentow
 *      wypisanie wszystkich (w tedy bez haszowania)
 *   wyszukiwanie po ocenie / nazwisko  bo bez hashu
 *   Usuwanie po ocenie / nazwisku (wszystkich) ( bez nazwisk)
 *       Czyszczenie pliku -  otworzyc jako nadpisywanie i zakmnac, ez
 *
 *  ; =59
 */

#define WYJSCIE 5
union unia{ // dowyszukiwania
    int szukana_ocena; // u1.szukana_ocena = 2; %d
    char szukane_nazwisko[100]; // strcpy(u1.szukane_nazwisko , "Swiatek"); %s
};

#define pojemnosc 5000 // Size of the Hash Table
// suma ASCII i modulo z Pojemnoscia
unsigned long hash(char* str) { // https://www.digitalocean.com/community/tutorials/hash-table-in-c-plus-plus
    unsigned long i = 0;
    for (int j=0; str[j]; j++) // dla kazdej litery na ascii i dodajemy do sumy
        i += str[j];
    return i % pojemnosc;
}

void dodaj_studentow(int ilosc, char klasa[50], int haszowanie){
    FILE *Plik;
    char nazwisko[100];
    int w, ocena;
    unsigned long hash1;

    Plik=fopen(strcat(klasa, ".txt"), "a"); // strcat do dopisywania na koncu pierwszego tego co w drugim
    if(Plik==0) printf("blad otwarcia\n");

    for(int i=0; i<ilosc; i++){
        printf("podaj ocene: \n");
        scanf("%d", &ocena);
        printf("Podaj nazwisko: \n");
        scanf("%s", &nazwisko);
        if(haszowanie){
            hash1= hash(nazwisko);
            w = fprintf(Plik, "%d;%lu;\n", ocena, hash1);
            printf("hash nazwiska A= %lu\n", hash1);
        }else{
            w = fprintf(Plik, "%d;%s;\n", ocena, nazwisko);
        }
    }
    w = fclose(Plik);
    if(w==EOF) printf("blad zamkniecia\n");
}

void wypisz_wszystkich(char nazwa_pliku[50], int hash){
    FILE *plik;
    int w;

    plik=fopen(strcat(nazwa_pliku, ".txt"), "r");

    printf("Ocena / Nazwisko\n");
        while(w!=EOF) {
            w = fgetc(plik); // w zmiennej "w" jest numer aktualnego znaku.
            if (w == 59) {
                printf(" ");
                continue;
            }
            printf("%c", w);
        }
    w = fclose(plik);
    if(w==EOF) printf("blad zamkniecia\n");
    if(hash) printf("nie dziw sie, nazwiska są zahaszowane ;)\n");
}

void znajdz(char nazwa_pliku[50], union unia dane, int tryb){ // 1 ocena, 0 nazwisko // dorobic haszowanie XD
    FILE *plik;
    int i, x, w, next_nazwisko, pom=0;
    long koniec_nazwiska, pozycja; // moznabyloby dac do inta, ale wieksze pliki problem
    char nazwisko[50];
    plik=fopen(strcat(nazwa_pliku, ".txt"), "r");

    if(tryb) {
        while(w!=EOF) {
            w = fgetc(plik);

            if (w == EOF){
                printf("blad odczytu / wyjscie\n"); // w ostatnim bedzie to bo przesuwamy na koniec pliku
                break;
            }

            x = w;
            if (w == 59) {
                pom += 1; // jesli wskazujemy na ;
                continue;
            }
            if (pom % 2 == 0) { // jesli wskazujemy na pierwszy element
                x -= 48; // zwraca kod ascii odejmuje kod ascii liczby 0, w wyniku mam liczbę jaka kryje się pod kodem ascii
                if ((int) x == dane.szukana_ocena) {
                    fseek(plik, 1, SEEK_CUR);
                    while (1) {
                        w = fgetc(plik);
                        if (w != 59) {
                            printf("%c", w);
                        } else {
                            printf("\n");
                            break;
                        }
                    }
                }
            }
        }
    }
    else {
        fseek(plik, 2, SEEK_SET); // ustawiamy na pierwsza litere nazwiska
        pozycja=ftell(plik); // gdzie sie zaczyna nazwisko
        w=fgetc(plik);
        i=0; // przy wejsciu zerujemy

        while(w!=EOF) { // jesli bylaby opcja zeby przejsc do kolejnej linii to byloby o wiele prosciej
            nazwisko[i]=(char)w;
            i++;
            w = fgetc(plik);
            if (w == EOF){
                printf("blad odczytu / wyjscie\n");
                break;
            }

            if(w==59){ // doszlismy do konca nazwiska   moznabyloby nie na seek_set tylko na cur, zaleznie od i (dlugosci)
                i=0; // zerujemy bo to nazwisko juz przeanalizowalismy
                koniec_nazwiska=ftell(plik); // wskazujemy na ; po nazwisku 3;nazwisko; <- // mozna byloby dac 3 i bysmy byli w kolenym nazwisku, ale problem bo mozna wyjsc poza zakres
                if(strcmp(dane.szukane_nazwisko, nazwisko)==0){ // sa takie same
                    //          w pozycji sie zaczyna, nazwisko jest 2 symbole wczensiej x;Nazwisko;
                    fseek(plik, pozycja-2, SEEK_SET); // cofamy o 2 pola, czyli na ocene
                    w=fgetc(plik); // pobieramy ocenke
                    printf("%c\n", w);
                    fseek(plik, koniec_nazwiska, SEEK_SET); // wracamy po wyswietleniu nazwiska
                }
                next_nazwisko = fseek(plik, koniec_nazwiska+4, SEEK_SET); // przechodizmy do kolejnego nazwiska
                if(next_nazwisko!=0) break; // jesli jest blad przy przejsciu, to znaczy ze koniec pliku
                pozycja=ftell(plik); // zapisujemy gdzie jest poczatek nowego nazwiska
                w = fgetc(plik); // pobieram pierwsza litere z nazwiska
                strcpy(nazwisko , " ");
            }
        }
    } // z hashem zrobić 100*, 10*, 1*.... kolejne wartosci, jesli zawsze bedzie 3 pola XD albo jakos inaczej
    w = fclose(plik);
    if(w==EOF) printf("blad zamkniecia\n");

}

void usun_z_oceny_nazwiska(char nazwa_pliku[50], union unia dane, int tryb){
    FILE *plik, *bufor;
    int i, x, w=0, ocena;
    char nazwisko[50];

    plik=fopen(strcat(nazwa_pliku, ".txt"), "r");
    bufor=fopen("BUFFOR.txt", "w+");
    if(tryb) {
        while(w!=EOF) {
            w = fgetc(plik);
            if(w==EOF) break;

            x = w-48;
            if ((int) x == dane.szukana_ocena){ // jesli jest rwone przechodzimy do ostatniego ;
                w = fgetc(plik); // tera czytamy ;
                while(1){ // tu odczytujemy nazwisko
                    w = fgetc(plik);
                    if(w==10 || w==13) break; // 10 lub 13 to przejscie do nowej linii
                }
            }
            else{
                fprintf(bufor, "%c", w);
            }
        }
    }
    else{ // tu zrobic przepisywanie do bufora jesli nazwisko jest rozne, jesli jest takie same, to usunac
        while(w!=EOF) {
            i=0;
            w = fgetc(plik);
            if (w == EOF) break;
            x=w-48;
            ocena = (int) x;
            fseek(plik, 2, SEEK_CUR); // na nazwisko
            w = fgetc(plik); // in w mamy pierwsza litere nazwiska tu git dziala
            // mamy pierwsza litere nazwiska
            while(w!=EOF) {
                nazwisko[i] = (char) w;
                i++;
                w = fgetc(plik);
                if (w == 59) { // doszlismy do konca nazwiska   moznabyloby nie na seek_set tylko na cur, zaleznie od i (dlugosci)
                    i = 0; // zerujemy bo to nazwisko juz przeanalizowalismy
                    printf("aktualne: %s\n", nazwisko);
                    printf("szukane:  %s\n", nazwisko);
                    if (strcmp(dane.szukane_nazwisko, nazwisko) == 0) { // sa takie same
                        printf("sa takie same");
                    }
                    else{
                        fprintf(bufor, "%d;%s;\n", ocena, nazwisko); // zapisujemy tych co nie chcemy wywalic
                    }
                    //in w mamy ostatni ;
                    w = fgetc(plik);
                    strcpy(nazwisko , " ");
                    break;
                }
            }
        }
    }
    w = fclose(plik);
    if(w==EOF) printf("blad zamkniecia pliku\n");
    w = fclose(bufor);
    if(w==EOF) printf("blad zamkniecia bufora\n");


    // zapis z bufora do naszego pliku
    plik = fopen(nazwa_pliku, "w+");
    bufor = fopen("BUFFOR.txt", "r");
    while(w!=EOF) {
        w = fgetc(bufor);
        if(w==EOF) break;
        fprintf(plik, "%c", w);
    }
    //zamkniecie
    w = fclose(plik);
    if(w==EOF) printf("blad zamkniecia pliku\n");
    w = fclose(bufor);
    if(w==EOF) printf("blad zamkniecia bufora\n");
}

void usuwanie_zawartosci(char nazwa_pliku[50]){ // 1 ocena, 0 nazwisko
    int w;
    FILE *plik;
    plik=fopen(strcat(nazwa_pliku, ".txt"), "w");// do zapisu i odczytu od poczatku pliku
    w = fclose(plik);
    if(w==EOF){printf("blad zamkniecia\n");}
    else printf("usunieto poprawie\n");
}

int main(void){
    union unia u1;
    int wybor, ilosc, tryb, haszowanie=0;
    char nazwa_pliku[50];

    //printf("czy haszujemy:?\n");
    //scanf("%d", &haszowanie);

    while (1) {
        //printf("dzialania:\n0-dodawanie stuentow (podana ilosc)\n1-wyswietlanie wszystkich studentow\n2-wyszukiwanie po ocenie / nazwisku\n3-usuwanie pierwszego napotkanego(po ocenie / nazwisku)\n4-usuwanie listy\n%d-Wyjscie\n", WYJSCIE);
        scanf("%d", &wybor);

        switch (wybor) {
            case 0:
                printf("podaj ilosc studentow do dopisania:\n");
                scanf("%d", &ilosc);
                printf("podaj kalse:\n");
                scanf("%s", &nazwa_pliku);
                dodaj_studentow(ilosc, nazwa_pliku, haszowanie);
                break;
            case 1:
                printf("podaj kalse:\n");
                scanf("%s", &nazwa_pliku);
                wypisz_wszystkich(nazwa_pliku, haszowanie);
                break;

            case 2:
                printf("podaj kalse:\n");
                scanf("%s", &nazwa_pliku);
                printf("wyszukiwanie po\n1-ocena\n0-nazwisko\n");
                scanf("%d", &tryb);

                if (tryb) {
                    printf("podaj ocene: \n");
                    scanf("%d", &u1.szukana_ocena);
                    printf("ocene %d maja: \n", u1.szukana_ocena);
                } else {
                    printf("podaj nazwisko:\n");
                    scanf("%s", &u1.szukane_nazwisko);
                    printf("Student %s ma ocene/oceny: \n", u1.szukane_nazwisko);
                }
                znajdz(nazwa_pliku, u1, tryb);
                break;

            case 3:
                printf("podaj kalse:\n");
                scanf("%s", &nazwa_pliku);
                printf("usuwanie po\n1-ocena\n0-nazwisko\n");
                scanf("%d", &tryb);

                if (tryb) {
                    printf("podaj ocene: \n");
                    scanf("%d", &u1.szukana_ocena);
                } else {
                    printf("podaj nazwisko:\n");
                    scanf("%s", &u1.szukane_nazwisko);
                }
                usun_z_oceny_nazwiska(nazwa_pliku, u1, tryb);
                break;
            case 4:
                printf("podaj kalse:\n");
                scanf("%s", &nazwa_pliku);
                usuwanie_zawartosci(nazwa_pliku);
                break;
            case WYJSCIE:
                printf("dzieki za skorzystanie z programu\n");
                return 0;
        }
    }

    return 0;
}