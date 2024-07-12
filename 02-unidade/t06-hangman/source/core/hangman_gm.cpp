/*!
 * Game Controller implementation.
 *
 * \author Selan
 * \date March 23rd, 2024
 * \file hangman_gm.cpp
 */
#include "../utils/text_color.h"
#include "hangman_gm.h"
#include "hm_word.h"
#include "player.h"

#include <cmath>
#include <limits> 

// === Public interface
/// Default Constructor
GameController::GameController()
    : m_game_state(game_state_e::UNDEFINED),
    m_username_state(username_e::UNDEFINED),
    m_menu_option(menu_e::NO_SET),
    m_score_option(score_menu_e::DEFAULT),
    m_match_state(match_e::UNDEFINED),
    m_last_guess_state(HangmanWord::guess_e::UNDEFINED),
    m_asked_to_quit(false),
    m_match_ended(false),
    m_reveal_word(false), 
    m_curr_player(nullptr),
    m_diff(L""),
    m_categories(),
    m_current_cat(L""),
    m_current_mistakes(0),
    m_word_guess(L""),
    m_ch_guess(0),
    m_database(),
    m_secret_word(L"", L"", L'_'),
    m_max_mistakes(0) {
}

/// Default Destructor
GameController::~GameController() = default;

// === Auxiliary functions to help user input

/*!
 * Converts wstring to lowercase.
 *
 * @param input Initial string.
 *
 * @return A wstring converted to lowercase.
 * 
 */
std::wstring GameController::to_lower_case(const std::wstring& input) {
  std::wstring result;

  for (wchar_t c : input) {
    result += towlower(c);
  }

  return result;
}

/*!
 * Converts all strings in a vector to lowercase.
 *
 * @param input_vector Initial vector.
 *
 * @return Vector with words converted to lowercase.
 * 
 */
std::vector<std::wstring> GameController::to_lower_case_vector(const std::vector<std::wstring>& input_vector) {
  std::vector<std::wstring> result_vector;

  for (const auto& str : input_vector) {
    result_vector.push_back(to_lower_case(str));
  }

  return result_vector;
}

/*!
 * Classify a name as valid or invalid.
 *
 * @param name String for the title.
 *
 * @return Return true if valid, or false if invalid.
 * 
 */
bool GameController::is_valid_name(const std::wstring& name) {
  for (wchar_t ch : name) {
    if (!iswalpha(ch) && !iswdigit(ch) && ch != L'_') {
      return false;
    }
  }
  return true;
}

/*!
 * Converts a string of categories into a game category string.
 * 
 * @return The string of categories.
 */
std::vector<std::wstring> GameController::stringcat_t_catgame() {
  std::vector<std::wstring> cats;
  if(m_categories.empty()) {  
    cats = {
      L"animais", L"comidas", L"cores", L"estados do brasil", 
      L"filmes", L"países", L"profissões", L"séries de tv/novelas", 
      L"signos do zodíaco"
    };
  } else {
    cats = m_categories;
    cats = to_lower_case_vector(cats);
  }
  return cats;
}

/*!
 * Check difficulty game and results, and return score.
 * 
 * @return Score in the match.
 */
long GameController::match_score() const {
  long score; //!< Score in the match.

  if(m_diff == L"easy") {
    m_match_state == match_e::PLAYER_WON ? score = 1 : score = -2;
  }
  
  if(m_diff == L"medium") {
    m_match_state == match_e::PLAYER_WON ? score = 2 : score = -2;
  }

  if(m_diff == L"hard") {
    m_match_state == match_e::PLAYER_WON ? score = 4 : score = -3;
  } 
  return score;
}

// === These read_xxx() methods are called in process_events()  
/*!
 * Read a <Enter> to continue.
 * 
 */
void GameController::read_enter_to_proceed() const {
  /// Clear buff.
  std::cin.clear(); 
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

  std::wstring line;
  std::getline(std::wcin, line);
}

/*!
 * Read a confirmation (Y/N).
 *
 * @return Return if the user confirm or no.
 * 
 */
bool GameController::read_user_confirmation() const{
  std :: wstring confirmation;
  getline(std :: wcin, confirmation);

  return (confirmation == L"Y" or confirmation == L"y");
};

/*!
 * Read a username from user.
 *
 * @return Return the username.
 * 
 */
std::wstring GameController::read_user_name() {
  std::wstring user_name;
  std::getline(std::wcin, user_name);

  return user_name;
}

/*!
 * Read a option from user.
 *
 * @return Option chosen by the user.
 * 
 */
