#include "screen.hpp"
#include "textformat.hpp"

#include <iostream>
#include <ctime>
#include <unistd.h> // time delay
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

void Screen::create_edge(){
    const char horizontal_edge = '-';
    const char vertical_edge = '|';
    const char corner = '+';
    //create edge
    for (int col = 0; col < width; col++){
        screen[0][col] = horizontal_edge;
        screen[height-1][col] = horizontal_edge;
    }
    for (int row = 0; row < height; row++){
        screen[row][0] = vertical_edge;
        screen[row][width-1] = vertical_edge;
    }
    //create corner
    screen[0][0] = corner;
    screen[0][width-1] = corner;
    screen[height-1][0] = corner;
    screen[height-1][width-1] = corner;
}
void Screen::print_screen(){
    system("clear");
    //add the format
    sort_list();
    for (format f: format_position){
        insert_format(f);
    }
    //print all element
    for (const auto& row : screen) {
        for (const auto& element : row) {
            std::cout << element;
        }
        std::cout << std::endl;
    }
}
void Screen::sort_list(){
    // sort the format location in descending order by the column
    sort(format_position.begin(), format_position.end(), compareItems);
}
bool Screen::compareItems(const format &item1, const format &item2){
    // Compare based on the column position 
    return item1.start_col > item2.start_col; // Sort in desencding order
}
void Screen::insert_format(format f){
    // insert the ASCI format into the screen accroding to format_position
    int row = f.start_row;
    int col = f.start_col; // index
    int length = f.length;; 
    // width = rightmost index + 1 (number of item in a row)
    if (col + length > width){ // if part of coloured word is outside the screen, change the length to the last word inside the screen
        length = width - col;
    }
    string reset = formatMap.find("reset")->second;
    screen[row].insert(screen[row].begin()+col+length, reset.begin(), reset.end());
    for (string type: f.format_types){
        string value = formatMap.find(type)->second; 
        screen[row].insert(screen[row].begin()+col, value.begin(), value.end());
    }
}
void Screen::insert_item(int start_row, int start_col, vector<string> item, vector<string> types){
    int row_size = item.size();
    //insert the provide format to every line in the item
    string start_format = "", end_format = "";
    if (!types.empty()){
        start_format += "<format>";
        for (string type: types){
            start_format += ("<|" + type + "|>");
        }
        end_format = "<end>";
    }
    for (int i = 0; i < row_size; i++){ // i = row
        item[i] = start_format + item[i] + end_format;
        //sample of formated text: {<format><|type1|><|type2|>Text<end>}
        formatting(start_row + i, start_col, item[i]);
        //cout << item[i];
        int col_size = item[i].length();
        for (int j = 0; j < col_size; j++){
            if (start_col + j >= width || start_row + i >= height){
                break; // prevent anything of screen
            }
            screen[start_row + i][start_col + j] = item[i][j];
        }
    }
}
void Screen::formatting(int row, int col, string &line){
    int start_pos = 0;
    while(true){
        start_pos = line.find("<format>", start_pos);
        if (start_pos == string::npos) {
            break;
        } 
        bool return_value = false;
        format f;
        f.start_row = row;
        f.start_col = col + start_pos;
        if (f.start_col >= width){ // if the starting point is somehow outside the screen, ingore the format
            break;
        }
        line.erase(start_pos, 8);
        while (true){
            int type_pos = line.find("<|", start_pos);
            if (type_pos == string::npos){
                break;
            }
            int stop_pos = line.find("|>", start_pos);
            string type = line.substr(type_pos+2, stop_pos-type_pos-2); //<|type|>
            line.erase(type_pos, stop_pos-type_pos+2);
            auto find_type = formatMap.find(type); // find if the elemet exist in format map
            if (find_type == formatMap.end()){ // if not exist
                continue;
            }
            return_value = true;
            f.format_types.push_back(type);
        }
        int end_pos = line.find("<end>", start_pos);
        line.erase(end_pos, 5);
        f.length = end_pos - start_pos;
        if (return_value){
            format_position.push_back(f);
        }
    }
}
void Screen::print_format(){
    for (auto &f : format_position){
        for (auto &type : f.format_types){
            cout << type << " ";
        }
        cout << "row: " << f.start_row << " col: " << f.start_col << " length: " << f.length << endl;
    }
}
