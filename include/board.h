#ifndef ARCADE_BOARD_H
#define ARCADE_BOARD_H

#include <random>

/// @file board.h
/// @brief The Minesweeper board.

/// One square of the board.
struct Cell {
  bool mine = false;     ///< true if a mine is buried here
  bool revealed = false; ///< true once the player has uncovered the square
  bool flagged =
      false;        ///< true if the player has marked it as a suspected mine
  int adjacent = 0; ///< how many of the eight neighbors hold mines
};

/// What happened when the player tried to reveal a square.
enum class RevealResult {
  ok,   ///< the square (and any neighbors that opened with it) is now revealed
  mine, ///< the square held a mine
  already_revealed, ///< nothing to do: the square was already open
  flagged,          ///< refused: the square is flagged
  out_of_bounds     ///< the position is not on the board
};

/// A rows-by-columns grid of cells in dynamically allocated memory.
///
/// The board owns its memory: the constructor allocates and the destructor
/// frees. Copying is disabled because a copy of a whole board has no use in
/// the game.
class Board {
public:
  /// Allocate an empty board.
  /// @param rows number of rows (at least 1)
  /// @param cols number of columns (at least 1)
  /// @param mine_count how many mines place_mines() should bury
  Board(int rows, int cols, int mine_count);

  /// Free all the memory the board owns.
  ~Board();

  /// Copying a board is not allowed.
  Board(const Board &) = delete;

  /// Assigning one board to another is not allowed.
  Board &operator=(const Board &) = delete;

  /// @return the number of rows
  int rows() const;

  /// @return the number of columns
  int cols() const;

  /// @return the number of mines the board was built for
  int mine_count() const;

  /// @param row a row number
  /// @param col a column number
  /// @return true if (row, col) is on the board
  bool in_bounds(int row, int col) const;

  /// Read a cell. The position must be on the board.
  /// @param row a row number
  /// @param col a column number
  /// @return the cell at that position
  const Cell &cell(int row, int col) const;

  /// Bury mine_count() mines on distinct random squares, then count neighbors.
  /// @param gen the random number generator to draw from
  void place_mines(std::mt19937 &gen);

  /// Bury a mine at a chosen square (used by tests). Does not update counts.
  /// @param row a row number
  /// @param col a column number
  void set_mine(int row, int col);

  /// Count the mines among the eight neighbors of a square.
  /// @param row a row number
  /// @param col a column number
  /// @return a number from 0 to 8; the square itself is not counted
  int count_adjacent(int row, int col) const;

  /// Fill in the adjacent count of every cell.
  void compute_adjacent();

  /// Print the board with row and column headers.
  /// @param reveal_all true to show every square, false to show only revealed
  /// ones
  void print(bool reveal_all) const;

  /// Uncover a square. If it has no neighboring mines, uncover its
  /// neighbors too, and so on.
  /// @param row a row number
  /// @param col a column number
  /// @return what happened
  RevealResult reveal(int row, int col);

  /// Flag or unflag an unrevealed square. Does nothing on a revealed square.
  /// @param row a row number
  /// @param col a column number
  void toggle_flag(int row, int col);

  /// @return true if every square without a mine has been revealed
  bool is_won() const;

  /// @return the number of revealed squares
  int revealed_count() const;

private:
  void reveal_from(int row, int col);

  Cell **m_cells;
  int m_rows;
  int m_cols;
  int m_mine_count;
};

#endif // ARCADE_BOARD_H
