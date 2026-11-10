// Minesweeper tests. None of them depends on random placement: each one builds
// a known board with set_mine().

#include <gtest/gtest.h>

#include "board.h"

namespace {

// Mines at (0,0) and (0,2) on a 3x3 board. Expected counts:
//   * 2 *        row 0:  mine, 2, mine
//   2 2 2        row 1:  2, 2, 2
//   0 0 0        row 2:  0, 0, 0
void build_known_layout(Board& board)
{
    board.set_mine(0, 0);
    board.set_mine(0, 2);
    board.compute_adjacent();
}

}  // namespace

TEST(BoardTest, AdjacentCountsOnKnownLayout)
{
    Board board{3, 3, 2};
    build_known_layout(board);
    EXPECT_EQ(board.count_adjacent(0, 1), 2);
    EXPECT_EQ(board.count_adjacent(1, 1), 2);
    EXPECT_EQ(board.count_adjacent(1, 0), 1);
    EXPECT_EQ(board.count_adjacent(2, 1), 0);
    EXPECT_EQ(board.cell(1, 2).adjacent, 1);
}

TEST(BoardTest, FlagTogglesOnAndOff)
{
    Board board{3, 3, 0};
    EXPECT_FALSE(board.cell(1, 1).flagged);
    board.toggle_flag(1, 1);
    EXPECT_TRUE(board.cell(1, 1).flagged);
    board.toggle_flag(1, 1);
    EXPECT_FALSE(board.cell(1, 1).flagged);
}

TEST(BoardTest, WinOnTwoByTwoBoard)
{
    Board board{2, 2, 1};
    board.set_mine(0, 0);
    board.compute_adjacent();
    EXPECT_FALSE(board.is_won());
    EXPECT_EQ(board.reveal(0, 1), RevealResult::ok);
    EXPECT_EQ(board.reveal(1, 0), RevealResult::ok);
    EXPECT_FALSE(board.is_won());
    EXPECT_EQ(board.reveal(1, 1), RevealResult::ok);
    EXPECT_TRUE(board.is_won());
    EXPECT_EQ(board.revealed_count(), 3);
}

TEST(BoardTest, RevealingAMineReportsIt)
{
    Board board{3, 3, 1};
    board.set_mine(1, 1);
    board.compute_adjacent();
    EXPECT_EQ(board.reveal(1, 1), RevealResult::mine);
    EXPECT_FALSE(board.is_won());
}

TEST(BoardTest, FloodFillOpensWholeEmptyRegion)
{
    // One mine in the corner of a 5x5 board: clicking the opposite corner
    // opens every square except the mine.
    Board board{5, 5, 1};
    board.set_mine(0, 0);
    board.compute_adjacent();
    EXPECT_EQ(board.reveal(4, 4), RevealResult::ok);
    EXPECT_EQ(board.revealed_count(), 24);
    EXPECT_FALSE(board.cell(0, 0).revealed);
    EXPECT_TRUE(board.is_won());
}

TEST(BoardTest, FlaggedSquaresAreNotRevealed)
{
    Board board{3, 3, 1};
    board.set_mine(0, 0);
    board.compute_adjacent();
    board.toggle_flag(2, 2);
    EXPECT_EQ(board.reveal(2, 2), RevealResult::flagged);
    EXPECT_FALSE(board.cell(2, 2).revealed);
    EXPECT_EQ(board.reveal(5, 5), RevealResult::out_of_bounds);
}
