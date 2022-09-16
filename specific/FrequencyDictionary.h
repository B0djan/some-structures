#ifndef _FREQUENCYDICTIONARY_H
#define _FREQUENCYDICTIONARY_H


#include "List.h"


class FrequencyDictionary {

private:
    std::vector<std::string> getMostPopularWords (size_t number_of_words) const;

public:
    void printThreeMostPopularWords() const;
};

#endif //  FREQUENCYDICTIONARY_H
