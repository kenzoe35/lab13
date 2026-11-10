#ifndef ARCADE_HANGMAN_H
#define ARCADE_HANGMAN_H

#include <random>
#include <string>

/// @file hangman.h
/// @brief Hangman, written with free functions only.

/// The number of wrong guesses that lose the game.
inline constexpr int max_misses = 6;

/// Choose a word at random.
/// @param words an array of words
/// @param count how many words are in @p words
/// @param gen the random number generator to draw from
/// @return one of the words
std::string pick_word(const std::string words[], int count, std::mt19937 &gen);

/// Convert an uppercase letter to lowercase; leave everything else alone.
/// @param c any character
/// @return the lowercase letter, or @p c unchanged
char to_lower(char c);

/// @param c any character
/// @return true for 'a' to 'z' and 'A' to 'Z'
bool is_letter(char c);

/// @param guessed the letters guessed so far
/// @param c a lowercase letter
/// @return true if @p c is already in @p guessed
bool already_guessed(const std::string &guessed, char c);

/// Show every occurrence of a letter in the masked word.
/// @param word the secret word
/// @param masked the word with unguessed letters shown as '_' (updated)
/// @param c the guessed lowercase letter
/// @return true if @p c appears in @p word at least once
bool reveal_letter(const std::string &word, std::string &masked, char c);

/// Print the gallows for a number of misses.
/// @param misses a number from 0 to max_misses
void draw_gallows(int misses);

/// Print the masked word, the letters guessed, and the misses left.
/// @param masked the masked word
/// @param guessed the letters guessed so far
/// @param misses_left how many wrong guesses remain
void print_status(const std::string &masked, const std::string &guessed,
                  int misses_left);

/// The score for a finished game.
/// @param misses_left wrong guesses the player still had
/// @param word_length number of letters in the word
/// @return misses_left * 10 + word_length * 5
int hangman_score(int misses_left, int word_length);

/// Play one game of Hangman.
/// @return the score: hangman_score() for a win, 0 for a loss or if the player
/// stops early
int play_hangman();

#endif // ARCADE_HANGMAN_H
