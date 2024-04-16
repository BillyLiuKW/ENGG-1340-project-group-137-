#include <iostream>
#include "game.hpp"
#include "character.hpp"
#include "moves.hpp"
using namespace std;

int main() {
  MainCharacter hero;
  Enemy test_e(1);
  GAME game;
  game.StartGame(hero, test_e);
  return 0;
}
