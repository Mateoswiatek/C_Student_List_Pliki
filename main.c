#include <stdio.h>

union unia1{
    int w_int;
    double pole2;
    char pole3[16];
} ;
int main(void){
    union unia1 u1, u2;
    u1.w_int = 2;
    u1.pole2 = 4.5;
    //printf("%d\n",  sizeof(u1));
    printf("%d %lf %s\n", u1.w_int, u1.pole2);
    return 0;
}