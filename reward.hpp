#ifndef RANDOM_REWARD_HPP
#define RANDOM_REWARD_HPP

#include "character.hpp"
using namespace std;

class random_reward{
    public:
        void reward(MainCharacter &m);
    private:
        void ability(MainCharacter &m);
        void skill(MainCharacter &m);
};

#endif