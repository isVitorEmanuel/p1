#include <string>
#include <vector>
#include "common.h"

#ifndef VALIDATED_H
#define VALIDATED_H

//== Headers to functions

/*!
 * This function prints the helper display to the user.
 *
 */
void helpDisplay ();

/*!
 * Check if the command-line inputs are valid for use.
 *
 * @param argc Number of inputs received.
 * @param argv Array with all command-line inputs as characters.
 * @return Returns a struct containing the usable data.
 *
 */
RunningOpt validated_input(int argc, char *argv[]);

#endif