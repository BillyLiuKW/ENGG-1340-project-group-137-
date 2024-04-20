#ifndef MOVES_HPP
#define MOVES_HPP

#include "character.hpp"
using namespace std;
class moves{
    public:
        void Maincharacter_ExecuteMove(int ID, MainCharacter m);
        void getMoveName(int ID);
        //Get the name of the move
        void addMove(MainCharacter& character, int ID);
        //Add moves to character's moveSet
        void select_move_to_change(MainCharacter& character,int index, int ID);
        //Allows user to select a move to change

    private:
        int water();
        int fire();
        int basic_attack(MainCharacter m);
        int vampire(MainCharacter m);
        int heal();
        int freeze(MainCharacter m);
        int anger(MainCharacter m);
        int defence(MainCharacter m);
        int weaken(MainCharacter m);
};

#endif