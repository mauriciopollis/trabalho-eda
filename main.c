#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "TARVB.c"

int main(int argc, char* argv[]) {

    int t = atoi(argv[1]);
 
    TARVB *a = TARVB_cria_arvoreb_arquivo(t, argv[2]);
    int op, continua = 1;
    Limpa_tela();
    while(continua) {
        printf("=Menu=============================================\n");
        printf("[0] - Inserir filme\n");
        printf("[1] - Remover filme\n");
        printf("[2] - Buscar informações subordinadas\n");
        printf("[3] - Alterar informações subordinadas\n");
        printf("[4] - Buscar todos os filmes de um diretor\n");
        printf("[5] - Retirar todos os filmes de um diretor\n");
        printf("[6] - Retirar todos os filmes de um gênero\n");
        printf("[7] - Retirar todos os filmes de uma franquia\n");
        //printf("[8] - Ver quantos filmes estão na árvore\n");
        //printf("[9] - Ver quantos nós existem na árvore\n");
        printf("[-1] - Sair\n");
        printf("\nEscolha: ");
        scanf("%d", &op);
        Limpa_tela();

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
                printf("\n");
                TARVB_busca_info_subordinada(a, titulo, ano);
                printf("\n");
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
                TARVB_modifica_secundarias(a, titulo, ano, novo_diretor, novo_genero, nova_duracao);
                break;
            case 4:
                printf("==================================================\n");
                printf("Escolha: Buscar filmes de um diretor\n");
                printf("Diretor: ");
                scanf(" %[^\n]", diretor);
                printf("\n");
                TARVB_lista_filmes_diretor(a, diretor);
                printf("\n");
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
                a = TARVB_remove_filmes_genero(a, genero, t);
                break;
            case 7:
                printf("Escolha: Retirar filmes de uma franquia\n");
                printf("Franquia: ");
                scanf(" %[^\n]", franquia);
                a = TARVB_remove_filmes_franquia(a, franquia, t);
                break;
            //case 8:
            //    printf("Escolha: Ver quantos filmes estão na árvore\n");
            //    printf("Existem %d filmes na árvore\n", TARVB_conta_filmes(a));
            //    break;
            //case 9:
            //    printf("Escolha: Ver quantos nós existem na árvore\n");
            //    printf("Existem %d nós na árvore\n", TARVB_conta_nos(a));
            //    break;
            default:
                continua = 0;
                printf("Escolha: Sair\n");
                break;
        }
    }

    TARVB_libera(a);

    return 0;
}