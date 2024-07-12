#include <string>
#include <vector>

#include "common.h"
#include "directory.h"

#ifndef LISTING_FILE_CONTENT_H
#define LISTING_FILE_CONTENT_H

//== Headers to functions

/*!
* Processes a given file info, if it has a valid path, updates total line count,
 * number of lines of code, number of blank lines and number of comments in the file.
* @param fileInfo Reference to the information of the file to be processed.
*/
void update_line_count(FileInfo &fileInfo);

/*!
 * Analyzes the amount of comment, code and blank lines in a given file,
 * updating file info attributes.
 * @param file_lines String collection of all lines in the file.
 * @param fileInfo Object that holds the file data.
 */
void code_analyzer(const std::vector<std::string>& file_lines, FileInfo &fileInfo);

/*!
 * Returns a copy of the given string with all content inside quotes removed.
 * @param s Original string that will be treated.
 * @return New string with just the content present outside quotes.
 */
inline std::string remove_quote_content (const std::string& s);

/*!
* This function adds the file type to the file object.
* @param fileInfo Object that will hold the file data.
*/
void setFileType(FileInfo &fileInfo);

/*!
* This function creates and returns a vector containing objects 
* for all the files that have been processed.
* @param src_files Vector containing the names of all files.
* @return Returns the vector containing objects with the data of each file.
*/
std::vector<FileInfo> list_content(const std::vector<std::string>& src_files);

#endif