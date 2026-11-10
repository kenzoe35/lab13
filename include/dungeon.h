#ifndef ARCADE_DUNGEON_H
#define ARCADE_DUNGEON_H

#include "direction.h"
#include "room.h"

/// @file dungeon.h
/// @brief The Dungeon game: six rooms, items, a trap, and text commands.

/// Link two rooms in both directions.
/// @param a the first room
/// @param d the direction from @p a to @p b
/// @param b the second room; it gets the opposite exit back to @p a
void connect_rooms(Room &a, Direction d, Room &b);

/// The score for a Dungeon run.
/// @param items_collected how many items the player is carrying
/// @param health the player's health
/// @return 10 * items_collected + health
int dungeon_score(int items_collected, int health);

/// Play the Dungeon until the player quits or dies.
/// @return dungeon_score() of the player when they quit, or 0 if the player died
int play_dungeon();

#endif // ARCADE_DUNGEON_H
