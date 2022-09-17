#ifndef _FREQUENCYDICTIONARY_H
#define _FREQUENCYDICTIONARY_H

#include "List.h"
#include "UnorderedMap.h"

class FrequencyDictionary {

private:
    UnorderedMap<std::string, int> string_to_number;
    UnorderedMap<int, List<std::string>> number_to_string;
public:
    explicit FrequencyDictionary() = default;

    void add_word(const std::string& word) {

    }
    void printThreeMostPopularWords() const;
};

#endif //  FREQUENCYDICTIONARY_H
