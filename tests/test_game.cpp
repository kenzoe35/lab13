#include <gtest/gtest.h>

#include "blackjack_game.h"
#include "dungeon_game.h"
#include "hangman_game.h"
#include "minesweeper_game.h"

TEST(GameTest, TitlesComeFromTheDerivedConstructors) {
  EXPECT_EQ(Hangman{}.title(), "Hangman");
  EXPECT_EQ(Dungeon{}.title(), "Dungeon");
  EXPECT_EQ(Blackjack{}.title(), "Blackjack");
  EXPECT_EQ(Minesweeper{}.title(), "Minesweeper");
}

TEST(GameTest, NewGamesHaveScoreZeroAndNoPlays) {
  const Hangman h;
  EXPECT_EQ(h.last_score(), 0);
  EXPECT_EQ(h.times_played(), 0);
}

TEST(GameTest, DerivedIsAGame) {
  const Minesweeper m;
  const Game &g{m};
  EXPECT_EQ(g.title(), "Minesweeper");
}
