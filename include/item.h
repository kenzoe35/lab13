#ifndef ARCADE_ITEM_H
#define ARCADE_ITEM_H

#include <string>

/// @file item.h
/// @brief Things the player can find and carry in the Dungeon.

/// The most items a player can hold.
inline constexpr int max_items = 10;

/// The most weight a player can carry.
inline constexpr int max_carry_weight = 10;

/// A named object with a weight.
///
/// A default-constructed Item is "empty": it stands for "no item" and has an
/// empty name. Only items made with the three-argument constructor are counted
/// by Item::count().
class Item {
public:
  /// Make an empty item.
  Item();

  /// Make a real item.
  /// @param name what the item is called
  /// @param description one line shown when the item is examined
  /// @param weight how heavy the item is
  Item(std::string name, std::string description, int weight);

  /// @return the item's name (empty for an empty item)
  const std::string &name() const;

  /// @return the item's description
  const std::string &description() const;

  /// @return the item's weight (0 for an empty item)
  int weight() const;

  /// @return true if this item stands for "no item"
  bool is_empty() const;

  /// How many real items have been constructed since the program started.
  /// Copies are not counted.
  /// @return the number of non-empty items created with the three-argument
  /// constructor
  static int count();

private:
  std::string m_name;
  std::string m_description;
  int m_weight;

  static int m_count;
};

#endif // ARCADE_ITEM_H
