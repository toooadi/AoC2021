#include <fstream>
#include <iostream>

using namespace std;
int main() {
    string filename = "inputDayOne.txt";
    ifstream input_file(filename);

    if(!input_file.is_open()) {
        cout << "Could not open file" << endl;
        return EXIT_FAILURE;
    }

    int prev_num;
    int num;
    int counter = 0;

    input_file >> prev_num;

    while(input_file >> num) {
        counter += prev_num < num ? 1 : 0;
        prev_num = num;
    }
    input_file.close();
    cout << counter << endl;

    return EXIT_SUCCESS;
}