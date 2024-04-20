#ifndef MOVES_HPP
#define MOVES_HPP

#include "character.hpp"
#include <vector>
#include <map>
#include <functional>
#include <string>
using namespace std;
struct Move_info{ //Store the information of the move
        string name;
        int ID;
        double power; //The power of the move 
        int cost;
        char type;
        //Physical moves cost HP to cast
        //Magical moves cost MP to cast
        //Damage formula is self_atk * power / enemy_def, so 25 atk * 50 power / 50 def = 25 damage
    };

int calculate_damage(double power, int self_atk, int enemy_def); //Apply the damage formula

void slash(MainCharacter &m, Enemy &e, Move_info info); //Define moves outside moves class
class moves{
    public:

        static void iniializeMoves(); // Initialize the moves for the function map

        void Maincharacter_ExecuteMove(int ID, MainCharacter &m, Enemy &e);

        void getMoveName(int ID);
        //Get the name of the move

        void addMove(MainCharacter& character, int ID);
        //Add moves to character's moveSet

        void select_move_to_change(MainCharacter& character,int index, int ID);
        //Allows user to select a move to change

    private:
        static map<int, function<void(MainCharacter&, Enemy&, Move_info)> > moveFunctions; //Create a function map for executing move functions

        static vector<Move_info> FULL_MOVE_POOL;

        void check_cost(); // Check if the character has enough HP/MP to cast the move


        

};

#endif