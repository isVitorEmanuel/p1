#ifndef _BPG_H_
#define _BPG_H_

#include <list> // std::list
#include <ostream>
#include <sstream>
#include <set>
#include <vector> // std::vector

#include "common.h"

namespace bpg {

/// A Cell is a simple struct that represents a location within a puzzle board.
struct Cell {
  using coord_type = short; //!< Alias for a cell coordinate type.

  enum class content : unsigned char {
    ship = 0,
    ship_aura,
    water
  };

  coord_type row{0}; //!< Row of a cell within a puzzle board.
  coord_type col{0}; //!< Column of a cell within a puzzle board.
  content cell_content{content::water}; //!< Content of a cell within a puzzle board.

  //=== Special members
  /// Default constructor
  Cell(coord_type r = 0, coord_type c = 0, content c_content = content::water)
      : row{r}, col{c}, cell_content{c_content} { /*empty*/ }
  /// Destructor
  ~Cell() = default;

  //=== Regular methods
  /// Check if two cells have the same coordinates.
  bool operator==(const Cell &rhs) const {
    return row == rhs.row and col == rhs.col and cell_content == rhs.cell_content;
  }

  /// Compare two cells and allows sorting
  bool operator<(const Cell &rhs) const {
    return (row < rhs.row) or (row == rhs.row and col < rhs.col);
  }
};

/// This class represents a ship.
class Ship {
public:
  /// The possible ships are: Battleship, Destroyer, Cruiser, Submarine
  /// Defines the ship type.
  enum class type : char {
    battleship = 'B',
    destroyer = 'D',
    cruiser = 'C',
    submarine = 'S'
  };
  /// Defines the ship orientation.
  enum class orientation : char {
    H = 'H' /* horizontal */,
    V = 'V' /* vertical */,
    U = 'U' /* undefined */
  };

  //=== Members
  type m_type = type::battleship; //!< Type of a ship, default is battleship.
  orientation m_orientation = orientation::U; //!< Orientation of a ship, default is undefined.
  Cell m_position = Cell(0,0, Cell::content::ship); //!< Starting position of a ship within a puzzle board.

  //=== Special Methods
  /// Default constructor
  Ship(type t = type::battleship, orientation o = orientation::U,
       Cell position = Cell(0,0,Cell::content::ship));
  /// Copy constructor.
  Ship(const Ship &ship);
  /// Destructor.
  ~Ship() = default;

  //=== Regular methods
  /// Equal operator
  bool operator==(const Ship &rhs) const;

  /// Comparison operator
  bool operator<(const Ship &rhs) const;

  /// Returns a string representation of a ship based on type, orientation and position on board.
  [[nodiscard]] std::string to_string() const;
};

/// This class represents a battleship puzzle board with ships on it.
class Puzzle {
public:
  short rows = default_rows; //!< Number of rows in the puzzle board.
  short cols = default_cols; //!< Number of columns in the puzzle board.
  std::vector<Cell> board; //!< Stores all Cells that make up the board.
  std::list<Ship> ship_list; //!< List of all ships currently on the board.

  /// Default constructor - must call fill_board()
  Puzzle(short rows = default_rows, short cols = default_cols);

  /// Copy constructor
  Puzzle(const Puzzle &pz);

  /// Destructor
  ~Puzzle() = default;

  /// Returns a string representation of a puzzle, Armada format
  [[nodiscard]] std::string to_string() const;

  /// Returns a string representation of a puzzle, Matrix format
  [[nodiscard]] std::string to_matrix() const;

  /*!
   * Returns a horizontally flipped version of a given Puzzle.
   *
   * @param pz Reference to the original puzzle which will be flipped.
   *
   * @return A puzzle with rows flipped horizontally.
   */
  static Puzzle flip_h (const Puzzle& pz);

