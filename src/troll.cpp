#include "troll.h"

Troll::Troll()
	: Monster("Troll", 25) {
}

int Troll::attack_damage() const {
	return 6; // Trolls do 6 damage per hit
}

std::string Troll::describe() const {
	return "A massive, lumbering Troll";
}