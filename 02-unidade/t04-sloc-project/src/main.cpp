/*!
 * @file main.cpp
 * @description
 * This program implements a single line of code count for C/C++ programs.
 * @author	Add your name here
 * @date	September, 9th 2024.
 * @remark On 2022-09-9 changed ...
 */
#include <cstdlib>
#include <fstream>
#include <map>
#include <iostream>

#include "listing_file_content.h"
#include "validated.h"
#include "common.h"
#include "directory.h"

using std::map;
using std::string;


//== Main entry

int main(int argc, char *argv[]) {

  RunningOpt runop = validated_input(argc, argv);
  auto src_files = list_of_src_files(runop.input_name);
  auto database = list_content(src_files);

  show_info(database, runop);

  return EXIT_SUCCESS;
}
