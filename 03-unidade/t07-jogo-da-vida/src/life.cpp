/**
 * LLSeq class implementation.
 *
 */

#include "life.h"

namespace life {

// === Implementation of the Cell class
/// Constructor
Cell::Cell(const size_t& r = 0, const size_t& c = 0, const bool& alive = false)
    : row(r), col(c), is_alive(alive) {}

///=== Members.
/*!
 * Set the cell to alive.
 */
void Cell::set_alive() { this->is_alive = true; }

/*!
 * Set the cell to dead.
 */
void Cell::set_dead() { this->is_alive = false; }

/*!
 * Equality operator for comparing two Cell objects.
 * @param other The other Cell object to compare with.
 * @return true if the cells are equal (same row, column, and alive status), false otherwise.
 */
bool Cell::operator==(const Cell& other) const {
  return row == other.row && col == other.col && is_alive == other.is_alive;
}

// === Implementation of the LifeCfg class
/// Basic constructor that creates a life board with all cells dead.
LifeCfg::LifeCfg(size_t rows = 10, size_t cols = 10) : m_rows(rows), m_cols(cols) { fill_board(); }

/// Copy constructor
LifeCfg::LifeCfg(const LifeCfg& cfg) {
  this->m_rows = cfg.m_rows;
  this->m_cols = cfg.m_cols;
  this->m_board.clear();
  this->m_board.reserve(cfg.m_board.size());
  for (const auto& cell : cfg.m_board) {
    this->m_board.emplace_back(cell.row, cell.col, cell.is_alive);
  }
}

/*!
 * Display the game's initial message.
 */
void LifeCfg::print_game_of_life_intro() {
  std::cout << "****************************************************************\n";
  std::cout << "Welcome to Conway’s game of Life.\n";
  std::cout << "Running a simulation on a grid of size " << m_rows << " by " << m_cols << " in which\n";
  std::cout << "each cell can either be occupied by an organism or not.\n";
  std::cout << "The occupied cells change from generation to generation\n";
  std::cout << "according to the number of neighboring cells which are alive.\n";
  std::cout << "****************************************************************\n";
  std::cout << std::endl;
}

/*!
 * Sets the image pixels based on the board's current state.
 * @param img The Canvas object representing the image.
 * @param conf The configuration object containing color settings.
 */
void LifeCfg::set_img(Canvas &img, Config &conf) {
  for (const Cell &c : m_board) {
    if (c.row > 0 && c.row <= m_rows && c.col > 0 && c.col <= m_cols) {
      if (c.is_alive) { img.pixel(c.col - 1, c.row - 1, conf.get_alive_color()); } 
      else { img.pixel(c.col - 1, c.row - 1, conf.get_bkg_color()); }
    }
  }
}

/*!
 * Generates a filename for saving an image based on the generation number.
 * @param dir The directory where the file will be saved.
 * @param generation The generation number used in the filename.
 * @return std::string The generated filename.
 */
std::string LifeCfg::generate_filename(const std::string& dir, int generation) {
    std::ostringstream ss;
    std::string prefix = "gen_";
    std::string ext = ".png";

    ss << dir << "/" << prefix << std::setfill('0') << std::setw(5) << generation << ext;
    return ss.str();
}

/*!
 * Encodes an image in PNG format and saves it to a file.
 * @param filename The filename (including path) where the PNG image will be saved.
 * @param image Pointer to the image data to be encoded.
 * @param width Width of the image in pixels.
 * @param height Height of the image in pixels.
 * @return true if the image was successfully encoded and saved, false otherwise.
 */
bool LifeCfg::encode_png(const std::string& filename, const unsigned char* image, unsigned width, unsigned height) {
  // Encode the image
  unsigned error = lodepng::encode(filename, image, width, height);

  // if there's an error, display it
  if (error != 0U) { return false; }

  return true;
}

//=== Attribute accessors members.
/*!
  * Returns a reference to a cell stored in the board.
  * @param r row of the cell
  * @param c column of the cell
  * @return Cell in the (r,c) position of the board
  */
Cell& LifeCfg::get_cell(const size_t& r, const size_t& c) {
  const size_t index = r * get_expanded_cols() + c;
  return m_board[index];
}

/*!
  * Returns a reference to a cell in the board in a position relative to another.
  * @param cell Central cell from which the info is coming from.
  * @param orientation Defines which neighborhood location will be acessed.
  * @return Neighbor cell in the specified position relative to the base one.
  */
Cell& LifeCfg::get_neighbor(const Cell& cell, const e_cell_neighbor& orientation) {
  if (orientation == e_cell_neighbor::UPPER)
    return get_cell(cell.row - 1, cell.col);
  if (orientation == e_cell_neighbor::BELOW)
    return get_cell(cell.row + 1, cell.col);
  if (orientation == e_cell_neighbor::LEFT)
    return get_cell(cell.row, cell.col - 1);
  if (orientation == e_cell_neighbor::RIGHT)
    return get_cell(cell.row, cell.col + 1);
  if (orientation == e_cell_neighbor::BELOW_LEFT)
    return get_cell(cell.row + 1, cell.col - 1);
  if (orientation == e_cell_neighbor::BELOW_RIGHT)
    return get_cell(cell.row + 1, cell.col + 1);
  if (orientation == e_cell_neighbor::UPPER_LEFT)
    return get_cell(cell.row - 1, cell.col - 1);
  if (orientation == e_cell_neighbor::UPPER_RIGHT)
    return get_cell(cell.row - 1, cell.col + 1);

  return get_cell(cell.row, cell.col);  // returns the same cell if no condition is satisfied.
}

/*!
 * Counts the number of alive neighbors for a given cell.
 * @param cell The cell for which to count alive neighbors.
 * @return size_t The number of alive neighboring cells.
 */
size_t LifeCfg::get_alive_neighbor_count(const Cell& cell) {
  std::vector<Cell> neighborhood{
    get_neighbor(cell, e_cell_neighbor::LEFT), get_neighbor(cell, e_cell_neighbor::RIGHT),
    get_neighbor(cell, e_cell_neighbor::UPPER), get_neighbor(cell, e_cell_neighbor::BELOW),
    get_neighbor(cell, e_cell_neighbor::UPPER_LEFT), get_neighbor(cell, e_cell_neighbor::UPPER_RIGHT),
    get_neighbor(cell, e_cell_neighbor::BELOW_LEFT), get_neighbor(cell, e_cell_neighbor::BELOW_RIGHT)
  };
  
  size_t count = 0;

  for (const auto& neighbor_cell : neighborhood) {
    if (neighbor_cell.is_alive)
      ++count;
  }
  return count;
}

///=== Members.
/*!
 * Equality operator for comparing two LifeCfg objects.
 * @param other The other LifeCfg object to compare with.
 * @return true if the configurations are equal, false otherwise.
 */
bool LifeCfg::operator==(const LifeCfg& other) const {
  if (m_rows != other.m_rows || m_cols != other.m_cols) {
    return false;
  }

  return std::equal(m_board.begin(), m_board.end(), other.m_board.begin(),
  []( const Cell& cell1, const Cell& cell2) { return cell1 == cell2; });
}

/*!
 * Fills the board with dead cells.
 */
void LifeCfg::fill_board() {
  for (size_t i = 0; i < this->get_expanded_rows(); ++i) {
    for (size_t j = 0; j < this->get_expanded_cols(); ++j) {
      this->m_board.emplace_back(i, j, false);
    }
  }
}

/*!
 * Reads the contents of a file and returns its lines as a vector of strings.
 * @param filename The name of the file to read.
 * @return std::vector<std::string> The lines read from the file.
 */
std::vector<string> LifeCfg::read_file_info(const std::string& filename) {
  std::vector<std::string> lines;    //!< Vector with all lines from file.
  std::ifstream file(filename);

  std::cout << ">>> Trying to open input file [" << filename << "]...";
  
  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) { lines.push_back(line); }
    std::cout << " done!" << std::endl;
    file.close();
  } else {
    std::cerr << " error! " << std::endl;
    exit(EXIT_FAILURE);
  }

  return lines;
}

