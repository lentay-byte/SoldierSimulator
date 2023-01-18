//-------------------------------------------------------------------------------
//  file: soldier.cpp
// class: COP 3003, Fall 2022
//  Devl: Lenworth Taylor
//  desc: Lab 1 for a soldier NPC AI demo of structs and enums
//-------------------------------------------------------------------------------
#include <iostream> // console I/O
#include <cstdlib> // random numbers
#include <ctime> // random seed
#include "Character.h" // character class

// Function Proto-types (Declarations)
//-------------------------------------------------------------------------------
SoldierMode homing(Character &soldier);
SoldierMode isPatrolling(Character * soldier, Character * &enemy);
SoldierMode isAttacking(Character &soldier, Character *& enemy);
SoldierMode isDefending(Character &soldier, Character *& enemy);
SoldierMode isRetreating(Character &soldier, Character *&enemy);
bool ifHit();
void ifCombat(Character &soldier, Character *&enemy, SoldierMode currentMode);
//-------------------------------------------------------------------------------

int main() {
    // init random numbers
    std::srand(std::time(NULL));

   // int level = std::rand() % START_LEVl_DIE + 1;
   // int hitPoint = std::rand() % HIT_POINT_DIE +1;

    Character soldier(SOLDIER_LEVEL, SOLDIER_HITPOINTS);
    std::cout << "Soldier level: " << soldier.getLevel()
                << "\nSoldier hit-point: " << soldier.getHitPoint()
                << "\nSolder health: " << soldier.getHealth() << std::endl;


    SoldierMode soldierMode = HOMING;
    Character * enemy = nullptr;

    //main game loop until soldier dies
    do {

        //switch statement to determine the state that the soldier is in
        switch (soldierMode) {
            case HOMING:
                soldierMode = homing(soldier);
                break; // end homing

            case PATROLLING:
                soldierMode = isPatrolling(&soldier,enemy);
                break; //end patrolling

            case ATTACKING:
                soldierMode = isAttacking(soldier,enemy);
                break; //end attacking

            case DEFENDING:
                soldierMode = isDefending(soldier, enemy);
                break; //end defending

            case RETREATING:
                soldierMode = isRetreating(soldier, enemy);
                break; // end retreat

        }//
    }while (soldier.getHealth() > 0);

    std::cout << "SOLDIER DIED!";
    delete enemy; // deletes enemy from memory at game end

    return 0;
}// end main

//Function Definitions
//--------------------------------------------------------------------------

/**
 * handle when the solder is at his base
 * @param soldier - structure for the soldier
 * @return either HOMING or PATROLLING
 */

SoldierMode homing(Character &soldier){
    SoldierMode retMode = HOMING;

    //checks if the soldier is at full health.
    if (soldier.getHealth() == soldier.getLevel() * soldier.getHitPoint()) {
        std::cout << "Soldier is at full health." << std::endl;
        retMode = PATROLLING;
    } else {
        std::cout << "Soldier needs to heal." << std::endl;
        soldier.healBy(HOMING);
    }

    return retMode;
}

/**
 * handle when the soldier is patrolling the area
 * @param soldier - structure for the soldier
 * @param enemy -structure for the enemy
 * @return either PATROLLING, ATTACKING, or RETREATING
 */

SoldierMode isPatrolling(Character * soldier, Character *& enemy){
    SoldierMode retMode = PATROLLING;
    if(!enemy) {
        // no enemy so check for encounter
        int enemyEncounter = std::rand() % ENCOUNTER_DIE + 1;

        //generates random level and hit point values for enemy if there is an encounter.
        if(enemyEncounter == 1) {
            enemy = new Character();
            int level = std::rand() % START_LEVl_DIE + 1;
            enemy->setLevel(level);
            int hitPoint = std::rand() % HIT_POINT_DIE + 1;
            enemy->setHitPoint(hitPoint);
            enemy->setFullHealth();
            std::cout << "Soldier has encountered an level " << enemy->getLevel() << " enemy with "
                      << enemy->getHitPoint() << " hit points! \nHealth: " <<enemy->getHealth()<< std::endl;
        }

        else {
            std::cout << "All Clear" << std::endl;
        }

    }
    else{

        // determines which mode the soldier should enter based on the enemy's skill level;
        if(soldier->getLevel() > (enemy->getLevel() + LEVEL_DIFFERENCE)) {
            retMode = ATTACKING;
        }
        else if(soldier->getLevel() < enemy->getLevel() - 2) {
            retMode = RETREATING;
        }
        else {
            retMode = DEFENDING;
        }

    }

    return retMode;
}

