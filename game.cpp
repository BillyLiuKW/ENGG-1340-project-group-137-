//Handles Game Logic
#include <iostream>
#include "character.h"
using namespace std;

class GAME{
    public:
        void StartGame(MainCharacter m, Enemy e);
        // To display the gameplay screen. 
        void Display();
        // To check whether the maincharacter or the enemy die. It reads both 
        bool checkhp(MainCharacter m, Enemy e);
        // To check whether the user choose skill out of range (e.g. there are totally 4 skills but the user entered to use the 5th skill)
        bool illegalmove(int chosen);
};

void GAME::StartGame(MainCharacter m, Enemy e) {
    Display();
    while (true) {
        // Get user input for chosen skill
        int chosenSkill;
        cout << "Please choose the skill you want to apply : ";
        cin >> chosenSkill;
        // Check if the chosen skill is illegal
        if (! illegalmove(chosenSkill)) {
            // Perform the skill action
            // ...
            
            // Update the health points of the main character and the enemy
            // ...
            
            // Check if any character has died
            if (! checkhp(m, e)) {
                // Handle game over or retry option
                break;
            }
        } else {
            cout << "Illegal move! Please choose a valid skill." << endl;
        }
    }
}


void GAME::Display(const string& Maincharacter_name, int Maincharacter_hp, int Maincharacter_atk, const string& enemy_name, int enemy_hp, int enemy_atk) {
    // This is the line for separating two fields
    string sepline;
    for (int i = 0; i < 49; i++) {
        sepline += "*";
    }
    //This is the line for constructing the margin.
    string margin;
    for (int i = 0; i < 49; i++) {
        margin += "-";
    }
    // leaving some spaces to show the screen.
    cout << string(5, '\n');

    // Starting margin
    cout << "+" << margin << "+" << endl;
    cout << "|" << setw(30) << "BATTLEFIELD" << setw(20) << "|"<< endl;
    cout << "+" << margin << "+" << endl;

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
        cout << "[";
        for (int i = 0; i < bar_size; i++) {
            cout << ".";
        }
        cout << "] " << setw(4) << right << enemy_hp << " |" << endl;
    }
    
    else {
        cout << "[";
        for (int i = 0; i < line_of_hp; i++) {
            cout << "#";
        }
        for (int i = 0; i < emptyspots; i++) {
            cout << ".";
        }
        cout << "] " << setw(4) << right << enemy_hp << " |" << endl;
    }
    
    //Separating two fields
    cout << "|" << setw(50) << "|" << endl;
    cout << "|" << sepline << "|" << endl;
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
        cout << "[";
        for (int i = 0; i < bar_size; i++) {
            cout << ".";
        }
        cout << "] " << setw(4) << right << Maincharacter_hp << " |" << endl;
    }
    
    else {
        cout << "[";
        for (int i = 0; i < line_of_hp; i++) {
            cout << "#";
        }
        for (int i = 0; i < emptyspots; i++) {
            cout << ".";
        }
        cout << "] " << setw(4) << right << Maincharacter_hp << " |" << endl;
    }
    
    
    
    // Ending margin
    cout << "|" << setw(50) << "|" << endl;
    cout << "+" << margin << "+" << endl;

    // Additional display elements and game status can be added here
    // For example, you can print a visual representation of the battle or any other relevant information
}

bool GAME::checkhp(MainCharacter m, Enemy e) {
    if (m.hp <= 0) {
        return false;
        // may insert another function to store game status and provide options for retry.
    }

    else if (e.hp <= 0) {
        return true;
        //may insert another function to store game status and proceed to next level.
    }
}

bool GAME::illegalmove(int chosen) {
    // Insert code to check if the chosen skill is out of range
}