#ifndef _UNORDERED_MAP_H
#define _UNORDERED_MAP_H

#include "List.h"

#include <string>
#include <vector>

template< typename First, typename Second >
class Pair {
private:
    First _first;
    Second _second;
public:
    Pair() = default;
    explicit Pair(const First& first, const Second& second): _first(first), _second(second) {};

    First& setFirst() { return _first; }
    Second& setSecond() { return _second; }
    First getFirst() const { return _first; }
    Second getSecond() const { return _second; }

};

template < typename Key, typename Value >
class UnorderedMap {
public:
    using const_iterator =  ::ListIterator<Pair<Key, Value>>;
    using iterator =        ::ListConstIterator<Pair<Key, Value>>;

    explicit UnorderedMap();
    ~UnorderedMap();
    // Value search(const Key& key) const;
    // void insert(const Key& key, const Value& value);

    size_t getSize() const {
        return size;
    }

    void insert(const Key& key, const Value& value) {
        size_t idx = getBasketNumber(MapHash(key));
        auto &list = m_basket[idx];
        for (auto& it : list)
            if (it.getFirst() == key) {
                it.setSecond() = value;
                return;
            }
        list.push_back(Pair<Key, Value> (key, value));
        list_keys.push_back(Pair<Key, Value> (key, value));
    }

    bool contained(const Key& key) const{
        size_t idx = getBasketNumber(MapHash(key));
        auto &list = m_basket[idx];
        for (auto& it : list)
            if (it.getFirst() == key) {
                return true;
            }
        return false;
    }

    const_iterator begin() const
    {
        return list_keys.begin();
    }

    const_iterator end() const
    {
        return list_keys.end();
    }

    iterator begin()
    {
        return list_keys.begin();
    }

    iterator end()
    {
        return list_keys.end();
    }

private:
    std::vector<List<Pair<Key, Value>>> m_basket;
    List<Pair<Key, Value>> list_keys;

    size_t size = 0;

    static int const _table_size = 10007;
    static int const _base = 123;
    static int const _hash_cfA = 930310127;
    static int const _hash_cfB = 935489;

    int MapHash (const std::string& str) const;
    int MapHash (size_t key) const ;
    int MapHash (int key) const;

    size_t getBasketNumber(size_t hash) const;
};

template< typename Key, typename Value >
UnorderedMap<Key, Value>::UnorderedMap() {
    m_basket.resize(_table_size);
}

template< typename Key, typename Value >
UnorderedMap<Key, Value>::~UnorderedMap() {
    // ****** дополнить ******** //
}

template< typename Key, typename Value >
int UnorderedMap<Key, Value>::MapHash(const std::string& str) const{
    int hash = 0;
    for (auto ch : str)
        hash = (hash * _base + static_cast<int>(ch) );
    return hash;
}

template< typename Key, typename Value >
int UnorderedMap<Key, Value>::MapHash(int key) const{
    return (key * _hash_cfA) % _hash_cfB;
}

template<typename Key, typename Value>
int UnorderedMap<Key, Value>::MapHash(size_t key) const {
    return ((int)key * _hash_cfA) % _hash_cfB;
}

template< typename Key, typename Value >
size_t UnorderedMap<Key, Value>::getBasketNumber(size_t hash) const{
    return hash % _table_size;
}

#endif //  _UNORDERED_MAP_H
