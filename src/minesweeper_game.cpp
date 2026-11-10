#include "minesweeper_game.h"

#include "minesweeper.h"

Minesweeper::Minesweeper() : Game{"Minesweeper"}, m_times_played{0} {}

void Minesweeper::play() {
  set_score(play_minesweeper());
  ++m_times_played;
}

int Minesweeper::times_played() const { return m_times_played; }
