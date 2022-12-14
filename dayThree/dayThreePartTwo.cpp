#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int pow(int base, int exp) {
    int res = 1;
    for (int i = 0 ; i < exp ; i++) {
        res *= base;
    }

    return res;
}

int main() {
    //open file
    string filename = "inputPartOne.txt";
    ifstream input_file(filename);

    if(!input_file.is_open()) {
        cout << "Could not open file" << endl;
        return EXIT_FAILURE;
    }

    //read first bitstring
    string input;
    input_file >> input;
    int n = input.length();

    vector<string> bins;
    int ones;
    int zeros;

    do {
        bins.push_back(input);
    }while(input_file >> input);

    vector<string> currMore(bins);
    vector<string> currLess(bins);
    vector<string> selecMore, selecLess;
    int currBit = 0;
    ones, zeros = 0;

    //find oxygen generator rating
    while(currMore.size() > 1) {
        for (int i = 0 ; i < currMore.size() ; i++) {
            //count number of 1's and 0's in currently examined position
            ones += currMore[i][currBit] == '1' ? 1 : 0;
            zeros += currMore[i][currBit] == '1' ? 0 : 1;
        }

        //check dominant bit
        bool moreOnes = ones >= zeros;
        for (int i = 0 ; i < currMore.size() ; i++) {
            if (moreOnes && currMore[i][currBit] == '1') {
                //if 1 is dominant bit, check if string has 1 in current position
                selecMore.push_back(currMore[i]);
            } else if(!moreOnes && currMore[i][currBit] == '0') {
                //if 0 is dominant bit, check if string has 0 in current position
                selecMore.push_back(currMore[i]);
            }
        }
        ones = 0;
        zeros = 0;
        currBit++;
        currMore = selecMore;
        selecMore.clear();
    }
    currBit = 0;

    //same procedure as above but for CO2 scrubber rating
    while(currLess.size() > 1) {
        for (int i = 0 ; i < currLess.size() ; i++) {
            ones += currLess[i][currBit] == '1' ? 1 : 0;
            zeros += currLess[i][currBit] == '1' ? 0 : 1;
        }
        bool lessOnes = ones < zeros;
        for (int i = 0 ; i < currLess.size() ; i++) {
            if (lessOnes && currLess[i][currBit] == '1') {
                selecLess.push_back(currLess[i]);
            } else if(!lessOnes && currLess[i][currBit] == '0') {
                selecLess.push_back(currLess[i]);
            }
        }
        currBit++;
        ones = 0;
        zeros = 0;
        currLess = selecLess;
        selecLess.clear();
    }
    //cout << selecLess[0] << " " << selecMore[0] << endl;
    int numOne = 0;
    int numTwo = 0;
    //convert binary numbers to decimal
    for (int i = 0 ; i < n ; i++) {
        numOne += selecMore[0][n - i - 1] == '1' ? pow(2, i) : 0;
        numTwo += selecLess[0][n - i - 1] == '1' ? pow(2, i) : 0;
    }
    cout << numTwo * numOne << endl;
    return EXIT_SUCCESS;
}

