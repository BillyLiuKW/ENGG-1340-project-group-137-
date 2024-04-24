#ifndef GAME_HPP
#define GAME_HPP

#include "character.hpp"
#include "screen.hpp"
#include "moves.hpp"
using namespace std;
class GAME{
    public:
        Screen display; // size of the display screen
        GAME() : display(60, 75){};
        // To handle the game logic.
        void StartGame(MainCharacter& m, Enemy& e);
        // To display the gameplay screen. 
        void Display(const string& Maincharacter_name, int Maincharacter_hp, int Maincharacter_atk, const string& enemy_name, int enemy_hp, int enemy_atk);
        // To check whether the character dies. It can check both ends.
        bool survive(int hp);
        //To handle the victory in each level.
        void Victory(MainCharacter &m, Enemy &e, Screen &display);
        // To retry the game.
        void Gameretry();
        //For levels distributing rewards for player.
        int current_level = 1;
        void reward(MainCharacter &m, int level);
        //To save to the level.
        void stats(MainCharacter &m, int lucky_draw_no, int health, int attack, int defence, int magic);
        void skill(MainCharacter &m, int lucky_draw_no);
};


#endif
