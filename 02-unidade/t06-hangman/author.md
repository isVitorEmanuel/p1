# Introduction

The project consists in the elaboration of a "hangman" game, totally playable in a Linux Terminal. There
is 3 difficulties possible: easy, medium and hard. And players can compete to be on the top of the scoreboard
for every one of them. There is currently the support for 9 different categories, with words being presented
in Portuguese.

# Author(s)

Igor Marques de Lima - igor.marques.121@ufrn.edu.br
Vitor Emanuel Rodrigues de Alencar - vitor.alencar.713@ufrn.edu.br

# Problems found or limitations

<!-- TODO -->

It was a very challenging project. Some of desired functionalities are not available in the current version.
For example, the scoreboard file is not a binary file for real, so anyone can edit it. Despite that, the core
of the game is present and you can have a lot of fun, some of the words can be very challenging to guess.
Try it yourself!

# Grading

Preencha os itens que você implementou, indicando qual a nota esperada para cada item.

| Item                                                                                      | Valor máximo | Valor esperado |
| ----------------------------------------------------------------------------------------- | :----------: |:--------------:|
| Lê nome do jogador                                                                        |      5       |       5        |
| Exibe e gerencia menu de opções                                                           |      10      |       10       |
| Exibe e gerencia escolha de categoria das palavras                                        |      10      |       10       |
| Exibe regras do jogo quando solicitado                                                    |      5       |       5        |
| Exibe tabela de pontuação                                                                 |      5       |       5        |
| Contabiliza e acumula os pontos de várias partidas                                        |      10      |       10       |
| Escolhe uma palavra aletória (sem repetir) a partir das lista de palavras lida do arquivo |      10      |       10       |
| Controla o número de erros para um jogador perder uma partida                             |      5       |       5        |
| Exibe partes do boneco na forca conforme os erros se acumulam                             |      5       |       4        |
| Exibe os erros/acertos da palavra secreta em uma partida                                  |      10      |       10       |
| Exibe palavra secreta completa, quando uma partida é perdida                              |      5       |       5        |
| Exibe a lista de chutes errados                                                           |      5       |       5        |
| Permite o cancelamento de uma partida em andamento                                        |      5       |       5        |
| Apresenta as telas no formato organizacional sugerido                                     |      5       |       5        |
| Projeto contém pelo menos 2 classes                                                       |      5       |       5        |
| Programa gerencia erros corretamente                                                      |      5       |       5        |
| Lê palavras e categorias do arquivo de palavras `words.csv`                               |      10      |       10       |
| Lê informações do pontuação `score.hgm`                                                   |      10      |       5        |
| Funcionamento geral correto do program                                                    |      10      |       8        |

# Compiling and Runnig

Open a Terminal in the "source" folder:

$ cmake -S . -B build
$ cmake --build build

Go to the newly generated build folder, open
./hangman
Have fun!