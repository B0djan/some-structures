#ifndef LIST_H
#define LIST_H

#include "list_iterator.h"

template< typename T >
struct list_node {
    list_node<T>* _prev;
    list_node<T>* _next;
    T _node;

    list_node() : _prev(nullptr), _next(nullptr) {
        _node = T();
    }
    explicit list_node(const T rhs) : _node(rhs), _prev(nullptr), _next(nullptr) {}

    T* getNodePtr() { return &_node; }
};

template< class T >
class list {
private:
    list_node<T>* _head_ptr;
    list_node<T>* _tail_ptr;
    int _size = 0;
public:
    using const_iterator =  ::list_const_iterator<T>;
    using iterator =        ::list_iterator<T>;

    explicit list() : _head_ptr(nullptr), _tail_ptr(nullptr) {};
    ~list();

    T* push_back(const T& rhs);
    T* push_front(const T& rhs);
    void pop_front();
    void pop_back();

    const_iterator begin() const {
        const_iterator it;
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

    bool empty() { return _size == 0; }
};

template< typename T >
list<T>::~list() {
    auto node = _head_ptr;
    while (node) {
        auto next_node = node->_next;
        delete node;
        node = next_node;
    }
}

template< typename T >
T* list<T>::push_back(const T& rhs) {
    auto* new_node = new list_node<T>(rhs);
    if (!new_node)
        return nullptr;
    new_node->_prev = _tail_ptr;
    if (_tail_ptr)
        _tail_ptr->_next = new_node;
    _tail_ptr = new_node;
    if (!_head_ptr)
        _head_ptr = new_node;
    _size += 1;
    return new_node->getNodePtr();
}

template< typename T >
T* list<T>::push_front(const T& rhs) {
    auto* new_node = new list_node<T>(rhs);
    if (!new_node)
        return nullptr;
    new_node->_next = _head_ptr;
    if (_head_ptr)
        _head_ptr->_prev = new_node;
    _head_ptr = new_node;
    if (!_tail_ptr)
        _tail_ptr = new_node;
    return new_node->getNodePtr();
}

template< typename T >
void list<T>::pop_front() {
    if (empty()) { return; }
    list_node<T> * tmp = _head_ptr->_next;
    _head_ptr->_next = tmp->_next;
    tmp->_next->pre = _head_ptr;
    delete tmp;
    _size -= 1;
}

template< typename T >
void list<T>::pop_back() {
    if (empty()) { return; }
    list_node<T>* tmp = _tail_ptr->pre;
    tmp->pre->_next = _tail_ptr;
    _tail_ptr->pre = tmp->pre;
    delete tmp;
    _size -= 1;
}


#endif //  LIST_H
