
# Dungeons

Embark on an adventure to conquer a dungeon filled with carefully designed mechanics!


## Gameplay

You will start the adventure as the Hero. As you progress through the floors of the dungeon, you will gain more power and  your goal is defeat [insert final boss name here].

In each turn, you can choose a move to use.


## Identification

- [@YAM MAN NOK (3036223294)](https://github.com/Flybug234)
- [@LIU KONG WA (3036227446)](https://github.com/BillyLiuKW)


## Features

* Random Events
    * Critical Hits
        ```cpp
        void Critical_hit(int &dmg, int chance = 10){
                srand(time(0));
                int random = rand() % 100;
                if (random < chance){
                        cout << "Critical hit!" << endl;
                        dmg *= 1.5;
                }
        }
        ```

    * Rewards 

* File input/output
     * File Input (when player was defeated and chose to retry the game, their stored game status will be loaded)
        ```cpp
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

     * File out (To save player's game status in checkpoints) 


