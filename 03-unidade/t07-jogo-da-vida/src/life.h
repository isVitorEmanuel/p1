//! This class implements a life board in the Conway's Game of Life.
/*!
 * @file life.h
 *
 * @details Class Life, to simulate the Conway's Game of Life.
 *
 * @author	Selan R dos Santos, <selan.rds@gmail.com>
 * @date	2015, updated 2015-04-03
 * @update 2019, April 2nd.
 * @version     v1.1
 */

#ifndef _LIFE_H_
#define _LIFE_H_

#include <cassert>
#include <cstring>  // std::memcpy().
#include <iostream>
#include <set>
#include <sstream>  // std::ostringstream
#include <stdexcept>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <thread>  
#include <chrono>  
#include <filesystem>

using std::cerr;
using std::cout;
using std::endl;
using std::set;
using std::string;
using std::vector;

#include "canvas.h"
#include "lodepng.h"
#include "config.h"

namespace life {

/// Cell represents an atomic location within a Life game board.
class Cell {
public:
  size_t row{ 0 };         //!< Row of a cell within a puzzle board.
  size_t col{ 0 };         //!< Row of a cell within a puzzle board.
  bool is_alive{ false };  //!< Tells whether a cell is alive or not.

  //=== Special members.
  /// Constructor
  Cell(const size_t& r, const size_t& c, const bool& alive);
  /// Destructor
  ~Cell() = default;

  //=== Members.
  /// Changes is_alive to true.
  void set_alive();
  /// Changes is_alive to false.
  void set_dead();
  /// Equality operator for comparing two Cell objects.
  bool operator==(const Cell& other) const;

};

/// All eight directions a cell neighbor can be found.
enum class e_cell_neighbor : short {
  UPPER = 0,
  BELOW,
  LEFT,
  RIGHT,
  UPPER_LEFT,
  UPPER_RIGHT,
  BELOW_LEFT,
  BELOW_RIGHT,
};

/// A life configuration.
class LifeCfg {

public:
  size_t m_rows;        //!< Number of rows in the game board.
  size_t m_cols;        //!< Number of columns in the game board.
  vector<Cell> m_board; //!< All cells that defines the current game board.

  //=== Special members
  /// Default constructor
  LifeCfg() : m_rows(10), m_cols(10){ }
  /// Argument constructor, also calls fill_board
  LifeCfg(size_t rows, size_t cols);
  /// Copy constructor
  LifeCfg(const LifeCfg& cfg);
  /// Default Destructor
  ~LifeCfg() = default;

  //=== Output members.
  /// Display the game's initial message.
  void print_game_of_life_intro();
  /// Sets the image pixels based on the board's current state.
  void set_img(Canvas& img, Config& conf);
  /// Generates a filename for saving an image based on the generation number.
  std::string generate_filename(const std::string& dir, int generation);
  /// Encodes an image in PNG format and saves it to a file.
  bool encode_png(const std::string& filename, const unsigned char* image, unsigned width, unsigned height);

  //=== Attribute accessors members.
  /// Number of columns with expanded borders
  [[nodiscard]] size_t get_expanded_cols() const { return m_cols + 2; }
  /// Number of rows with expanded borders
  [[nodiscard]] size_t get_expanded_rows() const { return m_rows + 2; }
  /// Returns a reference to a cell stored in the board.
  Cell& get_cell(const size_t& r, const size_t& c);
  /// Returns a reference to a cell in the board in a position relative to another.
  Cell& get_neighbor(const Cell& cell, const e_cell_neighbor& orientation);
  /// Counts the number of alive neighbors for a given cell.
  size_t get_alive_neighbor_count(const Cell& cell);

  //=== Members
  /// Equality operator for comparing two LifeCfg objects.
  bool operator==(const LifeCfg&) const;
  /// Fills the entire board with dead cells, uses expanded board values
  void fill_board();
  /// Returns a vector with all lines from a base file
  static std::vector<std::string> read_file_info(const std::string& filename);
  /// Initializes the board configuration from a base file.
  void load_from_file(Config& ini_config);
  /// Updates a row on the board based on file info.
  void update_row_from_file(const std::string& line, char trigger, size_t row, size_t max_cols);
  /// Converts the current board state to a string representation.
  [[nodiscard]] std::string to_string();
  /// Updates the board to the next generation according to the rules of the game.
  void update();
  /// Checks if the current board configuration is extinct (no live cells).
  bool extinct() const;
  /// Checks if the current board configuration is stable (matches any previous configurations).
  bool stable(const std::vector<LifeCfg>& previous_config) const;
  /// Runs the simulation for a given number of generations or until extinction/stability.
  void generation_loop(Config& ini_config);
};

}  // namespace life

#endif
