//-------------------------------------------------------------------------------
//  file: Character.cpp
// class: COP 3003, Fall 2022
//  Devl: Lenworth Taylor
//  desc: Implementation of a character class object.
//-------------------------------------------------------------------------------

#include "Character.h"

// Constructors
//-----------------------------------------------------------------------------
Character::Character(){
    level = 0;
    hitPoint = 0;
    health = 0;
}  // defaults constructor

Character::Character(int level, int hitPoint){
    this->level = level;
    this->hitPoint = hitPoint;
    this->health = level * hitPoint;
}  // property

// Accessors
//-----------------------------------------------------------------------------
int Character::getLevel(){ return level; }
void Character::setLevel(int value){ level = value; }

int Character::getHitPoint(){ return hitPoint; }
void Character::setHitPoint(int value){ hitPoint = value; }

int Character::getHealth(){ return health; }
void Character::setHealth(int value){ health = value; }

void Character::setFullHealth() {
    health = level * hitPoint;
}

// Methods
//-----------------------------------------------------------------------------


void Character::healBy(SoldierMode mode) {
    if (mode == ATTACKING) {
        health += ATTACK_HEAL;
    } else if (mode == DEFENDING) {
        health += DEFEND_HEAL;
    } else if (mode == RETREATING) {
        health += RETREAT_HEAL;
    } else {
        health += HOMING_HEAL;
    }

    //ensures that health doesn't exceed its max
    if (health > (level * hitPoint)) {
        setFullHealth();
    }
}

void Character::takeDamage(int hitVal) {
    health -= hitVal;
}
