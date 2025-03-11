#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CARTAS 100

typedef struct {
    char estado;
    char codigo[4];
    char nomeCidade[50];
    int populacao;
    float area;
    float pib;
    int pontosTuristicos;
} Carta;

void salvarCartas(Carta *cartas, int numCartas) {
    FILE *arquivo = fopen("cartas.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar!\n");
        return;
    }

    fprintf(arquivo, "%d\n", numCartas);
    for (int i = 0; i < numCartas; i++) {
        fprintf(arquivo, "%c %s %s %d %.2f %.2f %d\n",
                cartas[i].estado, cartas[i].codigo, cartas[i].nomeCidade,
                cartas[i].populacao, cartas[i].area, cartas[i].pib, cartas[i].pontosTuristicos);
    }
    
    fclose(arquivo);
}

int carregarCartas(Carta *cartas) {
    FILE *arquivo = fopen("cartas.txt", "r");
    if (arquivo == NULL) {
        printf("Nenhum arquivo de cartas encontrado. Criando um novo...\n");
        return 0;
    }

    int numCartas;
    fscanf(arquivo, "%d", &numCartas);
    for (int i = 0; i < numCartas; i++) {
        fscanf(arquivo, " %c %s %49[^\n] %d %f %f %d",
               &cartas[i].estado, cartas[i].codigo, cartas[i].nomeCidade,
               &cartas[i].populacao, &cartas[i].area, &cartas[i].pib, &cartas[i].pontosTuristicos);
    }

    fclose(arquivo);
    printf("%d cartas carregadas com sucesso!\n", numCartas);
    return numCartas;
}

void compararCartas(Carta carta1, Carta carta2) {
    int opcao;
    printf("\nEscolha o atributo para comparar:\n");
    printf("1 - População\n");
    printf("2 - Área\n");
    printf("3 - PIB\n");
    printf("4 - Pontos turísticos\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            printf("\nPopulação:\n");
            printf("%s: %d vs %s: %d\n", carta1.nomeCidade, carta1.populacao, carta2.nomeCidade, carta2.populacao);
            if (carta1.populacao > carta2.populacao)
                printf(">> %s venceu!\n", carta1.nomeCidade);
            else if (carta1.populacao < carta2.populacao)
                printf(">> %s venceu!\n", carta2.nomeCidade);
            else
                printf(">> Empate!\n");
            break;
        case 2:
            printf("\nÁrea:\n");
            printf("%s: %.2f km² vs %s: %.2f km²\n", carta1.nomeCidade, carta1.area, carta2.nomeCidade, carta2.area);
            if (carta1.area > carta2.area)
                printf(">> %s venceu!\n", carta1.nomeCidade);
            else if (carta1.area < carta2.area)
                printf(">> %s venceu!\n", carta2.nomeCidade);
            else
                printf(">> Empate!\n");
            break;
        case 3:
            printf("\nPIB:\n");
            printf("%s: %.2f bi vs %s: %.2f bi\n", carta1.nomeCidade, carta1.pib, carta2.nomeCidade, carta2.pib);
            if (carta1.pib > carta2.pib)
                printf(">> %s venceu!\n", carta1.nomeCidade);
            else if (carta1.pib < carta2.pib)
                printf(">> %s venceu!\n", carta2.nomeCidade);
            else
                printf(">> Empate!\n");
            break;
        case 4:
            printf("\nPontos turísticos:\n");
            printf("%s: %d vs %s: %d\n", carta1.nomeCidade, carta1.pontosTuristicos, carta2.nomeCidade, carta2.pontosTuristicos);
            if (carta1.pontosTuristicos > carta2.pontosTuristicos)
                printf(">> %s venceu!\n", carta1.nomeCidade);
            else if (carta1.pontosTuristicos < carta2.pontosTuristicos)
                printf(">> %s venceu!\n", carta2.nomeCidade);
            else
                printf(">> Empate!\n");
            break;
        default:
            printf("Opção inválida!\n");
            break;
    }
}

int main() {
    Carta cartas[MAX_CARTAS];
    int numCartas = carregarCartas(cartas);

    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1 - Cadastrar nova carta\n");
        printf("2 - Listar cartas\n");
        printf("3 - Comparar cartas\n");
        printf("4 - Salvar e sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        if (opcao == 1) {
            if (numCartas < MAX_CARTAS) {
                printf("\nDigite os dados da nova carta:\n");
                printf("Estado (A-H): ");
                scanf(" %c", &cartas[numCartas].estado);
                printf("Código: ");
                scanf(" %3s", cartas[numCartas].codigo);
                getchar();
                printf("Nome da cidade: ");
                fgets(cartas[numCartas].nomeCidade, 50, stdin);
                strtok(cartas[numCartas].nomeCidade, "\n");
                printf("População: ");
                scanf("%d", &cartas[numCartas].populacao);
                printf("Área (km²): ");
                scanf("%f", &cartas[numCartas].area);
                printf("PIB (bilhões): ");
                scanf("%f", &cartas[numCartas].pib);
                printf("Pontos turísticos: ");
                scanf("%d", &cartas[numCartas].pontosTuristicos);
                numCartas++;
                printf("Carta cadastrada com sucesso!\n");
            } else {
                printf("Limite de cartas atingido!\n");
            }
        } else if (opcao == 2) {
            printf("\nCartas cadastradas:\n");
            for (int i = 0; i < numCartas; i++) {
                printf("%d - %s\n", i + 1, cartas[i].nomeCidade);
            }
        } else if (opcao == 3) {
            int c1, c2;
            printf("\nEscolha duas cartas para comparar (número):\n");
            scanf("%d %d", &c1, &c2);
            if (c1 >= 1 && c1 <= numCartas && c2 >= 1 && c2 <= numCartas && c1 != c2) {
                compararCartas(cartas[c1 - 1], cartas[c2 - 1]);
            } else {
                printf("Cartas inválidas!\n");
            }
        }
    } while (opcao != 4);

    salvarCartas(cartas, numCartas);
    return 0;
}
