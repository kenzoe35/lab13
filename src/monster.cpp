#include "monster.h"

Monster::Monster(std::string name, int health)
	: m_name(std::move(name)), m_health(health) {
}

std::string Monster::describe() const {}

void Monster::take_damage(int amount) {}

bool Monster::is_dead() const {}

const std::string& Monster::name() const {}

