#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

void tokenize(string &str, char delim, vector<int> &out) {
    stringstream ss(str);
    std::string s; 
    while (std::getline(ss, s, delim)) { 
        int put = stoi(s);
        out.push_back(put);
    } 
}

int main() {
    string filename = "inputPartOne.txt";
    ifstream input_file(filename);

    if(!input_file.is_open()) {
        cout << "Could not open file" << endl;
        return EXIT_FAILURE;
    }
    
    string input;
    vector<int> fromX, fromY, toX, toY;
    vector<int> temp;

    //Matrix has to be stored in the heap because it's so large
    int **map = new int*[1000];
    for (int i = 0 ; i < 1000 ; i++) {
        map[i] = new int[1000];
        for (int j = 0 ; j < 1000 ; j++) {
            map[i][j] = 0;
        }
    }
    while (input_file >> input) {
        temp.clear();
        tokenize(input, ',', temp);
        fromX.push_back(temp[0]);
        fromY.push_back(temp[1]);

        //skip the arrow
        input_file >> input;
        input_file >> input;
        temp.clear();

        tokenize(input, ',', temp);
        toX.push_back(temp[0]);
        toY.push_back(temp[1]);
    }

    int n = toX.size();

    for (int i = 0 ; i < n ; i++) {
        if (fromX[i] == toX[i]) {
            int x = fromX[i];
            //Always start from point with smaller y and increase while iterating
            int yStart = fromY[i] < toY[i] ? fromY[i] : toY[i];
            int yEnd = yStart == fromY[i] ? toY[i] : fromY[i];

            for (int j = yStart ; j <= yEnd ; j++) {
                map[x][j]++;
            }
        } else if (fromY[i] == toY[i]) {
            int y = fromY[i];
            //Always start from point with smaller x and increase while iterating
            int xStart = fromX[i] < toX[i] ? fromX[i] : toX[i];
            int xEnd = xStart == fromX[i] ? toX[i] : fromX[i];

            for (int j = xStart ; j <= xEnd ; j++) {
                map[j][y]++;
            }

        //To compute task one, simply comment out this section of code
        } else if (abs(fromX[i] - toX[i]) == abs(fromY[i] - toY[i])) {
            //Always start from point with smallest x-coordinate
            int xStart = fromX[i] < toX[i] ? fromX[i] : toX[i];
            //adjust other variables accordingly
            int xEnd = xStart == fromX[i] ? toX[i] : fromX[i];
            int yStart = xStart == fromX[i] ? fromY[i] : toY[i];
            int yEnd = xStart == fromX[i] ? toY[i] : fromY[i];

            //check if you have to increase or decrease y in every step
            bool goesUp = yEnd > yStart;

            for (int j = xStart ; j <= xEnd ; j++) {
                map[j][yStart]++;
                yStart += goesUp ? 1 : -1;
            }


        }
    }
    //count entries in the map with one or more intersections
    int counter = 0;
    for (int i = 0 ; i < 1000 ; i++) {
        for (int j = 0 ; j < 1000 ; j++) {
            counter += map[i][j] > 1 ? 1 : 0;
        }
    }
    cout << counter << endl;

    return EXIT_SUCCESS;
}