//Write moves (for main character)
#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include "character.hpp"
#include <limits>
#include <cmath>
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

void miss(int &dmg, vector<string> &dialogs, int chance){
    srand(time(0));
    int random = rand() % 100;
    if (random < chance){
        string dialog = "<format><|bold|><|red|>The Attack missed!<end>";
        dialogs.push_back(dialog);
        dmg = 0;
    }
}

string display_damage(Enemy &e, int damage){
    string int_value = to_string(damage);
    string dialog = "Enemy <format><|yellow|>[" + e.name + "]<end>'s <format><|red|>HP<end>";
    dialog += " <format><|red|><|bold|>-" + int_value + "<end>";
    return dialog;
}


void slash(MainCharacter &m, Enemy &e,Move_info info, vector<string> &dialogs){
    int damage = calculate_damage(info.power, m.atk + m.atk_boost_sum, e.def + e.def_boost_sum);
    m.hp -= info.cost;
    Critical_hit(damage, dialogs);
    e.hp -= damage;
    string int_value = to_string(damage);
    string dialog = display_damage(e, damage);
    dialogs.push_back(dialog);
}

void fireball(MainCharacter &m, Enemy &e, Move_info info, vector<string> &dialogs){
    int damage = calculate_damage(info.power, m.atk + m.atk_boost_sum, e.def + e.def_boost_sum);
    m.mp -= info.cost;
    e.hp -= damage;
    string int_value = to_string(damage);
    string dialog = display_damage(e, damage);
    dialogs.push_back(dialog);
}

void regen(MainCharacter &m, Enemy &e, Move_info info, vector<string> &dialogs){ //30% max hp
    int regeneration = info.power/100 * m.max_hp;
    if (m.hp + regeneration > m.max_hp){
        m.hp = m.max_hp;
    }
    else{
        m.hp += regeneration;
    }
    m.mp -= info.cost;
    string int_value = to_string(regeneration);
    string dialog = "<format><|blue|>" + m.name + "<end> <format><|red|>HP<end> <format><|green|><|bold|>+"+ int_value + "<end>";
    dialogs.push_back(dialog);
}

void rage(MainCharacter &m, Enemy &e, Move_info info, vector<string> &dialogs){ //20% atk for 3 turns
    int increase = info.power * m.atk / 100; // calculate how many atk increase
    m.atk_boost.push_back(make_pair(increase, 3*2)); // every rounds will minus 2;
    m.mp -= info.cost;
    string int_value_1 = to_string(increase);
    string int_value_2 = to_string(info.power);
    string dialog = "<format><|blue|>" + m.name + "<end> <format><|cyan|>ATK<end> increases ";
    dialog += " <format><|bold|><|green|>" + int_value_1 + "(" + int_value_2 + "%)<end>";
    dialog += " for <format><|yellow|>3<end> rounds.";
    dialogs.push_back(dialog);
}

void lethal_strike(MainCharacter &m, Enemy &e, Move_info info, vector<string> &dialogs){
  int damage = calculate_damage(info.power, m.atk + m.atk_boost_sum, e.def + e.def_boost_sum);
  m.hp -= info.cost;
  Critical_hit(damage, dialogs,50);
  e.hp -= damage;
  string dialog = display_damage(e, damage);
  dialogs.push_back(dialog);
}

void weapon_master(MainCharacter &m, Enemy &e, Move_info info, vector<string> &dialogs){ //passive
    for (int i = 0; i < m.moveSet.size(); i++){
        if (moves::FULL_MOVE_POOL[m.moveSet[i]].type == "Physical"){
            m.boosted_moves.push_back(moves::FULL_MOVE_POOL[m.moveSet[i]]); //Store the unboosted moves info
            moves::FULL_MOVE_POOL[m.moveSet[i]].power *= 1.3; //Boost the power of the move
        }
    }
}

void mastery_of_magic(MainCharacter &m, Enemy &e, Move_info info, vector<string> &dialogs){ //passive
    for (int i = 0; i < m.moveSet.size(); i++){
        if (moves::FULL_MOVE_POOL[m.moveSet[i]].type == "Magical"){
            m.boosted_moves.push_back(moves::FULL_MOVE_POOL[m.moveSet[i]]); //Store the unboosted moves info
            moves::FULL_MOVE_POOL[m.moveSet[i]].power *= 1.3; //Boost the power of the move
        }
    }
}

