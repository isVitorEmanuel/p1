/*!
 * Player class implementation.
 *
 * \author Selan
 * \date April 21st, 2022
 * \file player.cpp
 */

#include <sstream>
#include "player.h"

// === Auxiliary functions to help user input

// === Regular methods of the Player class.

std::wstring Player::name() const { return m_name; }

void Player::name(const std::wstring &name) { m_name = name; }

int Player::total_score() const {
    return m_easy_score + m_medium_score + m_hard_score;
}

void Player::add_score(int quantity, const std::wstring& diff) {
    if (diff == L"easy"){
        m_easy_score += quantity;
    } else if (diff == L"medium"){
        m_medium_score += quantity;
    } else if (diff == L"hard"){
        m_hard_score += quantity;
    } else {
        throw std::invalid_argument("Invalid Difficulty");
    }
}

void Player::add_win(const std::wstring &diff) {
    if (diff == L"easy"){
        m_easy_games_won++;
    } else if (diff == L"medium"){
        m_medium_games_won++;
    } else if (diff == L"hard"){
        m_hard_games_won++;
    } else {
        throw std::invalid_argument("Invalid Difficulty");
    }
}

void Player::add_new_game(const std::wstring &diff) {
    if (diff == L"easy"){
        m_easy_games_played++;
    } else if (diff == L"medium"){
        m_medium_games_played++;
    } else if (diff == L"hard"){
        m_hard_games_played++;
    } else {
        throw std::invalid_argument("Invalid Difficulty");
    }
}

int Player::get_score_by_diff(const std::wstring &diff) const {
    if (diff == L"easy"){
        return m_easy_score;
    } else if (diff == L"medium"){
        return m_medium_score;
    } else if (diff == L"hard"){
        return m_hard_score;
    } else {
        throw std::invalid_argument("Invalid Difficulty");
    }
}

size_t Player::get_wins_by_diff(const std::wstring &diff) const {
    if (diff == L"easy"){
        return m_easy_games_won;
    } else if (diff == L"medium"){
        return m_medium_games_won;
    } else if (diff == L"hard"){
        return m_hard_games_won;
    } else {
        throw std::invalid_argument("Invalid Difficulty");
    }
}

size_t Player::get_number_of_games(const std::wstring &diff) const {
    if (diff == L"easy"){
        return m_easy_games_played;
    } else if (diff == L"medium"){
        return m_medium_games_played;
    } else if (diff == L"hard"){
        return m_hard_games_played;
    } else {
        throw std::invalid_argument("Invalid Difficulty");
    }
}

void Player::add_word(const std::wstring &w) { m_played_words.insert(w); }

bool Player::has_played(const std::wstring &w) const {
  return m_played_words.count(w) != 0;
}

void Player::clear_word_list() { m_played_words.clear(); }

size_t Player::get_total_games() const {
    return m_easy_games_played + m_medium_games_played + m_hard_games_played;
}

size_t Player::get_total_wins() const {
    return m_easy_games_won + m_medium_games_won + m_hard_games_won;
}

size_t Player::get_loses_by_diff(const std::wstring &diff) const {
    if (diff == L"easy"){
        return m_easy_games_played - m_easy_games_won;
    } else if (diff == L"medium"){
        return m_medium_games_played - m_medium_games_won;
    } else if (diff == L"hard"){
        return m_hard_games_played - m_hard_games_won;
    } else {
        throw std::invalid_argument("Invalid Difficulty");
    }
}

size_t Player::get_total_losses() const {
    return get_total_games() - get_total_wins();
}

std::wstring Player::to_csv_line() const {
    std::wstringstream wss;
    size_t easy_loses = this->get_loses_by_diff(L"easy");
    size_t medium_loses = this->get_loses_by_diff(L"medium");
    size_t hard_loses = this->get_loses_by_diff(L"hard");
    size_t total_games = this->get_total_games();
    size_t total_wins = this->get_total_wins();
    size_t total_losses = this->get_total_losses();
    size_t score = this->total_score();

    wss << m_name << L',';
    wss << m_easy_games_played << L',' << m_easy_games_won << L','
        << easy_loses << L',' << m_easy_score << L',';
    wss << m_medium_games_played << L',' << m_medium_games_won << L','
        << medium_loses << L',' << m_medium_score << L',';
    wss << m_hard_games_played << L',' << m_hard_games_won << L','
        << hard_loses << L',' << m_hard_score << L',';
    wss << total_games << L',' << total_wins << L','
        << total_losses << L',' << score;
    return wss.str();
}

