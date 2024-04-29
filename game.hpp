#ifndef GAME_HPP
#define GAME_HPP

#include "character.hpp"
#include "screen.hpp"
#include "moves.hpp"
using namespace std;
class GAME{
    public:
        Screen display; // size of the display screen
        GAME() : display(56, 75){};
        // start a new level
        void StartGame(MainCharacter& m, Enemy& e);
        // To display the gameplay screen. 
        void Display(const string& Maincharacter_name, int Maincharacter_hp, int Maincharacter_atk, const string& enemy_name, int enemy_hp, int enemy_atk);
        // To check whether the character or enemy dies. It can check both ends.
        bool survive(int hp);
        //To handle the victory in each level.
        void Victory(MainCharacter &m, Enemy &e, Screen &display);
        // To retry the game.
        void Gameretry();
        int current_level = 1;
        //For levels distributing rewards for player.
        void reward(MainCharacter &m, int level);
        // reward player status increase
        void stats(MainCharacter &m, int lucky_draw_no, int health, int attack, int defence, int magic);
        // reward player a skill
        void skill(MainCharacter &m, int lucky_draw_no);
        // display the describtion of the skill
        void skill_desc_display(int skill_index,vector<int> moveset); //Display Description of skills

};      


#endif
