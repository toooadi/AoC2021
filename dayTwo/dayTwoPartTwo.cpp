#include <fstream>
#include <iostream>
//#include <sstring>
#include <string>
using namespace std;

int main() {
    string filename = "inputPartOne.txt";
    ifstream input_file(filename);

    if(!input_file.is_open()) {
        cout << "Could not open file" << endl;
        return EXIT_FAILURE;
    }
    
    int hor = 0;
    int aim = 0;
    int dep = 0;
    string dir;
    int move;
    while(input_file >> dir) {
        string conv;
        input_file >> conv;
        move = stoi(conv);

        if (dir == "forward") {
            hor += move;
            dep += move * aim;
        } else if (dir == "down") {
            aim += move;
        } else {
            aim -= move;
        }
    }
    int res = dep * hor;
    cout << res << endl;

    return EXIT_SUCCESS;
}