#include <gtest/gtest.h>

#include "dungeon.h"
#include "hangman.h"
#include "minesweeper.h"

TEST(ScoreTest, HangmanScoreUsesMissesLeftAndWordLength) {
  EXPECT_EQ(hangman_score(6, 7), 6 * 10 + 7 * 5);
  EXPECT_EQ(hangman_score(1, 12), 1 * 10 + 12 * 5);
}

TEST(ScoreTest, DungeonScoreUsesItemsAndHealth) {
  EXPECT_EQ(dungeon_score(0, 100), 100);
  EXPECT_EQ(dungeon_score(3, 60), 90);
}

TEST(ScoreTest, MinesweeperScoreAddsABonusForAWin) {
  EXPECT_EQ(minesweeper_score(20, false), 20);
  EXPECT_EQ(minesweeper_score(54, true), 154);
}
