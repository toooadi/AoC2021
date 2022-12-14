#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <utility>
#include <limits>
using namespace std;

void tokenize(string &str, char delim, vector<int> &out) {
    stringstream ss(str);
    string s; 
    while (std::getline(ss, s, delim)) { 
        int put = stoi(s);
        out.push_back(put);
    } 
}

int findIndex(string str, vector<pair<string, pair<string, string>>> rules) {
    for (int i = 0 ; i < rules.size() ; i++) {
        if (rules[i].first == str) {
            return i;
        }
    }
    return -1;
}

int findIndex(char c, vector<pair<char, long long>> occ) {
    for (int i = 0 ; i < occ.size() ; i++) {
        if (occ[i].first == c) {
            return i;
        }
    }
    return -1;
}

int main() {
    string filename = "inputPartOne.txt";
    ifstream input_file(filename);

    if(!input_file.is_open()) {
        cout << "Could not open file" << endl;
        return EXIT_FAILURE;
    }
    string input;

    string start;
    input_file >> start;

    //Vector containing the pairs
    //and the pairs resulting from insertion between them
    vector<pair<string, pair<string, string>>> rules;

    while (input_file >> input) {
        string ruleStart = input;

        //skip arrow
        input_file >> input;
        input_file >> input;

        //first and second string resulting from insertion
        string firstRes, secondRes;
        firstRes.push_back(ruleStart[0]);
        firstRes.push_back(input[0]);

        secondRes.push_back(input[0]);
        secondRes.push_back(ruleStart[1]);

        pair<string, string> results(firstRes, secondRes);
        pair<string, pair<string, string>> elem(ruleStart, results);

        rules.push_back(elem);
    }
    vector<long long> numRules(rules.size(), 0);
    //read in input
    for (int i = 0 ; i < start.size() - 1 ; i++) {
        string str = start.substr(i, 2);
        int searchR = findIndex(str, rules);
        numRules[searchR]++;
    }

    for (int j = 0 ; j < 40 ; j++) {
        vector<long long> newNums(rules.size(), 0);
        for (int i = 0 ; i < rules.size() ; i++) {
            //add new amount of first generated elements
            string str = rules[i].second.first;
            int search = findIndex(str, rules);
            newNums[search] += numRules[i];

            //add new amount of second generated elements
            str = rules[i].second.second;
            search = findIndex(str, rules);
            newNums[search] += numRules[i];
            
        }
        //update number of current rules
        numRules = newNums;

    }

    //count occurences
    vector<pair<char, long long>> occ;
        for (int i = 0 ; i < rules.size() ; i++) {
            //check if char is in occ vector
            int search = findIndex(rules[i].first[0], occ);
            if (search != -1) {
                occ[search].second += numRules[i];
            } else {
                pair newp(rules[i].first[0], numRules[i]);
                occ.push_back(newp);
            }
            search = findIndex(rules[i].first[1], occ);
            if (search != -1) {
                occ[search].second += numRules[i];
            } else {
                pair newp(rules[i].first[1], numRules[i]);
                occ.push_back(newp);
            }
        }

        //first and last element are the only ones only being counted once
        occ[findIndex(start[0], occ)].second++;
        occ[findIndex(start[start.size() - 1], occ)].second++;

        //find max
        long long max = 0;
        long long min = numeric_limits<long long>::max();

        for (int i = 0 ; i < occ.size() ; i++) {
            max = occ[i].second > max ? occ[i].second : max;
            min = occ[i].second < min ? occ[i].second : min;
            cout << occ[i].first << " " << occ[i].second << endl;
        }

        cout << (max / 2) - (min / 2) << endl;



}