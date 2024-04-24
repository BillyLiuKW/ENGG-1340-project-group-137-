//Handles Game Logic
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cctype>
#include <algorithm>
#include <cstdlib>
#include <unistd.h>
#include "character.hpp"
#include "game.hpp"
#include "screen.hpp"
#include "moves.hpp"
#include "enemymoves.hpp"
using namespace std;

void pass() {
    int a = 0;
}


// update 1.0.0 new display is avaliable
void GAME::StartGame(MainCharacter& m, Enemy& e) { 
    moves skills(display.dialogs);
    skills.iniializeMoves();
    EnemyMoves enemy_skills(m, e, display.dialogs); // initiallize
    int round = 1;
    display.dialogs.push_back(" "); // line break
    display.dialogs.push_back("<format><|bold|><|red|>Level " +  to_string(current_level) + "<end>"); // show current level
    display.dialogs.push_back("<format><|bold|>BATTLE START!<end>");
    while (round < 11) {
        // show thw screen once before any action (don't remove this) should display 3 time each round
        display.dialogs.push_back(" "); // line break for the next round.
        display.dialogs.push_back("<format><|cyan|>Round " + to_string(round) + "<end>"); // show the current round.
        display.clear_screen();
        display.insert_battelfield(m, e); // input main character and enemy information to the screen
        display.print_screen();

        //
        /*//test
        cout << "crit chance: " << e.critical_chance << endl;
        cout << "boost: " <<e.crit_chance_boost_sum << endl;
        cout << "crit dmg: " << e.critical_damage << endl;
        cout << "coost: " <<e.crit_damage_boost_sum << endl;
        // end*/
        // Get user input for chosen skill
        //reward(m,2);
        //break;
        skills.display_moves(m);
        int chosen_Skill;
        
        do{
            while (true){ // to make sure the input is an integer
                cout << "Please choose the skill you want to apply : ";
                cin >> chosen_Skill;
                if (cin.fail()) {  // if use input a non integer
                    cout << "Please input an integer within the skill set!" << endl;
                    cin.clear();        
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }
                break;
            }
        } while (!skills.Maincharacter_ExecuteMove(chosen_Skill, m, e));

        // calculate all the buff/ debuff for the next half round
        // count down all buff/ debuff rounds by 1, remove
        skills.calculate_boost(m);
        enemy_skills.calculate_boost();
        // execute continue damage/ regeneration for main character
        skills.hp_change(m);
        // Player move End

        // I don't like negative hp
        m.hp = max(0, m.hp);
        e.hp = max(0, e.hp);
        
        // show battelfield before enemy's move
        display.clear_screen();
        display.insert_battelfield(m, e);
        display.print_screen();
        
        // Check if any character has died
        if (! survive(m.hp)) {
            //player dead and need functions to provide retry function 
            Gameretry();
            break;
        }
        if (! survive(e.hp)) {
            // return win function
            skills.resetBuffs(m);
            Victory(m, e, display);
            break;
        }
        // give some time for the player to read the screen
        cout << "Waiting for enemy's action ..." << endl;
        sleep(3);

        // enemy's action
        display.dialogs.push_back(" "); // add a line to saperate use move and enemy move
        enemy_skills.Enemy_ExecuteMove(); // use skill or normal attack

        // calculate enemy boost before next player move.
        skills.calculate_boost(m);
        enemy_skills.calculate_boost();
        enemy_skills.hp_change();
        // enemy's action End

        // show battelfield
        display.clear_screen();
        display.insert_battelfield(m, e);
        display.print_screen();
        
        //  Check if any character has died
        if (! survive(m.hp)) {
            //player dead and need functions to provide retry function 
            Gameretry();
            break;
        }
        //check whether enemy is dead
        if (! survive(e.hp)) {
            // return win function
            skills.resetBuffs(m); //Reset the buffs after battle
            Victory(m, e, display);
            break;
        }

        round++;
        sleep(3);
    }
    // if the player cannot defeat the enemy in 10 rounds, the game will end.
    cout << "You cannot defeat " << e.name << " in 10 rounds!" << endl;
    Gameretry();
    sleep(2);

}


