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
bool setAndCheck(int board[5][5], int number) {
    bool won = false;
    for (int i = 0 ; i < 5 ; i++) {
        bool rowWon = true;
        for (int j = 0 ; j < 5 ; j++) {
            //set board entry -1 if the number is on the board
            if (board[i][j] == number) {
                board[i][j] = -1;
            }
            //check if all elements of i-th row are -1, else set rowWon false
            if(board[i][j] != -1) {
                rowWon = false;
            }
        }
        won = rowWon ? true : won;
        
    }
    for (int i = 0 ; i < 5 ; i++) {
            bool colWon = true;
            for (int j = 0 ; j < 5 ; j++) {
                if (board[j][i] != -1) {
                    colWon = false;
                }
            }
            won = colWon ? true : won;
        }
    return won;
    
}
int calcScore(int board[5][5], int lastNum) {
    int sum = 0;
    for (int i = 0 ; i < 5 ; i++) {
        for (int j = 0 ; j < 5 ; j++) {
            sum += (board[i][j] != -1) ? board[i][j] : 0;
        }
    }
    return sum * lastNum;
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
    vector<int> numbers;
    char delim = ',';

    tokenize(input, delim, numbers);
    
    vector<int> winRounds;
    vector<int> scores;

    int board[5][5];
    int nextNum;
    while(input_file >> nextNum) {
        for (int i = 0 ; i < 5 ; i++) {
            for (int j = 0 ; j < 5 ; j++) {
                if(!(i == 0 && j == 0)) {
                    input_file >> nextNum;
                }
                board[i][j] = nextNum;
                //cout << nextNum << " ";
            }
            //cout << endl;
        }
        //cout << endl;
        int currNum;
        //bool didWin = false;
        for (int i = 0 ; i < numbers.size() ; i++) {
            currNum = numbers[i];
            if(setAndCheck(board, currNum)) {
                //didWin = true;
                winRounds.push_back(i + 1);
                break;
            }
        }
        /*if (didWin) {
            scores.push_back(calcScore(board, currNum));
        } else {
            winRounds.push_back(5000);
            scores.push_back(-1);
        }*/
        scores.push_back(calcScore(board, currNum));
    }

    //for task one, simply make this max a min
    int max = 0;
    int index = 0;
    for (int i = 0 ; i < winRounds.size() ; i++) {
        if (winRounds[i] > max) {
            index = i;
            max = winRounds[i];
        }
    }

    cout << scores[index] << endl;

    return EXIT_SUCCESS;
}