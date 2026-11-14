#pragma once

#include "monster.h"

class Goblin : public Monster {
public:
	// Constructor that initializes the Goblin with a name and health.
	Goblin();

	// Override original method to return the damage to Goblin does with one hit
	int attack_damage() const override;

	// Override original method to return a specific description of the Goblin
	std::string describe() const override;
};