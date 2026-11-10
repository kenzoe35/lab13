#ifndef ARCADE_ROOM_H
#define ARCADE_ROOM_H

#include <string>

#include "direction.h"
#include "item.h"

/// @file room.h
/// @brief A place in the Dungeon.

/// The most items a room can hold.
inline constexpr int max_room_items = 3;

/// A room with up to four exits and up to three items.
///
/// Exits are pointers to other rooms; a Room does not own the rooms it links
/// to, so the rooms must outlive any pointer to them.
class Room {
public:
  /// Make a room with no exits and no items.
  /// @param name short name shown to the player
  /// @param description one or two sentences shown by `look`
  Room(std::string name, std::string description);

  /// @return the room's name
  const std::string &name() const;

  /// @return the room's description
  const std::string &description() const;

  /// Link this room to another in one direction only.
  /// @param d the direction of the exit
  /// @param other the room on the other side (not owned)
  void connect(Direction d, Room *other);

  /// @param d a direction
  /// @return the room through that exit, or nullptr if there is none
  Room *exit(Direction d) const;

  /// @param d a direction
  /// @return true if there is an exit that way
  bool has_exit(Direction d) const;

  /// Add an item to the floor of the room.
  /// @param item the item to copy into the room
  /// @return false if the room already holds the maximum number of items
  bool add_item(const Item &item);

  /// Take an item off the floor by name.
  /// @param name the item to look for
  /// @param out receives a copy of the item when the function returns true
  /// @return true if an item with that name was in the room
  bool remove_item(const std::string &name, Item &out);

  /// Print the items on the floor, or a message if there are none.
  void list_items() const;

  /// Make this room a trap.
  /// @param damage health lost by a player who enters (0 means no trap)
  void set_trap_damage(int damage);

  /// @return health lost by a player who enters this room
  int trap_damage() const;

private:
  std::string m_name;
  std::string m_description;
  Room *m_exits[direction_count];
  Item m_items[max_room_items];
  int m_item_count;
  int m_trap_damage;
};

#endif // ARCADE_ROOM_H
