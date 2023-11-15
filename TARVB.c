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

TFILME *TARVB_busca(TARVB *a, char *titulo, int ano) {
    if(a != NULL) {
        int i = 0;
        while((i < a->nch) && TFILME_compara_titulo_ano(titulo, ano, a->chave[i]->titulo, a->chave[i]->ano) > 0) {
            i++;
        }
        if((i < a->nch) && TFILME_compara_titulo_ano(titulo, ano, a->chave[i]->titulo, a->chave[i]->ano) == 0) {
            return a->chave[i];
        }
        return TARVB_busca(a->filho[i], titulo, ano);
    }
    return NULL;
}

TARVB *TARVB_insere_filme(TARVB *a, char *titulo, int ano, char *diretor, char *genero, int duracao, int t) {
    TFILME *busca = TARVB_busca(a, titulo, ano);
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
    TFILME *busca = TARVB_busca(a, titulo, ano);
    if(busca != NULL) {
        printf("Diretor: %s\n", busca->diretor);
        printf("Gênero: %s\n", busca->genero);
        printf("Duracao: %d\n", busca->duracao);
    } else {
        printf("Filme não está na árvore\n");
    }
}

void TARVB_modifica_secundarias(TARVB *a, char *titulo, int ano, char *novo_diretor, char *novo_genero, int nova_duracao) {
    TFILME *busca = TARVB_busca(a, titulo, ano);
    if(busca != NULL) {
        strcpy(busca->diretor, novo_diretor);
        strcpy(busca->genero, novo_genero);
        busca->duracao = nova_duracao;
        printf("Informações secundárias alteradas\n");
        TFILME_imprime(busca);
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
        free(a->filho);
        for(int i=0; i<a->nch; i++) {
            TFILME_libera(a->chave[i]);
        }
        free(a->chave);
        free(a);
    }
}

TARVB *TARVB_remove_filme(TARVB *a, char *titulo, int ano, int t) {
    if(a == NULL) return a;
    TFILME *busca = TARVB_busca(a, titulo, ano);
    if(busca == NULL) return a;
    return TARVB_remove_filme_aux(a, busca, t);
}

