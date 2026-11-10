#include "dungeon.h"

#include <iostream>
#include <string>

#include "input.h"
#include "item.h"
#include "monster.h"
#include "player.h"

void connect_rooms(Room &a, Direction d, Room &b) {
  a.connect(d, &b);
  b.connect(opposite(d), &a);
}

namespace {

void describe_room(const Room &room) {
  std::cout << "\n== " << room.name() << " ==\n" << room.description() << "\n";
  const Direction all[direction_count] = {Direction::north, Direction::east,
                                          Direction::south, Direction::west};
  std::cout << "Exits:";
  for (int i = 0; i < direction_count; ++i) {
    if (room.has_exit(all[i])) {
      std::cout << ' ' << direction_name(all[i]);
    }
  }
  std::cout << "\n";
  room.list_items();
}

void print_help() {
  std::cout << "Commands: go <direction>, look, take <item>, drop <item>, "
               "inventory, help, quit\n";
}

/// Enter the room the player now stands in; returns false if the player died.
bool enter_room(Player &player) {
  const Room &room = *player.location();
  describe_room(room);
  if (room.trap_damage() > 0) {
    std::cout << "A trap springs! You lose " << room.trap_damage()
              << " health.\n";
    player.take_damage(room.trap_damage());
    std::cout << "Health: " << player.health() << "\n";
    if (!player.is_alive()) {
      std::cout << "You have died.\n";
      return false;
    }
  }
  return true;
}

/// How a fight ended.
enum class FightResult { won, fled, died };

/// The damage the player does with one attack.
constexpr int player_attack = 4;

/// The bonus for each monster defeated.
constexpr int monster_bonus = 25;

/// Fight one monster.
///
/// Every round: print monster.describe() and the player's health; read `a`
/// (attack for player_attack damage) or `f` (flee); if the monster is still
/// alive it hits back for monster.attack_damage(). Return FightResult::won
/// when the monster dies, ::fled if the player flees (or input ends), and
/// ::died if the player's health reaches 0.
///
/// Use only the Monster interface. There must be no `if` on the kind of
/// monster.
[[maybe_unused]] FightResult fight(Player &player, Monster &monster) {
  // TODO (Lab 13, Task 4)
  (void)player;
  (void)monster;
  return FightResult::fled;
}

/// Fight the monster in the room the player just entered, if there is a live
/// one. If the player flees, walk back through the exit they came in by:
/// player.move(opposite(came_by)).
/// @param defeated incremented when the player wins a fight
/// @return false if the player died
[[maybe_unused]] bool meet_monster(Player &player, Direction came_by,
                                   int &defeated) {
  // TODO (Lab 13, Task 4): needs Room::monster() from Task 3.
  (void)player;
  (void)came_by;
  (void)defeated;
  return true;
}

} // namespace

int dungeon_score(int items_collected, int health) {
  return 10 * items_collected + health;
}

int play_dungeon() {
  // Layout:   Hall    - Armory   - Library
  //             |          |          |
  //           Cellar  - Spikes   - Treasury
  Room rooms[6] = {
      Room{"Entrance Hall", "A draughty hall. Torches flicker on the walls."},
      Room{"Armory", "Racks of old weapons line the walls."},
      Room{"Library", "Dusty shelves reach the ceiling."},
      Room{"Cellar", "Barrels and cobwebs. It smells damp."},
      Room{"Spike Corridor", "The floor is covered in hidden pressure plates."},
      Room{"Treasury", "A small room that glitters in your lantern light."},
  };
  connect_rooms(rooms[0], Direction::east, rooms[1]);
  connect_rooms(rooms[1], Direction::east, rooms[2]);
  connect_rooms(rooms[3], Direction::east, rooms[4]);
  connect_rooms(rooms[4], Direction::east, rooms[5]);
  connect_rooms(rooms[0], Direction::south, rooms[3]);
  connect_rooms(rooms[1], Direction::south, rooms[4]);
  connect_rooms(rooms[2], Direction::south, rooms[5]);
  rooms[4].set_trap_damage(40);
  // TODO (Lab 13, Task 4): rooms[3].set_monster(new Goblin{});
  //                         rooms[5].set_monster(new Troll{});

  rooms[0].add_item(Item{"lantern", "A brass lantern with oil left in it.", 2});
  rooms[1].add_item(Item{"sword", "A heavy iron sword.", 5});
  rooms[1].add_item(Item{"shield", "A dented wooden shield.", 6});
  rooms[2].add_item(Item{"scroll", "A scroll covered in faded writing.", 1});
  rooms[3].add_item(Item{"rope", "Thirty feet of sturdy rope.", 3});
  rooms[5].add_item(Item{"crown", "A small golden crown.", 4});

  Player player{"Adventurer", &rooms[0]};

  std::cout << "\n--- Dungeon ---\n";
  print_help();
  if (!enter_room(player)) {
    return 0;
  }

  std::string line;
  while (prompt_line("\n> ", line)) {
    std::string verb;
    std::string noun;
    split_first(line, verb, noun);

    if (verb == "quit") {
      std::cout << "You leave the dungeon.\n";
      return dungeon_score(player.inventory_count(), player.health());
    } else if (verb == "help") {
      print_help();
    } else if (verb == "look") {
      describe_room(*player.location());
    } else if (verb == "inventory") {
      player.show_inventory();
    } else if (verb == "go") {
      Direction d = Direction::north;
      if (noun.empty()) {
        std::cout << "Go where? Try: go north\n";
      } else if (!parse_direction(noun, d)) {
        std::cout << "'" << noun << "' is not a direction.\n";
      } else if (!player.move(d)) {
        std::cout << "You can't go " << direction_name(d) << " from here.\n";
      } else if (!enter_room(player)) {
        return 0;
      }
      // TODO (Lab 13, Task 4): after entering, call meet_monster() and
      // return 0 if the player died. Add monster_bonus * defeated to the
      // score you return.
    } else if (verb == "take") {
      if (noun.empty()) {
        std::cout << "Take what?\n";
      } else if (player.take(*player.location(), noun)) {
        std::cout << "Taken: " << noun << "\n";
      } else {
        std::cout << "You can't take that.\n";
      }
    } else if (verb == "drop") {
      if (noun.empty()) {
        std::cout << "Drop what?\n";
      } else if (player.drop(*player.location(), noun)) {
        std::cout << "Dropped: " << noun << "\n";
      } else {
        std::cout << "You can't drop that.\n";
      }
    } else if (!verb.empty()) {
      std::cout << "Unknown command '" << verb << "'. Type help.\n";
    }
  }
  return dungeon_score(player.inventory_count(), player.health());
}
