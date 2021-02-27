#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAM 9

void ler_nome_arquivo(char nome_arquivo[])
{
    printf("\n\nInforme o nome de um arquivo: ");
    scanf(" %s", nome_arquivo);
}

void criar_arquivo(char nome_arquivo[])
{
    FILE *arquivo = fopen(nome_arquivo, "w");

    if (arquivo == NULL) {
        printf("\n\nNão foi possível criar o arquivo \"%s\".\n", nome_arquivo);
        return;
    }

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            fprintf(arquivo, "0 ");
        }
        fprintf(arquivo, "\n");
    }

    printf("\n\nO arquivo \"%s\" foi criado com sucesso.\n", nome_arquivo);
    fclose(arquivo);
    return;
}

void ler_arquivo(char nome_arquivo[], int tab[TAM][TAM])
{
    FILE *arquivo = fopen(nome_arquivo, "r");

    if (arquivo == NULL) {
        printf("\n\nNão foi possível abrir o arquivo \"%s\" para leitura.\n", nome_arquivo);
        criar_arquivo(nome_arquivo);
        return;
    }

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (fscanf(arquivo, "%d", &tab[i][j]) != 1) {
                printf("\n\nNão foi possível ler do arquivo \"%s\".\n", nome_arquivo);
                fclose(arquivo);
                return;
            }
        }
    }

    printf("\n\nO arquivo \"%s\" foi lido com sucesso.\n", nome_arquivo);
    fclose(arquivo);
    return;
}

void gravar_arquivo(char nome_arquivo[], int tab[TAM][TAM])
{
    FILE *arquivo = fopen(nome_arquivo, "w");

    if (arquivo == NULL) {
        printf("\nNão foi possível abrir o arquivo \"%s\" para gravação.\n", nome_arquivo);
        return;
    }

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            fprintf(arquivo, "%d ", tab[i][j]);
        }
        fprintf(arquivo, "\n");
    }

    printf("\nO arquivo \"%s\" foi gravado com sucesso.\n", nome_arquivo);
    fclose(arquivo);
    return;
}

void imprimir_valor(int valor)
{
    if (valor == 0) {
        printf("  ");
    } else {
        printf("%d ", valor);
    }
}

void imprimir_tabuleiro(int tab[TAM][TAM])
{
    printf("\n\n     1 2 3   4 5 6   7 8 9  ");
    printf("\n   +-------+-------+-------+\n");
    for (int i = 0; i < TAM; i++) {
        printf(" %d | ", i + 1);
        for (int j = 0; j < TAM; j++) {
            imprimir_valor(tab[i][j]);
            if (j % 3 == 2) {
                printf("| ");
            }
        }
        printf("\n");
        if (i % 3 == 2) {
            printf("   +-------+-------+-------+\n");
        }
    }
    printf("\n");
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

int ler_escolha(int tab[TAM][TAM])
{
    while (true) {
        char tecla;

        printf("\n\nDigite uma das teclas abaixo:\n");
        printf("\n[1 - 9] ~ Iniciar uma jogada;");
        printf("\n    [g] ~ Gravar o estado atual do jogo;");
        printf("\n    [l] ~ Ler um jogo salvo anteriormente;");
        printf("\n    [s] ~ Sair do jogo.\n\n");
        scanf(" %c", &tecla);

        if (((tecla - '0') >= 1) && ((tecla - '0') <= 9)) {
            return (tecla - '0') - 1;
        } else if (tecla == 'g') {
            char nome_arquivo[] = "default";
            ler_nome_arquivo(nome_arquivo);
            gravar_arquivo(nome_arquivo, tab);
            imprimir_tabuleiro(tab);
        } else if (tecla == 'l') {
            char nome_arquivo[] = "default";
            ler_nome_arquivo(nome_arquivo);
            ler_arquivo(nome_arquivo, tab);
            imprimir_tabuleiro(tab);
        } else if (tecla == 's') {
            if (confirmar_saida()) {
                return -1;
            }
            imprimir_tabuleiro(tab);
        } else {
            printf("\n\nTecla inválida. Tente novamente...\n\n");
            imprimir_tabuleiro(tab);
            continue;
        }
    }
}

int pedir_linha(void)
{
    while (true) {
        int lin;

        printf("\n\nDigite uma linha [1 - 9]: ");
        scanf("%d", &lin);

        if (lin < 1 || lin > 9) {
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

        printf("\n\nDigite uma coluna [1 - 9]: ");
        scanf("%d", &col);

        if (col < 1 || col > 9) {
            printf("\n\nColuna inválida. Tente novamente...\n");
            continue;
        }

        return col - 1;
    }
}

int pedir_valor(void)
{
    while (true) {
        int val;

        printf("\n\nDigite um valor [1 - 9]: ");
        scanf("%d", &val);

        if (val < 1 || val > 9) {
            printf("\n\nValor inválido. Tente novamente...\n");
            continue;
        }

        return val;
    }
}

bool testar_linha(int lin, int tab[TAM][TAM])
{
    for (int col1 = 0; col1 < (TAM - 1); col1++) {
        for (int col2 = col1 + 1; col2 < TAM; col2++) {
            if (tab[lin][col1] == 0 || tab[lin][col2] == 0) {
                continue;
            }
            if (tab[lin][col1] == tab[lin][col2]) {
                return false;
            }
        }
    }

    return true;
}

bool testar_coluna(int col, int tab[TAM][TAM])
{
    for (int lin1 = 0; lin1 < (TAM - 1); lin1++) {
        for (int lin2 = lin1 + 1; lin2 < TAM; lin2++) {
            if (tab[lin1][col] == 0 || tab[lin2][col] == 0) {
                continue;
            }
            if (tab[lin1][col] == tab[lin2][col]) {
                return false;
            }
        }
    }

    return true;
}

bool testar_sub_regiao(int sub_regiao, int tab[TAM][TAM])
{
    int lin_ini = (sub_regiao / 3) * 3;
    int lin_fim = lin_ini + 3;
    int col_ini = (sub_regiao % 3) * 3;
    int col_fim = col_ini + 3;
    int tab_temp[TAM][TAM];
    int k = 0;

    for (int i = lin_ini; i < lin_fim; i++) {
        for (int j = col_ini; j < col_fim; j++) {
            tab_temp[0][k++] = tab[i][j];
        }
    }

  return testar_linha(0, tab_temp);
}

bool tabuleiro_completo(int tab[TAM][TAM])
{
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tab[i][j] == 0) {
                return false;
            }
        }
    }

    for (int i = 0; i < TAM; i++) {
        if (!testar_linha(i, tab) || !testar_coluna(i, tab) || !testar_sub_regiao(i, tab)) {
            printf("\n\nO tabuleiro está completo, mas incorreto.\n");
            return false;
        }
    }

    printf("\n\nParabéns! Você conseguiu completar corretamente o tabuleiro.\n\n");
    return true;
}

