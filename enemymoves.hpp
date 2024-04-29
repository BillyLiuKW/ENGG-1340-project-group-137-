#ifndef ENEMYMOVE_HPP
#define ENEMYMOVE_HPP

#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <functional>

#include "character.hpp"
using namespace std;

class EnemyMoves{
    public:
        // this map provide a template for the skill effect skill {{"e_hp 70"}}
        map<string, function<void(EnemyMoves&, double, double)> > skill_option = {
            {"e_hp", &EnemyMoves::e_hp},
            {"m_hp", &EnemyMoves::m_hp},
            {"e_atk", &EnemyMoves::e_atk},
            {"m_atk", &EnemyMoves::m_atk},
            {"e_def", &EnemyMoves::e_def},
            {"m_def", &EnemyMoves::m_def},
            {"e_cont_hp", &EnemyMoves::e_cont_hp},
            {"e_cont_hp_const", &EnemyMoves::e_cont_hp_const},
            {"m_cont_hp", &EnemyMoves::m_cont_hp},
            {"m_cont_hp_const", &EnemyMoves::m_cont_hp_const},
            {"e_crit_chance", &EnemyMoves::e_crit_chance},
            {"e_crit_damage", &EnemyMoves::e_crit_damage},
            {"m_mp", &EnemyMoves::m_mp},
            
        };
        MainCharacter &m;
        Enemy &e;
        vector<string> &dialogs;
        int type_num = 4; // number of type of skill
        // set a in class variable so i don't need to pass to many function arguments
        EnemyMoves(MainCharacter &main_c, Enemy &enemy, vector<string> &dialogs_list): m(main_c), e(enemy), dialogs(dialogs_list){}
        void Enemy_ExecuteMove();
        // use normal attack
        void normal_attack();
        // use the chosen skill
        void use_skill(int skill_id);
        // calculate all boost and subtract all boost by 1 round and remove rounds <= 0
        void calculate_boost(); 
        // change enemy hp by continue damage/ regen
        void hp_change(); // apply the conyinue damage or regeneration
    private:
        vector<double> z_score(vector<double> &skill_uses, vector<int> &skill_num, int& type_num_s); // convert the skills uses to a standard score.
        int chooseSkillType(); // choose a skill type to use base on their number of uses. return skill index chosen in chooseSkill()
        int chooseSkill(vector<Enemy_Skill> skills); // only use in chooseSkillType(), choose a skill in "skills" lists and return its index.
        void e_hp(double multiplier, double other); // add enemy HP by "multiplier"
        void m_hp(double multiplier, double other); // damage player HP by "multiplier" * some calculation, corrlected by "other"
        void e_atk(double multiplier, double other); // increase/decrease enemy attack by "multiplier" for "other" rounds
        void m_atk(double multiplier, double other); // increase/decrease player atttack by "multiplier" for "other" rounds
        void e_def(double multiplier, double other); // increase/decrease enemy defend by "multiplier" for "other" rounds
        void m_def(double multiplier, double other); // increase/decrease player defend by "multiplier" for "other" rounds
        void e_cont_hp(double multiplier, double other); // increase/decrease enemy HP by "multiplier" * some calculation for "other" rounds
        void e_cont_hp_const(double multiplier, double other); // increase/decrease enemy HP by constant "multiplier" for "other" rounds
        void m_cont_hp(double multiplier, double other); // increase/decrease player HP by "multiplier" * some calculation for "other" rounds
        void m_cont_hp_const(double multiplier, double other); // increase/decrease player HP by constant "multiplier" for "other" rounds
        void e_crit_chance(double multiplier, double other); // increase/decrease enemy critical chance by "multiplier" for "other" rounds
        void e_crit_damage(double multiplier, double other); // increase/decrease enemy critical damage by "multiplier" for "other" rounds
        void m_mp(double multiplier, double other); // increase/decrease player mp by "multiplier" for "other" rounds
        int is_critical(double probability); // calculate is the attack critical with chance "probability". return 1 if critical
};

#endif
