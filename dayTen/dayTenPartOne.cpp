#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;
int main() {
    //First, read input
    string filename = "inputPartOne.txt";
    ifstream input_file(filename);

    if(!input_file.is_open()) {
        cout << "Could not open file" << endl;
        return EXIT_FAILURE;
    }

    string input;
    int sum = 0;
    vector<long long> rems;
    while(input_file >> input) {
        stack<char> stack;
        bool corr = false;
        //Part one
        for (int i = 0 ; i < input.size() ; i++) {
            char c = input[i];
            if (c == '[' || c == '{' || c == '(' || c == '<') {
                stack.push(c);
            } else {
                char p = stack.top();
                if (!((p == '(' && c == ')') || (p == '[' && c == ']') || (p == '{' && c == '}') || (p == '<' && c == '>'))) {
                    corr = true;
                    if (c == ')') {
                        sum += 3;
                        break;
                    } else if (c == ']') {
                        sum += 57;
                        break;
                    } else if (c == '}') {
                        sum += 1197;
                        break;
                    } else {
                        sum += 25137;
                        break;
                    }
                }
                stack.pop();
            }
        }

        //Part two
        if (!corr) {
            long long closers = 0;
            while (stack.size() > 0) {
                closers *= 5;
                char p = stack.top();
                if (p == '(') {
                    closers += 1;
                } else if (p == '[') {
                    closers += 2;
                } else if (p == '{') {
                    closers += 3;
                } else {
                    closers += 4;
                }
                stack.pop();
            }
            rems.push_back(closers);
        }
    }

    cout << sum << endl;
    sort(rems.begin(), rems.end());
    cout << rems[rems.size() / 2] << endl;

}