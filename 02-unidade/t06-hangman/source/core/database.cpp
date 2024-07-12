#include "database.h"

#include <cassert>
#include <cctype>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <locale> 
#include <algorithm> 
#include <locale> 
#include <codecvt>
#include <unordered_set>
#include <random>

DataBase::DataBase() 
		: m_words_category(), 
		m_play_words(), 
		m_hard_words(), 
		m_medium_words(), 
		m_easy_words() {
} 

//=== Auxiliary methods.
/*!
 * Remove whitespace from the left of a string.
 *
 * @param input_multimap String without the removed spaces.
 *
 * @return String without whitespaces.
 *
 */
std::wstring DataBase::trim_left(const std::wstring& str) {
  size_t first = str.find_first_not_of(L" \t\r\n");

  if (first == std::wstring::npos) {
    return L"";
  }

  return str.substr(first);
}

/*!
 * Remove whitespace from the right of a string.
 *
 * @param input_multimap String without the removed spaces.
 *
 * @return String without whitespaces.
 *
 */
std::wstring DataBase::trim_right(const std::wstring& str) {
  size_t last = str.find_last_not_of(L" \t\r\n");

  if (last == std::wstring::npos) {
    return L"";
  }
  return str.substr(0, last + 1);
}

/*!
 * Calculate bound of word.
 *
 * @param word Word to be calculate.
 *
 * @return Bound of word.
 *
 */
int DataBase::calculate_bound(const std::wstring& word) {
  std::unordered_set<wchar_t> letter;

  /// Calculte variety of chars.
  for (wchar_t c : word) {
    if (iswalpha(c) || iswblank(c)) { 
      letter.insert(towlower(c)); 
    }
  }

  int length = word.length();
  int variety = letter.size();

  return variety + length;
}

/*!
 * Classify a word as easy, medium or hard.
 *
 * @param word Word to be classified.
 *
 * @return Difficulty of word.
 *
 */
std::wstring DataBase::word_classify(const std::wstring& word){
  int bound_word = calculate_bound(word);
  
  double percentage = static_cast<double>(bound_word) / m_upper_bound; /// Percentage of the word bound compared to the max bound.

  /// Classify word.
  if (percentage <= 0.45) {
    return L"easy";
  } else if (percentage <= 0.75) {
    return L"medium";
  } else{
    return L"hard";
  }
}

/*!
 *
 * @param str String to remove accents.
 *
 * @return String without acents.
 *
 */
std::wstring DataBase::remove_acent(const std::wstring& str) {
  /// Data struct with acents.
  std::map<std::vector<std::wstring>, std::wstring> data_acent = {
    {{L"á", L"â", L"ã", L"à", L"ä"}, L"a"},
    {{L"é", L"ê", L"ũ", L"è", L"ë"}, L"e"},
    {{L"í", L"î", L"ĩ", L"ì", L"ï"}, L"i"},
    {{L"ó", L"ô", L"õ", L"ò", L"ö"}, L"o"},
    {{L"ú", L"û", L"ù", L"ü"}, L"u"},
    {{L"ç"}, L"c"},
    {{L"ñ"}, L"n"}
  };
  
  std::wstring result = str; //!<- String without acents

  /// Remove acents.
  for (auto& pair : data_acent) {
    for (const auto& accented_char : pair.first) {
      size_t pos = 0;
      while ((pos = result.find(accented_char, pos)) != std::wstring::npos) {
        result.replace(pos, accented_char.length(), pair.second);
        pos += pair.second.length();
      }
    }
  }
  return result;
}

//=== Methods to set member classes.
/*!
 * Filter words by category and repetitions.
 *
 * @param input_multimap Multimap with category and words.
 * @param user_categories Categories informed from user.
 *
 */
void DataBase::set_m_play_words(const std::vector<std::wstring>& user_categories) {
  std::vector<std::wstring> filtered_words;

  /// Get all words by category.
  for (const auto& category : user_categories) {
    auto range = m_words_category.equal_range(category);

    for(auto idx = range.first; idx != range.second; ++idx) {
      filtered_words.push_back(idx->second);
    }
  }

  /// Delete repetitions of words.
	std::sort(filtered_words.begin(), filtered_words.end());
  auto last = std::unique(filtered_words.begin(), filtered_words.end());
  filtered_words.erase(last, filtered_words.end());

  m_play_words.clear();
	m_play_words = filtered_words;
}

