#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define LIN 6
#define COL 5

typedef struct {
    char nickname[32];
    int score;
} score;

bool encerrar_programa(void)
{
    while (true) {
        char sair;

        printf("\n\nVocê realmente deseja encerrar o programa? [s/n]\n");
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

bool abandonar_partida(void)
{
    while (true) {
        char sair;

        printf("\n\nVocê realmente deseja abandonar a partida? [s/n]\n");
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

void limpar_stream(void)
{
    char c;

    while (((c = getchar()) != '\n') && (c != EOF)) {
        continue;
    }
}

void esperar_enter(void)
{
    printf("\n[DIGITE ENTER PARA CONTINUAR]\n");

    while (true) {
        char c = getchar();
        if (c == '\n') {
            break;
        }
    }
}

int descobrir_expoente(int num)
{
    if (num == 2) {
        return 1;
    }

    return descobrir_expoente(num / 2) + 1;
}

int gerar_numero(int maior_num)
{
    int expoente_do_maior_num = log2(maior_num);
    int expoente = (rand() % (expoente_do_maior_num - 1)) + 1;

    return pow(2, expoente);
}

int quantidade_digitos(int maior_num)
{   
    int num = maior_num;
    int cont = 0;

    while (num != 0) {
        num /= 10;
        cont++;
    }

    return cont;
}

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

void ler_dado(FILE *arquivo, score *dado)
{
    fscanf(arquivo, "%d %s", &dado->score, dado->nickname);
}

score *ler_arquivo(int *n_dados, char nome_arquivo[])
{
    FILE *arquivo = fopen(nome_arquivo, "r");

    if (arquivo == NULL) {
        printf("\n\nNão foi possível abrir o arquivo \"%s\" para leitura.\n", nome_arquivo);
        criar_arquivo(nome_arquivo);
        return malloc(sizeof(score));
    }

    int n_dados_temp;
    if (fscanf(arquivo, "%d", &n_dados_temp) != 1) {
        printf("\n\nNão foi possível ler do arquivo \"%s\".\n", nome_arquivo);
        fclose(arquivo);
        return 0;
    }
    
    score *dados = malloc(n_dados_temp * sizeof(score));
    
    if (dados == NULL) {
        printf("\n\nNão foi possível alocar memória.\n");
        exit(1);
    }

    int i;
    for (i = 0; i < n_dados_temp; i++) {
        ler_dado(arquivo, &dados[i]);
    }

    fclose(arquivo);
    printf("\n\nO arquivo \"%s\" foi lido com sucesso.\n", nome_arquivo);
    *n_dados = i;
    
    return dados;
}

void gravar_arquivo(char nome_arquivo[], int n_dados, score dados[n_dados])
{
    FILE *arquivo = fopen(nome_arquivo, "w");

    if (arquivo == NULL) {
        printf("\nNão foi possível abrir o arquivo \"%s\" para gravação.\n", nome_arquivo);
        return;
    }

    fprintf(arquivo, "%d\n", n_dados);

    for (int i = 0; i < n_dados; i++) {
        fprintf(arquivo, "%d %s\n", dados[i].score, dados[i].nickname);
    }

    printf("\n\nO arquivo \"%s\" foi gravado com sucesso.\n", nome_arquivo);
    fclose(arquivo);
    return;
}

int ler_partida(int *maior_num, int *num_atual, int *prox_num, int tab[LIN][COL])
{
    FILE *arquivo = fopen("partida", "r");

    if (arquivo == NULL) {
        printf("\n\nNão foi possível abrir o arquivo \"partida\" para leitura.\n");
        exit(1);
    }

    fscanf(arquivo, "%d", maior_num);
    fscanf(arquivo, "%d", num_atual);
    fscanf(arquivo, "%d", prox_num);

    int pontuacao;
    fscanf(arquivo, "%d", &pontuacao);
    
    for (int i = 0; i < LIN; i++) {
        for (int j = 0; j < COL; j++) {
            if (fscanf(arquivo, "%d", &tab[i][j]) != 1) {
                printf("\n\nNão foi possível ler do arquivo \"partida\".\n");
                fclose(arquivo);
                return 0;
            }
        }
    }
    
    fclose(arquivo);
    printf("\n\nO arquivo \"partida\" foi lido com sucesso.\n");
    return pontuacao;
}

void gravar_partida(int pontuacao, int maior_num, int num_atual, int prox_num, int tab[LIN][COL])
{
    FILE *arquivo = fopen("partida", "w");

    if (arquivo == NULL) {
        printf("\nNão foi possível abrir o arquivo \"partida\" para gravação.\n");
        return;
    }

    fprintf(arquivo, "%d\n", maior_num);
    fprintf(arquivo, "%d\n", num_atual);
    fprintf(arquivo, "%d\n", prox_num);
    fprintf(arquivo, "%d\n", pontuacao);

    for (int i = 0; i < LIN; i++) {
        for (int j = 0; j < COL; j++) {
            fprintf(arquivo, "%d ", tab[i][j]);
        }
        fprintf(arquivo, "\n");
    }
    
    fclose(arquivo);
    printf("\n\nO arquivo \"partida\" foi gravado com sucesso.\n");
    return;
}

void inserir_dado(int pontuacao, int n_dados, char nome_arquivo[], char nickname[], score dados[n_dados])
{ 
    score *dados_temp = realloc(dados, n_dados * sizeof(score));

    if (dados_temp == NULL) {
        printf("\n\nNão foi possível realocar memória.\n");
        exit(1);
    }

    dados = dados_temp;
    
    printf("\n\nNickname: ");
    scanf(" %s", nickname);
    
    strcpy(dados[n_dados - 1].nickname, nickname);
    dados[n_dados - 1].score = pontuacao;

    for (int i = (n_dados - 1); i > 0; i--) {
        if (dados[i].score > dados[i - 1].score) {
            score temp = dados[i];
            dados[i] = dados[i - 1];
            dados[i - 1] = temp;
        }
    }

    gravar_arquivo(nome_arquivo, n_dados, dados);
    return;
}

int definir_cor_fundo(int num)
{
    if (num > 0) {
        return 202;
    } else {
        return 19;
    }
}

void mudar_cor(int cor_fundo)
{
    printf("|%c[38;5;255;48;5;%dm", 27, cor_fundo);
}

void resetar_cor(void)
{
    printf("%c[0m", 27);
}

void imprimir_dash(int maior_num)
{
    int n_digitos = quantidade_digitos(maior_num);

    for (int i = 0; i < COL; i++) {
        printf("+");
        for (int j = 0; j < n_digitos; j++) {
            printf("-");
        }
    }
    printf("+\n\n");
}

void imprimir_espacos(int n_digitos)
{
    for (int i = 0; i < n_digitos; i++) {
        printf(" ");
    }
}

void imprimir_pipe(void)
{
    int cor_pipe = rand() % 255;

    printf("%c[38;5;%dm|%c[0m", 27, cor_pipe, 27);
}

void imprimir_numero(int num, int maior_num)
{
    int n_digitos = quantidade_digitos(maior_num);
    int cor_fundo = definir_cor_fundo(num);

    if (num == 0) {
        imprimir_pipe();
        imprimir_espacos(n_digitos);
        return;
    }

    if (num < 0) {
        num = -num;
    }
    
    mudar_cor(cor_fundo);
    printf("%*d", n_digitos, num);
    resetar_cor();
}

void imprimir_tabuleiro(int maior_num, int tab[LIN][COL])
{
    printf("\n\n");
    for (int i = 0; i < LIN; i++) {
        for (int j = 0; j < COL; j++) {
            imprimir_numero(tab[i][j], maior_num);
        }
        imprimir_pipe();
        printf("\n");
    }
    imprimir_dash(maior_num);
}

void imprimir_informacoes(int num_atual, int prox_num, int pontuacao)
{
    printf("\n\nPontuação: %d", pontuacao);
    printf("\nNúmero que está sendo lançado: %d", num_atual);
    printf("\nNúmero a ser lançado: %d\n\n", prox_num);
}

int pedir_coluna(int num)
{
    while (true) {
        int col;

        printf("\n\nEm qual coluna você quer que o número %d caia? [1 - 5]\n", num);
        scanf("%d", &col);

        if (col == 0) {
            return col - 1;
        }

        if (col == 6) {
            return col;
        }

        if (col < 1 || col > 5) {
            printf("\n\nColuna inválida. Tente novamente...\n");
            continue;
        } else {
            return col - 1;
        }
    }
}

int fazer_numero_cair(int col, int num, int tab[LIN][COL])
{
    for (int i = LIN - 1; i >= 0; i--) {
        if (tab[i][col] == 0) {
            tab[i][col] = num;
            return i;
        }
    }

    return -1;
}

bool tem_vizinho(int lin, int col, int tab[LIN][COL])
{
    if (lin < (LIN - 1) && tab[lin + 1][col] == tab[lin][col]) {
        return true;
    }

    if (col < (COL - 1) && tab[lin][col + 1] == tab[lin][col]) {
        return true;
    }

    return false;    
}

bool tem_jogada(int tab[LIN][COL])
{
    for (int i = 0; i < LIN; i++) {
        for (int j = 0; j < COL; j++) {
            if (tab[i][j] == 0) {
                return true;
            }
        }
    }

    printf("\n\nNão há mais jogadas possíveis no tabuleiro...\n");
    return false;
}

void subir_zeros(int tab[LIN][COL])
{
    for (int col = 0; col < COL; col++) {
        for (int lin = (LIN - 1); lin > 0; lin--) {
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

bool tem_regiao_para_trocar(int *lin, int *col, int tab[LIN][COL])
{
    for (int i = 0; i < LIN; i++) {
        for (int j = 0; j < COL; j++) {
            if (tab[i][j] == 0) {
                continue;
            }
            if (tem_vizinho(i, j, tab)) {
                *lin = i;
                *col = j;
                return true;
            }
        }
    }

    return false;
}

int trocar_regiao_por_x(int lin, int col, int num, int x, int tab[LIN][COL])
{
    if (lin > (LIN - 1) || col < 0 || col > (COL - 1) || tab[lin][col] != num) {
        return 0;
    }

    tab[lin][col] = x;
    int n_trocados = 1;

    n_trocados += trocar_regiao_por_x(lin + 1, col, num, x, tab);
    n_trocados += trocar_regiao_por_x(lin, col - 1, num, x, tab);
    n_trocados += trocar_regiao_por_x(lin, col + 1, num, x, tab);
    
    return n_trocados;
}

int jogar(int col, int *maior_num, int tab[LIN][COL])
{
    int lin_temp, col_temp;
    int pontuacao = 0;
    limpar_stream();

    while (tem_regiao_para_trocar(&lin_temp, &col_temp, tab)) {
        imprimir_tabuleiro(*maior_num, tab);
        esperar_enter();

        int num = tab[lin_temp][col_temp];
        int n_trocados = trocar_regiao_por_x(lin_temp, col_temp, num, 0, tab) - 1;
        int novo_num = num * pow(2, n_trocados);

        tab[lin_temp][col] = novo_num;
        pontuacao += novo_num;

        if (novo_num > *maior_num) {
            *maior_num = novo_num;
        }

        subir_zeros(tab);
    }

    return pontuacao;
}

void copiar_tabuleiro(int tab_temp[LIN][COL], int tab[LIN][COL])
{
    for (int i = 0; i < LIN; i++) {
        for (int j = 0; j < COL; j++) {
            tab_temp[i][j] = tab[i][j]; 
        }   
    }
}

void jogadas_possiveis(int num, int maior_num, int tab[LIN][COL])
{
    for (int i = 0; i < COL; i++) {
        int col_temp;
        int tab_temp[LIN][COL];
        copiar_tabuleiro(tab_temp, tab);

        int lin_temp = fazer_numero_cair(i, num, tab_temp);
        tab[lin_temp][i] = 0;

        if (tem_regiao_para_trocar(&lin_temp, &col_temp, tab_temp)) {
            trocar_regiao_por_x(lin_temp, col_temp, num, -num, tab_temp);

            printf("\nCombinações que se formam na coluna %d...\n", i + 1);
            imprimir_tabuleiro(maior_num, tab_temp);
            esperar_enter();
        }
    }
}

void mensagem_sair(void)
{
    printf("\n\nPara encerrar o programa, digite [0]");
    printf("\nPara abandonar esta partida, digite [6]\n");
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

bool continuar_partida_interrompida(void)
{
    while (true) {
        char escolha;

        printf("\n\nVocê deseja continuar a partida interrompida? [s/n]\n");
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

int achar_posicao_no_ranking(int n_dados, char nickname[], score dados[n_dados])
{
    for (int i = 0; i < n_dados; i++) {
        if (strcmp(dados[i].nickname, nickname) == 0) {
            return i + 1;
        }
    }
    
    return -1;
}

int inicio(int *maior_num, int *num_atual, int *prox_num, int tab[LIN][COL])
{
    FILE *arquivo = fopen("partida", "r");

    if (arquivo == NULL) {
        return 0;
    }

    if (continuar_partida_interrompida()) {
        fclose(arquivo);
        return ler_partida(maior_num, num_atual, prox_num, tab);
    }

    fclose(arquivo);
    return 0;
}

void final(int pontuacao, int n_dados, char nickname[], score dados[n_dados])
{
    printf("\n\nPontuação final: %d\n", pontuacao);
    printf("\nMaiores pontuações históricas:\n\n");

    int max = n_dados;
    
    if (max > 10) {
        max = 10;
    }

    for (int i = 0; i < max; i++) {
        printf("%2d. %-20s %5d\n", i + 1, dados[i].nickname, dados[i].score);
    }

    int classificacao = achar_posicao_no_ranking(n_dados, nickname, dados);
    
    if (classificacao == -1) {
        printf("\n\nNão foi possível determinar a classificação da pontuação atual.\n");
    } else {
        printf("\n\nVocê ficou na posição %d do ranking.\n", classificacao);
    }
}

int partida(int maior_num, int tab[LIN][COL])
{
    int num_atual = gerar_numero(maior_num);
    int prox_num = 0;
    int lin, col;

    int pontuacao = inicio(&maior_num, &num_atual, &prox_num, tab);

    if (prox_num == 0) {
        prox_num = gerar_numero(maior_num);
    }

    while (tem_jogada(tab)) {
        mensagem_sair();
        imprimir_tabuleiro(maior_num, tab);
        imprimir_informacoes(num_atual, prox_num, pontuacao);
        jogadas_possiveis(num_atual, maior_num, tab);
        
        while (true) {
            col = pedir_coluna(num_atual);

            if (col == -1) {
                if (encerrar_programa()) {
                    gravar_partida(pontuacao, maior_num, num_atual, prox_num, tab);
                    exit(1);
                }
                continue;
            }

            if (col == 6) {
                if (abandonar_partida()) {
                    gravar_partida(pontuacao, maior_num, num_atual, prox_num, tab);
                    return pontuacao;
                }
                continue;
            }

            lin = fazer_numero_cair(col, num_atual, tab);

            if (lin == -1) {
                printf("\n\nA coluna %d já está cheia. Tente novamente...", col + 1);
                continue;
            }

            break;
        }

        pontuacao += jogar(col, &maior_num, tab);
        gravar_partida(pontuacao, maior_num, num_atual, prox_num, tab);
        num_atual = prox_num;
        prox_num = gerar_numero(maior_num);
    }

    return pontuacao;
}

int main(void)
{
    srand(time(NULL));

    do {
        int tab[LIN][COL] = {{0}};
        int maior_num = 16;
        int n_dados = 0;
        char nickname[32];
        char nome_arquivo[] = "pontuacoes";
        
        int pontuacao = partida(maior_num, tab);
        
        score *dados = ler_arquivo(&n_dados, nome_arquivo);
        n_dados++;
        
        inserir_dado(pontuacao, n_dados, nome_arquivo, nickname, dados);
        final(pontuacao, n_dados, nickname, dados);
        free(dados);
    } while (jogar_novamente());

    return 0;
}