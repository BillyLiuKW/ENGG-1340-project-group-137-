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
map<int, function<void(MainCharacter&, Enemy&, Move_info, vector<string> &dialogs)> > moves::moveFunctions;
vector<Move_info> moves::FULL_MOVE_POOL;

int calculate_damage(int power, int self_atk, int enemy_def){
    int damage = (power * self_atk / enemy_def);
    return damage;
}

void Critical_hit(int &dmg, vector<string> &dialogs, int chance = 10){
    srand(time(0));
    int random = rand() % 100;
    if (random < chance){
        string dialog = "<format><|bold|><|red|>Critical hit!<end>";
        dialogs.push_back(dialog);
        dmg *= 1.5;
    }
}

string display_damage(Enemy &e, int damage){
    string int_value = to_string(damage);
    string dialog = "Enemy <format><|yellow|>[" + e.name + "]<end>'s <format><|red|>HP<end>";
    dialog += " <format><|red|><|bold|>-" + int_value + "<end>";
    return dialog;
}


void slash(MainCharacter &m, Enemy &e,Move_info info, vector<string> &dialogs){
    int damage = calculate_damage(info.power, m.atk, e.def);
    m.hp -= info.cost;
    Critical_hit(damage, dialogs);
    e.hp -= damage;
    string int_value = to_string(damage);
    string dialog = display_damage(e, damage);
    dialogs.push_back(dialog);
}

void fireball(MainCharacter &m, Enemy &e, Move_info info, vector<string> &dialogs){
    int damage = calculate_damage(info.power, m.atk, e.def);
    m.mp -= info.cost;
    e.hp -= damage;
    string int_value = to_string(damage);
    string dialog = display_damage(e, damage);
    dialogs.push_back(dialog);
}

void regen(MainCharacter &m, Enemy &e, Move_info info, vector<string> &dialogs){ //30% max hp
    int regeneration = info.power * m.max_hp;
    if (m.hp + regeneration > m.max_hp){
        regeneration = m.max_hp - m.max_hp;
        m.hp = m.max_hp;
    }
    else{
        m.hp += regeneration;
    }
    m.mp -= info.cost;
    string int_value = to_string(regeneration);
    string dialog = "<format><|blue|>Hero<end> <format><|red|>HP<end> <format><|green|><|bold|>+"+ int_value + "<end>";
    dialogs.push_back(dialog);
}

void rage(MainCharacter &m, Enemy &e, Move_info info, vector<string> &dialogs){ //20% atk for 3 turns
    //m.atk *= 1.2; //temp code
    int increase = m.atk * (info.power - 1); // calculate how many atk increase
    m.atk_boost.push_back(make_pair(increase, 3));
    m.mp -= info.cost;
    string int_value_1 = to_string(increase*100);
    string dialog = "<format><|blue|>Hero<end> <format><|cyan|>ATK<end> increases ";
    dialog += " <format><|bold|><green>" + int_value_1 + "%<end>";
    dialog += "<end> for <format><|yellow|>3<end> rounds.";
    dialogs.push_back(dialog);
}

void lethal_strike(MainCharacter &m, Enemy &e, Move_info info, vector<string> &dialogs){
  int damage = calculate_damage(info.power, m.atk, e.def);
  m.hp -= info.cost;
  Critical_hit(damage, dialogs,50);
  e.hp -= damage;
  string dialog = display_damage(e, damage);
  dialogs.push_back(dialog);
}






void moves::iniializeMoves(){
    Move_info slashInfo = {"Slash", 0 ,20, 10, "Physical"};
    FULL_MOVE_POOL.push_back(slashInfo);
    moveFunctions[0] = slash;
    //Follow this format to define more moves
    Move_info fireballInfo = {"Fireball", 1, 20, 20, "Magical"};
    FULL_MOVE_POOL.push_back(fireballInfo);
    moveFunctions[1] = fireball;
    Move_info regenInfo = {"Regen", 2, 30, 30, "Magical"};
    moveFunctions[2] = regen;
    FULL_MOVE_POOL.push_back(regenInfo);
    Move_info rageInfo = {"Rage", 3, 20, 30, "Magical"};
    moveFunctions[3] = rage;
    FULL_MOVE_POOL.push_back(rageInfo);
    Move_info lethal_strikeInfo = {"Lethal Strike", 4, 30, 30, "Physical"};
    moveFunctions[4] = lethal_strike;
    FULL_MOVE_POOL.push_back(lethal_strikeInfo);
    Move_info weapon_masterInfo = {"Weapon Master", 5, 0, 0, "Passive"};
    moveFunctions[5] = weapon_master;
    FULL_MOVE_POOL.push_back(weapon_masterInfo);

}

bool moves::Maincharacter_ExecuteMove(int index,MainCharacter &m, Enemy &e){
    if (index > m.moveSet.size() || index < 1){
        cout << "Error: Invalid move index!" << endl;
        cout << "Please try again!" << endl;
        return false; //Invalid move
    }
    int ID = m.moveSet[index-1];
    Move_info move = FULL_MOVE_POOL[ID];
    if (!check_cost(m, move)){
        cout << "Error! Not enough HP/MP!" << endl;
        cout << "Please try again!" << endl;
        return false; //Unable to cast the move
    }
    if (move.type == "Passive"){
        cout << "Error! Passive Moves Cannot be Used!" << endl;
        cout << "Please try again!" << endl;
        return false; //Passive moves cannot be used
    }
    string dialog = "<format><|blue|>" + m.name + "<end> used <format><|purple|>["  + move.name + "]<end>!";
    //dialog += (move.cost > 0)? ("<format><|blue|>MP<end> <format><|blue|><|bold>-" + to_string(move.cost) + "<end>") : "" ;
    dialogs.push_back(dialog);
    moveFunctions[move.ID](m,e,move, dialogs); //Execute the move function
    return true;
  
}

void moves::addMove(MainCharacter& character, int ID){
    //Note that the player would see {1,2,3,4} instead of {0,1,2,3}
    int index;
    if (character.moveSet.size() <= 4){
      character.moveSet.push_back(ID);
      cout << "Move added!" << endl;
    }
    else{
      cout << "Select a move to change (1-4): ";
      cin >> index;
      character.moveSet[index-1] = ID;
      cout << "Move changed!" << endl;
    }
}


string moves::getMoveName(int ID){
    return FULL_MOVE_POOL[ID].name;
}

bool moves::check_cost(MainCharacter &m, Move_info move){
    if (move.type == "Physical" && m.hp < move.cost){
        return false;
    }
    else{
        if (m.mp < move.cost && move.type == "Magical"){
        return false;
        }
    }
    return true; // enough HP/MP
}




