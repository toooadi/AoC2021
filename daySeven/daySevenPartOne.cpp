#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
#include <cmath>
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
    vector<int> pos;
    input_file >> input;
    tokenize(input, ',', pos);
    int n = pos.size();
    int max = 0;
    for (int i = 0 ; i < n ; i++) {
        max = pos[i] > max ? pos[i] : max;
    }
    int dist[max];

    //Part One
    for (int i = 0 ; i < max ; i++) {
        dist[i] = 0;
        for (int j = 0 ; j < n ; j++) {
            dist[i] += std::abs(i - pos[j]);
        }
    }
    int min = std::numeric_limits<int>::max();

    for (int i = 0 ; i < max ; i++) {
        min = dist[i] < min ? dist[i] : min;
    }

    cout << "Part One: " <<  min << endl;
    //Part Two
    int res = 0;
    for (int i = 0 ; i < max ; i++) {
        dist[i] = 0;
        for (int j = 0 ; j < n ; j++) {
            int diff = std::abs(pos[j] - i);
            int ds = diff * diff;
            dist[i] += (ds + diff) / 2;
        }
    }

    min = std::numeric_limits<int>::max();

    for (int i = 0 ; i < max ; i++) {
        min = dist[i] < min ? dist[i] : min;
    }

    cout << "Part Two: " << min << endl;



}