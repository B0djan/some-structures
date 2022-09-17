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
    FrequencyDictionary dictionary;
    std::string new_word;
    while (file >> new_word) {
        dictionary.add_word(new_word);
    }
    return 0;
}
