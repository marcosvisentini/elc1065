# t5 - Drop The Number

## Descrição

Faça um programa na linguagem de programação C para jogar uma aproximação do jogo “Drop The Number”.

Trata-se de um jogo com um tabuleiro de 5 colunas de 6 números cada. Inicialmente, o tabuleiro está vazio. A cada jogada, um número é lançado, e o jogador deve escolher em qual coluna ele irá cair. O número então cai sobre os demais números que porventura já estejam nessa coluna, ocupando o lugar livre mais baixo que houver na coluna. O número que cai tem até 3 casas vizinhas, que podem estar ocupadas por números (uma abaixo, uma à esquerda e uma à direita da casa que ele ocupa). Os vizinhos que tiverem o mesmo valor do número que caiu combinam-se com o novo número, esvaziando suas casas e transformando o número em um número maior, como explicado adiante. Caso existam casas ocupadas sobre as casas que foram esvaziadas, os números nessas casas devem “cair”, de forma que nunca exista uma casa ocupada com uma casa vazia embaixo. Deve ser novamente verificada a existência de vizinhos com mesmo número após a queda, e e esse processo se repete, até que não existam mais vizinhos com o mesmo número, o que encerra uma jogada.

Um número que se combina com um vizinho dobra o seu valor (multiplica por 2¹). Se se combina com mais dois vizinhos, quadruplica seu valor (multiplica por 2²). Se se combina com três vizinhos, multiplica seu valor por 2³, etc. Toda vez que um número se combina, o jogador ganha pontos, no valor do resultado da combinação.

O resultado da combinação fica sempre na coluna mais próxima à coluna escolhida pelo jogador, que contenha números combinados.

Os números lançados são valores aleatórios, sempre potências de 2. O menor valor possível de ser lançado é 2 e o maior valor possível é inicialmente 8, ajustado à metade do maior que já apareceu no tabuleiro, conforme o jogo evolui.

A cada jogada, o jogo deve mostrar o estado do tabuleiro, o número de pontos, o valor que está sendo lançado e o valor que será lançado na jogada seguinte. O jogador deve então escolher a coluna (entre 1 e 5). O jogo deve mostrar então cada posição do tabuleiro que produz uma combinação, destacando as casas envolvidas na combinação – pode ter que mostrar vários estados do tabuleiro em uma jogada (ou nenhum).

No final do jogo, o programa deve mostrar a pontuação final, as maiores pontuações históricas (limitadas a 10) e a classificação da pontuação atual no histórico do jogo. O programa deve então pedir o apelido do jogador e acrescentar ao histórico. Para isso, o programa deve manter um arquivo com todas as pontuações já obtidas (com os apelidos correspondentes), ordenassem ordem decrescente de pontos. O formato do arquivo deve ser uma primeira linha que diz quantos valores o arquivo contém, seguido de uma linha para cada valor, constituída pelo número de pontos seguido pelo apelido do jogador, separados por um espaço. Esse arquivo deve ser lido em um vetor de estruturas dinamicamente alocado, o novo valor deve ser colocado na posição correta dentro desse vetor, e a nova versão do arquivo novamente gravada, ao final de cada partida.

A cada jogada, deve ser permitido ao jogador encerrar o programa, caso em que o estado da partida deve ser salvo em um arquivo. Deve ser também possível abandonar a partida. Ao final do programa, deve ser oferecida a opção de jogar novamente. Ao iniciar o programa, ele deve perguntar ao jogador se deseja continuar a partida interrompida.
