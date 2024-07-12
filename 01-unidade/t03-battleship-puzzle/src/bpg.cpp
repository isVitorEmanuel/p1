#include "bpg.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <random>

using namespace bpg;

// Ship --------------------------------------------

// Default
Ship::Ship(Ship::type t, Ship::orientation o, Cell position)
    : m_type (t), m_orientation(o), m_position(position){}

//Copy Constructor
Ship::Ship(const Ship &ship){
  this->m_type = ship.m_type;
  this->m_orientation = ship.m_orientation;
  this->m_position = ship.m_position;
}

bool Ship::operator==(const bpg::Ship& rhs) const {
  return m_orientation == rhs.m_orientation and m_type == rhs.m_type and
           m_position == rhs.m_position;
}

bool Ship::operator<(const bpg::Ship& rhs) const {
  if (this->m_type == Ship::type::battleship)
    return false;

  if (rhs.m_type == Ship::type::battleship)
    return true;

  if (this->m_type == Ship::type::destroyer)
    return false;

  if (rhs.m_type == Ship::type::destroyer)
    return true;

  if (this->m_type == Ship::type::cruiser)
    return false;

  return true;
}

std::string Ship::to_string() const {
  std::ostringstream oss;

  char ship_type = static_cast<char>(this->m_type);
  short ship_row = this->m_position.row + 1;
  short ship_col = this->m_position.col + 1;
  char ship_orientation = static_cast<char>(this->m_orientation);

  oss << ship_type << " " << ship_row << " " << ship_col;
  if (ship_orientation != 'U'){
    oss << " " << ship_orientation;
  }

  return oss.str();
}

// Puzzle --------------------------------------------

Puzzle::Puzzle(short r, short c) : rows{r}, cols{c}{
  Puzzle::fill_board();
}

Puzzle::Puzzle(const Puzzle &pz) {
  this->rows = pz.rows;
  this->cols = pz.cols;
  this->board = pz.board;
  this->ship_list = pz.ship_list;
}

void Puzzle::fill_board() {
  for (short i = 0; i < this->rows; ++i) {
    for (short j = 0; j < this->cols; ++j) {
      this->board.emplace_back(i, j, Cell::content::water);
    }
  }
}

std::string Puzzle::to_string() const {
  std::string puzzle_code;
  for (const Ship& ship : ship_list){
    puzzle_code.append(ship.to_string());
    puzzle_code += '\n';
  }
  puzzle_code += '\n';
  return puzzle_code;
}

std::string Puzzle::to_matrix() const {
  std::ostringstream oss;

  oss << this->rows << " " << this->cols << '\n';

  for (int i = -1; i <= this->rows; ++i) {
    if (i == -1 or i == 0){
      oss << "    ";
    } else if (i < 10){
      oss << " " << i << "[";
    } else {
      oss << i << "[";
    }
    for (int j = 1; j <= this->cols; ++j) {
      int board_index = (j - 1) + (i - 1) * this->cols;
      // first line of the matrix with spaces or 1 according to board size
      if (i == -1){
        if (j < 10)
          oss << "  ";
        else
          oss << "1 ";
      }
      // second line of the matrix with
      else if (i == 0){
        if (j < 10)
          oss << j << " ";
        else
          oss << j - 10 << " ";
      }
      // Logic of placing ship icons
      else {
        if (this->board[board_index].cell_content == Cell::content::ship){
          if (Puzzle::next_is_ship(board_index) and !Puzzle::previous_is_ship(board_index))
             oss << " ◀";
          else if (!Puzzle::next_is_ship(board_index) and Puzzle::previous_is_ship(board_index))
            oss << " ▶";
          else if ((Puzzle::next_is_ship(board_index) and Puzzle::previous_is_ship(board_index))
                   or (Puzzle::below_is_ship(board_index) and Puzzle::above_is_ship(board_index)))
            oss << " ◼";
          else if (Puzzle::below_is_ship(board_index) and !Puzzle::above_is_ship(board_index))
            oss << " ▲";
          else if (!Puzzle::below_is_ship(board_index) and Puzzle::above_is_ship(board_index))
            oss << " ▼";
          else
            oss << " ●";
        }
        else
          oss << " .";

        if (j == this->cols){
          oss << " ]";
        }
      }
    }
    oss << "\n";
  }
  return oss.str();
}

