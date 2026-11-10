#include "blackjack.h"

#include <iostream>
#include <random>
#include <string>

#include "card.h"
#include "deck.h"
#include "hand.h"
#include "input.h"

namespace {

inline constexpr int starting_bankroll = 100;
inline constexpr int fixed_bet = 10;
inline constexpr int reshuffle_below = 15;
inline constexpr int dealer_stands_at = 17;

/// Replace the deck with a new shuffled one.
void new_shuffled_deck(Deck &deck, std::mt19937 &gen) {
  deck = Deck{};
  deck.shuffle(gen);
}

/// Take the top card, starting a fresh deck first if the old one ran out.
Card draw(Deck &deck, std::mt19937 &gen) {
  if (deck.empty()) {
    new_shuffled_deck(deck, gen);
  }
  return deck.deal();
}

void show_hands(const Hand &player, const Hand &dealer, bool hide_hole_card) {
  if (hide_hole_card) {
    std::cout << "Dealer shows: " << dealer[0] << "\n";
  } else {
    std::cout << "Dealer has:   " << dealer << " (" << dealer.value() << ")\n";
  }
  std::cout << "You have:     " << player << " (" << player.value() << ")\n";
}

/// Ask hit or stand until the player stands, busts, or reaches 21.
/// @return false if input ended
bool player_turn(Hand &player, const Hand &dealer, Deck &deck,
                 std::mt19937 &gen) {
  std::string line;
  while (!player.is_bust() && player.value() < 21) {
    if (!prompt_line("(h)it or (s)tand: ", line)) {
      return false;
    }
    if (line == "h") {
      player += draw(deck, gen);
      show_hands(player, dealer, true);
    } else if (line == "s") {
      return true;
    } else {
      std::cout << "Type h or s.\n";
    }
  }
  return true;
}

void announce(Outcome outcome, int change) {
  switch (outcome) {
  case Outcome::player_blackjack:
    std::cout << "Blackjack! You win " << change << ".\n";
    break;
  case Outcome::player_win:
    std::cout << "You win " << change << ".\n";
    break;
  case Outcome::push:
    std::cout << "Push. Your bet is returned.\n";
    break;
  case Outcome::player_loss:
    std::cout << "You lose " << -change << ".\n";
    break;
  }
}

} // namespace

void dealer_turn(Hand &dealer, Deck &deck) {
  while (dealer.value() < dealer_stands_at && !deck.empty()) {
    dealer += deck.deal();
  }
}

Outcome settle(const Hand &player, const Hand &dealer) {
  if (player.is_bust()) {
    return Outcome::player_loss;
  }
  if (player.is_blackjack() && dealer.is_blackjack()) {
    return Outcome::push;
  }
  if (player.is_blackjack()) {
    return Outcome::player_blackjack;
  }
  if (dealer.is_blackjack()) {
    return Outcome::player_loss;
  }
  if (dealer.is_bust() || player.value() > dealer.value()) {
    return Outcome::player_win;
  }
  if (player.value() == dealer.value()) {
    return Outcome::push;
  }
  return Outcome::player_loss;
}

int payout(Outcome outcome, int bet) {
  switch (outcome) {
  case Outcome::player_blackjack:
    return bet * 3 / 2;
  case Outcome::player_win:
    return bet;
  case Outcome::push:
    return 0;
  case Outcome::player_loss:
    return -bet;
  }
  return 0;
}

int play_blackjack() {
  std::random_device device;
  std::mt19937 gen{device()};

  Deck deck;
  deck.shuffle(gen);
  Hand player;
  Hand dealer;
  int bankroll = starting_bankroll;
  std::string line;

  std::cout << "\n--- Blackjack ---\n";
  while (bankroll > 0) {
    std::cout << "\nBankroll: " << bankroll << "\n";
    if (!prompt_line("Press Enter to deal, or q to quit: ", line) ||
        line == "q") {
      break;
    }
    if (deck.remaining() < reshuffle_below) {
      std::cout << "Shuffling a new deck.\n";
      new_shuffled_deck(deck, gen);
    }

    const int bet = fixed_bet < bankroll ? fixed_bet : bankroll;
    player.clear();
    dealer.clear();
    player += deck.deal();
    dealer += deck.deal();
    player += deck.deal();
    dealer += deck.deal();
    std::cout << "Bet: " << bet << "\n";
    show_hands(player, dealer, true);

    if (!player.is_blackjack() && !dealer.is_blackjack()) {
      if (!player_turn(player, dealer, deck, gen)) {
        break;
      }
      if (!player.is_bust()) {
        dealer_turn(dealer, deck);
      }
    }
    show_hands(player, dealer, false);

    const Outcome outcome = settle(player, dealer);
    const int change = payout(outcome, bet);
    bankroll += change;
    announce(outcome, change);
  }
  if (bankroll == 0) {
    std::cout << "You are out of money.\n";
  } else {
    std::cout << "You leave with " << bankroll << ".\n";
  }
  return bankroll;
}