void GAME::Display(const string& Maincharacter_name, int Maincharacter_hp, int Maincharacter_atk, const string& enemy_name, int enemy_hp, int enemy_atk) {
    // leaving some spaces to show the screen.
    cout << string(5, '\n');

    // Starting margin
    cout << "+" << string(49,'-') << "+" << endl;
    cout << "|" << setw(30) << "BATTLEFIELD" << setw(20) << "|"<< endl;
    cout << "+" << string(49,'-') << "+" << endl;

    // Enemy information
    cout << "| Enemy:" << setw(43) << "|" << endl;
    cout << "|   Name: " << setw(39) << left << enemy_name << " |" << endl;
    cout << "|   ATK:  " << setw(39) << left << enemy_atk << " |" << endl;
    cout << "|   Health: ";

    // Calculate the occupation of bar and fill empty spot
    int bar_size = 30;
    int line_of_hp = (enemy_hp * bar_size) / 150;
    int emptyspots = bar_size - line_of_hp;

    // Display enemy health as a bar
    if (enemy_hp < 0) {
        cout << "[" << string(bar_size,'.') << "] " << setw(4) << right << enemy_hp << " |" << endl;
    }
    
    else {
        cout << "[" << string(line_of_hp,'#') << string(emptyspots,'.') << "] " << setw(4) << right << enemy_hp << " |" << endl;
    }
    
    //Separating two fields
    cout << "|" << setw(50) << "|" << endl;
    cout << "|" << string(49,'*') << "|" << endl;
    cout << "|" << setw(50) << "|" << endl;

    // Main character information
    cout << "| Main Character:" << setw(34) << "|" << endl;
    cout << "|   Name: " << setw(39) << left << Maincharacter_name << " |" << endl;
    cout << "|   ATK:  " << setw(39) << left << Maincharacter_atk << " |" << endl;
    cout << "|   Health: ";

    // Calculate the occupation of bar and fill empty spot
    line_of_hp = (Maincharacter_hp * bar_size) / 150;
    emptyspots = bar_size - line_of_hp;

    // Display main character health as a bar
    if (Maincharacter_hp < 0) {
        cout << "[" << string(bar_size,'.') << "] " << setw(4) << right << Maincharacter_hp << " |" << endl;
    }
    
    else {
        cout << "[" << string(line_of_hp,'#') << string(emptyspots,'.') << "] " << setw(4) << right << Maincharacter_hp << " |" << endl;
    }
    
    // Ending margin
    cout << "|" << setw(50) << "|" << endl;
    cout << "+" << string(49,'-') << "+" << endl;
}

bool GAME::survive(int hp) {
    if (hp <= 0) {
        return false;
    }

    else {
        return true; 
    }
}

