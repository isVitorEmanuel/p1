#ifndef COMMON_H
#define COMMON_H

#include <string>

constexpr unsigned short max_rows{ 16 };
constexpr unsigned short min_rows{ 7 };

constexpr unsigned short max_cols{ 16 };
constexpr unsigned short min_cols{ 7 };

constexpr unsigned short min_n_puzzles{ 1 };
constexpr unsigned short max_n_puzzles{ 100 };

constexpr unsigned short default_rows{ 10 };
constexpr unsigned short default_cols{ 10 };
constexpr unsigned short default_n_puzzles{ 1 };

/// Running Options
struct RunningOpt {
  unsigned short n_puzzles = default_n_puzzles;
  unsigned short rows = default_rows;
  unsigned short cols = default_cols;
  std::string armada_file{ "puzzles_armada.bp" };
  std::string matrix_file{ "puzzles_matrix.bp" };
};

#endif  // !COMMON_H
