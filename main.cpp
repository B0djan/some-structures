#include <iostream>
#include <fstream>

#include "FrequencyDictionary.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return -1;
    }
    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        return -1;
    }
    std::string new_word;
    FrequencyDictionary dictionary;
    while (file >> new_word)
        dictionary.add_word(new_word);
    dictionary.printThreeMostPopularWords();
    return 0;
}
