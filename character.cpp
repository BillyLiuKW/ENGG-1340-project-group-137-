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
    
    moveSet = {0,1};
    //moveSet[0-3] (int) = ID for a move in moves.cpp


}


// ALL ENEMY CLASSES BELOW ARE TENTATIVE

// All image should have a height of 15 char (width can vary)
Dummy::Dummy(){
    hp = 80;
    atk = 10;
    def = 10;
    critical_chance = 0.05;
    critical_damage = 0.5;
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
    // ***** remerber to read what can be input *****
    // int: int_value, double: double_value, (+ve/-ve) any number, (+ve) positive onky, (-ve) negative only
    // e_hp : enemy recover 1st argument hp 
    //              format: "e_hp int_change(+ve/-ve) 0"
    // m_hp : enemy deal damage to main_C: formula (e.atk+e.buff_atk)*1st argument - (m.def+m.buff_def)
    //              format: "m_hp double_mutipiler(+ve) 0"
    // e_def : enemy defend change defefend of 1st arg for 2nd arg rounds (1st arg can be both +ve or -ve)
    //              format: "e_def int_change(+ve/-ve) int_rounds * 2"                 ********* rounds num need to * 2
    // m_def : same as above, but in main_c
    //              format: "m_def int_change(+ve/-ve) int_rounds * 2"                 ********* rounds num need to * 2 
    // e_atk : bascially same but just atk
    //              format: "e_atk int_change(+ve/-ve) int_rounds * 2"                 ********* rounds num need to * 2 
    // m_atk : same
     //             format: "m_atk int_change(+ve/-ve) int_rounds * 2"                 ********* rounds num need to * 2
    // e_cont_hp : enemy hp damage/ decrease for each round, // 
    //              format: "e_cont_hp double_mutiplier(+ve/-ve) int_rounds"           ********* rounds num don't need to * 2
    // e_cont_hp_const : enemy hp damage/ decrease a constant value for each round, 
    //              format: "e_cont_hp int_constant(-ve) int_rounds"                   ********* rounds num don't need to * 2
    // m_cont_hp : main_c hp damage/ decrease for each round, consider enemy atk
    //              format: "m_cont_hp double_mutiplier(-ve) int_rounds"               ********* rounds num don't need to * 2
    // m_cont_hp_const : main_c hp damage/ decrease a constant value for each round, 
    //              format: "m_cont_hp int_constant(-ve) int_rounds"                   ********* rounds num don't need to * 2
    // e_crit_chance : enemy critical chance increase temporialy,
    //              format: "e_crit_chance double_increase(+ve)(between 0-1) int_rounds * 2"  0.2 = +20% crit chance
    // e_crit_damage : enemy critical damage increase temporialy,
    //              format: "e_crit_chance double_increase(+ve) int_rounds * 2" 0.2 = +20% crit dmg
    // m_mp : stole main character mp (not finished yet)
    // if the skill only take 1 argument, you must put 0 in the second argument.
    // a skill can hold multiple option above 
    // example {skill ID, skill_ ype, skill name, {"option2 arg1 arg2", "option1 arg1 arg2"}}
    
    Enemy_Skill skill1 = {1, "regenerate", "Heal", vector<string>{"e_hp 50 0"}};
    Enemy_Skill skill2 = {2, "attack", "Heavy Attack", vector<string>{"m_hp 1.5 0", "m_atk -3 6", "m_cont_hp -0.5 2"}};
    Enemy_Skill skill3 = {3, "defend", "Defend", vector<string>{"e_def 5 6"}};
    Enemy_Skill skill4 = {4, "interfere", "Attack Boost", vector<string>{"e_atk 5 6", "e_crit_damage 0.5 6", "e_crit_chance 0.2 6"}};
    Enemy_Skill skill5 = {5, "regenerate", "Recover", vector<string>{"e_cont_hp_const 15 3"}};
    Enemy_Skill skill6 = {6, "attack", "Vampire", vector<string>{"m_hp 1.5 0", "e_hp 20 0"}};
    Enemy_Skill skill7 = {7, "attack", "Anger", vector<string>{"m_hp 2 0"}};
    Enemy_Skill skill8 = {8, "defend", "Jesus", vector<string>{"e_def 30 6", "m_hp 2.5 0"}};
    Enemy_Skill skill9 = {9, "attack", "Revenge", vector<string>{"m_hp 5 0", "e_hp 10 0"}};
    skill_list.push_back(skill1);
    skill_list.push_back(skill2);
    skill_list.push_back(skill3);
    skill_list.push_back(skill4);
    skill_list.push_back(skill5);
    skill_list.push_back(skill6);
    skill_list.push_back(skill7);
    skill_list.push_back(skill8);
    skill_list.push_back(skill9);
}


