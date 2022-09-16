#include "FrequencyDictionary.h"

template< typename Key, typename Value >
FrequencyDictionary<Key, Value>::FrequencyDictionary() = default;

template< typename Key, typename Value >
FrequencyDictionary<Key, Value>::~FrequencyDictionary() {
    for (auto i = 0; i < m_table_size; ++i) {
        delete m_basket[i];
    }
}

template< typename Key, typename Value >
size_t FrequencyDictionary<Key, Value>::getPolyhash(const std::string& str, size_t mod) {
    size_t hash = 0;
    for (auto ch : str)
        hash = ( hash * m_base % mod + static_cast<int>(ch) ) % mod;
    return hash;
}

template< typename Key, typename Value >
std::vector<std::string> FrequencyDictionary<Key, Value>::getMostPopularWords (size_t number_of_words) const{
    std::map<size_t, std::list<std::string>> number_copies_to_string;
    for (const auto& list : m_basket)
        for (const auto& node : list)
            number_copies_to_string[node.value].push_front(node.key);

    std::vector<std::string> answer;
    for (auto it = number_copies_to_string.rbegin();
         it != number_copies_to_string.rend() && answer.size() < number_of_words;
         ++it)
    {
        for (const auto& str : it->second )
            if (answer.size() < number_of_words)
                answer.push_back(str);
    }
    return answer;
}

template< typename Key, typename Value >
Value FrequencyDictionary<Key, Value>::search(const Key& rhs) const {
    size_t idx = FrequencyDictionary::getPolyhash(rhs, m_table_size);
    auto& basket_list = m_basket[idx];
    if (basket_list.empty())
        return -1; // косяк
    auto search_p = std::find_if(basket_list.begin(), basket_list.end(),
                                 [rhs](const StringToNumberCopies& node) { return rhs == node.key; });
    if (search_p == basket_list.end())
        return -1; // косяк
    return static_cast<int>(search_p->value);
}

template< typename Key, typename Value >
void  FrequencyDictionary<Key, Value>::insert(const Key& rhs) {
    size_t idx = FrequencyDictionary::getPolyhash(rhs, m_table_size);
    auto& basket_list = m_basket[idx];
    auto search_p = std::find_if(basket_list.begin(), basket_list.end(),
                                 [rhs](const StringToNumberCopies& node) { return rhs == node.key; });
    if (search_p == basket_list.end()) {
        basket_list.push_front({rhs, 1});
    } else {
        search_p->value += 1;
    }
}

template< typename Key, typename Value >
void FrequencyDictionary<Key, Value>::printThreeMostPopularWords() const{
    auto words = getMostPopularWords(3);
    for (const auto& word : words) {
        std::cout << word  << ' ';
    }
    std::cout << '\n';
}

