#ifndef MOVES_HPP
#define MOVES_HPP

#include "character.hpp"
#include <vector>
#include <map>
#include <string>
#include <functional>
#include <string>
using namespace std;




void Critical_hit(int &dmg, vector<string> &dialogs,int chance); //Physical moves have a 10% chance to deal 50% more damage, depending on move

void miss(int &dmg, ,vector<string> &dialogs,int chance); //Use this for moves that have a chance to miss

int calculate_damage(double power, int self_atk, int enemy_def); //Apply the damage formula
//Define moves outside moves class
void slash(MainCharacter &m, Enemy &e, Move_info info, vector<string> &dialogs); //deals phys dmg to enemy, base moves

void fireball(MainCharacter &m, Enemy &e, Move_info info, vector<string> &dialogs); //deals magic dmg to enemy, base moves

void regen(MainCharacter &m, Enemy &e, Move_info info, vector<string> &dialogs); //Restores 30% of max hp

void rage(MainCharacter &m, Enemy &e, Move_info info, vector<string> &dialogs); //Increases atk by 20% for 3 turns  

void lethal_strike(MainCharacter &m, Enemy &e, Move_info info, vector<string> &dialogs); //deals phys dmg to enemy, 50% chance to crit

void weapon_master(MainCharacter &m, Enemy &e, Move_info info, vector<string> &dialogs); //Passive move, increases power of phys move by 50%
//cannot be used

void mastery_of_magic(MainCharacter &m, Enemy &e, Move_info info, vector<string> &dialogs); //Passive move, increases power of magic move by 50%

void efficient_tactics(MainCharacter &m, Enemy &e, Move_info info, vector<string> &dialogs); //Passive move, reduces cost of all moves by 30%

void life_siphon(MainCharacter &m, Enemy &e, Move_info info, vector<string> &dialogs); //deals phys dmg to enemy, heals 50% of dmg dealt

void sluggish_strike(MainCharacter &m, Enemy &e, Move_info info, vector<string> &dialogs); //deals phys dmg to enemy, but chance to miss/ cost 0 hp

class moves{
    public:
        moves(vector<string> &dialogs_list): dialogs(dialogs_list) {}
        static void iniializeMoves(); // Initialize the moves for the function map

        vector<string> &dialogs;

        bool Maincharacter_ExecuteMove(int ID, MainCharacter &m, Enemy &e);

        string getMoveName(int ID);
        //Get the name of the move

        static void addMove(MainCharacter& character, int ID);
        //Add moves to character's moveSet
        static vector<Move_info> FULL_MOVE_POOL;

        void deleteMove(MainCharacter& character, int ID); // For testing purposes


    private:
        static map<int, function<void(MainCharacter&, Enemy&, Move_info, vector<string> &dialogs)> > moveFunctions; //Create a function map for executing move functions

        bool check_cost(MainCharacter &m, Move_info move); // Check if the character has enough HP/MP to cast the move
    
        void restore_passive(MainCharacter &m); //Restore the power of the moves after the passive for each turn
};



#endif