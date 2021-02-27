#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define TAM 5

void criar_arquivo(char nome_arquivo[])
{
    FILE *arquivo = fopen(nome_arquivo, "w");

    if (arquivo == NULL) {
        printf("\n\nNão foi possível criar o arquivo \"%s\".\n", nome_arquivo);
        return;
    }

    fprintf(arquivo, "0\n");

    printf("\n\nO arquivo \"%s\" foi criado com sucesso.\n", nome_arquivo);
    fclose(arquivo);
    return;
}

int ler_arquivo(char nome_arquivo[])
{
    FILE *arquivo = fopen(nome_arquivo, "r");

    if (arquivo == NULL) {
        printf("\n\nNão foi possível abrir o arquivo \"%s\" para leitura.\n", nome_arquivo);
        criar_arquivo(nome_arquivo);
        return 0;
    }

    int pontuacao = 0;

    if (fscanf(arquivo, "%d", &pontuacao) != 1) {
        printf("\n\nNão foi possível ler do arquivo \"%s\".\n", nome_arquivo);
        fclose(arquivo);
        return 0;
    }

    printf("\n\nO arquivo \"%s\" foi lido com sucesso.\n", nome_arquivo);
    fclose(arquivo);
    return pontuacao;
}

void gravar_arquivo(char nome_arquivo[], int pontuacao)
{
    FILE *arquivo = fopen(nome_arquivo, "w");

    if (arquivo == NULL) {
        printf("\nNão foi possível abrir o arquivo \"%s\" para gravação.\n", nome_arquivo);
        return;
    }

    fprintf(arquivo, "%d\n", pontuacao);

    printf("\nO arquivo \"%s\" foi gravado com sucesso.\n", nome_arquivo);
    fclose(arquivo);
    return;
}

void preencher_tabuleiro(int max, int tab[TAM][TAM])
{
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tab[i][j] == 0) {
                tab[i][j] = (rand() % max) + 1;
            }
        }
    }
}

void mudar_cor(int val)
{
    int cor_fundo[] = {12, 11, 9, 10, 28, 49, 214, 105, 203, 66};

    printf("%c[38;5;0;48;5;%dm", 27, cor_fundo[val - 1]);
}

void resetar_cor(void)
{
    printf("%c[0m", 27);
}

void imprimir_valor(int val)
{
    mudar_cor(val);
    printf("%2d ", val);
    resetar_cor();
}

void imprimir_tabuleiro(int tab[TAM][TAM])
{
    printf("\n\n    1  2  3  4  5   \n\n");
    for (int i = 0; i < TAM; i++) {
        printf("%d  ", i + 1);
        for (int j = 0; j < TAM; j++) {
            imprimir_valor(tab[i][j]);
        }
        printf("\n");
    }
}

void imprimir_pontuacao(int pontuacao)
{
    printf("\n\nPontuação: %d\n", pontuacao);
}

void inicio(void)
{
    printf("\n\nVamos jogar Get10!!\n");
    printf("\n\n[caso queira sair do jogo, digite 0]\n");
}

void final(int pontuacao)
{
    char nome_arquivo[] = "pontuacao-maxima";
    int pontuacao_maxima = ler_arquivo(nome_arquivo);
    
    printf("\n\nSua pontuação: %d", pontuacao);
    printf("\n\nPontuação máxima: %d", pontuacao_maxima);

    if (pontuacao > pontuacao_maxima) {
        printf("\n\nPontuação máxima atualizada: %d", pontuacao);
        printf("\n\nParabéns! Você superou a pontuação máxima por %d pontos.\n", pontuacao - pontuacao_maxima);
        gravar_arquivo(nome_arquivo, pontuacao);
    }
}

bool confirmar_saida(void)
{
    while (true) {
        char sair;

        printf("\n\nVocê realmente deseja sair do jogo? [s/n]\n");
        scanf(" %c", &sair);

        if (sair == 's' || sair == 'S') {
            return true;
        } else if (sair == 'n' || sair == 'N') {
            return false;
        } else {
            printf("\n\nOpção inválida. Tente novamente...\n");
            continue;
        }
    }
}

bool jogar_novamente(void)
{
    while (true) {
        char escolha;

        printf("\n\nVocê deseja jogar novamente? [s/n]\n");
        scanf(" %c", &escolha);

        if (escolha == 's' || escolha == 'S') {
            return true;
        } else if (escolha == 'n' || escolha == 'N') {
            return false;
        } else {
            printf("\n\nEscolha inválida. Tente novamente...\n");
            continue;
        }
    }
}

