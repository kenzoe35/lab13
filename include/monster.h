#ifndef ARCADE_MONSTER_H
#define ARCADE_MONSTER_H

#include <string>

/// @file monster.h
/// @brief The abstract base class for Dungeon monsters.

/// A monster with a name and health. Each kind hits differently.
class Monster {
public:
  /// @param name the monster's name
  /// @param health its starting health
  Monster(std::string name, int health);

  /// Virtual, so deleting a Goblin through a Monster * is safe.
  virtual ~Monster() = default;

  /// @return the damage this monster does with one hit
  virtual int attack_damage() const = 0;

  /// @return a one-line description shown at the start of each round
  virtual std::string describe() const;

  /// Lower the health, stopping at 0.
  /// @param amount the damage taken
  void take_damage(int amount);

  /// @return true when the health has reached 0
  bool is_dead() const;

  /// @return the monster's name
  const std::string &name() const;

private:
  std::string m_name;
  int m_health;
};

#endif // ARCADE_MONSTER_H
