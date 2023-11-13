#include<stdlib.h>
#include<string.h>

struct filme {
    char titulo[82];
    int ano;
    char diretor[52];
    char genero[32];
    int duracao;
};

typedef struct filme TFILME;

/*Cria um filme*/
TFILME *TFILME_cria(char *titulo, int ano, char *diretor, char *genero, int duracao);

/*Libera o filme*/
void TFILME_libera(TFILME *filme);

/*Imprime o filme*/
void TFILME_imprime(TFILME *filme);

/*Compara dois filmes baseados nos seus títulos e anos: -1 -> filme1 < filme2; 0 -> filme1 = filme2; +1 -> filme1 > filme2*/
int TFILME_compara_titulo_ano(char *titulo1, int ano1, char *titulo2, int ano2);

/*Compara dois filmes: -1 -> filme1 < filme2; 0 -> filme1 = filme2; +1 -> filme1 > filme2*/
int TFILME_compara_filmes(TFILME *filme1, TFILME *filme2);