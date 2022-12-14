#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

int findPath(int **cave, int **path);

int main() {
    string filename = "inputPartOne.txt";
    ifstream input_file(filename);

    if(!input_file.is_open()) {
        cout << "Could not open file" << endl;
        return EXIT_FAILURE;
    }
    string input;
    int **path = new int*[100];
    int **cave = new int*[100];
    int row = 0;
    while (input_file >> input) {
        cave[row] = new int[100];
        path[row] = new int[100];
        for (int i = 0 ; i < 100 ; i++) {
            string conv = "";
            conv.push_back(input[i]);
            cave[row][i] = stoi(conv);
            path[row][i] = 0;
        }
        row++;
    }

    cout << findPath(cave, path) << endl;

    return EXIT_SUCCESS;
}

int findPath(int **cave, int **path) {

    for (int i = 0 ; i < 100 ; i++) {
        for (int j = 0 ; j < 100 ; j++) {
            if (i != 0 && j != 0) {
                int costTop = cave[i][j] + path[i - 1][j];
                int costLeft = cave[i][j] + path[i][j - 1];
                path[i][j] = costTop < costLeft ? costTop : costLeft;
            } else if (i != 0) {
                path[i][j] = cave[i][j] + path[i - 1][j];
            } else if(j != 0) {
                path[i][j] = cave[i][j] + path[i][j - 1];
            }
        }
    }

    return path[99][99];
}