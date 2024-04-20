//Write moves (for main character)
#include <iostream>
#include <vector>
#include "character.hpp"

#include "moves.hpp"
using namespace std;

void moves::Maincharacter_ExecuteMove(int ID,MainCharacter m){
  switch(ID){
    case 1:
      basic_attack(m);
      break;
    case 2:
      fire();
      break;
    case 3:
      water();
      break;
    case 4:
      vampire(m);
    case 5:
      heal();
    case 6:
      freeze(m);
    case 7:
      anger(m);    
    case 8:
      weaken(m);
    case 9:
      defence(m);
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

int moves::defence(MainCharacter m){
  cout << "DEFENCE" << endl;
  return m.def * 1.5 ;
}

int moves::weaken(MainCharacter m){ //weaken oppenent = increase atk + self defence
  cout << "Mali-Mali-Home" <<endl;
  return m.atk * 1.5;
}

int moves::freeze(MainCharacter m){ // atk enemy without receiving damage
  cout << "Let it go~~~ Let it go~~~ " << endl;
  return m.atk;
}

int moves::anger(MainCharacter m){ //1.5 damage;
  cout << "argh!!!" << endl;
  return m.atk * 1.5;
}

int moves::heal(){
  cout << "Angel is coming" << endl;
  return 20;
}

int moves::vampire(MainCharacter m){ // hp+ half maincharacter atk, atk = half of maincharacter atk
  cout << "Hiss!" << endl;
  return m.atk/2;
}

int moves::basic_attack(MainCharacter m){
  cout << "Attack !!!" << endl;
  return m.atk;
}

int moves::fire(){
  cout << "Fire! Roar!" << endl;
  return 50;
}
int moves::water(){
  cout << "Water! Splash!" << endl;
  return 10;
}
    




