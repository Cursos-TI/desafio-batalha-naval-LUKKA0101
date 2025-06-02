#include <stdio.h>

#define TAB_SIZE 10
#define NAVIO 3
#define AGUA 0
#define HABILIDADE 5

// Cria o tabuleiro 10x10 e inicializa com 0 (água)
void inicializarTabuleiro(int tabuleiro[TAB_SIZE][TAB_SIZE]) {
    for (int i = 0; i < TAB_SIZE; i++) {
        for (int j = 0; j < TAB_SIZE; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Posiciona navios fixos no tabuleiro (apenas exemplo para teste)
void posicionarNavios(int tabuleiro[TAB_SIZE][TAB_SIZE]) {
    // Dois navios horizontais/verticais (tamanho 3)
    // Navio 1 horizontal linha 1, colunas 1 a 3
    for (int c = 1; c <= 3; c++) {
        tabuleiro[1][c] = NAVIO;
    }
    // Navio 2 vertical col 5, linhas 5 a 7
    for (int l = 5; l <= 7; l++) {
        tabuleiro[l][5] = NAVIO;
    }

    // Dois navios diagonais tamanho 3
    // Diagonal principal (i,i) linhas 3 a 5
    for (int i = 3; i <= 5; i++) {
        tabuleiro[i][i] = NAVIO;
    }
    // Diagonal anti (i, TAB_SIZE-1 - i) linhas 6 a 8
    for (int i = 6; i <= 8; i++) {
        tabuleiro[i][TAB_SIZE - 1 - i] = NAVIO;
    }
}

// Cria a matriz do cone 5x5 (cone apontando para baixo)
// Topo na linha 0, largura aumentando até linha 4
void criarCone(int cone[5][5]) {
    for (int i = 0; i < 5; i++) {       // linhas
        for (int j = 0; j < 5; j++) {   // colunas
            // Condição para formar um cone:
            // Na linha i, as colunas afetadas vão do (2 - i) até (2 + i)
            // Cuidado com limites da matriz (0 a 4)
            if (j >= 2 - i && j <= 2 + i) {
                cone[i][j] = 1;
            } else {
                cone[i][j] = 0;
            }
        }
    }
}

// Cria a matriz da cruz 5x5 (cruz no centro)
void criarCruz(int cruz[5][5]) {
    for (int i = 0; i < 5; i++) {       // linhas
        for (int j = 0; j < 5; j++) {   // colunas
            if (i == 2 || j == 2) {     // linha central ou coluna central
                cruz[i][j] = 1;
            } else {
                cruz[i][j] = 0;
            }
        }
    }
}

// Cria a matriz do octaedro 5x5 (losango com centro em (2,2))
void criarOctaedro(int octaedro[5][5]) {
    for (int i = 0; i < 5; i++) {       // linhas
        for (int j = 0; j < 5; j++) {   // colunas
            // Distância Manhattan do centro (2,2)
            int dist = abs(i - 2) + abs(j - 2);
            if (dist <= 2) {
                octaedro[i][j] = 1;
            } else {
                octaedro[i][j] = 0;
            }
        }
    }
}

// Sobrepõe a matriz de habilidade no tabuleiro a partir do ponto origem (linhaOrigem, colOrigem)
// marca as posições afetadas com valor HABILIDADE (5)
void aplicarHabilidade(int tabuleiro[TAB_SIZE][TAB_SIZE], int habilidade[5][5], int linhaOrigem, int colOrigem) {
    int tamanhoHabilidade = 5;
    int meio = tamanhoHabilidade / 2;  // 2

    for (int i = 0; i < tamanhoHabilidade; i++) {
        for (int j = 0; j < tamanhoHabilidade; j++) {
            if (habilidade[i][j] == 1) {
                // Calcula a posição no tabuleiro
                int linhaTab = linhaOrigem - meio + i;
                int colTab = colOrigem - meio + j;

                // Valida limites do tabuleiro
                if (linhaTab >= 0 && linhaTab < TAB_SIZE && colTab >= 0 && colTab < TAB_SIZE) {
                    // Se não for navio, marca como área de efeito
                    if (tabuleiro[linhaTab][colTab] == AGUA) {
                        tabuleiro[linhaTab][colTab] = HABILIDADE;
                    }
                }
            }
        }
    }
}

// Exibe o tabuleiro formatado
void exibirTabuleiro(int tabuleiro[TAB_SIZE][TAB_SIZE]) {
    printf("\nTabuleiro:\n");
    for (int i = 0; i < TAB_SIZE; i++) {
        for (int j = 0; j < TAB_SIZE; j++) {
            if (tabuleiro[i][j] == AGUA) {
                printf(" 0 ");
            } else if (tabuleiro[i][j] == NAVIO) {
                printf(" 3 ");
            } else if (tabuleiro[i][j] == HABILIDADE) {
                printf(" 5 ");
            } else {
                printf(" ? "); // caso inesperado
            }
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAB_SIZE][TAB_SIZE];
    int cone[5][5], cruz[5][5], octaedro[5][5];

    // Inicializa o tabuleiro com água
    inicializarTabuleiro(tabuleiro);

    // Posiciona os navios (fixos)
    posicionarNavios(tabuleiro);

    // Cria as matrizes de habilidades
    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);

    // Aplica as habilidades no tabuleiro
    // Pontos de origem definidos arbitrariamente
    aplicarHabilidade(tabuleiro, cone, 1, 2);      // perto do topo
    aplicarHabilidade(tabuleiro, cruz, 7, 7);      // mais pra baixo e direita
    aplicarHabilidade(tabuleiro, octaedro, 4, 5);  // centro

    // Exibe o tabuleiro final com navios e áreas de habilidade
    exibirTabuleiro(tabuleiro);

    return 0;
}
