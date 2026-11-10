cmake_minimum_required(VERSION 3.20)
project(arcade LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# AddressSanitizer: cmake -S . -B build-asan -DENABLE_ASAN=ON
option(ENABLE_ASAN "Build with AddressSanitizer" OFF)

add_compile_options(-Wall -Wextra)
if(ENABLE_ASAN)
    add_compile_options(-fsanitize=address -fno-omit-frame-pointer -g)
    add_link_options(-fsanitize=address)
endif()

add_library(arcade_lib STATIC
    src/blackjack.cpp
    src/blackjack_game.cpp
    src/board.cpp
    src/card.cpp
    src/deck.cpp
    src/direction.cpp
    src/dungeon.cpp
    src/dungeon_game.cpp
    src/game.cpp
    src/hand.cpp
    src/hangman.cpp
    src/hangman_game.cpp
    src/input.cpp
    src/item.cpp
    src/minesweeper.cpp
    src/minesweeper_game.cpp
    src/player.cpp
    src/room.cpp
)
target_include_directories(arcade_lib PUBLIC include)

add_executable(arcade app/main.cpp)
target_link_libraries(arcade PRIVATE arcade_lib)

# Tests (GoogleTest)
include(CTest)
if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

# Documentation:    cmake --build build --target docs
find_package(Doxygen QUIET)
if(DOXYGEN_FOUND)
    add_custom_target(docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Generating Doxygen Documentation"
        VERBATIM)
endif()
