[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/_VVDx-rS)
﻿# Lista de Exercício sobre Ranges e Funções Templates

Essa lista de exercícios tem por objetivo o desenvolvimento de uma biblioteca de funções **template** que operam sobre **ranges**, i.e. um par de ponteiros que definem um intervalo aberto-fechado sobre uma coleção. A programação com template ou _gabarito_ em C++ permite que você programe uma função sem especificar o tipo de dados sobre o qual a função vai trabalhar. Dessa forma é possível, por exemplo, criar uma _única_ função de ordenação que ordenda qualquer coleção de informações, como inteiros, strings, frutas e monstros.

Mais detalhes sobre cada função a ser implementada pode ser encontrada de maneira unificada no documento em PDF que se encontra [aqui](docs/lista_template.pdf).

# Resolvendo as Questões

Para resolver as questões segue as seguintes instruções:

1. Edite o arquivo `include/graal.h` para incluir seu código no corpo da função correspondente a cada questão da lista.
2. Quando finalizar ou se quiser tirar uma dúvida faça o _commit_ das alterações para o GitHub.

Ao final desse processo, todas as modificações preisam ser "_comitadas_" para o GitHub. O repo remoto no GitHub é o que será considerado como submissão do seu trabalho, além do envio do SIGAA.

Não esqueça de editar também o arquivo [`autor.md`](author.md) e incluir o seu nome e quais questões você conseguiu resolver.

Segue abaixo a árvore de diretórios do projeto, para facilitar a visualização dos arquivos.

```
.
├── author.md    <---------- VOCÊ DEVE INCLUIR SEU NOME NESSE ARQUIVO.
├── CMakeLists.txt
├── docs
│   └── lista_template.pdf
├── include
│   └── graal.h  <--------- ESTE É O ARQUIVO PARA INCLUIR SEU CÓDIGO.
├── README.md
└── tests
    ├── CMakeLists.txt
    ├── include
    │   └── tm
    │       ├── test_manager.cpp
    │       └── test_manager.h
    └── main.cpp  <--------- ESSE É O ARQUIVO COM OS TESTES, APENAS PARA CONSULTA.

5 directories, 9 files
```

# Compilando o Projeto

## Usando `cmake`

Nesta lista, todos os exercícios serão implementados na forma de uma função template.
Existem um arquivo `tests/main.cpp` onde os **testes unitários** para cada função foram implementados. Você pode olhar esse arquivo para entender como os testes foram projetados, mas você não deve alterá-lo.

A compilação e execução das questões pode ser feita usando `cmake`. A partir da pasta raiz do projeto faça:

```
cmake -S . -B build
```

para gerar os arquivos `Makefiles` do projeto na pasta `build` que será criada. Em seguinda compile com:

```
cmake --build build --target run_tests
```

Esse comando ativa a compilação e, em seguida, executa os testes.

Alternativamente, se você desejar apenas compilar e não rodar os testes, utilize:

```
cmake --build build
```

A compilação gera um executável com o nome `all_tests` dentro da pasta `build/tests`.

Logo após a compilação, para executar o programa com os testes use os comandos:

```
./build/tests/all_tests
```

Caso você deseje repetir o processo de compilação, digamos, após uma alteração, basta executar o comando `make` dentro da pasta `build`.

## Usando Compilação Manual com `g++`

É possível compilar o programa "na mão" (i.e. sem o `cmake`) usando o `g++`. Para isso use o comando abaixo a partir do diretório raiz do projeto.

```
mkdir -p build
```

para criar a pasta `build` onde o executável será gerado, e

```
g++ -Wall -std=c++17 -pedantic tests/include/tm/test_manager.cpp tests/main.cpp -I include -I tests/include/tm -o build/all_tests
```

para compilar e gerar o executável em `build`.

O executável será gerado na pasta `build`, bastando executá-lo depois, como explicado acima.

# Avaliação do Trabalho

Não esqueça de incluir comentários no formato **Doxygen** para cada uma das funções, bem como comentários regulares informativos dentro do corpo da função.

A ausência de comentário será penalizada com a retirada de 1 ponto da sua nota (que vai de zero a dez).

Esse trabalho tem um total de **110 points**. Abaixo temos uma tabela com a descrição dos pontos atribuídos a cada questão. Pontos parciais poderão ser considerados em questões incorretas.

| Item      | Value (points) |
| --------- | :------------: |
| MinMax    |     10 pts     |
| Reverse   |     10 pts     |
| Copy      |     10 pts     |
| Find If   |     10 pts     |
| All Of    |     10 pts     |
| None Of   |     10 pts     |
| Any Of    |     10 pts     |
| Equal     |     10 pts     |
| Unique    |     15 pts     |
| Partition |     15 pts     |

As seguintes situações podem retirar pontos da sua nota final:

| Item                                                 | Value (points) |
| ---------------------------------------------------- | :------------: |
| Erros de compilação e/ou execução                    |       -5       |
| Falta de comentários no estilo Doxygen               |      -10       |
| Vazamento de Memória                                 |      -10       |
| Enviar o [`author.md`](author.md) sem ser preenchido |       -5       |

O arquivo [`author.md`](author.md) deve conter também uma breve descrição dos possíveis erros, limitações, problemas encontrados ou dificuldades com o exercício. Não esqueça de incluir o nome do autor do trabalho!

# Autoria e Política de Colaboração

O trabalho é individual. Qualquer equipe pode ser convocada para uma entrevista. O objetivo da entrevista é duplo: confirmar a autoria do trabalho e responder dúvidas que possam existir sobre a implementação. Durante a entrevista o autor deve ser capazes de explicar, com desenvoltura, qualquer trecho do trabalho. Portanto, é possível que, após a entrevista, ocorra redução da nota geral do trabalho, caso as repostas oferecidas na entrevistas não sejam convincentes.

O trabalho em cooperação entre alunos da turma é estimulado. É aceitável a discussão de ideias e estratégias. Note, contudo, que esta interação **não** deve ser entendida como permissão para utilização de código ou parte de código de outras equipes, o que pode caracterizar a situação de plágio. Em resumo, tenha o cuidado de escrever seus próprios programas.

Trabalhos plagiados receberão nota **zero** automaticamente, independente de quem seja o verdadeiro autor dos trabalhos infratores. Fazer uso de qualquer assistência sem reconhecer os créditos apropriados é considerado **plagiarismo**. Quando submeter seu trabalho, forneça a citação e reconhecimentos necessários. Isso pode ser feito pontualmente nos comentários no início do código, ou, de maneira mais abrangente, no arquivo texto `author.md`. Além disso, no caso de receber assistência, certifique-se de que ela lhe
é dada de maneira genérica, ou seja, de forma que não envolva alguém tendo que escrever código por você.

# Entrega

Você pode submeter seu trabalho de duas formas: como repositório no GitHub Classroom (GHC), ou via SIGAA enviando todo o código fonte como um arquivo compactado. Se você decidir enviar apenas via GHC ainda assim é necessário enviar pelo SIGAA um arquivo texto com seu nome e o link para o repositório no GitHub.

Em qualquer uma das duas situações descritas, lembre-se de remover a pasta que contém o executável (normalmente a pasta `build`).

---

&copy; DIMAp/UFRN 2020-2024.
