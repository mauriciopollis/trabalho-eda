#include "TARVB.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(void) {

    // cria a árvore b
    int t = 2;
    TARVB *a = TARVB_cria(t);

    // lê o arquivo e vai preenchendo a árvore
    FILE *f = fopen("filmes.txt", "r");
    char titulo[82], diretor[52], genero[32];
    int ano, duracao;
    while(!feof(f)) {
        int r = fscanf(f, "%82[^/]/%d/%52[^/]/%32[^/]/%d\n", titulo, &ano, diretor, genero, &duracao);
        if(r == 5) { // leu os 5 campos
            a = TARVB_insere_filme(a, titulo, ano, diretor, genero, duracao, t);            
        }
        //printf("Nome: %s, Ano: %d, Diretor: %s, Gênero: %s, Duração(min): %d\n", titulo, ano, diretor, genero, duracao);
    }
    
    fclose(f);

    //TARVB_imprime_crescente(a);

    //TARVB *teste = TARVB_busca(a, "Star Wars Episode IV A New Hope", 1977);

    //TARVB_busca_info_subordinada(a, "Star Wars Episode IV A New Hope", 1977);

    //TARVB_modifica_secundarias(a, "Star Wars Episode IV A New Hope", 1977, "Ninguem", "Nenhum", 0);

    //TARVB_busca_info_subordinada(a, "Star Wars Episode IV A New Hope", 1977);

    //printf("%d\n", TARVB_conta_nos(a));

    //printf("%d\n", TARVB_conta_filmes(a));

    TARVB_imprime_crescente(a);

    TARVB_libera(a);

    return 0;
}