#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

// 1� passo -> Importar todos os dados
// 2� passo -> montar a tabela euclidiana
// 3� passo -> construção da tabela euclidiana normalizada
// 4� passo -> aplicar o limiar de 0.3
// 5� passo -> salvar o grafo no arquivo Grafo.csv

typedef struct Iris {
    float sep_len;
    float sep_width;
    float pet_len;
    float pet_width;
    char *variety;
} Iris;

float distancia_euclidiana(Iris *flor1, Iris *flor2){
    float DE = sqrt(pow((flor1->sep_len - flor2->sep_len), 2) +
                     pow((flor1->sep_width - flor2->sep_width), 2) +
                     pow((flor1->pet_len - flor2->pet_len), 2) +
                     pow((flor1->pet_width - flor2->pet_width), 2));
    return DE;
}

Iris *lista_de_vertices[150];
char lista_De_variedades[150][100];
float tabela_euclidiana_Norm[150][150];

void ler_arquivo_CSV() {
    FILE *file = fopen("IrisDataset.csv","r");

    char linha[100];
    char *token;

    if (file == NULL) {
        printf("Erro ao abrir o arquivo");
        return;
    }

    int conta_iris = 0;

    while (fgets(linha, 100, file) != NULL) {

        if (conta_iris >= 1) {
            Iris *flor = malloc(sizeof(Iris));

            token = strtok(linha , ",");
            flor->sep_len = atof(token);

            token = strtok(NULL, ",");
            flor->sep_width = atof(token);

            token = strtok(NULL, ",");
            flor->pet_len = atof(token);

            token = strtok(NULL, ",");
            flor->pet_width = atof(token);

            token = strtok(NULL,",");
            strcpy(lista_De_variedades[conta_iris - 1], token);
            flor->variety = lista_De_variedades[conta_iris - 1];


            lista_de_vertices[conta_iris - 1] = flor;
        }

        conta_iris++;
    }

    printf("A quantidade de linhas lida eh %d\n\n", conta_iris);
}

void salvar_grafo() {
    FILE *file = fopen("Grafo.csv","w");

    char linha[100];
    char *token;

    if (file == NULL) {
        printf("Erro ao abrir o arquivo");
        return;
    }

    for (int i = 0; i < 150; i++) {
        for (int z = 0; z < 150; z++) {
            if (i!=z && tabela_euclidiana_Norm[i][z]<=0.3) {
                fprintf(file, "%d %d\n",i ,z);
            }
        }
    }

    fclose(file);
}

void carregar_grafo() {
    FILE *file = fopen("Grafo.csv", "r");

    char linha[100];

    if (file == NULL) {
        printf("Erro ao abrir o arquivo");
        return;
    }

    fgets(linha, sizeof(linha), file);
    while (fgets(linha, sizeof(linha), file) != NULL) {
        char *token = strtok(linha, " ");

        int valor = atoi(token);
        printf("%d ",valor);

        token = strtok(NULL, " ");
        valor = atoi(token);

        printf("%d\n",valor);

    }

    fclose(file);
}

float tabela_euclidiana[150][150];

void criar_tabela_euclidiana(){

    for (int i = 0; i < 150; i++) {
        for (int j = 0; j < 150; j++) {
            tabela_euclidiana[i][j] = distancia_euclidiana(lista_de_vertices[i],lista_de_vertices[j]);
        }
    }

}

float menorValor_da_Linha(int linha){
    float menor = tabela_euclidiana[linha][linha]+10;
    for(int i = 0; i<150;i++){
        if(tabela_euclidiana[linha][i]<menor && i!=linha){
            menor = tabela_euclidiana[linha][i];
        }
    }
    return menor;

}

float maiorValor_da_Linha(int linha){
    float maior = tabela_euclidiana[linha][linha]-10;
    for(int i = 0; i<150;i++){
        if(tabela_euclidiana[linha][i]>maior){
            maior = tabela_euclidiana[linha][i];
        }
    }
    return maior;

}

void criar_tabela_euclidianaNorm(){

    for(int i = 0; i<150;i++){
        for(int j = 0; j<150; j++){

            if(i!=j){
                float DE = distancia_euclidiana(lista_de_vertices[i],lista_de_vertices[j]);
                tabela_euclidiana_Norm[i][j] = (DE - menorValor_da_Linha(i))/(maiorValor_da_Linha(i) - menorValor_da_Linha(i));
            }

            else{
                tabela_euclidiana_Norm[i][j] = 10;
            }

        }
    }
}

void imprime_lista_de_adjacencias() {

    int counter = 0;
    for (int i = 0; i < 150; i++) {
        for (int z = 0; z < 150; z++) {
            if (i!=z && tabela_euclidiana_Norm[i][z]<=0.3) { // ignora os elementos vazios "0" da lista
                printf("%d %d\n",i , z);
                counter++;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int opcao = -1;
    printf("[0] Ler IrisDataset.csv\n[1] Carregar Grafo.csv\n");
    scanf("%d", &opcao);
    switch (opcao) {
        case 0:
            ler_arquivo_CSV();
            criar_tabela_euclidiana();
            criar_tabela_euclidianaNorm();
            salvar_grafo();

            imprime_lista_de_adjacencias();

            break;
        case 1:
            carregar_grafo();
            imprime_lista_de_adjacencias();

            break;
        default:
            printf("Opção inválida!\n");

            break;
    }

    return 0;
}
