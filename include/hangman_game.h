#ifndef ARCADE_HANGMAN_GAME_H
#define ARCADE_HANGMAN_GAME_H

#include "game.h"

/// @file hangman_game.h
/// @brief Hangman as a Game.

/// Hangman, wrapping play_hangman().
class Hangman : public Game {
public:
  Hangman();

  /// Play once, record the score, and count the play.
  void play() override;

  /// @return how many times play() has run
  int times_played() const;

private:
  int m_times_played;
};

#endif // ARCADE_HANGMAN_GAME_H