/*!
 * Get all words and categories to create a multimap.
 *
 */
void DataBase::set_m_words_category() {
	std::wifstream file("../core/set/words.csv"); //!<- Path to file words.csv.

  if (!file.is_open()) {
    std::cout << ">>> Error opening the file words.csv!" << std::endl;
    exit(EXIT_FAILURE);
  } 

  file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t>));

  multimap_word all_words; //!<- Multimap with all words from file words.csv.
  std::wstring line; //!<- Each line of the CSV file.

  while(std::getline(file, line)) {
    std::wstringstream ss(line);
    std::wstring field; //!<- Each field of the line
    int index = 0; //!<- Index from de field
    std::wstring word = L"";

    while (std::getline(ss, field, L',')) { 
      field = trim_left(trim_right(field)); //!<- Field without whitespace at the edges.

      if (index == 0) {
        word = field; //!<- Set word of the line
      } 

      if (index != 0) {
        all_words.insert(std::make_pair(field, word)); //!<- Create a make_pair with word and fields (categories).
      }
      index++;
    }
  }

	m_words_category =  all_words;
}

/*!
 * Filter words by category and repetitions.
 *
 * @param difficulty Diffyculty chosen by user.
 *
 */
void DataBase::set_m_upper_bound(std::wstring difficulty) {
	multimap_word copy_multimap_word = m_words_category;
	int max_bound = 0;
	std::vector<std::wstring> words; //!<- Words of multimap.

  /// Get words of multimap.
	for(const auto& pair : copy_multimap_word) {
		words.push_back(pair.second);
	}

  if(difficulty == L"easy") {
    for(auto& word : words) {
      word = remove_acent(word);
    }
	}

  /// Calculate bounds of words.
	for (const std::wstring& word : words) {
		int bound = calculate_bound(word);

		if(bound > max_bound) {
			max_bound = bound;
		}
	}

	m_upper_bound = max_bound;
}

/*!
 * Set all words by difficultys in vector difficulty.
 *
 */
void DataBase::set_m_diff_words() {
  /// Clear old values of the vectors.
  m_easy_words.clear();
  m_medium_words.clear();
  m_hard_words.clear();

  /// Distribute words by their difficulty into vectors.
  for(const auto& word : m_play_words) {
    std::wstring word_difficulty = word_classify(word);

    if (word_difficulty == L"easy") {
      m_easy_words.push_back(word);
    }

    if (word_difficulty == L"medium") {
      m_medium_words.push_back(word);
    }

    if (word_difficulty == L"hard") {
      m_hard_words.push_back(word);
    }
  }
}

/*!
 * Randomly select the word based on probability values.
 *
 * @param easy_prob String without the removed spaces.
 * @param med_prob String without the removed spaces.
 * @param hard_prob String without the removed spaces.
 * 
 * @return Randomly selected word to play game.
 *
 */
std::wstring DataBase::select_word(float easy_prob, float med_prob, float hard_prob) {
  std::wstring sorted_word; //!<- Sorted word to play.
  
  /// Configuration to randomly select the word difficulty.
  std::random_device n_diff;  
  std::mt19937 gen_diff(n_diff()); 
  std::uniform_real_distribution<> dis(0, 1); 

  double random_number = dis(gen_diff); //!<- Difficulty of word.

  /// Configuration to shuffle vectors.
  std::random_device rd_key;
  std::mt19937 gen_word(rd_key()); 

  /// Sorted word.
  if(random_number <  easy_prob) {
    std::shuffle(m_easy_words.begin(), m_easy_words.end(), rd_key);
    return m_easy_words[0];
  } else if(random_number < easy_prob + med_prob) {
    std::shuffle(m_medium_words.begin(), m_medium_words.end(), rd_key);
    return m_medium_words[0];
  } else {
    std::shuffle(m_hard_words.begin(), m_hard_words.end(), rd_key);
    return m_hard_words[0];
  }
}