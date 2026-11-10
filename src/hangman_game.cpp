#include "hangman_game.h"

#include "hangman.h"

Hangman::Hangman() : Game{"Hangman"}, m_times_played{0} {}

void Hangman::play() {
  set_score(play_hangman());
  ++m_times_played;
}

int Hangman::times_played() const { return m_times_played; }
