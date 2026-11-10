#ifndef ARCADE_BLACKJACK_GAME_H
#define ARCADE_BLACKJACK_GAME_H

#include "game.h"

/// @file blackjack_game.h
/// @brief Blackjack as a Game.

/// Blackjack, wrapping play_blackjack().
class Blackjack : public Game {
public:
  Blackjack();

  /// Play once, record the score, and count the play.
  void play();

  /// @return how many times play() has run
  int times_played() const;

private:
  int m_times_played;
};

#endif // ARCADE_BLACKJACK_GAME_H
