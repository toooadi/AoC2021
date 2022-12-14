#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <chrono>
using namespace std;
bool containsChar(string s, char c) {
    bool res = false;
    for (int i = 0 ; i < s.size() ; i++) {
        res = s[i] == c ? true : res;
    }
    return res;
}
int numMatches(string s, string t) {
    int count = 0;
    for (int i = 0 ; i < s.size() ; i++) {
        for (int j = 0 ; j < t.size() ; j++) {
            count += s[i] == t[j] ? 1 : 0;
        }
    }
    return count;
}
vector<char> getMatches(string s, string t) {
    vector<char> res;
    for (int i = 0 ; i < s.size() ; i++) {
        for (int j = 0 ; j < t.size() ; j++) {
            if (s[i] == t[j]) {
                res.push_back(s[i]);
            }
        }
    }
    return res;
}
int main() {
    chrono::time_point start = chrono::high_resolution_clock::now();
    string filename = "inputPartOne.txt";
    ifstream input_file(filename);

    if(!input_file.is_open()) {
        cout << "Could not open file" << endl;
        return EXIT_FAILURE;
    }
    string input;
    vector<vector<string>> signals;
    vector<vector<string>> outputs;
    int index = 0;
    while(input_file >> input) {
        vector<string> temps;
        signals.push_back(temps);
        vector<string> tempo;
        outputs.push_back(tempo);
        signals[index].push_back(input);
        
        for(int i = 0 ; i < 9 ; i++) {
            input_file >> input;
            signals[index].push_back(input);
        }
        //skip |
        input_file >> input;

        for (int i = 0 ; i < 4 ; i++) {
            input_file >> input;
            outputs[index].push_back(input);
        }
        index++;
    }

    //index is now input size
    //Part one
    int count = 0;
    for (int i = 0 ; i < index ; i++) {
        for (int j = 0 ; j < 4 ; j++) {
            int s = outputs[i][j].size();
            if (s == 2 || s == 3 || s == 4 || s == 7) {
                count++;
            }
        }
    }
    cout << count << endl;

    //Part two, gonna be ugly
    
    
    int res = 0;
    for (int i = 0 ; i < index ; i++) {
        string zero, one, two, three, four, five, six, seven, eight, nine;
        char top, topleft, topright, middle, lowleft, lowright, low;
        for (int j = 0 ; j < 10 ; j++) {
            one = signals[i][j].size() == 2 ? signals[i][j] : one;
            four = signals[i][j].size() == 4 ? signals[i][j] : four;
            seven = signals[i][j].size() == 3 ? signals[i][j] : seven;
            eight = signals[i][j].size() == 7 ? signals[i][j] : eight;
        }
        //find out top
        /*for (int j = 0 ; j < 3 ; j++) {
            top = !containsChar(one, seven[j]) ? seven[j] : top;
        }*/

        //find out lowRight
        for (int j = 0 ; j < 10 ; j++) {
            if (signals[i][j].size() == 6 && numMatches(signals[i][j], one) == 1) {
                six = signals[i][j];
                for (int k = 0 ; k < 6 ; k++) {
                    lowright = signals[i][j][k] == one[0] ? one[0] : lowright;
                    lowright = signals[i][j][k] == one[1] ? one[1] : lowright;
                }
            }
        }

        //deduce topRight
        topright = lowright == one[0] ? one[1] : one[0];

        //deduce topLeft
        for (int j = 0 ; j < 10 ; j++) {
            if (signals[i][j].size() == 6 && six.compare(signals[i][j]) != 0 && numMatches(signals[i][j], four) == 3) {
                zero = signals[i][j];
                vector<char> matches = getMatches(zero, four);
                for (int k = 0 ; k < 3 ; k++) {
                    if (matches[k] != lowright && matches[k] != topright) {
                        topleft = matches[k];
                    }
                }
            }
        }

        //deduce middle
        for (int j = 0 ; j < 4 ; j++) {
            char c = four[j];
            if (c != topleft && c != topright && c != lowright) {
                middle = c;
            }
        }

        //deduce bottom
        /*for (int j = 0 ; j < 10 ; j++) {
            string s = signals[i][j];
            if(s.size() == 6 && s.compare(zero) != 0 && s.compare(six) != 0) {
                nine = s;
                vector<char> matches = getMatches(nine, zero);
                for (int k = 0 ; k < 5 ; k++) {
                    char c = matches[k];
                    if (c != topleft && c != topright && c != top && c != lowright) {
                        low = c;
                    }
                }
            }
        }*/
        
        //deduce lowleft
        /*vector<char> nematches = getMatches(nine, eight);
        for (int j = 0 ; j < 7 ; j++) {
            bool contained = false;
            for (int k = 0 ; k < 6 ; k++) {
                contained = eight[j] == nematches[k] ? true : contained;
            }
            lowleft = !contained ? eight[j] : lowleft;
        }*/

        //now the char variables contain all the correct positions
        //and we can look at the output
        //poop fart shit cum diarrhea
        int tempres = 0;
        for (int j = 0 ; j < 4 ; j++) {
            tempres *= 10;
            int seg;
            string num = outputs[i][j];
            int size = num.size();
            if (size == 2) {
                seg = 1;
            } else if (size == 3) {
                seg = 7;
            } else if (size == 4) {
                seg = 4;
            } else if (size == 7) {
                seg = 8;
            } else if (size == 5) {
                if (!containsChar(num, topright)) {
                    seg = 5;
                } else if (!containsChar(num, lowright)) {
                    seg = 2;
                } else {
                    seg = 3;
                }
            } else {
                if (!containsChar(num, middle)) {
                    seg = 0;
                } else if (!containsChar(num, topright)) {
                    seg = 6;
                } else {
                    seg = 9;
                }
            }
            tempres += seg;
        }
        res += tempres;
    }
    
    cout << res << endl;
    chrono::time_point end = chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    cout << "Elapsed time: " << elapsed.count() << " s" << endl;
}