// Updates list of ships based on board cells
void Puzzle::update_ship_list() {
  this->ship_list.clear();
  Ship aux = Ship();
  int aux_size;

  std::map<int, Ship::type> ship_type = {
    {4, Ship::type::battleship},
    {3, Ship::type::destroyer},
    {2, Ship::type::cruiser},
    {1, Ship::type::submarine}
  };

  std::list<int> ship_body_indexes;

  for (int i = 0; i < this->board.size(); i++){

    aux_size = 1;
    aux.m_orientation = Ship::orientation::U;

    bool i_already_checked = false;
    for (auto index : ship_body_indexes){
      if (index == i)
        i_already_checked = true;
    }

    if (i_already_checked){
      continue;
    }

    // Verifies if current cell is a ship cell
    bool is_ship = board[i].cell_content == Cell::content::ship;

    if (is_ship){
      aux.m_position = board[i];
      int j = i;

      while (next_is_ship(j)){
        aux.m_orientation = Ship::orientation::H;
        j++;
        ship_body_indexes.push_back(j);
        aux_size++;
      }

      while (below_is_ship(j)){
        aux.m_orientation = Ship::orientation::V;
        j+= this->cols;
        ship_body_indexes.push_back(j);
        aux_size++;
      }

      aux.m_type = ship_type[aux_size];

      // Puts the ship in the ship_list
      this->ship_list.push_back(aux);
    }
  }
}

// Verifies if next cell is at same row and if it's a ship
bool Puzzle::next_is_ship (int i) const {
  if (i+1 < board.size()){
    return board[i+1].cell_content == Cell::content::ship
                   and board[i+1].row == board[i].row;
  }
  return false;
}
// Verifies if previous cell is at same row and if it's a ship
bool Puzzle::previous_is_ship (int i) const {
  if (i - 1 >= 0){
    return board[i-1].cell_content == Cell::content::ship
           and board[i-1].row == board[i].row;
  }
  return false;
}

// If is possible to reach a cell below the current one, verifies if it's a ship
bool Puzzle::below_is_ship (int i) const {
  if (i + this->cols < board.size()){
    return board[i + this->cols].cell_content == Cell::content::ship;
  }
  return false;
}
// If is possible to reach a cell above the current one, verifies if it's a ship
bool Puzzle::above_is_ship (int i) const {
  if (i - this->cols >= 0){
    return board[i - this->cols].cell_content == Cell::content::ship;
  }
  return false;
}

// Flip functions

Puzzle Puzzle::flip_h (const Puzzle& pz) {
  Puzzle flipped_pz = Puzzle(pz);

  for (auto &cell : flipped_pz.board){
    cell.row = flipped_pz.rows - cell.row - 1;
  }

  std::sort(flipped_pz.board.begin(), flipped_pz.board.end());
  flipped_pz.update_ship_list();

  return flipped_pz;
}

Puzzle Puzzle::flip_v (const Puzzle& pz) {
  Puzzle flipped_pz = Puzzle(pz);
  for (auto &cell : flipped_pz.board){
    cell.col = flipped_pz.cols - cell.col - 1;
  }

  std::sort(flipped_pz.board.begin(), flipped_pz.board.end());
  flipped_pz.update_ship_list();

  return flipped_pz;
}

Puzzle Puzzle::flip_hv (const Puzzle& pz) {
  Puzzle flipped_pz = Puzzle(pz);
  return flip_h(flip_v(flipped_pz));
}

// Neighbor checker functions

int Puzzle::get_right(int i) const{
  if (i >= 0 and (i + 1) < board.size()) {
    if (board[i].row == board[i + 1].row) {
      return i + 1;
    }
  }
  return -1;
}
int Puzzle::get_left(int i) const{
  if ((i - 1) >= 0) {
    if (board[i].row == board[i - 1].row) {
      return i - 1;
    }
  }
  return -1;
}
int Puzzle::get_upper(int i) const{
  if (i - this->cols >= 0){
    return i - this->cols;
  }
  return -1;
}
int Puzzle::get_below(int i) const{
  if (i>=0 and i + this->cols < board.size()){
    return i + this->cols;
  }
  return -1;
}
int Puzzle::get_diag_ur(int i) const{
  return (get_upper(get_right(i)));
}
int Puzzle::get_diag_ul(int i) const{
  return get_upper(get_left(i));
}
int Puzzle::get_diag_br(int i) const{
  return get_below(get_right(i));
}
int Puzzle::get_diag_bl(int i) const{
  return get_below(get_left(i));
}

bool Puzzle::is_valid() {
  short ship_cells = 0;
  this->update_ship_list();

  for (auto cell : this->board){
    if (cell.cell_content == Cell::content::ship)
      ship_cells++;
  }

  if (this->ship_list.size() == 10 and ship_cells == 20){
    return true;
  }

  return false;
}

// Generator --------------------------------------------

