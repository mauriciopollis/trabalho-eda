#include "TFILME.c"

struct arvb {
    int nch;
    TFILME **chave;
    int folha;
    struct arvb **filho;
};

typedef struct arvb TARVB;

/*Inicializa uma árvore B nula*/
TARVB *TARVB_inicializa();

/*Libera árvore B*/
void TARVB_libera(TARVB *a);

/*Cria um nó de árvore B de grau t*/
TARVB *TARVB_cria(int t);

/*Busca se o filme está na árvore*/
TFILME *TARVB_busca(TARVB *a, char *titulo, int ano);

/*Insere o filme na árvore*/
TARVB *TARVB_insere_filme(TARVB *a, char *titulo, int ano, char *diretor, char *genero, int duracao, int t);

/*Divide a raíz*/
TARVB *TARVB_divide_raiz(TARVB *a, int t);

/*Função recursiva para inserir o filme na árvore(quando já se sabe que o filme não está na árvore e o nó não está cheio)*/
TARVB *TARVB_insere_filme_aux(TARVB *a, TFILME *filme, int t);

/*Divide o nó filho, transferindo uma chave para o nó pai*/
TARVB *TARVB_divide(TARVB *pai, int indice, TARVB *filho, int t);

/*Imprime o conteúdo dos nós da árvore em ordem crescente*/
void TARVB_imprime_crescente(TARVB *a);

/*Imprime o diretor, gênero e duração do filme*/
void TARVB_busca_info_subordinada(TARVB *a, char *titulo, int ano);

/*Altera as informações secundárias do filme*/
void TARVB_modifica_secundarias(TARVB *a, char *titulo, int ano, char *novo_diretor, char *novo_genero, int nova_duracao);

/*Retorna a quantidade de nós da árvore*/
int TARVB_conta_nos(TARVB *a);

/*Retorna o número de filmes na árvore*/
int TARVB_conta_filmes(TARVB *a);

/*Função de liberação especial de nós usada durante a remoção de um filme da árvore*/
void TARVB_libera_remocao(TARVB *a, int t);

/*Função principal para remoção de filmes*/
TARVB *TARVB_remove_filme(TARVB *a, char *titulo, int ano, int t);

/*Função auxiliar para remoção de filmes (adaptada da biblioteca da professora)*/
TARVB *TARVB_remove_filme_aux(TARVB *a, TFILME *filme, int t);

/*Remove todos os filmes de um diretor*/
TARVB *TARVB_remove_filmes_diretor(TARVB *a, char *diretor, int t);

/*Remove todos os filmes de uma franquia*/
TARVB *TARVB_remove_filmes_franquia(TARVB *a, char *franquia, int t);

/*Busca se existe um filme do diretor na árvore*/
TFILME *TARVB_busca_filme_diretor(TARVB *a, char *diretor);

/*Busca um filme da franquia na árvore*/
TFILME *TARVB_busca_filme_franquia(TARVB *a, char *franquia);

/*Imprime a árvore de forma hierárquica*/
void TARVB_imprime_vis(TARVB *a, int nivel);

/*Imprime a árvore de forma hierárquica*/
void TARVB_imprime_rec(TARVB *a, int nivel);

/*Cria a árvore a partir do arquivo*/
TARVB *TARVB_cria_arvoreb_arquivo(int t, char *nome_arquivo);

/*Lista todos os filmes creditados a um diretor*/
void TARVB_lista_filmes_diretor(TARVB *a, char *diretor);

/*Busca se existe um filme de um genero na árvore*/
TFILME *TARVB_busca_filme_genero(TARVB *a, char *genero);

/*Remove todos os filmes de um genero*/
TARVB *TARVB_remove_filmes_genero(TARVB *a, char *genero, int t);

/*Limpa tela*/
void Limpa_tela(void);