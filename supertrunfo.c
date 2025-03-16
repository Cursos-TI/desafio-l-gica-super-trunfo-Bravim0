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

void compararTodasAsCaracteristicas(Carta carta1, Carta carta2) {
    int pontos1 = 0, pontos2 = 0;
    
    if (carta1.populacao > carta2.populacao) pontos1++;
    else if (carta1.populacao < carta2.populacao) pontos2++;
    
    if (carta1.area > carta2.area) pontos1++;
    else if (carta1.area < carta2.area) pontos2++;
    
    if (carta1.pib > carta2.pib) pontos1++;
    else if (carta1.pib < carta2.pib) pontos2++;
    
    if (carta1.pontosTuristicos > carta2.pontosTuristicos) pontos1++;
    else if (carta1.pontosTuristicos < carta2.pontosTuristicos) pontos2++;
    
    printf("\nResultado da comparação:");
    printf("\n%s venceu em %d atributos", carta1.nomeCidade, pontos1);
    printf("\n%s venceu em %d atributos\n", carta2.nomeCidade, pontos2);
    
    if (pontos1 > pontos2)
        printf("\n>> %s é a vencedora!\n", carta1.nomeCidade);
    else if (pontos1 < pontos2)
        printf("\n>> %s é a vencedora!\n", carta2.nomeCidade);
    else
        printf("\n>> Empate!\n");
}

void compararCartas(Carta *cartas, int totalCartas) {
    int opcao;
    int carta1, carta2;

    printf("\nEscolha a primeira carta (1 a %d): ", totalCartas);
    scanf("%d", &carta1);
    printf("Escolha a segunda carta (1 a %d): ", totalCartas);
    scanf("%d", &carta2);

    // Ajusta para o índice do vetor (começando do 0)
    carta1--;
    carta2--;

    printf("\nEscolha a opção de comparação:\n");
    printf("1 - Comparar um único atributo\n");
    printf("2 - Comparar todos os atributos\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    if (opcao == 1) {
        printf("\nEscolha o atributo para comparar:\n");
        printf("1 - População\n2 - Área\n3 - PIB\n4 - Pontos turísticos\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                printf("\nPopulação: %s: %d vs %s: %d\n", cartas[carta1].nomeCidade, cartas[carta1].populacao, cartas[carta2].nomeCidade, cartas[carta2].populacao);
                if (cartas[carta1].populacao > cartas[carta2].populacao)
                    printf(">> %s venceu!\n", cartas[carta1].nomeCidade);
                else if (cartas[carta1].populacao < cartas[carta2].populacao)
                    printf(">> %s venceu!\n", cartas[carta2].nomeCidade);
                else
                    printf(">> Empate!\n");
                break;
            case 2:
                printf("\nÁrea: %s: %.2f km² vs %s: %.2f km²\n", cartas[carta1].nomeCidade, cartas[carta1].area, cartas[carta2].nomeCidade, cartas[carta2].area);
                if (cartas[carta1].area > cartas[carta2].area)
                    printf(">> %s venceu!\n", cartas[carta1].nomeCidade);
                else if (cartas[carta1].area < cartas[carta2].area)
                    printf(">> %s venceu!\n", cartas[carta2].nomeCidade);
                else
                    printf(">> Empate!\n");
                break;
            case 3:
                printf("\nPIB: %s: %.2f bi vs %s: %.2f bi\n", cartas[carta1].nomeCidade, cartas[carta1].pib, cartas[carta2].nomeCidade, cartas[carta2].pib);
                if (cartas[carta1].pib > cartas[carta2].pib)
                    printf(">> %s venceu!\n", cartas[carta1].nomeCidade);
                else if (cartas[carta1].pib < cartas[carta2].pib)
                    printf(">> %s venceu!\n", cartas[carta2].nomeCidade);
                else
                    printf(">> Empate!\n");
                break;
            case 4:
                printf("\nPontos turísticos: %s: %d vs %s: %d\n", cartas[carta1].nomeCidade, cartas[carta1].pontosTuristicos, cartas[carta2].nomeCidade, cartas[carta2].pontosTuristicos);
                if (cartas[carta1].pontosTuristicos > cartas[carta2].pontosTuristicos)
                    printf(">> %s venceu!\n", cartas[carta1].nomeCidade);
                else if (cartas[carta1].pontosTuristicos < cartas[carta2].pontosTuristicos)
                    printf(">> %s venceu!\n", cartas[carta2].nomeCidade);
                else
                    printf(">> Empate!\n");
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }
    } else if (opcao == 2) {
        compararTodasAsCaracteristicas(cartas[carta1], cartas[carta2]);
    } else {
        printf("Opção inválida!\n");
    }
}

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

    printf("\nCarta cadastrada com sucesso!\n");
}

void listarCartas(Carta *cartas, int totalCartas) {
    printf("\nListando cartas cadastradas:\n");
    if (totalCartas == 0) {
        printf("Nenhuma carta cadastrada.\n");
    } else {
        for (int i = 0; i < totalCartas; i++) {
            printf("%d - Código: %s, Cidade: %s, Estado: %c\n", i + 1, cartas[i].codigo, cartas[i].nomeCidade, cartas[i].estado);
        }
    }
}

// Função para salvar as cartas em um arquivo
void salvarCartasEmArquivo(Carta *cartas, int totalCartas) {
    FILE *arquivo = fopen("cartas.txt", "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar!\n");
        return;
    }

    for (int i = 0; i < totalCartas; i++) {
        fprintf(arquivo, "%s,%s,%c,%d,%.2f,%.2f,%d\n", 
                cartas[i].codigo, cartas[i].nomeCidade, cartas[i].estado, 
                cartas[i].populacao, cartas[i].area, cartas[i].pib, 
                cartas[i].pontosTuristicos);
    }

    fclose(arquivo);
    printf("Cartas salvas com sucesso no arquivo 'cartas.txt'!\n");
}

// Função para carregar as cartas a partir do arquivo
int carregarCartasDeArquivo(Carta *cartas) {
    FILE *arquivo = fopen("cartas.txt", "r");
    int totalCartas = 0;

    if (arquivo == NULL) {
        printf("Nenhum arquivo de cartas encontrado. Criando um novo arquivo.\n");
        return 0; // Nenhuma carta carregada
    }

    while (fscanf(arquivo, "%3s,%49[^,],%c,%d,%f,%f,%d\n", 
                  cartas[totalCartas].codigo, cartas[totalCartas].nomeCidade, 
                  &cartas[totalCartas].estado, &cartas[totalCartas].populacao, 
                  &cartas[totalCartas].area, &cartas[totalCartas].pib, 
                  &cartas[totalCartas].pontosTuristicos) == 7) {
        totalCartas++;
        if (totalCartas >= MAX_CARTAS) break;
    }

    fclose(arquivo);
    return totalCartas;
}

int main() {
    Carta cartas[MAX_CARTAS];
    int totalCartas = carregarCartasDeArquivo(cartas); // Carregar cartas ao iniciar
    int opcao;

    do {
        printf("\n1 - Cadastrar nova carta\n");
        printf("2 - Listar cartas\n");
        printf("3 - Comparar cartas\n");
        printf("4 - Salvar e sair\n");
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
                    compararCartas(cartas, totalCartas);
                } else {
                    printf("É necessário ter pelo menos 2 cartas para comparar!\n");
                }
                break;
            case 4:
                salvarCartasEmArquivo(cartas, totalCartas); // Salva as cartas no arquivo antes de sair
                printf("Salvando e saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while(opcao != 4);

    return 0;
}