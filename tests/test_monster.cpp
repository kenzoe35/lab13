#include <gtest/gtest.h>

#include <string>

#include "goblin.h"
#include "room.h"
#include "troll.h"

TEST(MonsterTest, DamageDependsOnTheKindThroughAMonsterPointer) {
  Goblin goblin;
  Troll troll;
  const Monster *monsters[2] = {&goblin, &troll};
  EXPECT_EQ(monsters[0]->attack_damage(), 3);
  EXPECT_EQ(monsters[1]->attack_damage(), 6);
}

TEST(MonsterTest, TakeDamageStopsAtZero) {
  Goblin goblin;
  EXPECT_FALSE(goblin.is_dead());
  goblin.take_damage(5);
  EXPECT_FALSE(goblin.is_dead());
  goblin.take_damage(1000);
  EXPECT_TRUE(goblin.is_dead());
}

TEST(MonsterTest, TrollOverridesDescribe) {
  const Goblin goblin;
  const Troll troll;
  const Monster &g = goblin;
  const Monster &t = troll;
  EXPECT_NE(g.describe(), t.describe());
  EXPECT_NE(g.describe().find("Goblin"), std::string::npos);
}

TEST(MonsterTest, RoomOwnsItsMonster) {
  Room room{"Cellar", "Damp."};
  EXPECT_EQ(room.monster(), nullptr);
  room.set_monster(new Goblin{});
  ASSERT_NE(room.monster(), nullptr);
  EXPECT_EQ(room.monster()->name(), "Goblin");
  room.set_monster(new Troll{}); // the Goblin is deleted, not leaked
  EXPECT_EQ(room.monster()->name(), "Troll");
}
