//Propeties of characters in the game

#include <iostream>
#include <vector>
#include <sstream>
#include <string>   
#include "character.hpp"
using namespace std;

MainCharacter::MainCharacter(){
    hp = 100; // Numbers subject to change
    max_hp = hp;
    atk = 25;
    def = 10;
    name = "Hero";
    image =
    {
        "aaaaaaaaaaaaaaaaaaaaa",
        "aaaaaaaaaaaaaaaaaaaaa",
        "aaaaaaaaaaaaaaaaaaaaa",
        "aaaaaaaaaaaaaaaaaaaaa",
        "aaaaaaaaaaaaaaaaaaaaa",
        "aaaaaaaaaaaaaaaaaaaaa",
        "aaaaaaaaaaaaaaaaaaaaa",
        "aaaaaaaaaaaaaaaaaaaaa",
        "aaaaaaaaaaaaaaaaaaaaa",
        "aaaaaaaaaaaaaaaaaaaaa",
        "aaaaaaaaaaaaaaaaaaaaa",
        "aaaaaaaaaaaaaaaaaaaaa",
        "aaaaaaaaaaaaaaaaaaaaa",
        "aaaaaaaaaaaaaaaaaaaaa",
        "aaaaaaaaaaaaaaaaaaaaa",
    };
    height = image.size();
    width = image[0].size();
    
    moveSet;
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
        "      {;   ...      ",
        "     xp|  rnczLL    ",
        "   .10//  zvZLZ|'   ",
        "  ^}xi\"   UYLZpp]   ",
        " '[zi$  {cndpbkY//  ",
        "lvXz' :tnvvzYYUOUYx,",
        " ^~}Qt>'fYYYJLLmpr~?",
        "   .)ZZ.rJYJLZ0wq~fC",
        "        vCJQQmZwbhY\"",
        "        'LULOqZdwL  ",
        "         $`lC.';$   ",
        "           UUX      ",
        "           Yx'      ",
        "           Jx.      ",
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
        "           }X){??  v(          ",
        "          rnpvjn}?(f]          ",
        "        YUqdQndj1}/|       0LLL",
        "         OLQmvcxb0tc       #*hd",
        "          mawqdxrf()]]+ xO*<UZ ",
        "cOJ?)xn}zuJqbwqtuLj]_[tuC)LtU  ",
        " 0wowwtOdp0Q|]jCuL0?}xkmo|J()  ",
        "    kk     d*j/hJ/(/)| ab*q    ",
        "           paq}!,+<?{/fwwwZ    ",
        "           CkdpmvuffrcC        ",
        "           Cw*##*ahbhb         ",
        "          OQmqh**ohkdqZ        ",
        "          **hd    W#aqQ        ",
        "          Lma     &hJb         ",
        "        upbwX     M***aha      "
    };
}

Mutant::Mutant(){
    hp = 85;
    atk = 30;
    def = 10;
    name = "Mutant";
    image = 
    {
        "     ww    i     hd     ",
        "      tw  o   ifw       ",
        "     ; ??fbhjwu }@      ",
        "    <adsad#^CADmhg>>    ",
        "     \\ADd#fdgPdgf/      ",
        " uu   \\ja\\u/^%/   uu    ",
        "  rty  i$YDnjdI@  uyy   ",
        "  adasL  dja_d  dasyu   ",
        "         k dad d        ",
        "         t wrr @        ",
        "         ( wre )        ",
        "   tjoej & #GT ^ gnjrg  ",
        "   tuu   { +da }   ert  ",
        "  uu     % Wds $     uu ",
        "         !ANJDS*DS^     "
    };
}

Robot::Robot(){
    hp = 220;
    atk = 10;
    def = 20;
    name = "Robot";
    image = 
    {
        "       gg               gg      ",
        "        ggg           ggg       ",
        "          &NKA&Ye3adnl)         ",
        "        e!n o dna o k!ppp       ",
        "        eppdkasdkAMSDKSopp      ",
        "           #*&DSAJDSNA9         ",             
        "   wSidjjdks<D:ALP{#KP)ACPA}[]w ",
        "   wew[MKLADM(#0l[da;[3wPE])czw ",
        "   wwwedasd]salsa[dlEP92-2c]cjw ",
        "   wsas#*DI*       &{D]sa3o}ifw ",
        "   wrer&$//' ^][   ds$mc$g\"vaw  ",
        "       ANJirj349p9eJcfadad;e    ",
        "       |dkadmk     sdadd*|      ",
        "       |las,d,     masmdl|      ",
        "       |ND*UH*     tD[3,s|      ",
    };
}
Dragon::Dragon(){
    hp = 880;
    atk = 80;
    def = 50;
    name = "Dragon";
    image = 
    {
        "               ~Y                ",
        "                qqx              ",
        "   `^           (Z|      `+*zi:` ",
        "   0Zq{          OQ/    qkpZZZOf'",
        "!Uwmmwpk?     :|qOzQ  \"LppmpqOOt ",
        "  JOOOwdOpw!iOwOO0wdmdk0OmwO0mpc'",
        "  CmpOOa0OOaOptC0OdbZOpO0OpqZ]^'I",
        " lLf/mmwO0tx< qOOm?   l  ._k<    ",
        "      c0      lLOZ{              ",
        "      `'       :Of               ",
        "                 O<              ",
        "                 ]-              ",
        "                .x'              ",
        "                O<   :           ",
        "                 ]0fz,           "
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
            case 4:
            {
                Mutant* mutantEnemy = new Mutant();
                hp = mutantEnemy->hp;
                max_hp = mutantEnemy->hp;
                atk = mutantEnemy->atk;
                def = mutantEnemy->def;
                name = mutantEnemy->name;
                image = mutantEnemy->image;
                height = image.size();
                width = image[0].size();
                delete mutantEnemy;
                break;
                }
            case 6:
            {
                Robot* robotEnemy = new Robot();
                hp = robotEnemy->hp;
                max_hp = robotEnemy->hp;
                atk = robotEnemy->atk;
                def = robotEnemy->def;
                name = robotEnemy->name;
                image = robotEnemy->image;
                height = image.size();
                width = image[0].size();
                delete robotEnemy;
                break;
                }
            default:
            {
                cout << "Error: Enemy type not found!" << endl;
                break;
            }
        }
    }

