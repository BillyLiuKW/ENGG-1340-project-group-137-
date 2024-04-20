#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <vector>
#include <string>
#include <vector>
using namespace std;

// does not include normal attack
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
        vector<int> moveSet;
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
        string name;
        vector<string> image;
        int height;
        int width;
};
class Mutant{
    public:
        Mutant();
        int hp;
        int atk;
        int def;
        string name;
        vector<string> image;
        int height;
        int width;
};
class Robot{
    public:
        Robot();
        int hp;
        int atk;
        int def;
        string name;
        vector<string> image;
        int height;
        int width;
};
class Dragon{
    public:
        Dragon();
        int hp;
        int atk;
        int def;
        string name;
        vector<string> image;
        int height;
        int width;
};
class Enemy{
    public:
        Enemy(int type);
        int hp;
        int max_hp;
        int atk;
        int def;
        string name;
        vector<string> image;
        int height;
        int width;
        vector<Enemy_Skill> skill_list;
};

#endif
