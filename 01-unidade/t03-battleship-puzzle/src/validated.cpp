
#include <iostream>
#include <string>
#include <vector>

#include "common.h"
#include "graal.h"
#include "validated.h"

/*!
 * This function prints the helper display to the user.
 *
 */
void helpDisplay () {
        std::cout << "Usage: [<options>] <number_of_puzzles>" << std::endl;
        std::cout << "  Program options are:" << std::endl;
        std::cout << "    --rows <num>\tSpecify the number of rows for the matrix," << std::endl;
        std::cout << "                \twith `<num>` in the range [7, 16 ]." << std::endl;
        std::cout << "                \tThe default value is 10." << std::endl;
        std::cout << "    --cols <num>\tSpecify the number of columns for the matrix," << std::endl;
        std::cout << "                 \twith `<num>` in the range [7,16]." << std::endl;
        std::cout << "                 \tThe default value is 10." << std::endl;
        std::cout << "  Requested input is:" << std::endl;
        std::cout << "   number_of_puzzles \tThe number of puzzles to be generated," << std::endl;
        std::cout << "                     \tin the range [1,100]." << std::endl;
        exit(EXIT_FAILURE);
}

/*!
 * Check if the command-line inputs are valid for use.
 *
 * @param index The memory address of the index i of the argv array.
 * @param argv The memory address of array argv.
 * @param optInit Address of struct that will be modified.
 *
 */
void validatedArgs(const int &index, const std::vector<std::string> & argv, RunningOpt &optInit) {

    std::string object;

    /// Check if the parameter 'lines/columns' is the last one in the array. If it is, return an error to the user.
    if(index + 1 >= argv.size()) {
        std::cout << "bpg ERROR: ``expected argument not received in:``\n+  "<< argv[index] <<"\n\n";
        helpDisplay();
    
    }

    argv[index] == "--r" or argv[index] == "--rows"? object = "rows" : object = "columns";

    /// Check if the values of the 'lines/columns' argument from the CLI are valid integers.
    if(!graal::all_of(std::begin(argv[index + 1]), std::end(argv[index + 1]), isdigit)) {
        std::cout << "bpg ERROR: ``invalid arguments received``. Expected an integer, but received an unexpected argument:\n+  "
        << argv[index] << "\nPlease provide a valid integer.\n\n";
        helpDisplay();
    } else {

        /// Convert the string argument to an integer.
        if (object == "columns"){
          optInit.cols = std::stoi(argv[index + 1]);
        } else {
          optInit.rows = std::stoi(argv[index + 1]);
        }

        /// Check if the number of lines/columns is between 7 and 16.
        if (optInit.cols < 7 or optInit.cols > 16) {
            std::cout << "bpg ERROR: ``invalid number of "<< object <<"``\n\n";
            helpDisplay();
        }
        if (optInit.rows < 7 or optInit.rows > 16) {
          std::cout << "bpg ERROR: ``invalid number of "<< object <<"``\n\n";
          helpDisplay();
        }
    }
}

/*!
 * Check if the command-line inputs are valid for use.
 *
 * @param argc Number of inputs received.
 * @param argv Array with all command-line inputs as characters.
 *
 * @return Returns a struct containing the usable data.
 *
 */
RunningOpt validated_input(int argc, char *argv[]) {

    /// Declare the variable to be used.
    RunningOpt runOptions;
    runOptions.n_puzzles = 0;

    /// Check the quantity of elements received.
    if(argc >= 7 or argc == 1) {
        std::cout << "bpg ERROR: ``invalid numbers of arguments``. Check the quantity of arguments passed and try again.\n\n";
        helpDisplay();
    }

    /// Create an array and convert the inputs to strings.
    std::vector<std::string> args;
    for (int i = 0; i < argc; ++i) {
        args.push_back(argv[i]);
    }

    /// Iterate over the vector.
    for(int index = 1; index < argc; index++) {

        /// Search for the parameter for lines.
        if(args[index] == "--rows" or args[index] == "--r") {

          validatedArgs(index, args, runOptions);

        /// Search for the parameter for columns.
        } else if (args[index] == "--cols" or args[index] == "--c"){

          validatedArgs(index, args, runOptions);
        
        } else {

            /// Search for the argument of the puzzle quantity.
            if ((args[index - 1] != "--rows" and args[index - 1] != "--r") and 
                (args[index - 1] != "--cols" and args[index - 1] != "--c")
                ) {
                
                /// Check if the values of the 'number of puzzles' argument from the CLI are valid integers.
                if(!graal::all_of(std::begin(args[index]), std::end(args[index]), isdigit)) {
                    std::cout << "bpg ERROR: ``invalid parameter provided``. Expected an integer or arguments [--rows] [--cols].\n"
                    << "Please check the parameter and try again.\n\n";
                    helpDisplay(); 
                } else {
                    
                    /// Check if number puzzles already informed.
                    if(runOptions.n_puzzles > 0) {
                        std::cout << "bpg ERROR: ``number of puzzles already informed!``\n\n";
                        helpDisplay();
                    }

                    /// Convert the string argument to an integer.
                    runOptions.n_puzzles = std::stoi(args[index]);  

                    // Check if number of puzzles is between 1 and 100
                    if (runOptions.n_puzzles < 1 or runOptions.n_puzzles > 100) {
                        std::cout << "bpg ERROR: ``invalid number of puzzles!``\n\n";
                        helpDisplay();
                    }     
                }
            }
        }
    }

    /// Check if the user provided the parameter 'number of puzzles'.
    if(runOptions.n_puzzles == 0) {
        std::cout << "bpg ERROR: ``Parameter not received``. Expected an integer for number of puzzles.\n"
        << "Please check the parameter and try again.\n\n";
        helpDisplay();
    }
    return runOptions;
}

