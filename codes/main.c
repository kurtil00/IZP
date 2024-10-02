#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

char* substring(char* string, int n){
    char* out = malloc((n+1)*sizeof(char));
    out[n] = '\0';
    // for(; n >= 0; n--){
    //     out[n] = string[n];
    // }
    memcpy(out, string, n);
    return out;
}

int main(int argc, char* argv[]){

    int pocet = -1;
    char pole[101];
    printf("%d", strlen(pole));
    printf("\n%d\n", sizeof(pole));
    do{
        pocet++;
        pole[pocet] = getchar();
    } while(pole[pocet] != '\n' && pocet < 100);
    printf("Pocet znaku: %i\n%s", pocet, substring(pole, pocet));

    int a;
    printf("\nTestovani substring\nPocet pro substring: ");

    char* str;
    str = "012345678901234567980123456789";
    scanf("%d", &a);
    printf("%s", substring(str, a));

    return 0;
}