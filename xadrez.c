#include <stdio.h>
#include <stdlib.h>

#define BOARD_SIZE 8

// Representação do tabuleiro de xadrez
char board[BOARD_SIZE][BOARD_SIZE];

// Função para inicializar o tabuleiro
void inicializar_tabuleiro() {
    char init[BOARD_SIZE][BOARD_SIZE] = {
        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}
    };

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = init[i][j];
        }
    }
}

// Função para exibir o tabuleiro
void exibir_tabuleiro() {
    printf("  a b c d e f g h\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%d ", 8 - i);
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("%c ", board[i][j]);
        }
        printf("%d\n", 8 - i);
    }
    printf("  a b c d e f g h\n");
}

// Função para converter as coordenadas de notação (ex: "e2 e4") para índices de array
void converter_notacao(char* notacao, int* x1, int* y1, int* x2, int* y2) {
    *y1 = notacao[0] - 'a';  // Coluna inicial (ex: 'e' -> 4)
    *x1 = 8 - (notacao[1] - '0');  // Linha inicial (ex: '2' -> 6)

    *y2 = notacao[3] - 'a';  // Coluna final (ex: 'e' -> 4)
    *x2 = 8 - (notacao[4] - '0');  // Linha final (ex: '4' -> 4)
}

// Função para validar o movimento da peça
int validar_movimento(int x1, int y1, int x2, int y2) {
    // Verificar se o movimento está dentro do tabuleiro
    if (x1 < 0 || x1 >= BOARD_SIZE || y1 < 0 || y1 >= BOARD_SIZE ||
        x2 < 0 || x2 >= BOARD_SIZE || y2 < 0 || y2 >= BOARD_SIZE) {
        return 0;
    }

    // Verificar se o movimento é para uma casa ocupada pela mesma cor
    if ((board[x1][y1] >= 'a' && board[x2][y2] >= 'a') || (board[x1][y1] <= 'Z' && board[x2][y2] <= 'Z')) {
        return 0;
    }

    return 1;
}

// Função para realizar o movimento
void realizar_movimento(int x1, int y1, int x2, int y2) {
    // Realizar o movimento: mover a peça e deixar a casa inicial vazia
    board[x2][y2] = board[x1][y1];
    board[x1][y1] = ' ';
}

int main() {
    char notacao[6];
    int x1, y1, x2, y2;

    inicializar_tabuleiro();

    while (1) {
        exibir_tabuleiro();

        printf("Digite seu movimento (ex: e2 e4): ");
        fgets(notacao, sizeof(notacao), stdin);

        // Converte a notação em coordenadas
        converter_notacao(notacao, &x1, &y1, &x2, &y2);

        // Verifica a validade do movimento
        if (validar_movimento(x1, y1, x2, y2)) {
            realizar_movimento(x1, y1, x2, y2);
        } else {
            printf("Movimento inválido. Tente novamente.\n");
        }
    }

    return 0;
}
