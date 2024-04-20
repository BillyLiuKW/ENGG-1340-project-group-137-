//Handles Game Logic
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include "character.hpp"
#include "game.hpp"
#include "screen.hpp"
using namespace std;

void pass() {
    int a = 0;
}


// update 1.0.0 new display is avaliable
void GAME::StartGame(MainCharacter& m, Enemy& e) { 
    //Display(m.name, m.hp,  m.atk, e.name,  e.hp, e.atk);
    display.clear_screen();
    display.insert_battelfield(m, e); // new display
    display.print_screen();
    int round = 1;
    while (round < 11) {
        cout << "This is round " << round << endl;
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
        // below only execute when valid skill is chosen
        // Perform the skill action
        // ...
        
        // Update the health points of the main character and the enemy
        // ...
        
        // Check if any character has died

        // enemy's action
        if (! survive(m.hp)) {
            //player dead and need functions to provide retry function 
            pass();
        }

        else if (! survive(e.hp)) {
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
        reward();
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

    Enemy e(this->current_level);
    StartGame(m,e);

}

void GAME::reward() {
    pass();
}
