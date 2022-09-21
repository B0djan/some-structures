#ifndef FREQUENCY_DICTIONARY_H
#define FREQUENCY_DICTIONARY_H

#include "unordered_map.h"

class frequency_dictionary {
private:
    unordered_map<std::string, int> _string_to_number;
    unordered_map<int, list<std::string>> _number_to_string;
    std::string* _free_most_popular_words;

    const char* punctuation_marks = ".,!?:";

    static void update_number_of_copies(int i, int& pos1, int& pos2, int& pos3);

    bool parse_word(const std::string& str, std::string& parsed_word) {
        if (str.empty())
            return false;
        int end_offset = 0;
        bool punctuation = true;
        for (int i = (int)str.size() - 1; i >= 0 && punctuation; i--, end_offset++) {
            punctuation = false;
            for (const char* ptr = punctuation_marks; *ptr; ptr++)
                punctuation = punctuation || (*ptr == str[i]);
        }
        for (int i = 0; i < (int)str.size() - end_offset; ++i) {
            auto symbol = (char)tolower(str[i]);
            if (!(symbol >= 'a' && symbol <= 'z'))
                return false;
        }
        parsed_word = std::string(str.begin(), str.end()-end_offset + 1);
        return true;
    }

    void fill();
public:
    explicit frequency_dictionary() {
        _free_most_popular_words = new std::string[3];
    }

    ~frequency_dictionary() {
        delete[] _free_most_popular_words;
    }

    void insert(const std::string& word) {
        std::string parsed_word;
        if (parse_word(word, parsed_word))
            _string_to_number[parsed_word] += 1;
    }

    void insert(const std::string& word, int value) {
        std::string parsed_word;
        if (parse_word(word, parsed_word))
            _string_to_number[parsed_word] += value;
    }

    int search(const std::string& word) {
        std::string parsed_word;
        if (!parse_word(word, parsed_word))
            return -1;
        return _string_to_number[parsed_word];
    }

    void erase(const std::string& word) {
        _string_to_number.erase(word);
    }


    void print_three_most_popular_words();
};

void frequency_dictionary::fill() {
    int positions[3];
    for (int & position : positions)
        position = 0;

    for (const auto& p : _string_to_number) {
        auto idx = p.second();
        _number_to_string[idx].push_back(p.first());
        update_number_of_copies(idx, positions[0], positions[1], positions[2]);
    }

    int i = 0;
    for (int j = 0; j < 3 && i < 3; ++j)
        for (const auto& word: _number_to_string[positions[j]]) {
            if (i >= 3)
                return;
            _free_most_popular_words[i] = word;
            i += 1;
        }
}

void frequency_dictionary::update_number_of_copies(int i, int& pos1, int& pos2, int& pos3) {
    if (i <= pos1) {
        return;
    }
    if (i <= pos2) {
        pos3 = i;
        return;
    }
    if (i <= pos1) {
        pos3 = pos2;
        pos2 = i;
        return;
    }
    pos3 = pos2;
    pos2 = pos1;
    pos1 = i;
}

void frequency_dictionary::print_three_most_popular_words() {
    fill();
    for (int i = 0; i < 3; ++i) {
        if (_free_most_popular_words[i].empty())
            return;
        std::cout << _free_most_popular_words[i] << ' ';
    }
    std::cout << '\n';
}

#endif //  FREQUENCY_DICTIONARY_H
