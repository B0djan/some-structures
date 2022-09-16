#ifndef _PAIR_H
#define _PAIR_H

template< typename First, typename Second >
class Pair {
public:
    First first;
    Second second;

    Pair() : next(nullptr) {};
    Pair(const First& first, const Second& second): first(first), second(second), next(nullptr) {};
private:
    Pair* next;
};

#endif //  _PAIR_H
