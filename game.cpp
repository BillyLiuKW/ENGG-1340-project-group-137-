//Handles Game Logic
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cctype>
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
    moves skills;
    skills.iniializeMoves();
    EnemyMoves enemy_skills(m, e, display.dialogs);
    //Display(m.name, m.hp,  m.atk, e.name,  e.hp, e.atk);
    int round = 1;
    display.dialogs.push_back("<format><|bold|><|red|>Level " +  to_string(current_level) + "<end>");
    display.dialogs.push_back("<format><|bold|>BATTLE START!<end>");
    while (round < 11) {
        display.clear_screen();
        display.dialogs.push_back(" ");
        display.dialogs.push_back("<format><|cyan|>Round " + to_string(round) + "<end>");
        display.insert_battelfield(m, e); // new display
        display.print_screen();
        
        // Get user input for chosen skill
        int chosen_Skill;
        cout << "Please choose the skill you want to apply : ";
        cin >> chosen_Skill;
        // Check if the chosen skill is illegal
        if (invalid_skill(chosen_Skill)) {
            cout << "Invalid choice! Please choose a valid skill." << endl;
            //continue;
            break; //temporarily
        }
        if (!skills.Maincharacter_ExecuteMove(chosen_Skill, m, e)){
            cout << "Not enough HP/MP to cast the move!" << endl;
            //continue;
            break; //temporarily
        }

        // below only execute when valid skill is chosen
        // Perform the skill action
        // ...
        
        // Update the health points of the main character and the enemy
        // ...
        
        // Check if any character has died

        // enemy's action
        enemy_skills.Enemy_ExecuteMove();
        if (! survive(m.hp)) {
            //player dead and need functions to provide retry function 
            Gameretry();
        }

        if (! survive(e.hp)) {
            // return win function
            Victory(m,e);
        }

            
        
        round++;
    }
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

bool GAME::invalid_skill(int chosen) {
    // Insert code to check if the chosen skill is out of range
    pass();
    return 0;
}

