# Introduction

The 'jogo da vida' project consists of developing a system that simulates Conway's Game of Life, a well-known cellular automaton (CA). The simulation is displayed via the command terminal or by generating images for each generation of the simulation.

# Author(s)

**Students**

* Igor Marques de Lima (igor.marques.121@ufrn.edu.br)
* Vitor Emanuel Rodrigues de Alencar (vitor.alencar.713@ufrn.edu.br)

# Difficulties

No difficulties were encountered during the execution of the project.

# Problems found or limitations

No problems or limitations were found during the development and testing of the project.

# Grading

Fill in the items you implemented, indicating the expected grade for each item.

| Item                                                                           | Maximum Points | Expected Points |
| ------------------------------------------------------------------------------ | :------------: | :-------------: |
| Correctly handles command line arguments OR collects via INI file              |       10       |       10        |
| Reads configuration from an ASCII file and initializes an object               |       5        |        5        |
| Correctly displays a configuration to standard output                          |       10       |       10        |
| Correctly displays a configuration in the saved image                          |       10       |       10        |
| Correctly applies the evolution rules described                                |       10       |       10        |
| Correctly executes the configuration evolution                                 |       10       |       10        |
| Correctly detects simulation stability                                         |       15       |       15        |
| Correctly detects simulation extinction                                        |       5        |        5        |
| Correctly generates image files for each generation                            |       10       |       10        |
| Program presents at least one class                                            |       5        |        5        |
| Correctly handles user input errors                                            |       10       |       10        |

# Compiling and Running

### Using CMake
To compile the project using CMake, from the root folder, execute:
`
cmake -S . -B build
`

to generate the project's Makefiles in the newly created build folder.
To compile the project, run:

`
cmake --build build
`

The compilation generates an executable named `glife` inside the `build/` directory.
To execute the program, use the command with the desired options:

`
./build/glife <path_to_configuration_file>
`

(The default configuration file path is `config/glife.ini`.)

Note: In the configuration file, provide a valid path both for the file containing the simulation 
data and for the path where the images will be saved.
