
# Dungeons

Embark on an adventure to conquer a dungeon filled with carefully designed mechanics!


## Gameplay

You will start the adventure as the Hero. As you progress through the floors of the dungeon, you will gain more power and  your goal is defeat [insert final boss name here].

In each turn, you can choose a move to use.


## Identification

- [@YAM MAN NOK (3036223294)](https://github.com/Flybug234)


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
