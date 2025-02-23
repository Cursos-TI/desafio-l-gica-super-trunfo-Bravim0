#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CARTAS 100  // Define o máximo de cartas que podem ser cadastradas

typedef struct {
    char estado;
    char codigo[4];
    char nomeCidade[50];
    int populacao;
    float area;
    float pib;
    int pontosTuristicos;
} Carta;

// Função para salvar cartas em um arquivo externo
void salvarCartas(Carta *cartas, int numCartas) {
    FILE *arquivo = fopen("cartas.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar!\n");
        return;
    }

    fprintf(arquivo, "%d\n", numCartas); // Salva o número de cartas
    for (int i = 0; i < numCartas; i++) {
        fprintf(arquivo, "%c %s %s %d %.2f %.2f %d\n",
                cartas[i].estado, cartas[i].codigo, cartas[i].nomeCidade,
                cartas[i].populacao, cartas[i].area, cartas[i].pib, cartas[i].pontosTuristicos);
    }
    
    fclose(arquivo);
    printf("Cartas salvas com sucesso!\n");
}

// Função para carregar cartas do arquivo
int carregarCartas(Carta *cartas) {
    FILE *arquivo = fopen("cartas.txt", "r");
    if (arquivo == NULL) {
        printf("Nenhum arquivo de cartas encontrado. Criando um novo...\n");
        return 0;
    }

    int numCartas;
    fscanf(arquivo, "%d", &numCartas); // Lê o número de cartas
    for (int i = 0; i < numCartas; i++) {
        fscanf(arquivo, " %c %s %49[^\n] %d %f %f %d",
               &cartas[i].estado, cartas[i].codigo, cartas[i].nomeCidade,
               &cartas[i].populacao, &cartas[i].area, &cartas[i].pib, &cartas[i].pontosTuristicos);
    }

    fclose(arquivo);
    printf("%d cartas carregadas com sucesso!\n", numCartas);
    return numCartas;
}

int main() {
    Carta cartas[MAX_CARTAS]; // Array de cartas
    int numCartas = carregarCartas(cartas); // Carrega cartas já salvas

    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1 - Cadastrar nova carta\n");
        printf("2 - Listar cartas\n");
        printf("3 - Salvar e sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer

        if (opcao == 1) {
            if (numCartas < MAX_CARTAS) {
                printf("\nDigite os dados da carta %d:\n", numCartas + 1);
                printf("Estado (A-H): ");
                scanf(" %c", &cartas[numCartas].estado);
                printf("Código (ex: C03): ");
                scanf(" %3s", cartas[numCartas].codigo);
                printf("Nome da cidade: ");
                getchar();
                fgets(cartas[numCartas].nomeCidade, 50, stdin);
                strtok(cartas[numCartas].nomeCidade, "\n"); // Remove o \n do final
                printf("População: ");
                scanf("%d", &cartas[numCartas].populacao);
                printf("Área (km²): ");
                scanf("%f", &cartas[numCartas].area);
                printf("PIB (bilhões de reais): ");
                scanf("%f", &cartas[numCartas].pib);
                printf("Número de pontos turísticos: ");
                scanf("%d", &cartas[numCartas].pontosTuristicos);

                numCartas++;
                printf("Carta cadastrada com sucesso!\n");
            } else {
                printf("Limite de cartas atingido!\n");
            }
        } else if (opcao == 2) {
            printf("\nCartas cadastradas:\n");
            for (int i = 0; i < numCartas; i++) {
                printf("\nCarta %d:\n", i + 1);
                printf("Estado: %c\n", cartas[i].estado);
                printf("Código: %s\n", cartas[i].codigo);
                printf("Nome da Cidade: %s\n", cartas[i].nomeCidade);
                printf("População: %d\n", cartas[i].populacao);
                printf("Área: %.2f km²\n", cartas[i].area);
                printf("PIB: %.2f bilhões de reais\n", cartas[i].pib);
                printf("Número de Pontos Turísticos: %d\n", cartas[i].pontosTuristicos);
            }
        }
    } while (opcao != 3);

    salvarCartas(cartas, numCartas);
   return 0;
}
