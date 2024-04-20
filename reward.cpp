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

void random_reward::ability(MainCharacter &m){
    int health, attack, defence;
    rand();
}

void random_reward::skill(MainCharacter &m){
    int x;
}