#include <fstream>
#include <iostream>
//#include <sstring>
#include <string>
using namespace std;

int pow(int base, int exp) {
    int res = 1;
    for (int i = 0 ; i < exp ; i++) {
        res *= base;
    }

    return res;
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
    int n = input.length();

    int ones[n];
    int zeros[n];
    for (int i = 0 ; i < n ; i++) {
        ones[i] = 0;
        zeros[i] = 0;
    }

    do {
        for (int i = 0 ; i < n ; i++) {
            ones[i] += input[i] == '1' ? 1 : 0;
            zeros[i] += input[i] == '1' ? 0 : 1;
        }
    }while(input_file >> input);

    int gamm, eps = 0;

    for (int i = 0 ; i < n ; i++) {
        gamm += ones[n - i - 1] > zeros[n - i - 1] ? pow(2, i) : 0;
        eps += ones[n - i - 1] < zeros[n - i - 1] ? pow(2, i) : 0;
    }
    cout << ones[0] << " " << zeros[0] << endl;
    cout << gamm * eps << endl;

    return EXIT_SUCCESS;
}

