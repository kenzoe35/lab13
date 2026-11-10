#include "direction.h"

Direction opposite(Direction d) {
  switch (d) {
  case Direction::north:
    return Direction::south;
  case Direction::east:
    return Direction::west;
  case Direction::south:
    return Direction::north;
  case Direction::west:
    return Direction::east;
  }
  return d; // unreachable; keeps the compiler quiet
}

std::string direction_name(Direction d) {
  switch (d) {
  case Direction::north:
    return "north";
  case Direction::east:
    return "east";
  case Direction::south:
    return "south";
  case Direction::west:
    return "west";
  }
  return "";
}

bool parse_direction(const std::string &text, Direction &d) {
  if (text == "north" || text == "n") {
    d = Direction::north;
  } else if (text == "east" || text == "e") {
    d = Direction::east;
  } else if (text == "south" || text == "s") {
    d = Direction::south;
  } else if (text == "west" || text == "w") {
    d = Direction::west;
  } else {
    return false;
  }
  return true;
}
