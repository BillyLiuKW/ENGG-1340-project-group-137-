//Write moves (for main character)
#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include <string>
#include "character.hpp"
#include "moves.hpp"

using namespace std;
map<int, function<void(MainCharacter&, Enemy&, Move_info)> > moves::moveFunctions;
vector<Move_info> moves::FULL_MOVE_POOL;

int calculate_damage(double power, int self_atk, int enemy_def){
  int damage = self_atk * power / enemy_def;
  return damage;
}

void slash(MainCharacter &m, Enemy &e,Move_info info){
  int damage = calculate_damage(info.power, m.atk, e.def);
  e.hp -= damage;

}

void moves::iniializeMoves(){
  Move_info slashInfo = {"Slash", 0 ,10, 20, 'p'};
  FULL_MOVE_POOL.push_back(slashInfo);
  moveFunctions[0] = slash;
  //Follow this format to define more moves
}

void moves::Maincharacter_ExecuteMove(int index,MainCharacter &m, Enemy &e){
  int ID = m.moveSet[index-1];
  Move_info move = FULL_MOVE_POOL[ID];
  moveFunctions[move.ID](m,e,move); //Execute the move function
  
}

void moves::addMove(MainCharacter& character, int ID){
    if (character.moveSet.size() <= 4){
      character.moveSet.push_back(ID);
      cout << "Move added!" << endl;
    }
}

void moves::select_move_to_change(MainCharacter& character, int index, int ID){
    //Note that the player would see {1,2,3,4} instead of {0,1,2,3}
    character.moveSet[index-1] = ID;
    cout << "Move changed!" << endl;
}








