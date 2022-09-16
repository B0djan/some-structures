#include <iostream>

template<typename T = int> class array;
template<typename T> std::ostream& operator<< (std::ostream& os, const array<T>& a);
template<typename T> std::istream& operator>> (std::istream& is, array<T>& a);

template<typename T>
class array {
    T* data = nullptr;
    size_t size;           // количество реальных элементов в массиве
    size_t capacity;
protected:
    size_t resize();
    size_t resize(size_t new_size);

    friend std::ostream& operator<< <> (std::ostream& os, const array<T>& a);
    friend std::istream& operator>> <> (std::istream& is, array<T>& a);
public:
    explicit array();
    explicit array(size_t init_size, T init_value = 0);

    array(const array& other);
    array(const array& other, size_t index_from, size_t number_of_elements);

    ~array();

    void push_back(const T& new_element);
    void pop_back();
    void insert(size_t index, const T& new_element);
    void insert(size_t index_from, const array<T>& sub_array);
    void erase(size_t index);
    void erase(size_t index_from, size_t number_of_elements);
    array<T> get_subsequence(size_t index_from, size_t number_of_elements);

    size_t get_size() const;
    size_t get_capacity() const;

    T& operator[] (size_t index);
    const T& operator[] (size_t index) const;
    array<T>& operator= (const array<T>& other);
};


template<typename T>
std::ostream& operator<< (std::ostream& os, const array<T>& a) {
    for ( size_t i = 0; i < a.size; ++i )
        os << a.data[i] << ' ';
    return os << std::endl;
}

template<typename T>
std::istream& operator>> (std::istream& is, array<T>& a) {
    size_t n;
    is >> n;
    a.resize(n);
    a.size = n;
    for ( size_t i = 0; i < n; ++i ) {
        is >> a.data[i];
    }
    return is;
}

template<typename T>
array<T>::array() : size(0 ), capacity(1 ) {
     data = new T[capacity];
}

template<typename T>
array<T>::array(size_t init_size, T init_value) : size (init_size ), capacity (2 * size ) {
    data = new T[capacity];
    for ( auto i = 0; i < size; ++i )
        data[i] = init_value;
}

template<typename T>
array<T>::array(const array& other) : size (other.size ), capacity (other.capacity ) {
    if (this != &other) {
        delete[] data;
        data = new T[capacity];
        for (auto i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }
}

template<typename T>
array<T>::array(const array& other, size_t index_from, size_t number_of_elements) {
    if (this != &other) {
        delete[] data;
        size = (other.size - index_from > number_of_elements) ? number_of_elements : other.size - index_from;
        capacity = 2 * size;
        data = new T[capacity];
        for ( size_t i = 0, j = index_from; j < index_from + number_of_elements && j < other.size; ++j, ++i ) {
             data[i] = other.data[j];
        }
    }
}

template<typename T>
array<T>::~array() { delete[] data; }

template<typename T>
size_t array<T>::resize() {
    capacity *= 2;
    T* new_data = new T[capacity];
    for ( size_t i = 0; i < size; ++i ) {
        new_data[i] = data[i];
    }
    delete[] data;
    data = new_data;
    return capacity;
}

template<typename T>
size_t array<T>::resize(size_t new_size) {
    capacity = new_size;
    return resize();
}

template<typename T>
size_t array<T>::get_size() const { return size; }

template<typename T>
size_t array<T>::get_capacity() const { return capacity; }

template<typename T>
void array<T>::push_back(const T& new_element) {
    if (size == capacity)
        resize();
    data[++size - 1] = new_element;
}

template<typename T>
void array<T>::pop_back() {
    if ( size > 0) {
        size = size - 1;
    }                                                               // or exception
}

template<typename  T>
void array<T>::insert(size_t index, const T& new_element) {
    if ( index > size || index < 0 ) { return; }                     // or exception
    if ( size == capacity )          { resize(); }
    for ( auto k = size; k > index; --k ) {
        size_t i = k - 1;
        data[k] = data[i];
    }
    size += 1;
    data[index] = new_element;
}

template<typename  T>
void array<T>::insert(size_t index, const array<T>& sub_array){
    if ( index > size || index < 0 ) { return; }                    // or exception
    if ( this->size + sub_array.get_size() >= capacity ) {
        resize(size + sub_array.get_size());
    }
    auto old_size = size;
    size += sub_array.get_size();
    for ( size_t k = old_size, l = size; k > index; --k, --l ) {
        auto i = k - 1;
        auto j = l - 1;
        data[j] = data[i];
    }
    for (size_t i = index, j = 0; i < index + sub_array.get_size(); ++i, ++j )
        data[i] = sub_array[j];
}

template<typename T>
void array<T>::erase(size_t index) {
    if ( index > size || index < 0 ) { return; }                     // or exception
    for ( size_t i = index + 1; i < size; ++i ) {
        data[i - 1] = data[i];
    }
    size -= 1;
}

template<typename T>
void array<T>::erase(size_t index, size_t number_of_elements) {
    if ( index > size || index < 0 )         { return; }             // or exception
    if ( size - index < number_of_elements ) { return; }             // or exception
    for ( size_t i = index + number_of_elements; i < size; ++i ) {
        data[i - number_of_elements] = data[i];
    }
    size -= number_of_elements;
}

template<typename T>
T& array<T>::operator[] (size_t index) {
    if ( index < 0 && index > size - 1 ) {} // or exception
    return { data[index] };
}

template<typename T>
const T& array<T>::operator[] (size_t index) const {
    if ( index < 0 && index > size - 1 ) {}  // or exception
    return { data[index] };
}

template<typename T>
array<T> array<T>::get_subsequence(size_t index_from, size_t number_of_elements) {
    if ( index_from + number_of_elements > size ) {}               // throw warning
    array<T> subsequence (*this, index_from, number_of_elements);
    return subsequence;
}

template<typename T>
array<T>& array<T>::operator= (const array<T>& other) {
    if(this != &other)
    {
        size = other.size;
        capacity = other.capacity;
        delete[] data;
        data = new T[capacity];
        for ( auto i = 0; i < size; ++i ) {
            data[i] = other.data[i];
        }
    }
    return *this;
}