GameController::menu_e GameController::read_menu_option() {
  int user_menu_option;
  std::wcin >> user_menu_option;

  std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
  
  switch(user_menu_option){
    case 1: 
      return GameController::menu_e::PLAY;
    case 2: 
      return GameController::menu_e::RULES;
    case 3: 
      return GameController::menu_e::SCORE;
    case 4: 
      return GameController::menu_e::EXIT;
    default: 
      return GameController::menu_e::UNDEFINED; 
  }
}

/*!
 * Reads an option from user in the scoreboard menu.
 * @return Chosen option.
 */
GameController::score_menu_e GameController::read_score_option() {
    int user_menu_option;
    std::wcin >> user_menu_option;

    std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch(user_menu_option){
        case 1:
            return GameController::score_menu_e::EASY;
        case 2:
            return GameController::score_menu_e::MEDIUM;
        case 3:
            return GameController::score_menu_e::HARD;
        case 4:
            return GameController::score_menu_e::TOTAL;
        case 5:
            return GameController::score_menu_e::RETURN;
        default:
            return GameController::score_menu_e::UNDEFINED;
    }
}

/*!
 * Read difficulty.
 *
 * @return Selected difficulty.
 * 
 */
std::wstring GameController::read_difficulty() {
  int user_menu_option;
  std::wcin >> user_menu_option;

  std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
  
  switch(user_menu_option){
    case 1: 
      return L"easy";
    case 2: 
      return L"medium";
    case 3: 
      return L"hard";
    default: 
      return L""; 
  }
}

/*!
 * Read the category.
 *
 * @return Selected category.
 * 
 */
std::wstring GameController::read_category() {
  int user_menu_option;
  std::wcin >> user_menu_option;

  std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

  switch(user_menu_option){
    case 1: 
      return L"Animais";
    case 2: 
      return L"Comidas";
    case 3: 
      return L"Cores";
    case 4: 
      return L"Estados do Brasil";
    case 5: 
      return L"Filmes";
    case 6: 
      return L"Países";
    case 7: 
      return L"Profissões";
    case 8: 
      return L"Séries de TV/Novelas";
    case 9: 
      return L"Signos do Zodíaco";
    case 0:
      return L"finish";
    default: 
      return L""; 
  }
}

/*!
 * Read user guess.
 *
 * @return User guess.
 * 
 */
std::wstring GameController::read_user_guess() {
  std::wcin.clear();
  std::wstring input;
  std::getline(std::wcin, input);

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  return input;
}

/*!
 * Check if the game is over.
 *
 * @return Indicate whether the game is over or not.
 * 
 */
bool GameController::game_over() const {
  return m_game_state == game_state_e::ENDING;
}

/*!
 * Set a game state.
 *
 * @return The current state of the game.
 */
GameController::match_e GameController::match_status() const {
  if (m_secret_word.wrong_guesses() >= m_max_mistakes) {
    return match_e::PLAYER_LOST;
  }
  else if (m_secret_word.correct_guesses() == m_secret_word.masked_str().size()) {
    return match_e::PLAYER_WON;
  }
  else {
    return match_e::ON;
  }
}

/*!
 * Reset all data of match.
 *
 */
void GameController::reset_match() {
  m_match_state = match_e::UNDEFINED;

  m_system_msg = L"";

  m_asked_to_quit = false;
  m_match_ended = false;

  m_diff = L"";
  m_categories.clear();
  m_current_cat = L"";
  m_max_mistakes = 0;
  m_current_mistakes = 0;
  m_word_guess = L"";
  m_ch_guess = 0;
  m_last_guess_state = HangmanWord::guess_e::UNDEFINED;

  m_secret_word.reset();
}


// === These show_xxx() methods display common elements to every screen.
/*!
 * Set a title for the screen.
 *
 * @param title String for the title.
 *
 */
void GameController::show_screen_title(const std::wstring &title) const {
  std::wcout << L"=-------[ " << title << L" ]-------=" << std::endl;
}

/*!
 * Set a content for the screen.
 *
 * @param content String for the content of game.
 *
 */
void GameController::show_main_content(const std::wstring &content) const {
  std::wcout << std::endl << content << std::endl;
}

/*!
 * Set a system message for the screen.
 *
 * @param msg String for the system message.
 *
 */
void GameController::show_system_msg(const std::wstring &msg) const {
  if(m_match_state == match_e::PLAYER_WON) {
    std::wcout << Color::wtcolor(L"MSG: [" + msg + L"]", Color::GREEN) << std::endl;
    return;
  }
  std::wcout << Color::wtcolor(L"MSG: [" + msg + L"]", Color::RED) << std::endl;
}
/*!
 * Set a interaction message for the screen.
 *
 * @param msg String for the interaction message of game.
 *
 */
