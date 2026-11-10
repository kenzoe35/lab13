#ifndef ARCADE_ARCADE_H
#define ARCADE_ARCADE_H

#include "game.h"

/// @file arcade.h
/// @brief The menu that owns and runs every Game.

/// The most games an Arcade can hold.
inline constexpr int max_games = 8;

/// A collection of games, played through Game pointers.
///
/// The arcade owns the games it is given and deletes them in its destructor.
class Arcade {
public:
  // Lab 13: write src/arcade.cpp and add it to CMakeLists.txt.
  Arcade();

  /// Deletes every game the arcade owns.
  ~Arcade();

  Arcade(const Arcade &) = delete;
  Arcade &operator=(const Arcade &) = delete;

  /// Add a game. The arcade takes ownership of @p game.
  /// @param game a game allocated with new; if the arcade is full it is
  /// deleted immediately
  void add(Game *game);

  /// Show the menu, play the chosen games, and print each score afterwards.
  /// Returns when the player chooses 0 or the input ends.
  void run();

private:
  Game *m_games[max_games];
  int m_count;
};

#endif // ARCADE_ARCADE_H