void efficient_tactics(MainCharacter &m, Enemy &e, Move_info info, vector<string> &dialogs){ //passive
    for (int i = 0; i < m.moveSet.size(); i++){
        if (moves::FULL_MOVE_POOL[m.moveSet[i]].type != "Passive"){
            m.boosted_moves.push_back(moves::FULL_MOVE_POOL[m.moveSet[i]]); //Store the unboosted moves info
            moves::FULL_MOVE_POOL[m.moveSet[i]].cost *= 0.7; //Reduce the cost of the move by 30% 
        }
    }
}

void life_siphon(MainCharacter &m, Enemy &e, Move_info info, vector<string> &dialogs){
    int damage = calculate_damage(info.power, m.atk + m.atk_boost_sum, e.def + e.def_boost_sum);
    m.mp -= info.cost;
    e.hp -= damage;
    int heal = damage * 0.5;
    if (m.hp + heal > m.max_hp){
        m.hp = m.max_hp;
    }
    else{
        m.hp += heal;
    }
    string int_value = to_string(damage);
    string dialog = display_damage(e, damage);
    dialogs.push_back(dialog);
    string int_value_1 = to_string(heal);
    dialog = "<format><|blue|>" + m.name + "<end> <format><|red|>HP<end> <format><|green|><|bold|>+"+ int_value_1 + "<end>";
    dialogs.push_back(dialog);
}


void sluggish_strike(MainCharacter &m, Enemy &e, Move_info info, vector<string> &dialogs){
    int damage = calculate_damage(info.power, m.atk + m.atk_boost_sum, e.def + e.def_boost_sum);
    miss(damage, dialogs, 50);
    if (damage == 0){
        return;
    }
    Critical_hit(damage, dialogs);
    e.hp -= damage;
    string dialog = display_damage(e, damage);
    dialogs.push_back(dialog);
}

void shield_blast(MainCharacter &m, Enemy &e, Move_info info, vector<string> &dialogs){
    int def_int = (m.def + m.def_boost_sum)*1.5; //compensate for lower def values
    int damage = calculate_damage(info.power, def_int ,  e.def + e.def_boost_sum);
    m.mp -= info.cost;
    e.hp -= damage;
    string dialog = display_damage(e, damage);
    dialogs.push_back(dialog);
}

void iron_wall(MainCharacter &m, Enemy &e, Move_info info, vector<string> &dialogs){ //20% def for 3 turns
    int increase = info.power * m.def / 100; // calculate how many def increase (exacat, not percentage)
    m.def_boost.push_back(make_pair(increase, 3*2)); // every rounds will minus 2;
    m.mp -= info.cost;
    string int_value_1 = to_string(increase);
    string int_value_2 = to_string(info.power);
    string dialog = "<format><|blue|>" + m.name + "<end> <format><|green|>DEF<end> increases ";
    dialog += " <format><|bold|><|green|>" + int_value_1 + " (" + int_value_2 + "%)<end>";
    dialog += " for <format><|yellow|>3<end> rounds.";
    dialogs.push_back(dialog);
}

void growth(MainCharacter &m, Enemy &e, Move_info info, vector<string> &dialogs){
    int increase_atk = info.power * m.atk / 100; // calculate how many atk increase
    int increase_def = info.power * m.def / 100;
    m.atk_boost.push_back(make_pair(increase_atk, 3*2)); // every rounds will minus 2;
    m.def_boost.push_back(make_pair(increase_def, 3*2)); // every rounds will minus 2;
    m.mp -= info.cost;
    string int_value_1 = to_string(info.power);
    string int_atk = to_string(increase_atk);
    string int_def = to_string(increase_def);
    string dialog = "<format><|blue|>" + m.name + "<end> <format><|green|>DEF<end> <format><|green|><|bold|>+"+ int_def + " (" + int_value_1 +"%)<end>";
    dialog += ", <format><|cyan|>ATK<end>  <format><|green|><|bold|>+" + int_atk + " (" + int_value_1 + "%)<end>";
    dialog += " for <format><|yellow|>3<end> rounds.";
    dialogs.push_back(dialog);
}

void strategist(MainCharacter &m, Enemy &e, Move_info info, vector<string> &dialogs){ //passive
    for (int i = 0; i < m.moveSet.size(); i++){
        if (moves::FULL_MOVE_POOL[m.moveSet[i]].type == "Buff"){
            m.boosted_moves.push_back(moves::FULL_MOVE_POOL[m.moveSet[i]]); //Store the unboosted moves info
            moves::FULL_MOVE_POOL[m.moveSet[i]].power += 20; //Add instead of multiply to the buff amount
        }
    }
}

