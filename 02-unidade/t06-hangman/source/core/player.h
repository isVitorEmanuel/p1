#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <cstddef>
#include <set>
#include <string>
#include <stdexcept>
#include <utility>
#include <fstream>
#include <iostream>
#include <codecvt>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>
#include <iomanip>

#include "hangman_common.h"

/// Representing a single player.
class Player {
  //=== Private members.
private:
  std::wstring m_name;                   //!< The player's name
  std::set<std::wstring> m_played_words; //!< List of words played in a game.

  int m_easy_score{};                    //!< The player's score on easy challenges.
  int m_medium_score{};                  //!< The player's score on medium challenges.
  int m_hard_score{};                    //!< The player's score on hard challenges.

  size_t m_easy_games_played{};          //!< Number of easy challenges played.
  size_t m_medium_games_played{};        //!< Number of medium challenges played.
  size_t m_hard_games_played{};          //!< Number of hard challenges played.

  size_t m_easy_games_won{};             //!< Number of easy challenges won by the player.
  size_t m_medium_games_won{};           //!< Number of medium challenges won by the player.
  size_t m_hard_games_won{};             //!< Number of hard challenges won by the player.

  inline static const std::string FILE_PATH = "../core/set/players.bin"; //!< Path to players.bin
  //=== Public interface
public:
  /// Default Ctro.
  Player(std::wstring n = L"no_name") : m_name{std::move(n)} { /*empty*/ }
  /// Dtro
  ~Player() = default;
  /// Returns the player's name
  [[nodiscard]] std::wstring name() const;
  ///  Sets player name.
  void name(const std::wstring &);
  /// Returns the player's accumulated score.
  [[nodiscard]] int total_score() const;
  /// Add the score from one challenge.
  void add_score(int quantity, const std::wstring& diff);
  /// Increments number of wins in one specified difficulty.
  void add_win(const std::wstring& diff);
  /// Increments number of played games in one specified difficulty.
  void add_new_game (const std::wstring& diff);
  /// Returns the player score on one specified difficulty.
  [[nodiscard]] int get_score_by_diff (const std::wstring &diff) const;
  /// Returns the number of wins on one specified difficulty.
  [[nodiscard]] size_t get_wins_by_diff (const std::wstring &diff) const;
  /// Returns the number of loses on one specified difficulty.
  [[nodiscard]] size_t get_loses_by_diff (const std::wstring &diff) const;
  /// Returns the number of games played on one specified difficulty.
  [[nodiscard]] size_t get_number_of_games (const std::wstring &diff) const;
  /// Add a word to the list of played words.
  void add_word(const std::wstring &);
  /// Check if this word has been played before.
  bool has_played(const std::wstring &) const;
  /// Clear the word list.
  void clear_word_list();
  /// Returns total number of games played.
  [[nodiscard]] size_t get_total_games() const;
  /// Returns total number of games won by the player.
  [[nodiscard]] size_t get_total_wins() const;
  /// Returns total number of games lost by the player.
  [[nodiscard]] size_t get_total_losses() const;

  /// Returns all score-related data in a single line, with comma-separated values.
  [[nodiscard]] std::wstring to_csv_line() const;
  /*!
   * Stablishes a way to get data stored at players.bin, a binary file which stores
   * scoreboard related content, each line representing a player.
   * @param name Name of the player, the first value stored at each line of the file.
   * @param i_begin Begin of the range of returned values, inclusive.
   * @param i_end End of the range of the returned values, inclusive.
   * @return A container with contents from the indicated range
   */
  static std::vector<std::wstring> get_scoreboard_info(const std::wstring& name, size_t i_begin, size_t i_end);

  /*!
   * Updates the entire players.bin file, changing the line of the player, if it is already registered
   * or creating a new line at the end, if it's a new player.
   * @param name Name of the player.
   */
  void update_scoreboard_info(const std::wstring& name);

  /// Recovers from the file the previous score
  void get_previous_score(const std::wstring& name);

  /// Recovers a vector with all players names in the players.bin file
  static std::vector<std::wstring> get_all_names();

  /*!
   * Prints a table with a list of players in decreasing order by score
   * @param option Defines the score that will be presented: easy, medium, hard or total score.
   */
  static void print_score(const int& option);

  /// Comparison function. Compares player easy score, with number of wins on easy games as tiebreaker.
  static bool comp_by_easy_score(const Player &p1, const Player &p2);
  /// Comparison function. Compares player medium score, with number of wins on medium games as tiebreaker.
  static bool comp_by_medium_score(const Player &p1, const Player &p2);
  /// Comparison function. Compares player hard score, with number of wins on hard games as tiebreaker.
  static bool comp_by_hard_score(const Player &p1, const Player &p2);
  /// Comparison function. Compares player total score, with number of wins as tiebreaker.
  static bool comp_by_total_score(const Player &p1, const Player &p2);
};
#endif