  /*!
   * Returns a vertically flipped version of a given Puzzle.
   *
   * @param pz Reference to the original puzzle which will be flipped.
   *
   * @return A puzzle with rows flipped vertically.
   */
  static Puzzle flip_v (const Puzzle& pz);

  /*!
   * Returns a flipped version of a given Puzzle, both horizontally and vertically.
   *
   * @param pz Reference to the original puzzle which will be flipped.
   *
   * @return A puzzle with rows flipped horizontally and vertically.
   */
  static Puzzle flip_hv (const Puzzle& pz);

  /// Updates the list of ships in the Puzzle based on board cells content.
  void update_ship_list();

  /**
 * \defgroup GetNeighbor Functions that get the index of a "neighbor" cell.
 * @brief The functions take a index of a element in the board and returns the correspondent index
   * of the neighbor cell, i.e. the cell above the current one.
 * @param i Index of a cell in the board vector.
 * @retval Returns the index of the neighbor cell if it is valid, -1 otherwise.
 * @{
 */
  int get_right(int i) const;
  int get_left(int i) const;
  int get_upper(int i) const;
  int get_below(int i) const;
  int get_diag_ur(int i) const;
  int get_diag_ul(int i) const;
  int get_diag_br(int i) const;
  int get_diag_bl(int i) const;
  /** @} */

  /*!
   * Checks if the puzzle is valid/complete.
   * @return True if board contains exactly 20 ship cells and ship_list contains exactly 10 ships.
   * False otherwise.
   */
  bool is_valid();

private:
  /// Fills the board with rows * cols Cells of water.
  void fill_board();

  /**
 * \defgroup IsShip Functions that check if a neighbor cell is a ship cell.
 * @brief The functions take a index of a element in the board and checks if the immediate
   * neighbor cell in the given direction is a Ship cell.
 * @param i Index of a cell in the board vector.
 * @retval Returns true if the neighbor index is valid AND cell content for that index is Ship.
   * False otherwise.
 * @{
   */
  [[nodiscard]] bool next_is_ship (int i) const;
  [[nodiscard]] bool below_is_ship (int i) const;
  [[nodiscard]] bool previous_is_ship (int i) const;
  [[nodiscard]] bool above_is_ship (int i) const;
  /** @} */

};

/// Represents an automatic way of randomly placing Ships on a Puzzle.
class Generator {
public:

  /*!
   * Generates a list of valid puzzles according to run_opt specification
   * @param run_opt A struct containing information about the number of puzzles that will be
   * generated, number of rows and cols.
   * @return A list containing n valid puzzles with fixed dimensions specified by run_opt param.
   */
  [[nodiscard]] static std::list<Puzzle> generate(const RunningOpt & run_opt);

  /*!
   * Tries to place a ship in a given Puzzle board, tries first horizontally then vertically,
   * if it is a submarine orientation remains undefined.
   * @param ship A ship with undefined orientation and type already established.
   * @param pz Puzzle that should be modified by ship addition.
   * @return True if placing ship operation was a success, False otherwise.
   */
  static bool try_place_ship (Ship &ship, Puzzle &pz);

  /*!
   * Effectively puts a ship in a given puzzle board, availability should be checked before calling
   * this function.
   * @param pz The puzzle where the ship will be put.
   * @param ship_size The number of cells the ship occupies.
   * @param index Index of the cell in the board corresponding to the ship starting position.
   * @param o Ship orientation: horizontal, vertical, undefined.
   * @return Puzzle with modifications after putting the ship.
   */
  static Puzzle put_ship (Puzzle &pz, int ship_size, int index, Ship::orientation o);

  /*!
   * Checks if a given Puzzle string is already present in a list of puzzle codes.
   * @param pz_code Code that will be compared to every other in the list
   * @param pz_codes List containing other puzzle codes.
   * @return True if code already in the list, False otherwise.
   */
  static bool code_in_list (const std::string& pz_code, const std::list<std::string>& pz_codes);
};

} // namespace bpg

#endif
