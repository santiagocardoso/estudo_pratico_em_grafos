#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "funcoes.h"

// Funcao que retorna o tamanho de uma pilha, onde caso pilha esteja vazia seus elementos pilha[0], pilha[1], pilha[2]... terao todos valor = -1.
int len(int v[]){
    int count = 0;
    for(int i = 0; i<150;i++){
       if(v[i]!=-1){
            count++;
       }
    }
    return count;
}

// Cria pilha com todos os elementos iguais a -1
int *criar_pilha(){
    int *v = malloc(sizeof(int)*150);

    for(int i = 0; i<150;i++){
        v[i] = -1;
    }
    return v;
}

void push(int *pilha, int valor){
    pilha[len(pilha)] = valor;
}

void pop(int *pilha){
    if(len(pilha)==0){
            printf("Pilha vazia!");
            return;
    }
    pilha[len(pilha)-1] = -1;
}

int visitados[2][150]; //linha 0 -> visitado : T/F         linha 1 -> vertice predecessor ao visitado : int v

void DFS(int vertice) {
    int** tabela_de_conexoes = criar_matriz_adjacencias();

    visitados[0][vertice] = 1; // Define o vertice como "true" para visitado
    int *pilha = criar_pilha();
    push(pilha, vertice);

    while(len(pilha)>0){
        int topo = pilha[len(pilha)-1];
        int ha_mais_vizinhos = 0;

        for(int i = 0; i<150;i++){
            if(tabela_de_conexoes[topo][i] == 1 && visitados[0][i] == 0){
                visitados[0][i] = 1;
                visitados[1][i] = topo;
                push(pilha,i);
                ha_mais_vizinhos = 1;
            }
        }

        if(ha_mais_vizinhos == 0){
            pop(pilha);
        }

    }
}

int contarComponentesConexos(int v) {

    int num_comps = 0;
    DFS(v);

    for(int i = 0; i<150;i++){
        if(visitados[0][i] == 1){
            num_comps++;
        }
    }

    return num_comps; // Retorna o n�mero de componentes conexos
}

int main(int argc, char *argv[]) {
    int opcao = -1;
    while (opcao != 0) {
        printf("\n[0] Sair\n[1] Ler IrisDataset.csv\n[2] Carregar Grafo.csv\n");
        scanf("%d", &opcao);
        switch (opcao) {
            case 0:
                printf("\nFinalizando o programa...\n");

                break;
            case 1:
                imprime_lista_de_adjacencias();

                break;
            case 2:
                carregar_grafo();

                break;
            default:
                printf("Op��o inv�lida!\n");

                break;
        }
    }

    return 0;
}
