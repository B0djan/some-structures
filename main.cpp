#include <iostream>
#include <fstream>

#include "FrequencyDictionary.h"
#include "UnorderedMap.h"

int main(int argc, char *argv[]) {
//    if (argc != 2) {
//        return -1;
//    }
//    std::ifstream file(argv[1]);
//    if (!file.is_open()) {
//        return -1;
//    }


//    FrequencyDictionary dictionary;
//    int n;
//    std::cin >> n;
//    for (int i = 0; i < n; ++i) {
//        std::string new_word;
//        std::cin >> new_word;
//        dictionary.add_word(new_word);
//    }
//    dictionary.printThreeMostPopularWords();

    UnorderedMap<int, List<std::string>> map;
    auto& list = map[1];
    std::cout << list.empty() << std::endl;

    return 0;
}
