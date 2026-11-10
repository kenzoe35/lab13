#include "board.h"

#include <iomanip>
#include <iostream>

Board::Board(int rows, int cols, int mine_count)
    : m_cells{nullptr}, m_rows{rows}, m_cols{cols}, m_mine_count{mine_count} {
  m_cells = new Cell *[m_rows];
  for (int r = 0; r < m_rows; ++r) {
    m_cells[r] = new Cell[m_cols];
  }
}

Board::~Board() {
  for (int r = 0; r < m_rows; ++r) {
    delete[] m_cells[r];
  }
  delete[] m_cells;
}

int Board::rows() const { return m_rows; }

int Board::cols() const { return m_cols; }

int Board::mine_count() const { return m_mine_count; }

bool Board::in_bounds(int row, int col) const {
  return row >= 0 && row < m_rows && col >= 0 && col < m_cols;
}

const Cell &Board::cell(int row, int col) const { return m_cells[row][col]; }

void Board::place_mines(std::mt19937 &gen) {
  std::uniform_int_distribution<int> pick_row{0, m_rows - 1};
  std::uniform_int_distribution<int> pick_col{0, m_cols - 1};
  int placed = 0;
  while (placed < m_mine_count) {
    const int r = pick_row(gen);
    const int c = pick_col(gen);
    if (!m_cells[r][c].mine) {
      m_cells[r][c].mine = true;
      ++placed;
    }
  }
  compute_adjacent();
}

void Board::set_mine(int row, int col) { m_cells[row][col].mine = true; }

int Board::count_adjacent(int row, int col) const {
  int count = 0;
  for (int dr = -1; dr <= 1; ++dr) {
    for (int dc = -1; dc <= 1; ++dc) {
      if (dr == 0 && dc == 0) {
        continue;
      }
      const int r = row + dr;
      const int c = col + dc;
      if (in_bounds(r, c) && m_cells[r][c].mine) {
        ++count;
      }
    }
  }
  return count;
}

void Board::compute_adjacent() {
  for (int r = 0; r < m_rows; ++r) {
    for (int c = 0; c < m_cols; ++c) {
      m_cells[r][c].adjacent = count_adjacent(r, c);
    }
  }
}

void Board::print(bool reveal_all) const {
  std::cout << "    ";
  for (int c = 0; c < m_cols; ++c) {
    std::cout << std::setw(2) << c << ' ';
  }
  std::cout << "\n";
  for (int r = 0; r < m_rows; ++r) {
    std::cout << std::setw(3) << r << ' ';
    for (int c = 0; c < m_cols; ++c) {
      const Cell &cell = m_cells[r][c];
      char symbol = '.';
      if (cell.revealed || reveal_all) {
        if (cell.mine) {
          symbol = '*';
        } else {
          symbol = static_cast<char>('0' + cell.adjacent);
        }
      } else if (cell.flagged) {
        symbol = 'F';
      }
      std::cout << std::setw(2) << symbol << ' ';
    }
    std::cout << "\n";
  }
}

RevealResult Board::reveal(int row, int col) {
  if (!in_bounds(row, col)) {
    return RevealResult::out_of_bounds;
  }
  Cell &start = m_cells[row][col];
  if (start.revealed) {
    return RevealResult::already_revealed;
  }
  if (start.flagged) {
    return RevealResult::flagged;
  }
  if (start.mine) {
    start.revealed = true;
    return RevealResult::mine;
  }
  reveal_from(row, col);
  return RevealResult::ok;
}

void Board::reveal_from(int row, int col) {
  // Base cases: off the board, already open, flagged, or a mine.
  if (!in_bounds(row, col)) {
    return;
  }
  Cell &cell = m_cells[row][col];
  if (cell.revealed || cell.flagged || cell.mine) {
    return;
  }
  cell.revealed = true;
  // Base case: a numbered square stops the spread.
  if (cell.adjacent > 0) {
    return;
  }
  // Recursive case: an empty square opens all eight neighbors.
  for (int dr = -1; dr <= 1; ++dr) {
    for (int dc = -1; dc <= 1; ++dc) {
      if (dr != 0 || dc != 0) {
        reveal_from(row + dr, col + dc);
      }
    }
  }
}

void Board::toggle_flag(int row, int col) {
  if (!in_bounds(row, col) || m_cells[row][col].revealed) {
    return;
  }
  m_cells[row][col].flagged = !m_cells[row][col].flagged;
}

bool Board::is_won() const {
  for (int r = 0; r < m_rows; ++r) {
    for (int c = 0; c < m_cols; ++c) {
      if (!m_cells[r][c].mine && !m_cells[r][c].revealed) {
        return false;
      }
    }
  }
  return true;
}

int Board::revealed_count() const {
  int count = 0;
  for (int r = 0; r < m_rows; ++r) {
    for (int c = 0; c < m_cols; ++c) {
      if (m_cells[r][c].revealed) {
        ++count;
      }
    }
  }
  return count;
}
