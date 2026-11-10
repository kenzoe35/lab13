#include "game.h"

#include <iostream>
#include <utility>

#include "input.h"

Game::Game(std::string title) : m_title{std::move(title)}, m_last_score{0} {}

const std::string &Game::title() const { return m_title; }

int Game::last_score() const { return m_last_score; }

void Game::play() { std::cout << "Game::play called\n"; }

void Game::set_score(int score) { m_last_score = score; }

bool Game::ask_play_again() const {
  std::string line;
  if (!prompt_line("Play again? (y/n): ", line)) {
    return false;
  }
  return !line.empty() && (line[0] == 'y' || line[0] == 'Y');
}
