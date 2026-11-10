#ifndef ARCADE_PLAYER_H
#define ARCADE_PLAYER_H

#include <string>

#include "direction.h"
#include "item.h"
#include "room.h"

/// @file player.h
/// @brief The adventurer in the Dungeon.

/// The player's starting (and maximum) health.
inline constexpr int starting_health = 100;

/// An adventurer who stands in a room, carries items, and has health.
class Player {
public:
  /// Make a player.
  /// @param name the player's name
  /// @param start the room the player starts in (not owned)
  Player(std::string name, Room *start);

  /// @return the room the player is standing in
  Room *location() const;

  /// Try to walk through an exit of the current room.
  /// @param d the direction to walk
  /// @return true if there was an exit and the player moved
  bool move(Direction d);

  /// @return the player's health, never below 0
  int health() const;

  /// Reduce health, stopping at 0.
  /// @param amount how much health to lose
  void take_damage(int amount);

  /// @return true while health is above 0
  bool is_alive() const;

  /// Change the player's name.
  /// @param name the new name
  /// @return this player, so calls can be chained
  Player &set_name(const std::string &name);

  /// @return the player's name
  const std::string &name() const;

  /// Pick an item up from a room.
  /// @param room the room to take from
  /// @param item_name the name of the item
  /// @return false if the item is not there, the inventory is full, or it is
  /// too heavy
  bool take(Room &room, const std::string &item_name);

  /// Put an item down in a room.
  /// @param room the room to drop into
  /// @param item_name the name of the item
  /// @return false if the player is not carrying it or the room is full
  bool drop(Room &room, const std::string &item_name);

  /// Print everything the player carries and the total weight.
  void show_inventory() const;

  /// @return the number of items carried
  int inventory_count() const;

  /// @return the total weight of the items carried
  int carried_weight() const;

private:
  std::string m_name;
  Room *m_location;
  int m_health;
  Item m_inventory[max_items];
  int m_inventory_count;
};

#endif // ARCADE_PLAYER_H