void nova_blast(MainCharacter &m, Enemy &e, Move_info info, vector<string> &dialogs){
    m.mp -= info.cost;
    if (info.power == 0){
        string dialog = "<format><|blue|>" + m.name + "<end> is charging up <format><|purple|>["  + info.name + "]<end>!";
        dialogs.push_back(dialog);
        moves::FULL_MOVE_POOL[14].power = 60; //change the power to make next time this is called, it will deal damage
        moves::FULL_MOVE_POOL[14].cost = 0; //change the cost to 0 so that cost is only used initially
        return;
    }
    int damage = calculate_damage(info.power, m.atk + m.atk_boost_sum, e.def + e.def_boost_sum);
    e.hp -= damage;
    string int_value = to_string(damage);
    string dialog = display_damage(e, damage);
    dialogs.push_back(dialog);
    moves::FULL_MOVE_POOL[14].power = 0; //reset the power to 0 after dealing damage
    moves::FULL_MOVE_POOL[14].cost = 50; //reset the cost to 50 after dealing damage
}

void pain_share(MainCharacter &m, Enemy &e, Move_info info, vector<string> &dialogs){
    int missing_hp = m.max_hp - m.hp;
    int missing_hp_percent = static_cast<int>(floor(static_cast<double>(missing_hp) * 100 / m.max_hp)); //Round down to the nearest 20%
    //Increase 10 power for every 20% missing hp
    int increase = missing_hp_percent / 20 * 10; 
    int damage = calculate_damage(info.power+increase, m.atk + m.atk_boost_sum, e.def + e.def_boost_sum);
    m.mp -= info.cost;
    e.hp -= damage;
    string dialog = display_damage(e, damage);
    dialogs.push_back(dialog);
}

void poison_strike(MainCharacter &m, Enemy &e, Move_info info, vector<string> &dialogs){
    int damage = calculate_damage(info.power, m.atk + m.atk_boost_sum, e.def + e.def_boost_sum);
    m.mp -= info.cost;
    e.hp -= damage;
    e.hp_boost.push_back(make_pair(-(damage * 0.2), 3)); // poison scales 20% of initial damage every turn
    string int_value = to_string(damage);
    string dialog = display_damage(e, damage);
    dialogs.push_back(dialog);
}


void moves::iniializeMoves(){
    Move_info slashInfo = {"Slash", 0 ,20, 10, "Physical"};
    slashInfo.desc = "Deals Physical Damage";
    FULL_MOVE_POOL.push_back(slashInfo);
    moveFunctions[0] = slash;
    //Follow this format to define more moves
    Move_info fireballInfo = {"Fireball", 1, 20, 20, "Magical"};
    fireballInfo.desc = "Deals Magical Damage";
    FULL_MOVE_POOL.push_back(fireballInfo);
    moveFunctions[1] = fireball;

    Move_info regenInfo = {"Regen", 2, 30, 30, "Magical"};
    regenInfo.desc = "Restores HP";
    moveFunctions[2] = regen;
    FULL_MOVE_POOL.push_back(regenInfo);

    Move_info rageInfo = {"Rage", 3, 20, 30, "Buff"};
    rageInfo.desc = "Increases ATK for 3 turns";
    moveFunctions[3] = rage;
    FULL_MOVE_POOL.push_back(rageInfo);

    Move_info lethal_strikeInfo = {"Lethal Strike", 4, 25, 25, "Physical"};
    lethal_strikeInfo.desc = "50% Chance to Crit";
    moveFunctions[4] = lethal_strike;
    FULL_MOVE_POOL.push_back(lethal_strikeInfo);

    Move_info weapon_masterInfo = {"Weapon Master", 5, 0, 0, "Passive"};
    weapon_masterInfo.desc = "Increases the Power of Physical Moves by 30%";
    moveFunctions[5] = weapon_master;
    FULL_MOVE_POOL.push_back(weapon_masterInfo);

    Move_info mastery_of_magicInfo = {"Mastery of Magic", 6, 0, 0, "Passive"};
    mastery_of_magicInfo.desc = "Increases the Power of Magical Moves by 30%";
    moveFunctions[6] = mastery_of_magic;
    FULL_MOVE_POOL.push_back(mastery_of_magicInfo);

    Move_info efficient_tacticsInfo = {"Efficient Tactics", 7, 0, 0, "Passive"};
    efficient_tacticsInfo.desc = "Reduces The Cost of all moves by 30%";
    moveFunctions[7] = efficient_tactics;
    FULL_MOVE_POOL.push_back(efficient_tacticsInfo);

    Move_info life_siphonInfo = {"Life Siphon", 8, 30, 40, "Magical"};
    life_siphonInfo.desc = "Heals 50% of Damage Dealt";
    moveFunctions[8] = life_siphon;
    FULL_MOVE_POOL.push_back(life_siphonInfo);

    Move_info sluggish_strikeInfo = {"Sluggish Strike", 9, 50, 0, "Physical"};
    sluggish_strikeInfo.desc = "50% Chance to Miss";
    moveFunctions[9] = sluggish_strike;
    FULL_MOVE_POOL.push_back(sluggish_strikeInfo);

    Move_info shield_blastInfo = {"Shield Blast", 10, 30, 30, "Magical"};
    shield_blastInfo.desc = "Scales off DEF";
    moveFunctions[10] = shield_blast;
    FULL_MOVE_POOL.push_back(shield_blastInfo);

    Move_info iron_wallInfo = {"Iron Wall", 11, 20, 30, "Buff"};
    iron_wallInfo.desc = "Increases DEF for 3 turns";
    moveFunctions[11] = iron_wall;
    FULL_MOVE_POOL.push_back(iron_wallInfo);

    Move_info growthInfo = {"Growth", 12, 10, 30, "Buff"};
    growthInfo.desc = "Increases ATK and DEF for 3 turns";
    moveFunctions[12] = growth;
    FULL_MOVE_POOL.push_back(growthInfo);

    Move_info strategistInfo = {"Strategist", 13, 0, 0, "Passive"};
    strategistInfo.desc = "Increases the Power of Buff Moves by 20%";
    moveFunctions[13] = strategist;
    FULL_MOVE_POOL.push_back(strategistInfo);

    Move_info nova_blastInfo = {"Nova Blast", 14, 0, 50, "Magical"};
    nova_blastInfo.desc = "Requires One Turn to Charge";
    moveFunctions[14] = nova_blast;
    FULL_MOVE_POOL.push_back(nova_blastInfo);

    Move_info pain_shareInfo = {"Pain Share", 15, 10, 30, "Magical"};
    pain_shareInfo.desc = "Increase Power by 10% for every 20% Missing HP";
    moveFunctions[15] = pain_share;
    FULL_MOVE_POOL.push_back(pain_shareInfo);

    Move_info poison_strikeInfo = {"Poison Strike", 16, 15, 20, "Physical"};
    poison_strikeInfo.desc = "Poisons Enemy for 2 turns";
    moveFunctions[16] = poison_strike;
    FULL_MOVE_POOL.push_back(poison_strikeInfo);
    

}

