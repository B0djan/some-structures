#include <iostream>

#include "UnorderedMap.h"

int main(int argc, char *argv[]) {
    UnorderedMap<int, int> map;
    map.insert(1, 1);
    map.insert(2, 2);
    map.insert(3, 3);
    for (const auto& p : map)
        std::cout << p.getFirst() << ' ' << p.getSecond() << '\n';
    std::cout << map.contained(1) << '\n';
    std::cout << map.contained(0) << '\n';
    return 0;
}
