#ifndef UNORDERED_MAP_H
#define UNORDERED_MAP_H

#include "list.h"
#include <string>

template< typename First, typename Second >
class Pair {
private:
    First _first;
    Second _second;
public:
    Pair() = default;
    explicit Pair(const First& first) : _first(first) {
        _second = Second();
    };
    explicit Pair(const First& first, Second& second): _first(first), _second(second) {};

    Second& second() { return _second; }
    First first() const { return _first; }
    Second second() const { return _second; }

};

template < typename Key, typename Value >
class unordered_map {
private:
    list <Pair <Key, Value> >* _baskets;
    list <Pair <Key, Value>* > _list_keys;

    size_t _size = 0;

    static int const _table_size = 10007;
    static int const _base       = 123;
    static int const _hash_cfA   = 930310127;
    static int const _hash_cfB   = 935489;

    int map_hash (const std::string& str) const;
    int map_hash (size_t key) const ;
    int map_hash (int key) const;

    size_t get_basket_number(size_t hash) const;
public:
    using const_iterator =  ::list_iterator<Pair<Key, Value>*>;
    using iterator =        ::list_const_iterator<Pair<Key, Value>*>;

    explicit unordered_map();
    ~unordered_map();

    Value& operator[] (const Key& key);

    const_iterator begin() const { return _list_keys.begin(); }
    iterator       begin()       { return _list_keys.begin(); }
    const_iterator end() const   { return _list_keys.end(); }
    iterator       end()         { return _list_keys.end(); }
};

template< typename Key, typename Value >
unordered_map<Key, Value>::unordered_map() {
    _baskets = new list<Pair<Key, Value>>[_table_size];
}

template< typename Key, typename Value >
unordered_map<Key, Value>::~unordered_map() {
    delete[] _baskets;
}

template< typename Key, typename Value >
Value& unordered_map<Key, Value>::operator[] (const Key& key) {
    size_t idx = get_basket_number(map_hash(key));
    auto &list = _baskets[idx];
    for (auto& it : list)
        if (it.first() == key) {
            return it.second();
        }
    auto new_pair_ptr = list.push_front(Pair<Key, Value> (key));
    _list_keys.push_back(new_pair_ptr);
    _size += 1;
    return new_pair_ptr->second();
}

template< typename Key, typename Value >
int unordered_map<Key, Value>::map_hash(const std::string& str) const{
    int hash = 0;
    for (auto ch : str)
        hash = (hash * _base + static_cast<int>(ch) );
    return hash;
}

template< typename Key, typename Value >
int unordered_map<Key, Value>::map_hash(int key) const{
    return (key * _hash_cfA) % _hash_cfB;
}

template<typename Key, typename Value>
int unordered_map<Key, Value>::map_hash(size_t key) const {
    return ((int)key * _hash_cfA) % _hash_cfB;
}

template< typename Key, typename Value >
size_t unordered_map<Key, Value>::get_basket_number(size_t hash) const{
    return hash % _table_size;
}

#endif //  UNORDERED_MAP_H
