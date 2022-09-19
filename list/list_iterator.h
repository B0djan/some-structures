#ifndef LIST_ITERATOR_H
#define LIST_ITERATOR_H

template< typename T > struct list_node;
template< typename T > class list;

template< typename T >
class list_const_iterator {
protected:
    list_node<T>* _current;
public:
    friend class list<T>;
    list_const_iterator() : _current(nullptr) {};

    const T& operator*() const {
        return _current->_node;
    }

    list_const_iterator& operator++() {
        if (_current)
            _current = _current->_next;
        return *this;
    }

    bool operator==(const list_const_iterator& rhs) const {
        return _current == rhs._current;
    }

    bool operator!= (const list_const_iterator& rhs) const {
        return _current != rhs._current;
    }

    list_node<T>* operator->() {
        return _current;
    }
};

template< typename T >
class list_iterator : public list_const_iterator<T> {
public:
    friend class list<T>;

    T& operator*() {
        return list_iterator<T>::_current->_node;
    }

    const T& operator*() const {
        return list_iterator<T>::operator*();
    }

    list_iterator& operator++() {
        list_iterator<T>::_current = list_iterator<T>::_current->_next;
        return *this;
    }
};

#endif //  LIST_ITERATOR_H
