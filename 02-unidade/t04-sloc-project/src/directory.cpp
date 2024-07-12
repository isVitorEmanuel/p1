#include <array>
#include <cctype>
#include <cstdlib>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <filesystem>
#include <map>
#include <algorithm> 
#include <iomanip>   

#include "common.h"

/*!
* Check if entry is a directory or file
* @param input Entry name.
* @return Returns enum typeEntry with the type of entry.
*/
typeEntry entry(std::string input) {
    
  typeEntry entry; 
  std::string path = input; //!< String with path of directory/file
  
  /// Verify if path exist
  if (std::filesystem::exists(path)) {

    /// If exist, verify the type
    if (std::filesystem::is_regular_file(path)) {
      entry = FIL;
    } else if (std::filesystem::is_directory(path)) {
      entry = DIRE;
    } 

  /// If the path does not exist, display an error message and terminate the program.
  } else {
    std::cout << "  Sorry, unable to read \"" << input << "\"." << std::endl;
    exit(EXIT_FAILURE);
  }
  return entry;
}

/*!
* Converts an entire string to lowercase.
* @param str String to be convert.
* @return String converted to lowercase.
*/
std::string toLowerCase(const std::string& str) {
  std::string result = str;
  for (char &c : result) {
    c = std::tolower(c);
  }
  return result;
}

/*!
* Get the extension of a file.
* @param file Name of file to get extension.
* @return String with a extension of file.
*/
std::string get_extension(const std::string &filename) {

    // Find the position of the last dot in the file name
    size_t lastDotPos = filename.find_last_of('.');
    
    // If no dot is found, the file has no extension
    if (lastDotPos == std::string::npos) {
      return "";
    }
    
    // Extract the extension from the file name
    return filename.substr(lastDotPos);
}

/*!
 * Checks if the file name provided as an argument
 * corresponds to one of the accepted filec types
 * by the sloc.
 * @param filename Name of file
 * @return Returns a boolean, true if the file type is supported, false 
 * if the file type is not supported.
 */
bool is_source_code(const std::string &filename) {

  std::array<std::string, 5> extensions{ ".cpp", ".c", ".h", ".hpp", ".java" }; //!< Vector with all supported extension

  std::string lowerFileName = toLowerCase(filename);
  std::string extension = get_extension(lowerFileName);

  /// Check if extension file is a supported extension
  for (const auto &e : extensions) {
    if (extension == e) {
        return true;
    }
  }
    return false;
}

/*!
* Receives user input (directory or file) and returns all the files that will be processed.
* @param inputName File or directory name.
* @return Returns a vector with the list of files to be processed.
*/
std::vector<std::string> list_of_src_files(std::string inputName) {

  typeEntry fileDirec = entry(inputName); //!< Variable with the name of the input.

  /// List of files to process.
  std::vector<std::string> src_list;

  /// Check if type input is file.
  if(fileDirec == FIL) {

    /// Check if extension file is supported.
    if(is_source_code(inputName)) {

      /// Add file in list of file to process
      src_list.push_back(inputName); 
    } else {
      
      /// Displays an error message and terminates the program.
      std::cout << "  Sorry, \"" << toLowerCase(get_extension(inputName)) << "\" files are not supported at this time." << std::endl;
      exit(EXIT_FAILURE);
    }

  /// Check if type input is directory
  } else {

    /// Iterates recursively through the files within the directory.
    for (const auto& entry : std::filesystem::recursive_directory_iterator(inputName)) {

      /// Check if entry is a file and is a supported file
      if (std::filesystem::is_regular_file(entry) && is_source_code(entry.path().filename().string())) {

        /// Add file in list of file to process
        src_list.push_back(entry.path().string());
      }

      /// Checks if there are files to be processed.
      if(src_list.size() == 0) {
        std::cout << "  Sorry, unable to find any supported source file inside directory \"" << inputName << "\"." << std::endl;
        exit(EXIT_FAILURE);
      }
    }
  }
  return src_list;
}

/*!
* Gets the size of the longest filename to be processed
* @param database Vector containing all the data of the files.
* @return Return the number of longest filename
*/
int longestFilename(std::vector<FileInfo> database) {

  int longest_filename = 0;
  for (auto const &file : database){
    if (file.filename.length() > longest_filename){
      longest_filename = file.filename.length();
    }
  }

  return longest_filename + 4;
}

/*!
* Converts the number of lines and their percentage into a 
* string and concatenates them.
* @param value Number of lines
* @param database Percent of lines
* @return Returns the number of lines and percentage concatenated into a string.
*/
std::string concatPercent(int value, double percent) {
  std::ostringstream oss;

  oss << value << " (" << std::setprecision(1) << std::fixed << percent << "%)";

  return oss.str();
}

