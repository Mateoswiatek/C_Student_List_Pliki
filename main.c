#include <stdio.h>
#include <string.h>
/*
 *      OPCJA Z HASHOWANIEM TAK /NIE -> suma ascii nazwiska -> modulo pewnej liczby.
 *
 *      dodawanie studentow
 *      wypisanie wszystkich (w tedy bez haszowania)
 * wyszukiwanie po ocenie / nazwisko
 * Usuwanie po ocenie / nazwisku pierwszego napotkanego (wszystkich)
 * Dodawanie po ocenie / nazwisku
 * Czyszczenie pliku
 *
 *  ; =59
 */

#define WYJSCIE 9
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

void znajdz(char nazwa_pliku[50], union unia dane, int tryb){ // 1 ocena, 0 nazwisko
    FILE *plik;
    int x, w, pom=0, aktualna_ocena;
    plik=fopen(strcat(nazwa_pliku, ".txt"), "r");

    printf("ocene %d maja: \n", dane.szukana_ocena);
    while(w!=EOF) {
        w = fgetc(plik);
        x=w;
        if (w == EOF){
            printf("blad odczytu / wyjscie\n"); // w ostatnim bedzie to bo przesuwamy na koniec pliku
            break;
        }
        if(w==59){
            pom+=1; // jesli wskazujemy na ;
            continue;
        }

        if(pom%2==0) { // jesli wskazujemy na pierwszy element
            x -= 48; // zwraca kod ascii odejmuje kod ascii liczby 0, w wyniku mam liczbę jaka kryje się pod kodem ascii
            if ((int) x == dane.szukana_ocena){
                fseek(plik, 1, SEEK_CUR);
                while(1){
                    w = fgetc(plik);
                    if(w!=59) {
                        printf("%c", w);
                    }else{
                        printf("\n");
                        break;
                    }
                } // bo najpierw wypisujemy, pozniej przesuwamy
            }
        }

        //w = fgetc(plik); dopóki w!=59  dopoki reszta z dzielenia to 0 to jessttesmy na liczbie
    }
    printf("wyszlismy\n");
    /*
    while(w!=EOF) {
        w = fgetc(plik); // w zmiennej "w" jest numer aktualnego znaku.
        if (w == 59) {
            printf(" ");
            continue;
        }
        printf("%c", w);
    }
     */
    w = fclose(plik);
    if(w==EOF) printf("blad zamkniecia\n");
}

int main(void){
    union unia u1;
    int wybor, ilosc, tryb, haszowanie=0;
    char nazwa_pliku[50];

    //printf("czy haszujemy:?\n");
    //scanf("%d", &haszowanie);

    //int x=2;
    //printf("ocenka to: %c\n ", (char)((int)((char)(x))));

    int ascii = 64; // Masz teraz jakis kod ascii
    char znak = (char)ascii; // Konwertuje go na typ znakowy

    printf("%c", znak);

    while (1) {
        printf("dzialania:\n0-dodawanie stuentow (podana ilosc)\n1-wyswietlanie wszystkich studentow\n2-wyszukiwanie po ocenie / nazwisku\n3-usuwanie pierwszego napotkanego(po ocenie / nazwisku)\n4-dodawanie po danej ocenie/nazwisku\n5-usuwanie listy\n%d-Wyjscie\n", WYJSCIE);
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
                printf("wyszukiwanie w ostatnio dodawanym po\n1-ocena\n0-nazwisko\n");
                scanf("%d", &tryb);

                if (tryb) {
                    printf("podaj ocene:\n");
                    scanf("%d", &u1.szukana_ocena);
                    znajdz(nazwa_pliku, u1, tryb);
                } else {
                    printf("podaj nazwisko: ");
                    scanf("%s", &u1.szukane_nazwisko);
                    znajdz(nazwa_pliku, u1, tryb);
                }
                break;
                /*
            case 3:
                printf("usuwanie po\n0-ocena\n1-nazwisko\n");
                scanf("%d", &tryb);
                if (tryb) {
                    printf("podaj nazwisko: ");
                    scanf("%s", &S_nazwisko);
                } else {
                    printf("podaj ocene:");
                    scanf("%d", &ocenka);
                }
                usuwanie_pierwszo_napotkanego(ws_root, root, tryb, ocenka, S_nazwisko);
                printf("wyszlo\n");
                root = numer_komurki_gdzie_root;
                break;
            case 4:
                printf("dodawanie po\n0-ocena\n1-nazwisko\n");
                scanf("%d", &tryb);
                if (tryb) {
                    printf("podaj nazwisko: ");
                    scanf("%s", &S_nazwisko);
                } else {
                    printf("podaj ocene:");
                    scanf("%d", &ocenka);
                }
                wpisz_po(root, tryb, ocenka, S_nazwisko);
                break;
            case 5:
                zwalnianie_listy(root);
                break;
            case WYJSCIE:
                printf("dzieki za skorzystanie z programu\n");
                return 0;*/
        }
    }

    return 0;
}