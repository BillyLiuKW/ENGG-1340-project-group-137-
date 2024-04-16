//Write moves
#include <iostream>
#include <vector>
#include "character.hpp"

#include "moves.hpp"
using namespace std;


void moves::ExecuteMove(int ID){
  switch(ID){
    case 1:
      fire();
      break;
    case 2:
      water();
      break;
    default:
      cout << "Move not found!" << endl;
      break;
  }
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




int moves::fire(){
  cout << "Fire!" << endl;
  return 50;
}
int moves::water(){
  cout << "Water!" << endl;
  return 10;
}
    




