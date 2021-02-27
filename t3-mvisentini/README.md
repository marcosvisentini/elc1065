# t3 - Sudoku

## Descrição

Faça um programa na linguagem de programação C. Seu programa deve apresentar um tabuleiro de sudoku, e permitir que o usuário jogue nesse tabuleiro. O tabuleiro inicial deve ser lido de um arquivo, que contém 81 números entre 0 e 9, que são os valores de cada posição do tabuleiro. O valor 0 é usado para representar uma casa vazia. Caso o arquivo não exista, deve inicializar com um tabuleiro default (que pode ser vazio).

O programa deve ter um laço principal que consiste em:

* apresenta o tabuleiro – caso o tabuleiro esteja completo e correto (fim do jogo), esse fato deve ser informado;
* lê uma tecla do usuário. Essa tecla pode ser:
  * um dígito entre 1 e 9 – representa o início de uma jogada, descrita abaixo;
  * a letra ‘g’ – grava o estado atual do jogo; o programa pede o nome de um arquivo e grava o tabuleiro nesse arquivo;
  * a letra ‘l’ – ler um jogo salvo anteriormente; o programa pede o nome do arquivo e substitui o tabuleiro pelo conteúdo desse arquivo (caso consiga ler o arquivo);
  * a letra ‘s’ – o usuário pede para sair do jogo; o programa pede confirmação.
* volta à apresentação do tabuleiro.
  
Uma jogada consiste em o usuário digitar 3 números: a linha, a coluna e o valor a colocar nessa posição. O programa deve avisar o usuário (e não aceitar a jogada), se algum desses valores for inválido (não tiver entre 1 e 9), se a posição escolhida não estiver vazia, ou se essa jogada levar a uma situação inválida do tabuleiro (pelas regras do sudoku).

Após cada jogada válida, o tabuleiro deve ser gravado no arquivo que foi lido no início do programa. Dessa forma, sempre que o programa começa, o usuário volta à mesma situação em que estava na última vez que jogou.
