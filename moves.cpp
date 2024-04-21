//Write moves (for main character)
#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include <string>
#include <cstdlib>
#include <ctime>
#include "character.hpp"
#include "moves.hpp"

using namespace std;
map<int, function<void(MainCharacter&, Enemy&, Move_info)> > moves::moveFunctions;
vector<Move_info> moves::FULL_MOVE_POOL;

int calculate_damage(int power, int self_atk, int enemy_def){
  int damage = (power * self_atk / enemy_def);
  return damage;
}

void Critical_hit(int &dmg, int chance = 10){
  srand(time(0));
  int random = rand() % 100;
  if (random < chance){
    cout << "Critical hit!" << endl;
    dmg *= 1.5;
  }
}

void slash(MainCharacter &m, Enemy &e,Move_info info){
  int damage = calculate_damage(info.power, m.atk, e.def);
  m.hp -= info.cost;
  Critical_hit(damage);
  e.hp -= damage;
}

void fireball(MainCharacter &m, Enemy &e, Move_info info){
  int damage = calculate_damage(info.power, m.atk, e.def);
  m.mp -= info.cost;
  e.hp -= damage;
}

void moves::iniializeMoves(){
  Move_info slashInfo = {"Slash", 0 ,10, 10, 'p'};
  FULL_MOVE_POOL.push_back(slashInfo);
  moveFunctions[0] = slash;
  //Follow this format to define more moves
  Move_info fireballInfo = {"Fireball", 1, 20, 20, 'm'};
}

bool moves::Maincharacter_ExecuteMove(int index,MainCharacter &m, Enemy &e){
  int ID = m.moveSet[index-1];
  Move_info move = FULL_MOVE_POOL[ID];
  if (!check_cost(m, move)){
    return false; //Unable to cast the move
  }
  cout << "Used " << move.name << " !" << endl;
  moveFunctions[move.ID](m,e,move); //Execute the move function
  return true;
  
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

string moves::getMoveName(int ID){
  return FULL_MOVE_POOL[ID].name;
}

bool moves::check_cost(MainCharacter &m, Move_info move){
  if (move.type == 'p' && m.hp < move.cost){
    return false;
  }
  else{
    if (m.mp < move.cost && move.type == 'm'){
      return false;
    }
  }
  return true; // enough HP/MP

}