TARVB* TARVB_remove_filme_aux(TARVB* a, TFILME *filme, int t) {
    if(a == NULL) return a;

    printf("Removendo %s(%d)\n", filme->titulo, filme->ano);
    if(a->folha) { //CASO 1 - CHEGOU EM UMA FOLHA
        printf("\nCASO 1\n");
        int i = 0;
        while(i < a->nch && TFILME_compara_filmes(filme, a->chave[i]) > 0) i++;
        if(a->nch<(2*t-1) && TFILME_compara_filmes(filme, a->chave[i]) == 0) {
            // remover o filme que está em a->chave[i];

            // movendo as chaves uma posição para a esquerda
            for(int j=i; i<(a->nch-1); i++) {
                a->chave[i] = a->chave[i+1];
            }
            a->nch -= 1;

            if(a->nch == 0) {
                TARVB_libera(a);
                a = NULL;
            }
            return a;
        }
        // não achou o filme
        return a;
    }
    // CHEGOU EM UM NÓ INTERNO
    int i = 0;
    while(i < a->nch && TFILME_compara_filmes(filme, a->chave[i]) > 0) i++;
    if(i < a->nch && TFILME_compara_filmes(filme, a->chave[i]) == 0) { //nó contém o filme -> casos 2a, 2b ou 2c
        if(a->filho[i]->nch >= t) { // CASO 2A
            printf("\nCASO 2A\n");
            // achar o predecessor k' de k na subárvore a->filho[i]
            TARVB *y = a->filho[i];
            while(!y->folha) y = y->filho[y->nch];
            TFILME *temp = y->chave[y->nch - 1];

            // trocar y e filme = a->chave[i] de lugar
            y->chave[y->nch - 1] = a->chave[i];
            a->chave[i] = temp;

            // não é preciso trocar os filhos, pois os filhos de y são NULL(está em uma folha) e os filhos de a->chave[i] devem ser os mesmos

            // remover filme de a->filho[i]
            a->filho[i] = TARVB_remove_filme_aux(a->filho[i], filme, t);
            
            return a;
        }
        if(a->filho[i]->nch == (t-1) && a->filho[i+1]->nch>=t) { // CASO 2B
            printf("\nCASO 2B\n");
            // achar o sucessor k' de k na subárvore a->filho[i+1]
            TARVB *y = a->filho[i+1];
            while(!y->folha) y = y->filho[0];
            TFILME *temp = y->chave[0];

            // trocar y e filme = a->chave[i] de lugar
            y->chave[0] = a->chave[i];
            a->chave[i] = temp;

            // não é preciso trocar os filhos, pois os filhos de y são NULL(está em uma folha) e os filhos de a->chave[i] devem ser os mesmos

            // remover filme de a->filho[i+1]
            a->filho[i+1] = TARVB_remove_filme_aux(a->filho[i+1], filme, t);
            
            return a;
        }
        if(a->filho[i]->nch == (t-1) && a->filho[i+1]->nch == (t-1)) { // CASO 2C
            printf("\nCASO 2C\n");
            //juntar k e a->filho[i+1] em a->filho[i], de forma que a perca k e o ponteiro para a->filho[i+1], e a->filho[i]->nch = 2t-1
            TARVB *y = a->filho[i];
            TARVB *z = a->filho[i+1];
            
            y->chave[y->nch] = a->chave[i]; // mover k = a->chave[i] para a->filho[i]
            y->nch += 1;

            // juntar a->filho[i+1] no nó "juntado" k + y
            for(int j=t; j<(2*t-1); j++) { // chaves
                y->chave[j] = z->chave[j-t];
            }
            for(int j=(t+1); j<(2*t); j++) { // filhos
                y->filho[j] = z->filho[j-t-1];
            }
            a->nch = 2*t-1;

            // "remover" a->chave[i] de a
            for(int j=i; j<(a->nch-1); j++) { //chaves
                a->chave[j] = a->chave[j+1];
            }
            for(int j=(i+1); j<a->nch; j++) { //filhos
                a->filho[j] = a->filho[j+1];
            }
            a->nch -= 1;

            // "deletar z"
            TARVB_libera_remocao(z, t);

            if(a->nch == 0) {
                TARVB *temp = a;
                a = a->filho[0];
                temp->filho[0] = NULL;
                TARVB_libera_remocao(temp, t);
                a = TARVB_remove_filme_aux(a, filme, t);
            } else {
                a->filho[i] = TARVB_remove_filme_aux(a->filho[i], filme, t);
            }

            return a;
        }
    }
    // nó não contém o filme -> casos 3a ou 3b
    //continuar buscando k, mantendo a certeza de que cada nó visitado tenha nch>=t
    //para isso, achar a->filho[i] que possa conter k
    // se a->filho[i]->nch = t-1, executar 3a ou 3b para garantir que irá descer para um nó com nch >=t
    // então, fazer a recursão no filho apropriado
    
    TARVB *y = a->filho[i], *z = NULL;
    if(y->nch == (t-1)) { // CASOS 3A E 3B
        // dar uma chave extra para a->filho[i], movendo uma chave de a para a->filho[i], movendo uma chave de a->filho[i+1](ou a->filho[i-1]) para a, 
        //e movendo o filho apropriado do irmão para a->filho[i]
        if((i < a->nch) && (a->filho[i+1]->nch>=t)) { // vizinho da frente é válido (3A)
            printf("\nCASO 3A: i menor que nch\n");
            z = a->filho[i+1];

            // passar a->chave[i] para y
            y->chave[y->nch] = a->chave[i];
            y->nch += 1;
            y->filho[y->nch] = z->filho[0]; // passa o menor filho de z para o maior filho de y

            // passar z->chave[0] para a->chave[i]
            a->chave[i] = z->chave[0];

            // desloca chaves e filhos de z uma unidade para a esquerda
            for(int j=0; j<(z->nch-1); j++) {
                z->chave[j] = z->chave[j+1];
            }
            for(int j=0; j<z->nch; j++) {
                z->filho[j] = z->filho[j+1];
            }
            z->nch -= 1;

            // continuar a remoção recursiva em y
            a->filho[i] = TARVB_remove_filme_aux(a->filho[i], filme, t);
        }
        if((i > 0) && (a->filho[i-1]->nch>=t)) { // vizinho da frente não é válido, olhar no vizinho de trás (3A)
            printf("\nCASO 3A: i igual a nch\n");
            z = a->filho[i-1];

            // deslocando todas as chaves e filhos de y uma unidade para a direita para abrir espaço para a nova chave vinda de a
            for(int j=y->nch; j>0; j--) {
                y->chave[j] = y->chave[j - 1];
            }
            for(int j=(y->nch+1); j>0; j++) {
                y->filho[j] = y->filho[j-1];
            }
            y->chave[0] = a->chave[i-1]; // transfere maior chave de a para menor chave de y
            y->nch += 1;
            a->chave[i-1] = z->chave[z->nch-1]; // passa a maior chave de z para a maior chave de a

            y->filho[0] = z->filho[z->nch]; // transfere o maior filho de z para o menor filho de y

            z->nch -=1;

            // continuar a remoção recursiva em y
            a->filho[i] = TARVB_remove_filme_aux(y, filme, t);
            return a;
        }
        
        // merge a->filho[i] com um irmão, o que envolve mover uma chave de a para o novo filho "merged" para ser a chave média desse novo nó "merged"
        if(i < a->nch && a->filho[i+1]->nch == (t-1)) { // vizinho da frente é válido (3B)
            printf("\nCASO 3B: i menor que nch\n");

            //copiar a->chave[i] para a posição mais à direita de y

            // copiar as t-1 chaves de z para o novo no "merge"
            // copiar as t raizes de z para o novo no "merge"

            //mover todos os nós e filhos de a uma unidade para a esquerda

            // liberar o antigo nó z

            // continuar a recursão
        }
        if((i > 0) && a->filho[i-1]->nch == (t-1)) { // vizinho da frente não é válido, olhar no vizinho de trás (3B)
            printf("\nCASO 3B: i igual a nch\n");

            // copiar a->chave[i-1] para z

            // copiar as t-1 chaves de y para o novo nó "merged"
            // copiar os t filhos de y para o novo nó "merged"

            // liberar o antigo nó y

            //mover todos os nós e filhos de a uma unidade para a esquerda

            // continuar a recursão
        }
    }

    a->filho[i] = TARVB_remove_filme_aux(a->filho[i], filme, t); // a->filho[i]->nch>=t
    return a;
}

TARVB *TARVB_remove_filmes_diretor(TARVB *a, char *diretor, int t);

TARVB *TARVB_remove_filmes_franquia(TARVB *a, char *franquia, int t);

TFILME *TARVB_busca_filme_diretor(TARVB *a, char *diretor);

void TARVB_libera_remocao(TARVB *a, int t) {
    for(int i=0; i<(2*t-1); i++) {
        a->chave[i] = NULL;
    }
    for(int i=0; i<(2*t); i++) {
        a->filho[i] = NULL;
    }
    free(a->chave);
    free(a->filho);
    free(a);
}