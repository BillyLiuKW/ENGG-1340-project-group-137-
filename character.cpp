//Propeties of characters in the game

#include <iostream>
#include <vector>
#include <sstream>
#include <string>   
#include "character.hpp"
using namespace std;

MainCharacter::MainCharacter(){
    hp = 100; // Numbers subject to change
    max_hp = 100;
    atk = 25;
    def = 10;
    mp = 100;
    max_mp = 100;
    name = "Hero";
    image =
    {
        "           '(!|cZY/         ",
        "           0i[0f[{au        ",
        "           BhmZzi@k+'       ",
        ">l         `bZhoXY*/        ",
        "z-xI      {!WknfQz8hc!      ",
        "'[Ir/.    *jZL{}_Qo&@kk[/UU^",
        "  \",(v1   +M#qQm*+())f&0Ob[.",
        "     ^a#MYW:dWLX-&U8Y(8Up|  ",
        "      ^rwO,~CXJmkq0zQptpwl  ",
        "        <|QnUqmYBCvpYtvZY(  ",
        "       'iudh{/uvB{|m#L)x-l  ",
        "        :qx&  ;C`  \"O?!t    ",
        "          \"|l         @]X|  ",
        "         IaqL         ./c1^ ",
        "        [cvu~          ^(ZMw"
    };
    height = image.size();
    width = image[0].size();
    
    moveSet;
    //moveSet[0-3] (int) = ID for a move in moves.cpp


}


// ALL ENEMY CLASSES BELOW ARE TENTATIVE

// All image should have a height of 15 char (width can vary)
Dummy::Dummy(){
    hp = 75;
    atk = 10;
    def = 10;
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
    Enemy_Skill skill1 = {1, "regenerate", "Heal", vector<string>{"e_hp 100", "e_atk 01"}};
    Enemy_Skill skill2 = {2, "attack", "Heavy Attack", vector<string>{"m_hp -100", "m_atk -10"}};
    Enemy_Skill skill3 = {3, "defend", "Defend", vector<string>{"e_def 10"}};
    Enemy_Skill skill4 = {4, "interfere", "Boost", vector<string>{"e_atk 1"}};
    skill_list.push_back(skill1);
    skill_list.push_back(skill2);
    skill_list.push_back(skill3);
    skill_list.push_back(skill4);
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

Demon::Demon(){
    hp = 500;
    atk = 100;
    def = 30;
    name = "Demon";
    image = 
    {
        "     ^                 ^        ",
        "      #U*           #U9         ",
        "       #*SDH     DS*&K          ",
        "           ANfdd93              ",
        "          aijdsajda             ",
        "            addsd               ",
        "        <^   dsd   ^>           ",
        "       <IN R  s  R NI>          ",
        "      <dnj F)ld[; $J#*J>        ",
        "     <NI#  ADMi3j9a  #&H>       ",
        "    <df$   amskmska   %$d>      ",
        "   <)      kdsskadm      (>     ",
        "  <D       symkasmk       d>    ",
        " <H                        H>   ",
        "<                            >  ",
    };
}

Titan::Titan(){
    hp = 800;
    atk = 50;
    def = 60;
    name = "Titan";
    image = 
    {
        "        Te    $sd      eT        ",
        "       HDSe  asddas   esdH       ",
        "        GSDesddDS*&Kae#@G        ",
        "         &***dANfdd9#*$          ",
        "   ^       adsaddsaj$         ^  ",
        "    ^       ddaddsd@         ^   ",
        "    dsadsdssd <^ dsadsd adaddd   ",
        "  asdasddsadasaddRdsasdsRsd NI>d ",
        "    dd <dnjd F)ld[; $J#*J>dmsak  ",
        "   d<NI# dADMi3j9aasdd#& sad3]   ",
        "  d<df$  asddasdamskmska  DJE#i  ",
        "ddssddsa kdsskadmasdsada JD#*jdi4",
        "saddsada symkasmkaddsdds 834HDIIJ",
        "      dsd#DSDS     DEsddasd      ",
        "      sadsadad     dasdsads      ",
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
                skill_list = dummyEnemy->skill_list;
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
                Dragon* dragonEnemy = new Dragon();
                hp = dragonEnemy->hp;
                max_hp = dragonEnemy->hp;
                atk = dragonEnemy->atk;
                def = dragonEnemy->def;
                name = dragonEnemy->name;
                image = dragonEnemy->image;
                height = image.size();
                width = image[0].size();
                delete dragonEnemy;
                break;
            }
            case 8:
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
            case 9:
            {
                Demon* demonEnemy = new Demon();
                hp = demonEnemy->hp;
                max_hp = demonEnemy->hp;
                atk = demonEnemy->atk;
                def = demonEnemy->def;
                name = demonEnemy->name;
                image = demonEnemy->image;
                height = image.size();
                width = image[0].size();
                delete demonEnemy;
                break;
                }
            case 10:
            {
                Titan* titanEnemy = new Titan();
                hp = titanEnemy->hp;
                max_hp = titanEnemy->hp;
                atk = titanEnemy->atk;
                def = titanEnemy->def;
                name = titanEnemy->name;
                image = titanEnemy->image;
                height = image.size();
                width = image[0].size();
                delete titanEnemy;
                break;
                }
            default:
            {
                cout << "Error: Enemy type not found!" << endl;
                break;
            }
        }
    }

