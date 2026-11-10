#ifndef ARCADE_DIRECTION_H
#define ARCADE_DIRECTION_H

#include <string>

/// @file direction.h
/// @brief The four compass directions used by the Dungeon.

/// A compass direction. The enumerator values (0 to 3) index a room's exits.
enum class Direction {
  north, ///< up the map
  east,  ///< to the right
  south, ///< down the map
  west   ///< to the left
};

/// The number of directions.
inline constexpr int direction_count = 4;

/// The direction pointing the other way.
/// @param d a direction
/// @return north for south, east for west, and so on
Direction opposite(Direction d);

/// The lowercase word for a direction.
/// @param d a direction
/// @return "north", "east", "south", or "west"
std::string direction_name(Direction d);

/// Convert text to a direction.
/// @param text "north", "n", "east", "e", "south", "s", "west", or "w"
/// @param d receives the direction when the function returns true
/// @return true if @p text names a direction
bool parse_direction(const std::string &text, Direction &d);

#endif // ARCADE_DIRECTION_H