void GameController::show_interaction_msg(const std::wstring &msg) const {
  if((m_match_state == match_e::PLAYER_LOST || m_match_state == match_e::PLAYER_WON) 
                                           && m_game_state == game_state_e::PLAYING) {
    std::wcout << Color::wtcolor(msg + L" > ", Color::GREEN);
    return;
  }
  std::wcout << msg << L" > ";
}

// === These display_xxx() methods are called in render()

/*!
 * Convert the number of mistakes in render gallows.
 *
 * @return The number of the gallows corresponding to the number of errors.
 * 
 */
int GameController::mistakes_to_gallows() const {
  if (m_diff == L"easy") {
    return static_cast<int>(std::round(m_current_mistakes * 0.6));
  } else if (m_diff == L"medium") {
    return static_cast<int>(std::round(m_current_mistakes * 0.75));
  } else if (m_diff == L"hard") {
    return m_current_mistakes;
  } else {
    return 0; 
  }
}

/*!
 * Set a display welcome.
 *
 * @param mistakes Number of curretly mistakes.
 * 
 */
void GameController::display_gallows(short mistakes) const{
  std::wcout << hangman_screen[mistakes];
}

/*!
 * Create a wstring with all select categories.
 *
 * @return A formated wstring with categories.
 */
std::wstring GameController::display_categories() const {
  if (m_categories.empty()) {
    return L"Default";
  }

  std::wstring result; /// All formated categories.

  /// Set and formated categories.
  for (size_t i = 0; i < m_categories.size(); ++i) {
    result += m_categories[i];
    if (i != m_categories.size() - 1) {
      result += L", ";
    }
  }
  return result;
}

/*!
 * Set a display welcome.
 *
 */
void GameController::display_welcome() const {
  std::system("clear");
  show_screen_title(L"Welcome");

  /// Display main content of this state.
  std::wcout << std::endl << L"---> Welcome to Hangman, v 1.0 <---" << std::endl;
  std::wcout << L"       -copyright UFRN 2024-" << std::endl << std::endl;

  /// Display the system and interacition message this state.
  if(m_username_state == username_e::INVALID_NAME) {
    show_system_msg(L"Invalid name! Please try again");
    show_interaction_msg(L"Please, enter your name [number, digits or '_']");
  } else if(m_username_state == username_e::CONFIRM_USERNAME) {
    show_system_msg(L"The user << " + m_user_name + L" >> is already in use" );
    show_interaction_msg(L"Do you confirm that this is the player? [y/N]");
  } else {
    show_interaction_msg(L"Please, enter your name [number, digits or '_']");
  }
}

/*!
 * Set a display menu.
 *
 */
void GameController::display_main_menu() const {
  std::system("clear");
  show_screen_title(L"Main Menu");

  /// Display main content of this state.
  std::wcout << std::endl << L"Please choose an option:\n" << std::endl;
  std::wcout << L"1 - Start a new challenge." << std::endl;
  std::wcout << L"2 - Show the game rules." << std::endl;
  std::wcout << L"3 - Show scoreboard." << std::endl;
  std::wcout << L"4 - Quit the game." << std::endl << std::endl;

  if(m_match_state == match_e::CANCEL) {
    show_system_msg(L"The score of the challenge you quitted was discarded.");
  }
  /// Display the system message.
  if(m_menu_option == menu_e::UNDEFINED) {
    show_system_msg(L"Sorry, invalid option! Try again.");
  }

  show_interaction_msg(L"Enter your option number and hit \"Enter\"");
}

/*!
 * Set a display on the playing game.
 * 
 * @param mistakes Number of currently mistakes in the match.
 */