int pedir_linha(void)
{
    while (true) {
        int lin;

        printf("\n\nDigite uma linha [1 - 5]: ");
        scanf("%d", &lin);

        if (lin == 0) {
            if (confirmar_saida()) {
                exit(1);
            }
        }

        if (lin < 1 || lin > 5) {
            printf("\n\nLinha inválida. Tente novamente...\n");
            continue;
        }

        return lin - 1;
    }
}

int pedir_coluna(void)
{
    while (true) {
        int col;

        printf("\n\nDigite uma coluna [1 - 5]: ");
        scanf("%d", &col);

        if (col == 0) {
            if (confirmar_saida()) {
                exit(1);
            }
        }

        if (col < 1 || col > 5) {
            printf("\n\nColuna inválida. Tente novamente...\n");
            continue;
        }

        return col - 1;
    }
}

bool tem_vizinho(int lin, int col, int tab[TAM][TAM])
{
    if (lin < (TAM - 1) && tab[lin + 1][col] == tab[lin][col]) {
        return true;
    }

    if (col < (TAM - 1) && tab[lin][col + 1] == tab[lin][col]) {
        return true;
    }

    return false;    
}

bool tem_jogada(int tab[TAM][TAM])
{
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tem_vizinho(i, j, tab)) {
                return true;
            }
        }
    }

    printf("\n\nNão há mais jogadas possíveis no tabuleiro...\n");
    return false;
}

bool chegou_no_10(int tab[TAM][TAM])
{
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tab[i][j] == 10) {
                return true;
            }
        }
    }

    return false;
}

void subir_zeros(int tab[TAM][TAM])
{
    for (int col = 0; col < TAM; col++) {
        for (int lin = (TAM - 1); lin > 0; lin--) {
            if (tab[lin][col] != 0) {
                continue;
            }
            for (int i = lin - 1; i >= 0; i--) {
                if (tab[i][col] == 0) {
                    continue;
                }
                tab[lin][col] = tab[i][col];
                tab[i][col] = 0;
                break;
            }
        }
    }
}

int trocar_regiao_por_zeros(int lin, int col, int val, int tab[TAM][TAM])
{
    if (lin < 0 || lin > (TAM - 1) || col < 0 || col > (TAM - 1)) {
        return 0;
    }

    if (tab[lin][col] != val) {
        return 0;
    }

    tab[lin][col] = 0;
    int n_trocados = 1;

    n_trocados += trocar_regiao_por_zeros(lin - 1, col, val, tab);
    n_trocados += trocar_regiao_por_zeros(lin + 1, col, val, tab);
    n_trocados += trocar_regiao_por_zeros(lin, col - 1, val, tab);
    n_trocados += trocar_regiao_por_zeros(lin, col + 1, val, tab);
    
    return n_trocados;
}

int jogar(int lin, int col, int max, int tab[TAM][TAM])
{
    int val = tab[lin][col];
    int novo_val = val + 1;
    int pontuacao = 0;
    int n_trocados = trocar_regiao_por_zeros(lin, col, val, tab);
    
    if (n_trocados > 1) {
        tab[lin][col] = novo_val;
        subir_zeros(tab);
        pontuacao = n_trocados * novo_val;

        if (novo_val > max) {
            max = novo_val;
            pontuacao *= 2;
        }

        preencher_tabuleiro(max - 1, tab);
        return pontuacao;
    } else {
        printf("\n\nNão há jogada na posição informada. Tente novamente...\n");
        tab[lin][col] = val;
        return 0;
    }
}

int partida(void)
{
    int tab[TAM][TAM] = {{0}};
    int max = 3;
    int pontuacao = 0;

    preencher_tabuleiro(max, tab);
    
    while (tem_jogada(tab) && !chegou_no_10(tab)) {
        imprimir_tabuleiro(tab);
        imprimir_pontuacao(pontuacao);

        int lin = pedir_linha();
        int col = pedir_coluna();

        pontuacao += jogar(lin, col, max, tab);
    }
    
    imprimir_tabuleiro(tab);
    return pontuacao;
}

int main(void)
{
    srand(time(NULL));
    
    do {
        inicio();
        int pontuacao = partida();
        final(pontuacao);
    } while (jogar_novamente());

    return 0;
}