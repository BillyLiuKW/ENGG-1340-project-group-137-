#ifndef SCREEEN.HPP
#define SCREEEN.HPP

#include <iostream>
#include <string>
#include <vector>

using namespace std;
typedef vector< vector<char> > array2d;
struct format{
    int start_row = 0;
    int start_col = 0; // index of starting letter
    int length = 0;
    vector<string> format_types = {}; 
};

class Screen{
    public:
        //size of the screen
        int height = 50, width = 50;
        Screen();

        //make the edge and conern of the screen
        void create_edge(array2d &screen);
        // insert the item to the screen, remove all format information and put them in the format_position list
        void insert_item(int start_row, int start_col, const vector<string> item, array2d &screen, vector<format> &format_position, vector<string> types);
        // print screen
        void print_screen(array2d screen, vector<format> &format_position);
        // only use in sort_list(), 
        bool compareItems(const format &item1, const format &item2);
        // sort the format_position by column position in descending order
        void sort_list(vector<format> &format_position);
        // insert the text format in the screen
        void insert_format(array2d &screen, format f);
        // insert the text format in the format_position list
        void formatting(int row, int col, string &line, vector<format> &format_position, int height_limit, int width_limit);
        // print all the format location
        void print_format(vector<format> format_position);
        // insert the battelfield to the screen
        void insert_battelfield();
        // insert the information of the character
        void insert_information();   
    private:
};

#endif
