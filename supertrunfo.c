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

    printf("Código (3 caracteres): ");
    scanf("%s", carta->codigo);

    printf("Nome da Cidade: ");
    scanf(" %[^\n]", carta->nomeCidade);

    printf("Estado (1 caractere): ");
    scanf(" %c", &carta->estado);

    printf("População: ");
    scanf("%d", &carta->populacao);

    printf("Área (em km²): ");
    scanf("%f", &carta->area);

    printf("PIB (em bilhões): ");
    scanf("%f", &carta->pib);

    printf("Pontos turísticos: ");
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
            printf("%d - Código: %s, Cidade: %s, Estado: %c\n", 
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

void compararCartasSelecionadas(Carta *cartasSelecionadas, int numCartasSelecionadas) {
    if (numCartasSelecionadas < 2) {
        printf("É necessário selecionar pelo menos 2 cartas para comparação!\n");
        return;
    }

    int pontos[numCartasSelecionadas];

    for (int i = 0; i < numCartasSelecionadas; i++) {
        pontos[i] = 0;
    }

    for (int i = 0; i < numCartasSelecionadas; i++) {
        for (int j = i + 1; j < numCartasSelecionadas; j++) {
            int pontos1 = 0, pontos2 = 0;

            if (cartasSelecionadas[i].populacao > cartasSelecionadas[j].populacao) pontos1++;
            else if (cartasSelecionadas[i].populacao < cartasSelecionadas[j].populacao) pontos2++;

            if (cartasSelecionadas[i].area > cartasSelecionadas[j].area) pontos1++;
            else if (cartasSelecionadas[i].area < cartasSelecionadas[j].area) pontos2++;

            if (cartasSelecionadas[i].pib > cartasSelecionadas[j].pib) pontos1++;
            else if (cartasSelecionadas[i].pib < cartasSelecionadas[j].pib) pontos2++;

            if (cartasSelecionadas[i].pontosTuristicos > cartasSelecionadas[j].pontosTuristicos) pontos1++;
            else if (cartasSelecionadas[i].pontosTuristicos < cartasSelecionadas[j].pontosTuristicos) pontos2++;

            if (pontos1 > pontos2) {
                pontos[i]++;
            } else if (pontos2 > pontos1) {
                pontos[j]++;
            }
        }
    }

    int vencedorIndex = 0;
    for (int i = 1; i < numCartasSelecionadas; i++) {
        if (pontos[i] > pontos[vencedorIndex]) {
            vencedorIndex = i;
        }
    }

    printf("\nA carta vencedora é: %s\n", cartasSelecionadas[vencedorIndex].nomeCidade);
    printf("Com %d vitórias!\n", pontos[vencedorIndex]);
}

void compararTodasAsCartas(Carta *cartas, int totalCartas) {
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
                cartas[i].pontosVitoria++;
            } else if (pontos2 > pontos1) {
                cartas[j].pontosVitoria++;
            }
        }
    }

    for (int i = 0; i < totalCartas - 1; i++) {
        for (int j = i + 1; j < totalCartas; j++) {
            if (cartas[i].pontosVitoria < cartas[j].pontosVitoria) {
                Carta temp = cartas[i];
                cartas[i] = cartas[j];
                cartas[j] = temp;
            }
        }
    }

    printf("\nPódio das Cartas:\n");
    printf("1º Lugar: %s (%d vitórias)\n", cartas[0].nomeCidade, cartas[0].pontosVitoria);
    if (totalCartas > 1) {
        printf("2º Lugar: %s (%d vitórias)\n", cartas[1].nomeCidade, cartas[1].pontosVitoria);
    }
    if (totalCartas > 2) {
        printf("3º Lugar: %s (%d vitórias)\n", cartas[2].nomeCidade, cartas[2].pontosVitoria);
    }
}

int main() {
    Carta cartas[MAX_CARTAS];
    int totalCartas = carregarCartasDeArquivo(cartas);
    int opcao;

    do {
        printf("\n1 - Cadastrar nova carta\n");
        printf("2 - Listar cartas\n");
        printf("3 - Comparar cartas selecionadas\n");
        printf("4 - Comparar todas as cartas e ver o pódio\n");
        printf("5 - Salvar e sair\n");
        printf("Escolha uma opção: ");
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
            case 3: {
                int numCartasSelecionadas;
                printf("Quantas cartas deseja comparar? ");
                scanf("%d", &numCartasSelecionadas);

                if (numCartasSelecionadas <= 1) {
                    printf("É necessário selecionar pelo menos 2 cartas para comparação!\n");
                    break;
                }

                listarCartas(cartas, totalCartas);
                Carta cartasSelecionadas[numCartasSelecionadas];
                printf("Escolha as cartas pelo índice (1 a %d):\n", totalCartas);
                for (int i = 0; i < numCartasSelecionadas; i++) {
                    int indice;
                    printf("Carta %d: ", i + 1);
                    scanf("%d", &indice);
                    if (indice >= 1 && indice <= totalCartas) {
                        cartasSelecionadas[i] = cartas[indice - 1];
                    } else {
                        printf("Índice inválido, tente novamente.\n");
                        i--;
                    }
                }

                compararCartasSelecionadas(cartasSelecionadas, numCartasSelecionadas);
                break;
            }
            case 4:
                compararTodasAsCartas(cartas, totalCartas);
                break;
            case 5:
                salvarCartasEmArquivo(cartas, totalCartas);
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while(opcao != 5);

    return 0;
}