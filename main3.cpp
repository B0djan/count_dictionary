#include "Unordered_map.h"
#include <iostream>

int main() {
    my::unordered_map<int, int> map;
    map[1] = 1;
    map[2] = 2;
    map[3] = 3;
    map[4] = 4;
    map[5] = 5;
    map[6] = 6;
    map[7] = 7;

    map.print();

    return 0;
}