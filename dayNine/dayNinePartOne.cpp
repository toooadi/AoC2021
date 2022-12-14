#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;
int basinSize(int i, int j, int prev, bool **low, int **field, int n, int m);

int main() {

    //First, read input
    string filename = "inputPartOne.txt";
    ifstream input_file(filename);

    if(!input_file.is_open()) {
        cout << "Could not open file" << endl;
        return EXIT_FAILURE;
    }
    string input;
    vector<string> in;
    while (input_file >> input) {
        in.push_back(input);
    }
    int n = in.size();
    int m = in[0].size();

    int **field = new int*[n];
    for(int i = 0; i < n; i++) {
        field[i] = new int[m];
    }

    for (int i = 0 ; i < n ; i++) {
        for (int j = 0 ; j < m ; j++) {
            string s = "";
            s.push_back(in[i][j]);
            field[i][j] = stoi(s);
        }
    }

    //start Task One
    bool **lowPoints = new bool*[n];
    for (int i = 0 ; i < n ; i++) {
        lowPoints[i] = new bool[m];
    }

    //First, find low points
    for (int i = 0 ; i < n ; i++) {
        for (int j = 0 ; j < m ; j++) {
            bool isRisk = true;
            if (j > 0 && field[i][j - 1] <= field[i][j]) {
                isRisk = false;
            }
            if (i > 0 && field[i - 1][j] <= field[i][j]) {
                isRisk = false;
            }
            if (j < (m - 1) && field[i][j + 1] <= field[i][j]) {
                isRisk = false;
            }
            if (i < (n - 1) && field[i + 1][j] <= field[i][j]) {
                isRisk = false;
            }
            lowPoints[i][j] = isRisk;
        }
    }
    //Add up risk points
    int sum = 0;
    for (int i = 0 ; i < n ; i++) {
        for (int j = 0 ; j < m ; j++) {
            if (lowPoints[i][j]) {
                sum += field[i][j] + 1;
            }
        }
    }

    cout << sum << endl;

    //Part two, check recursively for basins
    //first create copy of boolean array in order to prevent double checking
    bool **lowCopy = new bool*[n];
    for (int i = 0 ; i < n ; i++) {
        lowCopy[i] = new bool[m];
        for (int j = 0 ; j < m ; j++) {
            lowCopy[i][j] = false;
        }
    }
    int first = 0, second = 0, third = 0;

    for (int i = 0 ; i < n ; i++) {
        for (int j = 0 ; j < m ; j++) {
            if (lowPoints[i][j]) {
                int bs = basinSize(i, j, -1, lowCopy, field, n, m);
                if (bs > first) {
                    int temp = first;
                    first = bs;
                    third = second;
                    second = temp;
                } else if (bs > second) {
                    third = second;
                    second = bs;
                } else if (bs > third) {
                    third = bs;
                }
            }
        }
    }

    int prod = first * second * third;
    cout << prod << endl;
}

int basinSize(int i, int j, int prev, bool **low, int **field, int n, int m) {
    if (i < 0 || j < 0 || i >= n || j >= m || field[i][j] <= prev || field[i][j] == 9 || low[i][j]) {
        return 0;
    }
    low[i][j] = true;
    int newpre = field[i][j];
    return 1 + basinSize(i + 1, j, newpre, low, field, n, m) + basinSize(i - 1, j, newpre, low, field, n, m)
            + basinSize(i, j + 1, newpre, low, field, n, m) + basinSize(i, j - 1, newpre, low, field, n, m);

}