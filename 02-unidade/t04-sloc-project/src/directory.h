#include <string>
#include <vector>

#include "common.h"

#ifndef DIRECTORY_H
#define DIRECTORY_H

//== Headers to functions

/*!
* Converts an entire string to lowercase.
* @param str String to be convert.
* @return String converted to lowercase.
*/
std::string toLowerCase(const std::string& str);

/*!
* Get the extension of a file.
* @param file Name of file to get extension.
* @return String with a extension of file.
*/
std::string get_extension(const std::string &filename);

/*!
* Check if entry is a directory or file
* @param input Entry name.
* @return Returns enum typeEntry with the type of entry.
*/
typeEntry entry(std::string input);

/*!
* Receives user input (directory or file) and returns all the files that will be processed.
* @param inputName File or directory name.
* @return Returns a vector with the list of files to be processed.
*/
std::vector<std::string> list_of_src_files(std::string inputName);

/*!
* Gets the size of the longest filename to be processed
* @param database Vector containing all the data of the files.
* @return Return the number of logest filename
*/
int longestFilename(std::vector<FileInfo> database);

/*!
* Converts the number of lines and their percentage into a 
* string and concatenates them.
* @param value Number of lines
* @param database Percent of lines
* @return Returns the number of lines and percentage concatenated into a string.
*/
std::string concatPercent(int value, double percent);

/*!
* Function that compares file data and informs their order 
* based on the output option provided by the user.
* @param a First file to be compared.
* @param b Second file to be compared.
* @param optionComplete Option chosen by the user.
* @return Returns a boolean indicating whether the first 
* file is greater than or less than the second one.
*/
bool compareFileInfo(const FileInfo& a, const FileInfo& b, const std::string& optionComplete);

/*!
* Creates a string with the table of data for each file.
* @param oss Object osstringstream with the string of the table
* @param database Vector with all file data.
* @param option Option chosen by the user.
* @return Returns a boolean indicating whether the first 
* file is greater than or less than the second one.
*/
void tableString(std::ostringstream& oss, std::vector<FileInfo> database, const std::string& option);

/*!
* Displays all the data in a table.
* @param database Vector with all file data.
* @param run Options chosen by the user.
*/
void show_info(std::vector<FileInfo> database, RunningOpt run);

#endif