/**
 * handle when the soldier is attacking an enemy
 * @param soldier - structure for the soldier
 * @param enemy -structure for the enemy
 * @return either ATTACKING, DEFENDING, PATROLLING, or HOMING
 */

SoldierMode isAttacking(Character &soldier, Character *&enemy){
    SoldierMode retMode = ATTACKING;

    int halfLife = soldier.getHealth()/2;

    //loops battle until the enemy or soldier dies
    do {
        std::cout << "attacking enemy" << std::endl;
        ifCombat(soldier, enemy, retMode);

        //switches soldier mode to DEFENDING if health gets too low
        if(soldier.getHealth() < halfLife){
            retMode = DEFENDING;
            return retMode;
        }

    }while(enemy->getHealth() > 0);

    enemy = nullptr;
    std::cout << "ENEMY DIED!" << std::endl;

    //determines if the soldier should return to base to heal or return to patrolling
    // depending on its health
    if(soldier.getHealth() > halfLife){
        retMode = PATROLLING;
    }
    else
        retMode= HOMING;

    return retMode;
}

/**
 * handle when the soldier is patrolling the area
 * @param soldier - structure for the soldier
 * @param enemy -structure for the enemy
 * @return either ATTACKING OR DEFENDING
 */

SoldierMode isDefending(Character &soldier, Character *& enemy) {
    SoldierMode retMode = DEFENDING;

    int quarterLife = soldier.getHealth() / 3;

    //loops battle until the enemy or soldier dies
    do {
        std::cout << "defending base" << std::endl;
        ifCombat(soldier, enemy, retMode);

        //switches soldier mode to RETREATING if health gets too low
        if (soldier.getHealth() < quarterLife) {
            retMode = RETREATING;
            return retMode;
        }

    } while (enemy->getHealth() > 0);

    enemy = nullptr;
    std::cout << "ENEMY DIED!" << std::endl;

    retMode = HOMING;
    return retMode;
}
/**
 * handle when the soldier is patrolling the area
 * @param soldier - structure for the soldier
 * @param enemy -structure for the enemy
 * @return either ATTACKING OR DEFENDING
 */

SoldierMode isRetreating(Character &soldier, Character *&enemy){
    SoldierMode retMode = RETREATING;

    int halfLife = soldier.getHealth()/2;


    do{
        std::cout<< "retreating" << std::endl;

        //heals soldier while retreating
        soldier.healBy(retMode);

        //reaches base once health is above half
        if(soldier.getHealth() > halfLife) {
            retMode = HOMING;
            break;
        }
    }while(enemy->getHealth() > 0);

    return retMode;
}

/**
 * test if a hit has occurred
 * @return a bool
 */

bool ifHit(){
    bool hitTest = false;
    int hit = std::rand() % IF_HIT_DIE + 1;

    // returns true if there was a hit.
    if(hit == 1)
        hitTest = true;
    return hitTest;
}

/**
 * handles the combat between a soldier and an enemy.
 * @param soldier - structure for the soldier.
 * @param enemy - structure for the enemy.
 * @param currentMode - current mode of the soldier.
 */

void ifCombat(Character &soldier, Character *& enemy, SoldierMode currentMode){

    // bool variables to check if soldier or enemy got a hit on their target
    bool hitSoldier = ifHit();
    bool hitEnemy = ifHit();

    // adjust enemy's health of the soldier got a hit.
    if(hitSoldier){

        //Damage enemy health
        enemy->takeDamage(soldier.getHitPoint());
        std::cout << "Enemy health: " << enemy->getHealth() << std::endl;

    }

    // adjusts soldier's health if the enemy got a hit.
    if(hitEnemy){
        // damages soldier health based on the enemy's hit points
        soldier.takeDamage(enemy->getHitPoint());

        //heals soldier based on the current soldier mode
        soldier.healBy(currentMode);
        std::cout << " Soldier health: " << soldier.getHealth() << std::endl;
    }

}





