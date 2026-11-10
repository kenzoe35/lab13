// Instructor checks for the game rules: dealer_turn, settle, payout.
// Uses an unshuffled Deck, which deals AC 2C 3C 4C 5C ... in that order.

#include <gtest/gtest.h>

#include <string>

#include "blackjack.h"
#include "card.h"
#include "deck.h"
#include "hand.h"

namespace {

Hand hand_from(const std::string &text) {
  Hand hand;
  int suit = 0;
  for (char c : text) {
    int rank = 0;
    if (c == 'A') {
      rank = 1;
    } else if (c >= '2' && c <= '9') {
      rank = c - '0';
    } else if (c == 'T') {
      rank = 10;
    } else if (c == 'J') {
      rank = 11;
    } else if (c == 'Q') {
      rank = 12;
    } else if (c == 'K') {
      rank = 13;
    }
    if (rank != 0) {
      hand += Card{rank, static_cast<Suit>(suit % 4)};
      ++suit;
    }
  }
  return hand;
}

} // namespace

TEST(DealerTurnTest, DrawsBelowSeventeen) {
  Deck deck;
  Hand dealer = hand_from("T 6");
  dealer_turn(dealer, deck);
  EXPECT_EQ(dealer.count(), 3); // drew the ace of clubs
  EXPECT_EQ(dealer.value(), 17);
  EXPECT_EQ(deck.remaining(), 51);
}

TEST(DealerTurnTest, StandsOnHardSeventeen) {
  Deck deck;
  Hand dealer = hand_from("T 7");
  dealer_turn(dealer, deck);
  EXPECT_EQ(dealer.count(), 2);
  EXPECT_EQ(deck.remaining(), 52);
}

TEST(DealerTurnTest, StandsOnSoftSeventeen) {
  Deck deck;
  Hand dealer = hand_from("A 6");
  dealer_turn(dealer, deck);
  EXPECT_EQ(dealer.count(), 2);
  EXPECT_EQ(dealer.value(), 17);
}

TEST(DealerTurnTest, KeepsDrawingUntilSeventeenOrMore) {
  Deck deck;
  Hand dealer = hand_from("2 3"); // 5, then draws A (16), 2 (18)
  dealer_turn(dealer, deck);
  EXPECT_EQ(dealer.count(), 4);
  EXPECT_EQ(dealer.value(), 18);
  EXPECT_EQ(deck.remaining(), 50);
}

TEST(SettleTest, PlayerBustLosesEvenIfDealerBusts) {
  EXPECT_EQ(settle(hand_from("T T 5"), hand_from("T 6 T")),
            Outcome::player_loss);
}

TEST(SettleTest, BlackjackBeatsTwentyOneInThreeCards) {
  EXPECT_EQ(settle(hand_from("A K"), hand_from("7 7 7")),
            Outcome::player_blackjack);
  EXPECT_EQ(settle(hand_from("7 7 7"), hand_from("A K")), Outcome::player_loss);
}

TEST(SettleTest, TwoBlackjacksPush) {
  EXPECT_EQ(settle(hand_from("A K"), hand_from("A Q")), Outcome::push);
}

TEST(SettleTest, ComparesTotals) {
  EXPECT_EQ(settle(hand_from("T 9"), hand_from("T 8")), Outcome::player_win);
  EXPECT_EQ(settle(hand_from("T 8"), hand_from("T 9")), Outcome::player_loss);
  EXPECT_EQ(settle(hand_from("T 8"), hand_from("9 9")), Outcome::push);
}

TEST(SettleTest, DealerBustPaysThePlayer) {
  EXPECT_EQ(settle(hand_from("T 2"), hand_from("T 6 K")), Outcome::player_win);
}

TEST(PayoutTest, ThreeToTwoOnBlackjack) {
  EXPECT_EQ(payout(Outcome::player_blackjack, 10), 15);
  EXPECT_EQ(payout(Outcome::player_win, 10), 10);
  EXPECT_EQ(payout(Outcome::push, 10), 0);
  EXPECT_EQ(payout(Outcome::player_loss, 10), -10);
}
