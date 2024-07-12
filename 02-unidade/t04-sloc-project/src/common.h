#include <string>
#include <vector>

#ifndef COMMON_H
#define COMMON_H

//== Enumerations

/// This enumeration lists all the supported languages.
enum lang_type_e {
  C = 0, //!< C language
  CPP,   //!< C++ language
  H,     //!< C/C++ header
  HPP,   //!< C++ header
  JAVA,  //!< Java language
  UNDEF, //!< Undefined type.
};

/// This enumeration lists all types of entry
enum typeEntry {
  DIRE = 0,
  FIL,
};

//== Class/Struct declaration

/// Integer type for counting lines.
using count_t = unsigned long;
/// Stores the file information we are collecting.
class FileInfo {
public:
  std::string filename;    //!< the filename.
  lang_type_e type;   //!< the language type.
  count_t n_blank;    //!< # of blank lines in the file.
  count_t n_comments; //!< # of comment lines.
  count_t n_loc;      //!< # lines of code.
  count_t n_lines;    //!< # of lines.

  /// Ctro.
  FileInfo(std::string fn = "", lang_type_e t = UNDEF, count_t nb = 0,
           count_t nc = 0, count_t nl = 0, count_t ni = 0)
      : filename{std::move(fn)}, type{t}, n_blank{nb}, n_comments{nc},
        n_loc{nl}, n_lines{ni} {
    /* empty*/
  }
};

/// The running options provided via CLI.
struct RunningOpt {
  std::string input_name = ""; //!< This might be a filename or a directory.
  std::string option = "-sd";
  // TODO: add other running options here.
};

//== Aux functions

// trim from left
inline std::string ltrim(const std::string &s, const char *t = " \t\n\r\f\v") {
  std::string clone{s};
  clone.erase(0, clone.find_first_not_of(t));
  return clone;
}
// trim from right
inline std::string rtrim(const std::string &s, const char *t = " \t\n\r\f\v") {
  std::string clone{s};
  size_t end_pos = clone.find_last_not_of(t);
  if (end_pos != std::string::npos)
    clone.erase(clone.find_last_not_of(t) + 1);
  else
    clone.clear();
  return clone;
}
// trim from left & right
inline std::string trim(const std::string &s, const char *t = " \t\n\r\f\v") {
  std::string clone{s};
  clone = ltrim(clone, t);
  clone = rtrim(clone, t);

  return clone;
}

#endif