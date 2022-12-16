#include <stdio.h>
#include <string.h>

union unia{
    int szukana_ocena;
    char szukane_nazwisko[100];
};
int main(void){
    union unia u1;
    u1.szukana_ocena = 2;
    printf("%d\n",  sizeof(u1));
    printf("ocenka %d leci do %s\n", u1.szukana_ocena, u1.szukane_nazwisko);
    strcpy(u1.szukane_nazwisko , "Swiatek");
    printf("ocenka %d leci do %s\n", u1.szukana_ocena, u1.szukane_nazwisko);
    return 0;
}