std::list<Puzzle> Generator::generate(const RunningOpt & run_opt){
  std::list<Puzzle> puzzle_list;
  std::list<std::string> puzzle_codes;

  std::vector<Ship> armada = {
    Ship(Ship::type::battleship),Ship(Ship::type::destroyer),
    Ship(Ship::type::destroyer),Ship(Ship::type::cruiser),
    Ship(Ship::type::cruiser),Ship(Ship::type::cruiser),
    Ship(Ship::type::submarine), Ship(Ship::type::submarine),
    Ship(Ship::type::submarine),Ship(Ship::type::submarine)
  };

  while (puzzle_list.size() < run_opt.n_puzzles){

    Puzzle pz = Puzzle(run_opt.rows, run_opt.cols);
    std::vector<Ship> current_armada = armada;

    // Shuffles the current copy of the armada
    std::random_device rd;
    std::default_random_engine g(rd());
    std::shuffle(current_armada.begin(), current_armada.end(), g);

    while (!current_armada.empty()){
      bool success_placing_ship = try_place_ship(current_armada[0], pz);

      if (success_placing_ship){
        current_armada.erase(current_armada.begin());
      } else {
        break;
      }
    }

    // List of ships to be put is empty and a valid puzzle has been generated
    if (current_armada.empty() and pz.is_valid()){
      // creates a list with generated puzzle and flipped versions
      std::list<Puzzle> puzzle_candidates = {
        pz, Puzzle::flip_v(pz), Puzzle::flip_h(pz), Puzzle::flip_hv(pz)
      };

      // try to add every candidate to puzzle list if number of puzzles not achieved yet
      for (auto& puzzle : puzzle_candidates){
        // Comment the next 2 lines to show ships in order they were placed instead of B,D,C,S
        puzzle.ship_list.sort();
        puzzle.ship_list.reverse();

        if (!code_in_list(puzzle.to_string(), puzzle_codes) and
            puzzle_list.size() < run_opt.n_puzzles){
          puzzle_codes.push_back(puzzle.to_string());
          puzzle_list.push_back(puzzle);
        }
      }
    }
  }

  return puzzle_list;
}

bool Generator::try_place_ship(Ship& ship, Puzzle& pz) {

  // Data structure for ship size
  const std::map<Ship::type, int> ship_size_map = {
    {Ship::type::battleship, 4},
    {Ship::type::destroyer, 3},
    {Ship::type::cruiser, 2},
    {Ship::type::submarine, 1}
  };

  const int ship_size = ship_size_map.at(ship.m_type);

  for (int i = 0; i <= pz.board.size(); ++i){

    bool is_available = true;
    if (pz.board[i].cell_content == Cell::content::water){

      if (ship.m_type == Ship::type::submarine){ // submarines only need 1 water cell
        put_ship(pz, ship_size, i, ship.m_orientation);
        return true;
      }

      // Try Horizontal ship
      ship.m_orientation = Ship::orientation::H;
      bool enough_space_in_row = true;
      for (int j = 0; j < ship_size; j++){
        if (j < ship_size - 1)
          enough_space_in_row = pz.get_right(i+j) > 0;
        if (enough_space_in_row){
          if (pz.board[i+j].cell_content != Cell::content::water){
            is_available = false;
          }
        } else {
          is_available = false;
        }
      }

      if (is_available){ // success with horizontal ship
        put_ship(pz, ship_size, i, ship.m_orientation);
        return true;
      } else {
        is_available = true; // code continues to check if vertical ship is possible
      }
      // Try vertical ship
      ship.m_orientation = Ship::orientation::V;
      bool enough_space_in_column = true;
      for (int j = 0; j < ship_size; j++){
        if (j < ship_size - 1)
          enough_space_in_column = pz.get_below(i+j*pz.cols) > 0;
        if (enough_space_in_column){
          if (pz.board[i+j*pz.cols].cell_content != Cell::content::water){
            is_available = false;
          }
        } else {
          is_available = false;
        }
      }

      if (is_available){ // success with vertical ship
        put_ship(pz, ship_size, i, ship.m_orientation);
        return true;
      }
    }
  }

  return false;
}

Puzzle Generator::put_ship(Puzzle& pz, int ship_size, int i, Ship::orientation o) {

  // Fill cells for horizontal ship
  if (o == Ship::orientation::H){
    for (int j = 0; j < ship_size; j++){
      pz.board[i+j].cell_content = Cell::content::ship;
    }
  }

  // Fill cells for vertical ship
  if (o == Ship::orientation::V){
    for (int j = 0; j < ship_size; j++){
      pz.board[i+j*pz.cols].cell_content = Cell::content::ship;
    }
  }
  // Fill cell for submarine
  if (o == Ship::orientation::U){
    pz.board[i].cell_content = Cell::content::ship;
  }

  // Fill all cells that are water near a ship with ship_aura
  for (int j = 0; j < pz.board.size(); ++j) {
    if (pz.board[j].cell_content == Cell::content::ship){
      std::list<int> neighbor_cells_indexes = {
        pz.get_left(j),pz.get_right(j),pz.get_below(j),pz.get_upper(j),
        pz.get_diag_ur(j), pz.get_diag_ul(j),pz.get_diag_br(j), pz.get_diag_bl(j)
      };
      for (auto index : neighbor_cells_indexes){
        if (index >= 0){
          if (pz.board[index].cell_content == Cell::content::water){
            pz.board[index].cell_content = Cell::content::ship_aura;
          }
        }
      }
    }
  }

  return pz;
}

// Could be replaced by std::any_of using a lambda function
bool Generator::code_in_list(const std::string& pz_code, const std::list<std::string>& pz_codes) {
  for (const auto& code : pz_codes){
    if (pz_code == code){
      return true;
    }
  }
  return false;
}
