#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string toBin(string hex, int n);

void parseBin(string &bin, int &i, int &versionSum);

int main() {
    string filename = "inputPartOne.txt";
    ifstream input_file(filename);

    if(!input_file.is_open()) {
        cout << "Could not open file" << endl;
        return EXIT_FAILURE;
    }
    string input;

    input_file >> input;

    int n = input.size();

    string bin = toBin(input, n);
    n *= 4;
    int i = 0, versionSum = 0;
    //cout << bin << endl;
    parseBin(bin, i, versionSum);

    cout << versionSum << endl;
}

//recursion his dad
void parseBin(string &bin, int &i, int &versionSum) {
    //get version
    int version = stoi(bin.substr(i, 3), nullptr, 2);
    versionSum += version;
    //increase i (which is basically a position pointer for bin)
    i += 3;
    int typeID = stoi(bin.substr(i, 3), nullptr, 2);
    i += 3;
    if (typeID == 4) {
        //packet is a literal
        char c = bin[i];
        string num = "";
        while (c == '1') {
            i++;
            num += bin.substr(i, 4);
            i += 4;
            c = bin[i];
        }
        //increment for the last time when first bit is 0
        i++;
        num += bin.substr(i, 4);
        i += 4;
        //int numDec = stoi(num, nullptr, 2);
    } else {
        //get one bit length type
        char lengthTypeID = bin[i];
        //increment
        i++;
        if (lengthTypeID == '0') {
            //read out total length of subpackets
            int length = stoi(bin.substr(i, 15), nullptr, 2);
            i += 15;
            int curri = i;
            //read subpackets while difference is still smaller than length
            while (i - curri < length) {
                parseBin(bin, i, versionSum);
            }
        } else if(lengthTypeID == '1') {
            int numSubPackets = stoi(bin.substr(i, 11), nullptr, 2);
            i += 11;
            for (int j = 0 ; j < numSubPackets ; j++) {
                parseBin(bin, i, versionSum);
            }
        }
    }

}

string toBin(string hex, int n) {
    string bin = "";
    for (int i = 0 ; i < n ; i++) {
        char c = hex[i];
        if (c == '0') {
            bin += "0000";
        } else if (c == '1') {
            bin += "0001";
        }else if (c == '2') {
            bin += "0010";
        }else if (c == '3') {
            bin += "0011";
        }else if (c == '4') {
            bin += "0100";
        }else if (c == '5') {
            bin += "0101";
        }else if (c == '6') {
            bin += "0110";
        }else if (c == '7') {
            bin += "0111";
        }else if (c == '8') {
            bin += "1000";
        }else if (c == '9') {
            bin += "1001";
        }else if (c == 'A') {
            bin += "1010";
        }else if (c == 'B') {
            bin += "1011";
        }else if (c == 'C') {
            bin += "1100";
        }else if (c == 'D') {
            bin += "1101";
        }else if (c == 'E') {
            bin += "1110";
        }else if (c == 'F') {
            bin += "1111";
        }
    }
    return bin;
}