bool validar_jogada(int lin, int col, int val, int tab[TAM][TAM])
{
    if (tab[lin][col] != 0) {
        printf("\n\nA posição informada [%d][%d] já está preenchida.\n", lin + 1, col + 1);
        printf("\n\nTente novamente...\n");
        return false;
    } else {
        tab[lin][col] = val;
    }
    
    for (int i = 0; i < TAM; i++) {
        if (!testar_linha(i, tab) || !testar_coluna(i, tab) || !testar_sub_regiao(i, tab)) {
            printf("\n\nA jogada gera uma situação inválida no tabuleiro.\n");
            tab[lin][col] = 0;
            return false;
        }
    }

    return true;
}

void jogar(char nome_arquivo[], int tab[TAM][TAM])
{
    while (true) {
        imprimir_tabuleiro(tab);

        if (tabuleiro_completo(tab)) {
            return;
        }

        int lin = ler_escolha(tab);
        
        if (lin == -1) {
            exit(1);
        }

        int col = pedir_coluna();
        int val = pedir_valor();

        while (!validar_jogada(lin, col, val, tab)) {
            imprimir_tabuleiro(tab);
            lin = pedir_linha();
            col = pedir_coluna();
            val = pedir_valor();
        }

        gravar_arquivo(nome_arquivo, tab);
    }
}

void inicio(char nome_arquivo[])
{
    while (true) {
        char escolha;

        printf("\n\nVocê deseja ler o tabuleiro de um arquivo? [s/n]\n");
        scanf(" %c", &escolha);

        if (escolha == 's' || escolha == 'S') {
            ler_nome_arquivo(nome_arquivo);
            return;
        } else if (escolha == 'n' || escolha == 'N') {
            printf("\n\nNeste caso, ele será lido de um arquivo \"default\".\n");
            return;
        } else {
            printf("\n\nEscolha inválida. Tente novamente...\n");
            continue;
        }
    }
}

int main(void)
{
    do {
        int tab[TAM][TAM] = {{0}};
        char nome_arquivo[] = "default";

        inicio(nome_arquivo);
        ler_arquivo(nome_arquivo, tab);
        jogar(nome_arquivo, tab);
    } while (jogar_novamente());

    return 0;
}