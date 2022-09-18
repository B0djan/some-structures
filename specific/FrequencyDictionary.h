#ifndef _FREQUENCYDICTIONARY_H
#define _FREQUENCYDICTIONARY_H

#include "List.h"
#include "UnorderedMap.h"

class FrequencyDictionary {

private:
    UnorderedMap<std::string, int> string_to_number;
    UnorderedMap<int, List<std::string>> number_to_string;
    std::string* free_most_popular_words;

    // может быть указатель обрезается интегером в списке.

    void fill() {
        for (const auto& p : string_to_number) {
            auto idx = p->getSecond();
            auto val = p->getFirst();
            number_to_string[idx].push_back(val);
        }
        int i = 0;
        for (auto it = number_to_string.begin(); it != number_to_string.end() && i < 3; ++it) {
            for (const auto& word: it->node->getSecond()) {
                if (i >= 3) { break; }
                free_most_popular_words[i] = word;
                i+= 1;
            }
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
    }
};

#endif //  FREQUENCYDICTIONARY_H
