#include <iostream>
#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <random>
#include <cmath>
#include <algorithm>

#include "character.hpp"
#include "enemymoves.hpp"
using namespace std;

void EnemyMoves::Enemy_ExecuteMove(MainCharacter &m, Enemy &e, vector<string> &dialog) {
    chooseSkillType(e);
    if (e.hp >= e.max_hp){}
    
    Enemy_Skill useable_skill = {};
}    
vector<double> EnemyMoves::z_score(vector<double> &skill_uses, vector<int> &skill_num, int &type_num_s){
    vector<double> standard_score(type_num, 0);
    double mean = 0;
    for (int i = 0; i < type_num; i++){
        if (skill_num[i] == 0) {
            type_num_s--;
            continue;
        }
        mean += skill_uses[i];
    }
    if (type_num_s > 0) {
        mean /= type_num_s;
        double variance = 0;
        for (int i = 0; i < type_num; i++){ // calculate variance
            if (skill_num[i] == 0) {
                continue;
            }
            variance += (skill_uses[i] - mean)*(skill_uses[i] - mean);
        }
        variance /= type_num_s;
        cout << "Number: " << type_num_s << " Mean: " << mean << " Variance: " << variance;
         
        for (int i = 0; i < type_num; i++){ // turn to standard score
            if (skill_num[i] == 0) {
                continue;
            }
            if (variance == 0) {
                standard_score[i] = 0;
            }
            else {
                standard_score[i] = (skill_uses[i] - mean) / sqrt(variance);
            }
        }        
    }
    return standard_score;
}
int EnemyMoves::chooseSkillType(Enemy &e){
        // calculate the probability of which type should use
    int type_num_s = type_num; // number of type of skill that have at least 1 skill
    double normal_attack_prob = 0.4;
    vector<Enemy_Skill> attack_skills, defend_skills, interfence_skills, regerneration_skills;
    vector<int> skill_num(type_num, 0);
    vector<double> skill_uses(type_num, 0), skill_weighting = {0.3, 0.3, 0.2, 0.2}; // with the same order
    for (auto &skill: e.skill_list){
        string type = skill.type;
        if (type == "attack"){
            attack_skills.push_back(skill);
            skill_uses[0] += skill.uses;
            skill_num[0]++;
        }
        else if (type == "defend"){
            defend_skills.push_back(skill);
            skill_uses[1] += skill.uses;
            skill_num[1]++;
        }
        else if (type == "interfere"){
            interfence_skills.push_back(skill);
            skill_uses[2] += skill.uses;
            skill_num[2]++;
        }
        else if (type == "regenerate"){
            regerneration_skills.push_back(skill);
            skill_uses[3] += skill.uses;
            skill_num[3]++;
        }
    }
    //testing
    skill_uses[0] = 0;
    skill_uses[3] = 1;
    //***
    vector<double> probability(type_num+1, 0);
    probability[0] = 1; // base attack
    vector<double> standard_score = z_score(skill_uses, skill_num, type_num_s);
    double min = 0;
    for (double i: standard_score){
        if (i < min){
            min = i;
        }
    }
    double max = 0;
    for (double i: standard_score){
        if (i > min){
            max = i;
        }
    }
    double difference = max - min;

    double prob_sum; 
    for(int i = 0; i < type_num; i++){
        if (skill_num[i] != 0){
            prob_sum += skill_weighting[i];
        }
    }

    if (type_num_s == 0){ // no skill
        probability[0] = 1;
    }
    else if (difference == 0){ // all skill use the same time
        double skill_prob = (1 - normal_attack_prob);
        probability[0] = normal_attack_prob;
        for (int i = 0; i < type_num; i++){
            if (skill_num[i] == 0){
                probability[i+1] = 0;
            }
            else {
                probability[i+1] = skill_prob * skill_weighting[i]/prob_sum;
            }
        }
    }
    else { 
        for (int i = 0; i < type_num; i++){
            if (skill_num[i] == 0){
                probability[i+1] = 0;
            }
            else {
                probability[i+1] = difference/(standard_score[i] - min + 1) * skill_weighting[i]/prob_sum * type_num_s;
            }
        }
        double sum;
        for (int i = 0; i < type_num; i++){
            if (skill_num[i] != 0) // only calculate type that have at least 1 skill.
                sum += probability[i+1];
        }
        probability[0] = sum * normal_attack_prob/(1 - normal_attack_prob); // p/(sum+p) = base
        // calibrate all prob sum to 1
        double total_sum = 0;
        for (auto i: probability){
            total_sum += i;
        }
        for (int i = 0; i < probability.size(); i++){
            probability[i] /= total_sum;
        }
    }
    /* //output testing
    cout << endl;
    for (auto i: skill_num){
        cout << i << " ";
    }
    cout << endl;
    for (auto i: skill_uses){
        cout << i << " ";
    }
    cout << endl;
    for (auto i: standard_score){
        cout << i << " ";
    }
    cout << endl;
    for (auto i: probability){
        cout << i << " ";
    }
    cout << endl;
    // *** end */

    time_t seed = time(NULL);
    mt19937 gen(seed);

    discrete_distribution<int> distribution(probability.begin(), probability.end());
    int randomNum = distribution(gen);

    int skillID;
    switch (randomNum)
    {
    case 0:
        skillID = 0; // normal attack
        break;
    case 1:
        skillID = chooseSkill(attack_skills);
        break;
    case 2:
        skillID = chooseSkill(defend_skills);
        break;
    case 3:
        skillID = chooseSkill(interfence_skills);
        break;
    case 4:
        skillID = chooseSkill(regerneration_skills);
        break;
    default:
        cout << "some error may happen" << endl; // should not go to default
    }
    return skillID;

}
int EnemyMoves::chooseSkill(vector<Enemy_Skill> skills) {
    int size = skills.size();
    if (size == 1){
        return skills[0].index;
    }
    // for size > 2
    vector<double> skill_uses(type_num, 0), probability(type_num, 0), standard_score = {};
    double mean;
    for (auto &skill: skills){
        skill_uses.push_back(skill.uses);
        mean += skill.uses;
    }
    double variance = 0;
    for (auto &i: skill_uses){
        variance += (i - mean)* (i - mean);
    }
    if (variance == 0){
        for (int i = 0; i < size; i++){
            probability[i] = 1/size;
        }
    }
    else {
        for (int i = 0; i < size; i++){
            standard_score.push_back((skill_uses[i]-mean)/sqrt(variance));
        }
        double min = 0;
        for (double i: standard_score){
            if (i < min){
                min = i;
            }
        }
        double max = 0;
        for (double i: standard_score){
            if (i > min){
                max = i;
            }
        }
        for (int i = 0; i < size; i++){
            probability[i] = (max - min)/(standard_score[i] - min + 1);
        }
        int prob_sum = 0;
        for (int i = 0; i < size; i++){
            prob_sum += probability[i];
        }
        for (int i = 0; i < size; i++){
            probability[i] /= prob_sum;
        }
    }

    time_t seed = time(NULL);
    mt19937 gen(seed);
    discrete_distribution<int> distribution(probability.begin(), probability.end());
    int randomNum = distribution(gen);
    return randomNum;
}
