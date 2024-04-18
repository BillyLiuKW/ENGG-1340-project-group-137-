//Propeties of characters in the game

#include <iostream>
#include <vector>
#include <sstream>
#include <string>   
#include "character.hpp"
using namespace std;

MainCharacter::MainCharacter(){
    int hp = 100; // Numbers subject to change
    int max_hp = hp;
    int atk = 25;
    int def = 10;
    string name = "Hero";
    image =
    {
        "",
    };
    height = image.size();
    width = image[0].size();
    
    vector<int> moveSet;
    //moveSet[0-3] (int) = ID for a move in moves.cpp


}


// ALL ENEMY CLASSES BELOW ARE TENTATIVE

// All image should have a height of 15 char (width can vary)
Dummy::Dummy(){
    hp = 50;
    atk = 10;
    def = 5;
    name = "Dummy";
    image =
    {
        "      {;   ...      "
        "     xp|  rnczLL    "
        "   .10//  zvZLZ|'   "
        "  ^}xi\"   UYLZpp]   "
        " '[zi$  {cndpbkY//  "
        "lvXz' :tnvvzYYUOUYx,"
        " ^~}Qt>'fYYYJLLmpr~?"
        "   .)ZZ.rJYJLZ0wq~fC"
        "        vCJQQmZwbhY\""
        "        'LULOqZdwL  "
        "         $`lC.';$   "
        "           UUX      "
        "           Yx'      "
        "           Jx.      "
        "           OQ-      "
    };
}

Goblin::Goblin(){
    hp = 75;
    atk = 15;
    def = 7;
    name = "Goblin";
    image = 
    {
        "        x{-  n       "
        "      ffZx/_t(       "
        "     LQdYhuj)n    bQL"
        "      uOQxfbj     |M*"
        "       Zwaj/j[-\"fkOCC"
        "mq-[{Xzwbpxr(?[jLZC\" "
        "QmapOdpL|10c|?fdbtr? "
        "  kk    Oroz(t(akoZ  "
        "        aU!_<[/ $q   "
        "        hdmcjfz      "
        "        kWW*aa*      "
        "       Omb#Mokq      "
        "       Mao  &Wb\"     "
        "      hQk   oh*      "
        "      pZh   MM#ho    "
    };
}

Enemy::Enemy(int type){
        switch(type){
            //When making Enemy objects, use the following syntax: Enemy enemy(1) to create different types of enemies
            case 1:
            {
                Dummy* dummyEnemy = new Dummy();
                hp = dummyEnemy->hp;
                max_hp = dummyEnemy->hp;
                atk = dummyEnemy->atk;
                def = dummyEnemy->def;
                name = dummyEnemy->name;
                image = dummyEnemy->image;
                height = image.size();
                width = image[0].size();
                delete dummyEnemy;
                break;
            }
            case 2:
            {
                Goblin* goblinEnemy = new Goblin();
                hp = goblinEnemy->hp;
                max_hp = goblinEnemy->hp;
                atk = goblinEnemy->atk;
                def = goblinEnemy->def;
                name = goblinEnemy->name;
                image = goblinEnemy->image;
                height = image.size();
                width = image[0].size();
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

