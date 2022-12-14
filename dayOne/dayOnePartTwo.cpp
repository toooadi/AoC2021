#include <fstream>
#include <iostream>
using namespace std;

int main() {
    string filename = "inputDayOnePartTwo.txt";
    ifstream input_file(filename);

    if(!input_file.is_open()) {
        cout << "Could not open file" << endl;
        return EXIT_FAILURE;
    }

    int firstSum, secondSum, thirdSum = 0;
    int num;
    int counter = 0;

    input_file >> thirdSum;
    input_file >> secondSum;
    input_file >> firstSum;

    thirdSum += secondSum + firstSum;
    secondSum += firstSum;

    while(input_file >> num) {
        int newSum = secondSum + num;
        counter += newSum > thirdSum ? 1 : 0;

        thirdSum = newSum;
        secondSum = firstSum + num;
        firstSum = num;
    }

    cout << counter << endl;
}