void GAME::Victory(MainCharacter &m, Enemy &e, Screen &display) {
    display.dialogs.push_back("<format><|yellow|>Congratulations!<end> You have defeated Enemy <format><|yellow|><|bold|>[" + e.name + "]<end>!");
    display.clear_screen();
    display.insert_battelfield(m, e); // input main character and enemy information to the screen
    display.print_screen();
    m.hp = m.max_hp;
    m.mp = m.max_mp;
    this->current_level++;
    // That means the player has win the game.
    
    if (this->current_level > 10) {
        cout << "Congratulations! You have defeated all enemies in this game! You are a true hero!!" << endl;
        cout << "See you next time!" << endl;
        // To clear all game status 
        ifstream fin("game_status.txt");
        if (fin.good()) {
            remove("game_status.txt");
        }
        //End the game.
        exit(0);
    }
    reward(m, e, this->current_level);// player can receive reward after every boss and checkpt
    // checkpoint reward are tackle in same function
    if (this->current_level == 3 || this->current_level == 5 || this->current_level == 7) {
        //player can get reward from these level and they are not required to beat any enemy in these levels.
        //these levels are checkpoints as well.
        this->current_level++;
        char y_n;
        cout << "Do you want to store your game status? [y/n] " << endl;
        cin >> y_n;
        while (y_n != 'y' && y_n != 'n') {
            cout << "Invalid input! Please enter again! " << endl;
            cout << "Do you want to store your game status? [y/n] " << endl;
            cin >> y_n;
        }
        if (y_n == 'y') {
            ofstream fout("game_status.txt");
            if (fout.is_open()) {
                fout << m.name << " " << m.hp << " " << m.max_hp << " " << m.atk << " " << m.def << " " << m.mp << " ";
                fout << m.moveSet.size() << " ";
                for (int k = 0; k < m.moveSet.size(); k++) {
                    fout << m.moveSet[k] << " ";
                }
                fout << this->current_level;
                fout.close();
                cout << "Game status saved successfully! " << endl;
                sleep(2);
            }

            else{
                cout << "Error! Not able to save your game status. " << endl;
            }
        }

        else {
            cout << "remarkably brave! " << endl;
            sleep(2);
        }
    }
    //player will proceed to next level.
    cout << "Proceeding to level " << this->current_level << " ...." << endl;
    sleep(1);
    Enemy new_e(this->current_level); 
    StartGame(m, new_e);

}

void GAME::Gameretry(){
    char option;
    while (true) {
        cout << "Game over! You are defeated!" << endl;
        cout << "Do you want to retry? [y/n]" << endl;
        cin >> option;
        if (option == 'y') {
            ifstream fin("game_status.txt");
            if (fin.is_open()) {
                MainCharacter m;
                // Assigning stored values to m one by one.
                fin >> m.name >> m.hp >> m.max_hp >> m.atk >> m.def >> m.mp;
                // To input the size of moveSet stored.
                int size;
                fin >> size;
                m.moveSet.resize(size);
                for (int i = 0; i < size; i++) {
                    fin >> m.moveSet[i];
                }
                // to read the level stored.
                fin >> this->current_level;
                //close the file after reading all data.
                this->display.dialogs.insert(this->display.dialogs.begin(), "Game status successfully loaded"); // add the output message to dialog
                fin.close();
                cout << "Proceeding to level " << this->current_level << endl;
                Enemy e(this->current_level);
                sleep(1);
                StartGame(m,e);
                return;
            }
            //player should start from level 1 if they did not store any status.
            else {
                MainCharacter m;
                this->current_level = 1;
                Enemy e(this->current_level);
                cout << "Proceeding to level 1...." << endl;
                sleep(2);
                StartGame(m,e);
                return;
            }
        
        }
        else if (option == 'n'){
            cout << "Thank you and Goodbye!" << endl;
            exit(0);
        }

        else {
            cout << "Error: invalid option!" << endl;
            cout << "Please try again!" << endl;
        }   
    }
}

