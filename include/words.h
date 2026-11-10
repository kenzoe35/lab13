#ifndef ARCADE_WORDS_H
#define ARCADE_WORDS_H

#include <string>

/// @file words.h
/// @brief The word list for Hangman.

/// The number of words in the list.
inline constexpr int word_count = 10;

/// Lowercase words for Hangman.
inline const std::string word_list[word_count] = {
    "pointer",  "compiler",  "variable",    "function",    "debugger",
    "iterator", "reference", "constructor", "inheritance", "recursion",
};

#endif // ARCADE_WORDS_H
