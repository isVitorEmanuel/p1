#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "validated.h"
#include "common.h"

/*!
 * This function prints the helper display to the user.
 *
 */
void helpDisplay () {
        std::cout << "Welcome to slocpp, version 1.0, (c) 2024 Selan, DIMAp, UFRN."<< std::endl;
        std::cout << "Usage: sloc [options] file/directory" << std::endl;
        std::cout << "Options:" << std::endl;
        std::cout << "  -h/--help       Display this information." << std::endl;
        std::cout << "  -r              Look for files recursively in the directory provided." << std::endl;
        std::cout << "  -s f/t/c/b/s/a  Sort table in ascending order by (f)ilename, (t) filetype," << std::endl;
        std::cout << "                  (c)omments, (b)lank lines, (s)loc, or (a)ll. Default is to show" << std::endl;
        std::cout << "                  files in ordem of appearance." << std::endl;
        std::cout << "  -S f/t/c/b/s/a  Same as above, but in descending order." << std::endl;
        exit(EXIT_SUCCESS);
}

/*!
 * Check if the command-line inputs are valid for use.
 *
 * @param argc Number of inputs received.
 * @param argv Array with all command-line inputs as characters.
 * @return Returns a struct containing the usable data.
 *
 */
RunningOpt validated_input(int argc, char *argv[]) {

  /// Declare the variable to be used.
  RunningOpt runOptions;

  /// Check the quantity of elements received.
  if(argc > 4) {
      std::cout << "sloc ERROR: ``invalid numbers of arguments``. Check the quantity of arguments passed and try again.\n";
      exit(EXIT_FAILURE);
  }

  if(argc == 1) {
      helpDisplay();
  }

  /// Create an array and convert the inputs to strings.
  std::vector<std::string> args;
  for (int i = 0; i < argc; ++i) {
    args.push_back(argv[i]);
  }

  /// Iterate over the vector.
  for(int index = 1; index < argc; index++) {

    /// Searching for the help flag.
    if(args[index] == "-h" or args[index] == "--help") {

      helpDisplay();      

    /// Searching for the recursive analysis flag.
    } else if(args[index] == "-r") {

      runOptions.input_name = "src";

      /// Searching for the -s options flag.
    } else if(args[index] == "-s" or args[index] == "-S") {

      std::vector<std::string> values{"f", "t", "c", "b", "s", "a"}; //!< Vector with all options

      std::string searchElement = args[index + 1]; //!< String with a option 
      bool validValue = false;

      // Use std::find to search element in vector
      for(std::string option : values) {
        if(option == searchElement) {
          validValue = true;
          break;
        }
      }

      /// Checks if the option chosen by the user is valid.
      if (validValue) {
        runOptions.option = args[index] + searchElement;
      } else {
        std::cout << "sloc ERROR: ``invalid value with argument -s``. Check the parameter and arguments passed and try again.\n";
        exit(EXIT_FAILURE);
      }
    } else {

      /// Searching for the input value of the directory or file.
      if ((args[index - 1] != "-S" and args[index - 1] != "-s")) {
        if(runOptions.input_name == "") {
          runOptions.input_name = args[index];
        } 
      }
    }
  }

  /// Check if the entry exists.
  if(runOptions.input_name == "") {
    std::cout << "sloc ERROR: ``No files or directories to process``. Check the parameter and arguments passed and try again." << std::endl;
    exit(EXIT_FAILURE);
  }

  return runOptions;
}
