#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void mensagem_inicial(void)
{
    printf("\n\nO programa sorteou um número entre 1 e 100.");
    printf("\nSerá que você é capaz de adivinhar que número é esse?\n");
}

int gerar_numero(void)
{
    return ((rand() % 100) + 1);
}

int pedir_numero(void)
{
    while (true) {
        int numero;

        printf("\n\nTente adivinhar o número sorteado [1, 100]: ");
        scanf("%d", &numero);

        if (numero < 1 || numero > 100) {
            printf("\nO número informado foge do intervalo [1, 100].\nTente novamente...\n");
            continue;
        }

        return numero;
    }    
}

bool analisar_numero(int numero_sorteado, int numero_usuario)
{
    if (numero_usuario == numero_sorteado) {
        return true;
    } else if (numero_usuario > numero_sorteado) {
        printf("\nO número que você informou é MAIOR que o número sorteado.\n");
        return false;
    } else {
        printf("\nO número que você informou é MENOR que o número sorteado.\n");
        return false;
    }
}

bool jogar_novamente(int numero_sorteado, int n_tentativas)
{
    printf("\n\nVocê conseguiu adivinhar o");
    printf("\nnúmero [%d] após %d tentativa(s)!\n\n", numero_sorteado, n_tentativas);

    while (true) {
        char escolha;

        printf("\nVocê deseja jogar novamente? [s/n]\n");
        scanf(" %c", &escolha);

        if (escolha == 's' || escolha == 'S') {
            return true;
        } else if (escolha == 'n' || escolha == 'N') {
            return false;
        } else {
            printf("\nOpção inválida. Tente novamente...\n");
            continue;
        }
    }
}

int main(void)
{
    srand(time(NULL));

    int n_tentativas, numero_sorteado;

    do {
        mensagem_inicial();
        bool eh_igual;
        numero_sorteado = gerar_numero();
        n_tentativas = 0;

        do {
            int numero_usuario = pedir_numero();
            eh_igual = analisar_numero(numero_sorteado, numero_usuario);

            n_tentativas++;
        } while (!eh_igual);
    } while (jogar_novamente(numero_sorteado, n_tentativas));
    return 0;
}