void GameController::display_play_screen(size_t mistakes) const {
  std::system("clear");
  show_screen_title(L"Hangman Challenge");
  
  if(m_match_state == match_e::CONF_DIFF || m_match_state == match_e::INVALID_DIFF) {
    /// Display the main content from this state.
    std::wcout << std::endl << L"Chosen a difficulty game: " << std::endl;
    std::wcout << L"1 - Easy." << std::endl;
    std::wcout << L"2 - Medium." << std::endl;
    std::wcout << L"3 - Hard." << std::endl << std::endl;

    /// Display the system message from this state.
    if(m_match_state == match_e::INVALID_DIFF) {
      show_system_msg(L"Invalid difficulty.");
    }
    
    show_interaction_msg(L"Digit the number");
  } else if(m_match_state == match_e::CONF_CAT || m_match_state == match_e::INVALID_CAT) {
    /// Display the main content from this state.
    std::wcout << std::endl << L"Categories: " << display_categories() << std::endl; 
    std::wcout << std::endl << L"Chosen categories of the match: " << std::endl;
    std::wcout << L"1 - Animais." << std::endl;
    std::wcout << L"2 - Comidas." << std::endl;
    std::wcout << L"3 - Cores." << std::endl;
    std::wcout << L"4 - Estados do Brasil." << std::endl;
    std::wcout << L"5 - Filmes." << std::endl;
    std::wcout << L"6 - Países." << std::endl;
    std::wcout << L"7 - Profissões." << std::endl;
    std::wcout << L"8 - Séries de TV/Novelas." << std::endl;
    std::wcout << L"9 - Signos do Zodíaco." << std::endl;
    std::wcout << L"0 - Finalize choice." << std::endl << std::endl;

    /// Display a system message.
    if(m_match_state == match_e::INVALID_CAT) {
      show_system_msg(L"Invalid Category!");
    }

    show_interaction_msg(L"Digit the number");
  } else {
    /// Display categories in the start of game.
    if(m_secret_word.correct_guesses() - m_secret_word.n_open_letters() == 0 && 
       m_secret_word.wrong_guesses() == 0 && mistakes == 0) {
      std::wcout <<  L"Categories: " << display_categories() << std::endl;
    }
    std::wcout << std::endl;

    /// Display gallows.
    if(mistakes >= m_max_mistakes) { display_gallows(6); } 
    else { display_gallows(mistakes_to_gallows()); }
    std::cout << std::endl;

    /// Display masked_word.
    if(m_match_state == match_e::PLAYER_LOST) {
      /// Set auxiliary wstrings.  
      const std::wstring& actual_word = m_secret_word();
      const std::wstring& masked_str = m_secret_word.masked_str();

      /// Display a masked word with color.
      for (size_t i = 0; i < masked_str.size(); ++i) {
        wchar_t mask = masked_str[i];
        if (mask == L'_') {
          // Print the actual letter in green and underlined
          std::wcout << Color::wtcolor(std::wstring(1, actual_word[i]), Color::GREEN, Color::UNDERLINE) << L" ";
        } else {
          std::wcout << mask << L" ";
        }
      }
    } else if(m_match_state == match_e::ON) {
      /// Display common masked word.
      for (const wchar_t& mask : m_secret_word.masked_str()) {
        std::wcout << mask << " ";
      }
    } else {
      /// Display secret_word.
      for (const wchar_t& mask : m_secret_word()) {
        std::wcout << mask << " ";
      }
    }

    std::vector<wchar_t> wrong_guesses = m_secret_word.wrong_guesses_list(); /// Set auxiliary vector with wrong guesses.

    /// Display wrong guesses.
    std::wcout << std::endl << std::endl << "Wrong guesses so far: < ";
    for(const auto& letter : wrong_guesses) {
      std::wcout << letter << " ";
    }
    std::wcout << ">" << std::endl << std::endl;

    /// Display system and interaction message.
    if(m_match_state == match_e::PLAYER_LOST) {
      show_system_msg(L"Wrong guess. Sorry but you LOST the challange.");
      show_interaction_msg(L"Press \"Enter\" to continue");
      return;
    } else if(m_match_state == match_e::PLAYER_WON) {
      std::wstring str_score = std::to_wstring(match_score());
      show_system_msg(L"Correct guess. Congrats! You WON the challenge with score = " + str_score + L'.');
      show_interaction_msg(L"Press \"Enter\" to continue");
      return;
    } else if(m_last_guess_state == HangmanWord::guess_e::WRONG) {
      show_system_msg(L"Wrong guess.");
    } else if(m_last_guess_state == HangmanWord::guess_e::REPEATED) {
      if(!(m_secret_word.correct_guesses() == 0 && m_secret_word.wrong_guesses() == 1 && mistakes == 0)){
        show_system_msg(L"Repetead.");
      }
    }
    show_interaction_msg(L"Guess a letter [enter '#' to quit]");
  } 
}

/*!
 * Set a display quitting.
 *
 */
void GameController::display_quitting() const {
  std::system("clear");
  show_screen_title(L"Attention");
  show_interaction_msg(L"\nDo you really want to quit the challenge? [y/N]");
}

