#include "TARVB.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(void) {

    for(int t=2; t<70; t++) {
        TARVB *a = TARVB_cria(t);
        FILE *f = fopen("filmes.txt", "r");
        char titulo[82], diretor[52], genero[32];
        int ano, duracao;
        while(!feof(f)) {
            int r = fscanf(f, "%82[^/]/%d/%52[^/]/%32[^/]/%d", titulo, &ano, diretor, genero, &duracao);
            if(r == 5) { // leu os 5 campos
                a = TARVB_insere_filme(a, titulo, ano, diretor, genero, duracao, t);            
            }
        }
        fclose(f);
        printf("t = %d, %d filmes\n", t, TARVB_conta_filmes(a));
        TARVB_libera(a);
    }
    return 0;
}