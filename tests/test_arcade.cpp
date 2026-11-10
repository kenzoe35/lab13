#include <gtest/gtest.h>

#include <iostream>
#include <sstream>
#include <string>

#include "arcade.h"

namespace {

int live_fakes = 0;
int plays = 0;

class FakeGame : public Game {
public:
  explicit FakeGame(int score) : Game{"Fake"}, m_score{score} { ++live_fakes; }
  ~FakeGame() override { --live_fakes; }
  void play() override {
    ++plays;
    set_score(m_score);
  }

private:
  int m_score;
};

/// Runs an arcade with canned input and captures what it prints.
std::string run_with(Arcade &arcade, const std::string &input) {
  std::istringstream in{input};
  std::ostringstream out;
  std::streambuf *old_in = std::cin.rdbuf(in.rdbuf());
  std::streambuf *old_out = std::cout.rdbuf(out.rdbuf());
  arcade.run();
  std::cin.rdbuf(old_in);
  std::cout.rdbuf(old_out);
  return out.str();
}

} // namespace

TEST(ArcadeTest, DestructorDeletesEveryGameThroughTheBasePointer) {
  live_fakes = 0;
  {
    Arcade arcade;
    arcade.add(new FakeGame{1});
    arcade.add(new FakeGame{2});
    EXPECT_EQ(live_fakes, 2);
  }
  EXPECT_EQ(live_fakes, 0);
}

TEST(ArcadeTest, RunPlaysTheChosenGameAndPrintsItsScore) {
  plays = 0;
  Arcade arcade;
  arcade.add(new FakeGame{42});
  const std::string output = run_with(arcade, "1\n0\n");
  EXPECT_EQ(plays, 1);
  EXPECT_NE(output.find("1. Fake"), std::string::npos);
  EXPECT_NE(output.find("score: 42"), std::string::npos);
}

TEST(ArcadeTest, BadChoicesDoNotPlayAnything) {
  plays = 0;
  Arcade arcade;
  arcade.add(new FakeGame{1});
  run_with(arcade, "7\nabc\n\n0\n");
  EXPECT_EQ(plays, 0);
}

TEST(ArcadeTest, RunEndsWhenInputEnds) {
  Arcade arcade;
  arcade.add(new FakeGame{1});
  run_with(arcade, "");
  SUCCEED();
}

TEST(ArcadeTest, AddingMoreThanMaxGamesDoesNotLeakOrCrash) {
  live_fakes = 0;
  {
    Arcade arcade;
    for (int i = 0; i < max_games + 2; ++i) {
      arcade.add(new FakeGame{i});
    }
    EXPECT_EQ(live_fakes, max_games);
  }
  EXPECT_EQ(live_fakes, 0);
}
