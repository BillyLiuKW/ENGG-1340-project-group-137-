#ifndef GAME_HPP
#define GAME_HPP

#include "character.hpp"
#include "screen.hpp"
#include "moves.hpp"
using namespace std;
class GAME{
    public:
        Screen display; // size of the display screen
        moves skills;
        GAME() : display(60, 50){};
        // To handle the game logic.
        void StartGame(MainCharacter& m, Enemy& e);
        // To display the gameplay screen. 
        void Display(const string& Maincharacter_name, int Maincharacter_hp, int Maincharacter_atk, const string& enemy_name, int enemy_hp, int enemy_atk);
        // To check whether the character dies. It can check both ends.
        bool survive(int hp);
        // To check whether the user choose skill out of range (e.g. there are totally 4 skills but the user chose the 5th skill)
        bool invalid_skill(int chosen);
        //To handle the victory in each level.
        void Victory(MainCharacter &m, Enemy &e);
        // To retry the game.
        void Gameretry();
        //For levels distributing rewards for player.
        void reward();
        //To save to the level.
        int current_level = 1;
};


#endif
