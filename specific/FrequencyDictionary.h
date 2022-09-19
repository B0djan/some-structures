#ifndef _FREQUENCYDICTIONARY_H
#define _FREQUENCYDICTIONARY_H

#include "list.h"
#include "unordered_map.h"

class FrequencyDictionary {

private:
    unordered_map<std::string, int> string_to_number;
    unordered_map<int, list<std::string>> number_to_string;
    std::string* free_most_popular_words;

    static void updateNumberOfCopies(int i, int& pos1, int& pos2, int& pos3) {
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

    void fill() {
        int positions[3];
        for (int & position : positions)
            position = 0;

        for (const auto& p : string_to_number) {
            auto idx = p->getSecond();
            number_to_string[idx].push_back(p->getFirst());
            updateNumberOfCopies(idx, positions[0], positions[1], positions[2]);
        }

        int i = 0;
        for (int j = 0; j < 3 && i < 3; ++j)
            for (const auto& word: number_to_string[positions[j]]) {
                if (i >= 3) { return; }
                free_most_popular_words[i] = word;
                i += 1;
            }
    }
public:
    explicit FrequencyDictionary() {
        free_most_popular_words = new std::string[3];
    }

    ~FrequencyDictionary() { delete[] free_most_popular_words; }

    void add_word(const std::string& word) {
        string_to_number[word] += 1;
    }

    void printThreeMostPopularWords() {
        fill();
        for (int i = 0; i < 3; ++i) {
            if (free_most_popular_words[i].empty())
                return;
            std::cout << free_most_popular_words[i] << ' ';
        }
        std::cout << '\n';
    }
};

#endif //  FREQUENCYDICTIONARY_H
