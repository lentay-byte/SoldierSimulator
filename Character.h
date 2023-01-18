//-------------------------------------------------------------------------------
//  file: Character.h
// class: COP 3003, Fall 2022
//  Developed by : Lenworth Taylor
//  desc: Declaration of a character class object.
//-------------------------------------------------------------------------------

//HEADER GUARD
#ifndef SOLDIER_CHARACTER_H
#define SOLDIER_CHARACTER_H

// constants & types
//-------------------------------------------------------------------------------
const int START_LEVl_DIE = 7;
const int HIT_POINT_DIE = 20;
const int ENCOUNTER_DIE = 3;
const int LEVEL_DIFFERENCE = 2;
const int IF_HIT_DIE = 3;
const int ATTACK_HEAL = 2;
const int DEFEND_HEAL= 4;
const int RETREAT_HEAL = 8;
const int HOMING_HEAL = 12;

const int SOLDIER_LEVEL = 5;
const int SOLDIER_HITPOINTS = 10;


enum SoldierMode {
    HOMING,
    PATROLLING,
    ATTACKING,
    DEFENDING,
    RETREATING
};

//------------------------------------------------------------------------------

//Class declaration
class Character {
private:
    int level;
    int hitPoint;
    int health;

public:
    // Constructors
    //-----------------------------------------------------------------------------
    Character();  // defaults constructor
    Character(int level, int hitPoint);  // property

    // Accessors
    //-----------------------------------------------------------------------------
    int getLevel();
    void setLevel(int value);

    int getHitPoint();
    void setHitPoint(int value);

    int getHealth();
    void setHealth(int value);

    // Methods
    //-----------------------------------------------------------------------------
    void setFullHealth();
    void healBy(SoldierMode mode);
    void takeDamage(int hitVal);

};
#endif //SOLDIER_CHARACTER_H
