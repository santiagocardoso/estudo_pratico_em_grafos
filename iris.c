#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "funcoes.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf ("Número de argumentos errado!\n");
        return EXIT_FAILURE;
    }

    limiar = atof(argv[1]);

    int opcao = -1;
    int vertice;
    while (opcao != 0) {
        printf("[0] Sair\n[1] Ler IrisDataset.csv\n[2] Carregar Grafo.csv\n[3] Contar componentes conexos (vértice)\n");
        printf("\nOpção: ");
        scanf("%d", &opcao);
        printf("\n");
        switch (opcao) {
            case 0:
                printf("Finalizando o programa...\n");

                break;
            case 1:
                imprime_lista_de_adjacencias();

                break;
            case 2:
                carregar_grafo();

                break;
            case 3:
                printf("Vértice: ");
                scanf("%d", &vertice);
                printf("Componentes: %d\n\n", contarComponentesConexos(vertice));

                break;
            default:
                printf("Op��o inv�lida!\n");

                break;
        }
    }

    return EXIT_SUCCESS;
}
