#include "player.h"

#include <iostream>

Player::Player(std::string name, Room *start)
    : m_name{name}, m_location{start}, m_health{starting_health}, m_inventory{},
      m_inventory_count{0} {}

Room *Player::location() const { return m_location; }

bool Player::move(Direction d) {
  Room *next = m_location->exit(d);
  if (next == nullptr) {
    return false;
  }
  m_location = next;
  return true;
}

int Player::health() const { return m_health; }

void Player::take_damage(int amount) {
  m_health -= amount;
  if (m_health < 0) {
    m_health = 0;
  }
}

bool Player::is_alive() const { return m_health > 0; }

Player &Player::set_name(const std::string &name) {
  m_name = name;
  return *this;
}

const std::string &Player::name() const { return m_name; }

bool Player::take(Room &room, const std::string &item_name) {
  if (m_inventory_count == max_items) {
    return false;
  }
  Item found;
  if (!room.remove_item(item_name, found)) {
    return false;
  }
  if (carried_weight() + found.weight() > max_carry_weight) {
    room.add_item(found); // put it back; the room had space a moment ago
    return false;
  }
  m_inventory[m_inventory_count] = found;
  ++m_inventory_count;
  return true;
}

bool Player::drop(Room &room, const std::string &item_name) {
  for (int i = 0; i < m_inventory_count; ++i) {
    if (m_inventory[i].name() == item_name) {
      if (!room.add_item(m_inventory[i])) {
        return false;
      }
      for (int j = i; j < m_inventory_count - 1; ++j) {
        m_inventory[j] = m_inventory[j + 1];
      }
      --m_inventory_count;
      m_inventory[m_inventory_count] = Item{};
      return true;
    }
  }
  return false;
}

void Player::show_inventory() const {
  if (m_inventory_count == 0) {
    std::cout << "You are carrying nothing.\n";
    return;
  }
  std::cout << "You are carrying:\n";
  for (int i = 0; i < m_inventory_count; ++i) {
    std::cout << "  " << m_inventory[i].name() << " (weight "
              << m_inventory[i].weight() << ")\n";
  }
  std::cout << "Total weight: " << carried_weight() << " of "
            << max_carry_weight << "\n";
}

int Player::inventory_count() const { return m_inventory_count; }

int Player::carried_weight() const {
  int total = 0;
  for (int i = 0; i < m_inventory_count; ++i) {
    total += m_inventory[i].weight();
  }
  return total;
}
