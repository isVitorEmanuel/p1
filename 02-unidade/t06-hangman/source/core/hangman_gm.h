#ifndef _HANGMAN_GM_H_
#define _HANGMAN_GM_H_

#include <unordered_map>
#include <string>

#include "database.h"
#include "dice.h"
#include "hangman_common.h"
#include "hm_word.h"
#include "player.h"

/*!
 * This class represents the Game Controller which keeps track of player,
 * scores, and match total values, as well as determining when a match ends.
 */
class GameController {
public:
  //=== Renderings to hangman.
  std::vector<std::wstring> hangman_screen = {
    {
      L"    ┌──────┐    \n"
      L"    │      │    \n"
      L"    │           \n"   
      L"    │           \n"
      L"    │           \n"
      L"    │           \n"
      L"    │           \n"
      L"  ──┴──         \n"
    },
    {
      L"    ┌──────┐    \n"
      L"    │      │    \n"
      L"    │      O    \n"    
      L"    │           \n"
      L"    │           \n"
      L"    │           \n"
      L"    │           \n"
      L"  ──┴──         \n"
    },
    {
      L"    ┌──────┐    \n"
      L"    │      │    \n"
      L"    │      O    \n"    
      L"    │      |    \n"
      L"    │           \n"
      L"    │           \n"
      L"    │           \n"
      L"  ──┴──         \n"
    },
    {
      L"    ┌──────┐    \n"
      L"    │      │    \n"
      L"    │      O    \n"    
      L"    │     /|    \n"
      L"    │           \n"
      L"    │           \n"
      L"    │           \n"
      L"  ──┴──         \n"
    },
    {
      L"    ┌──────┐    \n"
      L"    │      │    \n"
      L"    │      O    \n"    
      L"    │     /|\\  \n"
      L"    │           \n"
      L"    │           \n"
      L"    │           \n"
      L"  ──┴──         \n"
    },
    {
      L"    ┌──────┐    \n"
      L"    │      │    \n"
      L"    │      O    \n"    
      L"    │     /|\\  \n"
      L"    │     /     \n"
      L"    │           \n"
      L"    │           \n"
      L"  ──┴──         \n"
    },
    {
      L"    ┌──────┐    \n"
      L"    │      │    \n"
      L"    │      O    \n"    
      L"    │     /|\\  \n"
      L"    │     / \\  \n"
      L"    │           \n"
      L"    │           \n"
      L"  ──┴──         \n"
    }
  };
  //=== Struct
  //!< Validate username.
  enum class username_e : short {
    UNDEFINED = 0,
    VALID_NAME,
    INVALID_NAME,
    CONFIRM_USERNAME,
  };

  //!< The game states.
  enum class game_state_e : short {
    STARTING = 0, //!< Beginning the game.
    WELCOME,      //!< Opening messasges.
    MAIN_MENU,    //!< Enter main menu mode, reading option from the player.
    PLAYING,      //!< Playing the game.
    SCORE_MENU,   //!< Enter scoreboard menu, user must choose which table it wants to see.
    SHOW_SCORE,   //!< Show top scores.
    SHOW_RULES,   //!< Asks user if s/he wants to read the rules.
    QUITTING,     //!< User might want to quit (before game finishes), need to
                  //!< confirm.
    ENDING,       //!< Closing the game (final message).
    UNDEFINED,
  };
  
private:
  //=== Structs
  //!< The menu options.
  enum class menu_e : short {
    NO_SET = 0, //!< Default menu.
    PLAY,       //!< Begin new game.
    RULES,      //!< Show rules of the game.
    SCORE,      //!< Show top scores.
    EXIT,       //!< Exit the game.
    UNDEFINED,  //!< No option chosen.
  };

  enum class score_menu_e : short {
      DEFAULT = 0, //!< Nothing selected yet.
      EASY,        //!<- Show easy score.
      MEDIUM,      //!<- Show medium score.
      HARD,        //!<- Show hard score.
      TOTAL,       //!<- Show total score.
      RETURN,      //!<- Return to main menu.
      UNDEFINED,   //!<- Undefined choice.
  };

  //!< The match status.
  enum class match_e : short {
    CONF_DIFF = 1,  //!< Init chosen difficulty.
    INVALID_DIFF,   //!< Informe difficulty is invalid.
    CONF_CAT,       //!< Init chosen category.
    INVALID_CAT,    //!< Informed category is invalid.
    ON,             //!< Match still open and running.
    PLAYER_WON,     //!< Match ended and player WON.
    PLAYER_LOST,    //!< Match ended and player LOST.
    CANCEL,         //!< Match has been canceled.
    UNDEFINED,      //!< Undefined match status.
  };

