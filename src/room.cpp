#include "room.h"

#include <iostream>

Room::Room(std::string name, std::string description)
    : m_name{name}, m_description{description},
      m_exits{nullptr, nullptr, nullptr, nullptr}, m_items{}, m_item_count{0},
      m_trap_damage{0} {}

const std::string &Room::name() const { return m_name; }

const std::string &Room::description() const { return m_description; }

void Room::connect(Direction d, Room *other) {
  m_exits[static_cast<int>(d)] = other;
}

Room *Room::exit(Direction d) const { return m_exits[static_cast<int>(d)]; }

bool Room::has_exit(Direction d) const { return exit(d) != nullptr; }

bool Room::add_item(const Item &item) {
  if (m_item_count == max_room_items) {
    return false;
  }
  m_items[m_item_count] = item;
  ++m_item_count;
  return true;
}

bool Room::remove_item(const std::string &name, Item &out) {
  for (int i = 0; i < m_item_count; ++i) {
    if (m_items[i].name() == name) {
      out = m_items[i];
      // Close the gap so the items stay packed at the front.
      for (int j = i; j < m_item_count - 1; ++j) {
        m_items[j] = m_items[j + 1];
      }
      --m_item_count;
      m_items[m_item_count] = Item{};
      return true;
    }
  }
  return false;
}

void Room::list_items() const {
  if (m_item_count == 0) {
    std::cout << "There is nothing here.\n";
    return;
  }
  std::cout << "You see:\n";
  for (int i = 0; i < m_item_count; ++i) {
    std::cout << "  " << m_items[i].name() << " (weight " << m_items[i].weight()
              << ")\n";
  }
}

void Room::set_trap_damage(int damage) { m_trap_damage = damage; }

int Room::trap_damage() const { return m_trap_damage; }
