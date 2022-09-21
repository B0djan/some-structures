#include <iostream>
#include <fstream>
#include <sstream>

#include "frequency_dictionary.h"

int main(int argc, char *argv[]) {
//    if (argc != 2) {
//        return -1;
//    }
//    std::ifstream file(argv[1]);
//    if (!file.is_open()) {
//        return -1;
//    }
//    std::string new_word;
//    frequency_dictionary dictionary;
//    while (file >> new_word)
//        dictionary.insert(new_word);
//    dictionary.print_three_most_popular_words();

//    std::string str;
//    std::cin >> str;
//    std::stringstream ss (str);
//    std::string word;
    frequency_dictionary dictionary;

    dictionary.insert("papa");
    dictionary.erase("papa");
    dictionary.print_three_most_popular_words();
    return 0;
}
