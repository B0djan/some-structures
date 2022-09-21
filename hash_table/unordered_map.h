#ifndef UNORDERED_MAP_H
#define UNORDERED_MAP_H

#include "list.h"
#include <string>

template< typename First, typename Second > struct Pair;
template < typename Key, typename Value > class unordered_map;

template < typename Key, typename Value >
class unordered_map_const_iterator {
public:
    Pair<Key, Value>* _current;
public:
    friend class unordered_map<Key, Value>;
    unordered_map_const_iterator() : _current(nullptr) {};

    const Pair<Key, Value>& operator*() const {
        return (*_current);
    }

    unordered_map_const_iterator& operator++() {
        if (_current)
            _current = _current->_next;
        return *this;
    }

    bool operator==(const unordered_map_const_iterator& rhs) const {
        return _current == rhs._current;
    }

    bool operator!= (const unordered_map_const_iterator& rhs) const {
        return _current != rhs._current;
    }

    Pair<Key, Value>* operator->() {
        return _current;
    }
};

template < typename Key, typename Value >
class unordered_map_iterator : public unordered_map_const_iterator<Key, Value> {
public:
    friend class unordered_map<Key, Value>;

    Pair<Key, Value>& operator*() {
        return unordered_map_iterator<Key, Value>::_current->_node;
    }

    const Pair<Key, Value>& operator*() const {
        return unordered_map_iterator<Key, Value>::operator*();
    }

    unordered_map_iterator& operator++() {
        unordered_map_iterator<Key, Value>::_current = unordered_map_iterator<Key, Value>::_current->_next;
        return *this;
    }
};


template< typename First, typename Second >
struct Pair {
public:
    First _first;
    Second _second;
    Pair* _next;
    Pair* _prev;
public:
    Pair() = default;
    explicit Pair(const First& first) : _first(first) , _next(nullptr), _prev(nullptr) {
        _second = Second();
    };
    explicit Pair(const First& first, Second& second):
        _first(first), _second(second), _next(nullptr), _prev(nullptr)  {};

    Second& second() { return _second; }
    First first() const { return _first; }
    Second second() const { return _second; }

};

template < typename Key, typename Value >
class unordered_map {
private:
    list <Pair <Key, Value> >* _baskets;
    Pair<Key, Value>* _tail_ptr = nullptr;
    Pair<Key, Value>* _head_ptr = nullptr;

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
    using const_iterator =  ::unordered_map_iterator<Key, Value>;
    using iterator =        ::unordered_map_const_iterator<Key, Value>;

    explicit unordered_map();
    ~unordered_map();

    Value& operator[] (const Key& key);
    void erase (const Key& key);

    const_iterator begin() const {
        iterator it;
        it._current = _head_ptr;
        return it;
    }

    const_iterator end() const {
        const_iterator it;
        if (_tail_ptr)
            it._current = _tail_ptr->_next;
        return it;
    }

    iterator begin() {
        iterator it;
        it._current = _head_ptr;
        return it;
    }

    iterator end() {
        iterator it;
        if (_tail_ptr)
            it._current = _tail_ptr->_next;
        return it;
    }
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
    new_pair_ptr->_prev = _tail_ptr;
    if (_tail_ptr)
        _tail_ptr->_next = new_pair_ptr;
    _tail_ptr = new_pair_ptr;
    if (!_head_ptr)
        _head_ptr = new_pair_ptr;
    _size += 1;
    return new_pair_ptr->second();
}

template< typename Key, typename Value >
void unordered_map<Key, Value>::erase(const Key& key) {
    size_t idx = get_basket_number(map_hash(key));
    auto &list = _baskets[idx];
    for (auto& it : list)
        if (it.first() == key) {
            if (it._prev)
                it._prev->_next = it._next;
            if (it._next)
                it._next->_prev = it._prev;
            if (_head_ptr == &it)
                _head_ptr = (it._next);
            if (_tail_ptr == &it)
                _tail_ptr = (it._prev);
        }
    _size -= 1;
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
