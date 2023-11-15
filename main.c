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

    //TARVB_imprime_rec(a, 0);

    //TARVB_imprime_crescente(a);

    //TARVB *teste = TARVB_busca(a, "Star Wars Episode IV A New Hope", 1977);
    //printf("%s %d %d\n", a->chave[0]->titulo, a->chave[0]->ano, a->folha);
    
    printf("%d\n", TARVB_conta_filmes(a));
    a = TARVB_remove_filme(a, "Friends S2E16: The One Where Joey Moves Out",1996, t);
    printf("%d\n", TARVB_conta_filmes(a));

    a = TARVB_remove_filme(a, "Friends S1E3: The One with the Thumb", 1994, t);
    printf("%d\n", TARVB_conta_filmes(a));

    a = TARVB_remove_filme(a, "Schindlers List", 1993, t);
    printf("%d\n", TARVB_conta_filmes(a));
    a = TARVB_remove_filme(a, "Gifted Hands: The Ben Carson Story", 2009, t);
    printf("%d\n", TARVB_conta_filmes(a));
    a = TARVB_remove_filme(a, "The Avengers", 2012, t);
    printf("%d\n", TARVB_conta_filmes(a));
    a = TARVB_remove_filme(a, "Dances with Wolves", 1990, t);
    printf("%d\n", TARVB_conta_filmes(a));
    //a = TARVB_remove_filme(a, "The Exorcist", 1973, t);
    //printf("%d\n", TARVB_conta_filmes(a));
    //a = TARVB_remove_filme(a, "The Walking Dead S1E1: Days Gone Bye", 2010, t);
    //printf("%d\n", TARVB_conta_filmes(a));
    //a = TARVB_remove_filme(a, "The Walking Dead S1E2: Guts", 2010, t);
    //printf("%d\n", TARVB_conta_filmes(a));
    //a = TARVB_remove_filme(a, "The Walking Dead S1E3: Tell It to the Frogs", 2010, t);
    //printf("%d\n", TARVB_conta_filmes(a));
    //a = TARVB_remove_filme(a, "Friends S1E3: The One with the Thumb", 1994, t);
    //printf("%d\n", TARVB_conta_filmes(a));

    //TARVB_busca_info_subordinada(a, "Star Wars Episode IV A New Hope", 1977);

    // TARVB_busca_info_subordinada(a, "Friends S1E3: The One with the Thumb", 1994);

    //TARVB_modifica_secundarias(a, "Star Wars Episode IV A New Hope", 1977, "Ninguem", "Nenhum", 0);

    //TARVB_busca_info_subordinada(a, "Star Wars Episode IV A New Hope", 1977);

    //printf("%d\n", TARVB_conta_nos(a));

    //printf("%d\n", TARVB_conta_filmes(a));

    //TARVB_imprime_crescente(a);

    TARVB_libera(a);

    return 0;
}