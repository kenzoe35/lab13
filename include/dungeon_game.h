#ifndef ARCADE_DUNGEON_GAME_H
#define ARCADE_DUNGEON_GAME_H

#include "game.h"

/// @file dungeon_game.h
/// @brief Dungeon as a Game.

/// Dungeon, wrapping play_dungeon().
class Dungeon : public Game {
public:
  Dungeon();

  /// Play once, record the score, and count the play.
  void play();

  /// @return how many times play() has run
  int times_played() const;

private:
  int m_times_played;
};

#endif // ARCADE_DUNGEON_GAME_H
