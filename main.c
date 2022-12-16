#include <stdio.h>
#include <string.h>

#define WYJSCIE 9
union unia{
    int szukana_ocena; // u1.szukana_ocena = 2; %d
    char szukane_nazwisko[100]; // strcpy(u1.szukane_nazwisko , "Swiatek"); %s
};

void dodaj_studentow(int ilosc, char klasa[50]){
    printf("w petli %d, %s\n", ilosc, klasa);
}



int main(void){
    union unia u1;
    int wybor, ilosc;
    char nazwa_pliku[50] ;

    while (1) {
        printf("dzialania:\n0-dodawanie stuentow (podana ilosc)\n1-wyswietlanie wszystkich studentow\n2-wyszukiwanie po ocenie / nazwisku\n3-usuwanie pierwszego napotkanego(po ocenie / nazwisku)\n4-dodawanie po danej ocenie/nazwisku\n5-usuwanie listy\n%d-Wyjscie\n", WYJSCIE);
        scanf("%d", &wybor);

        switch (wybor) {
            case 0:
                printf("podaj ilosc studentow do dopisania\n");
                scanf("%d", &ilosc);
                printf("podaj kalse (1,2)");
                scanf("%s", &nazwa_pliku);
                dodaj_studentow(ilosc, nazwa_pliku);
                break;
            /*case 1:
                wypisz_wszystkich(root);
                break;
            case 2:
                printf("wyszukiwanie po\n0-ocena\n1-nazwisko\n");
                scanf("%d", &tryb);
                if (tryb) {
                    printf("podaj nazwisko: ");
                    scanf("%s", &S_nazwisko);
                } else {
                    printf("podaj ocene:");
                    scanf("%d", &ocenka);
                }
                wyszukiwanie(root, tryb, ocenka, S_nazwisko);
                break;
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