#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <vector>
#include <string>
#include <vector>
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
        vector<string> image;
};
class Goblin{
    public:
        Goblin();
        int hp;
        int atk;
        int def;
        string name;
        vector<string> image;
};
class Enemy{
    public:
        Enemy(int type);
        int hp;
        int atk;
        int def;
        string name;
        vector<string> image;
};

#endif
