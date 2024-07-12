# Project Battleship Puzzle Generator

**Subject: Programação I (DIM0176)**

**Students**

* Igor Marques de Lima
* Vitor Emanuel Rodrigues de Alencar

## 1. About Project
The project consists of creating a Battleship Puzzle Generator (BPG), where we should generate a set of distinct puzzles and write them to an output file.

Users must provide the quantity of puzzles via command-line arguments and can also provide the dimensions (rows and columns), the default is 10 for both. After that, the generator creates the puzzles with the specified dimensions and a fixed number of ships. Output files are stored in the "data" folder.
## 2. Compile and Run  

### 2.1 Using Cmake
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
./build/bpg
` 
### 2.2 Using g++
To compile the project using g++, from the root folder, execute:

`
mkdir -p build
`
to generate the build folder.
To compile the project, do:

`
g++ src/bpg.cpp src/bpg.h src/common.h src/graal.h src/main.cpp src/validated.cpp src/validated.h -o build/bpg
`

The compilation generates an executable named bpg inside the build/ directory.
Immediately after compilation, to execute the program, use the commands:

`
./build/bpg
`
### 2.3 Command-line Arguments
When running the command `./bpg`, it is necessary to pass command-line arguments to the script. They are:

* `[number of puzzles]`
* `[options]` (Optional)

The `[number of puzzles]` argument does not have an identifier and is mandatory, with values between 1 and 100, inclusively.

The `[options]` arguments are optional and has identifiers:
* `[--r/--rows]`: Specifies the number of rows in the puzzle.
* `[--c/--cols]`: Specifies the number of columns in the puzzle.

If not specified, the default value for each argument is 10. If specified, their values must be between 7 and 16, inclusively.

The arguments can be passed in any order, but attention must be paid to the syntax, values, and the mandatory argument. Invalid arguments can lead to program execution errors.

**Examples of valid arguments:**

`./bpg 5
`

`
./bpg 3 --r 15 --c 12
`

`
./bpg --r 15 3 --c 12
`

`
./bpg --r 15 3
`

**Examples of invalid arguments:**

`./bpg 
`

`
./bpg 0
`

`
./bpg --r 15 --c 12
`

`
./bpg --r 18 3
`

`
./bpg 3 --r --c 13 10 
`

## 3. Errors and Limitations

No issues have been found while testing the current version of the program. It can successfully generate up to 100 distinct valid puzzles in the two output file formats (armada and matrix) as specified.

## 4. Difficulties

The biggest difficulty found was how to make code readable and scalable. Some functions in the project  were too big and in some moments changes and debugging demanded more time than expected. Some methods in the puzzle class would probably need to be refactored to become more generic if the project grew in size. It was also hard to avoid "overnesting" i.e. multiple conditionals inside loops.