std::vector<std::wstring> Player::get_scoreboard_info(const std::wstring& name, size_t i_begin, size_t i_end){
    std::wifstream file(FILE_PATH, std::ios::binary);

    if (!file.is_open()) {
        std::cout << ">>> Error opening the file players.bin!" << std::endl;
        exit(EXIT_FAILURE);
    }

    file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t>));

    std::vector<std::wstring> result; //!<- resulting vector covering desired range
    std::wstring line; //!<- stores one line of the file

    while (std::getline(file, line)) {
        std::wstringstream wss(line);
        std::wstring current_value; //!<- stores a value between commas in the line
        // block of code executes if the first value of current line matches 'name'
        if (std::getline(wss, current_value, L',') and current_value == name){
            std::vector<std::wstring> all_values; //!<- unfiltered container for line content
            all_values.push_back(current_value); //!<- stores name at first position

            while (std::getline(wss, current_value, L',')){
                all_values.push_back(current_value);
            }
            result.push_back(all_values[0]); //!<- stores name at result container first position
            for (size_t i = i_begin; i <= i_end; ++i){
                result.push_back(all_values[i]);
            }
            break; /// player name must be unique so no need to continue the loop after first occurence
        }

    }

    file.close();
    return result;
}

void Player::update_scoreboard_info(const std::wstring& name){

    std::wfstream file(FILE_PATH, std::ios::in | std::ios::out | std::ios::binary);

    if (!file.is_open()) {
        std::cerr << ">>> Error opening the file players.bin!" << std::endl;
        exit(EXIT_FAILURE);
    }

    file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t>));

    std::wstring line; //!<- stores content from one line of the file
    std::vector<std::wstring> lines; //!<- container to store all lines of the file

    /// stores all lines of the file in the container
    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    bool found = false; //!<- flag that indicates if a player with 'name' is already registered
    for (auto& current_line : lines) {
        std::wstringstream wss(current_line);
        std::wstring current_name;
        if (std::getline(wss, current_name, L',') and current_name == name) {
            current_line = this->to_csv_line(); /// updates the player line with most recent values
            found = true;
            break; /// player name must be unique so no need to continue the loop after first occurence
        }
    }

    /// player not found, info will be added at the end of the file
    if (!found) {
        lines.push_back(this->to_csv_line());
    }

    file.close();
    /// clears current content of the file
    std::ofstream clear_file(FILE_PATH, std::ios::trunc);
    clear_file.close();

    /// updates the file, writing again every stored line
    std::wofstream write_file(FILE_PATH, std::ios::binary);
    for (const auto& updated_line : lines) {
        write_file << updated_line << std::endl;
    }

    write_file.close();
}

void Player::get_previous_score(const std::wstring &name) {
    std::vector<std::wstring> values = get_scoreboard_info(name, 1, 16);

    if (!values.empty()) {
    m_easy_games_played = std::stoi(values[1]);
    m_easy_games_won = std::stoi(values[2]);
    m_easy_score = std::stoi(values[4]);
    m_medium_games_played = std::stoi(values[5]);
    m_medium_games_won = std::stoi(values[6]);
    m_medium_score = std::stoi(values[8]);
    m_hard_games_played = std::stoi(values[9]);
    m_hard_games_won = std::stoi(values[10]);
    m_hard_score = std::stoi(values[12]);
    }

    this->update_scoreboard_info(name);
}

std::vector<std::wstring> Player::get_all_names() {

    std::wifstream file(FILE_PATH, std::ios::binary);

    if (!file.is_open()) {
        std::cout << ">>> Error opening the file players.bin!" << std::endl;
        exit(EXIT_FAILURE);
    }

    file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t>));

    std::vector<std::wstring> result; //!<- resulting list of names in the file
    std::wstring line; //!<- stores one line of the file

    while (std::getline(file, line)) {
        std::wstringstream wss(line);
        std::wstring current_name;

        if (std::getline(wss, current_name, L',')){
            result.push_back(current_name);
        }
    }

    file.close();

    return result;
}

