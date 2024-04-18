#ifndef GAME_HPP
#define GAME_HPP

#include "character.hpp"
#include "screen.hpp"
using namespace std;
class GAME{
    public:
        Screen display(50, 50); // size of the display screen
        // To handle the game logic.
        void StartGame(MainCharacter& m, Enemy& e);
        // To display the gameplay screen. 
        void Display(const string& Maincharacter_name, int Maincharacter_hp, int Maincharacter_atk, const string& enemy_name, int enemy_hp, int enemy_atk);
        // To check whether the character dies. It can check both ends.
        bool survive(int hp);
        // To check whether the user choose skill out of range (e.g. there are totally 4 skills but the user chose the 5th skill)
        bool invalid_skill(int chosen);
};


#endif
