#include "mbed.h"
#include <cstdio>


class Character {
    protected:
        const char* Class;
        int health, atk, def, mana;

    public:
        Character(const char* c, int h, int a, int d, int m) {
            Class = c;
            health = h;
            atk = a;
            def = d;
            mana = m;
        }

        bool isAlive() const {
            return health > 0;
        }

        void heal(int amount) {
        health += amount;
        }

        void takeDamage(int dmg) {
            int finalDmg = dmg - def;
            if (finalDmg < 1) finalDmg = 1;

            health -= finalDmg;
            if (health < 0) health = 0;
        }

        void attack(Character& target) {
            target.takeDamage(atk);
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
};

class Player : public Character {
    public:
        Player(const char* t, int h, int a, int d, int m)
            : Character(t, h, a, d, m) {}

};

class Enemy : public Character {
    public:
        Enemy(const char* t, int h, int a, int d, int m)
            : Character(t, h, a, d, m) {}
};



int main() {
    Player player("Warrior", 100, 20, 5, 10);
    Enemy enemy("Goblin", 50, 10, 2, 0);

    while (player.isAlive() && enemy.isAlive()) {

        printf("%s attacks %s\n", player.getClass(), enemy.getClass());
        player.attack(enemy);
        printf("Enemy HP: %d\n\n", enemy.getHealth());

        if (!enemy.isAlive()) break;

        printf("%s attacks %s\n", enemy.getClass(), player.getClass());
        enemy.attack(player);
        printf("Player HP: %d\n\n", player.getHealth());

        thread_sleep_for(1000);
    }

    if (player.isAlive()) {
        printf("You win\n");
    } else {
        printf("You Lose\n");
    }
}
