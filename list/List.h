#ifndef _LIST_H
#define _LIST_H

#include "ListIterator.h"

template<typename T>
struct ListNode
{
    ListNode<T>* prev = nullptr;
    ListNode<T>* next = nullptr;
    T node;

    ListNode() : prev(nullptr), next(nullptr) {
        node = T();
    }
    explicit ListNode(const T& rhs) : node(rhs), prev(nullptr), next(nullptr) {}
};

template<class T>
class List {
public:
    using const_iterator =  ::ListConstIterator<T>;
    using iterator =        ::ListIterator<T>;

    explicit List() : head_ptr(new ListNode<T>()), tail_ptr(new ListNode<T>())
    {
        head_ptr->next = tail_ptr;
        tail_ptr->prev = head_ptr;
    }

    ~List()
    {
        auto it = head_ptr->next;
        while (it) {
            auto to_free = it;
            it = it->next;
            delete to_free;
        }
    }

    const_iterator begin() const
    {
        const_iterator it;
        it.current = head_ptr->next;
        return it;
    }

    const_iterator end() const
    {
        const_iterator it;
        it.current = tail_ptr;
        return it;
    }

    iterator begin()
    {
        iterator it;
        it.current = head_ptr->next;
        return it;
    }

    iterator end()
    {
        iterator it;
        it.current = tail_ptr;
        return it;
    }

    auto push_back(const T& rhs)
    {
        auto *tmp = new ListNode<T>(rhs);
        tail_ptr->prev->next = tmp;
        tmp->prev = tail_ptr->prev;
        tmp->next = tail_ptr;
        tail_ptr->prev = tmp;
        size += 1;
        return &tmp->node;
    }

    void push_front(const T& rhs)
    {
        auto *tmp = new ListNode<T>(rhs);
        head_ptr->next->pre = tmp;
        tmp->next = head_ptr->next;
        head_ptr->next = tmp;
        tmp->pre = head_ptr;
        size += 1;
    }

    void pop_front()
    {
        if (empty()) { return; }
        ListNode<T> * tmp = head_ptr->next;
        head_ptr->next = tmp->next;
        tmp->next->pre = head_ptr;
        delete tmp;
        size -= 1;
    }
    void pop_back()
    {
        if (empty()) { return; }
        ListNode<T>* tmp = tail_ptr->pre;
        tmp->pre->next = tail_ptr;
        tail_ptr->pre = tmp->pre;
        delete tmp;
        size -= 1;
    }

    bool empty()
    {
        return size == 0;
    }

