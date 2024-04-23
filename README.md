
# Dungeons

Embark on an adventure to conquer a dungeon filled with carefully designed mechanics!


## Gameplay

You will start the adventure as the Hero. As you progress through the floors of the dungeon, you will gain more power and  your goal is defeat [insert final boss name here].

In each turn, you can choose a move to use.


## Identification

- [@YAM MAN NOK (3036223294)](https://github.com/Flybug234)
- [@LIU KONG WA (3036227446)](https://github.com/BillyLiuKW)
- [@CHAN WA HONG(3036227226)](https://github.com/cwhong05)

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
    ```cpp
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

                
        }
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

     * File output (To save player's game status in checkpoints) 
         ```cpp
        void GAME::Victory(MainCharacter &m, Enemy &e) {
                cout << "Congratulations! The " << e.name << " is defeated!" << endl;
                this->current_level++;
                reward(m,this->current_level);// player can receive reward after every boss and checkpt
                // checkpoint reward are tackle in same function
                if (this->current_level == 3 || this->current_level == 5 || this->current_level == 7) {
                        //player can get reward from these level and they are not required to beat any enemy in these levels.
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


