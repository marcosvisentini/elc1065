#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void mensagem_inicial(void)
{
    printf("\n\nEscolha um número entre 1 e 100. O programa");
    printf("\ntentará adivinhar qual número você escolheu!\n");
}

int gerar_numero(int min, int max)
{
    return ((rand() % (max - min + 1)) + min);
}

bool analisar_informacao(int min, int max, int numero_aleatorio, char resposta_usuario)
{
    return (((resposta_usuario == '<') && ((numero_aleatorio - 1) < min)) ||
            ((resposta_usuario == '>') && ((numero_aleatorio + 1) > max)));
}

bool pedir_informacao(int *min, int *max, int numero_aleatorio)
{
    while (true) {
        char resposta_usuario;

        printf("\n\nO número que você escolheu é IGUAL [=], MAIOR [>] ou MENOR [<] que %d?\n", numero_aleatorio);
        scanf(" %c", &resposta_usuario);

        bool esta_mentindo = analisar_informacao(*min, *max, numero_aleatorio, resposta_usuario);

        if (esta_mentindo) {
            printf("\n\nSua resposta não coincide com as anteriores.\n");
            continue;
        }

        if (resposta_usuario == '=') {
            return true;
        } else if (resposta_usuario == '>') {
            *min = numero_aleatorio + 1;
            return false;
        } else {
            *max = numero_aleatorio - 1;
            return false;
        }
    }
}

bool jogar_novamente(int numero_usuario)
{
    printf("\n\nO programa conseguiu adivinhar");
    printf("\no número [%d] que você escolheu!\n", numero_usuario);

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

    int numero_aleatorio;

    do {
        mensagem_inicial();
        int min = 1;
        int max = 100;
        bool adivinhou;
        
        do {
            numero_aleatorio = gerar_numero(min, max);
            adivinhou = pedir_informacao(&min, &max, numero_aleatorio);
        } while (!adivinhou);
    } while (jogar_novamente(numero_aleatorio));
    return 0;
}