#ifndef ENEMYMOVE_HPP
#define ENEMYMOVE_HPP

#include <iostream>
#include <vector>
#include <iostream>

#include "character.hpp"
using namespace std;

class EnemyMoves{
    public:
        int type_num = 4; // number of type of skill
        void Enemy_ExecuteMove(MainCharacter &m, Enemy &e, vector<string> &dialogs);
        vector<double> z_score(vector<double> &skill_uses, vector<int> &skill_num, int& type_num_s);
    private:
        int chooseSkillType(Enemy &e); // returm skill chosen in chooseSkill()
        int chooseSkill(vector<Enemy_Skill> skills); // only use in chooseSkillType()
    
};

#endif
