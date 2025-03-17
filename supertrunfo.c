#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CARTAS 100

typedef struct {
    char codigo[4];
    char nomeCidade[50];
    char estado;
    int populacao;
    float area;
    float pib;
    int pontosTuristicos;
    int pontosVitoria;
} Carta;

void cadastrarCarta(Carta *carta) {
    printf("\nCadastro da carta:\n");

    printf("Código (3 caracteres): ");
    scanf("%s", carta->codigo);

    printf("Nome da Cidade: ");
    scanf(" %[^\n]", carta->nomeCidade);

    printf("Estado (1 caractere): ");
    scanf(" %c", &carta->estado);

    printf("População: ");
    scanf("%d", &carta->populacao);

    printf("Área (em km²): ");
    scanf("%f", &carta->area);

    printf("PIB (em bilhões): ");
    scanf("%f", &carta->pib);

    printf("Pontos turísticos: ");
    scanf("%d", &carta->pontosTuristicos);

    carta->pontosVitoria = 0;

    printf("\nCarta cadastrada com sucesso!\n");
}

void listarCartas(Carta *cartas, int totalCartas) {
    printf("\nListando cartas cadastradas:\n");
    if (totalCartas == 0) {
        printf("Nenhuma carta cadastrada.\n");
    } else {
        for (int i = 0; i < totalCartas; i++) {
            printf("%d - Código: %s, Cidade: %s, Estado: %c\n", 
                   i + 1, cartas[i].codigo, cartas[i].nomeCidade, cartas[i].estado);
        }
    }
}

void salvarCartasEmArquivo(Carta *cartas, int totalCartas) {
    FILE *arquivo = fopen("cartas.txt", "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar!\n");
        return;
    }

    for (int i = 0; i < totalCartas; i++) {
        fprintf(arquivo, "%s,%s,%c,%d,%.2f,%.2f,%d,%d\n", 
                cartas[i].codigo, cartas[i].nomeCidade, cartas[i].estado, 
                cartas[i].populacao, cartas[i].area, cartas[i].pib, 
                cartas[i].pontosTuristicos, cartas[i].pontosVitoria);
    }

    fclose(arquivo);
    printf("Cartas salvas com sucesso!\n");
}

int carregarCartasDeArquivo(Carta *cartas) {
    FILE *arquivo = fopen("cartas.txt", "r");
    int totalCartas = 0;

    if (arquivo == NULL) {
        printf("Nenhum arquivo encontrado. Criando novo arquivo.\n");
        return 0;
    }

    while (fscanf(arquivo, "%3s,%49[^,],%c,%d,%f,%f,%d,%d\n", 
                  cartas[totalCartas].codigo, cartas[totalCartas].nomeCidade, 
                  &cartas[totalCartas].estado, &cartas[totalCartas].populacao, 
                  &cartas[totalCartas].area, &cartas[totalCartas].pib, 
                  &cartas[totalCartas].pontosTuristicos, 
                  &cartas[totalCartas].pontosVitoria) == 8) {
        totalCartas++;
        if (totalCartas >= MAX_CARTAS) break;
    }

    fclose(arquivo);
    return totalCartas;
}

void compararCartas(Carta carta1, Carta carta2) {
    int pontos1 = 0, pontos2 = 0;

    if (carta1.populacao > carta2.populacao) pontos1++;
    else if (carta1.populacao < carta2.populacao) pontos2++;

    if (carta1.area > carta2.area) pontos1++;
    else if (carta1.area < carta2.area) pontos2++;

    if (carta1.pib > carta2.pib) pontos1++;
    else if (carta1.pib < carta2.pib) pontos2++;

    if (carta1.pontosTuristicos > carta2.pontosTuristicos) pontos1++;
    else if (carta1.pontosTuristicos < carta2.pontosTuristicos) pontos2++;

    printf("\nResultado da comparação:\n");
    if (pontos1 > pontos2) {
        printf("%s venceu!\n", carta1.nomeCidade);
    } else if (pontos2 > pontos1) {
        printf("%s venceu!\n", carta2.nomeCidade);
    } else {
        printf("Empate entre %s e %s!\n", carta1.nomeCidade, carta2.nomeCidade);
    }
}

