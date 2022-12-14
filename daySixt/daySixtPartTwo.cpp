#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <limits>

using namespace std;

//parse binary string from hex string
string toBin(string hex, int n);

//evaluate expression given by the hex string
long long parseBin(string &bin, int &i, int &versionSum);

//find minimum of a vector
long long min_element(vector<long long> vec) {
    int n = vec.size();
    long long min = numeric_limits<long long>::max();
    for (int i = 0 ; i < n ; i++) {
        min = vec[i] < min ? vec[i] : min;
    }
    return min;
}

//find maximum of a vector
long long max_element(vector<long long> vec) {
    int n = vec.size();
    long long max = numeric_limits<long long>::min();
    for (int i = 0 ; i < n ; i++) {
        max = vec[i] > max ? vec[i] : max;
    }
    return max;
}

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

    cout << parseBin(bin, i, versionSum) << endl;
}

//evaluate expression given by hex string
long long parseBin(string &bin, int &i, int &versionSum) {
    //get version
    int version = stoi(bin.substr(i, 3), nullptr, 2);
    versionSum += version;
    //increase i (which is basically a position pointer for bin)
    i += 3;
    int typeID = stoi(bin.substr(i, 3), nullptr, 2);
    i += 3;
    //packet is a literal
    if (typeID == 4) {
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
        return stoll(num, nullptr, 2);
    } else {
        //declare vector for numbers in subpackets
        vector<long long> nums;
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
                nums.push_back(parseBin(bin, i, versionSum));
            }
        } else if(lengthTypeID == '1') {
            int numSubPackets = stoi(bin.substr(i, 11), nullptr, 2);
            i += 11;
            //since we have a fixed amount of packets,
            //we can use a for loop
            for (int j = 0 ; j < numSubPackets ; j++) {
                nums.push_back(parseBin(bin, i, versionSum));
            }
        }
        //apply operation
        if (typeID == 0) {
            return accumulate(nums.begin(), nums.end(), 0ll);
        } else if (typeID == 1) {
            return accumulate(nums.begin(), nums.end(), 1ll, multiplies<long long>{});
        } else if (typeID == 2) {
            return min_element(nums);
        } else if (typeID == 3) {
            return max_element(nums);
        } else if (typeID == 5) {
            return nums[0] > nums[1];
        } else if (typeID == 6) {
            return nums[0] < nums[1];
        } else {
            return nums[0] == nums[1];
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