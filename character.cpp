//Propeties of characters in the game

#include <iostream>
#include <vector>
#include <sstream>
#include <string>   
#include "character.hpp"
using namespace std;

MainCharacter::MainCharacter(){
    int hp = 100; // Numbers subject to change
    int atk = 25;
    int def = 10;
    string name = "Hero";
    vector<int> moveSet;
    //moveSet[0-3] (int) = ID for a move in moves.cpp


}


// ALL ENEMY CLASSES BELOW ARE TENTATIVE
Dummy::Dummy(){
    hp = 50;
    atk = 10;
    def = 5;
    name = "Dummy";

}

Goblin::Goblin(){
    hp = 75;
    atk = 15;
    def = 7;
    name = "Goblin";

}

Enemy::Enemy(int type){
        switch(type){
            //When making Enemy objects, use the following syntax: Enemy enemy(1) to create different types of enemies
            case 1:
            {
                Dummy* dummyEnemy = new Dummy();
                hp = dummyEnemy->hp;
                atk = dummyEnemy->atk;
                def = dummyEnemy->def;
                name = dummyEnemy->name;
                delete dummyEnemy;
                break;
            }
            case 2:
            {
                Goblin* goblinEnemy = new Goblin();
                hp = goblinEnemy->hp;
                atk = goblinEnemy->atk;
                def = goblinEnemy->def;
                name = goblinEnemy->name;
                delete goblinEnemy;
                break;
                }
            default:
            {
                cout << "Error: Enemy type not found!" << endl;
                break;
            }
        }
    }