void GameController::display_rules() const {
  std::system("clear");
  show_screen_title(L"Gameplay");

  /// Display the main content this state
  std::wcout << std::endl << L"Hi \"" << m_user_name << L"\" , here are the game rules:" << std::endl;;
  std::wcout << L"[1] You need to guess the secret word or phrase the game has chosen" << std::endl;
  std::wcout << L"    by suggesting letters." << std::endl;
  std::wcout << L"[2] We will display a row of dashes, representing each letter of the" << std::endl;
  std::wcout << L"    the secret word/phrase you're trying to guess." << std::endl;
  std::wcout << L"[3] Each correct guess earns you 1 point." << std::endl;
  std::wcout << L"[4] Each wrong guess you loose 1 point and I draw on component of a" << std::endl;
  std::wcout << L"    hanged stick figure (the hangman!)" << std::endl;
  std::wcout << L"[5] If you wrong guess 6 times you loose the challenge" << std::endl;
  std::wcout << L"[6] If you can guess the secret word/phrase before the hangman is" << std::endl;
  std::wcout << L"    complete you add 2 extra points to your overall score." << std::endl;
  std::wcout << L"[7] After a guessing round (challenge) is complete you may try another\n" << 
                L"    secret word/phrase or quit the game." << std::endl;

  show_interaction_msg(L"\nPress \"Enter\" to continue");
}

/*!
 * Set a goodbye display.
 *
 */
void GameController::display_endgame() const {
  std::system("clear");
  show_screen_title(L"Farewell");

  /// Display the main content this state.
  std::wcout << L"\nThanks for playing. See you next time!" << std::endl;
}

/*!
 * Set a scoreboard display.
 *
 */
void GameController::display_scoreboard() const {
  std::system("clear");
  std::wstring title;
  std::wstring score_info;
  int opt = 0;
  if (m_score_option == score_menu_e::EASY){
      title = L"Easy Scoreboard";
      opt = 1;
      score_info = L"In easy matches, players earn +1 points per win and -2 points on fails.";
  }
  else if (m_score_option == score_menu_e::MEDIUM){
      title = L"Medium Scoreboard";
      opt = 2;
      score_info = L"In medium matches, players earn +2 points per win and -2 points on fails.";
  }
  else if (m_score_option == score_menu_e::HARD){
      title = L"Hard Scoreboard";
      opt = 3;
      score_info = L"In hard matches, players earn +4 points per win and -3 points on fails.";
  }
  else if (m_score_option == score_menu_e::TOTAL){
      title = L"Total Scoreboard";
      opt = 4;
  }

  std::system("clear");
  show_screen_title(title);
  Player::print_score(opt);

  if (opt == 1 or opt == 2 or opt == 3)
    std::wcout << Color::wtcolor(L"\nNote: " + score_info, Color::YELLOW);
  show_interaction_msg(L"\nPress \"Enter\" to continue");
}

void GameController::display_score_menu() const {
    std::system("clear");
    show_screen_title(L"Scoreboard View");

    std::wcout << std::endl << L"Please choose an option:\n" << std::endl;
    std::wcout << L"1 - EASY difficulty scoreboard." << std::endl;
    std::wcout << L"2 - MEDIUM difficulty scoreboard." << std::endl;
    std::wcout << L"3 - HARD difficulty scoreboard." << std::endl;
    std::wcout << L"4 - TOTAL scoreboard - overall player performance." << std::endl << std::endl;
    std::wcout << L"5 - Return to main menu." << std::endl << std::endl;

    show_interaction_msg(L"\nChoose an option to continue");
}

// === Common methods for the Game Loop design pattern.
/*!
 * Initialize the game by changing its state.
 *
 * @param argc Number of command line arguments
 * @param argv Command line arguments
 *
 * @return Game state as STARTING
 *
 */
GameController::game_state_e GameController::initialize(int argc, char *argv[]) {
  m_game_state = game_state_e::STARTING;

    /// Create a database.
  DataBase init_database;
  m_database = init_database;
  m_database.set_m_words_category();

  /// Fills the list of names of player who already played the game before.
  m_players = Player::get_all_names();

  return m_game_state;
}

/*!
 * Process all events during the game.
 *
 */
