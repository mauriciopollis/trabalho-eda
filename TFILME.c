#include "TFILME.h"


TFILME *TFILME_cria(char *titulo, int ano, char *diretor, char *genero, int duracao) {
    TFILME *novo_filme = (TFILME *) malloc(sizeof(TFILME));
    
    strcpy(novo_filme->titulo, titulo);
    novo_filme->ano = ano;
    strcpy(novo_filme->diretor, diretor);
    strcpy(novo_filme->genero, genero);
    novo_filme->duracao = duracao;

    return novo_filme;
}

void TFILME_libera(TFILME *filme) {
    free(filme);
}

void TFILME_imprime(TFILME *filme) {
    printf("%s, %d, %s, %s, %d\n", filme->titulo, filme->ano, filme->diretor, filme->genero, filme->duracao);
}

int TFILME_compara_titulo_ano(char *titulo1, int ano1, char *titulo2, int ano2) {
    if(strcmp(titulo1, titulo2) < 0) {
        return -1;
    }
    if(strcmp(titulo1, titulo2) == 0) {
        if(ano1 < ano2) {
            return -1;
        }
        if(ano1 == ano2) {
            return 0;
        }
        // return 1;
    }
    return 1;
}

int TFILME_compara_filmes(TFILME *filme1, TFILME *filme2) {
    return TFILME_compara_titulo_ano(filme1->titulo, filme1->ano, filme2->titulo, filme2->ano);
}