Goblin::Goblin(){
    hp = 100;
    atk = 20;
    def = 10;
    critical_chance = 0.05;
    critical_damage = 0.5;
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
    Enemy_Skill skill1 = {1, "interfere", "Stealing", vector<string>{"m_atk -5 4", "m_def -5 4", "e_atk +5 4", "e_def +5 4"}};
    Enemy_Skill skill2 = {2, "attack", "Yelling", vector<string>{"m_hp 1.5 0"}};
    Enemy_Skill skill3 = {3, "attack", "Fling", vector<string>{"m_hp 1.2 0", "m_cont_hp_const -8 6"}};
    Enemy_Skill skill4 = {4, "defende", "Shield", vector<string>{"e_def 15 4", "e_hp 20 0"}};
    Enemy_Skill skill5 = {5, "regenerate", "Rage", vector<string>{"e_cont_hp 15 3", "e_crit_chance 0.4 6", "e_crit_damage 1 6"}};
    Enemy_Skill skill6 = {6, "interfere", "Convert", vector<string>{"m_mp 10 0", "e_hp 10 0"}};
    Enemy_Skill skill7 = {7, "interfere", "Encourage", vector<string>{"e_atk 20 10"}};
    Enemy_Skill skill8 = {8, "Jump Attack", "Jesus", vector<string>{"m_hp 2 0", "m_atk -5 6"}};
    Enemy_Skill skill9 = {9, "defend", "Ingore", vector<string>{"e_def 22 8", "m_atk -8 6"}};
    Enemy_Skill skill10 = {9, "regenerate", "Low Lv Magic", vector<string>{"e_hp 10 0", "e_cont_hp 10 3"}};
    skill_list.push_back(skill1);
    skill_list.push_back(skill2);
    skill_list.push_back(skill3);
    skill_list.push_back(skill4);
    skill_list.push_back(skill5);
    skill_list.push_back(skill6);
    skill_list.push_back(skill7);
    skill_list.push_back(skill8);
    skill_list.push_back(skill9);
    skill_list.push_back(skill10);
}


Mutant::Mutant(){
    hp = 130;
    atk = 30;
    def = 20;
    critical_chance = 0.05;
    critical_damage = 0.5;
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
    Enemy_Skill skill1 = {1, "attack", "Shapeshifting", vector<string>{"m_hp 1.2 0", "e_def 20 0"}};    
    Enemy_Skill skill2 = {2, "attack", "Telepathy", vector<string>{"m_def -10 4", "e_crit_chance 0.4 4", "e_crit_damage 0.5 4"}};
    Enemy_Skill skill3 = {3, "attack", "Superhuman Strength", vector<string>{"m_hp 1.4 0", "e_def 20 6"}};
    Enemy_Skill skill4 = {4, "regenerate", "Regeneration", vector<string>{"e_hp 50 0"}};
    Enemy_Skill skill5 = {5, "defend", "Power Control", vector<string>{"m_def -10 4", "e_def 20 4"}};
    Enemy_Skill skill6 = {6, "interfere", "Time Manipulation", vector<string>{"m_atk -10 4", "m_def -5 4", "e_atk +10 4", "e_def +5 4"}};
    Enemy_Skill skill7 = {7, "defend", "Animal Control", vector<string>{"e_def +30 4"}};
    Enemy_Skill skill8 = {8, "regenerate", "Vampire", vector<string>{"e_hp 30 0", "m_hp 1.5 0"}};
    Enemy_Skill skill9 = {9, "attack", "Invisibe", vector<string>{"m_hp 2 0"}};
    skill_list.push_back(skill1);
    skill_list.push_back(skill2);
    skill_list.push_back(skill3);
    skill_list.push_back(skill4);
    skill_list.push_back(skill5);
    skill_list.push_back(skill6);
    skill_list.push_back(skill7);
    skill_list.push_back(skill8);
    skill_list.push_back(skill9);
}

