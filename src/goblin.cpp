#include "goblin.h"

Goblin::Goblin()
	: Monster("Goblin", 15) {
}

int Goblin::attack_damage() const {
	return 3; // Goblins do 3 damage per hit
}

std::string Goblin::describe() const {
	return "A sneaky Goblin";
}