# Introduction

The 'sloc' project consists of developing a terminal application that counts how many lines of code, comments, and blank lines are found in one or more C/C++ source files provided as input, and prints out this information to the standard output.

The purpose is to develop a program that, when given a file or directory as input, examines each file, counts, and categorizes its lines into comments, blank lines, and code. After this analysis, the program should present a summary containing the total number of lines of code, comments, and blank lines, as well as calculate the percentage that each of these categories represents in relation to the total number of lines in the file.

The supported file extensions for analysis are:

* `".cpp"`: a C/C++ program.
* `".c"`: a C program.
* `".h"`: a C/C++ header file.
* `".hpp"`: a C++ header file.
* `".java"`: a Java program.

 
# Author(s)

**Students**

* Igor Marques de Lima (igor.marques.121@ufrn.edu.br)
* Vitor Emanuel Rodrigues de Alencar (vitor.alencar.713@ufrn.edu.br)

# Problems found or limitations

There is a limitation in our program while counting code lines, there is a pattern uncovered that is a single-line comment right after a multi-line comment being closed, the second comment is treated as a piece of code, leading to a error in counting lines of code. No other issues have been found while testing.

# Grading

Preencha os itens que você implementou, indicando qual a nota esperada para cada item.

| Item                                                | Valor máximo | Valor esperado |
| --------------------------------------------------- | :----------: |:--------------:|
| Read a single source file                           |      10      |       10       |
| Read a list of files from a directory               |      15      |       15       |
| Show help as requested `-h`                         |      4       |       4        |
| Treat error situations                              |      8       |       8        |
| Show correct number of blank lines                  |      5       |       5        |
| Show correct number of comment lines                |      10      |       10       |
| Show correct number of code lines                   |      10      |       8        |
| Show correct number of total lines                  |      5       |       5        |
| Show the type of source file                        |      5       |       5        |
| Show percentages as requested                       |      10      |       10       |
| Show consolidation at the bottom of a table         |      5       |       5        |
| Table is formatted as requested                     |      8       |       8        |
| The project contains at least one struct or classes |      5       |       5        |

# Compiling and Runnig


### Using Cmake
To compile the project using Cmake, from the root folder, execute:

`
cmake -S . -B build
`

to generate the project's Makefiles in the newly created build folder.
To compile the project, do:

`
cmake --build build
`

The compilation generates an executable named bpg inside the build/ directory.
To execute the program, use the command with the desired options:

`
./build/sloc
` 
### Using g++
To compile the project using g++, from the root folder, execute:

`
mkdir -p build
`
to generate the build folder.
To compile the project, do:

`
g++ src/common.h src/directory.cpp src/directory.h src/listing_file_content.cpp src/listing_file_content.h src/main.cpp src/validated.cpp src/validated.h -o build/sloc
`

The compilation generates an executable named bpg inside the build/ directory.
Immediately after compilation, to execute the program, use the commands:

`
./build/sloc
`