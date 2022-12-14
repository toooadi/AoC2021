#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int minX = 244;
    int maxX = 303;

    int minY = -91;
    int maxY = -54;

    int res = 0;
    for (int i = 18 ; i <= 303 ; i++) {
        for (int j = -91 ; j < 1000 ; j++) {
            int currX = 0, currY = 0;
            int XSpeed = i, YSpeed = j;
            bool reachedTarget = false;

            while(currX <= maxX && currY >= minY) {
                if (minX <= currX && currX <= maxX && minY <= currY && currY <= maxY) {
                    reachedTarget = true;
                }
                currY += YSpeed;
                currX += XSpeed;
                YSpeed--;
                XSpeed -= XSpeed > 0 ? 1 : 0;

            }
            res += reachedTarget ? 1 : 0;
        }
    }

    cout << res << endl;
}