Robot::Robot(){
    hp = 200;
    atk = 15;
    def = 45;
    critical_chance = 0.05;
    critical_damage = 0.5;
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
    Enemy_Skill skill1 = {1, "attack", "Electric Shock", vector<string>{"m_hp 1.2 0", "m_cont_hp_const -7 3"}};
    Enemy_Skill skill2 = {2, "defend", "Armor Plating", vector<string>{"m_def 10 8"}};
    Enemy_Skill skill3 = {3, "attack", "Plasma Blade", vector<string>{"m_hp 1.5 0", "m_atk -10 6"}};
    Enemy_Skill skill4 = {4, "interfere", "Disrupt Systems", vector<string>{"m_def -10 6", "m_const_hp -5 0", "e_def 10 6", "e_cont_hp_const +5 6"}};
    Enemy_Skill skill5 = {5, "regenerate", "Self-Reboot", vector<string>{"e_hp 30 0"}};
    Enemy_Skill skill6 = {6, "attack", "Ion Cannon", vector<string>{"m_hp 2 0", "m_cont_hp -0.8 2"}};
    Enemy_Skill skill7 = {7, "attack", "Rapid Fire", vector<string>{"m_hp 1.2 0"}};
    Enemy_Skill skill8 = {8, "interfere", "Virus Upload", vector<string>{"m_def -10 4", "m_hp 1.5 0", "e_crit_chance 0.5, 4", "e_crit_damage 0.5 4"}};
    Enemy_Skill skill9 = {9, "defend", "Force Field", vector<string>{"e_def 20 4"}};
    Enemy_Skill skill10 = {10, "regenerate", "Nano Repair", vector<string>{"e_cont_hp_const 15 3"}};
    skill_list.push_back(skill1);
    skill_list.push_back(skill2);
    skill_list.push_back(skill3);
    skill_list.push_back(skill4);
    skill_list.push_back(skill5);
    skill_list.push_back(skill6);
    skill_list.push_back(skill7);
    skill_list.push_back(skill8);
    skill_list.push_back(skill9);
    skill_list.push_back(skill10);
}

Dragon::Dragon(){
    hp = 250;
    atk = 80;
    def = 20;
    critical_chance = 0.05;
    critical_damage = 0.5;
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
    Enemy_Skill skill1 = {1, "attack", "Fireball", vector<string>{"m_cont_hp_const -15 4"}};
    Enemy_Skill skill2 = {2, "defend", "Protection", vector<string>{"e_def 15 10"}};
    Enemy_Skill skill3 = {3, "attack", "Claw Strike", vector<string>{"m_cont_hp_const -10 4", "m_hp 1.1 0","e_crit_chance 0.2, 6"}};
    Enemy_Skill skill4 = {4, "interfere", "Roar", vector<string>{ "m_atk -10 4", "m_def -10 4", "e_def 10 4", "e_atk 10 4"}};
    Enemy_Skill skill5 = {5, "regenerate", "Healing Pearl", vector<string>{"e_hp 30 0"}};
    Enemy_Skill skill6 = {6, "attack", "Dragon Fury", vector<string>{"e_hp -50 0","m_hp 100 0"}};
    Enemy_Skill skill7 = {7, "attack", "Tail Swipe", vector<string>{"m_hp 1.3 0"}};
    Enemy_Skill skill8 = {8, "defend", "Dodge", vector<string>{"e_def 50 2"}};
    Enemy_Skill skill9 = {9, "regenerate", "Hot Spring", vector<string>{"e_cont_hp_const 20 3", "e_hp 10 0", "e_atk 10 6"}};
    skill_list.push_back(skill1);
    skill_list.push_back(skill2);
    skill_list.push_back(skill3);
    skill_list.push_back(skill4);
    skill_list.push_back(skill5);
    skill_list.push_back(skill6);
    skill_list.push_back(skill7);
    skill_list.push_back(skill8);
    skill_list.push_back(skill9);
}

Demon::Demon(){
    hp = 350;
    atk = 70;
    def = 50;
    critical_chance = 0.05;
    critical_damage = 0.5;
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
    Enemy_Skill skill1 = {1, "attack", "Venom", vector<string>{"m_hp 2 0", "m_cont_hp -0.6 3"}};
    Enemy_Skill skill2 = {2, "interfere", "Fire form the HELL", vector<string>{"m_cont_hp -0.2 4", "m_atk -25 8", "m_def -25 8"}};
    Enemy_Skill skill3 = {3, "interfere", "MP Stealing", vector<string>{"m_mp -50 0", "m_atk -10 3"}};
    Enemy_Skill skill4 = {4, "attack", "Horror", vector<string>{"m_hp -2.4 3", "m_cont_hp_const -15 3"}};
    Enemy_Skill skill5 = {5, "regenerate", "Infection", vector<string>{"e_cont_hp 1 3", "m_cont_hp -1.5 3", "m_hp 0.9 0"}};
    Enemy_Skill skill6 = {6, "defend", "You Shall Not Pass", vector<string>{"e_def 20 8", "e_cont_hp_const 5 2"}};
    Enemy_Skill skill7 = {7, "interfere", "Sarifice", vector<string>{"e_hp -20 0", "e_def -10 6", "e_crit_chance 1 4", "e_crit_damage 2 4"}};
    Enemy_Skill skill8 = {8, "defend", "Solidified", vector<string>{"e_def 1000 2"}};
    Enemy_Skill skill9 = {9, "attack", "Damage Shift", vector<string>{"m_hp 1 0", "m_cont_hp 1 2", "e_hp 20 0", "e_cont_hp 1 2"}};
    Enemy_Skill skill10 = {10, "regenerate", "Coming from Abyss", vector<string>{"e_cont_hp_const 100 3"}};
    Enemy_Skill skill11 = {11, "interfere", "Final Form", vector<string>{"e_cont_hp 1 3", "e_atk 40 4", "e_def 30 4", "e_crit_chance 0.6 4", "e_crit_damage 4 4"}};
    Enemy_Skill skill12 = {12, "attack", "Ignite", vector<string>{"m_cont_hp 1 3", "m_cont_hp 5 3", "m_def -10 6"}};
    skill_list.push_back(skill1);
    skill_list.push_back(skill2);
    skill_list.push_back(skill3);
    skill_list.push_back(skill4);
    skill_list.push_back(skill5);
    skill_list.push_back(skill6);
    skill_list.push_back(skill7);
    skill_list.push_back(skill8);
    skill_list.push_back(skill9);
    skill_list.push_back(skill10);
    skill_list.push_back(skill11);
    skill_list.push_back(skill12);
}

