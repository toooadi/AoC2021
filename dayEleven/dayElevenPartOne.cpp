#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;
bool wasSync(bool flashed[10][10]) {
    bool sync = true;
    for (int i = 0 ; i < 10 ; i++) {
        for (int j = 0 ; j < 10 ; j++) {
            sync = flashed[i][j] ? sync : false;
        }
    }
    return sync;
}
void resetFlashed(bool flashed[10][10]) {
    for (int i = 0 ; i < 10 ; i++) {
        for (int j = 0 ; j < 10 ; j++) {
            flashed[i][j] = false;
        }
    }
}

int UpdateTables(int squids[10][10] , bool flashed[10][10], bool isFirst, bool &didFlash) {
    int numFlashes = 0;
    for (int i = 0 ; i < 10 ; i++) {
        for (int j = 0 ; j < 10 ; j++) {
            //Add 1 without adjacent flash only on first update (+1 from step recharge)
            squids[i][j] += isFirst ? 1 : 0;
            
            //Flash if greater than 9
            if (squids[i][j] > 9) {
                //confirm that the board has changed
                didFlash = true;
                //Add 1 flash
                numFlashes++;
                //confirm the squid has flashed
                flashed[i][j] = true;
                //set squids energy to 0 again
                squids[i][j] = 0;

                if (i != 0) {
                    //Only add if indexing is correct and adjacent squid hasn't yet flashed
                    squids[i - 1][j]+= flashed[i - 1][j] ? 0 : 1;
                    if (j != 0) {
                        squids[i - 1][j - 1] += flashed[i - 1][j - 1] ? 0 : 1;
                    }
                    if (j != 9) {
                        squids[i - 1][j + 1] += flashed[i - 1][j + 1] ? 0 : 1;
                    }
                }
                if (i != 9) {
                    squids[i + 1][j] += flashed[i + 1][j] ? 0 : 1; 
                    if (j != 0) {
                        squids[i + 1][j - 1] += flashed[i + 1][j - 1] ? 0 : 1;
                    }
                    if (j != 9) {
                        squids[i + 1][j + 1] += flashed[i + 1][j + 1] ? 0 : 1;
                    }
                }
                if (j != 0) {
                    squids[i][j - 1] += flashed[i][j - 1] ? 0 : 1;
                }
                if (j != 9) {
                    squids[i][j + 1] += flashed[i][j + 1] ? 0 : 1;
                }
            }
        }
    }
    return numFlashes;
}
int main() {
    string filename = "inputPartOne.txt";
    ifstream input_file(filename);

    if(!input_file.is_open()) {
        cout << "Could not open file" << endl;
        return EXIT_FAILURE;
    }
    string input;

    int squids[10][10];
    int row = 0;
    while (input_file >> input) {
        for (int i = 0 ; i < 10 ; i++) {
            string conv = "";
            conv.push_back(input[i]);
            squids[row][i] = stoi(conv);
        }
        row++;
    }
    
    //Part one And two
    int flashes = 0;
    bool flashed[10][10];
    bool didFlash = false;

    //Variables for part two
    bool isSync = false;
    int numRounds = 0;
    for (int i = 0 ; i < 100 ; i++) {
        //Only add if not yet synchronised to find first synchronized round
        numRounds += !isSync ? 1 : 0;
        resetFlashed(flashed);
        flashes += UpdateTables(squids, flashed, true, didFlash);

        while(didFlash) {
            didFlash = false;
            flashes += UpdateTables(squids, flashed, false, didFlash);
        }
        isSync = wasSync(flashed) ? true : isSync;

    }

    //Part two if it isn't during the execution of part one
    while(!isSync) {
        numRounds++;
        resetFlashed(flashed);
        UpdateTables(squids, flashed, true, didFlash);

        while(didFlash) {
            didFlash = false;
            flashes += UpdateTables(squids, flashed, false, didFlash);
        }
        isSync = wasSync(flashed) ? true : isSync;

    }

    cout << flashes << endl;
    cout << numRounds << endl;

    return EXIT_SUCCESS;

}