bool isInteger(string x){
    for (char c : x) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

void GAME::reward(MainCharacter &m, Enemy &e, int level){ // normal reward where player can receive reward every level
    string type;
    if (level != 3 && level != 5 && level != 7){
        cout << "Choose Reward Type : 1. Stat   2. Skills" << endl;
        cout << "Please Enter 1/2 : ";
        cin >> type ;
        while (stoi(type) != 1 && stoi(type) != 2){
            cout << "Invalid Input. Please enter again : " ;
            cin >> type; 
        }
    }
    else{
        cout << "Welcome to checkpoint" << endl;
        type = "3";
    }
    string lucky_draw_no;
    cout << "Enter a number for lucky draw : ";
    cin >> lucky_draw_no;
    while (!isInteger(lucky_draw_no)){
        cout << "Invalid Input. Please enter again : " ;
        cin >> lucky_draw_no; }
    int health, attack, defence, magic;
   switch(level){ // basic value of random reward
       case 2:{
           health = 20, attack = 5, defence = 5, magic = 20;
           break;
       }
       case 3:{
           health = 40, attack = 15, defence = 10, magic = 40;
           break;
       }
       case 4:{
    
           health = 50, attack = 20, defence = 10, magic = 50;
           break;
       }
       case 5:{
           health = 60, attack = 25, defence = 15, magic = 50;
           break;
       }
       case 6:{
           health = 80, attack = 30, defence = 15, magic = 60;
           break;
       }
        case 7:{
           health = 80, attack = 40, defence = 25, magic = 70;
           break;
       }
       case 8:{
           health = 90 , attack = 30, defence = 15, magic = 60;
           break;
       }
       case 9:{
           health = 90, attack = 40, defence = 25, magic = 80;
           break;
       }
       case 10:{
           health = 100, attack = 40, defence = 25, magic = 80;
           break;
       }
       default:{
           break;
       }
   }

    switch (stoi(type)){
        case (1):{
            stats(m, stoi(lucky_draw_no), health, attack, defence,magic);
            break;}
        case (2):{
            skill(m, e, stoi(lucky_draw_no));
            break;}
        case 3:{
            stats(m, stoi(lucky_draw_no), health, attack, defence,magic);
            skill(m, e, stoi(lucky_draw_no));
            break;
        }
        default:
            return;
    }
}

void round_to_five(int &x){
    x = (x/5)*5;
}

void GAME::stats(MainCharacter &m, int lucky_draw_no, int health, int attack, int defence, int magic){
    srand(lucky_draw_no);
    int hp_increase = rand() % health + health;
    int atk_increase = rand() % attack + attack;
    int def_increase = rand() % defence + defence;
    int mp_increase = rand() % magic + magic;
    round_to_five(hp_increase);
    round_to_five(atk_increase);
    round_to_five(def_increase);
    round_to_five(mp_increase);
    m.hp += hp_increase;
    m.max_hp += hp_increase;
    m.atk += atk_increase;
    m.def += def_increase;
    m.max_mp += mp_increase;
    m.mp += mp_increase;
    cout << "hp+ " << hp_increase << "    ";
    cout << "atk+ " << atk_increase << "    ";
    cout << "def+ " << def_increase <<  "    ";
    cout << "mp+ " << mp_increase << endl;
    sleep(4);
}

void reward_screen(MainCharacter m){
    for (int i = 0 ; i < m.moveSet.size() ; i++){
        cout << i+1 << ". ";
        cout << moves::FULL_MOVE_POOL[m.moveSet[i]].name; 
        cout << "   ";}
    cout << endl;}

void GAME::skill(MainCharacter &m, Enemy &e, int lucky_draw_no){
    //Player will see {1,2,3,4} instead of {0,1,2,3}  in the display moveSet
    srand(lucky_draw_no);
    cout << "Your current moves : " << endl;
    reward_screen(m);
    int random = rand() % moves::FULL_MOVE_POOL.size();
    while (find(m.moveSet.begin(), m.moveSet.end(), moves::FULL_MOVE_POOL[random].ID) != m.moveSet.end()) {
        // Generate a new random number
        random = rand() % moves::FULL_MOVE_POOL.size(); // Avoid duplicate moves
    }
    //cout << "New Skill : " << moves::FULL_MOVE_POOL[random].name << endl;

    display.dialogs.push_back("Skill <format><|purple|>[" + moves::FULL_MOVE_POOL[random].name + "]<end> has been added.");
    display.clear_screen();
    display.insert_battelfield(m, e); // input main character and enemy information to the screen
    display.print_screen();
    //moves::addMove(m, moves::FULL_MOVE_POOL[random].ID);
    //cout << "After : " << endl;
    //reward_screen(m);
    system("read -p '\033[1mPress Enter to continue...\033[0m' var"); // pause the game until the user press enter
    


}
