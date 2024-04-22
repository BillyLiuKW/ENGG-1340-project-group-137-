#include <iostream>
#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <random>
#include <cmath>
#include <algorithm>
#include <sstream>
#include <functional>
#include "character.hpp"
#include "enemymoves.hpp"
using namespace std;

void EnemyMoves::Enemy_ExecuteMove() {
    // chose a skill or normal attack
    int skill_id = chooseSkillType();
    //cout << "Skill: " << skill_id << endl; // test

    // execute the skill
    if (skill_id == 0){
        normal_attack();
    }
    else {
        use_skill(skill_id);
    }
    // minus number of rounds of all boost by 1
    boost_count_down();
    //calculate the boosts for the next round
    e.atk_boost_sum = 0;
    for (auto &pair: e.atk_boost) {
        e.atk_boost_sum += pair.first;
    }
    e.def_boost_sum = 0;
    for (auto &pair: e.def_boost) {
        e.def_boost_sum += pair.first;
    }
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
int EnemyMoves::chooseSkillType(){
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
        double sum = 0;
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
    cout << "skill_num ";
    for (auto i: skill_num){
        cout << i << " ";
    }
    cout << endl;
    cout << "skill_uses ";
    for (auto i: skill_uses){
        cout << i << " ";
    }
    cout << endl;
    cout << "standard_score ";
    for (auto i: standard_score){
        cout << i << " ";
    }
    cout << endl;
    cout << "prob ";
    for (auto i: probability){
        cout << i << " ";
    }
    cout << endl;
    // *** end */

    random_device rd;
    mt19937 generator(rd()); 
    discrete_distribution<int> distribution(probability.begin(), probability.end());
    int randomNum = distribution(generator);

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
    //cout << "size: " << size << endl; // test
    if (size == 1){
        return skills[0].index;
    }
    // for size > 2
    vector<double> skill_uses = {}, probability(size, 0), standard_score = {};
    double mean = 0;
    for (auto &skill: skills){
        skill_uses.push_back(skill.uses);
        mean += skill.uses;
    }
    mean /= size;
    double variance = 0;
    for (auto &i: skill_uses){
        variance += (i - mean)* (i - mean);
    }
    variance /= size;
    if (variance == 0){
        for (int i = 0; i < size; i++){
            probability[i] = 1/static_cast<double>(size);
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
        double prob_sum = 0;
        for (int i = 0; i < size; i++){
            prob_sum += probability[i];
        }
        for (int i = 0; i < size; i++){
            probability[i] /= prob_sum;
        }
    }
    /*// test 
    cout << endl <<"Mean(1): " << mean <<" Variance(1): " << variance ;
    cout << endl;
    cout << "skill_uses(1) ";
    for (auto i: skill_uses){
        cout << i << " ";
    }
    cout << endl;
    cout << "standard_score(1) ";
    for (auto i: standard_score){
        cout << i << " ";
    }
    cout << endl;
    cout << "Prob(1): ";
    for (auto i: probability){
        cout << i << " ";
    }
    cout << endl;
    // test end*/

    random_device rd;
    mt19937 generator(rd()); 
    discrete_distribution<int> distribution(probability.begin(), probability.end());
    int randomNum = distribution(generator);
    return skills[randomNum].index;
}
void EnemyMoves::normal_attack(){
    dialogs.push_back("Enemy <format><|yellow|>[" + e.name + "]<end> has use <format><|bold|>normal attack<end>.");
    double damage;
    damage = (e.atk + e.atk_boost_sum) - (m.def + m.def_boost_sum);
    (damage < 1)? damage = 1: damage = damage ; // if damage < 1, set damage to 1.
    m.hp -= static_cast<int>(damage);
    string int_value = to_string(static_cast<int>(damage));
    dialogs.push_back("<format><|blue|>Hero<end> <format><|red|>HP<end> <format><|red|><|bold|>-"+ int_value + "<end>");
}
void EnemyMoves::use_skill(int skill_id){
    dialogs.push_back("Enemy <format><|yellow|>[" + e.name + "]<end> has use skill <format><|purple|>[" + e.skill_list[skill_id-1].skill_name + "]<end>.");
    for (string effect: e.skill_list[skill_id - 1].effect){
        e.skill_list[skill_id -1].uses++;
        istringstream iss(effect);
        string option;
        double value;
        double other;
        iss >> option >> value >> other;
        
        if (skill_option.find(option) == skill_option.end()){
            cout << "skill option: " << option << " not found in skill: " << e.skill_list[skill_id-1].skill_name;
            continue;
        }
        skill_option[option](*this, value, other);
    }
}
void EnemyMoves::e_hp(double multiplier, double other){
    e.hp += multiplier;
    // Enemy [name]'s HP + value (grenn if positive, red if negative)
    string int_value = to_string(static_cast<int>(multiplier)); // make the double have no decimal place and then string
    string dialog = "Enemy <format><|yellow|>[" + e.name + "]<end>'s <format><|red|>HP<end> <format>";
    dialog += ((multiplier < 0)? ("<|red|>" + int_value): ("<|green|>+" + int_value));
    dialog += "<end>";
    dialogs.push_back(dialog);  
}
void EnemyMoves::m_hp(double multiplier, double other){
    double damage = 0;
    damage = (e.atk +e.atk_boost_sum) * multiplier - (m.def + m.def_boost_sum);
    (damage < 1)? damage = 1: damage = damage;
    m.hp -= static_cast<int>(damage);
    string int_value = to_string(static_cast<int>(damage));
    string dialog = "<format><|blue|>Hero<end> <format><|red|>HP<end> <format><|red|><|bold|>-"+ int_value +"<end>";
    dialogs.push_back(dialog);

}
void EnemyMoves::e_atk(double multiplier, double other){
    e.atk_boost.push_back(make_pair(static_cast<int> (multiplier), static_cast<int>(other))); // other the number of round
    string int_value_1 = to_string(static_cast<int>(multiplier));
    string int_value_2 = to_string(static_cast<int>(other));
    string dialog = "Enemy <format><|yellow|>[" + e.name + "]<end>'s <format><|cyan|>ATK<end> <format>";
    dialog += ((multiplier < 0)? ("<|red|>" + int_value_1): ("<|green|>+" + int_value_1));
    dialog += "<end> for <format><|yellow|>" + int_value_2 + "<end> rounds.";
    dialogs.push_back(dialog);
    
}
void EnemyMoves::m_atk(double multiplier, double other){
    m.atk_boost.push_back(make_pair(static_cast<int> (multiplier), static_cast<int>(other))); // other the number of round
    string int_value_1 = to_string(static_cast<int>(multiplier));
    string int_value_2 = to_string(static_cast<int>(other));
    string dialog = "<format><|blue|>Hero<end> <format><|cyman|>ATK<end> <format>";
    dialog += ((multiplier < 0)? ("<|red|>" + int_value_1): ("<|green|>+" + int_value_1));
    dialog += "<end> for <format><|yellow|>" + int_value_2 + "<end> rounds.";
    dialogs.push_back(dialog);

}
void EnemyMoves::e_def(double multiplier, double other){
    e.def_boost.push_back(make_pair(static_cast<int> (multiplier), static_cast<int>(other))); // other the number of round
    string int_value_1 = to_string(static_cast<int>(multiplier));
    string int_value_2 = to_string(static_cast<int>(other));
    string dialog = "Enemy <format><|yellow|>[" + e.name + "]<end>'s <format><|cyan|>DEF<end> <format>";
    dialog += ((multiplier < 0)? ("<|red|>" + int_value_1): ("<|green|>+" + int_value_1));
    dialog += "<end> for <format><|yellow|>" + int_value_2 + "<end> rounds.";
    dialogs.push_back(dialog);
}
void EnemyMoves::m_def(double multiplier, double other){
    m.atk_boost.push_back(make_pair(static_cast<int> (multiplier), static_cast<int>(other))); // other the number of round
    string int_value_1 = to_string(static_cast<int>(multiplier));
    string int_value_2 = to_string(static_cast<int>(other));
    string dialog = "<format><|blue|>Hero<end> <format><|cyan|>DEF<end> <format>";
    dialog += ((multiplier < 0)? ("<|red|>" + int_value_1): ("<|green|>+" +int_value_1));
    dialog += "<end> for <format><|yellow|>" + int_value_2 + "<end> rounds.";
    dialogs.push_back(dialog);
} 
void EnemyMoves::boost_count_down(){
    for (auto &pair: e.atk_boost) {
        pair.second--;
    }
    for (auto &pair: e.def_boost) {
        pair.second--;
    }
    // remove all pair that round remains < 0 with lambda function
    e.atk_boost.erase(remove_if(e.atk_boost.begin(), e.atk_boost.end(), [](pair<int, int> pair){return pair.second < 0;}), e.atk_boost.end());
    e.def_boost.erase(remove_if(e.def_boost.begin(), e.def_boost.end(), [](pair<int, int> pair){return pair.second < 0;}), e.def_boost.end());
}
