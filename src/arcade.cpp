#include "arcade.h"

Arcade::Arcade() : m_count(0) {
	// TODO: Allocate games and initialize m_count to 0
	for (int i = 0; i < max_games; ++i) {
		m_games[i] = nullptr;
	}
}
Arcade::~Arcade() {
	// TODO: Delete every game the arcade owns
	for (int i = 0; i < max_games; ++i) {
		delete m_games[i];
	}
}

void add(Game* game) {
	// TODO: Take ownership of game; if full, delete it immediately; otherwise add to m_games and update count
}


void run() {
	// TODO: Show menu, play chosen games, print each score afterwards, and return on 0 or end of input
}