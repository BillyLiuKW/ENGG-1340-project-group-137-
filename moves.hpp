#ifndef MOVES_HPP
#define MOVES_HPP

#include "character.hpp"
using namespace std;
class moves{
    public:
        void ExecuteMove(int ID);
        void getMoveName(int ID);
        //Get the name of the move
        void addMove(MainCharacter& character, int ID);
        //Add moves to character's moveSet
        void select_move_to_change(MainCharacter& character,int index, int ID);
        //Allows user to select a move to change

    private:
        int water();
        int fire();

};

#endif