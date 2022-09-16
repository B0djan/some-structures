#ifndef _LISTITERATOR_H
#define _LISTITERATOR_H

template< typename T > struct ListNode;
template< typename T > class List;

template< typename T >
class ListConstIterator {
public:
    friend class List<T>;
    ListConstIterator() : current(nullptr) {};

    const T& operator*() const {
        return current->node;
    }

    ListConstIterator& operator++() {
        current = current->next;
        return *this;
    }

    bool operator==(const ListConstIterator& rhs) const {
        return current == rhs.current;
    }

    bool operator!= (const ListConstIterator& rhs) const {
        return current != rhs.current;
    }

    ListNode<T>* operator->() {
        return current;
    }

protected:
    ListNode<T>* current;
};

template< typename T >
class ListIterator : public ListConstIterator<T> {
public:
    friend class List<T>;

    T& operator*() {
        return ListIterator<T>::current->node;
    }

    const T& operator*() const {
        return ListIterator<T>::operator*();
    }

    ListIterator& operator++() {
        ListIterator<T>::current = ListIterator<T>::current->next;
        return *this;
    }
};

#endif //  _LISTITERATOR_H
