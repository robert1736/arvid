#include "mbed.h"
#include <cstdio>


class Character {
    protected:
        const char* Class;
        int health, atk, def, mana, maxHealth;

    public:
        Character(const char* c, int h, int a, int d, int m, int mh) {
            Class = c;
            health = h;
            atk = a;
            def = d;
            mana = m;
            maxHealth = mh;
        }

        bool isAlive() const {
            return health > 0;
        }

        void heal(int amount) {
        health += amount;
        if (health > maxHealth)
            health = maxHealth;
        }


        void takeDamage(int dmg) {
            int finalDmg = dmg - def;
            if (finalDmg < 1) finalDmg = 1;

            health -= finalDmg;
            if (health < 0) health = 0;
        }

        void attack(Character& target) {
            int dmg = atk;
            if ((rand() % 100) < 15) {   //critical chance
                 dmg*= 2;
             }  
            target.takeDamage(dmg);
        }

        bool useMana(int amount) { 
                if (mana >= amount) {
                mana -= amount;
                return true;
             }
            return false;
        }

        //getters
        int getHealth() const {
            return health;
        }

        const char* getClass() const {
            return Class;
        }

        //spells
        void fireball(Character& target) {
            if (useMana(5)) {
                target.takeDamage(atk + 10);
                }
            }
};

class Player : public Character {
    public:
        Player(const char* t, int h, int a, int d, int m, int mh)
            : Character(t, h, a, d, m, mh) {}

};

class Enemy : public Character {
    public:
        Enemy(const char* t, int h, int a, int d, int m, int mh)
            : Character(t, h, a, d, m, mh) {}
};

enum GameState {   
    MENU,
    BATTLE,
    GAMEOVER
    //inventory
    //pause
    //
};
enum Turn {
    PLAYER,
    ENEMY
};

int main() {
    Turn currentTurn = PLAYER;
    GameState state = MENU;
    Player player("Warrior", 100, 20, 5, 10,100);
    Enemy enemy("Goblin", 50, 10, 2, 0, 50);


    while (true) {
        switch(state) {

            case MENU:
                printf("=== ARVID ===\n");
                printf("Starting game...\n");

                thread_sleep_for(1000);

                state = BATTLE;
                break;





            case BATTLE:
                if (currentTurn == PLAYER) {

                        printf("\n YOUR TURN \n");
                        printf("1. Attack\n");
                        printf("2. Fireball\n");
                        printf("3. Heal\n");
                        //etc

                        //input for choice

                        switch(choice) {

                            case 1:
                                player.attack(enemy);
                                printf("You attacked!\n");
                                break;

                            case 2:
                                player.fireball(enemy);
                                printf("Fireball cast!\n");
                                break;

                            case 3:
                                player.heal(10);
                                printf("You healed!\n");
                                break;

                            default:
                                printf("Invalid input\n");
                                break;
                        }

                        printf("Enemy HP: %d\n", enemy.getHealth());

                        if (!enemy.isAlive()) {
                            state = GAMEOVER;
                            break;
                        }

                        currentTurn = ENEMY;
                    }

                    if (currentTurn == ENEMY) {

                        printf("\nENEMY TURN \n");


                        if (enemy.getHealth() < 20) {
                            enemy.heal(10);
                            printf("Enemy healed!\n");
                        }
                        else {
                            enemy.attack(player);
                            printf("Enemy attacks!\n");
                        }

                        printf("Player HP: %d\n", player.getHealth());

                        if (!player.isAlive()) {
                            state = GAMEOVER;
                            break;
                        }

                        currentTurn = PLAYER;
                    }

                    thread_sleep_for(1000);
                    break;
            case GAMEOVER:

                if (player.isAlive()) {
                    printf("You Win\n");
                }
                else {
                    printf("You Lose\n");
                }

                return 0;    

        }

    }
}

/////NOTES/////////
//////////////////////////////////////////////////
//character selection idea:

//enum CharacterType {
//  WARRIOR,
// GOBLIN,
// MAGE
//};
//CharacterType type;

//const char getName() {
    //switch (type {
        //case WARRIOR return "Warrior";
        //case RANGER return "Ranger";
    //}
    //return "Unknown";
//////////////////////////////////////////
