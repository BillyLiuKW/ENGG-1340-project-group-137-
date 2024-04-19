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
        // default construction to make a screen
        Screen(int height, int width) {
            //cout << "e" << endl;
            this->height = height; // assign the value of the size
            this->width = width;
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
        void insert_information(int row, int col, Enemy info);
        void insert_information(int row, int col, MainCharacter info);
        //insert a line to seperate the display screen
        void insert_speration(int row);
        //insert dialog
        void insert_dialog();
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
