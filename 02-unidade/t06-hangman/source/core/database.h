#ifndef DATABASE_H
#define DATABASE_H

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

using multimap_word = std::multimap<std::wstring, std::wstring>;

/*!
 * This class represents the database of game, 
 * 
 */
class DataBase {
private:
	multimap_word m_words_category; /// Multimap with all categorys and word from the game
	std::vector<std::wstring> m_play_words; /// Words filtered by category
	std::vector<std::wstring> m_hard_words; /// Easy words filtered by category 
	std::vector<std::wstring> m_medium_words; /// Easy words filtered by category
	std::vector<std::wstring> m_easy_words; /// Easy words filtered by category
	int m_upper_bound; /// Max bound of words.
public:
	//=== Public interface
	/// Constructor
	DataBase();
	/// Destrucot
	~DataBase() = default;

	//=== Methods to set member classes.
	/// Set words and categories multimaps. 
	void set_m_words_category();
	/// Set words filtered by category. 
	void set_m_play_words(
		const std::vector<std::wstring>& user_categories
	);
	/// Set upper_bound (most difficult word to guess).
	void set_m_upper_bound(std::wstring difficulty);
	/// Set all words in the category vectors.
	void set_m_diff_words();
	/// Return de word guess.
	std::wstring select_word(float easy_prob, float med_prob, float hard_prob);
private:
	///=== Auxiliary methods.
	/// Remove whitespace from the right of a string.
	std::wstring trim_right(const std::wstring& str);
	/// Remove whitespace from the left of a string.
	std::wstring trim_left(const std::wstring& str);
	/// Calculate bound of word.
	int calculate_bound(const std::wstring& word);
	/// Classify a word as easy, medium or hard.
	std::wstring word_classify(const std::wstring& word);
	/// Remove acents from words.
	std::wstring remove_acent(const std::wstring& str);
};
#endif