void GAME::Victory(MainCharacter &m, Enemy &e) {
    cout << "Congratulations! The " << e.name << " is defeated!" << endl;
    this->current_level++;
    if (this->current_level == 3 || this->current_level == 5 || this->current_level == 7) {
        //player can get reward from these level and they are not required to beat any enemy in these levels.
        reward(m);
        //these levels are checkpoints as well.
        this->current_level++;
        char y_n;
        cout << "Do you want to store your game status? [y/n] " << endl;
        if (y_n == 'y') {
            ofstream fout("game_status.txt");
            if (fout.is_open()) {
                fout << m.hp << " " << m.max_hp << " " << m.atk << " " << m.def;
                fout << m.moveSet.size();
                for (int k = 0; k < m.moveSet.size(); k++) {
                    fout << m.moveSet[k] << " ";
                }
                fout << this->current_level;
                fout.close();
                cout << "Game status saved successfully! " << endl;
            }

            else{
                cout << "Error! Not able to save your game status. " << endl;
            }
        }

        else {
            cout << "remarkably brave! " << endl;
        }
    }
    // That means the player has win the game.
    else if (this->current_level > 10) {
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
    //player will proceed to next level.
    cout << "Proceeding to level " << this->current_level << " ...." << endl;

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
                fin >> m.hp >> m.max_hp >> m.atk >> m.def;
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
                Enemy e(this->current_level);
                moves skills;
                skills.iniializeMoves();
                skills.addMove(m, 0);
                skills.addMove(m, 1);
                cout << "Proceeding to level 1...." << endl;
                sleep(1);
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

void GAME::reward(MainCharacter &m){
    cout << "Choose Reward Type : 1. Stat   2. Skills" << endl;
    string type;
    cout << "Please Enter 1/2 : ";
    cin >> type ;
    int y = 1;
    while (y){
            if ( !isInteger(type) || stoi(type) > 2 )
                {cout << "Invalid Input. Please enter again : " ;
                cin >> type; }
            else
                y--;
        }
    string lucky_draw_no;
    cout << "Enter a number for lucky draw : ";
    cin >> lucky_draw_no;
    while (!isInteger(lucky_draw_no)){
        cout << "Invalid Input. Please enter again : " ;
        cin >> lucky_draw_no; }
    switch (stoi(type)){
        case (1):
            ability(m,stoi(lucky_draw_no));
            break;
        case (2):
            skill(m,stoi(lucky_draw_no));
            break;
        default:
            return;
    }
}

void GAME::ability(MainCharacter &m, int lucky_draw_no){ //basic value
    srand(lucky_draw_no);
    int health, attack, defence, magic;
    bool x = 1;
    health = rand() % 51 + 50;
    attack = rand() % 31 + 15;
    defence = rand() % 16 + 15;
    magic = rand() % 31 + 20;
    while (x){
        if (health % 5 != 0)
            health--;
        if (attack % 5 != 0)
            attack--;
        if (defence % 5 != 0)
            defence--;
    }
    cout << "hp +" << health << endl;
    cout << "atk +" << attack << endl;
    cout << "def +" << defence << endl;
    cout << "mp +" << magic << endl;
    m.hp += health;
    m.atk += attack;
    m.def += defence;
    m.mp += magic;
}

struct FULL_MOVE_POOL{
    string name;
    int ID;
};

void GAME::skill(MainCharacter &m, int lucky_draw_no){
    //Player will see {1,2,3,4} instead of {0,1,2,3}  in the display moveSet
    srand(lucky_draw_no);
    Move_info move; 
    vector <FULL_MOVE_POOL> move_info;
    FULL_MOVE_POOL Slash = {"Slash", 0 };
    move_info.push_back(Slash);
    FULL_MOVE_POOL Fire = {"Fireball", 1 };
    move_info.push_back(Fire);
    FULL_MOVE_POOL Regen = {"Regen", 2};
    move_info.push_back(Regen);
    FULL_MOVE_POOL check;
    int size_of_full_move_pool = 4; //no of skills
    if ( m.moveSet.size() >= 4 ) 
        { for ( int i = 0; i < 4 ; i++ )
            { check = move_info[m.moveSet[i]];
            cout << i + 1 << ". " << check.name ; 
            if ( i < 3 )
                { cout << "    ";}
            else
                {cout << endl;}} 
        string change_move ;
        cout << "Select Move to Change : ";
        cin >> change_move ;
        int y = 1;
        while (y){
            if ( !isInteger(change_move) || stoi(change_move) > 4 )
                {cout << "Invalid Input. Please enter again : " ;
                cin >> change_move; }
            else
                y--;
        }
        int no = stoi(change_move) - 1; 
        y =1;
        int y = 1, z = 0;
        while (y) //check whether the move is in the FULL_MOVE_POOL
        {
            int x = rand() % move_info.size();
            check = move_info[x];
            for ( int i = 0 ; i < 4 ; i++ )
                { if ( m.moveSet[i] == check.ID )
                    z++; }
            if ( z == 0 )
                { m.moveSet[no] = x;
                  y--; }
            z = 0;
        }
        cout << endl;
        cout << "New Skills attain : " << check.name << endl;
        cout << "New move : " << endl;
        for ( int i = 0; i < 4 ; i++ )
            { check = move_info[m.moveSet[i]];
            cout << i + 1 << ". " << check.name ; 
            if ( i < 3 )
                { cout << "    ";}
            else
                {cout << endl;}}         }
        else if ( m.moveSet.size() < 4 ){
            int y = 1, z = 0; // z is for checking duplicate skills while y is a bool for while loop logic
            while (y) //check whether the move is in the FULL_MOVE_POOL
            {   
                int x = rand() % size_of_full_move_pool + 1;
                check = move_info[x];
                for ( int i = 0 ; i < m.moveSet.size() ; i++ )
                    { if ( m.moveSet[i] == check.ID )
                        z++; }
                if ( z == 1 )
                    { m.moveSet.push_back(x);
                    y--; }
                z = 0;
            }
            }
        cout << endl;
        cout << "New Move Add : " << check.name << endl;
        cout << "New Move : " << endl;
        for ( int i = 0; i < m.moveSet.size() ; i++ )
            { check = move_info[m.moveSet[i]];
            cout << i + 1 << ". " << check.name ; 
            if ( i < (m.moveSet.size() - 1) )
                { cout << "    ";}
            else
                {cout << endl;}} 
}


