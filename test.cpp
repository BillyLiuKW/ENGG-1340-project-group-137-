#include <iostream>
#include <ctime>
#include <unistd.h> // time delay
#include <vector>
#include <algorithm>
#include <map>

using std::cout;
using std::endl;
using std::vector;
using std::string;

typedef vector< vector<char> > array2d; 

struct format{
    int start_row = 0;
    int start_col = 0; // index of starting letter
    int length = 0;
    vector<string> format_types = {}; 
};

const vector<string> character= 
{
    "       fWvuvXB       ",
    "     -Y(_(}}z>jk^    ",
    "    J?[<ll;:l X>u    ",
    "    ra,llllllllnrn   ",
    " `~+<`lllllllll+Z+ & ",
    " ^&]lllllllllll>llbz ",
    "  d|ll        l>l\"Z\" ",
    "  d(ll  DEAD  l>llZ\" ",
    "  b(ll        l>^lZ^ ",
    "  d(lllllllllll>llZ\" ",
    "  d|lllllllllll>llZ\" ",
    "  d(iIlllllllll>`IZ\" ",
    "  bxi!llllllll[~>lZ^ ",
    "Ua^lJ||JJJJJJJZmar}o[",
    "*Bzj1}}}}}}}}}}1}zXn8",
}; // size = 15*21 row * col

const std::map <string, string> formatMap = {
    {"reset", "\033[0m"},
    {"bold", "\033[1m"},
    {"red", "\033[31m"},
    {"yellow", "\033[33m"},
    {"cyan", "\033[36m"}
};

void initialize_screen();
void create_edge(array2d &screen);
void insert_item(int start_row, int start_col, const vector<string> item, array2d &screen, vector<format> &format_position, vector<string> types);
void print_screen(array2d screen, vector<format> &format_position);
bool compareItems(const format &item1, const format &item2);
void sort_list(vector<format> &format_position);
void insert_format(array2d &screen, format f);
void formatting(int row, int col, string &line, vector<format> &format_position, int height_limit, int width_limit);
void print_format(vector<format> format_position);

int main() {
    //cout << "\e[8;50;200t"; // set the size of the terminal to 100*100
    system("clear");
    
    int height = 65, width = 100; // 65, 
    array2d screen(height, vector<char>(width, ' ')); //create a 2d vector of height * size with default value "
    vector<format> format_position = {}; 

    create_edge(screen); //pass the address (i'm afraid to use dynamic array)

    insert_item(10, 10, character, screen, format_position, {""});
    //insert_item(10, 31, character, screen, format_position, {"yellow"});

    vector<string> hp = {{"HP [==============]"},{"HP [==============]"}};
    string a = "<Format><red>";
    insert_item(10+15+1, 10 + ((21-4)/2), {"Name"}, screen, format_position, {"bold"});
    insert_item(10+15+2, 10, {"HP [==============]"}, screen, format_position, {"red", "bold"});
    insert_item(10+15+3, 10, {"MP [==============]"}, screen, format_position, {"cyan", "bold"});


    print_screen(screen, format_position);
    //print_format(format_position);
    
    return 0;
}

void create_edge(array2d &screen){
    const char horizontal_edge = '-';
    const char vertical_edge = '|';
    const char corner = '+';
    int height = screen.size();
    int width = screen[0].size();

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

void insert_item(int start_row, int start_col, vector<string> item, array2d &screen, vector<format> &format_position, vector<string> types){
    int row_size = item.size();
    int height_limit = screen.size();
    int width_limit = screen[0].size();
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
        formatting(start_row + i, start_col, item[i], format_position, height_limit, width_limit);
        //cout << item[i];
        int col_size = item[i].length();
        for (int j = 0; j < col_size; j++){
            if (start_col + j >= width_limit || start_row + i >= height_limit){
                break; // prevent anything of screen
            }
            screen[start_row + i][start_col + j] = item[i][j];
        }
    }
}

void formatting(int row, int col, string &line, vector<format> &format_position, int height_limit, int width_limit){
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
        if (f.start_col >= width_limit){ // if the starting point is somehow outside the screen, ingore the format
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

bool compareItems(const format &item1, const format &item2){
    // Compare based on the column position 
    return item1.start_col > item2.start_col; // Sort in desencding order
}

void sort_list(vector<format> &format_position){
    // sort the format location in descending order by the column
    std::sort(format_position.begin(), format_position.end(), compareItems);
}

void insert_format(array2d &screen, format f){
    // insert the ASCI format into the screen accroding to format_position
    int row = f.start_row;
    int col = f.start_col; // index
    int length = f.length;
    int width_limit = screen[0].size(); // max number of item in a row (not index)
    if (col + length > width_limit){ // if part of coloured word is outside the screen, change the length to the last word inside the screen
        length = width_limit - col;
    }
    
    string reset = formatMap.find("reset")->second;
    screen[row].insert(screen[row].begin()+col+length, reset.begin(), reset.end());
    for (string type: f.format_types){
        string value = formatMap.find(type)->second; 
        screen[row].insert(screen[row].begin()+col, value.begin(), value.end());
    }
}

void print_screen(array2d screen, vector<format> &format_position){
    //add the format
    sort_list(format_position);
    for (format f: format_position){
        insert_format(screen, f);
    }

    //print all element
    for (const auto& row : screen) {
        for (const auto& element : row) {
            std::cout << element;
        }
        std::cout << std::endl;
    }
}

void print_format(vector<format> format_position){
    for (auto &f : format_position){
        for (auto &type : f.format_types){
            cout << type << " ";
        }
        cout << "row: " << f.start_row << " col: " << f.start_col << " length: " << f.length << endl;
    }
}



                             
