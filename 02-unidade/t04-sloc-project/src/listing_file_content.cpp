#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>

#include "common.h"
#include "directory.h"

/*!
* This function adds the file type to the file object.
* @param fileInfo Object that will hold the file data.
*/
void setFileType(FileInfo& fileInfo) {

  std::string lowerFileName = toLowerCase(fileInfo.filename); //!< File name in lowercase.
  std::string fileExtension = get_extension(lowerFileName); //!< Extension of file

  /// Mapping of the extensions.
  std::map<std::string, lang_type_e> typesMap = {
    {".c", C},
    {".cpp", CPP},
    {".h", H},
    {".hpp", HPP},
    {".java", JAVA},
  };
  
  /// Maps the file extension to the supported extensions.
  auto it = typesMap.find(fileExtension);

  if (it != typesMap.end()) {
    fileInfo.type = it->second;
  } else {
    fileInfo.type = UNDEF;
  }
}

inline std::string remove_quote_content (const std::string& s){
  bool inside_quotes = false;
  std::string treated_line;
  // Loop iteration over all characters of line
  for (int i = 0; i < s.length(); ++i){
    char current_char = s[i];
    bool previous_is_escape = i > 0 and s[i-1] == '\\';

    // Switcher for inside_quotes
    if (current_char == '"' and !previous_is_escape)
      inside_quotes = !inside_quotes;
    else if (!inside_quotes)
      treated_line+= current_char;
  }
  return treated_line;
}

/*!
 * Analyzes the amount of comment, code and blank lines in a given file,
 * updating file info attributes.
 * @param file_lines String collection of all lines in the file.
 * @param fileInfo Object that holds the file data.
 */
void code_analyzer(const std::vector<std::string>& file_lines, FileInfo &fileInfo){
  bool in_multiline_comment = false;

  for (auto& line : file_lines){
    // Trimmed version of current line
    std::string trimmed_line = trim(line);

    // Checks if it is a blank line outside of comment block
    if (!in_multiline_comment and trimmed_line.empty()){
      fileInfo.n_blank++;
      continue;
    }

    // treat the line so comments inside quotes are ignored
    std::string treated_line = remove_quote_content(trimmed_line);

    bool has_double_slashes = treated_line.find("//") != std::string::npos;
    bool has_open_ml_comment = treated_line.find("/*") != std::string::npos;
    bool has_closing_ml_comment = treated_line.find("*/") != std::string::npos;
    bool starts_with_double_slashes = has_double_slashes and treated_line.find("//") == 0;

    // single-line comment with no code
    if (starts_with_double_slashes and !in_multiline_comment){
      fileInfo.n_comments++;
      continue;
    }

    // Checks if current line is part of a multi-line comment block
    if (in_multiline_comment){
      fileInfo.n_comments++;
      if (has_closing_ml_comment){ // checks if multi-line comment is being closed
        in_multiline_comment = false;
        // If */ is not at the end of the trimmed line, so there is also code after it

        if (treated_line.find("*/") != treated_line.length() - 2)
          fileInfo.n_loc++;
      }
    } else { // not inside a multi-line comment block
      // opens and closes multiline-comment block at the same line
      if (has_open_ml_comment and has_closing_ml_comment){
        fileInfo.n_comments++;
        in_multiline_comment = false;
        // If /* not at the start or */ at the end, increases code count
        if (treated_line.find("*/") != treated_line.length() - 2
            or treated_line.find("/*") != 0)
          fileInfo.n_loc++;
      } else if (has_open_ml_comment) { // if just opening a multi-line comment block
        in_multiline_comment = true;
        fileInfo.n_comments++;
        // if /* is not at the beginning of line, there is code before
        if (treated_line.find_first_of("/*") != 0){
          fileInfo.n_loc++;
        }
      } else if (has_double_slashes){
        fileInfo.n_comments++;
        fileInfo.n_loc++; // slashes are not at the beginning, so there is code before
      } else {
        fileInfo.n_loc++; // line with just code
      }
    }

  } // end of for loop
}

/*!
* Processes a given file info, if it has a valid path, updates total line count,
 * number of lines of code, number of blank lines and number of comments in the file.
* @param fileInfo Reference to the information of the file to be processed.
 */
void update_line_count(FileInfo& fileInfo) {

  std::ifstream file{fileInfo.filename};
  std::string line;
  std::vector<std::string> all_file_lines;

  if (file.is_open()) {
    while (std::getline(file, line)) {
      fileInfo.n_lines++;
      all_file_lines.push_back(line);
    }

    code_analyzer(all_file_lines, fileInfo);

    file.close();
  } else {
    std::cout << "Sorry, error when opening file." << std::endl;
    exit(EXIT_FAILURE);
  }
}

/*!
* This function creates and returns a vector containing objects 
* for all the files that have been processed.
* @param src_files Vector containing the names of all files.
* @return Returns the vector containing objects with the data of each file.
*/
std::vector<FileInfo> list_content(const std::vector<std::string>& src_files) {

  std::vector<FileInfo> filesInfo;

  for(auto &file : src_files) {

    FileInfo fileContent;

    fileContent.filename = file;
    setFileType(fileContent);
    update_line_count(fileContent);

    filesInfo.push_back(fileContent);

  }

  return filesInfo;
}