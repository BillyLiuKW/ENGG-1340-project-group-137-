#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <vector>
#include <string>
#include <vector>
#include <utility>
using namespace std;

// does not include normal attack

struct Move_info{ //Store the information of the move
        string name;
        int ID;
        int power; //The power of the move 
        int cost;
        string type;
        //Physical moves cost HP to cast
        //Magical moves cost MP to cast
        //Damage formula is self_atk * power / enemy_def, so 25 atk * 50 power / 50 def = 25 damage
    };

struct Enemy_Skill{
    int index; // index of the skill in the skill_list (start at 1) 0 is normal attack
    string type; // basic type of the skill: attack/ defend/ interfere (buff or debuff)/ regenerate 
    string skill_name;
    vector<string> effect;
    int uses; //if the skill is used more, it will have lower chance to be used. set to 0 if all 
};

class MainCharacter{
    public:
        MainCharacter(); // Constructer
        int hp;
        int max_hp;
        int atk;
        int def;
        vector<pair<int, int> > atk_boost = {}; // use {boost value, how many round remain} store the buff in attack
        int atk_boost_sum = 0; // the total buff after each move.
        vector<pair<int, int> > def_boost = {}; // same 
        int def_boost_sum = 0; 
        vector<pair<int, int> > hp_boost = {}; // continue damage or regeneration
        int mp;
        int max_mp;
        vector<int> moveSet;
        vector<Move_info> boosted_moves;
        string name;
        vector<string> image;
        int height;
        int width;

};
class Dummy{
    public:
        Dummy();
        int hp;
        int atk;
        int def;
        double critical_chance;
        double critical_damage;
        string name;
        vector<string> image;
        int height;
        int width;
        vector<Enemy_Skill> skill_list;
};
class Goblin{
    public:
        Goblin();
        int hp;
        int atk;
        int def;
        double critical_chance;
        double critical_damage;
        string name;
        vector<string> image;
        int height;
        int width;
        vector<Enemy_Skill> skill_list;
};
class Mutant{
    public:
        Mutant();
        int hp;
        int atk;
        int def;
        double critical_chance;
        double critical_damage;
        string name;
        vector<string> image;
        int height;
        int width;
        vector<Enemy_Skill> skill_list;
};
class Robot{
    public:
        Robot();
        int hp;
        int atk;
        int def;
        double critical_chance;
        double critical_damage;
        string name;
        vector<string> image;
        int height;
        int width;
        vector<Enemy_Skill> skill_list;
};
class Dragon{
    public:
        Dragon();
        int hp;
        int atk;
        int def;
        double critical_chance;
        double critical_damage;
        string name;
        vector<string> image;
        int height;
        int width;
        vector<Enemy_Skill> skill_list;
};
class Demon{
    public:
        Demon();
        int hp;
        int atk;
        int def;
        double critical_chance;
        double critical_damage;
        string name;
        vector<string> image;
        int height;
        int width;
        vector<Enemy_Skill> skill_list;
};
class Titan{
    public:
        Titan();
        int hp;
        int atk;
        int def;
        double critical_chance;
        double critical_damage;
        string name;
        vector<string> image;
        int height;
        int width;
        vector<Enemy_Skill> skill_list;
};
class Enemy{
    public:
        Enemy(int type);
        int hp;
        int max_hp;
        int atk;
        int def;
        double critical_chance; // 0-1
        double critical_damage; // e.g. 0.5 = 150% damage
        vector<pair<int, int> > atk_boost = {}; // use {boost value, how many round remain}
        int atk_boost_sum = 0;
        vector<pair<int, int> > def_boost = {};
        int def_boost_sum = 0;
        vector<pair<int, int> > hp_boost = {}; // continue damage or regeneration
        vector<pair<double, int> > crit_chance_boost = {};
        double crit_chance_boost_sum = 0;
        vector<pair<double, int> > crit_damage_boost = {};
        double crit_damage_boost_sum = 0;
        string name;
        vector<string> image;
        int height;
        int width;
        vector<Enemy_Skill> skill_list;
};

#endif