void Player::print_score(const int &option) {
    std::vector<std::wstring> all_names = get_all_names();
    std::vector<Player> players;

    for (const auto& name : all_names){
        Player aux(name);
        aux.get_previous_score(name);
        players.push_back(aux);
    }
    if (option == 1) { /// Easy difficulty scoreboard
        std::sort(players.begin(), players.end(), comp_by_easy_score);
        /// Header
        std::wcout << std::setw(40) << std::left << L"Name"
              << std::setw(15) << std::internal << L"Games played"
              << std::setw(10) << std::internal << L"Wins"
              << std::setw(10) << std::internal << L"Loses"
              << std::setw(10) << std::internal << L"Score" << std::endl;
        for (const auto& player : players){
            std::wcout << std::setw(40) << std::left << player.m_name
                       << std::setw(15) << std::internal << player.m_easy_games_played
                       << std::setw(10) << std::internal << player.m_easy_games_won
                       << std::setw(10) << std::internal << player.get_loses_by_diff(L"easy")
                       << std::setw(10) << std::internal << player.m_easy_score << std::endl;
        }
    } else if (option == 2) { /// Medium difficulty scoreboard
        std::sort(players.begin(), players.end(), comp_by_medium_score);
        /// Header
        std::wcout << std::setw(40) << std::left << L"Name"
                   << std::setw(15) << std::internal << L"Games played"
                   << std::setw(10) << std::internal << L"Wins"
                   << std::setw(10) << std::internal << L"Loses"
                   << std::setw(10) << std::internal << L"Score" << std::endl;
        for (const auto& player : players){
            std::wcout << std::setw(40) << std::left << player.m_name
                       << std::setw(15) << std::internal << player.m_medium_games_played
                       << std::setw(10) << std::internal<< player.m_medium_games_won
                       << std::setw(10) << std::internal << player.get_loses_by_diff(L"medium")
                       << std::setw(10) << std::internal << player.m_medium_score << std::endl;
        }
    } else if (option == 3) { /// Hard difficulty scoreboard
        std::sort(players.begin(), players.end(), comp_by_hard_score);
        /// Header
        std::wcout << std::setw(40) << std::left << L"Name"
                   << std::setw(15) << std::internal << L"Games played"
                   << std::setw(10) << std::internal << L"Wins"
                   << std::setw(10) << std::internal << L"Loses"
                   << std::setw(10) << std::internal << L"Score" << std::endl;
        for (const auto& player : players){
            std::wcout << std::setw(40) << std::left << player.m_name
                       << std::setw(15) << std::internal << player.m_hard_games_played
                       << std::setw(10) << std::internal << player.m_hard_games_won
                       << std::setw(10) << std::internal << player.get_loses_by_diff(L"hard")
                       << std::setw(10) << std::internal << player.m_hard_score << std::endl;
        }
    } else if (option == 4) { /// Total scoreboard
        std::sort(players.begin(), players.end(), comp_by_total_score);
        /// Header
        std::wcout << std::setw(40) << std::left << L"Name"
                   << std::setw(15) << std::internal << L"Games played"
                   << std::setw(10) << std::internal << L"Wins"
                   << std::setw(10) << std::internal << L"Loses"
                   << std::setw(10) << std::internal << L"Score" << std::endl;
        for (const auto& player : players){
            std::wcout << std::setw(40) << std::left << player.m_name
                       << std::setw(15) << std::internal << player.get_total_games()
                       << std::setw(10) << std::internal << player.get_total_wins()
                       << std::setw(10) << std::internal << player.get_total_losses()
                       << std::setw(10) << std::internal << player.total_score() << std::endl;
        }
    } else {
        std::wcout << L"Invalid option!" << std::endl;
    }
}

bool Player::comp_by_easy_score(const Player &p1, const Player &p2){
        if (p1.m_easy_score > p2.m_easy_score)
            return true;

        return p1.m_easy_games_won > p2.m_easy_games_won;
}
bool Player::comp_by_medium_score(const Player &p1, const Player &p2){
    if (p1.m_medium_score > p2.m_medium_score)
        return true;

    return p1.m_medium_games_won > p2.m_medium_games_won;
}
bool Player::comp_by_hard_score(const Player &p1, const Player &p2){
    if (p1.m_hard_score > p2.m_hard_score)
        return true;

    return p1.m_hard_games_won > p2.m_hard_games_won;
}
bool Player::comp_by_total_score(const Player &p1, const Player &p2){
    if (p1.total_score() > p2.total_score())
        return true;

    return p1.get_total_wins() > p2.get_total_wins();
}