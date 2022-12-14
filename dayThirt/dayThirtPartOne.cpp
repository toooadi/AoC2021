#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <utility>
#include <set>
using namespace std;

void tokenize(string &str, char delim, vector<int> &out) {
    stringstream ss(str);
    string s; 
    while (std::getline(ss, s, delim)) { 
        int put = stoi(s);
        out.push_back(put);
    } 
}
void tokenize(string &str, char delim, vector<string> &out) {
    stringstream ss(str);
    string s; 
    while (std::getline(ss, s, delim)) { 
        //int put = stoi(s);
        out.push_back(s);
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
    set<pair<int, int>> coords;
    vector<pair<string, int>> folds;

    while (input_file >> input) {
        vector<int> temp;
        if(input != "fold") {
            tokenize(input, ',', temp);
            pair one(temp[0], temp[1]);
            coords.insert(one);
        } else {
            //skip to relevant information
            input_file >> input;
            input_file >> input;
            vector<string> temp;
            tokenize(input, '=', temp);
            pair one(temp[0], stoi(temp[1]));
            folds.push_back(one);
        }
    }
    set<pair<int, int>>::iterator itr;
    set<pair<int, int>> smallerSet;
    int foldc = folds[0].second;
    if (folds[0].first == "x") {
        for (itr = coords.begin() ; itr != coords.end() ; itr++) {
            pair<int, int> check = *itr;
            if (check.first > foldc) {
                check.first = check.first - 2 * (check.first - foldc);
            }
            smallerSet.insert(check);
        }
    } else {
        for (itr = coords.begin() ; itr != coords.end() ; itr++) {
            pair<int, int> check = *itr;
            if (check.second > foldc) {
                check.second = check.second - 2 * (check.second - foldc);
            }
            smallerSet.insert(check);
        }
    }
    
    cout << smallerSet.size() << endl;

}