#include <iostream>
#include <vector>
#include <sstream>
#include <string>   
#include "character.h"
using namespace std;

class MainCharacter{
    public:
        int hp = 100; // Numbers subject to change
        int atk = 25;
        int def = 10;
        vector<void (*)(std::string)> moveSets; //Function pointers in a vector to store movesets

        void visual(){
            stringstream ss;
            ss << "Hero: "<< endl << "HP: " << hp << endl << "ATK: " << atk << endl << "DEF: " << def;
            cout << ss.str();
        }
};

int main(){
    MainCharacter me;
    me.visual();
    return 0;
}