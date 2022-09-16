#ifndef _UNORDERED_MAP_H
#define _UNORDERED_MAP_H

#include "UnorderedMapIterator.h"
#include "List.h"

#include <string>

template< typename First, typename Second >
class Pair {
private:
    First _first;
    Second _second;
public:
    Pair() = default;
    explicit Pair(const First& first): _first(first) {};
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

    explicit UnorderedMap() = default;
    ~UnorderedMap();
    // Value search(const Key& key) const;
    // void insert(const Key& key, const Value& value);

    size_t getSize() const {
        return size;
    }

    Value& operator[] (Key key) {
        size_t idx = getBasketNumber(MapHash(key));
        List<Pair<Key, Value>>& list = m_basket[idx];
        for (auto& it : list) {
            if (it.first == key) {
                return it.second;
            }
        }
        auto new_pair = Pair<Key, Value> (key);
        list.push_back(new_pair);
        list_keys.push_back(new_pair);
        return (list.end()->node.second);
    }

    /*
    const Value& operator[] (Key key) const {
        size_t idx = getBasketNumber(MapHash(key));
        auto list = m_basket[idx];
        for (const auto it = list.begin(); it != list.end(); ++it) {
            auto p = it->node;
            if (p.first == key) {
                return p.second;
            }
        }
        return nullptr;
    }
     */

    int contained(const Key& key) const{
        size_t idx = getBasketNumber(MapHash(key, _table_size));
        auto list = m_basket[idx];
        for (const auto it = list.begin(); it != list.end(); ++it) {
            auto p = it->node;
            if (p.first == key) {
                return true;
            }
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
    List<Pair<Key, Value>> *m_basket = new List<Pair<Key, Value>>[_table_size];
    List<Pair<Key, Value>> list_keys;

    size_t size = 0;

    static int const _table_size = 10007;
    static int const _base = 123;
    static int const _hash_cfA = 930310127;
    static int const _hash_cfB = 935489;

    int MapHash (const std::string& str);
    int MapHash (size_t key);
    int MapHash (int key);

    size_t getBasketNumber(size_t hash);
};

template< typename Key, typename Value >
UnorderedMap<Key, Value>::~UnorderedMap() {
    // ****** дополнить ******** //
}

template< typename Key, typename Value >
int UnorderedMap<Key, Value>::MapHash(const std::string& str) {
    size_t hash = 0;
    for (auto ch : str)
        hash = (hash * _base + static_cast<int>(ch) );
    return hash;
}

template< typename Key, typename Value >
int UnorderedMap<Key, Value>::MapHash(size_t key) {
    return (key * _hash_cfA) % _hash_cfB;
}

template< typename Key, typename Value >
int UnorderedMap<Key, Value>::MapHash(int key) {
    return (key * _hash_cfA) % _hash_cfB;
}

template< typename Key, typename Value >
size_t UnorderedMap<Key, Value>::getBasketNumber(size_t hash) {
    return hash % _table_size;
}

#endif //  _UNORDERED_MAP_H
