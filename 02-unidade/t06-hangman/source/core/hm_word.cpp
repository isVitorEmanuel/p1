/*!
 * Hangman Word class
 * @file hm_word.cpp
 *
 * Class implementation.
 *
 * \author Selan
 * \date April 20th, 2022
 */

#include <cwctype>
#include <unordered_map>
#include <random>
#include "hm_word.h"
#include <iostream>
#include <algorithm>  

//=== Public interface
/// Default Ctro. Assumes input strings are all lower case.
/*!
* @param secret The secret word.
* @param show List of letters in the secret word to show to player.
* @param mask Char to use as mask.
*/
HangmanWord::HangmanWord(std::wstring secret, std::wstring show, wchar_t mask)
	: m_secret_word(secret), 
	m_masked_word(show), 
	m_mask_char(mask) {}

void HangmanWord::show_init_letters(const std::wstring& m_diff) {
	std::unordered_map<wchar_t, int> char_count;
	std::vector<wchar_t> once;
	std::vector<wchar_t> twice;
	std::vector<wchar_t> thrice;

	std::wstring normalized_secret = m_secret_word;
	if ( m_diff == L"easy") {
			normalized_secret = normalize(m_secret_word);
	}

	for (size_t i = 0; i < m_secret_word.size(); ++i) {
		wchar_t ch = (m_diff == L"easy") ? normalized_secret[i] : m_secret_word[i];
		if (ch != L' ' && ch != L'-') {
			char_count[ch]++;
		}
	}

	for (const auto& pair : char_count) {
		if (pair.second == 1) {
			once.push_back(pair.first);
		} else if (pair.second == 2) {
			twice.push_back(pair.first);
		} else if (pair.second >= 3) {
			thrice.push_back(pair.first);
		}
	}

	std::random_device rd;
	std::mt19937 gen(rd());

  std::vector<wchar_t> chosen_letters;

	while (chosen_letters.empty()) {
		std::shuffle(once.begin(), once.end(), gen);
		std::shuffle(twice.begin(), twice.end(), gen);
		std::shuffle(thrice.begin(), thrice.end(), gen);

		std::uniform_real_distribution<> dis(0.0, 1.0);
		double random_number = dis(gen);

		if(m_diff == L"easy") {
			if (random_number <= 0.4) {
				if (!thrice.empty()) {
					chosen_letters.push_back(thrice[0]);
					chosen_letters.push_back(thrice[0]);
					chosen_letters.push_back(thrice[0]);
				}
			} else if (random_number > 0.4 && random_number <= 0.7) {
				if (!twice.empty() && !once.empty()) {
					chosen_letters.push_back(twice[0]);
					chosen_letters.push_back(twice[0]);
					chosen_letters.push_back(once[0]);
				}
			} else {
				if (once.size() >= 3) {
					chosen_letters.push_back(once[0]);
					chosen_letters.push_back(once[1]);
					chosen_letters.push_back(once[2]);
				}
			}
		} else {
			if(random_number <= 0.5) {
				if(!(twice.empty())) {
					chosen_letters.push_back(twice[0]);
					chosen_letters.push_back(twice[0]);
				}
			} else {
				chosen_letters.push_back(once[0]);
				chosen_letters.push_back(once[1]);
			}
		}
	}
	
	for (wchar_t ch : chosen_letters) {
		m_open_letters += ch;
	}

	for (wchar_t ch : m_open_letters) {
		for (size_t i = 0; i < m_secret_word.size(); ++i) {
			wchar_t current_char = (m_diff == L"easy") ? normalized_secret[i] : m_secret_word[i];
			if (current_char == ch && m_masked_word[i] == m_mask_char) {
				m_masked_word[i] = m_secret_word[i];
				break;
			}
		}
	}
}

void HangmanWord::initialize(const std::wstring &sw, const std::wstring& diff , const std::wstring &ol,
                                wchar_t mch) {
	m_secret_word = sw;
	m_open_letters = ol;
	m_mask_char = mch;

	std::wstring buff = m_secret_word;

	for (size_t i = 0; i < m_secret_word.length(); ++i) {
		if (m_secret_word[i] == L' ' || m_secret_word[i] == L'-') {
			buff[i] = m_secret_word[i]; 
			m_open_letters.push_back(m_secret_word[i]);
		} else {
			buff[i] = m_mask_char;
		}
	}

	m_masked_word = buff;

	if(diff != L"hard") {
		show_init_letters(diff);
	}
	
	m_n_correct_guesses = 0;
}

