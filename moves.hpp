#ifndef MOVES_HPP
#define MOVES_HPP

#include "character.hpp"
#include <vector>
#include <map>
#include <string>
#include <functional>
#include <string>
using namespace std;

struct Move_info{ //Store the information of the move
        string name;
        int ID;
        int power; //The power of the move 
        int cost;
        string type;
        //Physical moves cost HP to cast
        //Magical moves cost MP to cast
        //Damage formula is self_atk * power / enemy_def, so 25 atk * 50 power / 50 def = 25 damage
    };


void Critical_hit(int &dmg, int chance); //Physical moves have a 10% chance to deal 50% more damage, depending on move

int calculate_damage(double power, int self_atk, int enemy_def); //Apply the damage formula
//Define moves outside moves class
void slash(MainCharacter &m, Enemy &e, Move_info info, vector<string> &dialogs); //deals phys dmg to enemy, base moves

void fireball(MainCharacter &m, Enemy &e, Move_info info, vector<string> &dialogs); //deals magic dmg to enemy, base moves

void regen(MainCharacter &m, Enemy &e, Move_info info, vector<string> &dialogs); //Restores 30% of max hp

void rage(MainCharacter &m, Enemy &e, Move_info info, vector<string> &dialogs); //Increases atk by 20% for 3 turns  

void lethal_strike(MainCharacter &m, Enemy &e, Move_info info, vector<string> &dialogs); //deals phys dmg to enemy, 50% chance to crit

void weapon_master(MainCharacter &m, Enemy &e, Move_info info, vector<string> &dialogs); //Passive move, increases power of phys move by 50%
//cannot be used

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


    private:
        static map<int, function<void(MainCharacter&, Enemy&, Move_info, vector<string> &dialogs)> > moveFunctions; //Create a function map for executing move functions

        bool check_cost(MainCharacter &m, Move_info move); // Check if the character has enough HP/MP to cast the move
    

};



#endif