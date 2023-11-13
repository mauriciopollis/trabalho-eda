#include "TARVB.h"
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

TARVB *TARVB_inicializa() {
    return NULL;
}

TARVB *TARVB_cria(int t) {
    TARVB *a = (TARVB *) malloc(sizeof(TARVB));
    a->nch = 0;
    a->folha = 1;
    a->chave = (TFILME **) malloc(sizeof(TFILME*) * (2*t-1));
    a->filho = (TARVB **) malloc(sizeof(TARVB *) * 2 * t);
    for(int i=0; i<(2*t); i++) {
        a->filho[i] = NULL;
    }
    return a;
}

TARVB *TARVB_busca(TARVB *a, char *titulo, int ano) {
    if(a != NULL) {
        int i = 0;
        while((i < a->nch) && TFILME_compara_titulo_ano(titulo, ano, a->chave[i]->titulo, a->chave[i]->ano) > 0) {
            i++;
        }
        if((i < a->nch) && TFILME_compara_titulo_ano(titulo, ano, a->chave[i]->titulo, a->chave[i]->ano) == 0) {
            return a;
        }
        return TARVB_busca(a->filho[i], titulo, ano);
    }
    return NULL;
}

TARVB *TARVB_insere_filme(TARVB *a, char *titulo, int ano, char *diretor, char *genero, int duracao, int t) {
    TARVB *busca = TARVB_busca(a, titulo, ano);
    if(busca != NULL) return a;
    
    TFILME *filme = TFILME_cria(titulo, ano, diretor, genero, duracao);

    if(a == NULL) {
        a = TARVB_cria(t);
        a->chave[0] = filme;
        a->nch = 1;
        return a;
    }
    
    if(a->nch == (2*t-1)) {
        // dividir a raiz
        a = TARVB_divide_raiz(a, t);
    }        
    // inserir o filme
    a = TARVB_insere_filme_aux(a, filme, t);

    return a;
}

TARVB *TARVB_divide_raiz(TARVB *a, int t) {

    // cria nova raíz
    TARVB *nova_raiz = TARVB_cria(t);
    nova_raiz->folha = 0;

    // cria novo filho direito
    TARVB *novo_filho = TARVB_cria(t);
    novo_filho->folha = a->folha; // se a antiga raiz era folha, o novo_filho também será
    novo_filho->nch = t - 1;

    // copia chave central para nova raiz
    nova_raiz->chave[0] = a->chave[t - 1];
    nova_raiz->nch = 1;

    // conecta a nova raíz com as filhos esquerdo e direito
    nova_raiz->filho[0] = a;
    nova_raiz->filho[1] = novo_filho;

    // copia chaves adequadas do filho esquerdo para o filho direito
    for(int i=t; i<(2*t-1); i++) {
        novo_filho->chave[i - t] = a->chave[i];
    }

    // copia os filhos adequados do filho esquerdo para o filho direito
    for(int i=t; i<(2*t); i++) {
        novo_filho->filho[i - t] = a->filho[i];
        //a->filho[i] = NULL; // isso é necessário ou posso considerar que todas as chaves de índice i >= t e seus filhos são todos "lixo"? 
    }

    // "deleta" as chave do filho esquerdo
    a->nch = t - 1;

    return nova_raiz;
}

TARVB *TARVB_insere_filme_aux(TARVB *a, TFILME *filme, int t) {
    
    if(a->folha) {
        // nó é folha, inserir nesse nó. Por construção, a folha nunca estará cheia nesse momento.
        int i = 0;
        while((i < a->nch) && (TFILME_compara_filmes(filme, a->chave[i]) > 0)) {
            i += 1;
        }
        // neste instante, i guarda o índice da posição que o novo filme deve ocupar no nó

        // movendo todos os filmes maiores que o filme a ser inserido uma posição para a direita
        for(int j = a->nch; j>i; j--) {
            a->chave[j] = a->chave[j - 1];
        }
        //printf("inseriu %s %d\n", filme->titulo, filme->ano);
        // não é necessário se preocupar em mover os filhos, pois todos os filhos de uma folha são NULL
        a->chave[i] = filme;
        a->nch += 1;

        return a;

    } else {
        // nó não é folha
        // achar o filho onde o filme deve ser inserido
        int i = 0;
        while((i < a->nch) && (TFILME_compara_filmes(filme, a->chave[i]) > 0)) {
            i += 1;
        }
        // neste instante, i guarda o índice do filho onde o filme deve ser inserido

        // verificar se o filho está cheio
        if(a->filho[i]->nch == (2*t-1)) {
            // filho cheio, fazer separação do filho[i]
            a = TARVB_divide(a, i, a->filho[i], t);
            // a divisão do nó pode fazer com que o valor de i esteja incorreto
            if(TFILME_compara_filmes(filme, a->chave[i]) > 0) i++;
        }

        // inserir filme no filho[i]
        a->filho[i] = TARVB_insere_filme_aux(a->filho[i], filme, t);

        return a;
    }
}

