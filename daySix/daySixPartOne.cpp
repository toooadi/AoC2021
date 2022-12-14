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
    vector<int> pop;
    input_file >> input;
    tokenize(input, ',', pop);
    long long currDays[9];
    for (int j = 0 ; j < 9 ; j++) {
        currDays[j] = 0;
    }
    for (int i = 0 ; i < pop.size() ; i++) {
        currDays[pop[i]]++;
    }


    for (int j = 0 ; j < 256 ; j++) {
        long long preggo = currDays[0];
        for (int k = 0 ; k < 8 ; k++) {
            currDays[k] = currDays[k + 1];
        }
        currDays[6] = currDays[6] + preggo;
        currDays[8] = preggo;
        
    }
    long long sum = 0;
    for (int j = 0 ; j < 9 ; j++) {
         sum += currDays[j];
     }

    cout << sum << endl;
}