Titan::Titan(){
    hp = 500;
    atk = 100;
    def = 100;
    critical_chance = 0.05;
    critical_damage = 0.5;
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
    Enemy_Skill skill1 = {1, "attack", "Thunder Strike", vector<string>{"m_cont_hp 1.2 3"}};
    Enemy_Skill skill2 = {2, "interfere", "Mind Control", vector<string>{"m_atk -20 3", "m_def -15 3", "e_atk 20 3", "e_def 15 3"}};
    Enemy_Skill skill3 = {3, "defend", "Diamond Shield", vector<string>{"e_def 30 3", "e_cont_hp_const 10 3"}};
    Enemy_Skill skill4 = {4, "attack", "Venomous Bite", vector<string>{"m_hp 1.2 0", "m_cont_hp_const -10 3"}};
    Enemy_Skill skill5 = {5, "regenerate", "Healing Touch", vector<string>{"m_hp 1.1 0", "e_cont_hp_const 30 2"}};
    Enemy_Skill skill6 = {6, "interfere", "Confusion", vector<string>{"m_atk -10 2", "m_def -10 2", "e_atk 10 2", "e_def 10 2", "e_crit_chance 0.5 2","e_crit_damage 0.3 2"}};
    Enemy_Skill skill7 = {7, "attack", "Blazing Inferno", vector<string>{"m_cont_hp_const -5 3", "m_hp 1.1 0"}};
    Enemy_Skill skill8 = {8, "regenerate", "Natural Regeneration", vector<string>{"e_cont_hp_const 20 3"}};
    Enemy_Skill skill9 = {9, "defend", "Iron Will", vector<string>{"e_def 30 3"}};
    Enemy_Skill skill10 = {10, "attack", "Jesus", vector<string>{"m_hp 1.5 0", "e_crit_chance 0.5 2", "e_crit_damage 0.3 2"}};
    skill_list.push_back(skill1);
    skill_list.push_back(skill2);
    skill_list.push_back(skill3);
    skill_list.push_back(skill4);
    skill_list.push_back(skill5);
    skill_list.push_back(skill6);
    skill_list.push_back(skill7);
    skill_list.push_back(skill8);
    skill_list.push_back(skill9);
    skill_list.push_back(skill10);
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
                critical_chance = dummyEnemy->critical_chance;
                critical_damage = dummyEnemy->critical_damage;
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
                critical_chance = goblinEnemy->critical_chance;
                critical_damage = goblinEnemy->critical_damage;
                name = goblinEnemy->name;
                image = goblinEnemy->image;
                height = image.size();
                width = image[0].size();
                skill_list = goblinEnemy->skill_list;
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
                critical_chance = mutantEnemy->critical_chance;
                critical_damage = mutantEnemy->critical_damage;
                name = mutantEnemy->name;
                image = mutantEnemy->image;
                height = image.size();
                width = image[0].size();
                skill_list = mutantEnemy->skill_list;
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
                critical_chance = dragonEnemy->critical_chance;
                critical_damage = dragonEnemy->critical_damage;
                name = dragonEnemy->name;
                image = dragonEnemy->image;
                height = image.size();
                width = image[0].size();
                skill_list = dragonEnemy->skill_list;
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
                critical_chance = robotEnemy->critical_chance;
                critical_damage = robotEnemy->critical_damage;
                name = robotEnemy->name;
                image = robotEnemy->image;
                height = image.size();
                width = image[0].size();
                skill_list = robotEnemy->skill_list;
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
                critical_chance = demonEnemy->critical_chance;
                critical_damage = demonEnemy->critical_damage;
                name = demonEnemy->name;
                image = demonEnemy->image;
                height = image.size();
                width = image[0].size();
                skill_list = demonEnemy->skill_list;
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
                critical_chance = titanEnemy->critical_chance;
                critical_damage = titanEnemy->critical_damage;
                name = titanEnemy->name;
                image = titanEnemy->image;
                height = image.size();
                width = image[0].size();
                skill_list = titanEnemy->skill_list;
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

