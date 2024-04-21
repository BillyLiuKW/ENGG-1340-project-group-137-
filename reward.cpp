//random reward
#include <iostream>
#include <cstdlib>
#include <string>
#include "character.hpp"

#include "reward.hpp"
using namespace std;

void random_reward::reward(MainCharacter &m){
    cout << "Choose Reward Type : 1. MainCharater Ability   2. Skills" << endl;
    int type;
    cout << "Please Enter 1/2 : ";
    cin >> type ;
    string lucky_draw_no;
    cout << "Enter a number for lucky draw : ";
    cin >> lucky_draw_no;
    srand(stod(lucky_draw_no));
    switch(type){
        case (1):
            ability(m);
        case (2):
            skill(m);
    }
}

void random_reward::ability(MainCharacter &m){ //basic value
    int health, attack, defence, magic;
    bool x = 1;
    health = rand() % 51 + 50;
    attack = rand() % 31 + 15;
    defence = rand() % 16 + 15;
    magic = rand() % 31 + 20;
    while (x){
        if (health % 5 != 0)
            health--;
        if (attack % 5 != 0)
            attack--;
        if (defence % 5 != 0)
            defence--;
    }
    cout << "hp +" << health << endl;
    cout << "atk +" << attack << endl;
    cout << "def +" << defence << endl;
    cout << "mp +" << magic << endl;
    m.hp += health;
    m.atk += attack;
    m.def += defence;
    m.mp += magic;
}

void random_reward::skill(MainCharacter &m){
    int x;
}