bool moves::Maincharacter_ExecuteMove(int index, MainCharacter &m, Enemy &e){
    if (index > m.moveSet.size() || index < 1){
        cout << "Error: Invalid move index!" << endl;
        cout << "Please try again!" << endl;
        return false; //Invalid move
    }
    for (auto& moveID : m.moveSet){
      if (FULL_MOVE_POOL[moveID].type == "Passive"){
        moveFunctions[moveID](m,e,FULL_MOVE_POOL[moveID], dialogs); //Execute the passive move functions
      }
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
    if (move.cost == 0){
        //don't display cost if it's 0
    }
    else if (move.type == "Physical"){
        dialog += (" <format><|red|>HP<end> <format><|red|><|bold|>-" + to_string(move.cost) + "<end>");
    }
    else if (move.type == "Magical" || move.type == "Buff"){
        dialog += (move.cost > 0)? (" <format><|blue|>MP<end> <format><|blue|><|bold|>-" + to_string(move.cost) + "<end>") : "" ;
    }

    dialogs.push_back(dialog);
    moveFunctions[move.ID](m,e,move, dialogs); //Execute the move function
    restore_passive(m); //Restore effects of passive moves after executing the move
    return true;
  
}

void moves::addMove(MainCharacter& character, int ID, vector<string> &dialogs){
    //Note that the player would see {1,2,3,4} instead of {0,1,2,3}
    int index;
    bool validInput = false;
    while (!validInput) {
        cout << "Select a move to change (1-4) or input 0 to discard the move: ";
        cin >> index;
        if (cin.fail()) {
            cin.clear(); // clear the error state
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore the rest of the line
            cout << "Invalid input. Please enter a number." << endl;
        } else  if (index > 4){
            cout << "Invalid input. Please enter a number between (1-4)." << endl;
        }
        else {
            validInput = true;
        }
    }
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (index != 0){
        string old_name = FULL_MOVE_POOL[character.moveSet[index-1]].name;
        if (character.moveSet.size() < index){
            character.moveSet.push_back(ID);
        }
        else {
            cout << "Replaced" << old_name << " with " << FULL_MOVE_POOL[ID].name << endl;
            character.moveSet[index-1] = ID;
        }       
        dialogs.push_back("Skill <format><|purple|>[" + FULL_MOVE_POOL[ID].name + "]<end> has been added.");
    }
    else {
        cout << "Move discarded!" << endl;
        dialogs.push_back("Skill <format><|purple|>[" + FULL_MOVE_POOL[ID].name + "]<end> Discarded.");
    }
}


string moves::getMoveName(int ID){
    return FULL_MOVE_POOL[ID].name;
}

bool moves::check_cost(MainCharacter &m, Move_info move){
    if (move.type == "Physical" && m.hp <= move.cost){
        return false;
    }
    else{
        if (move.type == "Magical" || move.type == "Buff"){
            if (m.mp < move.cost){
                return false;
            }
        }
    }
    return true; // enough HP/MP
}

void moves::restore_passive(MainCharacter &m){
  for (int i = 0; i < m.boosted_moves.size(); i++){
    FULL_MOVE_POOL[m.boosted_moves[i].ID] = m.boosted_moves[i]; //Restore the info of the moves
  }
  m.boosted_moves.clear(); //Clear the boosted moves
}


void moves::deleteMove(MainCharacter& character, int ID){
    for (int i = 0; i < character.moveSet.size(); i++){
        if (character.moveSet[i] == ID){
            character.moveSet.erase(character.moveSet.begin() + i);
            cout << "Move deleted!" << endl;
            return;
        }
    }
    cout << "Move not found!" << endl;
}

void moves::calculate_boost(MainCharacter &m){
    // calculate the boosts
    // minus 1 round after the boost at the end of every half round round
    m.atk_boost_sum = 0;
    for (auto &pair: m.atk_boost) {
        m.atk_boost_sum += pair.first;
        pair.second--;
    }
    m.atk_boost_sum = m.atk_boost_sum;
    m.def_boost_sum = 0;
    for (auto &pair: m.def_boost) {
        m.def_boost_sum += pair.first;
        pair.second--;
    }
    m.def_boost_sum = m.def_boost_sum;

    // remove all pair that round remains <= 0 with lambda function
    m.atk_boost.erase(remove_if(m.atk_boost.begin(), m.atk_boost.end(), [](pair<int, int> pair){return pair.second <= 0;}), m.atk_boost.end());
    m.def_boost.erase(remove_if(m.def_boost.begin(), m.def_boost.end(), [](pair<int, int> pair){return pair.second <= 0;}), m.def_boost.end());
}

void moves::hp_change(MainCharacter &m){
    for (auto &pair: m.hp_boost){
        int value = pair.first;
        int max_regeneration = m.max_hp - m.hp;
        value = min(max_regeneration, pair.first);
        m.hp += value;
        pair.second--;
        string int_value = to_string(value);
        string rounds = to_string(pair.second);
        string dialog = "<format><|blue|>" + m.name + "<end> <format><|red|>HP<end> <format>";
        dialog += ((value < 0)? ("<|red|>" + int_value): ("<|green|>+" + int_value));
        dialog += "<end>";
        dialog += " (remain <format><|yellow|><|bold|>" + rounds + "<end> rounds.)";
        dialogs.push_back(dialog);      
    }
    m.hp_boost.erase(remove_if(m.hp_boost.begin(), m.hp_boost.end(), [](pair<int, int> pair){return pair.second <= 0;}), m.hp_boost.end());
}

void moves::display_moves(MainCharacter &m){
  vector<Move_info> moves;
  for (int i = 0; i < m.moveSet.size(); i++){
      moves.push_back(FULL_MOVE_POOL[m.moveSet[i]]);
  }
    //cout << "+-------------------------------------------------------------------------+" << endl;
    cout << "|    Skills                    | Cost   | Power  | Type                   |" << endl;
    cout << "|------------------------------|--------|--------|------------------------|" << endl;
    for (int i = 0; i < moves.size(); i++){
        cout << "| " << i+1 << ". ";
        cout << left << setw(25) << moves[i].name;
        cout << " | " << left << setw(3) << moves[i].cost << ((moves[i].type == "Physical")? " HP" : " MP");
        cout << " | " << left << setw(6) << moves[i].power; 
        cout << " | " << left << setw(23) << moves[i].type;
        cout << "|" << endl;
    }
    cout << "+-------------------------------------------------------------------------+" << endl;
    
}


void moves::resetBuffs(MainCharacter &m){
    m.atk_boost.clear();
    m.def_boost.clear();
    m.hp_boost.clear();
    m.atk_boost_sum = 0;
    m.def_boost_sum = 0;
}


void moves::move_description(int ID){
    cout << FULL_MOVE_POOL[ID].name << ": " << FULL_MOVE_POOL[ID].desc << endl;
}
