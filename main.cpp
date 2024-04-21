#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <unistd.h>
#include "game.hpp"
#include "character.hpp"
#include "moves.hpp"
using namespace std;

// main menu for the game.
void menu() {
      vector<string> test = { 
        "                                                                           ",
        "           )(                                                 )(           ",
        " ()///////(**)======================> <======================(**)///////() ",
        "           )(    ____                                         )(           ",
        "            #   |  _ \\ _   _ _ __   __ _  ___  ___  _ __      #          ",
        "            #   | | | | | | | '_ \\ / _` |/ _ \\/ _ \\| '_ \\     #       ",
        "            #   | |_| | |_| | | | | (_| |  __/ (_) | | | |    #           ",
        "            #   |____/ \\__,_|_| |_|\\__, |\\___|\\___/|_| |_|    #       ",
        "           )(                      |___/                      )(           ",
        " ()///////(**)======================> <======================(**)///////() ",
        "           )(                                                 )(           ",
        "            #   1. Start A New Game                           #            ",
        "            #   2. Continue                                   #            ",
        "            #   3. Enemy Handbook                             #            ",
        "            #   4. Game Instruction                           #            ",
        "            #   5. Exit                                       #            ",
        "            #                                                 #            ",
        "           )(=================================================)(           ",  
    };
    // print the menu
    for (auto &line: test){
        cout << line << endl;
    }
}
// To handle the command input by player.
void select_option(int option, GAME game) {
    switch(option) {
        case 1:
        { // game_status.txt exist only if the player has stored game status before.
            // previous game status will be removed when player choose to start a new game.
            ifstream fin("game_status.txt");
            if (fin.good()) {
              remove("game_status.txt");
            }
            
            MainCharacter m;
            Enemy e(game.current_level);
            moves skills;
            skills.iniializeMoves();
            skills.addMove(m, 0);
            cout << "Proceeding to level 1...." << endl;
            sleep(1);
            game.StartGame(m,e);
            break;
        }

        case 2:
        {
            MainCharacter m;
            
            ifstream fin("game_status.txt");
            // check whether is game_status.txt existing.
            if (fin.fail()) {
                cout << "You haven't stored any game status!Start a new game instead." << endl;
            }
            else {
                // Assigning stored values to m one by one.
                fin >> m.hp >> m.max_hp >> m.atk >> m.def;
                // To input the size of moveSet stored.
                int size;
                fin >> size;
                m.moveSet.resize(size);
                for (int j; j < size; j++) {
                    fin >> m.moveSet[j];
                }
                // to read the level stored.
                fin >> game.current_level;
                //close the file after reading all data.
                game.display.dialogs.insert(game.display.dialogs.begin(), "Game status successfully loaded"); // add the output message to dialog
                fin.close();
                cout << "Proceeding to level " << game.current_level << endl;
            }
            // Both case will do the below code
            Enemy e(game.current_level);
            sleep(1);
            game.StartGame(m,e);
            break;
        }

        default:
        {
            break;
        }
        
      }
}

int main() {
    GAME game;
    int option;
    while (true) {
        menu();
        cout << "Select An Option: ";
        cin >> option;
        select_option(option,game);
        // if player choose option 5, he or she will escape from select_option().
        if (option == 5) {
            char y_n;
            cout << "Do you want to exit the game? [y/n]" << endl;
            cin >> y_n;
            if (y_n == 'y') {
                cout << "Thank you and goodbye!" << endl;
                exit(0);
            }
            
            else if (y_n == 'n'){
                continue;;
            }
            else {
                cout << "Error: invalid answer!" << endl;
                continue;
            }
        }
        return 0;
    }
}
