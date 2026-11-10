#ifndef ARCADE_BLACKJACK_H
#define ARCADE_BLACKJACK_H

#include "deck.h"
#include "hand.h"

/// @file blackjack.h
/// @brief Blackjack for one player against the dealer.

/// How a round ended, from the player's side.
enum class Outcome {
  player_blackjack, ///< the player has blackjack and the dealer does not
  player_win, ///< the player's total beats the dealer's, or the dealer busts
  push,       ///< a tie
  player_loss ///< the player busts, or the dealer's hand is better
};

/// The dealer draws until the hand is worth 17 or more. A soft 17 stands.
/// @param dealer the dealer's hand
/// @param deck where the cards come from; the dealer also stops if the deck
/// runs out
void dealer_turn(Hand &dealer, Deck &deck);

/// Decide who won. A player bust loses even if the dealer also busts.
/// @return the outcome from the player's side
Outcome settle(const Hand &player, const Hand &dealer);

/// How much the bankroll changes.
/// @param outcome how the round ended
/// @param bet the amount staked
/// @return +bet * 3 / 2 for a blackjack, +bet for a win, 0 for a push, -bet for
/// a loss
int payout(Outcome outcome, int bet);

/// Play Blackjack from the arcade menu: rounds until the player quits or the
/// bankroll is 0.
/// @return the final bankroll
int play_blackjack();

#endif // ARCADE_BLACKJACK_H
