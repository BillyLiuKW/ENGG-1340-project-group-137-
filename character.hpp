#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <vector>
#include <string>
using namespace std;

class MainCharacter{
    public:
        MainCharacter(); // Constructer
        int hp;
        int atk;
        vector<int> moveSet;
        string name;

};
class Dummy{
    public:
        Dummy();
        int hp;
        int atk;
        int def;
        string name;
};
class Goblin{
    public:
        Goblin();
        int hp;
        int atk;
        int def;
        string name;
};
class Enemy{
    public:
        Enemy(int type);
        int hp;
        int atk;
        int def;
        string name;
};

#endif