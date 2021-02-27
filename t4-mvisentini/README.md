# t4 - Get10

## Descrição

Faça um programa na linguagem de programação C para jogar o jogo “Get10”.

Trata-se de um jogo com um tabuleiro de 5x5 números pequenos. O tabuleiro está sempre cheio de números que são escolhidos ao acaso pelo programa. Posições vizinhas (na horizontal ou na vertical) contendo o mesmo valor formam grupos. Em cada jogada, o jogador deve escolher uma posição do tabuleiro que pertença a um desses grupos (não pode ser uma posição que não tenha pelo menos um vizinho com o mesmo valor). O valor na posição escolhida pelo jogador é trocado por um valor imediatamente superior ao que ali estava, e todos as demais posições do grupo têm seus valores apagados. Os valores que estão acima dos valores apagados “caem”, ocupando esses lugares. Todos os lugares livres ficarão nas linhas superiores. O programa preenche esses lugares com novos valores aleatórios.

O objetivo do jogo é fazer o maior número de pontos, e ter os maiores valores possíveis nas posições (pelo menos uma versão do programa termina quando o primeiro grupo de noves é transformado no valor 10, daí o nome o jogo). O jogo termina quando não tem mais jogadas possíveis.

No início do jogo, o tabuleiro é preenchido com números de 1 a 3. Ao final de cada jogada, o jogo coloca novos valores aleatórios nas posições que foram esvaziadas, e são sempre menores que o maior valor existente no tabuleiro.

O número de pontos de uma jogada é o tamanho do grupo multiplicado pelo novo valor (um a mais que o valor que compunha o grupo). Se o novo valor aumentar o maior valor no tabuleiro, a jogada vale o dobro.

O programa deve apresentar o número de pontos junto com o tabuleiro a cada jogada.

O programa deve manter a máxima pontuação histórica em um arquivo. No final do jogo, o programa deve apresentar a pontuação final do jogo e a máxima histórica. Caso o jogador tenha feito mais pontos que o máximo, deve ser parabenizado e o máximo atualizado no arquivo.

O programa não pode ter mais do que uma variável global.