    /*
    // Копировать конструктор
    hn_list(const hn_list<T> & rhs) :head_node_ptr(new hn_list_node<T>()), tail_node_ptr(new hn_list_node<T>()), theSize(rhs.theSize)
    {
        cout << "Введите конструкцию копии hn_list" << endl;
        head_node_ptr->next = tail_node_ptr;
        tail_node_ptr->pre = head_node_ptr;
        for (const_iterator it = rhs.begin(); it != rhs.end(); it++)
        {
            push_back(*it);
        }
    }

    void push_back(const hn_list_node<T>& rhs)
    {
        hn_list_node<T> *tmp = new hn_list_node<T>(rhs);
        tail_node_ptr->pre->next = tmp;
        tmp->pre = tail_node_ptr->pre;
        tmp->next = tail_node_ptr;
        tail_node_ptr->pre = tmp;
        ++theSize;
    }

    void push_front(const T& rhs)
    {
        hn_list_node<T> * tmp = new hn_list_node<T>(rhs);
        head_node_ptr->next->pre = tmp;
        tmp->next = head_node_ptr->next;
        head_node_ptr->next = tmp;
        tmp->pre = head_node_ptr;
        ++theSize;
    }
    void pop_front()
    {
        if (empty())
            return;
        hn_list_node<T> * tmp = head_node_ptr->next;
        head_node_ptr->next = tmp->next;
        tmp->next->pre = head_node_ptr;
        delete tmp;
        --theSize;
    }
    void pop_back()
    {
        if (empty())
            return;
        hn_list_node<T>* tmp = tail_node_ptr->pre;
        tmp->pre->next = tail_node_ptr;
        tail_node_ptr->pre = tmp->pre;
        delete tmp;
        --theSize;
    }
    bool empty()
    {
        return theSize == 0 ? true : false;
    }
    void clear()
    {
        while (!empty())
        {
            pop_back();
        }
    }
    void resize(int num)
    {
        if (num==theSize)
        {
            return;
        }
        else if (num > theSize)
        {
            int n = num - theSize;
            for (int i = 0; i < n; i++)
            {
                push_back(T());
            }
        }
        else
        {
            int n = theSize - num;
            for (int i = 0; i < n; i++)
            {
                pop_back();
            }
        }

    }
    const T& front()
    {
        return head_node_ptr->next->node;
    }
    const T& back()
    {
        return tail_node_ptr->pre->node;
    }
    int size()const
    {
        return theSize;
    }

    // Должен реализовать другую версию итератора
    void insert(const_iterator it, const T& rhs)
    {
        hn_list_node<T> * tmp = it.current;
        hn_list_node<T> * new_node = new hn_list_node<T>(rhs);
        tmp->pre->next = new_node;
        new_node->pre = tmp->pre;
        new_node->next = tmp;
        tmp->pre = new_node;
        ++theSize;

    }

    // Удалить только первый равный узел
    void remove(const T& rhs)
    {
        if (empty())
            return;
        else
        {
            for (iterator it = begin(); it != end(); it++)
            {
                if (*it == rhs)
                {
                    cout << "remove  " <<*it<< endl;
                    hn_list_node<T> * tmp = it.current;
                    tmp->next->pre = tmp->pre;
                    tmp->pre->next = tmp->next;
                    delete tmp;
                    --theSize;
                    return;// Он был удален и должен быть возвращен, потому что итератор был признан недействительным
                }
            }
        }
    }
    // Возвращаем hn_list <T> & здесь для поддержки четного ожидания, т.е. ld = lc = lb;
    // Может также вернуть void
    const hn_list<T>& operator = (const hn_list<T>& rhs)
    {
        cout << «Введите оператор присваивания» << endl;
        if (this == &rhs)
        {
            return *this;
        }
        else
        {
            this->clear();
            hn_list::const_iterator it = rhs.begin();
            for (; it != rhs.end(); it++)
            {
                push_back(*it);
            }
            return *this;
        }
    }


     */

private:
    ListNode<T>* head_ptr;
    ListNode<T>* tail_ptr;
    int size = 0;
};



/*
template< typename Node, typename T>
class ListIterator {
private:
    T* _ptr;
public:
    ListIterator() : _ptr (nullptr) {}
    ListIterator(Node* ptr) : _ptr(ptr) {};

    ListIterator& operator++() {
        if (_ptr != nullptr)
            _ptr = _ptr->next;
        return *this;
    }

    T& operator*() {
        return _ptr->value;
    }

    bool operator==(const Node* ptr) const {
        return (ptr == _ptr);
    }
    bool operator!=(const Node* ptr) const {
        return (ptr != _ptr);
    }
};

template< typename T >
class List {
    struct Node {
        T value;
        Node* next;
        explicit Node(const T& value) : value(value), next(nullptr) {}
    };
private:
    size_t size = 0;
    Node* head;
    Node* tail;
public:
    typedef ListIterator<Node, T> iterator;
    typedef ListIterator<const Node, const T> const_iterator;

    List();
    ~List();

    void push_back(T rhs);
    bool empty();

    iterator begin() { return iterator{head}; }
    const_iterator begin() const { return const_iterator{head}; }
    iterator end() { return iterator{nullptr}; }
    const_iterator end() const { return const_iterator{nullptr}; }
};

template< typename T >
List<T>::List() : head(nullptr), tail(nullptr), size(0) {}

template< typename T >
List<T>::~List() {
    Node* it = head;
    while (it) {
        Node* prev = it;
        it = it->next;
        delete prev;
    }
}

template< typename T >
void List<T>::push_back(T rhs) {
    Node* new_node = new Node(rhs);
    if (!tail) {
        head = new_node;
        tail = new_node;
    }
    tail->next = new_node;
    tail = new_node;
    size += 1;
}

template< typename T >
bool List<T>::empty() {
    return head == tail;
}

 */

#endif //  _LIST_H
