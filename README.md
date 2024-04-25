
# Dungeon

Embark on an adventure to conquer a dungeon filled with carefully designed mechanics!


## Gameplay

You will start the adventure as the Hero. As you progress through the floors of the dungeon, you will gain more power and your goal is to conquer the dungeon.

In each turn, you can choose a move to use. You will always move first and the enemy AI will choose a move as well. Simpily enter the move number to fight the enemy. After defeating an enemy, rewards will be give and you can power up your character throughout the journey.


## Identification

- YAM MAN NOK (3036223294) [@Flybug234](https://github.com/Flybug234)
- LIU KONG WA (3036227446) [@BillyLiuKW](https://github.com/BillyLiuKW)
- CHAN WA HONG(3036227226) [@cwhong05](https://github.com/cwhong05)
- WONG CHAI   (3036221741) [@pizza-without-pineapple](https://github.com/pizza-without-pineapple)

## Features

* Random Events
    * Critical Hits
        * both player and enemy have a critical chance that can deal extra damage.
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
        * player can choose which type of reward they want to recieve. <br>
          After that, they will enter a sequence to generate a seed reward. <br>
          A reward will be given base on a random event generate by the seed.
            
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
        ```
    * Enemy's action
        * Enemy action is base on a probability model.  
          Enemy will execute normal attack or different types of skill base on this probability model.<br>
          This model will change depend on different situtation <br>
          e.g.
            * 1) When the health points of the enemy is lowerer, it has a higher chance to use defend or regenerate skill.
                 On the other hand, if the health points of the main character is lower, Enemy will use attack skill more fequently.
            * 2) probability of specific skill will vary base on how many times it is used
                 i.e. more it derivative from the mean usage, lesser chance it will be used.
    * Recover
        * After each battel, player will recieved a hp and mp recover. <br>
          The recover value is base on triangular distribution such that the median will have a highest probability.
          
              
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
         ```

     * File output (To save player's game status in checkpoints) 
        ```cpp
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
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // this line must be add after any cin <<. Otherwise it willmake a new line in getline
                if (y_n == 'y') {
                    ofstream fout("game_status.txt");
                    if (fout.is_open()) {
                        fout << m.name << "\n" << m.hp << " " << m.max_hp << " " << m.atk << " " << m.def << " " << m.mp << " " << m.max_mp << " ";
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
        ```
* Data Structures for Saving Game Status
  * Move Execution 
  ```cpp
  //Set up the function map to directly call the function using moveFunctions[i]
  //In moves.hpp
  map<int, function<void(MainCharacter&, Enemy&, Move_info, vector<string> &dialogs)> > moves::moveFunctions;
  ```
  ```cpp
  //Example usage
  //In moves.cpp
  void slash(MainCharacter &m, Enemy &e,Move_info info, vector<string> &dialogs){
        int damage = calculate_damage(info.power, m.atk + m.atk_boost_sum, e.def + e.def_boost_sum);
        m.hp -= info.cost;
        Critical_hit(damage, dialogs);
        e.hp -= damage;
        string int_value = to_string(damage);
        string dialog = display_damage(e, damage);
        dialogs.push_back(dialog);
  }
  moveFunctions[0] = slash;
  moveFunction[0](arg1,arg2,arg3,arg4);
  ```
  * Enemy's skill.
     * Each skill is a structure containing its index, skill type, name, and effect
          ```cpp
          // an example skill
          Enemy_Skill skill2 = {2, "attack", "Heavy Attack", vector<string>{"m_hp 15 0", "m_atk -3 3", "m_cont_hp -5 2"}};
          
          // the skill structure
          struct Enemy_Skill{
              int index; // index of the skill in the skill_list
              string type; // basic type of the skill: attack/ defend/ interfere (buff or debuff)/ regenerate 
              string skill_name;
              vector<string> effect;
              int uses; // number of skills used
          };
          ```
          
        * The effect in the skill store one or more simple action to do <br>
          For example, reduce player HP, increase own ATK etc. <br>
          the other arguments is the power and duration/ special effect (if any) <br>
          <br>
          a map will match each simple action and execute its corresponding
          ```cpp
          // part of the map
          map<string, function<void(EnemyMoves&, double, double)> > skill_option = {
              {"e_hp", &EnemyMoves::e_hp},
              {"m_hp", &EnemyMoves::m_hp},
              {"e_atk", &EnemyMoves::e_atk},
              {"m_atk", &EnemyMoves::m_atk},
              ...  
           };

          // part of an example function
          void EnemyMoves::m_hp(double multiplier, double other){
              double damage = 0;
              double penetrate = other; // ingore main character defend. up to 30% 
              int critical = is_critical(e.critical_chance + e.crit_chance_boost_sum);
              damage = (e.atk +e.atk_boost_sum) * multiplier * (1 + critical * (e.critical_damage + e.crit_damage_boost_sum)) / (m.def +    m.def_boost_sum) * (1 - 0.3 * penetrate);
              damage = max(1.0, damage);
              m.hp -= static_cast<int>(damage);
              ...
          }   
          ```
        * all the skills of an enemy will store at a vector of skill_structure.
          

       
  * Vector For Move Information
  ```cpp
  //In character.hpp
  //Define the Move_info contents
  struct Move_info{ //Store the information of the move
        string name;
        int ID;
        int power; 
        int cost;
        string type;
  };
  ```
  ```cpp
  //In moves.cpp
  //Set up the vector for moves
  vector<Move_info> moves::FULL_MOVE_POOL;
  ```
  ```cpp
  //Insert the Move_info to vector FULL_MOVE_POOL to save the information of the move
  void moves::iniializeMoves(){
    Move_info slashInfo = {"Slash", 0 ,20, 10, "Physical"};
    FULL_MOVE_POOL.push_back(slashInfo);
  }
  ```
* Dynamic Memory Management
  * Enemy Creation
  ```cpp
  // In character.hpp
  // Create a class definition for every enemy type
  class Dummy{
    public:
        Dummy();
        int hp;
        int atk;
        int def;
        double critical_chance;
        double critical_damage;
        string name;
        vector<string> image;
        int height;
        int width;
        vector<Enemy_Skill> skill_list;
  };
  ```
  ```cpp
  // In character.cpp
  // Temporarily create the class object and inserts the stats to the more general Enemy class
  // In Enemy class
  Dummy* dummyEnemy = new Dummy();
  hp = dummyEnemy->hp;
  max_hp = dummyEnemy->hp;
  atk = dummyEnemy->atk;
  def = dummyEnemy->def;
  critical_chance = dummyEnemy->critical_chance;
  critical_damage = dummyEnemy->critical_damage;              
  name = dummyEnemy->name;
  image = dummyEnemy->image;
  height = image.size();
  width = image[0].size();
  skill_list = dummyEnemy->skill_list;
  delete dummyEnemy; //Delete the temporary class object to free up memory
  break;
  ```
  * Checking, storing and updating the current level of the game (this pointer)
  ```cpp
  void GAME::Victory(MainCharacter &m, Enemy &e, Screen &display) {
    display.dialogs.push_back(" ");
    display.dialogs.push_back("<format><|yellow|>Congratulations!<end> You have defeated Enemy <format><|yellow|><|bold|>[" + e.name + "]<end>!");
    sleep(1);
    display.clear_screen();
    display.insert_battelfield(m, e); // input main character and enemy information to the screen
    display.print_screen();
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
    ```
    ```cpp
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
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // this line must be add after any cin <<. Otherwise it willmake a new line in getline
        if (y_n == 'y') {
            ofstream fout("game_status.txt");
            if (fout.is_open()) {
                fout << m.name << "\n" << m.hp << " " << m.max_hp << " " << m.atk << " " << m.def << " " << m.mp << " " << m.max_mp << " ";
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
   ```

* Program Codes in Multiple Files
  ```cpp
  // In game.cpp
  // We make .hpp header files to use code from other files
  #include "character.hpp"
  #include "game.hpp"
  #include "screen.hpp"
  #include "moves.hpp"
  #include "enemymoves.hpp"
  ```
  


        
