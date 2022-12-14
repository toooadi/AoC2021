#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

char addtoChar(int a, int b);

int charToInt(char c);

string parseList(string input) {
    string vec = "";
    for (int i = 0 ; i < input.size() ; i++) {
        if (input[i] != ',') {
            vec.push_back(input[i]);
        }
    }
    return vec;
}

bool explode(string &num) {
    int i = 0;
    int levelcount = 0;
    bool exploded = false;
    while (i < num.size()) {
        levelcount += num[i] == '[' ? 1 : 0;
        levelcount -= num[i] == ']' ? 1 : 0;
        if (levelcount > 4) {
            //confirm a number has exploded
            exploded = true;
            //get first and second number of explosive number
            int first = charToInt(num[i + 1]);
            int second = charToInt(num[i + 2]);
            //add to the number on the left
            int j = i - 1;
            while(j > 0 && (num[j] == '[' || num[j] == ']')) {
                j--;
            }
            if (j > 0) {
                int change = charToInt(num[j]);
                num[j] = addtoChar(change, first);
            }

            //add to the number on the right;
            j = i + 4;
            while (j < num.size() && (num[j] == '[' || num[j] == ']')) {
                j++;
            }
            if (j < num.size()) {
                int change = charToInt(num[j]);
                num[j] = addtoChar(change, second);
            }

            //generate new number
            string subOne = num.substr(0, i);
            string subTwo = num.substr(i + 4, string::npos);
            num = subOne + '0' + subTwo;
            //decrease levelcount since we now deleted one level
            levelcount--;

            //after this block i points to the position of the 0 which
            //is in the place of the exploded number
        }

        i++;
    }
    return exploded;
}

bool split(string &num) {
    for (int i = 0 ; i < num.size() ; i++) {
        if (num[i] != '[' && num[i] != ']' && charToInt(num[i]) > 9) {
            //find first and second substring
            string subOne = num.substr(0, i);
            string subTwo = num.substr(i + 1, string::npos);

            int temp = charToInt(num[i]);
            char first = addtoChar(temp / 2, 0);
            //check if the number is odd
            temp += (temp % 2) == 1 ? 1 : 0;
            char second = addtoChar(temp / 2 , 0);
            //update number
            num = subOne + '[' + first + second + ']' + subTwo;
            //exit method
            return true;

        }
    }
    return false;
}
int calcMagnitude(int &i, string &num) {
    int first, second;
    if (num[i + 1] != '[') {
        first = charToInt(num[i + 1]);
    } else {
        i++;
        first = calcMagnitude(i, num);
    }
    i++;
    if (num[i + 1] != '[') {
        second = charToInt(num[i + 1]);
    } else {
        i++;
        second = calcMagnitude(i, num);
    }
    i++;
    return 3 * first + 2 * second;
    
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

    string num = parseList(input);

    while(input_file >> input) {
        string temp = parseList(input);
        num = '[' + num + temp + ']';
        //operate as long as necessary
        while(explode(num) || split(num)) {
            split(num);
        }
        
    }
    int i = 0;
    cout << calcMagnitude(i, num) << endl;

    return EXIT_SUCCESS;
}

char addtoChar(int a, int b) {
    int sum = a + b;
    switch(sum) {
        case 0:
            return '0';
        case 1:
            return '1';
        case 2:
            return '2';
        case 3:
            return '3';
        case 4:
            return '4';
        case 5:
            return '5';
        case 6:
            return '6';
        case 7:
            return '7';
        case 8:
            return '8';
        case 9:
            return '9';
        case 10:
            return 'A';
        case 11:
            return 'B';
        case 12:
            return 'C';
        case 13:
            return 'D';
        case 14:
            return 'E';
        case 15:
            return 'F';
        case 16:
            return 'G';
        case 17:
            return 'H';
        case 18:
            return 'I';
        case 19:
            return 'J';
        case 20:
            return 'K';
        case 21:
            return 'L';
        case 22:
            return 'M';
        case 23:
            return 'N';
        case 24:
            return 'O';
        case 25:
            return 'P';
        case 26:
            return 'Q';
        case 27:
            return 'R';
        case 28:
            return 'S';
        case 29:
            return 'T';
        case 30:
            return 'U';
        case 31:
            return 'V';
        case 32:
            return 'W';
        case 33:
            return 'X';
        case 34:
            return 'Y';
        case 35:
            return 'Z';
        case 36:
            return 'a';
        case 37:
            return 'b';
        case 38:
            return 'c';
        case 39:
            return 'd';
        case 40:
            return 'e';
        case 41:
            return 'f';
        case 42:
            return 'g';
        case 43:
            return 'h';
        case 44:
            return 'i';
        case 45:
            return 'j';
        case 46:
            return 'k';
        case 47:
            return 'l';
        case 48:
            return 'm';
        case 49:
            return 'n';
        case 50:
            return 'o';
        case 51:
            return 'p';
        case 52:
            return 'q';
        case 53:
            return 'r';
        case 54:
            return 's';
        case 55:
            return 't';
        case 56:
            return 'u';
        case 57:
            return 'v';
        default:
            cout << "fuck" << endl;
            return 'w';
        
    }
}

int charToInt(char c) {
    switch(c) {
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        case 'A':
            return 10;
        case 'B':
            return 11;
        case 'C':
            return 12;
        case 'D':
            return 13;
        case 'E':
            return 14;
        case 'F':
            return 15;
        case 'G':
            return 16;
        case 'H':
            return 17;
        case 'I':
            return 18;
        case 'J':
            return 19;
        case 'K':
            return 20;
        case 'L':
            return 21;
        case 'M':
            return 22;
        case 'N':
            return 23;
        case 'O':
            return 24;
        case 'P':
            return 25;
        case 'Q':
            return 26;
        case 'R':
            return 27;
        case 'T':
            return 28;
        case 'U':
            return 29;
        case 'V':
            return 30;
        case 'W':
            return 31;
        case 'X':
            return 32;
        case 'Y':
            return 33;
        case 'Z':
            return 34;
        case 'a':
            return 35;
        case 'b':
            return 36;
        case 'c':
            return 37;
        case 'd':
            return 38;
        case 'e':
            return 39;
        case 'f':
            return 40;
        case 'g':
            return 41;
        case 'h':
            return 42;
        case 'i':
            return 43;
        case 'j':
            return 44;
        case 'k':
            return 45;
        case 'l':
            return 46;
        case 'm':
            return 47;
        case 'n':
            return 48;
        case 'o':
            return 49;
        case 'p':
            return 50;
        case 'q':
            return 51;
        case 'r':
            return 52;
        case 's':
            return 53;
        case 't':
            return 54;
        case 'u':
            return 55;
        case 'v':
            return 56;
        case 'w':
            return 57;
        default:
            return 58;
        
        
    }
}