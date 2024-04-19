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
};

#endif
