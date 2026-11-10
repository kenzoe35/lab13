#include "minesweeper.h"

#include <iostream>
#include <random>
#include <string>

#include "board.h"
#include "input.h"

namespace {

/// Read "<row> <col>" from text. Returns false if it is not two whole numbers.
bool parse_position(const std::string &text, int &row, int &col) {
  std::string first;
  std::string second;
  split_first(text, first, second);
  return parse_int(first, row) && parse_int(second, col);
}

} // namespace

int minesweeper_score(int revealed_count, bool won) {
  return revealed_count + (won ? 100 : 0);
}

int play_minesweeper() {
  constexpr int rows = 8;
  constexpr int cols = 8;
  constexpr int mines = 10;

  std::random_device device;
  std::mt19937 gen{device()};
  Board board{rows, cols, mines};
  board.place_mines(gen);

  std::cout << "\n--- Minesweeper ---\n";
  std::cout
      << "Commands: r <row> <col> (reveal), f <row> <col> (flag), q (quit)\n";

  std::string line;
  while (true) {
    std::cout << "\n";
    board.print(false);
    if (!prompt_line("> ", line)) {
      return minesweeper_score(board.revealed_count(), false);
    }
    std::string verb;
    std::string rest;
    split_first(line, verb, rest);

    if (verb == "q") {
      std::cout << "You walk away from the board.\n";
      return minesweeper_score(board.revealed_count(), false);
    }
    if (verb != "r" && verb != "f") {
      std::cout << "Unknown command. Use r, f, or q.\n";
      continue;
    }
    int row = 0;
    int col = 0;
    if (!parse_position(rest, row, col) || !board.in_bounds(row, col)) {
      std::cout << "Enter two numbers from 0 to " << rows - 1
                << ", like: " << verb << " 3 4\n";
      continue;
    }
    if (verb == "f") {
      board.toggle_flag(row, col);
      continue;
    }
    switch (board.reveal(row, col)) {
    case RevealResult::mine:
      std::cout << "\nBOOM! You hit a mine.\n";
      board.print(true);
      return minesweeper_score(board.revealed_count(), false);
    case RevealResult::already_revealed:
      std::cout << "That square is already revealed.\n";
      break;
    case RevealResult::flagged:
      std::cout << "That square is flagged. Unflag it first.\n";
      break;
    case RevealResult::ok:
    case RevealResult::out_of_bounds:
      break;
    }
    if (board.is_won()) {
      std::cout << "\nYou cleared the board! Squares revealed: "
                << board.revealed_count() << "\n";
      board.print(true);
      return minesweeper_score(board.revealed_count(), true);
    }
  }
}
