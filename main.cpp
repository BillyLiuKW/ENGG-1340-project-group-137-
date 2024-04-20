#include <iostream>
#include <vector>
#include <fstream>
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
          Enemy e(1);
          game.StartGame(m,e);
        }

        case 2:
        {
          ifstream fin("game_status.txt");
          // check whether is game_status.txt existing.
          if (fin.fail()) {
            cout << "You haven't stored any game status!Start a new game instead." << endl;
            main();
          }
          MainCharacter m;
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
          int slevel;
          fin >> slevel;
          //close the file after reading all data.
          cout << "Game status successfully loaded" << endl;
          fin.close();
          sleep.(1); // time delay prevent the screen flush the output message
          Enemy e(slevel);
          game.StartGame(m,e);

        }


      }
}

int main() {
  menu();
  GAME game;
  int option;
  cout << "Select An Option: ";
  cin >> option;
  select_option(option,game);
  return 0;
}