/*!
 * Loads the board configuration from a file.
 * @param filename The name of the file to load from.
 */
void LifeCfg::load_from_file(Config& ini_config) {
  std::vector<std::string> lines = read_file_info(ini_config.get_input_cfg());
  size_t line_count = 0;
  char alive_char = ' ';
  
  if(ini_config.get_max_gen() == 0) {
    std::cout << ">>> Running the simulation until extinction/stability is reached, whichever occurs first." << std::endl;
  } 

  if(ini_config.get_max_gen() != 0) {
    std::cout << ">>> Running simulation up to " << ini_config.get_max_gen()
              << " generations, or until extinction/stability is reached, whichever comes first." << std::endl;
  }

  std::cout << ">>> Processing data, plase wait..." << std::endl;

  for (const auto& line : lines) {
    /// Set number of lines and columns
    if (line_count == 0) {
      this->m_rows = std::stoi(line);
      this->m_cols = std::stoi(line.substr(line.find(' ') + 1));
      fill_board();
      
      std::cout << ">>> Grid size read from input file: " << m_rows 
                << " rows by " << m_cols << " cols." << std::endl;
    /// Set alive char in file.
    } else if (line_count == 1) {
      alive_char = line[0];
      std::cout << ">>> Character that represents a living cell read from input file: ’" << alive_char << "’." << std::endl;
    }
    /// Set configuration of board.
    else {
      const size_t row = line_count - 1;
      if (row > m_rows) {
        break;
      }
      update_row_from_file(line, alive_char, row, m_cols);
    }
    ++line_count;
  }
  std::cout << ">>> Finished reading input data file." << std::endl << std::endl;
}

