#ifndef SCREEEN_HPP
#define SCREEEN_HPP

#include <iostream>
#include <string>
#include <vector>
#include "character.hpp"

using namespace std;
struct format{
    int start_row = 0;
    int start_col = 0; // index of starting letter
    int length = 0;
    vector<string> format_types = {}; 
};

class Screen{
    public:
        int height, width;
        vector<format> format_position = {};
        vector<vector<char> > screen;
        int max_dialog = 8;
        vector<string> dialogs = {"BATTLE START"}; // store any action by enemy and character

        /*  a sample. use display.dialogs.push_back("dialoge") to insert new dialog. 
            {"test1",
            "Enemy <format><|yellow|>[Golbin]<end> has used skill <format><|purple|>[SKILL]<end>",
            "<format><|blue|>Hero<end> <format><|red|>HP<end> <format><|red|><|bold|>-50<end>", 
            "<format><|blue|>Hero<end> has used skill <format><|purple|>[Heal]<end>", 
            "<format><|blue|>Hero<end> <format><|red|>HP<end> <format><|green|><|bold|>+10<end>",
            "test6",
            }; */ 

        // default construction to make a screen
        Screen(int height, int width) {
            //cout << "e" << endl;
            this->height = height; // assign the value of the size
            this->width = width;
            dialogs.resize(max_dialog, " ");
            screen.resize(height, vector<char>(width, ' '));
            create_edge();
        };

        // insert the item to the screen, remove all format information and put them in the format_position list
        void insert_item(int start_row, int start_col, vector<string> item, vector<string> types);
        // print screen
        void print_screen();
        // print all the format location
        void print_format();
        // insert the battelfield to the screen
        void insert_battelfield(MainCharacter& m, Enemy& e);
        // insert the information of the enemy of character
        void insert_information(int row, Enemy info);
        void insert_information(int row, MainCharacter info);
        //insert a line to seperate the display screen
        void insert_speration(int row);
        //insert dialog
        void insert_dialog(int start_row);
        //clear the screeen
        void clear_screen();

    private:
        //make the edge and conern of the screen
        void create_edge();
        // only use in sort_list(), 
        static bool compareItems(const format &item1, const format &item2);
        // sort the format_position by column position in descending order
        void sort_list();
        // insert the text format in the screen
        void insert_format(format f);
        // insert the text format in the format_position list
        void formatting(int row, int col, string &line);

};
#endif
