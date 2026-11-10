#ifndef ARCADE_GAME_H
#define ARCADE_GAME_H

#include <string>

/// @file game.h
/// @brief The base class for every game in the Arcade.

/// A game with a title and the score from its most recent play.
class Game {
public:
  /// @param title the name shown to the player
  explicit Game(std::string title);

  /// @return the game's title
  const std::string &title() const;

  /// @return the score from the most recent play, or 0 if never played
  int last_score() const;

  /// Placeholder. Derived classes define their own play() this week.
  void play();

protected:
  /// Record the score of a finished game.
  /// @param score the score to remember
  void set_score(int score);

  /// Ask "Play again? (y/n)".
  /// @return true if the player answered yes; false on no or end of input
  bool ask_play_again() const;

private:
  std::string m_title;
  int m_last_score;
};

#endif // ARCADE_GAME_H
