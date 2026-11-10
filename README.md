# Arcade: Week 13 starter (S13)

A text-game arcade in C++20. This is the starting point for **Lab 13: Polymorphism**. It is your Lab 12 solution: four games derived from `Game`, with a non-virtual `play()`. `main` creates the objects directly and prints `last_score()` after each one.

## What is already here

| Part | Files | Notes |
| --- | --- | --- |
| Game hierarchy (finished) | `game.*`, `hangman_game.*`, `dungeon_game.*`, `blackjack_game.*`, `minesweeper_game.*` | `play()` is not virtual yet |
| The games | `hangman.*`, `dungeon.*`, `blackjack.*`, `minesweeper.*` and their helper classes | The `play_*` functions |
| **Arcade** | `include/arcade.h` | Signatures are given. You write `src/arcade.cpp`. |
| **Monster** | `include/monster.h` | The abstract `Monster` is declared. You write `src/monster.cpp`, `goblin.*`, `troll.*`. |
| Combat | `src/dungeon.cpp` | `fight()` and `meet_monster()` have a description and a TODO |
| Tests | `tests/` | `test_arcade.cpp` and `test_monster.cpp` build automatically once the files they need exist |
| Notes to fill in | `POLYMORPHISM_NOTES.md`, `GDB_LOG.md` | |

## File names

The tests expect these files, so use these names:

- `src/arcade.cpp`
- `src/monster.cpp`, `include/goblin.h`, `src/goblin.cpp`, `include/troll.h`, `src/troll.cpp`

Classes: `Goblin` (3 damage, 8 health) and `Troll` (6 damage, 20 health). Each has a default constructor. Add every new `.cpp` file to the `arcade_lib` list in `CMakeLists.txt`.

## Build and run

```
cmake -S . -B build
cmake --build build
./build/arcade
cd build && ctest --output-on-failure
```

AddressSanitizer, in a separate folder:

```
cmake -S . -B build-asan -DENABLE_ASAN=ON
cmake --build build-asan
./build-asan/arcade
```

## Rules

- No warnings under `-Wall -Wextra`.
- Allowed headers: `<iostream>`, `<iomanip>`, `<string>`, `<fstream>`, `<stdexcept>`, `<random>`. No standard containers, no `<algorithm>`, no `using namespace std;`.
- Naming: `underscore_separated` functions and variables, `Capitalized` types, private data members start with `m_`, enumerators are lowercase, no ALL_CAPS constants.
- Conventional Commits, composed in the editor (not `-m`).