TARVB *TARVB_divide(TARVB *pai, int indice, TARVB *filho_esq, int t) {
    // indice identifica pai->filho[indice]

    // cria novo vizinho da direita
    TARVB *novo_direita = TARVB_cria(t);
    novo_direita->folha = filho_esq->folha;
    novo_direita->nch = t - 1;

    // copia as chaves que devem ser transferidas para o filho da direita que foi criado
    for(int i=t; i<filho_esq->nch; i++) {
        novo_direita->chave[i - t] = filho_esq->chave[i];
    }

    // copia os filhos que devem ser transferidos para o filho da direita que foi criado
    for(int i=t; i<(2*t); i++) {
        novo_direita->filho[i - t] = filho_esq->filho[i];
        filho_esq->filho[i] = NULL; // elimina a ligação que o filho da esquerda tinha com os nós que agora serão filhos da direita
    }

    // desloca as chaves do pai maiores que pai->chave[indice] uma unidade para a direita
    int j;
    for(j=pai->nch; j>indice; j--) {
        pai->chave[j] = pai->chave[j - 1];
    }

    // copia elemento central do filho para o pai
    pai->chave[indice] = filho_esq->chave[t - 1];
    pai->nch += 1;

    // desloca os filhos do pai maiores que pai->filho[indice] uma unidade para a direita
    for(j = pai->nch; j>(indice + 1); j--) {
        pai->filho[j] = pai->filho[j - 1];
    }

    // redefine o tamanho do vizinho da esquerda
    filho_esq->nch = t - 1;

    // liga o pai ao novo filho da direita
    pai->filho[indice + 1] = novo_direita;

    return pai;
}

void TARVB_imprime_crescente(TARVB *a) {
    if(a->folha) {
        for(int i=0; i<a->nch; i++) {
            TFILME_imprime(a->chave[i]);
        }
    } else {
        int i;
        for(i=0; i<a->nch; i++) {
            TARVB_imprime_crescente(a->filho[i]);
            TFILME_imprime(a->chave[i]);
        }
        TARVB_imprime_crescente(a->filho[i]);
    }
}

void TARVB_busca_info_subordinada(TARVB *a, char *titulo, int ano) {
    TARVB *busca = TARVB_busca(a, titulo, ano);
    if(busca != NULL) {
        int i = 0;
        for(i = 0; i<busca->nch; i++) {
            if(TFILME_compara_titulo_ano(titulo, ano, a->chave[i]->titulo, a->chave[i]->ano) == 0) {
                printf("Diretor: %s\n", a->chave[i]->diretor);
                printf("Gênero: %s\n", a->chave[i]->genero);
                printf("Diretor: %d\n", a->chave[i]->duracao);
            }
        }
    } else {
        printf("Filme não está na árvore\n");
    }
}

void TARVB_modifica_secundarias(TARVB *a, char *titulo, int ano, char *novo_diretor, char *novo_genero, int nova_duracao) {
    TARVB *busca = TARVB_busca(a, titulo, ano);
    if(busca != NULL) {
        int i = 0;
        for(i = 0; i<busca->nch; i++) {
            if(TFILME_compara_titulo_ano(titulo, ano, a->chave[i]->titulo, a->chave[i]->ano) == 0) {
                strcpy(a->chave[i]->diretor, novo_diretor);
                strcpy(a->chave[i]->genero, novo_genero);
                a->chave[i]->duracao = nova_duracao;
                printf("Informações secundárias alteradas\n");
                TFILME_imprime(a->chave[i]);
            }
        }
    } else {
        printf("Filme não está na árvore\n");
    }
}

int TARVB_conta_nos(TARVB *a) {
    if(a == NULL) {
        return 0;
    }
    if(a->folha) {
        return 1;
    }
    int soma = 0;
    for(int i=0; i<=a->nch; i++) {
        soma += TARVB_conta_nos(a->filho[i]);
    }
    return 1 + soma;
}

int TARVB_conta_filmes(TARVB *a) {
    if(a == NULL) {
        return 0;
    }
    if(a->folha) {
        return a->nch;
    }
    int soma = 0;
    for(int i=0; i<=a->nch; i++) {
        soma += TARVB_conta_filmes(a->filho[i]);
    }
    return a->nch + soma;
}

void TARVB_libera(TARVB *a) {
    if(a != NULL) {
        for(int i=0; i<=a->nch; i++) {
            TARVB_libera(a->filho[i]);
        }
        for(int i=0; i<a->nch; i++) {
            TFILME_libera(a->chave[i]);
        }
        free(a);
    }
}