void compararTodasAsCartas(Carta *cartas, int totalCartas) {
    // Zerar pontos de vitória antes de começar a contagem
    for (int i = 0; i < totalCartas; i++) {
        cartas[i].pontosVitoria = 0;
    }

    for (int i = 0; i < totalCartas; i++) {
        for (int j = i + 1; j < totalCartas; j++) {
            int pontos1 = 0, pontos2 = 0;

            if (cartas[i].populacao > cartas[j].populacao) pontos1++;
            else if (cartas[i].populacao < cartas[j].populacao) pontos2++;

            if (cartas[i].area > cartas[j].area) pontos1++;
            else if (cartas[i].area < cartas[j].area) pontos2++;

            if (cartas[i].pib > cartas[j].pib) pontos1++;
            else if (cartas[i].pib < cartas[j].pib) pontos2++;

            if (cartas[i].pontosTuristicos > cartas[j].pontosTuristicos) pontos1++;
            else if (cartas[i].pontosTuristicos < cartas[j].pontosTuristicos) pontos2++;

            if (pontos1 > pontos2) {
                cartas[i].pontosVitoria++;  // Incrementa a vitória da carta 1
            } else if (pontos2 > pontos1) {
                cartas[j].pontosVitoria++;  // Incrementa a vitória da carta 2
            }
        }
    }

    // Ordenar as cartas por pontos de vitória (maior para menor)
    for (int i = 0; i < totalCartas - 1; i++) {
        for (int j = i + 1; j < totalCartas; j++) {
            if (cartas[i].pontosVitoria < cartas[j].pontosVitoria) {
                Carta temp = cartas[i];
                cartas[i] = cartas[j];
                cartas[j] = temp;
            }
        }
    }

    // Exibir pódio
    printf("\nPódio das Cartas:\n");
    printf("1º Lugar: %s (%d vitórias)\n", cartas[0].nomeCidade, cartas[0].pontosVitoria);
    if (totalCartas > 1) {
        printf("2º Lugar: %s (%d vitórias)\n", cartas[1].nomeCidade, cartas[1].pontosVitoria);
    }
    if (totalCartas > 2) {
        printf("3º Lugar: %s (%d vitórias)\n", cartas[2].nomeCidade, cartas[2].pontosVitoria);
    }
}

int main() {
    Carta cartas[MAX_CARTAS];
    int totalCartas = carregarCartasDeArquivo(cartas);
    int opcao;

    do {
        printf("\n1 - Cadastrar nova carta\n");
        printf("2 - Listar cartas\n");
        printf("3 - Comparar duas cartas\n");
        printf("4 - Comparar todas as cartas e ver o pódio\n");
        printf("5 - Salvar e sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                if (totalCartas < MAX_CARTAS) {
                    cadastrarCarta(&cartas[totalCartas]);
                    totalCartas++;
                } else {
                    printf("Limite de cartas atingido.\n");
                }
                break;
            case 2:
                listarCartas(cartas, totalCartas);
                break;
            case 3:
                if (totalCartas >= 2) {
                    int indice1, indice2;
                    listarCartas(cartas, totalCartas);
                    printf("Escolha o índice das duas cartas para comparar: ");
                    scanf("%d %d", &indice1, &indice2);
                    compararCartas(cartas[indice1 - 1], cartas[indice2 - 1]);
                } else {
                    printf("É necessário pelo menos 2 cartas!\n");
                }
                break;
            case 4:
                compararTodasAsCartas(cartas, totalCartas);
                break;
            case 5:
                salvarCartasEmArquivo(cartas, totalCartas);
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while(opcao != 5);

    return 0;
}