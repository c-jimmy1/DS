#include <iostream>

int pathcount(int x, int y) {
    if (x == 0 && y == 0) {
        return 1;
    }
    if (x == 0 && y != 0) {
        return pathcount(x , y-1);
    }
    if (y == 0 && x != 0) {
        return pathcount(x-1, y);
    }
    return pathcount(x , y-1) + pathcount(x-1, y);
}

int main() {
    std::cout << pathcount(0,0) << std::endl;
    return 0;
}