std::wstring HangmanWord::normalize(const std::wstring& input) {
	static const std::unordered_map<wchar_t, wchar_t> normalization_map = {
		{L'à', L'a'}, {L'á', L'a'}, {L'â', L'a'}, {L'ã', L'a'}, {L'ä', L'a'}, {L'å', L'a'},
		{L'è', L'e'}, {L'é', L'e'}, {L'ê', L'e'}, {L'ë', L'e'},
		{L'ì', L'i'}, {L'í', L'i'}, {L'î', L'i'}, {L'ï', L'i'},
		{L'ò', L'o'}, {L'ó', L'o'}, {L'ô', L'o'}, {L'õ', L'o'}, {L'ö', L'o'},
		{L'ù', L'u'}, {L'ú', L'u'}, {L'û', L'u'}, {L'ü', L'u'},
		{L'ç', L'c'},
		{L'À', L'a'}, {L'Á', L'a'}, {L'Â', L'a'}, {L'Ã', L'a'}, {L'Ä', L'a'}, {L'Å', L'a'},
		{L'È', L'e'}, {L'É', L'e'}, {L'Ê', L'e'}, {L'Ë', L'e'},
		{L'Ì', L'i'}, {L'Í', L'i'}, {L'Î', L'i'}, {L'Ï', L'i'},
		{L'Ò', L'o'}, {L'Ó', L'o'}, {L'Ô', L'o'}, {L'Õ', L'o'}, {L'Ö', L'o'},
		{L'Ù', L'u'}, {L'Ú', L'u'}, {L'Û', L'u'}, {L'Ü', L'u'},
		{L'Ç', L'c'}
	};

	std::wstring output;
	output.reserve(input.size());

	for (wchar_t ch : input) {
		auto it = normalization_map.find(ch);
		if (it != normalization_map.end()) {
			output.push_back(it->second);
		} else {
			output.push_back(std::towlower(ch));
		}
	}

	return output;
}

HangmanWord::guess_e HangmanWord::guess(wchar_t g, std::wstring diff) {

	if(diff == L"easy") {
		std::wstring normalized_secret_word = normalize(m_secret_word);
		std::wstring normalized_masked_word = normalize(m_masked_word);
		wchar_t normalized_g = normalize(std::wstring(1, g))[0];

    if (normalized_secret_word.find(normalized_g) != std::wstring::npos) {
			if (normalized_masked_word.find(normalized_g) != std::wstring::npos) {
				return guess_e::REPEATED;
			}

			for (size_t i = 0; i < m_secret_word.size(); ++i) {
				if (normalized_secret_word[i] == normalized_g) {
					m_masked_word[i] = m_secret_word[i];
					m_n_correct_guesses++;
					m_correct_guesses.push_back(normalized_g);
				}
			}
			return guess_e::CORRECT;
    } else {
			for (const wchar_t& ch : m_wrong_guesses) {
				if (ch == g) {
					return guess_e::REPEATED;
					}
        }
        m_wrong_guesses.push_back(normalized_g);

        return guess_e::WRONG;
    	}
	} else {

		if (m_secret_word.find(g) != std::wstring::npos) {
			if (m_masked_word.find(g) != std::wstring::npos) {
				return guess_e::REPEATED;	
			}

		for (size_t i = 0; i < m_secret_word.size(); ++i) {
			if (m_secret_word[i] == g) {
				m_masked_word[i] = g;
				m_n_correct_guesses++;
				m_correct_guesses.push_back(g); 
			}
		}

		return guess_e::CORRECT;    
	} else {

		for (const wchar_t ch : m_wrong_guesses) {
			if (ch == g) {
				return guess_e::REPEATED;
			}
		}

		m_wrong_guesses.push_back(g);

		return guess_e::WRONG;
		}
	}
}

[[nodiscard]] size_t HangmanWord::wrong_guesses() const {
    return m_wrong_guesses.size();
}

[[nodiscard]] size_t HangmanWord::correct_guesses() const {
	size_t correct = 0;
	for (size_t i = 0; i < m_secret_word.size(); ++i) {
		if (m_secret_word[i] != m_mask_char && m_secret_word[i] == m_masked_word[i]) {
			++correct;
		}
	}
	return correct;
}

[[nodiscard]] std::vector<wchar_t> HangmanWord::wrong_guesses_list() const {
    return m_wrong_guesses;
}

[[nodiscard]] std::vector<wchar_t> HangmanWord::correct_guesses_list() const {
    return m_correct_guesses;
}

[[nodiscard]] short HangmanWord::n_masked_ch() const {	
	return m_masked_word.size();
}

[[nodiscard]] wchar_t HangmanWord::mask_char() const {
	return m_mask_char;
}

[[nodiscard]] std::wstring HangmanWord::operator()() const {
    return m_secret_word;
}

[[nodiscard]] std::wstring HangmanWord::masked_str() const {
	return m_masked_word;
}

void HangmanWord::reset() {
	m_secret_word.clear();
	m_masked_word.clear();
	m_open_letters.clear();
	
	m_n_correct_guesses = 0;
	m_wrong_guesses.clear();
	m_correct_guesses.clear();
	
	m_mask_char = L'_';
}
