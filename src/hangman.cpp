#include "hangman.h"

#include <iomanip>
#include <iostream>

#include "input.h"
#include "words.h"

std::string pick_word(const std::string words[], int count, std::mt19937 &gen) {
  std::uniform_int_distribution<int> pick{0, count - 1};
  return words[pick(gen)];
}

char to_lower(char c) {
  if (c >= 'A' && c <= 'Z') {
    return static_cast<char>(c - 'A' + 'a');
  }
  return c;
}

bool is_letter(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool already_guessed(const std::string &guessed, char c) {
  for (std::string::size_type i = 0; i < guessed.size(); ++i) {
    if (guessed[i] == c) {
      return true;
    }
  }
  return false;
}

bool reveal_letter(const std::string &word, std::string &masked, char c) {
  bool found = false;
  for (std::string::size_type i = 0; i < word.size(); ++i) {
    if (word[i] == c) {
      masked[i] = c;
      found = true;
    }
  }
  return found;
}

void draw_gallows(int misses) {
  std::cout << "  +---+\n";
  switch (misses) {
  case 0:
    std::cout << "  |   |\n      |\n      |\n      |\n";
    break;
  case 1:
    std::cout << "  |   |\n  O   |\n      |\n      |\n";
    break;
  case 2:
    std::cout << "  |   |\n  O   |\n  |   |\n      |\n";
    break;
  case 3:
    std::cout << "  |   |\n  O   |\n /|   |\n      |\n";
    break;
  case 4:
    std::cout << "  |   |\n  O   |\n /|\\  |\n      |\n";
    break;
  case 5:
    std::cout << "  |   |\n  O   |\n /|\\  |\n /    |\n";
    break;
  default:
    std::cout << "  |   |\n  O   |\n /|\\  |\n / \\  |\n";
    break;
  }
  std::cout << "=========\n";
}

void print_status(const std::string &masked, const std::string &guessed,
                  int misses_left) {
  std::cout << std::left << std::setw(14) << "Word:" << masked << "\n"
            << std::setw(14) << "Guessed:" << guessed << "\n"
            << std::setw(14) << "Misses left:" << misses_left << "\n";
}

int hangman_score(int misses_left, int word_length) {
  return misses_left * 10 + word_length * 5;
}

int play_hangman() {
  std::random_device device;
  std::mt19937 gen{device()};

  const std::string word = pick_word(word_list, word_count, gen);
  std::string masked(word.size(), '_');
  std::string guessed;
  int misses = 0;

  std::cout << "\n--- Hangman ---\n";
  while (misses < max_misses && masked != word) {
    draw_gallows(misses);
    print_status(masked, guessed, max_misses - misses);

    std::string line;
    if (!prompt_line("Guess a letter: ", line)) {
      return 0;
    }
    if (line.size() != 1 || !is_letter(line[0])) {
      std::cout << "Please enter a single letter.\n";
      continue;
    }
    const char guess = to_lower(line[0]);
    if (already_guessed(guessed, guess)) {
      std::cout << "You already guessed '" << guess << "'.\n";
      continue;
    }
    guessed += guess;
    if (!reveal_letter(word, masked, guess)) {
      ++misses;
      std::cout << "No '" << guess << "' in the word.\n";
    }
  }

  draw_gallows(misses);
  if (masked == word) {
    std::cout << "You win! The word was " << word << ".\n";
    return hangman_score(max_misses - misses, static_cast<int>(word.size()));
  } else {
    std::cout << "You lose. The word was " << word << ".\n";
    return 0;
  }
}
