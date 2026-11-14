#pragma once

#include "monster.h"

class Troll : public Monster {
public:
    Troll();

    // Returns the damage a troll does which is 6
    int attack_damage() const override;

    // Returns a one-line description of the troll
    std::string describe() const override;
};