/*!
 * @brief Updates a row of the board from file data.
 * @param line The line from the file representing a row.
 * @param trigger The character indicating a live cell.
 * @param row The row index to update.
 * @param max_cols The maximum number of columns.
 */
void LifeCfg::update_row_from_file(const std::string& line, char trigger, size_t row, size_t max_cols) {
  size_t col = 1;
  for (auto c : line) {
    if (col > max_cols)
      break;
    if (c == trigger)
      this->get_cell(row, col).set_alive();
    col++;
  }
}

/*!
 * Converts the current board state to a string representation.
 * @return std::string The string representation of the board.
 */
std::string LifeCfg::to_string() {
  std::ostringstream oss;
  for (size_t i = 1; i <= m_rows; ++i) {
    oss << "[";
    for (size_t j = 1; j <= m_cols; ++j) {
      if (get_cell(i, j).is_alive) {
        oss << "•";
      } else
        oss << " ";
    }
    oss << "]\n";
  }
  return oss.str();
}

/*!
 * Updates the board to the next generation according to the rules of the game.
 */
void LifeCfg::update() {
  auto previous_cfg = LifeCfg(*this);

  for (int i = 1; i <= this->m_rows; ++i) {
    for (int j = 1; j <= this->m_cols; ++j) {
      Cell& new_cell = get_cell(i, j);
      const Cell& past_cell = previous_cfg.get_cell(i,j);
      size_t alive_neighbors = previous_cfg.get_alive_neighbor_count(past_cell);
      
      if (alive_neighbors <= 1 or alive_neighbors >= 4) { new_cell.set_dead(); }
      else if (!past_cell.is_alive and alive_neighbors == 3) { new_cell.set_alive(); }
    }
  }
}

/*!
 * Checks if the current board configuration is extinct (no live cells).
 * @return true if there are no live cells, false otherwise.
 */
bool LifeCfg::extinct() const {
  for (const auto& cell : m_board) {
    if (cell.is_alive) { return false; }
  }
  return true;
}

/*!
 * Checks if the current board configuration is stable (matches any previous configurations).
 * @param previous_configs The vector of previous configurations to check against.
 * @return true if the configuration is stable, false otherwise.
 */
bool LifeCfg::stable(const std::vector<LifeCfg>& previous_configs) const {
  for (const auto& cfg : previous_configs) {
    if (*this == cfg) {
      return true;
    }
  }
  return false;
}

/// TODO:

/*!
 * Runs the simulation for a given number of generations or until extinction/stability.
 * @param ini_config An object with all options of configurations of the simulation.
 */
void LifeCfg::generation_loop(Config& ini_config) {

  print_game_of_life_intro();

  std::vector<LifeCfg> history;   //!<- Vector with all history of generations.
  int max_gen;
  int generation = 1;
  int frame_duration = 1000 / ini_config.get_fps();

  /// Set the max generation.
  if (ini_config.get_max_gen() == 0) { max_gen = 99999; } 
  else { max_gen = ini_config.get_max_gen(); }
  
  while (generation <= max_gen) {
    /// Check stop conditions.
    if (this->extinct()) { 
      std::cout << "\n>>> Extinct configuration. ";
      break; 
    }
    if (this->stable(history)) { 
      auto it = std::find(history.begin(), history.end(), *this);  //<- Find element.
      int index = std::distance(history.begin(), it);
      int frequency = generation - index - 2; 

      std::cout << "\nStable configuration starting at generation " << index + 1 << " with frequency = " << frequency << ". ";
      break; 
    }
    
    /// Display or generate an image of each generation of the simulation.
    if(ini_config.get_generate_image()) {
      
      std::cout << "Generation " << generation << ":" << std::endl;
      
      Canvas image(m_cols, m_rows, ini_config.get_block_size());  //!< The image set a canvas.  
      set_img(image, ini_config);  //!< Update the configuration in image.

      std::string filename = generate_filename(ini_config.get_path(), generation);
      bool sucess = encode_png(filename, image.pixels(), image.width(), image.height());  //!< Indicate if the image generation was a sucessfuly.

      if(sucess) { std::cout << "Image saved successfully: " << filename << std::endl; }
      if(!sucess) { std::cout << "Failed to save image: " << filename << std::endl; }

    } else {
      std::cout << "Generation " << generation << ":" << std::endl;
      std::cout << this->to_string();
      std::this_thread::sleep_for(std::chrono::milliseconds(frame_duration));
    }
    
    /// Update data.
    history.push_back(*this);
    this->update();
    generation++;
  }

  std::cout << "Finish simulation!" << std::endl;
}
}  // namespace life