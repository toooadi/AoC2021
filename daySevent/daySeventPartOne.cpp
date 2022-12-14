#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int minX = 269;
    int maxX = 292;

    int minY = -68;
    int maxY = -44;

    int res = minY;
    for (int i = 21 ; i < 50 ; i++) {
        for (int j = 0 ; j < 400 ; j++) {
            int currX = 0, currY = 0;
            int XSpeed = i, YSpeed = j;
            bool reachedTarget = false;
            int highestY = 0;

            while(currX <= maxX && currY >= minY) {
                highestY = currY > highestY ? currY : highestY;
                if (minX <= currX && currX <= maxX && minY <= currY && currY <= maxY) {
                    reachedTarget = true;
                }
                currY += YSpeed;
                currX += XSpeed;
                YSpeed--;
                XSpeed -= XSpeed > 0 ? 1 : 0;

            }
            res = (highestY > res && reachedTarget) ? highestY : res;
        }
    }

    cout << res << endl;
}