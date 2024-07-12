/*!
 * \brief Battleship Puzzle Generator
 * \author Selan
 * \date March 15th, 2024.
 *
 * This program generates and outputs to a file a bat of
 * battleship puzzles.
 * https://en.wikipedia.org/wiki/Battleship_(puzzle)
 *
 * The puzzles should be between 10x10 and 16x16 boards,
 * with 10 ships.
 * The ships might be:
 *  - 01 Battleship (4 pieces long)
 *  - 02 Cruisers (3 pieces long)
 *  - 03 Destroyers (2 pieces long)
 *  - 04 Submarines (1 piece long)
 *
 * The puzzles file should be read by another application, the
 * battleship puzzle game.
 */

#include <iostream> // std::cout, std::endl
#include <fstream>

#include "bpg.h"
#include "common.h"
#include "graal.h"
#include "validated.h"

/*!
 * This function prints the welcome display to the user.
 *
 */
void welcome_msg() {

  /// Display welcome screen to the user.
  std::cout << "--------------------------------------------------------------\n";
  std::cout << "<<<< Welcome to Project Battleship Puzzle Generator (PBG) >>>>\n";
  std::cout << "--------------------------------------------------------------\n";
  std::cout << "This project was developed by the following students of the \nBTI course at UFRN:\n";
  std::cout << "\n- Vitor Emanuel Rodrigues de Alencar\n";
  std::cout << "- Igor Marques de Lima\n";
  std::cout << "\n--------------------------------------------------------------\n";
  std::cout << "IMD (UFRN), 2024.1!\n";
  std::cout << "--------------------------------------------------------------\n";
}

void save_puzzles(const RunningOpt &run_opt,
                  const std::list<bpg::Puzzle> &puzzles) {

  std::ofstream puzzles_armada("./data/" + run_opt.armada_file);
  std::ofstream puzzles_matrix ("./data/" + run_opt.matrix_file);

  if (!puzzles_armada.is_open()) {
    std::cerr << "Failed to open armada output file." << std::endl;
  }
  if (!puzzles_matrix.is_open()) {
    std::cerr << "Failed to open matrix output file." << std::endl;
  }

  puzzles_armada << run_opt.n_puzzles << "\n\n";
  puzzles_matrix << run_opt.n_puzzles << "\n\n";

  for (auto& puzzle : puzzles){
    puzzles_armada << puzzle.rows << " " << puzzle.cols << '\n';
    puzzles_armada << puzzle.to_string();
    puzzles_matrix << puzzle.to_matrix() << '\n';
  }
  puzzles_armada.close();
  puzzles_matrix.close();
}

int main(int argc, char *argv[]) {

  // [1] Print Welcome message.
  welcome_msg();

  // [2] Read and validate the running options passed as arguments.
  RunningOpt run_opt = validated_input(argc, argv);

  // [3] Generate all puzzles.

   auto puzzles = bpg::Generator::generate(run_opt);

  // [4] Send puzzles to output

   save_puzzles(run_opt, puzzles);

  std::cout << ">>> Job finished!\n\n";

  return EXIT_SUCCESS;
}
