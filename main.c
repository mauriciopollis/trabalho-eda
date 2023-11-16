#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "TARVB.c"

int main(void) {

    int t = 2;
    char *arquivo = "filmes.txt";

    TARVB *a = TARVB_cria_arvoreb_arquivo(t, arquivo);
    int op, continua = 1;
    while(continua) {
        printf("Inserir filme[0]\n");
        printf("Remover filme[1]\n");
        printf("Buscar informações secundárias[2]\n");
        printf("Alterar informações secundárias[3]\n");
        printf("Buscar filmes de um diretor[4]\n");
        printf("Retirar filmes de um diretor[5]\n");
        printf("Retirar filmes de um gênero[6]\n");
        printf("Retirar filmes de uma franquia[7]\n");
        printf("Sair[qualquer outro]\n");
        printf("Escolha: ");
        scanf("%d", &op);

        char titulo[82], diretor[52], genero[32], novo_diretor[52], novo_genero[32], franquia[82];
        int ano, duracao, nova_duracao;
        switch(op) {
            case 0:
                printf("Escolha: Inserir filme\n");
                printf("Título: ");
                scanf(" %[^\n]", titulo);
                printf("Ano: ");
                scanf("%d", &ano);
                printf("Diretor: ");
                scanf(" %[^\n]", diretor);
                printf("Gênero: ");
                scanf(" %[^\n]", genero);
                printf("Duração: ");
                scanf("%d", &duracao);
                a = TARVB_insere_filme(a, titulo, ano, diretor, genero, duracao, t);
                break;
            case 1:
                printf("Escolha: Remover filme\n");
                printf("Título: ");
                scanf(" %[^\n]", titulo);
                printf("Ano: ");
                scanf("%d", &ano);
                a = TARVB_remove_filme(a, titulo, ano, t);
                break;
            case 2:
                printf("Escolha: Buscar informações secundárias\n");
                printf("Título: ");
                scanf(" %[^\n]", titulo);
                printf("Ano: ");
                scanf("%d", &ano);
                TARVB_busca_info_subordinada(a, titulo, ano);
                break;
            case 3:
                printf("Escolha: Alterar informações secundárias\n");
                printf("Título: ");
                scanf(" %[^\n]", titulo);
                printf("Ano: ");
                scanf("%d", &ano);
                printf("Novo diretor: ");
                scanf(" %[^\n]", novo_diretor);
                printf("Novo gênero: ");
                scanf(" %[^\n]", novo_genero);
                printf("Nova duração: ");
                scanf("%d", &nova_duracao);
                TARVB_modifica_secundarias(a, titulo, ano, novo_diretor, novo_genero, nova_duracao); // melhorar essa função
                break;
            case 4:
                printf("Escolha: Buscar filmes de um diretor\n");
                printf("Diretor: ");
                scanf(" %[^\n]", diretor);
                // falta essa função
                break;
            case 5:
                printf("Escolha: Retirar filmes de um diretor\n");
                printf("Diretor: ");
                scanf(" %[^\n]", diretor);
                a = TARVB_remove_filmes_diretor(a, diretor, t);
                break;
            case 6:
                printf("Escolha: Retirar filmes de um gênero\n");
                printf("Gênero: ");
                scanf(" %[^\n]", genero);
                // falta essa função
                break;
            case 7:
                printf("Escolha: Retirar filmes de uma franquia\n");
                printf("Franquia: ");
                scanf(" %[^\n]", franquia);
                a = TARVB_remove_filmes_franquia(a, franquia, t); // melhorar essa função
                break;
            default:
                continua = 0;
                printf("Escolha: Sair\n");
                break;
        }
    }

    TARVB_libera(a);

    return 0;
}