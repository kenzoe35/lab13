#include "arcade.h"
#include "input.h"
#include <iostream>
#include <string>

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

void Arcade::add(Game *game) {
	// TODO: Take ownership of game; if full, delete it immediately; otherwise add to m_games and update count
	if (m_count >= max_games) {
		delete game;
	}
	else {
		m_games[m_count] = game;
		++m_count;
	}
}


void Arcade::run() {
    std::string line;
    while (true) {
        std::cout << "\n=== ARCADE ===\n";
        for (int i = 0; i < m_count; ++i) {
            std::cout << i + 1 << ". " << m_games[i]->title() << "\n";
        }
        std::cout << "0. Quit\n";

        if (!prompt_line("Choose: ", line)) {
            break; // input ended
        }

        // Convert input string to an integer choice
        int choice = 0;
        try {
            choice = std::stoi(line);
        }
        catch (...) {
            std::cout << "Please enter a valid number.\n";
            continue;
        }

        if (choice == 0) {
            break;
        }

        // Check if the choice matches a valid game index
        if (choice > 0 && choice <= m_count) {
            int index = choice - 1;
            m_games[index]->play();
            std::cout << m_games[index]->title() << " score: " << m_games[index]->last_score() << "\n";
        }
        else {
            std::cout << "Please enter 1-" << m_count << ", or 0 to quit.\n";
        }
    }
}