/*!
* Function that compares file data and informs their order 
* based on the output option provided by the user.
* @param a First file to be compared.
* @param b Second file to be compared.
* @param optionComplete Option chosen by the user.
* @return Returns a boolean indicating whether the first 
* file is greater than or less than the second one.
*/
bool compareFileInfo(const FileInfo& a, const FileInfo& b, const std::string& optionComplete) {
  
  char order = optionComplete[1]; //!< Informs the order of data printing (ascending/descending).
  char option = optionComplete[2]; //!< Informs which parameter will be ordered.

  /// Checks the print order.
  switch(order) {
    case 's':

      /// Check the parameter will be ordered
      switch(option) {

        /// Return the greater file based on the parameter
        case 'f': return a.filename < b.filename;
        case 't': return a.type < b.type;
        case 'c': return a.n_comments < b.n_comments;
        case 'b': return a.n_blank < b.n_blank;
        case 's': return a.n_loc < b.n_loc;
        case 'a': return a.n_lines < b.n_lines;
      }

      break;
    
    case 'S':

      /// Check the parameter will be ordered
      switch(option) {

        /// Return the greater file based on the parameter
        case 'f': return a.filename > b.filename;
        case 't': return a.type > b.type;
        case 'c': return a.n_comments > b.n_comments;
        case 'b': return a.n_blank > b.n_blank;
        case 's': return a.n_loc > b.n_loc;
        case 'a': return a.n_lines > b.n_lines;
      }

      break;

    /// If there is a reading error in the order, display an error message.
    default:
      std::cout << "Sorry, unable to sort the files according to the desired option." << std::endl;
      exit(EXIT_FAILURE);
  }

  return false;
}

/*!
* Creates a string with the table of data for each file.
* @param oss Object osstringstream with the string of the table
* @param database Vector with all file data.
* @param option Option chosen by the user.
* @return Returns a boolean indicating whether the first 
* file is greater than or less than the second one.
*/
void tableString(std::ostringstream& oss, std::vector<FileInfo> database, const std::string& option) {

  int total_comments = 0, total_blank = 0, total_loc = 0, total_lines = 0; //!< Variables with a total number lines.

  /// Sorts the vector of files according to the option chosen by the user.
  std::sort(database.begin(), database.end(), [option](const FileInfo& a, const FileInfo& b) {
    return compareFileInfo(a, b, option);
  });

  /// Mapping of file type from integer to string.
  std::map<int, std::string> typesMap = {
    {C, "C"},
    {CPP, "C++"},
    {H, "C/C++ header"},
    {HPP, "C++ header"},
    {JAVA, "Java"},
    {UNDEF, "Undefined"},
  };

  int longest_filename = longestFilename(database); //!< Variables with longest file name

  /// Iterates through the vector with file data.
  for (const auto& filedata : database) {

    auto it = typesMap.find(filedata.type); //!< Iterator for the file type.

    /// Calculates the percentages of each type of line.
    double percent_comments = (static_cast<double>(filedata.n_comments) / filedata.n_lines) * 100;
    double percent_blank = (static_cast<double>(filedata.n_blank) / filedata.n_lines) * 100;
    double percent_loc = (static_cast<double>(filedata.n_loc) / filedata.n_lines) * 100;

    if (filedata.n_lines == 0){
      percent_comments = 0.0;
      percent_blank = 0.0;
      percent_loc = 0.0;
    }
    
    /// Adds the file data line to the table through the ostringstream object.
    oss << std::setw(longest_filename) << filedata.filename
        << std::setw(16) << it->second
        << std::setw(16) << concatPercent(filedata.n_comments, percent_comments)
        << std::setw(16) << concatPercent(filedata.n_blank, percent_blank)
        << std::setw(16) << concatPercent(filedata.n_loc, percent_loc)
        << std::setw(5) << filedata.n_lines
        << std::endl;

    /// Adds the number of lines from the processed file to the total.
    total_comments += filedata.n_comments;
    total_blank += filedata.n_blank;
    total_loc += filedata.n_loc;
    total_lines += filedata.n_lines;
  }

  /// Calculates the total percentage of lines.
  double total_percent_comments = (static_cast<double>(total_comments) / total_lines) * 100;
  double total_percent_blank = (static_cast<double>(total_blank) / total_lines) * 100;
  double total_percent_loc = (static_cast<double>(total_loc) / total_lines) * 100;

  /// Avoid NaN on table when dividing by zero.
  if (total_lines == 0){
    total_percent_comments = 0.0;
    total_percent_blank = 0.0;
    total_percent_loc = 0.0;
  }

  /// Adds the total percentages to the table."
  oss << std::string(4 * 16 + 5 + longest_filename, '-') << std::endl;
  oss << std::setw(longest_filename) << "SUM"
      << std::setw(16) << ""
      << std::setw(16) << concatPercent(total_comments, total_percent_comments)
      << std::setw(16) << concatPercent(total_blank, total_percent_blank)
      << std::setw(16) << concatPercent(total_loc, total_percent_loc)
      << std::setw(5) << total_lines << std::endl;
  oss << std::string(4 * 16 + 5 + longest_filename, '-') << std::endl;
}

/*!
* Displays all the data in a table.
* @param database Vector with all file data.
* @param run Options chosen by the user.
*/
void show_info(std::vector<FileInfo> database, RunningOpt run) {

  int longest_filename = longestFilename(database); //!< Variables with longest file name

  std::ostringstream oss; // Ostringstream object with the string of the table to be printed.

  /// Display the number of processed files
  std::cout << "Files processed: " << database.size() << std::endl;

  if(database.size() == 0) {
    std::cout << "Sorry, it was not possible to process the file data." << std::endl;
    exit(EXIT_FAILURE);
  }
  
  /// Display a header of table
  oss << std::string(4 * 16 + 5 + longest_filename, '-') << std::endl;
  oss << std::left << std::setw(longest_filename) << "Filename"
      << std::setw(16) << "Language"
      << std::setw(16) << "Comments"
      << std::setw(16) << "Blank"
      << std::setw(16) << "Code"
      << std::setw(5) << "All" << std::endl;
  oss << std::string(4 * 16 + 5 + longest_filename, '-') << std::endl;

  /// Call the tableStream function to create the body of the table.
  tableString(oss, database, run.option);

  /// Display table
  std::cout << oss.str();
}