  //=== Data members
  game_state_e m_game_state;   //!< Current game state.
  username_e m_username_state; //!< Current username state.
  menu_e m_menu_option;        //!< Current menu option.
  score_menu_e m_score_option; //!< Current score menu option.
  match_e m_match_state;       //!< Current match state.
  
  HangmanWord::guess_e m_last_guess_state;
  std::wstring m_system_msg; //!< Current system message displayed to user.
  bool m_asked_to_quit; //!< Flag that indicates whether the user wants to end an ongoing game.
  bool m_match_ended;   //!< Flag that indicates whether the current match has ended or not.
  bool m_reveal_word;   //!< Flag that is active when user looses and we need to show the answer.

  //=== Game related members
  std::vector<std::wstring> m_players;  //!< List of players, indexed by name (must be unique).
  Player *m_curr_player; //!< Reference to the current player.
  std::wstring m_diff;   //!< Current difficulty.
  std::vector<std::wstring> m_categories;  //!< Selected categories.
  std::wstring m_current_cat;  //!< Current category.
  size_t m_current_mistakes;   //!< Current mistakes.
  std::wstring m_word_guess; //!< Latest player guessed word;
  wchar_t m_ch_guess = 0; //!< Latest player guessed letter.
  DataBase m_database; //!<- Database with all words and categories.
  HangmanWord m_secret_word; //!< Keeps track of the masked word, wrong guesses, etc.
  size_t m_max_mistakes; //!< Max number of mistakes allowed in a match.
  std::wstring m_user_name; //!< Stores the user name provided in the Welcome state.

public:
  //=== Public interface
  GameController();
  /// Deleted constructors
  GameController(const GameController &) = delete;
  GameController(GameController &&) = delete;
  GameController &operator=(const GameController &) = delete;
  GameController &operator=(GameController &&) = delete;
  /// Destructor
  ~GameController();

  //=== Common methods for the Game Loop design pattern.
  game_state_e initialize(int argc, char *argv[]);
  /// Renders the game to the user.
  void render() const;
  /// Update the game based on the current game state.
  void update();
  /// Process user input events, depending on the current game state.
  void process_events();
  /// Returns true when the user wants to quit the game.
  bool game_over() const;
  
private:
  // === Auxiliary functions to help user input
  bool is_valid_name(const std::wstring& name);
  std::vector<std::wstring> to_lower_case_vector(
    const std::vector<std::wstring>& input_vector
  );
  std::wstring to_lower_case(const std::wstring& input);
  std::vector<std::wstring> stringcat_t_catgame();
  

  // === These read_xxx() methods are called in process_events()
  /// Reads the user command inside the action screen.
  // std::wstring read_user_command(  ) const;
  /// Read the user name at the beginning of the game.
  std::wstring read_user_name();
  /// Reads the user confirmation, Yes/No.
  bool read_user_confirmation() const;
  /// Reads a simple enter from the user. (aka a pause)
  void read_enter_to_proceed() const;
  /// Read a difficulty.
  std::wstring read_difficulty();
  /// Read category.
  std::wstring read_category();
  /// Reads user guess letter.
  std::wstring read_user_guess();
  /// Reads user menu choice.
  static menu_e read_menu_option();
  /// Reads user score menu choice.
  static score_menu_e read_score_option();

  // === These display_xxx() methods are called in render()
  /// Show select categories.
  std::wstring display_categories() const;
  /// Show the welcome mesage.
  void display_welcome() const;
  /// Show the main menu.
  void display_main_menu() const;
  /// Show main play screen (w/ the hagman)
  void display_play_screen(size_t mistakes) const;
  /// Show screen confirming user quitting a challenge.
  void display_quitting() const;
  /// Show the game rules.
  void display_rules() const;
  /// Show farewell message displayed at the end of the game.
  void display_endgame() const;
  /// Show the top (5?) score board.
  void display_scoreboard() const;
  /// Showv the scoreboard menu.
  void display_score_menu() const;

  // === These show_xxx() methods display common elements to every screen.
  /* All screens may have up to 4 components:
   *  (1) title,                  -> must have
   *  (2) main content,           -> optional
   *  (3) a system message,       -> optional
   *  (4) an interaction message. -> optional
   */
  /// Show screen title.
  void show_screen_title(const std::wstring &) const;
  /// Show game content.
  void show_main_content(const std::wstring &) const;
  /// Show system message to player.
  void show_system_msg(const std::wstring &) const;
  /// Show interactive message to player.
  void show_interaction_msg(const std::wstring &) const;

  /// Evaluates the match situation, whether it's over or if it still on.
  match_e match_status() const;
  int mistakes_to_gallows () const;
  /// Show the gallows with the hangman, whose body displayed depends on the #
  /// of mistakes made (argument).
  void display_gallows(short mistakes) const;
  /// Return the current score.
  long match_score() const;
  /// Reset a new match.
  void reset_match();

};
#endif
