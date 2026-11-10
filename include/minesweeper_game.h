#ifndef ARCADE_MINESWEEPER_GAME_H
#define ARCADE_MINESWEEPER_GAME_H

#include "game.h"

/// @file minesweeper_game.h
/// @brief Minesweeper as a Game.

/// Minesweeper, wrapping play_minesweeper().
class Minesweeper : public Game {
public:
  Minesweeper();

  /// Play once, record the score, and count the play.
  void play();

  /// @return how many times play() has run
  int times_played() const;

private:
  int m_times_played;
};

#endif // ARCADE_MINESWEEPER_GAME_H
