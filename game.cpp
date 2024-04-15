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


void GAME::Display() {
    // Insert code to display the gameplay screen
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