void GameController::process_events() {
  if(m_game_state == game_state_e::STARTING) {
    /// Do nothing.
  } else if(m_game_state == game_state_e::WELCOME) {
    /// Check state o username.
    if(m_username_state == username_e::CONFIRM_USERNAME) {
      m_asked_to_quit = read_user_confirmation();
    } else {
      m_user_name = read_user_name();
    }
  } else if(m_game_state == game_state_e::MAIN_MENU) {
    m_menu_option = read_menu_option();
  } else if(m_game_state == game_state_e::PLAYING) {
      if(m_match_state == match_e::CONF_DIFF || m_match_state == match_e::INVALID_DIFF) {
        m_diff = read_difficulty();
      } else if(m_match_state == match_e::CONF_CAT || m_match_state == match_e::INVALID_CAT) {
        m_current_cat = read_category();
      } else if(m_match_state == match_e::ON) {
        m_word_guess = to_lower_case(read_user_guess());
      } else if(m_match_ended) {
        read_enter_to_proceed();
      }
  } else if(m_game_state == game_state_e::SHOW_SCORE) {
      read_enter_to_proceed();
  } else if (m_game_state == game_state_e::SCORE_MENU) {
      m_score_option = read_score_option();
  } else if(m_game_state == game_state_e::SHOW_RULES) { 
    read_enter_to_proceed();
  } else if(m_game_state == game_state_e::QUITTING) {
    m_asked_to_quit = read_user_confirmation();
  } else if(m_game_state == game_state_e::ENDING) {
    /// Do nothing.
  } else {
    throw std::runtime_error("Sorry! Unfortunately, there was a problem with the game state!");
  }
}

/*!
 * Update all states of the GameController during the game.
 *
 */
void GameController::update() {
  if(m_game_state == game_state_e::STARTING) { 
    /// Update game state to WELCOME
    m_game_state = game_state_e::WELCOME;
  } else if(m_game_state == game_state_e::WELCOME) {

    /// Start by checking if the name is valid.
    if(is_valid_name(m_user_name)) {
      auto it = std::find(m_players.begin(), m_players.end(), m_user_name); /// Check if the user name already exist.

      if(it != m_players.end()) {

        /// Check the status of the username.
        if(m_username_state == username_e::INVALID_NAME || m_username_state == username_e::UNDEFINED) {
          m_username_state = username_e::CONFIRM_USERNAME;
        } else if(m_username_state == username_e::CONFIRM_USERNAME) {

          /// Check the user confirmation.
          if(m_asked_to_quit) {

            /// In this case, the user confirms that they have this username.
            m_curr_player = new Player(m_user_name); //!<- Set user.
            m_curr_player->name(m_user_name); //!<- Set user name.
            m_curr_player->get_previous_score(m_user_name);

            /// Set gamestate.
            m_username_state = username_e::VALID_NAME;
            m_game_state = game_state_e::MAIN_MENU;
          } else {
            
            /// In this case, the user does not confirm that they have this username.
            m_username_state = username_e::UNDEFINED;
          }
        }
      } else {

        /// Create new user and set game states.
        m_players.emplace_back(m_user_name);
        m_curr_player = new Player(m_user_name);
        m_username_state = username_e::VALID_NAME;
        m_game_state = game_state_e::MAIN_MENU;
      }
    } else {

      /// This case the user digit a invalid name.
      m_username_state = username_e::INVALID_NAME;
    }
  } else if(m_game_state == game_state_e::MAIN_MENU) {
    reset_match();
    /// Check the chosen option and change the game state based on it.
    if(m_menu_option == menu_e::PLAY) {
      m_game_state = game_state_e::PLAYING;
      m_match_state = match_e::CONF_DIFF;
    } else if(m_menu_option == menu_e::RULES) {
      m_game_state = game_state_e::SHOW_RULES;
    } else if(m_menu_option == menu_e::SCORE) {
      m_game_state = game_state_e::SCORE_MENU;
    } else if(m_menu_option == menu_e::EXIT) {
      m_game_state = game_state_e::QUITTING;
    } else if(m_menu_option == menu_e::UNDEFINED) {
      m_game_state = game_state_e::MAIN_MENU;
    }
  } else if(m_game_state == game_state_e::PLAYING) {

    /// Set difficulty game and set max mistakes.
    if(m_match_state == match_e::CONF_DIFF || m_match_state == match_e::INVALID_DIFF) {
      
      /// Check if informed difficulty is valid.
      m_match_state = m_diff == L""? match_e::INVALID_DIFF : match_e::CONF_CAT;

      /// Set number max of mistakes.
      if(m_diff == L"easy") { m_max_mistakes = 10; }
      if(m_diff == L"medium") { m_max_mistakes = 8; }
      if(m_diff == L"hard") { m_max_mistakes = 6; }

    /// Set all categories of the match.
    } else if(m_match_state == match_e::CONF_CAT || m_match_state == match_e::INVALID_CAT) {

      /// If the user informed a invalid category, set a game state to INVALID_CAT.
      if(m_current_cat == L"") {
        m_match_state = match_e::INVALID_CAT;

      /// If the user finish chosen categories, set a secret_word.
      } else if (m_current_cat == L"finish") {
        std::wstring valid_word; //!<- Valid word that will be used
        m_match_state = match_e::ON;

        /// Get the possible words.
        m_database.set_m_upper_bound(m_diff);
        m_database.set_m_play_words(stringcat_t_catgame());
        m_database.set_m_diff_words();

        ///  Set a word.
        if (m_diff == L"easy") { 

          std::wstring test_word = L""; ///!<- Candidate word to be valid.
          
          do {
            test_word = m_database.select_word(prob_easy_easy, prob_easy_medi, prob_easy_hard); /// Get a random possible word using easy probs.
          } while (m_curr_player->has_played(test_word)); /// Check if the user has played this word.
          
          /// Set a valid word.
          valid_word = test_word;
        } else if (m_diff == L"medium") {

          std::wstring test_word = L""; ///!<- Candidate word to be valid.
          
          do {
            test_word = m_database.select_word(prob_medi_easy, prob_medi_medi, prob_hard_hard); /// Get a random possible word using medium probs.
          } while (m_curr_player->has_played(test_word)); /// Check if the user has played this word.
          
          /// Set a valid word.
          valid_word = test_word;
        } else {
          
          std::wstring test_word = L""; ///!<- Candidate word to be valid.

          do {
           test_word = m_database.select_word(prob_hard_easy, prob_hard_medi, prob_hard_hard); /// Get a random possible word using hard probs.
          } while (m_curr_player->has_played(test_word)); /// Check if the user has played this word.
          
          /// Set a valid word.
          valid_word = test_word;
        }

        /// Initlize a object secret word with valid_word.
        m_secret_word.initialize(valid_word, m_diff);
      } else {
        m_match_state = match_e::CONF_CAT;
        m_categories.push_back(m_current_cat);
      }
    } else if(m_match_state == match_e::ON) {

      /// Checks if the user is quitting the game.
      if(m_word_guess == L"#") {
        m_game_state = game_state_e::QUITTING;
        return;
      }

      /// Check if user guess a word.
      if(m_word_guess.size() != 1) {
        if(m_diff == L"easy") {
          m_word_guess = m_secret_word.normalize(m_word_guess);
          if(m_word_guess == m_secret_word.normalize(m_secret_word())) {
            m_match_ended = true;
            m_match_state = match_e::PLAYER_WON;
            m_curr_player->add_word(m_secret_word()); //<- Add the word to the user's guessed words list.
            m_curr_player->add_win(m_diff);
            m_curr_player->add_score(match_score(), m_diff);
            m_curr_player->add_new_game(m_diff);
            m_curr_player->update_scoreboard_info(m_user_name);
          } else { 
            /// If the user did not guess correctly, update the data and change the guess state to WRONG.
            m_last_guess_state = HangmanWord::guess_e::WRONG;
            m_current_mistakes += 2;

            /// Check if the user has reached the maximum number of errors.
            if(m_current_mistakes >= m_max_mistakes) {
              m_match_ended = true;
              m_match_state = match_e::PLAYER_LOST;
              m_curr_player->add_word(m_secret_word()); //<- Add the word to the user's guessed words list.
              m_curr_player->add_score(match_score(), m_diff);
              m_curr_player->add_new_game(m_diff);
              m_curr_player->update_scoreboard_info(m_user_name);
            }
          }
        } else {
        /// If the user guessed correctly, add, change the states to PLAYER_WON, and update the data.
          if(m_word_guess == m_secret_word()) {
            m_match_ended = true;
            m_match_state = match_e::PLAYER_WON;
            m_curr_player->add_word(m_secret_word()); //<- Add the word to the user's guessed words list.
            m_curr_player->add_win(m_diff);
            m_curr_player->add_score(match_score(), m_diff);
            m_curr_player->add_new_game(m_diff);
            m_curr_player->update_scoreboard_info(m_user_name);
          } else { 
            /// If the user did not guess correctly, update the data and change the guess state to WRONG.
            m_last_guess_state = HangmanWord::guess_e::WRONG;
            m_current_mistakes += 2;

            /// Check if the user has reached the maximum number of errors.
            if(m_current_mistakes >= m_max_mistakes) {
              m_match_ended = true;
              m_match_state = match_e::PLAYER_LOST;
              m_curr_player->add_word(m_secret_word()); //<- Add the word to the user's guessed words list.
              m_curr_player->add_score(match_score(), m_diff);
              m_curr_player->add_new_game(m_diff);
              m_curr_player->update_scoreboard_info(m_user_name);
            }
          }
        }
      } else {
        m_ch_guess = m_word_guess[0];          

        m_last_guess_state = m_secret_word.guess(m_ch_guess, m_diff); ///!<- State of the user guess.

        if (m_last_guess_state == HangmanWord::guess_e::WRONG) {
          ++m_current_mistakes;
          m_match_state =  match_status(); ///!<- State of the match.

          /// If the user lost, end the game.
          if(m_match_state == match_e::PLAYER_LOST) {
            m_match_ended = true;
            m_curr_player->add_word(m_secret_word()); //<- Add the word to the user's guessed words list.
            m_curr_player->add_score(match_score(), m_diff);
            m_curr_player->add_new_game(m_diff);
            m_curr_player->update_scoreboard_info(m_user_name);
          } 

          if(m_current_mistakes >= m_max_mistakes) {
            m_match_ended = true;
            m_match_state = match_e::PLAYER_LOST;
            m_curr_player->add_word(m_secret_word()); //<- Add the word to the user's guessed words list.
            m_curr_player->add_score(match_score(), m_diff);
            m_curr_player->add_new_game(m_diff);
            m_curr_player->update_scoreboard_info(m_user_name);
          }
        } else if(m_last_guess_state == HangmanWord::guess_e::CORRECT) {
          m_match_state = match_status();  ///!<- State of the match.

          /// If the use won, end the game.
          if(m_match_state == match_e::PLAYER_WON) {
            m_match_ended = true;
            m_curr_player->add_word(m_secret_word()); //<- Add the word to the user's guessed words list.
            m_curr_player->add_win(m_diff);
            m_curr_player->add_score(match_score(), m_diff);
            m_curr_player->add_new_game(m_diff);
            m_curr_player->update_scoreboard_info(m_user_name);
          } 
        }
      } 
    } else {
      /// Add word to played 
      m_game_state = game_state_e::MAIN_MENU;
    }
  } else if(m_game_state == game_state_e::SHOW_SCORE) {
      /// Update game state to MAIN_MENU.
      m_game_state = game_state_e::MAIN_MENU;
  } else if (m_game_state == game_state_e::SCORE_MENU) {
      if (m_score_option == score_menu_e::EASY or
      m_score_option == score_menu_e::MEDIUM or
      m_score_option == score_menu_e::HARD or
      m_score_option == score_menu_e::TOTAL)
          m_game_state = game_state_e::SHOW_SCORE;
      if (m_score_option == score_menu_e::RETURN or m_score_option == score_menu_e::UNDEFINED)
          m_game_state = game_state_e::MAIN_MENU;
  } else if(m_game_state == game_state_e::SHOW_RULES) {
    /// Update game state to MAIN_MENU.
    m_game_state = game_state_e::MAIN_MENU;
  } else if(m_game_state == game_state_e::QUITTING) {

    /// Check asked in match.
    if(m_match_state == match_e::ON) {

      /// Check user confirm.
      if(m_asked_to_quit) {

        /// Return to main menu and cancel game.
        m_game_state = game_state_e::MAIN_MENU;
        m_match_state = match_e::CANCEL;
      } else {

        /// Continue game.
        m_game_state = game_state_e::PLAYING;
        m_last_guess_state = HangmanWord::guess_e::UNDEFINED;
      }
    } else {
      m_asked_to_quit ? m_game_state = game_state_e::ENDING : m_game_state = game_state_e::MAIN_MENU;
    }
  } else if(m_game_state == game_state_e::ENDING) {
    /// Do nothing.
  } else if(m_game_state == game_state_e::UNDEFINED) {
    throw std::runtime_error("Sorry! Unfortunately, there was a problem with the game state!");
  } 
}

/*!
 * Display all messages during game.  
 *
 */
void GameController::render() const {
  if(m_game_state == game_state_e::STARTING) {
    /// Do nothing.
  } else if(m_game_state == game_state_e::WELCOME) {
    display_welcome();
  } else if(m_game_state == game_state_e::MAIN_MENU) {
    display_main_menu();
  } else if(m_game_state == game_state_e::PLAYING) {
    display_play_screen(m_current_mistakes);
  } else if (m_game_state == game_state_e::SCORE_MENU) {
    display_score_menu();
  } else if(m_game_state == game_state_e::SHOW_SCORE) {
    display_scoreboard();
  } else if(m_game_state == game_state_e::SHOW_RULES) {
    display_rules();
  } else if(m_game_state == game_state_e::QUITTING) {
    display_quitting();
  } else if(m_game_state == game_state_e::ENDING) {
    display_endgame();
  } else {
    throw std::runtime_error("Sorry! Unfortunately, there was a problem with the game state!");
  }
}
